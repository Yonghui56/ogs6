/**
 * \file
 * \author Karsten Rink
 * \date   2012-01-04
 * \brief  Implementation of the DirectConditionGenerator class.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include <fstream>
#include <memory>

// ThirdParty/logog
#include "logog/include/logog.hpp"

#include "DirectConditionGenerator.h"

#include "GeoLib/IO/AsciiRasterInterface.h"

#include "Raster.h"
#include "MeshSurfaceExtraction.h"
#include "Mesh.h"
#include "MeshLib/Node.h"

#include <cmath>
#include <limits>

const std::vector< std::pair<std::size_t,double> >& DirectConditionGenerator::directToSurfaceNodes(const MeshLib::Mesh &mesh, const std::string &filename)
{
	if (_direct_values.empty())
	{
		GeoLib::Raster* raster (GeoLib::IO::AsciiRasterInterface::readRaster(filename));
		if (! raster) {
			ERR("Error in DirectConditionGenerator::directToSurfaceNodes() - could not load raster file.");
			return _direct_values;
		}

		const MathLib::Vector3 dir(0,0,-1);
		const std::vector<GeoLib::Point*> surface_nodes(MeshLib::MeshSurfaceExtraction::getSurfaceNodes(mesh, dir, 90) );
		const std::size_t nNodes(surface_nodes.size());
		const double no_data (raster->getHeader().no_data);
		_direct_values.reserve(nNodes);
		for (std::size_t i=0; i<nNodes; i++)
		{
			double val (raster->getValueAtPoint(*surface_nodes[i]));
			val = (val == no_data) ? 0 : val;
			_direct_values.push_back (std::pair<std::size_t, double>(surface_nodes[i]->getID(), val));
		}
		delete raster;
	}
	else
		ERR("Error in DirectConditionGenerator::directToSurfaceNodes() - Data vector contains outdated values.");

	return _direct_values;
}


const std::vector< std::pair<std::size_t,double> >& DirectConditionGenerator::directWithSurfaceIntegration(MeshLib::Mesh &mesh, const std::string &filename, double scaling)
{
	if (!_direct_values.empty()) {
		ERR(
		    "Error in DirectConditionGenerator::directWithSurfaceIntegration()"
		    "- Data vector contains outdated values...");
		return _direct_values;
	}

	std::unique_ptr<GeoLib::Raster> raster(
	    GeoLib::IO::AsciiRasterInterface::readRaster(filename));
	if (!raster) {
		ERR(
		    "Error in DirectConditionGenerator::directWithSurfaceIntegration()"
		    "- could not load raster file.");
		return _direct_values;
	}

	MathLib::Vector3 const dir(0.0, 0.0, -1.0);
	double const angle(90);
	std::string const prop_name("OriginalSubsurfaceNodeIDs");
	std::unique_ptr<MeshLib::Mesh> surface_mesh(
	    MeshLib::MeshSurfaceExtraction::getMeshSurface(
	        mesh, dir, angle, prop_name));

	std::vector<double> node_area_vec =
		MeshLib::MeshSurfaceExtraction::getSurfaceAreaForNodes(*surface_mesh);
	const std::vector<MeshLib::Node*> &surface_nodes(surface_mesh->getNodes());
	const std::size_t nNodes(surface_mesh->getNNodes());
	const double no_data(raster->getHeader().no_data);

	boost::optional<MeshLib::PropertyVector<int> const&> opt_node_id_pv(
	    surface_mesh->getProperties().getPropertyVector<int>(prop_name));
	if (!opt_node_id_pv) {
		ERR(
		    "Need subsurface node ids, but the property \"%s\" is not "
		    "available.",
		    prop_name.c_str());
		return _direct_values;
	}

	MeshLib::PropertyVector<int> const& node_id_pv(*opt_node_id_pv);
	_direct_values.reserve(nNodes);
	for (std::size_t i=0; i<nNodes; ++i)
	{
		double val(raster->getValueAtPoint(*surface_nodes[i]));
		val = (val == no_data) ? 0 : ((val*node_area_vec[i])/scaling);
		_direct_values.push_back(std::pair<std::size_t, double>(node_id_pv[i], val));
	}

	return _direct_values;
}


int DirectConditionGenerator::writeToFile(const std::string &name) const
{
	std::ofstream out( name.c_str(), std::ios::out );

	if (out)
	{
		for (std::vector< std::pair<std::size_t,double> >::const_iterator it = _direct_values.begin(); it != _direct_values.end(); ++it)
			out << it->first << "\t" << it->second << "\n";

		out.close();
	}
	return 0;
}

