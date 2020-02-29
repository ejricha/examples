cmake_minimum_required(VERSION 3.15)
project(LinkTypes LANGUAGES CXX)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# All applications will end in .bin
set(CMAKE_EXECUTABLE_SUFFIX .bin)

# Libraries
add_library(cat cat.cpp)
add_library(a   a.cpp)
add_library(b   b.cpp)
add_library(c   c.cpp)
add_library(d   d.cpp)
add_library(e   e.cpp)
add_library(f   f.cpp)
add_library(g   g.cpp)
target_link_libraries(cat
	PUBLIC    a b
	PRIVATE   c d
	INTERFACE e
	PUBLIC    f g
	)
