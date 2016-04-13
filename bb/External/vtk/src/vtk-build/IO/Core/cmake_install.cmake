# Install script for directory: D:/ogs/bb/External/vtk/src/vtk/IO/Core

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Debug/vtkIOCore-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Release/vtkIOCore-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/MinSizeRel/vtkIOCore-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/RelWithDebInfo/vtkIOCore-6.3.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "RuntimeLibraries")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Debug/vtkIOCore-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Release/vtkIOCore-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/MinSizeRel/vtkIOCore-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/RelWithDebInfo/vtkIOCore-6.3.dll")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/Modules" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/IO/Core/CMakeFiles/vtkIOCore.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3" TYPE FILE FILES
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkAbstractParticleWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkArrayReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkArrayWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkASCIITextCodec.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkBase64InputStream.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkBase64OutputStream.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkBase64Utilities.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkDataCompressor.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkDelimitedTextWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkGlobFileNames.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkInputStream.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkJavaScriptDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkOutputStream.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkSortFileNames.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkTextCodec.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkTextCodecFactory.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkUTF16TextCodec.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkUTF8TextCodec.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkAbstractPolyDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkZLibDataCompressor.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkArrayDataReader.h"
    "D:/ogs/bb/External/vtk/src/vtk/IO/Core/vtkArrayDataWriter.h"
    "D:/ogs/bb/External/vtk/src/vtk-build/IO/Core/vtkIOCoreModule.h"
    )
endif()

