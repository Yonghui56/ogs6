# Install script for directory: D:/ogs/bb/External/vtk/src/vtk/Common/Transforms

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/VTK")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Debug/vtkCommonTransforms-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Release/vtkCommonTransforms-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/MinSizeRel/vtkCommonTransforms-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/RelWithDebInfo/vtkCommonTransforms-6.3.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "RuntimeLibraries")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Debug/vtkCommonTransforms-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Release/vtkCommonTransforms-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/MinSizeRel/vtkCommonTransforms-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/RelWithDebInfo/vtkCommonTransforms-6.3.dll")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/Modules" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Common/Transforms/CMakeFiles/vtkCommonTransforms.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3" TYPE FILE FILES
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkAbstractTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkCylindricalTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkGeneralTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkHomogeneousTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkIdentityTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkLinearTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkMatrixToHomogeneousTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkMatrixToLinearTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkPerspectiveTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkSphericalTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkThinPlateSplineTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkTransform2D.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkTransformCollection.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkWarpTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk/Common/Transforms/vtkLandmarkTransform.h"
    "D:/ogs/bb/External/vtk/src/vtk-build/Common/Transforms/vtkCommonTransformsModule.h"
    )
endif()

