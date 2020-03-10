cmake_minimum_required(VERSION 3.15)
project(OranizedDependencies LANGUAGES CXX)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# All applications will end in .bin
set(CMAKE_EXECUTABLE_SUFFIX .bin)

# All libraries will have the same version
set(Library_SOVERSION 0)
set(Library_VERSION 0.2.0)

# All source files are in src/,
#  and header files are in include/
set(SRC src)
set(INC include)
include_directories(${INC})

# Add the library as static or shared,
#  but make sure both DepsFull and DepsLess
#  are building each library the same way
string(RANDOM LENGTH 20 ALPHABET "1" R)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
function(AddStaticOrSharedLibrary target source index)
	# Determine the type of library to build
	string(SUBSTRING ${R} ${index} 1 isShared)
	if(isShared)
		set(TYPE SHARED)
	else()
		set(TYPE STATIC)
	endif()

	# Actually add the library
	add_library(${target} ${TYPE} ${source})

	# Set the properties of the library
	set_target_properties(${target} PROPERTIES
		SOVERSION ${LibrarySOVERSION}
		VERSION   ${LibraryVERSION}
		)
endfunction()

# Build each app/lib twice
foreach(X DepsFull DepsLess)
	# Applications
	add_executable(${X}A1 ${SRC}/a1.cpp)
	add_executable(${X}A2 ${SRC}/a2.cpp)
	add_executable(${X}A3 ${SRC}/a3.cpp)

	# Add libraries as randomly STATIC or SHARED
	AddStaticOrSharedLibrary(${X}B1 ${SRC}/b1.cpp 1)
	AddStaticOrSharedLibrary(${X}B2 ${SRC}/b2.cpp 2)
	AddStaticOrSharedLibrary(${X}B3 ${SRC}/b3.cpp 3)
	AddStaticOrSharedLibrary(${X}B4 ${SRC}/b4.cpp 4)
	AddStaticOrSharedLibrary(${X}B5 ${SRC}/b5.cpp 5)
	AddStaticOrSharedLibrary(${X}C1 ${SRC}/c1.cpp 6)
	AddStaticOrSharedLibrary(${X}C2 ${SRC}/c2.cpp 7)
	AddStaticOrSharedLibrary(${X}C3 ${SRC}/c3.cpp 8)
	AddStaticOrSharedLibrary(${X}D1 ${SRC}/d1.cpp 9)
	AddStaticOrSharedLibrary(${X}D2 ${SRC}/d2.cpp 10)
	AddStaticOrSharedLibrary(${X}E1 ${SRC}/e1.cpp 11)
	AddStaticOrSharedLibrary(${X}E2 ${SRC}/e2.cpp 12)
	AddStaticOrSharedLibrary(${X}E3 ${SRC}/e3.cpp 13)
	AddStaticOrSharedLibrary(${X}E4 ${SRC}/e4.cpp 14)

	# Phony target that depends on all the applications
	add_custom_target(${X})
	add_dependencies(${X} ${X}A1 ${X}A2 ${X}A3)
endforeach()

# Only PUBLIC linking works with the random
#  combination of STATIC and SHARED libraries
set(LINK PUBLIC)

# Fully specified dependencies
set(X DepsFull)
target_link_libraries(${X}A1 ${LINK} ${X}B1 ${X}B2 ${X}B3 ${X}B4 ${X}B5 ${X}C1 ${X}C2 ${X}C3 ${X}D1 ${X}D2 ${X}E1 ${X}E2 ${X}E3 ${X}E4)
target_link_libraries(${X}A2 ${LINK} ${X}B1 ${X}B3 ${X}B5 ${X}C1 ${X}C2 ${X}E1 ${X}E2 ${X}E3)
target_link_libraries(${X}A3 ${LINK} ${X}B2 ${X}B3 ${X}C1 ${X}D1 ${X}E1)
target_link_libraries(${X}B1 ${LINK} ${X}C1 ${X}C2 ${X}C3 ${X}D1 ${X}D2 ${X}E1 ${X}E2 ${X}E3 ${X}E4)
target_link_libraries(${X}B2 ${LINK} ${X}C2 ${X}C3 ${X}D2 ${X}E1 ${X}E2 ${X}E4)
target_link_libraries(${X}B3 ${LINK} ${X}D2 ${X}E2 ${X}E3)
target_link_libraries(${X}B4 ${LINK} ${X}C2 ${X}C3 ${X}D2 ${X}E1 ${X}E3 ${X}E4)
target_link_libraries(${X}B5 ${LINK} ${X}C1 ${X}C3 ${X}E1 ${X}E3 ${X}E4)
target_link_libraries(${X}C1 ${LINK} ${X}D1 ${X}D2 ${X}E1 ${X}E2 ${X}E3 ${X}E4)
target_link_libraries(${X}C2 ${LINK} ${X}D1 ${X}E1 ${X}E2 ${X}E4)
target_link_libraries(${X}C3 ${LINK} ${X}E2 ${X}E3)
target_link_libraries(${X}D1 ${LINK} ${X}E1 ${X}E2 ${X}E3 ${X}E4)
target_link_libraries(${X}D2 ${LINK} ${X}E1 ${X}E2 ${X}E3)

# Fewer dependencies
set(X DepsLess)
target_link_libraries(${X}A1 ${LINK} ${X}B1 ${X}B2 ${X}B3 ${X}B4 ${X}B5)
target_link_libraries(${X}A2 ${LINK} ${X}B1 ${X}B3 ${X}B5)
target_link_libraries(${X}A3 ${LINK} ${X}B2 ${X}B3 ${X}C1)
target_link_libraries(${X}B1 ${LINK} ${X}C1 ${X}C2 ${X}C3)
target_link_libraries(${X}B2 ${LINK} ${X}C2 ${X}C3 ${X}D2)
target_link_libraries(${X}B3 ${LINK} ${X}D2)
target_link_libraries(${X}B4 ${LINK} ${X}C2 ${X}C3 ${X}D2)
target_link_libraries(${X}B5 ${LINK} ${X}C1 ${X}C3)
target_link_libraries(${X}C1 ${LINK} ${X}D1 ${X}D2)
target_link_libraries(${X}C2 ${LINK} ${X}D1)
target_link_libraries(${X}C3 ${LINK} ${X}E2 ${X}E3)
target_link_libraries(${X}D1 ${LINK} ${X}E1 ${X}E2 ${X}E3 ${X}E4)
target_link_libraries(${X}D2 ${LINK} ${X}E1 ${X}E2 ${X}E3)
