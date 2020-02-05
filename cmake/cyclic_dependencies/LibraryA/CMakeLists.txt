# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(LibraryA LANGUAGES CXX)

add_library(A a.cpp)

# A depends on B
target_link_libraries(A B)
