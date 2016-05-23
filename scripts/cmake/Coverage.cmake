include(CodeCoverage)

set(COVERAGE_EXCLUDES
    '/gpfs0/*'
    '/usr/*'
    '${CMAKE_BINARY_DIR}/*'
    '${CMAKE_SOURCE_DIR}/Tests/*'
    '${CMAKE_SOURCE_DIR}/ThirdParty/*'
)

if(LCOV_PATH AND GENHTML_PATH)
    SETUP_TARGET_FOR_COVERAGE(
        NAME testrunner_coverage
        EXECUTABLE testrunner -j ${PROCESSOR_COUNT}
        DEPENDENCIES testrunner
    )
    SETUP_TARGET_FOR_COVERAGE(
        NAME ctest_coverage
        EXECUTABLE ctest -E LARGE -j ${PROCESSOR_COUNT}
        DEPENDENCIES ogs
    )
else()
    message(STATUS "No lcov coverage report generated because lcov or genhtml was not found.")
endif()

if(PYTHON_EXECUTABLE)
    SETUP_TARGET_FOR_COVERAGE_COBERTURA(
        NAME testrunner_coverage_cobertura
        EXECUTABLE testrunner -j ${PROCESSOR_COUNT}
        DEPENDENCIES testrunner
    )
    SETUP_TARGET_FOR_COVERAGE_COBERTURA(
        NAME ctest_coverage_cobertura
        EXECUTABLE ctest -E LARGE -j ${PROCESSOR_COUNT}
        DEPENDENCIES ogs
    )
else()
    message(STATUS "No cobertura coverage report generated because Python executable was not found.")
endif()
