# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Source the top-level cmake file
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/../.external")
include(${EXTERNAL_DIR}/scripts/cmake/Common.cmake)

# Set the project name
project(ExampleRanges LANGUAGES CXX)

# Add the top-level include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Use the defined type of ranges
if(RANGES)
	message("Using RANGES=${RANGES}")
	add_definitions(-DRANGES_${RANGES})

	# Ranges v3
	if("${RANGES}" MATCHES "V3")
		message("Using Eric Niebler's range-v3 library")
		include_directories(${EXTERNAL_DIR}/range-v3/include)
	elseif("${RANGES}" MATCHES "NANO")
		message("Using Tristan Brindle's NanoRange library")
		include_directories(${EXTERNAL_DIR}/NanoRange/include)
	elseif("${RANGES}" MATCHES "CMCSTL2")
		message("Using Casey Carter's CMCSTL2 range library")
		include_directories(${EXTERNAL_DIR}/cmcstl2/include)
	else()
		message("Unknown range library (${RANGES})")
	endif()
endif(RANGES)

# Delve into the src/ subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
