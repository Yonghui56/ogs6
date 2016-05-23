/**
 * @copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/LICENSE.txt
 */

#include <memory>

#include "gtest/gtest.h"

#include "MeshLib/Mesh.h"
#include "MeshLib/Node.h"
#include "MeshLib/Elements/Element.h"
#include "MeshLib/MeshInformation.h"
#include "MeshLib/MeshSurfaceExtraction.h"
#include "MeshLib/MeshGenerators/MeshGenerator.h"
#include "MeshLib/MeshEditing/AddLayerToMesh.h"
#include "MeshLib/MeshQuality/MeshValidation.h"

namespace AddLayerValidation
{
    // validates mesh. for line meshes, node order tests will fail because vertical elements are
    // created during the extrusion. Therefore node order tests are switched off for line meshes.
    void validate(MeshLib::Mesh const& mesh, bool testNodeOrder)
    {
        int const reduce_tests = (testNodeOrder) ? 0 : 1;

        std::size_t const nErrorFlags (static_cast<std::size_t>(ElementErrorFlag::MaxValue));
        ElementErrorFlag const flags[nErrorFlags] = {ElementErrorFlag::ZeroVolume,
        ElementErrorFlag::NonCoplanar, ElementErrorFlag::NonConvex,  ElementErrorFlag::NodeOrder};
        std::vector<ElementErrorCode> const codes (MeshLib::MeshValidation::testElementGeometry(mesh));
        for (std::size_t i=0; i<codes.size(); ++i)
            for (std::size_t j=0; j<nErrorFlags-reduce_tests; ++j)
                ASSERT_FALSE(codes[i][flags[j]]);
    }

    void testZCoords2D(MeshLib::Mesh const& input, MeshLib::Mesh const& output, double height)
    {
        std::size_t const nNodes (input.getNNodes());
        for (std::size_t i=0; i<nNodes; ++i)
        {
            ASSERT_EQ((*input.getNode(i))[2], (*output.getNode(i))[2]);
            ASSERT_EQ((*input.getNode(i))[2] + height, (*output.getNode(nNodes+i))[2]);
        }
    }

    void testZCoords3D(MeshLib::Mesh const& input, MeshLib::Mesh const& output, double height)
    {
        std::size_t const nNodes (input.getNNodes());
        for (std::size_t i=0; i<nNodes; ++i)
            ASSERT_EQ((*input.getNode(i))[2] + height, (*output.getNode(i))[2]);
    }
};

TEST(MeshLib, AddTopLayerToLineMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateLineMesh(1.0, 5));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", true));

    ASSERT_EQ(2*mesh->getNNodes(), result->getNNodes());
    ASSERT_EQ(2*mesh->getNElements(), result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(5, n_elems[0]); // tests if 5 lines are present
    ASSERT_EQ(5, n_elems[2]); // tests if 5 quads are present

    AddLayerValidation::testZCoords2D(*mesh, *result, height);
    AddLayerValidation::validate(*result, false);
}

TEST(MeshLib, AddBottomLayerToLineMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateLineMesh(1.0, 5));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", false));

    ASSERT_EQ(2*mesh->getNNodes(), result->getNNodes());
    ASSERT_EQ(2*mesh->getNElements(), result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(5, n_elems[0]); // tests if 5 lines are present
    ASSERT_EQ(5, n_elems[2]); // tests if 5 quads are present

    AddLayerValidation::testZCoords2D(*mesh, *result, -1 * height);
    AddLayerValidation::validate(*result, false);
}

TEST(MeshLib, AddTopLayerToTriMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularTriMesh(5, 5));
    std::string const& mat_name ("MaterialIDs");
    boost::optional<MeshLib::PropertyVector<int>&> mats =
        mesh->getProperties().createNewPropertyVector<int>(mat_name, MeshLib::MeshItemType::Cell);
    if (mats)
    {
        mats->resize(mesh->getNElements());
        std::fill_n(mats->begin(), mesh->getNElements(), 0);
    }
    boost::optional<MeshLib::PropertyVector<double>&> test =
        mesh->getProperties().createNewPropertyVector<double>("test", MeshLib::MeshItemType::Cell);
    if (test)
    {
        test->resize(mesh->getNElements());
        std::fill_n(test->begin(), mesh->getNElements(), 0.1);
    }
    ASSERT_EQ(2, mesh->getProperties().getPropertyVectorNames().size());
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", true));

    ASSERT_EQ(2*mesh->getNNodes(), result->getNNodes());
    ASSERT_EQ(2*mesh->getNElements(), result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(mesh->getNElements(), n_elems[1]); // tests if 50 tris are present
    ASSERT_EQ(mesh->getNElements(), n_elems[6]); // tests if 50 prisms are present

    ASSERT_EQ(1, result->getProperties().getPropertyVectorNames().size());
    boost::optional<MeshLib::PropertyVector<int>&> new_mats =
        result->getProperties().getPropertyVector<int>(mat_name);
    ASSERT_EQ(result->getNElements(), new_mats->size());
    ASSERT_EQ(mesh->getNElements(), std::count(new_mats->cbegin(), new_mats->cend(), 0));
    ASSERT_EQ(mesh->getNElements(), std::count(new_mats->cbegin(), new_mats->cend(), 1));
    AddLayerValidation::testZCoords2D(*mesh, *result, height);
    AddLayerValidation::validate(*result, true);
}

TEST(MeshLib, AddBottomLayerToTriMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularTriMesh(5, 5));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", false));

    ASSERT_EQ(2*mesh->getNNodes(), result->getNNodes());
    ASSERT_EQ(2*mesh->getNElements(), result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(50, n_elems[1]); // tests if 50 tris are present
    ASSERT_EQ(50, n_elems[6]); // tests if 50 prisms are present

    AddLayerValidation::testZCoords2D(*mesh, *result, -1 * height);
    AddLayerValidation::validate(*result, true);
}

TEST(MeshLib, AddTopLayerToQuadMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularQuadMesh(5, 5));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", true));

    ASSERT_EQ(2*mesh->getNNodes(), result->getNNodes());
    ASSERT_EQ(2*mesh->getNElements(), result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(25, n_elems[2]); // tests if 25 quads are present
    ASSERT_EQ(25, n_elems[4]); // tests if 25 hexes are present

    AddLayerValidation::testZCoords2D(*mesh, *result, height);
    AddLayerValidation::validate(*result, true);
}

TEST(MeshLib, AddBottomLayerToQuadMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularQuadMesh(5, 5));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", false));

    ASSERT_EQ(2*mesh->getNNodes(), result->getNNodes());
    ASSERT_EQ(2*mesh->getNElements(), result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(25, n_elems[2]); // tests if 25 quads are present
    ASSERT_EQ(25, n_elems[4]); // tests if 25 hexes are present

    AddLayerValidation::testZCoords2D(*mesh, *result, -1 * height);
    AddLayerValidation::validate(*result, true);
}

TEST(MeshLib, AddTopLayerToHexMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularHexMesh(5, 5));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", true));

    ASSERT_EQ(mesh->getNNodes(), result->getNNodes()-36);
    ASSERT_EQ(mesh->getNElements(), result->getNElements()-25);

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(150, n_elems[4]); // tests if 150 hexes are present

    MathLib::Vector3 const dir(0, 0, -1);
    std::unique_ptr<MeshLib::Mesh> const test_input (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*mesh, dir, 90));
    std::unique_ptr<MeshLib::Mesh> const test_output (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*result, dir, 90));
    AddLayerValidation::testZCoords3D(*test_input, *test_output, height);
    AddLayerValidation::validate(*result, true);
}

TEST(MeshLib, AddBottomLayerToHexMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularHexMesh(5, 5));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh, height, "mesh", false));

    ASSERT_EQ(mesh->getNNodes(), result->getNNodes()-36);
    ASSERT_EQ(mesh->getNElements(), result->getNElements()-25);

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(150, n_elems[4]); // tests if 150 hexes are present

    MathLib::Vector3 const dir(0, 0, 1);
    std::unique_ptr<MeshLib::Mesh> const test_input (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*mesh, dir, 90));
    std::unique_ptr<MeshLib::Mesh> const test_output (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*result, dir, 90));
    AddLayerValidation::testZCoords3D(*test_input, *test_output, -1 * height);
    AddLayerValidation::validate(*result, true);
}

TEST(MeshLib, AddTopLayerToPrismMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularTriMesh(5, 5));
    std::unique_ptr<MeshLib::Mesh> const mesh2 (MeshLib::addLayerToMesh(*mesh, 5, "mesh", true));
    double const height (1);
    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh2, height, "mesh", true));

    ASSERT_EQ(mesh2->getNNodes()/2.0 * 3, result->getNNodes());
    ASSERT_EQ(mesh2->getNElements()/2.0 * 3, result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(50, n_elems[1]); // tests if 50 tris are present
    ASSERT_EQ(100, n_elems[6]); // tests if 50 prisms are present

    MathLib::Vector3 const dir(0, 0, -1);
    std::unique_ptr<MeshLib::Mesh> test_input (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*mesh2, dir, 90));
    std::unique_ptr<MeshLib::Mesh> test_output (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*result, dir, 90));
    AddLayerValidation::testZCoords3D(*test_input, *test_output, height);
    AddLayerValidation::validate(*result, true);
}

TEST(MeshLib, AddBottomLayerToPrismMesh)
{
    std::unique_ptr<MeshLib::Mesh> const mesh (MeshLib::MeshGenerator::generateRegularTriMesh(5, 5));
    std::unique_ptr<MeshLib::Mesh> const mesh2 (MeshLib::addLayerToMesh(*mesh, 5, "mesh", true));
    double const height (1);
    std::string const& mat_name ("MaterialIDs");
    boost::optional<MeshLib::PropertyVector<int>&> mats =
        mesh2->getProperties().createNewPropertyVector<int>(mat_name, MeshLib::MeshItemType::Cell);
    if (mats)
    {
        mats->resize(mesh2->getNElements());
        std::fill_n(mats->begin(), mesh2->getNElements(), 0);
    }

    std::unique_ptr<MeshLib::Mesh> const result (MeshLib::addLayerToMesh(*mesh2, height, "mesh", false));
    ASSERT_EQ(mesh2->getNNodes()/2.0 * 3, result->getNNodes());
    ASSERT_EQ(mesh2->getNElements()/2.0 * 3, result->getNElements());

    std::array<unsigned, 7> const n_elems (MeshLib::MeshInformation::getNumberOfElementTypes(*result));
    ASSERT_EQ(mesh->getNElements(), n_elems[1]); // tests if 50 tris are present
    ASSERT_EQ(2 * mesh->getNElements(), n_elems[6]); // tests if 50 prisms are present
    ASSERT_EQ(1, result->getProperties().getPropertyVectorNames().size());
    boost::optional<MeshLib::PropertyVector<int>&> new_mats =
        result->getProperties().getPropertyVector<int>(mat_name);
    ASSERT_EQ(result->getNElements(), new_mats->size());
    ASSERT_EQ(mesh2->getNElements(), std::count(new_mats->cbegin(), new_mats->cend(), 0));
    ASSERT_EQ(mesh->getNElements(), std::count(new_mats->cbegin(), new_mats->cend(), 1));

    MathLib::Vector3 const dir(0, 0, 1);
    std::unique_ptr<MeshLib::Mesh> test_input (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*mesh2, dir, 90));
    std::unique_ptr<MeshLib::Mesh> test_output (
        MeshLib::MeshSurfaceExtraction::getMeshSurface(*result, dir, 90));
    AddLayerValidation::testZCoords3D(*test_input, *test_output, -1 * height);
    AddLayerValidation::validate(*result, true);
}
