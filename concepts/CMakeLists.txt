# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
include(${CMAKE_SOURCE_DIR}/../cmake/Common.cmake)

# Set the project name
project(ExampleConcepts)

# Use the Ranges v3 library for their concepts implementation
message("Using Eric Niebler's range-v3 library")
include_directories(${CMAKE_SOURCE_DIR}/../.external/range-v3/include)

# Delve into the src/ subdirectory
add_subdirectory(src)
