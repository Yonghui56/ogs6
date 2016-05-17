/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef INTEGRATIONGAUSSPYRAMID_H_
#define INTEGRATIONGAUSSPYRAMID_H_

#include "MathLib/Integration/GaussLegendrePyramid.h"

namespace NumLib
{

/**
 * \brief Gauss quadrature rule for pyramid
 */
class IntegrationGaussPyramid
{
    typedef MathLib::TemplateWeightedPoint<double, double, 3>
        WeightedPoint;
public:
    /**
     * Construct this object with the given integration order
     *
     * @param order     integration order (default 2)
     */
    explicit IntegrationGaussPyramid(std::size_t order = 2)
    : _order(order), _n_sampl_pt(0)
    {
        this->setIntegrationOrder(order);
    }

    /// Change the integration order.
    void setIntegrationOrder(std::size_t order)
    {
        _order = order;
        _n_sampl_pt = getNPoints(_order);
    }

    /// return current integration order.
    std::size_t getIntegrationOrder() const {return _order;}

    /// return the number of sampling points
    std::size_t getNPoints() const {return _n_sampl_pt;}

    /**
     * get coordinates of a integration point
     *
     * @param igp      The integration point index
     * @return a weighted point
     */
    WeightedPoint getWeightedPoint(std::size_t igp)
    {
        return getWeightedPoint(getIntegrationOrder(), igp);
    }

    /**
     * get coordinates of a integration point
     *
     * @param order    the number of integration points
     * @param igp      the sampling point id
     * @return weight
     */
    static WeightedPoint
    getWeightedPoint(std::size_t order, std::size_t igp)
    {
        switch (order)
        {
            case 1: return getWeightedPoint<MathLib::GaussLegendrePyramid<1> >(igp);
            case 2: return getWeightedPoint<MathLib::GaussLegendrePyramid<2> >(igp);
            case 3: return getWeightedPoint<MathLib::GaussLegendrePyramid<3> >(igp);
        }
        return WeightedPoint(std::array<double, 3>(), 0);
    }

    template <typename Method>
    static WeightedPoint
    getWeightedPoint(std::size_t igp)
    {
        return WeightedPoint(Method::X[igp], Method::W[igp]);
    }


    /**
     * get the number of integration points
     *
     * @param order    the number of integration points
     * @return the number of points
     */
    static std::size_t
    getNPoints(std::size_t order)
    {
        switch (order)
        {
            case 1: return MathLib::GaussLegendrePyramid<1>::NPoints;
            case 2: return MathLib::GaussLegendrePyramid<2>::NPoints;
            case 3: return MathLib::GaussLegendrePyramid<3>::NPoints;
        }
        return 0;
    }

private:
    std::size_t _order;
    std::size_t _n_sampl_pt;
};

}

#endif //INTEGRATIONGAUSSPYRAMID_H_
