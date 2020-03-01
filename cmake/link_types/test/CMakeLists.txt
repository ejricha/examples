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
foreach(LinkA IN ITEMS Public Private Interface None)
	foreach(LinkB IN ITEMS Public Private Interface None)
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
		if(NOT LinkA STREQUAL None)
			if(NOT LinkB STREQUAL None)
				message(STATUS "  App links to both A and B")
				target_link_libraries(${TargetApp}
					${LINKA} ${TargetA}
					${LINKB} ${TargetB}
					)
				message(STATUS "  Lib links to B")
				target_link_libraries(${TargetA}
					${LINKB} ${TargetB}
					)
			else()
				message(STATUS "  App links only to A")
				target_link_libraries(${TargetApp}
					${LINKA} ${TargetA}
					)
				message(STATUS "  Lib links to nothing")
			endif()
		else()
			if(NOT LinkB STREQUAL None)
				message(STATUS "  App links only to B")
				target_link_libraries(${TargetApp}
					${LINKB} ${TargetB}
					)
				message(STATUS "  Lib links to B")
				target_link_libraries(${TargetA}
					${LINKB} ${TargetB}
					)
			else()
				message(STATUS "  App links to nothing")
				message(STATUS "  Lib links to nothing")
			endif()
		endif()

		# Also add compile definitions
		if(LinkA STREQUAL Public OR LinkA STREQUAL Private)
			if(LinkA STREQUAL Public OR LinkB STREQUAL Public OR LinkB STREQUAL Private)
				message(STATUS "  App prints from both A and B")
				target_compile_definitions(${TargetApp}
					PUBLIC PRINT_FROM_A
					PUBLIC PRINT_FROM_B
				)
				message(STATUS "  Lib prints from B")
				target_compile_definitions(${TargetA}
					PUBLIC PRINT_FROM_B
					)
			else()
				message(STATUS "  App prints only from A")
				target_compile_definitions(${TargetApp}
					PUBLIC PRINT_FROM_A
					)
				message(STATUS "  Lib prints from nothing")
			endif()
		elseif(LinkA STREQUAL Interface OR LinkB STREQUAL Public OR LinkB STREQUAL Private)
			message(STATUS "  App prints only from B")
			target_compile_definitions(${TargetApp}
				PUBLIC PRINT_FROM_B
				)
			message(STATUS "  Lib prints from B")
			target_compile_definitions(${TargetA}
				PUBLIC PRINT_FROM_B
				)
		else()
			message(STATUS "  App prints from nothing")
			message(STATUS "  Lib prints from nothing")
		endif()
	endforeach()
endforeach()

