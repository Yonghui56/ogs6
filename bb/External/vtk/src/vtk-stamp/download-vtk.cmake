message(STATUS "downloading...
     src='http://www.vtk.org/files/release/6.3/VTK-6.3.0.tar.gz'
     dst='D:/ogs/bb/External/vtk/src/VTK-6.3.0.tar.gz'
     timeout='none'")




file(DOWNLOAD
  "http://www.vtk.org/files/release/6.3/VTK-6.3.0.tar.gz"
  "D:/ogs/bb/External/vtk/src/VTK-6.3.0.tar.gz"
  SHOW_PROGRESS
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://www.vtk.org/files/release/6.3/VTK-6.3.0.tar.gz' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
