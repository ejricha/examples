# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/../.external")
include(${EXTERNAL_DIR}/scripts/cmake/Common.cmake)

message("Using Casey Carter's CMCSTL2 library")
include_directories(${EXTERNAL_DIR}/cmcstl2/include)

# Add the top-level include directory for concepts
include_directories(${CMAKE_SOURCE_DIR}/include)

# Build shared libraries for BaseClass and DerivedClass
set(BUILD_SHARED_LIBS ON)
add_library(base BaseClass.cpp)
add_library(derived DerivedClass.cpp)

# Add an executable built from a single source file
add_executable(Examples.bin Examples.cpp)
target_link_libraries(Examples.bin PUBLIC base derived)
