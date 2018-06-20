cmake_minimum_required(VERSION 3.10)

#find_package(SFML REQUIRED graphics window system)

file(GLOB_RECURSE APP_HEADERS "*.hpp")
file(GLOB_RECURSE APP_SOURCES "*.cpp")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
foreach(FILE ${APP_HEADERS} ${APP_SOURCES}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
	
    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	
    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

	# Add the file to the group
    source_group("${GROUP}" FILES "${FILE}")
endforeach()


add_executable(sge_sfml_app ${APP_HEADERS} ${APP_SOURCES})

add_dependencies(
	sge_sfml_app 
	sge_lib 
	external_sfml
	CopyExternalBinaries
	LinkResources
)

target_link_libraries(
	sge_sfml_app 
	sge_lib 
	optimized sfml-window 
	optimized sfml-graphics 
	optimized sfml-system 
	debug sfml-window-d 
	debug sfml-graphics-d 
	debug sfml-system-d 
	${ASSIMP_LIBRARY}  
	#pthread
	optimized tinyxml2
	debug tinyxml2d
	${GLEW_LIBRARY}
	${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
)
