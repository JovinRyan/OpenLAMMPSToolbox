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

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(SOURCE_FILES
    ${SOURCE_DIR}/calculations/ddc_get_displacement.cpp     # Functions for calculations like selecting subset, finding delta & selecting subset, etc.
    ${SOURCE_DIR}/calculations/ddc_compute_delta_selection.cpp
    ${SOURCE_DIR}/calculations/ddc_compute_selection.cpp
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
)

set(MAIN_SOURCE_FILE
    ${SOURCE_DIR}/main_postprocessing.cpp
)

add_executable(olt_postprocessing ${MAIN_SOURCE_FILE} ${SOURCE_FILES})

include_directories(${INCLUDE_DIR})
