# External Libraries
include(ExternalProject)
ExternalProject_Add(
	external_assimp
	PREFIX ${PROJECT_SOURCE_DIR}/external/assimp/
	GIT_REPOSITORY https://github.com/assimp/assimp.git
	GIT_TAG v4.1.0
	GIT_PROGRESS 1
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/assimp/
		-DASSIMP_NO_EXPORT=On
		-DASSIMP_BUILD_ASSIMP_TOOLS=Off
		-DASSIMP_BUILD_TESTS=Off
		-DCMAKE_INSTALL_MESSAGE=LAZY
)

ExternalProject_Add(
	external_sfml 
	PREFIX ${PROJECT_SOURCE_DIR}/external/assimp/
	GIT_REPOSITORY https://github.com/SFML/SFML.git 
	GIT_TAG 2.5.0
	GIT_PROGRESS 1
	CMAKE_ARGS 
		-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/sfml/
		-DSFML_BUILD_AUDIO=Off
		-DSFML_BUILD_NETWORK=Off	
		-DCMAKE_INSTALL_MESSAGE=LAZY
)

ExternalProject_Add(
	external_glm
	PREFIX ${PROJECT_SOURCE_DIR}/external/glm/
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 0.9.9.0
	GIT_PROGRESS 1
	CMAKE_ARGS
		
		-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/glm/
		-DCMAKE_INSTALL_MESSAGE=LAZY
)

ExternalProject_Add(
	external_tinyxml2
	PREFIX ${PROJECT_SOURCE_DIR}/external/tinyxml2/
	GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
	GIT_TAG 6.2.0
	GIT_PROGRESS 1
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/tinyxml2/
		-DCMAKE_INSTALL_MESSAGE=LAZY
)

ExternalProject_Add(
	external_easylogging
	PREFIX ${PROJECT_SOURCE_DIR}/external/easylogging/
	GIT_REPOSITORY https://github.com/muflihun/easyloggingpp.git
	GIT_TAG v9.96.4
	GIT_PROGRESS 1
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/easylogging/
		-DCMAKE_INSTALL_MESSAGE=LAZY
)


ExternalProject_Add(
	external_glew
	PREFIX ${PROJECT_SOURCE_DIR}/external/glew/
	URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip
	CONFIGURE_COMMAND ${CMAKE_COMMAND} 
		-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
	        <SOURCE_DIR>/build/cmake # Tell CMake to use subdirectory as source.
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/glew/
		-DBUILD_UTILS=Off
		-DCMAKE_INSTALL_MESSAGE=LAZY
)

include_directories(external/assimp/include)
include_directories(external/easylogging/include)
include_directories(external/glew/include)
include_directories(external/glm/include)
include_directories(external/tinyxml2/include)
include_directories(external/sfml/include)

link_directories(external/assimp/lib)
link_directories(external/glew/lib)
link_directories(external/tinyxml2/lib)
link_directories(external/sfml/lib)
