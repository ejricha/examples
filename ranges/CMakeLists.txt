# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
include(${CMAKE_SOURCE_DIR}/cmake/Common.cmake)

# Set the project name
project(ExampleRanges)

# Add the top-level include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Use the defined type of ranges
if(RANGES)
	message("Using RANGES=${RANGES}")
	add_definitions(-DRANGES_${RANGES})

	# Ranges v3
	include_directories(${CMAKE_SOURCE_DIR}/external/range-v3/include)
endif(RANGES)

# Add an executable built from a single source file
add_executable_cpp("Examples")
