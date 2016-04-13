# Install script for directory: D:/ogs/bb/External/vtk/src/vtk/IO/Geometry

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Debug/vtkIOGeometry-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Release/vtkIOGeometry-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/MinSizeRel/vtkIOGeometry-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/RelWithDebInfo/vtkIOGeometry-6.3.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "RuntimeLibraries")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Debug/vtkIOGeometry-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Release/vtkIOGeometry-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/MinSizeRel/vtkIOGeometry-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/RelWithDebInfo/vtkIOGeometry-6.3.dll")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/Modules" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/IO/Geometry/CMakeFiles/vtkIOGeometry.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3" TYPE FILE FILES
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkAVSucdReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkBYUReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkBYUWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkChacoReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkFacetWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkFLUENTReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkGAMBITReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkGaussianCubeReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkIVWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkMCubesReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkMCubesWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkMFIXReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkMoleculeReaderBase.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkOBJReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkOpenFOAMReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkParticleReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkPDBReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkProStarReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkSTLReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkSTLWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkTecplotReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkUGFacetReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkWindBladeReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Geometry/vtkXYZMolReader.h"
    "D:/ogs/bb/External/vtk/src/vtk-build/IO/Geometry/vtkIOGeometryModule.h"
    )
endif()

