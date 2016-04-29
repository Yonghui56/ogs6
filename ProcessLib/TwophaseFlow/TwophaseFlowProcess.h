/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef PROCESS_LIB_TWOPHASEFLOWPROCESS_H_
#define PROCESS_LIB_TWOPHASEFLOWPROCESS_H_

#include <cassert>

#include "AssemblerLib/VectorMatrixAssembler.h"
#include "ProcessLib/Process.h"
#include "ProcessLib/ProcessUtil.h"

#include "TwophaseFlowFEM.h"
#include "TwophaseFlowProcessData.h"

namespace MeshLib
{
    class Element;
}

namespace ProcessLib
{

namespace TwophaseFlow
{

template<typename GlobalSetup>
class TwophaseFlowProcess final
        : public Process<GlobalSetup>
{
    using Base = Process<GlobalSetup>;
    using GlobalMatrix = typename GlobalSetup::MatrixType;
    using GlobalVector = typename GlobalSetup::VectorType;

public:
	TwophaseFlowProcess(
        MeshLib::Mesh& mesh,
        typename Base::NonlinearSolver& nonlinear_solver,
        std::unique_ptr<typename Base::TimeDiscretization>&& time_discretization,
        std::vector<std::reference_wrapper<ProcessVariable>>&& process_variables,
		TwophaseFlowProcessData&& process_data)
        : Process<GlobalSetup>(mesh, nonlinear_solver, std::move(time_discretization),
                               std::move(process_variables))
        , _process_data(std::move(process_data))
    {
        if (dynamic_cast<NumLib::ForwardEuler<GlobalVector>*>(
                    &Base::getTimeDiscretization()) != nullptr)
        {
            ERR("TwophaseFlowProcess can not be solved with the ForwardEuler"
                " time discretization scheme. Aborting");
            // Because the M matrix is not assembled. Thus, the linearized system
            // would be singular. The same applies to CrankNicolson with theta = 0.0,
            // but this case is not checked here.
            // Anyway, the TwophaseFlowProcess shall be transferred to a simpler
            // ODESystemTag in the future.
            std::abort();
        }
    }

    //! \name ODESystem interface
    //! @{

    bool isLinear() const override
    {
        return true;
    }

    //! @}

private:
    using LocalAssemblerInterface =
        ProcessLib::LocalAssemblerInterface<GlobalMatrix, GlobalVector>;

    using GlobalAssembler = AssemblerLib::VectorMatrixAssembler<
            GlobalMatrix, GlobalVector, LocalAssemblerInterface,
            NumLib::ODESystemTag::FirstOrderImplicitQuasilinear>;

    void createAssemblers(AssemblerLib::LocalToGlobalIndexMap const& dof_table,
                          MeshLib::Mesh const& mesh,
                          unsigned const integration_order) override
    {
        DBUG("Create global assembler.");
        _global_assembler.reset(new GlobalAssembler(dof_table));

        ProcessLib::createLocalAssemblers<GlobalSetup, LocalAssemblerData>(
                    mesh.getDimension(), mesh.getElements(),
                    dof_table, integration_order, _local_assemblers,
                    _process_data);
    }

    void assembleConcreteProcess(const double t, GlobalVector const& x,
                                 GlobalMatrix& M, GlobalMatrix& K, GlobalVector& b) override
    {
        DBUG("Assemble TwophaseFlowProcess.");

        // Call global assembler for each local assembly item.
        GlobalSetup::executeMemberDereferenced(
            *_global_assembler, &GlobalAssembler::assemble,
            _local_assemblers, t, x, M, K, b);
    }


	TwophaseFlowProcessData _process_data;

    std::unique_ptr<GlobalAssembler> _global_assembler;
    std::vector<std::unique_ptr<LocalAssemblerInterface>> _local_assemblers;
};

template <typename GlobalSetup>
std::unique_ptr<TwophaseFlowProcess<GlobalSetup>>
createTwophaseFlowProcess(
    MeshLib::Mesh& mesh,
    typename Process<GlobalSetup>::NonlinearSolver& nonlinear_solver,
    std::unique_ptr<typename Process<GlobalSetup>::TimeDiscretization>&& time_discretization,
    std::vector<ProcessVariable> const& variables,
    std::vector<std::unique_ptr<ParameterBase>> const& parameters,
    BaseLib::ConfigTree const& config,
	std::map<std::string,
		std::unique_ptr<MathLib::PiecewiseLinearInterpolation >> const&
	curves)
{
    config.checkConfParam("type", "TWOPHASE_FLOW");

    DBUG("Create TwophaseFlowProcess.");

    // Process variable.
    auto process_variables =
        findProcessVariables(variables, config, { "capillary_pressure","gas_pressure" });// attach another primary variable

	//

	// Intrinsic permeability parameter.
	auto& intrinsic_permeability =
		findParameter<double, MeshLib::Element const&>(
			config, "intrinsic_permeability", parameters);

	DBUG("Use \'%s\' as intrinsic_permeability parameter.",
		intrinsic_permeability.name.c_str());

	// Porosity parameter.
	auto& porosity =
		findParameter<double, MeshLib::Element const&>(
			config, "porosity", parameters);

	DBUG("Use \'%s\' as porosity parameter.",
		porosity.name.c_str());

	// Viscosity parameter.
	auto& viscosity_gas =
		findParameter<double, MeshLib::Element const&>(
			config, "viscosity_gas", parameters);

	DBUG("Use \'%s\' as gas phase viscosity parameter.",
		viscosity_gas.name.c_str());

	// Viscosity parameter.
	auto& viscosity_liq =
		findParameter<double, MeshLib::Element const&>(
			config, "viscosity_liq", parameters);

	DBUG("Use \'%s\' as liquid phase viscosity parameter.",
		viscosity_liq.name.c_str());

	//has  gravity
	auto grav = config.getConfParam<bool>("g");

	TwophaseFlowProcessData process_data {
		intrinsic_permeability,
		porosity,
		viscosity_gas,
		viscosity_liq,
		grav,
		curves
    };

    return std::unique_ptr<TwophaseFlowProcess<GlobalSetup>>{
        new TwophaseFlowProcess<GlobalSetup>{
            mesh, nonlinear_solver,std::move(time_discretization),
            std::move(process_variables),
            std::move(process_data)
        }
    };
}

}   // namespace TwophaseFlow
}   // namespace ProcessLib

#endif  // PROCESS_LIB_TWOPHASEFLOWPROCESS_H_
