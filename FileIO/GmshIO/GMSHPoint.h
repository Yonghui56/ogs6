/**
 * \file
 * \author Thomas Fischer
 * \date   2012-03-21
 * \brief  Definition of the GMSHPoint class.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef GMSHPOINT_H_
#define GMSHPOINT_H_

// GeoLib
#include "GeoLib/Point.h"

namespace FileIO
{
namespace GMSH {

class GMSHPoint : public GeoLib::Point {
public:
    GMSHPoint(GeoLib::Point const& pnt, std::size_t id, double mesh_density);
    virtual ~GMSHPoint();
    void write(std::ostream &os) const;
private:
    double _mesh_density;
};

/** overload the output operator for class GMSHPoint */
std::ostream& operator<< (std::ostream &os, GMSHPoint const& p);

}
}

#endif /* GMSHPOINT_H_ */
