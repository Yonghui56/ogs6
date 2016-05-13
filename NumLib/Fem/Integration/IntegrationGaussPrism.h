/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef INTEGRATIONGAUSSPRISM_H_
#define INTEGRATIONGAUSSPRISM_H_

#include "MathLib/Integration/GaussLegendre.h"
#include "MathLib/Integration/GaussLegendreTri.h"

namespace NumLib
{

/**
 * \brief Gauss quadrature rule for prisms
 */
class IntegrationGaussPrism
{
    typedef MathLib::TemplateWeightedPoint<double, double, 3>
        WeightedPoint;
public:
    /**
     * Construct this object with the given integration order
     *
     * @param order     integration order (default 2)
     */
    explicit IntegrationGaussPrism(std::size_t order = 2)
    : _order(2), _n_sampl_pt(0)
    {
        this->setIntegrationOrder(order);
    }

    /// Change the integration order.
    void setIntegrationOrder(std::size_t /*order*/)
    {
        _order = 2; // fixed
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
     * @param ipg      the sampling point id
     * @return weight
     */
    static WeightedPoint
    getWeightedPoint(std::size_t /*order*/, std::size_t igp)
    {
        const unsigned gp_r = igp % 3;
        const unsigned gp_t = (unsigned)(igp/3);
        std::array<double, 3> rst;
        rst[0] = MathLib::GaussLegendreTri<2>::X[gp_r][0];
        rst[1] = MathLib::GaussLegendreTri<2>::X[gp_r][1];
        rst[2] = MathLib::GaussLegendre<2>::X[gp_t];
        double w = MathLib::GaussLegendreTri<2>::W[gp_r] * 0.5 * MathLib::GaussLegendre<2>::W[gp_t];
        return WeightedPoint(rst, w);
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
        if (order==2) return 6;
        return 0;
    }

private:
    std::size_t _order;
    std::size_t _n_sampl_pt;
};

}

#endif //INTEGRATIONGAUSSPRISM_H_
