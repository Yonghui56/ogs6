/**
 * \file
 * \author Thomas Fischer
 * \date   2012-03-21
 * \brief  Implementation of the GMSHPoint class.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include <cmath>
#include <limits>

#include "GmshIO/GMSHPoint.h"

namespace FileIO
{
namespace GMSH {

GMSHPoint::GMSHPoint(GeoLib::Point const& pnt, std::size_t id, double mesh_density) :
    GeoLib::Point(pnt, id), _mesh_density(mesh_density)
{}

void GMSHPoint::write(std::ostream &os) const
{
    os << "Point(" << _id << ") = {" << _x[0] << ", " << _x[1] << ", " << _x[2];
    if (fabs(_mesh_density) > std::numeric_limits<double>::epsilon()) {
        os << ", " << _mesh_density << "};";
    } else {
        os << "};";
    }
}

GMSHPoint::~GMSHPoint()
{}

std::ostream& operator<< (std::ostream &os, GMSHPoint const& p)
{
    p.write (os);
    return os;
}

}
} // end namespace FileIO
