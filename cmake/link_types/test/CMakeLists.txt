# Set the project name
project(TestLink LANGUAGES CXX)

# All source files are in src/,
#  and header files are in include/
set(SRC src)
set(INC include)
include_directories(${INC})

# Add a top-level build target
add_custom_target(${PROJECT_NAME})

# Add apps/libraries from the same source code a number of ways
foreach(LinkA IN ITEMS PUBLIC PRIVATE INTERFACE)
	foreach(LinkB IN ITEMS PUBLIC PRIVATE INTERFACE)
		set(Type ${LinkA}A_${LinkB}B)
		message(STATUS "Building ${Type}")

		# Set the names of the three targets
		set(TargetApp ${PROJECT_NAME}_App_${Type})
		set(TargetA ${PROJECT_NAME}_A_${Type})
		set(TargetB ${PROJECT_NAME}_B_${Type})

		# Add an application, and make project depend on it
		add_executable(${TargetApp} ${SRC}/main.cpp)
		add_dependencies(${PROJECT_NAME} ${TargetApp})
		
		# Libraries
		add_library(${TargetA} ${SRC}/a.cpp)
		add_library(${TargetB} ${SRC}/b.cpp)
		
		# Get uppercase versions of linking variables
		string(TOUPPER ${LinkA} LINKA)
		string(TOUPPER ${LinkB} LINKB)
	
		# Set properties to each library
		target_link_libraries(${TargetApp}
			${LINKA} ${TargetA}
			${LINKB} ${TargetB}
			)
		target_link_libraries(${TargetA}
			${LINKB} ${TargetB}
			)
	endforeach()
endforeach()

