# Common.cmake
#
# Variables that should be set in all projects

# Requires version 3.0 of cmake
cmake_minimum_required(VERSION 3.0)

# Default to 
set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug/Release")

# We need at least C++17 to run
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Treat warnings as errors
set(CUSTOM_WARNING_LEVEL -Wall -Wextra -pedantic -Werror)

# Use colorful output by default
option(COLOR_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if(COLOR_OUTPUT)
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		add_compile_options(-fdiagnostics-color=always)
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		add_compile_options(-fcolor-diagnostics)
	endif()
endif()

# Macro to add a simple executable
macro(add_executable_cpp NAME)
	set(BIN "${NAME}.bin")
	set(CPP "${NAME}.cpp")
	message("Building ${BIN} from ${CPP}")
	add_executable(${BIN} ${CPP})
endmacro()
