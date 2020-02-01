# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/../.external")
include(${EXTERNAL_DIR}/scripts/cmake/Common.cmake)

# Add an executable built from a single source file
add_executable_cpp("Examples")
