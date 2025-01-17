# Check if cmake is run from the project root directory
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "CMake should not be run from the project root directory.\n"
        "Please run 'cmake ..' from the project build directory.\n"
        "If you previously attempted to run cmake from the project root directory,"
        "delete the auto-generated CMakeCache.txt file and CMakeFiles directory and try again.")
endif()

cmake_minimum_required(VERSION 3.00)

project(OpenLAMMPSToolbox VERSION 0.1)

set(CMAKE_CXX_COMPILER "g++" CACHE STRING "Choose the C++ compiler: 'g++', 'clang++', or 'icpx' (default is 'g++')")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(SOURCE_FILES
    ${SOURCE_DIR}/calculations/ddc_get_displacement.cpp     # Functions for calculations like selecting subset, finding delta & selecting subset, etc.
    ${SOURCE_DIR}/calculations/ddc_compute_delta_selection.cpp
    ${SOURCE_DIR}/calculations/ddc_compute_selection.cpp
    ${SOURCE_DIR}/calculations/ddc_bulk_selection.cpp
    ${SOURCE_DIR}/calculations/ddc_get_defects.cpp
    ${SOURCE_DIR}/containers/atom_classes.cpp               # Data containers
    ${SOURCE_DIR}/containers/atom_kdtree.cpp
    ${SOURCE_DIR}/containers/dump_data_container.cpp
    ${SOURCE_DIR}/read_write/read_file.cpp                  # Read & write files
    ${SOURCE_DIR}/read_write/write_file.cpp
    ${SOURCE_DIR}/utils/string_to_vec.cpp                   # Utility files
    ${SOURCE_DIR}/utils/ddc_sort.cpp
    ${SOURCE_DIR}/utils/sort_checker.cpp
    ${SOURCE_DIR}/utils/string_to_atom.cpp
    ${SOURCE_DIR}/utils/ddc_reset_id.cpp
    ${SOURCE_DIR}/utils/ddc_subset_creator.cpp
    ${SOURCE_DIR}/utils/vector_utils.cpp
    ${SOURCE_DIR}/utils/atom_creator.cpp
)

set(MAIN_SOURCE_FILE
    ${SOURCE_DIR}/main_postprocessing.cpp
)

add_executable(olt_postprocessing ${MAIN_SOURCE_FILE} ${SOURCE_FILES})

set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

set(TEST_FILES
    ${SOURCE_FILES}
    ${TEST_DIR}/atom_quicksort_test.cpp
    ${TEST_DIR}/atom_methods_test.cpp
    ${TEST_DIR}/sort_check_test.cpp
)

set(MAIN_TEST_FILE
    ${SOURCE_DIR}/main_tests.cpp
)

add_executable(run_tests ${MAIN_TEST_FILE} ${TEST_FILES} )

set(MAIN_DEV_FILE
    ${SOURCE_DIR}/main_dev.cpp
)

add_executable(olt_dev ${MAIN_DEV_FILE} ${SOURCE_FILES})

include_directories(${INCLUDE_DIR})

target_link_libraries(olt_dev readline)
target_link_libraries(olt_postprocessing readline)
