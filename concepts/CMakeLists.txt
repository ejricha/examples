# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
include(${CMAKE_SOURCE_DIR}/../cmake/Common.cmake)

# Set the project name
project(ExampleConcepts LANGUAGES CXX)

# Delve into the src/ subdirectory
add_subdirectory(src)
