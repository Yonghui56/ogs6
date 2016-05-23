macro(InstallDependencies TARGET INSTALL_COMPONENT)

    if(MSVC)
        set(TARGET_EXE ${EXECUTABLE_OUTPUT_PATH}/Release/${TARGET}.exe)
    else()
        set(TARGET_EXE ${EXECUTABLE_OUTPUT_PATH}/${TARGET})
    endif()

    if(EXISTS ${TARGET_EXE})
        include(GetPrerequisites)
        # arg3: exclude system, arg4: recursive
        get_prerequisites(${TARGET_EXE} TARGET_DEPENDENCIES 1 1 "" "/usr/local/lib")
        message(STATUS "${TARGET_EXE} dependencies:")
        foreach(DEPENDENCY ${TARGET_DEPENDENCIES})
            if(NOT ${DEPENDENCY} MATCHES "@loader_path")
                gp_resolve_item("${TARGET_EXE}" "${DEPENDENCY}" "" "" DEPENDENCY_PATH)
                get_filename_component(RESOLVED_DEPENDENCY_PATH "${DEPENDENCY_PATH}" REALPATH)
                string(TOLOWER ${DEPENDENCY} DEPENDENCY_LOWER)
                set(DEPENDENCY_PATHS ${DEPENDENCY_PATHS} ${RESOLVED_DEPENDENCY_PATH})
                message("    ${RESOLVED_DEPENDENCY_PATH}")
            endif()
        endforeach()
        install(FILES ${DEPENDENCY_PATHS} DESTINATION bin COMPONENT ${INSTALL_COMPONENT})
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ;)
    else()
        # Run CMake after target was built to run GetPrerequisites on executable
        add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND}
            ARGS ${CMAKE_SOURCE_DIR} WORKING_DIRECTORY ${CMAKE_BINARY_DIR} VERBATIM)
    endif()

endmacro()
