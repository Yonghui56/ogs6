if(EXISTS "D:/ogs/bb/External/boost/src/boost_1_56_0.tar.bz2")
  file("MD5" "D:/ogs/bb/External/boost/src/boost_1_56_0.tar.bz2" hash_value)
  if("x${hash_value}" STREQUAL "xa744cf167b05d72335f27c88115f211d")
    return()
  endif()
endif()
message(STATUS "downloading...
     src='http://opengeosys.s3.amazonaws.com/ogs6-lib-sources/boost_1_56_0.tar.bz2'
     dst='D:/ogs/bb/External/boost/src/boost_1_56_0.tar.bz2'
     timeout='none'")




file(DOWNLOAD
  "http://opengeosys.s3.amazonaws.com/ogs6-lib-sources/boost_1_56_0.tar.bz2"
  "D:/ogs/bb/External/boost/src/boost_1_56_0.tar.bz2"
  SHOW_PROGRESS
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://opengeosys.s3.amazonaws.com/ogs6-lib-sources/boost_1_56_0.tar.bz2' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
