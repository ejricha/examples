# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(TestCycle LANGUAGES CXX)

add_subdirectory(a)
add_subdirectory(b)
add_subdirectory(c)
add_subdirectory(main)
