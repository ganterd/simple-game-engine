
file(GLOB_RECURSE SGE_LIB_HEADERS "*.hpp")
file(GLOB_RECURSE SGE_LIB_SOURCES "*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(
	sge_lib SHARED 
	${SGE_LIB_HEADERS} 
	${SGE_LIB_SOURCES}
	${PROJECT_SOURCE_DIR}/external/easylogging/include/easylogging++.cc
)
add_dependencies(
	sge_lib 
	external_assimp 
	external_glew
	external_glm 
	external_tinyxml2 
	external_easylogging
)
