/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include <cassert>
#include <logog/include/logog.hpp>

#include "BLAS.h"
#include "MatrixVectorTraits.h"
#include "SimpleMatrixVectorProvider.h"

namespace detail
{

template<typename MatVec>
MatVec*
transfer(std::map<std::size_t, MatVec*>& from_unused,
         std::map<MatVec*, std::size_t>& to_used,
         typename std::map<std::size_t, MatVec*>::iterator it)
{
    auto const id = it->first;
    auto& ptr = it->second;

    auto res = to_used.emplace(ptr, id);
    assert(res.second && "Emplacement failed.");
    from_unused.erase(it);
    return res.first->first;
}

template<typename MatVec>
void
transfer(std::map<MatVec*, std::size_t>& from_used,
         std::map<std::size_t, MatVec*>& to_unused,
         typename std::map<MatVec*, std::size_t>::iterator it)
{
    auto& ptr = it->first;
    auto const id = it->second;

    auto res = to_unused.emplace(id, ptr);
    assert(res.second && "Emplacement failed.");
    (void) res; // res unused if NDEBUG
    from_used.erase(it);
}

} // detail


namespace MathLib
{

template<typename Matrix, typename Vector>
template<bool do_search, typename MatVec, typename... Args>
std::pair<MatVec*, bool>
SimpleMatrixVectorProvider<Matrix, Vector>::
get_(std::size_t& id,
     std::map<std::size_t, MatVec*>& unused_map,
     std::map<MatVec*, std::size_t>& used_map,
     Args&&... args)
{
    if (id >= _next_id) {
        ERR("An obviously uninitialized id argument has been passed."
            " This might not be a serious error for the current implementation,"
            " but it might become one in the future."
            " Hence, I will abort now.");
        std::abort();
    }

    if (do_search)
    {
        auto it = unused_map.find(id);
        if (it != unused_map.end()) // unused matrix/vector found
            return { ::detail::transfer(unused_map, used_map, it), false };
    }

    // not searched or not found, so create a new one
    id = _next_id++;
    auto res = used_map.emplace(
        MatrixVectorTraits<MatVec>::newInstance(std::forward<Args>(args)...).release(),
        id);
    assert(res.second && "Emplacement failed.");
    return { res.first->first, true };
}

template<typename Matrix, typename Vector>
template<bool do_search, typename... Args>
std::pair<Matrix*, bool>
SimpleMatrixVectorProvider<Matrix, Vector>::
getMatrix_(std::size_t& id, Args&&... args)
{
    return get_<do_search>(id, _unused_matrices, _used_matrices, std::forward<Args>(args)...);
}


template<typename Matrix, typename Vector>
Matrix&
SimpleMatrixVectorProvider<Matrix, Vector>::
getMatrix()
{
    std::size_t id = 0u;
    return *getMatrix_<false>(id).first;
}

template<typename Matrix, typename Vector>
Matrix&
SimpleMatrixVectorProvider<Matrix, Vector>::
getMatrix(std::size_t& id)
{
    return *getMatrix_<true>(id).first;
}

template<typename Matrix, typename Vector>
Matrix&
SimpleMatrixVectorProvider<Matrix, Vector>::
getMatrix(MatrixSpecifications const& ms)
{
    std::size_t id = 0u;
    return *getMatrix_<false>(id, ms).first;
    // TODO assert that the returned object always is of the right size
}

template<typename Matrix, typename Vector>
Matrix&
SimpleMatrixVectorProvider<Matrix, Vector>::
getMatrix(MatrixSpecifications const& ms, std::size_t& id)
{
    return *getMatrix_<true>(id, ms).first;
    // TODO assert that the returned object always is of the right size
}

template<typename Matrix, typename Vector>
Matrix&
SimpleMatrixVectorProvider<Matrix, Vector>::
getMatrix(Matrix const& A)
{
    std::size_t id = 0u;
    auto const& res = getMatrix_<false>(id, A);
    if (!res.second) // no new object has been created
        BLAS::copy(A, *res.first);
    return *res.first;
}

template<typename Matrix, typename Vector>
Matrix&
SimpleMatrixVectorProvider<Matrix, Vector>::
getMatrix(Matrix const& A, std::size_t& id)
{
    auto const& res = getMatrix_<true>(id, A);
    if (!res.second) // no new object has been created
        BLAS::copy(A, *res.first);
    return *res.first;
}

template<typename Matrix, typename Vector>
void
SimpleMatrixVectorProvider<Matrix, Vector>::
releaseMatrix(Matrix const& A)
{
    auto it = _used_matrices.find(const_cast<Matrix*>(&A));
    if (it == _used_matrices.end()) {
        ERR("The given matrix has not been found. Cannot release it. Aborting.");
        std::abort();
    } else {
        ::detail::transfer(_used_matrices, _unused_matrices, it);
    }
}

template<typename Matrix, typename Vector>
template<bool do_search, typename... Args>
std::pair<Vector*, bool>
SimpleMatrixVectorProvider<Matrix, Vector>::
getVector_(std::size_t& id, Args&&... args)
{
    return get_<do_search>(id, _unused_vectors, _used_vectors, std::forward<Args>(args)...);
}


template<typename Matrix, typename Vector>
Vector&
SimpleMatrixVectorProvider<Matrix, Vector>::
getVector()
{
    std::size_t id = 0u;
    return *getVector_<false>(id).first;
}

template<typename Matrix, typename Vector>
Vector&
SimpleMatrixVectorProvider<Matrix, Vector>::
getVector(std::size_t& id)
{
    return *getVector_<true>(id).first;
}

template<typename Matrix, typename Vector>
Vector&
SimpleMatrixVectorProvider<Matrix, Vector>::
getVector(MatrixSpecifications const& ms)
{
    std::size_t id = 0u;
    return *getVector_<false>(id, ms).first;
    // TODO assert that the returned object always is of the right size
}

template<typename Matrix, typename Vector>
Vector&
SimpleMatrixVectorProvider<Matrix, Vector>::
getVector(MatrixSpecifications const& ms, std::size_t& id)
{
    return *getVector_<true>(id, ms).first;
    // TODO assert that the returned object always is of the right size
}

template<typename Matrix, typename Vector>
Vector&
SimpleMatrixVectorProvider<Matrix, Vector>::
getVector(Vector const& x)
{
    std::size_t id = 0u;
    auto const& res = getVector_<false>(id, x);
    if (!res.second) // no new object has been created
        BLAS::copy(x, *res.first);
    return *res.first;
}

template<typename Matrix, typename Vector>
Vector&
SimpleMatrixVectorProvider<Matrix, Vector>::
getVector(Vector const& x, std::size_t& id)
{
    auto const& res = getVector_<true>(id, x);
    if (!res.second) // no new object has been created
        BLAS::copy(x, *res.first);
    return *res.first;
}

template<typename Matrix, typename Vector>
void
SimpleMatrixVectorProvider<Matrix, Vector>::
releaseVector(Vector const& x)
{
    auto it = _used_vectors.find(const_cast<Vector*>(&x));
    if (it == _used_vectors.end()) {
        ERR("The given vector has not been found. Cannot release it. Aborting.");
        std::abort();
    } else {
        ::detail::transfer(_used_vectors, _unused_vectors, it);
    }
}

template<typename Matrix, typename Vector>
SimpleMatrixVectorProvider<Matrix, Vector>::
~SimpleMatrixVectorProvider()
{
    if ((!_used_matrices.empty()) || (!_used_vectors.empty())) {
        WARN("There are still some matrices and vectors in use."
             " This might be an indicator of a possible waste of memory.");
    }

    for (auto& id_ptr : _unused_matrices)
        delete id_ptr.second;

    for (auto& ptr_id : _used_matrices)
        delete ptr_id.first;

    for (auto& id_ptr : _unused_vectors)
        delete id_ptr.second;

    for (auto& ptr_id : _used_vectors)
        delete ptr_id.first;
}

} // MathLib
