# Install script for directory: D:/ogs/bb/External/vtk/src/vtk/Utilities/KWSys/vtksys

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/algorithm")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/deque")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/exception")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/functional")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/iterator")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/list")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/map")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/memory")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/new")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/numeric")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/queue")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/set")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/stack")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/stdexcept")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/string.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/string")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/utility")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/stl" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/stl/vector")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/cstddef")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/ios" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/ios/iostream")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/ios" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/ios/fstream")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/ios" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/ios/sstream")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys/ios" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/ios/iosfwd")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Directory.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/DynamicLoader.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Encoding.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Glob.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/RegularExpression.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/SystemTools.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/CommandLineArguments.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/FStream.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/SystemInformation.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Configure.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/SharedForward.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Process.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Base64.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Encoding.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/FundamentalType.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/MD5.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/System.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/Configure.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/String.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/hashtable.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/hash_fun.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/hash_map.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/hash_set.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vtk-6.3/vtksys" TYPE FILE FILES "D:/ogs/bb/External/vtk/src/vtk-build/Utilities/KWSys/vtksys/auto_ptr.hxx")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Debug/vtksys-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/Release/vtksys-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/MinSizeRel/vtksys-6.3.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/ogs/bb/External/vtk/src/vtk-build/lib/RelWithDebInfo/vtksys-6.3.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "RuntimeLibraries")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Debug/vtksys-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/Release/vtksys-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/MinSizeRel/vtksys-6.3.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/ogs/bb/External/vtk/src/vtk-build/bin/RelWithDebInfo/vtksys-6.3.dll")
  endif()
endif()

