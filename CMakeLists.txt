# CMakeLists.txt
#
# Top-level file

cmake_minimum_required(VERSION 3.0)

# Source some common files
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/../.external")
include(${EXTERNAL_DIR}/scripts/cmake/Common.cmake)

# Set the project name
project(ExampleRanges LANGUAGES CXX)

# Build the following subdirs
add_subdirectory(ranges)
