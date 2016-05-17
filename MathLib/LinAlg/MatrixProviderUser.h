/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef MATHLIB_MATRIX_PROVIDER_USER_H
#define MATHLIB_MATRIX_PROVIDER_USER_H

#include <cstddef>

#include "SparsityPattern.h"

namespace AssemblerLib { class LocalToGlobalIndexMap; }
namespace MeshLib { class Mesh; }

namespace MathLib
{

struct MatrixSpecifications
{
    MatrixSpecifications(std::size_t const nrows_, std::size_t const ncols_,
                         SparsityPattern const*const sparsity_pattern_,
                         AssemblerLib::LocalToGlobalIndexMap const*const dof_table_,
                         MeshLib::Mesh const*const mesh_)
        : nrows(nrows_), ncols(ncols_), sparsity_pattern(sparsity_pattern_)
        , dof_table(dof_table_), mesh(mesh_)
    {}

    std::size_t const nrows;
    std::size_t const ncols;
    SparsityPattern const*const sparsity_pattern;
    AssemblerLib::LocalToGlobalIndexMap const*const dof_table;
    MeshLib::Mesh const*const mesh;
};

class MatrixSpecificationsProvider
{
public:
    virtual MatrixSpecifications getMatrixSpecifications() const = 0;

    virtual ~MatrixSpecificationsProvider() = default;
};


/*! Manages storage for vectors.
 *
 * This interface provides storage management semantics for vectors, which
 * can be acquired at a certain point in time, be released later on and
 * be acquired again etc.
 *
 * "Released" means that the caller indicates, that he currently does not need
 * that \c Vector instance, i.e, Either it is not needed anymore for the entire
 * program run, or it is temporarily not needed, but might be aquired again
 * later on. Thereby the implementation of this interface can decide, whether
 * the storage for the specific vector can be freed or reused in the meantime.
 *
 * All get-methods of this class come in two variants: One with an \c id argument,
 * and one without. The latter makes it possible to temporarily release a vector
 * during the program run and re-acquire it again. The former variant is intended
 * as a short-cut that simplifies vector acquisition for callers that will use
 * the same vector throughout all of their lifetime without releasing it
 * intermediately.
 *
 * \attention
 * The first time a vector is acquired by a method with \c id argument, the \c id
 * has to be initialized with zero. The respective method then will set the \c id
 * to the specific \c id of the returned vector.
 */
template<typename Vector>
class VectorProvider
{
public:
    //! Get an uninitialized vector.
    virtual Vector& getVector() = 0;

    //! Get an uninitialized vector with the given \c id.
    virtual Vector& getVector(std::size_t& id) = 0;

    //! Get a copy of \c x.
    virtual Vector& getVector(Vector const& x) = 0;

    //! Get a copy of \c x in the storage of the vector with the given \c id.
    virtual Vector& getVector(Vector const& x, std::size_t& id) = 0;

    //! Get a vector according to the given specifications.
    virtual Vector& getVector(MatrixSpecifications const& ms) = 0;

    //! Get a vector according to the given specifications in the storage
    //! of the vector with the given \c id.
    virtual Vector& getVector(MatrixSpecifications const& ms, std::size_t& id) = 0;

    //! Release the given vector.
    //!
    //! \pre \c x must have been acquired before, i.e., you must not call this
    //! method twice in a row in the same \c x!
    virtual void releaseVector(Vector const& x) = 0;

    virtual ~VectorProvider() = default;
};

/*! Manages storage for matrices.
 *
 * This the matrix-analog of VectorProvider. The same notes apply to this class.
 */
template<typename Matrix>
class MatrixProvider
{
public:
    //! Get an uninitialized matrix.
    virtual Matrix& getMatrix() = 0;

    //! Get an uninitialized matrix with the given \c id.
    virtual Matrix& getMatrix(std::size_t& id) = 0;

    //! Get a copy of \c A.
    virtual Matrix& getMatrix(Matrix const& A) = 0;

    //! Get a copy of \c A in the storage of the matrix with the given \c id.
    virtual Matrix& getMatrix(Matrix const& A, std::size_t& id) = 0;

    //! Get a matrix according to the given specifications.
    virtual Matrix& getMatrix(MatrixSpecifications const& ms) = 0;

    //! Get a matrix according to the given specifications in the storage
    //! of the matrix with the given \c id.
    virtual Matrix& getMatrix(MatrixSpecifications const& ms, std::size_t& id) = 0;

    //! Release the given matrix.
    //!
    //! \pre \c A must have been acquired before, i.e., you must not call this
    //! method twice in a row in the same \c A!
    virtual void releaseMatrix(Matrix const& A) = 0;

    virtual ~MatrixProvider() = default;
};

} // namespace MathLib

#endif // MATHLIB_MATRIX_PROVIDER_USER_H
