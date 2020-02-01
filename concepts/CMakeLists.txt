# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/../.external")
include(${EXTERNAL_DIR}/scripts/cmake/Common.cmake)

# Set the project name
project(ExampleConcepts LANGUAGES CXX)

# Delve into the src/ subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
