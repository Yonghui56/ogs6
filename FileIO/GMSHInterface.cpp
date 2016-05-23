/**
 * \file
 * \author Thomas Fischer
 * \date   2010-04-29
 * \brief  Implementation of the GMSHInterface class.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 * @file GMSHInterface.cpp
 * @date 2010-04-29
 * @author Thomas Fischer
 */

#include <fstream>
#include <memory>
#include <vector>

#include <logog/include/logog.hpp>

#include "BaseLib/BuildInfo.h"
#include "BaseLib/FileTools.h"
#include "BaseLib/StringTools.h"

#include "FileIO/GMSHInterface.h"
#include "FileIO/GmshIO/GMSHAdaptiveMeshDensity.h"
#include "FileIO/GmshIO/GMSHFixedMeshDensity.h"

#include "GeoLib/AnalyticalGeometry.h"
#include "GeoLib/GEOObjects.h"
#include "GeoLib/Point.h"
#include "GeoLib/Polygon.h"
#include "GeoLib/Polyline.h"
#include "GeoLib/PolylineWithSegmentMarker.h"
#include "GeoLib/QuadTree.h"

#include "MathLib/LinAlg/Solvers/GaussAlgorithm.h"

#include "MeshLib/Elements/Elements.h"
#include "MeshLib/Mesh.h"
#include "MeshLib/MeshEditing/ElementValueModification.h"
#include "MeshLib/Node.h"

namespace FileIO
{
GMSHInterface::GMSHInterface(GeoLib::GEOObjects & geo_objs,
                             bool /*include_stations_as_constraints*/,
                             GMSH::MeshDensityAlgorithm mesh_density_algorithm,
                             double param1,
                             double param2,
                             std::size_t param3,
                             std::vector<std::string>& selected_geometries) :
    _n_lines(0), _n_plane_sfc(0), _geo_objs(geo_objs), _selected_geometries(selected_geometries)
{
    switch (mesh_density_algorithm) {
    case GMSH::MeshDensityAlgorithm::FixedMeshDensity:
        _mesh_density_strategy = new GMSH::GMSHFixedMeshDensity(param1);
        break;
    case GMSH::MeshDensityAlgorithm::AdaptiveMeshDensity:
        _mesh_density_strategy = new GMSH::GMSHAdaptiveMeshDensity(param1, param2, param3);
        break;
    }
}

GMSHInterface::~GMSHInterface()
{
    for (auto * gmsh_pnt : _gmsh_pnts)
        delete gmsh_pnt;
    delete _mesh_density_strategy;
    for (auto * polygon_tree : _polygon_tree_list)
        delete polygon_tree;
}

int GMSHInterface::writeGeoFile(GeoLib::GEOObjects &geo_objects, std::string const& file_name)
{
    std::vector<std::string> names;
    geo_objects.getGeometryNames(names);

    if (names.empty())
    {
        ERR ("No geometry information available.");
        return 1;
    }

    bool const multiple_geometries = (names.size() > 1);
    std::string merge_name("MergedGeometry");
    if (multiple_geometries)
    {
        if (geo_objects.mergeGeometries (names, merge_name) != 1)
            return 2;
        names.clear();
        names.push_back(merge_name);
    }
    else
        merge_name = names[0];

    // default parameters for GMSH interface
    double param1(0.5);    // mesh density scaling on normal points
    double param2(0.05);   // mesh density scaling on station points
    std::size_t param3(2); // points per leaf
    GMSHInterface gmsh_io(geo_objects, true, FileIO::GMSH::MeshDensityAlgorithm::AdaptiveMeshDensity, param1, param2, param3, names);
    int const writer_return_val = gmsh_io.writeToFile(file_name);

    if (multiple_geometries)
    {
        geo_objects.removeSurfaceVec(merge_name);
        geo_objects.removePolylineVec(merge_name);
        geo_objects.removePointVec(merge_name);
    }
    return (writer_return_val==1) ? 0 : 3;
}

bool GMSHInterface::isGMSHMeshFile(const std::string& fname)
{
    std::ifstream input(fname.c_str());

    if (!input) {
        ERR("GMSHInterface::isGMSHMeshFile(): Could not open file %s.", fname.c_str());
        return false;
    }

    std::string header_first_line;
    input >> header_first_line;
    if (header_first_line.find("$MeshFormat") != std::string::npos) {
        // read version
        std::string version;
        getline(input, version);
        getline(input, version);
        INFO("GMSHInterface::isGMSHMeshFile(): Found GMSH mesh file version: %s.",
             version.c_str());
        input.close();
        return true;
    }

    return false;
}

MeshLib::Mesh* GMSHInterface::readGMSHMesh(std::string const& fname)
{
    std::string line;
    std::ifstream in(fname.c_str(), std::ios::in);
    if (!in.is_open())
    {
        WARN ("GMSHInterface::readGMSHMesh() - Could not open file %s.", fname.c_str());
        return nullptr;
    }

    getline(in, line); // $MeshFormat keyword
    if (line.find("$MeshFormat") == std::string::npos)
    {
        in.close();
        WARN ("No GMSH file format recognized.");
        return nullptr;
    }

    getline(in, line); // version-number file-type data-size
    if (line.substr(0,3).compare("2.2") != 0) {
        WARN("Wrong gmsh file format version.");
        return nullptr;
    }

    if (line.substr(4,1).compare("0") != 0) {
        WARN("Currently reading gmsh binary file type is not supported.");
        return nullptr;
    }
    getline(in, line); //$EndMeshFormat

    std::vector<MeshLib::Node*> nodes;
    std::vector<MeshLib::Element*> elements;
    std::vector<int> materials;
    std::map<unsigned, unsigned> id_map;
    while (line.find("$EndElements") == std::string::npos)
    {
        // Node data
        getline(in, line); //$Nodes Keywords
        if (line.find("$Nodes") != std::string::npos)
        {
            std::size_t n_nodes(0);
            long id;
            double x, y, z;
            in >> n_nodes >> std::ws;
            nodes.resize(n_nodes);
            for (std::size_t i = 0; i < n_nodes; i++) {
                in >> id >> x >> y >> z >> std::ws;
                id_map.insert(std::map<unsigned, unsigned>::value_type(id, i));
                nodes[i] = new MeshLib::Node(x,y,z,id);
            }
            getline(in, line); // End Node keyword $EndNodes
        }

        // Element data
        if (line.find("$Elements") != std::string::npos)
        {
            std::size_t n_elements(0);
            if (! (in >> n_elements >> std::ws)) { // number-of-elements
                ERR("Read GMSH mesh does not contain any elements");
            }
            elements.reserve(n_elements);
            materials.reserve(n_elements);
            for (std::size_t i = 0; i < n_elements; i++)
            {
                MeshLib::Element* elem(nullptr);
                int mat_id(0);
                std::tie(elem, mat_id) = readElement(in, nodes, id_map);

                if (elem) {
                    elements.push_back(elem);
                    materials.push_back(mat_id);
                }
            }
            getline(in, line); // END keyword
        }

        if (line.find("PhysicalNames") != std::string::npos)
        {
            std::size_t n_lines(0);
            in >> n_lines >> std::ws; // number-of-lines
            for (std::size_t i = 0; i < n_lines; i++)
                getline(in, line);
            getline(in, line); // END keyword
        }
    }
    in.close();
    if (elements.empty()) {
        for (auto it(nodes.begin()); it != nodes.end(); ++it) {
            delete *it;
        }
        return nullptr;
    }

    MeshLib::Mesh * mesh(new MeshLib::Mesh(
        BaseLib::extractBaseNameWithoutExtension(fname), nodes, elements));

    boost::optional<MeshLib::PropertyVector<int> &> opt_material_ids(
        mesh->getProperties().createNewPropertyVector<int>(
            "MaterialIDs", MeshLib::MeshItemType::Cell, 1)
    );
    if (!opt_material_ids) {
        WARN("Could not create PropertyVector for MaterialIDs in Mesh.");
    } else {
        MeshLib::PropertyVector<int> & material_ids(opt_material_ids.get());
        material_ids.insert(material_ids.end(), materials.cbegin(),
            materials.cend());
    }

    MeshLib::ElementValueModification::condense(*mesh);

    INFO("\t... finished.");
    INFO("Nr. Nodes: %d.", nodes.size());
    INFO("Nr. Elements: %d.", elements.size());

    return mesh;
}

void GMSHInterface::readNodeIDs(std::ifstream &in,
                                unsigned n_nodes,
                                std::vector<unsigned> &node_ids,
                                std::map<unsigned, unsigned> const& id_map)
{
    unsigned idx;
    for (unsigned i = 0; i < n_nodes; i++)
    {
        in >> idx;
        node_ids.push_back(id_map.at(idx));
    }
}

std::pair<MeshLib::Element*, int>
GMSHInterface::readElement(std::ifstream &in,
    std::vector<MeshLib::Node*> const& nodes,
    std::map<unsigned, unsigned> const& id_map)
{
    unsigned idx, type, n_tags, dummy;
    int mat_id;
    std::vector<unsigned> node_ids;
    std::vector<MeshLib::Node*> elem_nodes;
    in >> idx >> type >> n_tags >> mat_id >> dummy;

    // skip tags
    for (std::size_t j = 2; j < n_tags; j++)
        in >> dummy;

    switch (type)
    {
    case 1: {
        readNodeIDs(in, 2, node_ids, id_map);
        // edge_nodes array will be deleted from Line object
        MeshLib::Node** edge_nodes = new MeshLib::Node*[2];
        edge_nodes[0] = nodes[node_ids[0]];
        edge_nodes[1] = nodes[node_ids[1]];
        return std::make_pair(new MeshLib::Line(edge_nodes), mat_id);
    }
    case 2: {
        readNodeIDs(in, 3, node_ids, id_map);
        MeshLib::Node** tri_nodes = new MeshLib::Node*[3];
        tri_nodes[0] = nodes[node_ids[2]];
        tri_nodes[1] = nodes[node_ids[1]];
        tri_nodes[2] = nodes[node_ids[0]];
        return std::make_pair(new MeshLib::Tri(tri_nodes), mat_id);
    }
    case 3: {
        readNodeIDs(in, 4, node_ids, id_map);
        MeshLib::Node** quad_nodes = new MeshLib::Node*[4];
        for (unsigned k(0); k < 4; k++)
            quad_nodes[k] = nodes[node_ids[k]];
        return std::make_pair(new MeshLib::Quad(quad_nodes), mat_id);
    }
    case 4: {
        readNodeIDs(in, 4, node_ids, id_map);
        MeshLib::Node** tet_nodes = new MeshLib::Node*[5];
        for (unsigned k(0); k < 4; k++)
            tet_nodes[k] = nodes[node_ids[k]];
        return std::make_pair(new MeshLib::Tet(tet_nodes), mat_id);
    }
    case 5: {
        readNodeIDs(in, 8, node_ids, id_map);
        MeshLib::Node** hex_nodes = new MeshLib::Node*[8];
        for (unsigned k(0); k < 8; k++)
            hex_nodes[k] = nodes[node_ids[k]];
        return std::make_pair(new MeshLib::Hex(hex_nodes), mat_id);
    }
    case 6: {
        readNodeIDs(in, 6, node_ids, id_map);
        MeshLib::Node** prism_nodes = new MeshLib::Node*[6];
        for (unsigned k(0); k < 6; k++)
            prism_nodes[k] = nodes[node_ids[k]];
        return std::make_pair(new MeshLib::Prism(prism_nodes), mat_id);
    }
    case 7: {
        readNodeIDs(in, 5, node_ids, id_map);
        MeshLib::Node** pyramid_nodes = new MeshLib::Node*[5];
        for (unsigned k(0); k < 5; k++)
            pyramid_nodes[k] = nodes[node_ids[k]];
        return std::make_pair(new MeshLib::Pyramid(pyramid_nodes), mat_id);
    }
    case 15:
        in >> dummy; // skip rest of line
        break;
    default:
        WARN("GMSHInterface::readGMSHMesh(): Unknown element type %d.", type);
        break;
    }
    return std::make_pair(nullptr, -1);
}


bool GMSHInterface::write()
{
    _out << "// GMSH input file created by OpenGeoSys " << BaseLib::BuildInfo::git_describe;
#ifdef BUILD_TIMESTAMP
    _out << " built on " << BaseLib::BuildInfo::build_timestamp;
#endif
    _out << "\n\n";

    writeGMSHInputFile(_out);
    return true;
}

void GMSHInterface::writeGMSHInputFile(std::ostream& out)
{
    DBUG("GMSHInterface::writeGMSHInputFile(): get data from GEOObjects.");

    if (_selected_geometries.empty())
        return;

    bool remove_geometry(false);
    // *** get and merge data from _geo_objs
    if (_selected_geometries.size() > 1) {
        _gmsh_geo_name = "GMSHGeometry";
        remove_geometry = true;
        _geo_objs.mergeGeometries(_selected_geometries, _gmsh_geo_name);
    } else {
        _gmsh_geo_name = _selected_geometries[0];
        remove_geometry = false;
    }
    std::vector<GeoLib::Point*> * merged_pnts(const_cast<std::vector<GeoLib::Point*> *>(_geo_objs.getPointVec(_gmsh_geo_name)));
    if (! merged_pnts) {
        ERR("GMSHInterface::writeGMSHInputFile(): Did not found any points.");
        return;
    }

    // Rotate points to the x-y-plane.
    _inverse_rot_mat = GeoLib::rotatePointsToXY(*merged_pnts);
    // Compute inverse rotation matrix to reverse the rotation later on.
    _inverse_rot_mat.transposeInPlace();

    std::vector<GeoLib::Polyline*> const* merged_plys(_geo_objs.getPolylineVec(_gmsh_geo_name));
    DBUG("GMSHInterface::writeGMSHInputFile(): \t ok.");

    // *** compute topological hierarchy of polygons
    if (merged_plys) {
        for (std::vector<GeoLib::Polyline*>::const_iterator it(merged_plys->begin());
            it!=merged_plys->end(); ++it) {
            if ((*it)->isClosed()) {
                _polygon_tree_list.push_back(new GMSH::GMSHPolygonTree(new GeoLib::Polygon(*(*it), true), NULL, _geo_objs, _gmsh_geo_name, _mesh_density_strategy));
            }
        }
        DBUG("GMSHInterface::writeGMSHInputFile(): Compute topological hierarchy - detected %d polygons.", _polygon_tree_list.size());
        GeoLib::createPolygonTrees<GMSH::GMSHPolygonTree>(_polygon_tree_list);
        DBUG("GMSHInterface::writeGMSHInputFile(): Compute topological hierarchy - calculated %d polygon trees.", _polygon_tree_list.size());
    } else {
        return;
    }

    // *** insert stations and polylines (except polygons) in the appropriate object of
    //     class GMSHPolygonTree
    // *** insert stations
    auto gmsh_stations = std::unique_ptr<std::vector<GeoLib::Point*>>(
        new std::vector<GeoLib::Point*>);
    for (auto const& geometry_name : _selected_geometries) {
        auto const* stations(_geo_objs.getStationVec(geometry_name));
        if (stations) {
            for (auto * station : *stations) {
                bool found(false);
                for (auto it(_polygon_tree_list.begin());
                    it != _polygon_tree_list.end() && !found; ++it) {
                    gmsh_stations->emplace_back(new GeoLib::Station(
                        *static_cast<GeoLib::Station*>(station)));
                    if ((*it)->insertStation(gmsh_stations->back())) {
                        found = true;
                    }
                }
            }
        }
    }

    std::string gmsh_stations_name(_gmsh_geo_name+"-Stations");
    if (! gmsh_stations->empty()) {
        _geo_objs.addStationVec(std::move(gmsh_stations), gmsh_stations_name);
    }

    // *** insert polylines
    const std::size_t n_plys(merged_plys->size());
    for (std::size_t k(0); k<n_plys; k++) {
        if (! (*merged_plys)[k]->isClosed()) {
            for (std::list<GMSH::GMSHPolygonTree*>::iterator it(_polygon_tree_list.begin());
                it != _polygon_tree_list.end(); ++it) {
                (*it)->insertPolyline(new GeoLib::PolylineWithSegmentMarker(*(*merged_plys)[k]));
            }
        }
    }

    // *** init mesh density strategies
    for (std::list<GMSH::GMSHPolygonTree*>::iterator it(_polygon_tree_list.begin());
        it != _polygon_tree_list.end(); ++it) {
        (*it)->initMeshDensityStrategy();
    }

    // *** create GMSH data structures
    const std::size_t n_merged_pnts(merged_pnts->size());
    _gmsh_pnts.resize(n_merged_pnts);
    for (std::size_t k(0); k<n_merged_pnts; k++) {
        _gmsh_pnts[k] = NULL;
    }
    for (std::list<GMSH::GMSHPolygonTree*>::iterator it(_polygon_tree_list.begin());
        it != _polygon_tree_list.end(); ++it) {
        (*it)->createGMSHPoints(_gmsh_pnts);
    }

    // *** finally write data :-)
    writePoints(out);
    std::size_t pnt_id_offset(_gmsh_pnts.size());
    for (std::list<GMSH::GMSHPolygonTree*>::iterator it(_polygon_tree_list.begin());
        it != _polygon_tree_list.end(); ++it) {
        (*it)->writeLineLoop(_n_lines, _n_plane_sfc, out);
        (*it)->writeSubPolygonsAsLineConstraints(_n_lines, _n_plane_sfc-1, out);
        (*it)->writeLineConstraints(_n_lines, _n_plane_sfc-1, out);
        (*it)->writeStations(pnt_id_offset, _n_plane_sfc-1, out);
        (*it)->writeAdditionalPointData(pnt_id_offset, _n_plane_sfc-1, out);
    }

    if (remove_geometry) {
        _geo_objs.removeSurfaceVec(_gmsh_geo_name);
        _geo_objs.removePolylineVec(_gmsh_geo_name);
        _geo_objs.removePointVec(_gmsh_geo_name);
        _geo_objs.removeStationVec(gmsh_stations_name);
    }
}

void GMSHInterface::writePoints(std::ostream& out) const
{
    for (auto & gmsh_pnt : _gmsh_pnts) {
        // reverse rotation
        if (gmsh_pnt) {
            double* tmp = _inverse_rot_mat * gmsh_pnt->getCoords();
            (*gmsh_pnt)[0] = tmp[0];
            (*gmsh_pnt)[1] = tmp[1];
            (*gmsh_pnt)[2] = tmp[2];
            delete [] tmp;
            out << *gmsh_pnt << "\n";
        }
    }
}

} // end namespace FileIO
