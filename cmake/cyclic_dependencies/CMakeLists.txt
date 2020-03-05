cmake_minimum_required(VERSION 3.15)
project(TestCycle LANGUAGES CXX)

add_subdirectory(LibraryA)
add_subdirectory(LibraryB)
add_subdirectory(LibraryC)
add_subdirectory(ExecutableApp)
