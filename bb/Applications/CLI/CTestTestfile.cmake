# CMake generated Testfile for 
# Source directory: D:/ogs/Applications/CLI
# Build directory: D:/ogs/bb/Applications/CLI
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(ogs_no_args "D:/ogs/bb/bin/RelWithDebInfo/ogs.exe")
  set_tests_properties(ogs_no_args PROPERTIES  WILL_FAIL "TRUE")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(ogs_no_args "D:/ogs/bb/bin/Release/ogs.exe")
  set_tests_properties(ogs_no_args PROPERTIES  WILL_FAIL "TRUE")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(ogs_no_args "D:/ogs/bb/bin/Debug/ogs.exe")
  set_tests_properties(ogs_no_args PROPERTIES  WILL_FAIL "TRUE")
else()
  add_test(ogs_no_args NOT_AVAILABLE)
endif()
