/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef GAUSSLEGENDREPYRAMID_H_
#define GAUSSLEGENDREPYRAMID_H_

#include <array>

namespace MathLib
{

/// Gauss-Legendre quadrature on pyramid
///
/// \tparam ORDER   integration order.
template <unsigned ORDER>
struct GaussLegendrePyramid {
    static const unsigned Order = ORDER;
    static const unsigned NPoints = ORDER;
    static const std::array<std::array<double, 3>, NPoints> X;
    static const double W[NPoints];
};

template <>
struct GaussLegendrePyramid<2> {
    static const unsigned Order = 2;
    static const unsigned NPoints = 5;
    static const std::array<std::array<double, 3>, NPoints> X;
    static const double W[NPoints];
};

template <>
struct GaussLegendrePyramid<3> {
    static const unsigned Order = 3;
    static const unsigned NPoints = 13;
    static const std::array<std::array<double, 3>, NPoints> X;
    static const double W[NPoints];
};

}

#endif //GAUSSLEGENDREPYRAMID_H_
