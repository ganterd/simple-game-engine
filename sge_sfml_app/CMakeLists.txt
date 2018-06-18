cmake_minimum_required(VERSION 3.10)

#find_package(SFML REQUIRED graphics window system)

file(GLOB_RECURSE APP_HEADERS "*.hpp")
file(GLOB_RECURSE APP_SOURCES "*.cpp")

add_executable(sge_sfml_app ${APP_HEADERS} ${APP_SOURCES})

add_dependencies(
	sge_sfml_app 
	sge_lib 
	external_sfml
)

target_link_libraries(
	sge_sfml_app 
	sge_lib 
	sfml-window 
	sfml-graphics 
	sfml-system 
	assimp 
	pthread
	GLEW
	${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
	tinyxml2
)
