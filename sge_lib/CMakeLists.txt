
file(GLOB_RECURSE SGE_LIB_HEADERS "*.hpp")
file(GLOB_RECURSE SGE_LIB_SOURCES "*.cpp")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
foreach(FILE ${SGE_LIB_HEADERS} ${SGE_LIB_SOURCES})
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

	# Add the file to the group
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DSGE_BUILDING)

add_library(
	sge_lib SHARED
	#${SGE_LIB_HEADERS}
	${SGE_LIB_SOURCES}
)
add_dependencies(
	sge_lib
	external_assimp
	external_glew
	external_glm
	external_tinyxml2
	external_easylogging
)
#message("GLEW: " ${GLEW_LIBRARY} "...")
target_link_libraries( sge_lib
    ${SFML_LIBRARIES}
	${ASSIMP_LIBRARY}
	${TINYXML2_LIBRARY}
	${GLEW_LIBRARY}
	${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
)

remove_definitions(-DSGE_BUILDING)
