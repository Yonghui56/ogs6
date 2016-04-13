# Install script for directory: D:/ogs/bb/External/vtk/src/vtk/IO/XML

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Debug/vtkIOXML-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Release/vtkIOXML-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/MinSizeRel/vtkIOXML-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/RelWithDebInfo/vtkIOXML-6.3.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "RuntimeLibraries")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Debug/vtkIOXML-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Release/vtkIOXML-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/MinSizeRel/vtkIOXML-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/RelWithDebInfo/vtkIOXML-6.3.dll")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/Modules" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/IO/XML/CMakeFiles/vtkIOXML.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3" TYPE FILE FILES
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkRTXMLPolyDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLCompositeDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLCompositeDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLDataSetWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLFileReadTester.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLGenericDataObjectReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLHierarchicalBoxDataFileConverter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLHierarchicalBoxDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLHierarchicalBoxDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLHierarchicalDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLHyperOctreeReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLHyperOctreeWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLImageDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLImageDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLMultiBlockDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLMultiBlockDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLMultiGroupDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPImageDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPolyDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPolyDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPPolyDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPRectilinearGridReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPStructuredDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPStructuredGridReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPUnstructuredDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLPUnstructuredGridReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLRectilinearGridReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLRectilinearGridWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLStructuredDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLStructuredDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLStructuredGridReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLStructuredGridWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLUniformGridAMRReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLUniformGridAMRWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLUnstructuredDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLUnstructuredDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLUnstructuredGridReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLUnstructuredGridWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLWriterC.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/XML/vtkXMLWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk-build/IO/XML/vtkIOXMLModule.h"
    )
endif()

