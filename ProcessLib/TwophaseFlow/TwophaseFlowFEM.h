/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef PROCESS_LIB_TWOPHASEFLOW_FEM_H_
#define PROCESS_LIB_TWOPHASEFLOW_FEM_H_

#include <vector>

#include "NumLib/Fem/FiniteElement/TemplateIsoparametric.h"
#include "NumLib/Fem/ShapeMatrixPolicy.h"
#include "NumLib/Function/Interpolation.h"
#include "ProcessLib/LocalAssemblerInterface.h"
#include "ProcessLib/Parameter.h"
#include "ProcessLib/ProcessUtil.h"
#include "TwophaseFlowProcessData.h"
#include "TwophaseFlow_materialproperty.h"

namespace ProcessLib
{

namespace TwophaseFlow
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
                       TwophaseFlowProcessData const& process_data)
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

    void assemble(double const /*t*/, std::vector<double> const& local_x) override
    {
		_localA.setZero();
		_localM.setZero();
		_localRhs.setZero();
		const int n_nodes = _element.getNNodes();
		const int n_dof = local_x.size();
		const int  N_size = n_dof / n_nodes;

		const double rho_w = 1000.;//water density
		const double storage = 0.0;
		const double T = 293.15;
		double rho_G(0.0);
		double Sw(0.0);//water saturation
		double k_rel_G = 0.0;  // relative permeability of gas phase
		double k_rel_L = 0.0;  // relative permeability of liquid phase
		double drhow_dp(0.0);
		double dSwdPc(0.0);
		double drhoGadPG(0.0);
		
		Eigen::MatrixXd mass_mat_coeff = Eigen::MatrixXd::Zero(N_size, N_size);
		Eigen::MatrixXd K_mat_coeff = Eigen::MatrixXd::Zero(N_size, N_size);
		Eigen::VectorXd H_vec_coeff = Eigen::VectorXd::Zero(N_size);
		Eigen::MatrixXd localMass_tmp = Eigen::MatrixXd::Zero(n_nodes, n_nodes);
		Eigen::MatrixXd localDispersion_tmp = Eigen::MatrixXd::Zero(n_nodes, n_nodes);
		Eigen::VectorXd localGravity_tmp = Eigen::VectorXd::Zero(n_nodes);
		MathLib::PiecewiseLinearInterpolation const&  interP_Pc = *_process_data.curves.at("curveA");
		MathLib::PiecewiseLinearInterpolation const&  interP_Kr_L = *_process_data.curves.at("curveB");

		//const bool hasGravityEffect = false;

		IntegrationMethod integration_method(_integration_order);
		unsigned const n_integration_points = integration_method.getNPoints();//retuen gauss point number

		double PC_int_pt = 0.0;//primary variable PC
		double PG_int_pt = 0.0;//primary variable PG

		std::array<double*, 1> const int_pt_array = { &PC_int_pt };

		for (std::size_t ip(0); ip < n_integration_points; ip++) {
			auto const& sm = _shape_matrices[ip];
			auto const& wp = integration_method.getWeightedPoint(ip);

			//NumLib::shapeFunctionInterpolate(local_x, sm.N, int_pt_array);
			NumLib::shapeFunctionInterpolate(local_x, sm.N, PC_int_pt, PG_int_pt);
			

			//Sw = getSwbyPc_van(Pc);
			Sw = interP_Pc.getValue(PC_int_pt);//read from Pc-S curve
										//dSwdPc = getdSwdPc_van(Pc);
			dSwdPc = interP_Pc.getSlope(PC_int_pt);//read from slope of Pc-S curve
											//k_rel = getKrelbySw_van(Sw,0);
			k_rel_G = getKrGbySw_BrookCorey(Sw,0);
			k_rel_L= interP_Kr_L.getValue(Sw);//read from S-Kr curve
			rho_G = getrhoG(PG_int_pt, T);
			drhoGadPG = get_Deriv_rhoG_dP(PG_int_pt, T);
			/*
			*construct the mass matrix
			*/
			mass_mat_coeff(0, 0) = -_process_data.porosity(_element)*rho_G*dSwdPc;
			mass_mat_coeff(0, 1) = _process_data.porosity(_element) * (1 - Sw)*drhoGadPG;
			mass_mat_coeff(1, 0) = _process_data.porosity(_element)*rho_w*dSwdPc;
			mass_mat_coeff(1, 1) = 0.0;

			//std::cout << mass_mat_coeff << std::endl;
			//assembly the mass matrix
			for (int ii = 0; ii < N_size; ii++) {
				for (int jj = 0; jj < N_size; jj++) {
					localMass_tmp.setZero();
					localMass_tmp.noalias()= sm.N *
						mass_mat_coeff(ii, jj) * sm.N.transpose() *
						sm.detJ * wp.getWeight();
					_localM.block(n_nodes*ii, n_nodes*jj, n_nodes, n_nodes).noalias() += localMass_tmp;
				
				}
			}
			/*
			*construct the K matrix
			*/
			K_mat_coeff(0, 0) = 0.0;// _process_data.intrinsic_permeability(_element)*k_rel / _process_data.viscosity(_element);
			K_mat_coeff(0, 1) = rho_G*_process_data.intrinsic_permeability(_element)*k_rel_G / _process_data.viscosity_gas(_element);
			K_mat_coeff(1, 0) = -rho_w*_process_data.intrinsic_permeability(_element)*k_rel_L / _process_data.viscosity_liq(_element);
			K_mat_coeff(1, 1) = rho_w*_process_data.intrinsic_permeability(_element)*k_rel_L / _process_data.viscosity_liq(_element);
			//std::cout << K_mat_coeff << std::endl;
			//assembly the mass matrix
			for (int ii = 0; ii < N_size; ii++) {
				for (int jj = 0; jj < N_size; jj++) {
					localDispersion_tmp.setZero();
					localDispersion_tmp.noalias() = sm.dNdx.transpose() *
						K_mat_coeff(ii, jj) * sm.dNdx *
						sm.detJ * wp.getWeight();
					_localA.block(n_nodes*ii, n_nodes*jj, n_nodes, n_nodes).noalias() += localDispersion_tmp;

				}
			}
			/*
			_localA.noalias() += sm.dNdx.transpose() *
				K_mat_coeff(0, 0) * sm.dNdx *
				sm.detJ * wp.getWeight();
			_localM.noalias() += sm.N *
				mass_mat_coeff(0, 0) * sm.N.transpose() *
				sm.detJ * wp.getWeight();//Eigen::Map<Eigen::VectorXd>
			*/
			H_vec_coeff(0) = K_mat_coeff(0, 1)*rho_G;
			H_vec_coeff(1) = K_mat_coeff(1, 1)*rho_w;

			if (_process_data.has_gravity) {
				for (int idx = 0; idx < N_size; idx++) {
					Eigen::Vector3d const vec_g(0, 0, -9.81);
					// since no primary vairable involved
					// directly assemble to the Right-Hand-Side
					// F += dNp^T * K * gz
					localGravity_tmp.setZero();
					localGravity_tmp.noalias()= sm.dNdx.transpose() * H_vec_coeff(idx) * vec_g * sm.detJ * wp.getWeight();
					_localRhs.block(n_nodes*idx, 0, n_nodes, 1).noalias() += localGravity_tmp;
				}
			} // end of if hasGravityEffect

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
	TwophaseFlowProcessData const& _process_data;

    NodalMatrixType _localA;
	NodalMatrixType _localM;
    NodalVectorType _localRhs;

    unsigned const _integration_order;
};


}   // namespace  TwophaseFlow
}   // namespace ProcessLib

#endif  // PROCESS_LIB_TWOPHASE_FEM_H_
