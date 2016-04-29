/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef PROCESSLIB_RICHARDSFLOW_TWOPHASEFLOWPROCESSDATA_H
#define PROCESSLIB_RICHARDSFLOW_TWOPHASEFLOWPROCESSDATA_H

#include "MathLib/InterpolationAlgorithms/PiecewiseLinearInterpolation.h"

namespace MeshLib
{
    class Element;
}


namespace ProcessLib
{

template <typename ReturnType, typename... Args>
struct Parameter;

namespace TwophaseFlow
{

struct TwophaseFlowProcessData
{
	TwophaseFlowProcessData(
            ProcessLib::Parameter<double, MeshLib::Element const&> const&
			intrinsic_permeability_,
			Parameter<double, MeshLib::Element const&> const&
			porosity_,
			Parameter<double, MeshLib::Element const&> const&
			viscosity_gas_, 
			Parameter<double, MeshLib::Element const&> const&
			viscosity_liq_,
			bool const has_gravity_, 
			std::map<std::string,
				std::unique_ptr<MathLib::PiecewiseLinearInterpolation >> const&
			curves_)
        : intrinsic_permeability(intrinsic_permeability_)
		, porosity(porosity_)
		, viscosity_gas(viscosity_gas_)
		, viscosity_liq(viscosity_liq_)
		, has_gravity(has_gravity_)
		, curves(curves_)

    {}

	TwophaseFlowProcessData(TwophaseFlowProcessData&& other)
        : intrinsic_permeability(other.intrinsic_permeability)
		, porosity(other.porosity)
		, viscosity_gas(other.viscosity_gas)
		, viscosity_liq(other.viscosity_liq)
		, has_gravity(other.has_gravity)
		, curves(other.curves)
    {}

    //! Copies are forbidden.
	TwophaseFlowProcessData(TwophaseFlowProcessData const&) = delete;

    //! Assignments are not needed.
    void operator=(TwophaseFlowProcessData const&) = delete;

    //! Assignments are not needed.
    void operator=(TwophaseFlowProcessData&&) = delete;

    Parameter<double, MeshLib::Element const&> const& intrinsic_permeability;
	Parameter<double, MeshLib::Element const&> const& porosity;
	Parameter<double, MeshLib::Element const&> const& viscosity_gas;
	Parameter<double, MeshLib::Element const&> const& viscosity_liq;
	std::map<std::string,
		std::unique_ptr<MathLib::PiecewiseLinearInterpolation >> const&
		curves;
	bool const has_gravity;
};

} // namespace TwophaseFlow
} // namespace ProcessLib

#endif // PROCESSLIB_TWOPHASEFLOW_TWOPHASEFLOWPROCESSDATA_H
