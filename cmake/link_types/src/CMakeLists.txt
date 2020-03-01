# Application with no source code
add_executable(App app.cpp)

# Libraries with empty source code
add_library(Cat cat.cpp)
add_library(A   a.cpp)
add_library(B   b.cpp)
add_library(C   c.cpp)
add_library(D   d.cpp)
add_library(E   e.cpp)
add_library(F   f.cpp)
add_library(G   g.cpp)

# Define some dependencies
target_link_libraries(App
	INTERFACE Cat
	)
target_link_libraries(Cat
	PUBLIC    A B
	PRIVATE   C D
	INTERFACE E
	PUBLIC    F G
	)
