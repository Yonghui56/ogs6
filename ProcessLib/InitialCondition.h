/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef PROCESS_LIB_INITIAL_CONDITION_H_
#define PROCESS_LIB_INITIAL_CONDITION_H_

#include <cassert>
#include "BaseLib/ConfigTree.h"
#include "MeshLib/Node.h"
#include "MeshLib/PropertyVector.h"

namespace BaseLib
{
class ConfigTree;
}

namespace MeshLib
{
template <typename>
class PropertyVector;
class Mesh;
}

namespace ProcessLib
{
/// The InitialCondition is a base class for spatial distributions of values
/// defined on mesh nodes.
class InitialCondition
{
public:
    virtual ~InitialCondition() = default;
    virtual double getValue(MeshLib::Node const&, int const component_id) const = 0;
};

/// Uniform value initial condition
class UniformInitialCondition : public InitialCondition
{
public:
    UniformInitialCondition(double const value) : _value(value)
    {
    }
    /// Returns a value for given node and component.
    /// \todo The component_id is to be implemented.
    virtual double getValue(MeshLib::Node const&,
                            int const /* component_id */) const override
    {
        return _value;
    }

private:
    double _value;
};

/// Construct a UniformInitialCondition from configuration.
/// The initial condition will expect a correct number of components in the
/// configuration, which should be the same as in the corresponding process
/// variable.
std::unique_ptr<InitialCondition> createUniformInitialCondition(
    BaseLib::ConfigTree const& config, int const n_components);

/// Distribution of values given by a mesh property defined on nodes.
class MeshPropertyInitialCondition : public InitialCondition
{
public:
    MeshPropertyInitialCondition(
        MeshLib::PropertyVector<double> const& property)
        : _property(property)
    {
        assert(_property.getMeshItemType() == MeshLib::MeshItemType::Node);
    }

    virtual double getValue(MeshLib::Node const& n,
                            int const component_id) const override
    {
        return _property[n.getID() * _property.getNumberOfComponents() +
                         component_id];
    }

private:
    MeshLib::PropertyVector<double> const& _property;
};

/// Construct a MeshPropertyInitialCondition from configuration.
/// The initial condition will expect a correct number of components in the
/// configuration, which should be the same as in the corresponding process
/// variable.
std::unique_ptr<InitialCondition> createMeshPropertyInitialCondition(
    BaseLib::ConfigTree const& config, MeshLib::Mesh const& mesh,
    int const n_components);

}  // namespace ProcessLib

#endif  // PROCESS_LIB_INITIAL_CONDITION_H_
