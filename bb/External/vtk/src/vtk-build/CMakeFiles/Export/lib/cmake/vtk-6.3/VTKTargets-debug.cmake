#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vtksys" for configuration "Debug"
set_property(TARGET vtksys APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtksys PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtksys-6.3.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "ws2_32;Psapi"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtksys-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtksys )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtksys "${_IMPORT_PREFIX}/lib/vtksys-6.3.lib" "${_IMPORT_PREFIX}/bin/vtksys-6.3.dll" )

# Import target "vtkCommonCore" for configuration "Debug"
set_property(TARGET vtkCommonCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkCommonCore PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkCommonCore-6.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkCommonCore-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonCore "${_IMPORT_PREFIX}/lib/vtkCommonCore-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkCommonCore-6.3.dll" )

# Import target "vtkCommonMath" for configuration "Debug"
set_property(TARGET vtkCommonMath APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkCommonMath PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkCommonMath-6.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkCommonMath-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonMath )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonMath "${_IMPORT_PREFIX}/lib/vtkCommonMath-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkCommonMath-6.3.dll" )

# Import target "vtkCommonMisc" for configuration "Debug"
set_property(TARGET vtkCommonMisc APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkCommonMisc PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkCommonMisc-6.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkCommonMisc-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonMisc )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonMisc "${_IMPORT_PREFIX}/lib/vtkCommonMisc-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkCommonMisc-6.3.dll" )

# Import target "vtkCommonSystem" for configuration "Debug"
set_property(TARGET vtkCommonSystem APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkCommonSystem PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkCommonSystem-6.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtksys"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkCommonSystem-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonSystem )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonSystem "${_IMPORT_PREFIX}/lib/vtkCommonSystem-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkCommonSystem-6.3.dll" )

# Import target "vtkCommonTransforms" for configuration "Debug"
set_property(TARGET vtkCommonTransforms APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkCommonTransforms PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkCommonTransforms-6.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkCommonTransforms-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonTransforms )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonTransforms "${_IMPORT_PREFIX}/lib/vtkCommonTransforms-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkCommonTransforms-6.3.dll" )

# Import target "vtkCommonDataModel" for configuration "Debug"
set_property(TARGET vtkCommonDataModel APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkCommonDataModel PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkCommonDataModel-6.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtksys"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkCommonDataModel-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonDataModel )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonDataModel "${_IMPORT_PREFIX}/lib/vtkCommonDataModel-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkCommonDataModel-6.3.dll" )

# Import target "vtkCommonExecutionModel" for configuration "Debug"
set_property(TARGET vtkCommonExecutionModel APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkCommonExecutionModel PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkCommonExecutionModel-6.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkCommonExecutionModel-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonExecutionModel )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonExecutionModel "${_IMPORT_PREFIX}/lib/vtkCommonExecutionModel-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkCommonExecutionModel-6.3.dll" )

# Import target "vtkzlib" for configuration "Debug"
set_property(TARGET vtkzlib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkzlib PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkzlib-6.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkzlib-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkzlib )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkzlib "${_IMPORT_PREFIX}/lib/vtkzlib-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkzlib-6.3.dll" )

# Import target "vtkIOCore" for configuration "Debug"
set_property(TARGET vtkIOCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkIOCore PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkIOCore-6.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkzlib;vtksys"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkIOCore-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOCore "${_IMPORT_PREFIX}/lib/vtkIOCore-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkIOCore-6.3.dll" )

# Import target "vtkIOGeometry" for configuration "Debug"
set_property(TARGET vtkIOGeometry APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkIOGeometry PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkIOGeometry-6.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkzlib;vtksys"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkIOGeometry-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOGeometry )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOGeometry "${_IMPORT_PREFIX}/lib/vtkIOGeometry-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkIOGeometry-6.3.dll" )

# Import target "vtkexpat" for configuration "Debug"
set_property(TARGET vtkexpat APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkexpat PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkexpat-6.3.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkexpat-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkexpat )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkexpat "${_IMPORT_PREFIX}/lib/vtkexpat-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkexpat-6.3.dll" )

# Import target "vtkIOXMLParser" for configuration "Debug"
set_property(TARGET vtkIOXMLParser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkIOXMLParser PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkIOXMLParser-6.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtkexpat"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkIOXMLParser-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOXMLParser )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOXMLParser "${_IMPORT_PREFIX}/lib/vtkIOXMLParser-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkIOXMLParser-6.3.dll" )

# Import target "vtkIOXML" for configuration "Debug"
set_property(TARGET vtkIOXML APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(vtkIOXML PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/vtkIOXML-6.3.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "vtksys"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/vtkIOXML-6.3.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOXML )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOXML "${_IMPORT_PREFIX}/lib/vtkIOXML-6.3.lib" "${_IMPORT_PREFIX}/bin/vtkIOXML-6.3.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
