# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
include(${CMAKE_SOURCE_DIR}/../cmake/Common.cmake)

# Add an executable built from a single source file
add_executable_cpp("Examples")
