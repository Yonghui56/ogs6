 /**
 * \file
 * \author Karsten Rink
 * \date   2012-09-25
 * \brief  Definition of the GeoMapper class.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef GEOMAPPER_H
#define GEOMAPPER_H

#include <cstddef>
#include <vector>

#include "GeoLib/Point.h"
#include "GeoLib/Grid.h"

#include "MathLib/Point3d.h"

namespace MeshLib {
    class Mesh;
    class Node;
}

namespace GeoLib {
    class Raster;
}

namespace MeshGeoToolsLib {

/**
 * \brief A set of tools for mapping the elevation of geometric objects
 */
class GeoMapper
{
public:
    GeoMapper(GeoLib::GEOObjects &geo_objects, const std::string &geo_name);
    ~GeoMapper();

    /// Maps geometry based on a raster file
    void mapOnDEM(const std::string &file_name);

    /// Maps geometry based on a mesh file
    void mapOnMesh(const std::string &file_name);

    /**
     * Maps the geometry based on the given mesh file. The elevation value of all geometric
     * points are modified such that they are located on the mesh surface.
     */
    void mapOnMesh(const MeshLib::Mesh* mesh);

    /// Maps geometry to a constant elevation value
    void mapToConstantValue(double value);

    /**
     * Maps the geometry based on the given mesh file. A new geometry is created where all
     * geometric points are assigned an elevation value on the mesh surface. Additional points are
     * inserted whenever a polyline from the original geometry intersects a mesh node or the edge
     * of a mesh element.
     * \param mesh          Mesh the geometry is mapped on
     * \param new_geo_name  Name of the newly created geometry
     * \result              A new geometry with the given name is inserted into _geo_objects
     */
    void advancedMapOnMesh(const MeshLib::Mesh* mesh, const std::string &new_geo_name);

private:
    /// Mapping stations, boreholes on a raster or mesh.
    void mapStationData(std::vector<GeoLib::Point*> const& points);

    /// Mapping points on a raster.
    void mapPointDataToDEM(std::vector<GeoLib::Point*> const& points);

    /// Mapping points on mesh.
    void mapPointDataToMeshSurface(std::vector<GeoLib::Point*> const& points);

    /// Returns the elevation at Point (x,y) based on a mesh. This uses collision detection for triangles and nearest neighbor for quads.
    /// NOTE: This medhod only returns correct values if the node numbering of the elements is correct!
    double getMeshElevation(double x, double y, double min_val, double max_val) const;

    /// Returns the elevation at Point (x,y) based on a raster
    float getDemElevation(GeoLib::Point const& pnt) const;

    /// Calculates the intersection of two lines embedded in the xy-plane
    GeoLib::Point* calcIntersection(MathLib::Point3d const*const p1, MathLib::Point3d const*const p2, GeoLib::Point const*const q1, GeoLib::Point const*const q2) const;

    /// Returns the position of a point within a line-segment
    unsigned getPointPosInLine(GeoLib::Polyline const*const line, unsigned start, unsigned end, GeoLib::Point const*const point, double eps) const;

    /// Returns the maximum segment length in a polyline vector
    double getMaxSegmentLength(const std::vector<GeoLib::Polyline*> &lines) const;

    /// Returns if a point p is within a bounding box defined by a and b
    bool isPntInBoundingBox(double ax, double ay, double bx, double by, double px, double py) const;

    GeoLib::GEOObjects& _geo_objects;
    std::string& _geo_name;

    /// only necessary for mapping on mesh
    MeshLib::Mesh* _surface_mesh;
    GeoLib::Grid<MeshLib::Node>* _grid;

    /// only necessary for mapping on DEM
    GeoLib::Raster *_raster;
};

} // end namespace MeshGeoToolsLib

#endif //GEOMAPPER_H
