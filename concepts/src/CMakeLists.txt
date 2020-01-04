# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
include(${CMAKE_SOURCE_DIR}/../cmake/Common.cmake)

message("Using Casey Carter's CMCSTL2 library")
include_directories(${CMAKE_SOURCE_DIR}/../.external/cmcstl2/include)

# Build shared libraries for BaseClass and DerivedClass
set(BUILD_SHARED_LIBS ON)
add_library(base BaseClass.cpp BaseClass.hpp)
add_library(derived DerivedClass.cpp DerivedClass.hpp)

# Add an executable built from a single source file
add_executable(Examples.bin Examples.cpp)
target_link_libraries(Examples.bin PUBLIC base derived)
