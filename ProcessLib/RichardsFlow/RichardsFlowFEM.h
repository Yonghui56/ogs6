/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef PROCESS_LIB_RICHARDSFLOW_FEM_H_
#define PROCESS_LIB_RICHARDSFLOW_FEM_H_

#include <vector>

#include "NumLib/Fem/FiniteElement/TemplateIsoparametric.h"
#include "NumLib/Fem/ShapeMatrixPolicy.h"
#include "NumLib/Function/Interpolation.h"
#include "ProcessLib/LocalAssemblerInterface.h"
#include "ProcessLib/Parameter.h"
#include "ProcessLib/ProcessUtil.h"
#include "RichardsFlowProcessData.h"

namespace ProcessLib
{

namespace RichardsFlow
{

template <typename ShapeFunction,
         typename IntegrationMethod,
         typename GlobalMatrix,
         typename GlobalVector,
         unsigned GlobalDim>
class LocalAssemblerData : public ProcessLib::LocalAssemblerInterface<GlobalMatrix, GlobalVector>
{
    using ShapeMatricesType = ShapeMatrixPolicyType<ShapeFunction, GlobalDim>;
    using NodalMatrixType = typename ShapeMatricesType::NodalMatrixType;
    using NodalVectorType = typename ShapeMatricesType::NodalVectorType;
    using ShapeMatrices = typename ShapeMatricesType::ShapeMatrices;

public:
    /// The hydraulic_conductivity factor is directly integrated into the local
    /// element matrix.
    LocalAssemblerData(MeshLib::Element const& element,
                       std::size_t const local_matrix_size,
                       unsigned const integration_order,
                       RichardsFlowProcessData const& process_data)
        : _element(element)
        , _shape_matrices(
              initShapeMatrices<ShapeFunction, ShapeMatricesType, IntegrationMethod, GlobalDim>(
                  element, integration_order))
        , _process_data(process_data)
		, _localM(local_matrix_size, local_matrix_size)
        , _localA(local_matrix_size, local_matrix_size) // TODO narrowing conversion
        , _localRhs(local_matrix_size)
        , _integration_order(integration_order)
    {
		const MeshLib::CoordinateSystem coordsystem(element);
		const MeshLib::ElementCoordinatesMappingLocal ele_local_coord(element, coordsystem);// wp.getCoords());
	}

    void assemble(double const t, std::vector<double> const& local_x) override
    {
		_localA.setZero();
		_localM.setZero();
		_localRhs.setZero();
		const double rho_w = 1000.;//water density
		const double storage = 0.0;
		double Sw(0.0);//water saturation
		double Pc(0.0);//capillary pressure
		double k_rel = 0.0;  // relative permeability
		double drhow_dp(0.0);
		double dSwdPc(0.0);

		Eigen::MatrixXd mass_mat_coeff = Eigen::MatrixXd::Zero(1, 1);
		Eigen::MatrixXd K_mat_coeff = Eigen::MatrixXd::Zero(1, 1);
		
		MathLib::PiecewiseLinearInterpolation const&  interP_Pc = *_process_data.curves.at("curveA");
		MathLib::PiecewiseLinearInterpolation const&  interP_Kr = *_process_data.curves.at("curveB");

		//const bool hasGravityEffect = false;

		IntegrationMethod integration_method(_integration_order);
		unsigned const n_integration_points = integration_method.getNPoints();//retuen gauss point number

		double P_int_pt = 0.0;
		std::array<double*, 1> const int_pt_array = { &P_int_pt };

		for (std::size_t ip(0); ip < n_integration_points; ip++) {
			auto const& sm = _shape_matrices[ip];
			auto const& wp = integration_method.getWeightedPoint(ip);

			//NumLib::shapeFunctionInterpolate(local_x, sm.N, int_pt_array);
			NumLib::shapeFunctionInterpolate(local_x, sm.N, P_int_pt);
			Pc = -P_int_pt;
			//Sw = getSwbyPc_van(Pc);
			Sw = interP_Pc.getValue(Pc);//read from Pc-S curve
										//dSwdPc = getdSwdPc_van(Pc);
			//dSwdPc = interP_Pc.getSlope(Pc);//read from slope of Pc-S curve
											//k_rel = getKrelbySw_van(Sw,0);
			dSwdPc = interP_Pc.PressureSaturationDependency(Pc,true);
			k_rel = interP_Kr.getValue(Sw);//read from S-Kr curve

			mass_mat_coeff(0, 0) = storage * Sw + _process_data.porosity(_element) * Sw * drhow_dp - _process_data.porosity(_element) * dSwdPc;
			K_mat_coeff(0, 0) = _process_data.intrinsic_permeability(_element)*k_rel / _process_data.viscosity(_element);

			_localA.noalias() += sm.dNdx.transpose() *
				K_mat_coeff(0, 0) * sm.dNdx *
				sm.detJ * wp.getWeight();

			//std::cout << t << "  " << _localA << "\n";
			_localM.noalias() += sm.N *
				mass_mat_coeff(0, 0) * sm.N.transpose() *
				sm.detJ * wp.getWeight();//Eigen::Map<Eigen::VectorXd>
			//std::cout << t << "  " << _localM << "\n";
			if (_process_data.has_gravity) {

				//Eigen::Vector3d const vec_g(0, 0, -9.81); //2D X-Z 
				//Eigen::Vector2d const vec_g(0, -9.81);//2D X-Y
				const double vec_g(-9.81);//1D
				// since no primary vairable involved
				// directly assemble to the Right-Hand-Side
				// F += dNp^T * K * gz
				_localRhs.noalias() += sm.dNdx.transpose() * K_mat_coeff(0, 0) * rho_w * vec_g * sm.detJ * wp.getWeight();
			} // end of if hasGravityEffect
			//std::cout << t << "  " << _localRhs << "\n";
		}
    }

    void addToGlobal(AssemblerLib::LocalToGlobalIndexMap::RowColumnIndices const& indices,
        GlobalMatrix& M, GlobalMatrix& K, GlobalVector& b)
        const override
    {
		M.add(indices, _localM);
        K.add(indices, _localA);
        b.add(indices.rows, _localRhs);
    }

private:
    MeshLib::Element const& _element;
    std::vector<ShapeMatrices> _shape_matrices;
    RichardsFlowProcessData const& _process_data;

    NodalMatrixType _localA;
	NodalMatrixType _localM;
    NodalVectorType _localRhs;

    unsigned const _integration_order;
};


}   // namespace  RichardsFlow
}   // namespace ProcessLib

#endif  // PROCESS_LIB_RICHARDSFLOW_FEM_H_
