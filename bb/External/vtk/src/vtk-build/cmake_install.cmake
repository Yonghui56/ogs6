# Install script for directory: D:/ogs/bb/External/vtk/src/vtk

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3" TYPE FILE FILES
    "D:/ogs/bb/External/vtk/src/vtk-build/CMakeFiles/VTKConfig.cmake"
    "D:/ogs/bb/External/vtk/src/vtk-build/VTKConfigVersion.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/exportheader.cmake.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/GenerateExportHeader.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/pythonmodules.h.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/UseVTK.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/FindTCL.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/TopologicalSort.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkTclTkMacros.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtk-forward.c.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkGroups.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkForwardingExecutable.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkJavaWrapping.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkMakeInstantiator.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkMakeInstantiator.cxx.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkMakeInstantiator.h.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkModuleAPI.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkModuleHeaders.cmake.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkModuleInfo.cmake.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkModuleMacros.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkModuleMacrosPython.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkMPI.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkExternalModuleMacros.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkObjectFactory.cxx.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkObjectFactory.h.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkPythonPackages.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkPythonWrapping.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkTclWrapping.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkThirdParty.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapHierarchy.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapJava.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapperInit.data.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapping.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapPython.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapPythonSIP.cmake"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapPython.sip.in"
    "D:/ogs/bb/External/vtk/src/vtk/CMake/vtkWrapTcl.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/VTKTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/VTKTargets.cmake"
         "D:/ogs/bb/External/vtk/src/vtk-build/CMakeFiles/Export/lib/cmake/vtk-6.3/VTKTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/VTKTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3/VTKTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/CMakeFiles/Export/lib/cmake/vtk-6.3/VTKTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/CMakeFiles/Export/lib/cmake/vtk-6.3/VTKTargets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/CMakeFiles/Export/lib/cmake/vtk-6.3/VTKTargets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/CMakeFiles/Export/lib/cmake/vtk-6.3/VTKTargets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/vtk-6.3" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/CMakeFiles/Export/lib/cmake/vtk-6.3/VTKTargets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/ogs/bb/External/vtk/src/vtk-build/Remote/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Common/Core/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Common/Math/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Common/Misc/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Common/System/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Common/Transforms/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Common/DataModel/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/Common/ExecutionModel/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/ThirdParty/zlib/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/IO/Core/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/IO/Geometry/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/ThirdParty/expat/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/IO/XMLParser/cmake_install.cmake")
  include("D:/ogs/bb/External/vtk/src/vtk-build/IO/XML/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/ogs/bb/External/vtk/src/vtk-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
