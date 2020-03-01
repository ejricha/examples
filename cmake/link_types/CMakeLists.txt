cmake_minimum_required(VERSION 3.15)
project(LinkTypes LANGUAGES CXX)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# All applications will end in .bin
set(CMAKE_EXECUTABLE_SUFFIX .bin)

# Libraries with empty source code
add_library(Cat cat.cpp)
add_library(A   a.cpp)
add_library(B   b.cpp)
add_library(C   c.cpp)
add_library(D   d.cpp)
add_library(E   e.cpp)
add_library(F   f.cpp)
add_library(G   g.cpp)
target_link_libraries(Cat
	PUBLIC    A B
	PRIVATE   C D
	INTERFACE E
	PUBLIC    F G
	)
