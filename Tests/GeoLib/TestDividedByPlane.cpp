/**
 * \file   TestDividedByPlane.cpp
 * \author Karsten Rink
 * \date   2014-02-26
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 *
 */

#include "gtest/gtest.h"

#include "GeoLib/AnalyticalGeometry.h"
#include "GeoLib/Point.h"

TEST(GeoLib, TestDividedByPlane)
{
    // xy plane
    GeoLib::Point a(0,0,0);
    GeoLib::Point b(1,0,0);
    GeoLib::Point c(0,1,0);
    GeoLib::Point d(1,1,0);

    bool result = GeoLib::dividedByPlane(a, d, b, c);
    ASSERT_TRUE(result);

    result = GeoLib::dividedByPlane(b, c, a, d);
    ASSERT_TRUE(result);

    d = GeoLib::Point(0.1, 0.1, 0);
    result = GeoLib::dividedByPlane(b, c, a, d);
    ASSERT_FALSE(result);

    // xz plane
    c = GeoLib::Point(0, 0, 1);
    d = GeoLib::Point(1, 0, 1);
    result = GeoLib::dividedByPlane(a, d, b, c);
    ASSERT_TRUE(result);

    // yz plane
    b = GeoLib::Point(0, 1, 0);
    d = GeoLib::Point(0, 1, 1);
    result = GeoLib::dividedByPlane(a, d, b, c);
    ASSERT_TRUE(result);
}
