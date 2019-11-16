# CMakeLists.txt
#
# Top-level file

cmake_minimum_required(VERSION 3.0)

# Source some common files
include(${CMAKE_SOURCE_DIR}/cmake/Common.cmake)

# Set the project name
project(CppMaryland)

# Build the following subdirs
add_subdirectory(ranges)
