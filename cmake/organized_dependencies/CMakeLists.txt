cmake_minimum_required(VERSION 3.15)
project(OranizedDependencies LANGUAGES CXX)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# All source files are in src/,
#  and header files are in include/
set(SRC src)
set(INC include)
include_directories(${INC})

# Build each app/lib twice
foreach(X deps_full deps_less)
	# Applications
	add_executable(${X}_a1 ${SRC}/a1.cpp)

	# Libraries
	add_library(${X}_b1 ${SRC}/b1.cpp)
	add_library(${X}_e7 ${SRC}/e7.cpp)
endforeach()

# Fully specified dependencies
set(X deps_full)
target_link_libraries(${X}_a1 ${X}_b1)
target_link_libraries(${X}_a1 ${X}_e7)
target_link_libraries(${X}_b1 ${X}_e7)

# Fewer dependencies
set(X deps_less)
target_link_libraries(${X}_a1 ${X}_b1)
target_link_libraries(${X}_b1 ${X}_e7)
