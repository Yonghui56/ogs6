/**
 * \file   BoostXmlGmlInterface.cpp
 * \author Karsten Rink
 * \date   2014-01-31
 * \brief  Implementation of the BoostXmlGmlInterface class.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include <boost/property_tree/xml_parser.hpp>
#include <logog/include/logog.hpp>

#include "BoostXmlGmlInterface.h"

#include "BaseLib/ConfigTreeUtil.h"
#include "BaseLib/uniqueInsert.h"
#include "GeoLib/GEOObjects.h"
#include "GeoLib/Point.h"
#include "GeoLib/PointVec.h"
#include "GeoLib/Polyline.h"
#include "GeoLib/Surface.h"
#include "GeoLib/Triangle.h"

namespace GeoLib
{
namespace IO
{

BoostXmlGmlInterface::BoostXmlGmlInterface(GeoLib::GEOObjects& geo_objs) :
		_geo_objects(geo_objs)
{}

bool BoostXmlGmlInterface::readFile(const std::string &fname)
{
	//! \todo Reading geometries is always strict.
	auto doc = BaseLib::makeConfigTree(fname, true, "OpenGeoSysGLI");

	// ignore attributes related to XML schema
	doc->ignoreConfAttribute("xmlns:xsi");
	doc->ignoreConfAttribute("xsi:noNamespaceSchemaLocation");
	doc->ignoreConfAttribute("xmlns:ogs");

	auto points = std::unique_ptr<std::vector<GeoLib::Point*>>(
	    new std::vector<GeoLib::Point*>);
	auto polylines = std::unique_ptr<std::vector<GeoLib::Polyline*>>(
	    new std::vector<GeoLib::Polyline*>);
	auto surfaces = std::unique_ptr<std::vector<GeoLib::Surface*>>(
	    new std::vector<GeoLib::Surface*>);

	using MapNameId = std::map<std::string, std::size_t>;
	std::unique_ptr<MapNameId> pnt_names{new MapNameId};
	std::unique_ptr<MapNameId> ply_names{new MapNameId};
	std::unique_ptr<MapNameId> sfc_names{new MapNameId};

	auto geo_name = doc->getConfParam<std::string>("name");
	if (geo_name.empty())
	{
		ERR("BoostXmlGmlInterface::readFile(): <name> tag is empty.");
		std::abort();
	}

	for (auto st : doc->getConfSubtreeList("points"))
	{
		readPoints(st, *points, *pnt_names);
		_geo_objects.addPointVec(std::move(points), geo_name, pnt_names.release());
	}

	for (auto st : doc->getConfSubtreeList("polylines"))
	{
		readPolylines(st,
		              *polylines,
		              *_geo_objects.getPointVec(geo_name),
		              _geo_objects.getPointVecObj(geo_name)->getIDMap(),
		              *ply_names);
	}

	for (auto st : doc->getConfSubtreeList("surfaces"))
	{
		readSurfaces(st,
		             *surfaces,
		             *_geo_objects.getPointVec(geo_name),
		             _geo_objects.getPointVecObj(geo_name)->getIDMap(),
		             *sfc_names);
	}

	if (!polylines->empty()) {
		_geo_objects.addPolylineVec(std::move(polylines), geo_name, ply_names.release());
	}

	if (!surfaces->empty()) {
		_geo_objects.addSurfaceVec(std::move(surfaces), geo_name, sfc_names.release());
	}

	return true;
}

void BoostXmlGmlInterface::readPoints(BaseLib::ConfigTree const& pointsRoot,
	                                  std::vector<GeoLib::Point*>& points,
	                                  std::map<std::string, std::size_t>& pnt_names )
{
	for (auto const pt : pointsRoot.getConfParamList("point"))
	{
		auto const p_id = pt.getConfAttribute<std::size_t>("id");
		auto const p_x  = pt.getConfAttribute<double>("x");
		auto const p_y  = pt.getConfAttribute<double>("y");
		auto const p_z  = pt.getConfAttribute<double>("z");

		auto const p_size = points.size();
		BaseLib::insertIfKeyUniqueElseError(_idx_map, p_id, p_size,
		    "The point id is not unique.");
		points.push_back(new GeoLib::Point(p_x, p_y, p_z, p_id));

		if (auto const p_name = pt.getConfAttributeOptional<std::string>("name"))
		{
			if (p_name->empty()) {
				ERR("Empty point name found in geometry file.");
				std::abort();
			}

			BaseLib::insertIfKeyUniqueElseError(pnt_names, *p_name, p_size,
			    "The point name is not unique.");
		}
	}
}

void BoostXmlGmlInterface::readPolylines(
    BaseLib::ConfigTree const& polylinesRoot,
    std::vector<GeoLib::Polyline*>& polylines,
    std::vector<GeoLib::Point*> const& points,
    std::vector<std::size_t> const& pnt_id_map,
    std::map<std::string, std::size_t>& ply_names)
{
	for (auto const pl : polylinesRoot.getConfSubtreeList("polyline"))
	{
		auto const id = pl.getConfAttribute<std::size_t>("id");
		// The id is not used but must be present in the GML file.
		// That's why pl.ignore...() cannot be used.
		(void) id;

		polylines.push_back(new GeoLib::Polyline(points));

		if (auto const p_name = pl.getConfAttributeOptional<std::string>("name"))
		{
			if (p_name->empty()) {
				ERR("Empty polyline name found in geometry file.");
				std::abort();
			}

			BaseLib::insertIfKeyUniqueElseError(ply_names, *p_name, polylines.size()-1,
			    "The polyline name is not unique.");

			for (auto const pt : pl.getConfParamList<std::size_t>("pnt")) {
				polylines.back()->addPoint(pnt_id_map[_idx_map[pt]]);
			}
		}
		else
		{
			// polyline has no name, ignore it.
			pl.ignoreConfParamAll("pnt");
		}
	}
}

void BoostXmlGmlInterface::readSurfaces(
    BaseLib::ConfigTree const&  surfacesRoot,
    std::vector<GeoLib::Surface*>& surfaces,
    std::vector<GeoLib::Point*> const& points,
    const std::vector<std::size_t>& pnt_id_map,
    std::map<std::string, std::size_t>& sfc_names)
{
	for (auto const& sfc : surfacesRoot.getConfSubtreeList("surface"))
	{
		auto const id = sfc.getConfAttribute<std::size_t>("id");
		// The id is not used but must be present in the GML file.
		// That's why sfc.ignore...() cannot be used.
		(void) id;
		surfaces.push_back(new GeoLib::Surface(points));

		if (auto const s_name = sfc.getConfAttributeOptional<std::string>("name"))
		{
			if (s_name->empty()) {
				ERR("Empty surface name found in geometry file.");
				std::abort();
			}

			BaseLib::insertIfKeyUniqueElseError(sfc_names, *s_name, surfaces.size()-1,
			    "The surface name is not unique.");

			for (auto const& element : sfc.getConfParamList("element")) {
				auto const p1_attr = element.getConfAttribute<std::size_t>("p1");
				auto const p2_attr = element.getConfAttribute<std::size_t>("p2");
				auto const p3_attr = element.getConfAttribute<std::size_t>("p3");

				auto const p1 = pnt_id_map[_idx_map[p1_attr]];
				auto const p2 = pnt_id_map[_idx_map[p2_attr]];
				auto const p3 = pnt_id_map[_idx_map[p3_attr]];
				surfaces.back()->addTriangle(p1,p2,p3);
			}
		}
		else
		{
			// surface has no name, ignore it.
			sfc.ignoreConfParamAll("element");
		}
	}
}

bool BoostXmlGmlInterface::write()
{
	if (this->_exportName.empty()) {
		ERR("BoostXmlGmlInterface::write(): No geometry specified.");
		return false;
	}

	GeoLib::PointVec const*const pnt_vec(_geo_objects.getPointVecObj(_exportName));
	if (! pnt_vec) {
		ERR("BoostXmlGmlInterface::write(): No PointVec within the geometry \"%s\".",
			_exportName.c_str());
		return false;
	}

	std::vector<GeoLib::Point*> const*const pnts(pnt_vec->getVector());
	if (! pnts) {
		ERR("BoostXmlGmlInterface::write(): No vector of points within the geometry \"%s\".",
			_exportName.c_str());
		return false;
	}
	if (pnts->empty()) {
		ERR("BoostXmlGmlInterface::write(): No points within the geometry \"%s\".",
			_exportName.c_str());
		return false;
	}

	// create a property tree for writing it to file
	boost::property_tree::ptree pt;

	// put header in property tree
	pt.put("<xmlattr>.xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	pt.put("<xmlattr>.xsi:noNamespaceSchemaLocation",
		"http://www.opengeosys.org/images/xsd/OpenGeoSysGLI.xsd");
	pt.put("<xmlattr>.xmlns:ogs", "http://www.opengeosys.net");
	auto& geometry_set = pt.add("OpenGeoSysGLI", "");

	geometry_set.add("name", _exportName);
	auto& pnts_tag = geometry_set.add("points", "");
	for (std::size_t k(0); k<pnts->size(); k++) {
		auto& pnt_tag = pnts_tag.add("point", "");
		pnt_tag.put("<xmlattr>.id", k);
		pnt_tag.put("<xmlattr>.x", (*((*pnts)[k]))[0]);
		pnt_tag.put("<xmlattr>.y", (*((*pnts)[k]))[1]);
		pnt_tag.put("<xmlattr>.z", (*((*pnts)[k]))[2]);
		std::string const& point_name(pnt_vec->getItemNameByID(k));
		if (!point_name.empty())
			pnt_tag.put("<xmlattr>.name", point_name);
	}

	addPolylinesToPropertyTree(geometry_set);
	addSurfacesToPropertyTree(geometry_set);

	boost::property_tree::xml_writer_settings<std::string> settings('\t', 1);
	write_xml(_out, pt, settings);
	return true;
}

void BoostXmlGmlInterface::addSurfacesToPropertyTree(
	boost::property_tree::ptree & geometry_set)
{
	GeoLib::SurfaceVec const*const sfc_vec(_geo_objects.getSurfaceVecObj(_exportName));
	if (!sfc_vec) {
		INFO("BoostXmlGmlInterface::addSurfacesToPropertyTree(): "
			"No surfaces within the geometry \"%s\".", _exportName.c_str());
		return;
	}

	std::vector<GeoLib::Surface*> const*const surfaces(sfc_vec->getVector());
	if (!surfaces || surfaces->empty())
	{
		INFO(
		    "BoostXmlGmlInterface::addSurfacesToPropertyTree(): "
		    "No surfaces within the geometry \"%s\".",
		    _exportName.c_str());
		return;
	}

	auto& surfaces_tag = geometry_set.add("surfaces", "");
	for (std::size_t i=0; i<surfaces->size(); ++i) {
		GeoLib::Surface const*const surface((*surfaces)[i]);
		std::string sfc_name("");
		sfc_vec->getNameOfElement(surface, sfc_name);
		auto& surface_tag = surfaces_tag.add("surface", "");
		surface_tag.put("<xmlattr>.id", i);
		if (!sfc_name.empty())
			surface_tag.put("<xmlattr>.name", sfc_name);
		for (std::size_t j=0; j<surface->getNTriangles(); ++j) {
			auto& element_tag = surface_tag.add("element", "");
			element_tag.put("<xmlattr>.p1", (*(*surface)[j])[0]);
			element_tag.put("<xmlattr>.p2", (*(*surface)[j])[1]);
			element_tag.put("<xmlattr>.p3", (*(*surface)[j])[2]);
		}
	}
}

void BoostXmlGmlInterface::addPolylinesToPropertyTree(
	boost::property_tree::ptree & geometry_set)
{
	GeoLib::PolylineVec const*const vec(_geo_objects.getPolylineVecObj(_exportName));
	if (!vec) {
		INFO("BoostXmlGmlInterface::addPolylinesToPropertyTree(): "
			"No polylines within the geometry \"%s\".", _exportName.c_str());
		return;
	}

	std::vector<GeoLib::Polyline*> const*const polylines(vec->getVector());
	if (!polylines || polylines->empty())
	{
		INFO(
		    "BoostXmlGmlInterface::addPolylinesToPropertyTree(): "
		    "No polylines within the geometry \"%s\".",
		    _exportName.c_str());
		return;
	}

	auto& polylines_tag = geometry_set.add("polylines", "");
	for (std::size_t i=0; i<polylines->size(); ++i) {
		GeoLib::Polyline const*const polyline((*polylines)[i]);
		std::string ply_name("");
		vec->getNameOfElement(polyline, ply_name);
		auto& polyline_tag = polylines_tag.add("polyline", "");
		polyline_tag.put("<xmlattr>.id", i);
		if (!ply_name.empty())
			polyline_tag.put("<xmlattr>.name", ply_name);
		for (std::size_t j=0; j<polyline->getNumberOfPoints(); ++j) {
			polyline_tag.add("pnt", polyline->getPointID(j));
		}
	}
}

} // end namespace IO
} // end namespace GeoLib
