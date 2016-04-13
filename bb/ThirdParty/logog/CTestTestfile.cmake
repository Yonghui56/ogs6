# CMake generated Testfile for 
# Source directory: D:/ogs/ThirdParty/logog
# Build directory: D:/ogs/bb/ThirdParty/logog
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test-harness "D:/ogs/bb/bin/RelWithDebInfo/test-logog.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test-harness "D:/ogs/bb/bin/Release/test-logog.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test-harness "D:/ogs/bb/bin/Debug/test-logog.exe")
else()
  add_test(test-harness NOT_AVAILABLE)
endif()
