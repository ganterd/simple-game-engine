# External Libraries

##### Assimp #####
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

# Try to determine the prefix used if not linux..... ffs, this is complicated
# This code is pulled from the Assimp CMake
if( MSVC )
  if( MSVC70 OR MSVC71 )
    set(MSVC_PREFIX "vc70")
  elseif( MSVC80 )
    set(MSVC_PREFIX "vc80")
  elseif( MSVC90 )
    set(MSVC_PREFIX "vc90")
  elseif( MSVC10 )
    set(MSVC_PREFIX "vc100")
  elseif( MSVC11 )
    set(MSVC_PREFIX "vc110")
  elseif( MSVC12 )
    set(MSVC_PREFIX "vc120")
  elseif( MSVC14 )
    set(MSVC_PREFIX "vc140")
  else()
    set(MSVC_PREFIX "vc150")
  endif()
  set(ASSIMP_LIBRARY "assimp-${MSVC_PREFIX}-mt" CACHE STRING "")
else()
	set(ASSIMP_LIBRARY "assimp" CACHE STRING "")
	message("HERE")
endif()


##### SFML #####
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

##### GLM #####
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

##### TinyXML2 ######
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

##### EasyLogging++ #####
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

##### GLEW #####
ExternalProject_Add(
	external_glew
	PREFIX ${PROJECT_SOURCE_DIR}/external/glew/
	URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip
	SOURCE_SUBDIR build/cmake/
	#CONFIGURE_COMMAND ${CMAKE_COMMAND} 
	#	-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
	#        <SOURCE_DIR>/build/cmake # Tell CMake to use subdirectory as source.
	CMAKE_ARGS
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
		-DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external/glew/
		-DBUILD_UTILS=Off
		-DCMAKE_INSTALL_MESSAGE=LAZY
)
if(MSVC)
	set(GLEW_LIBRARY optimized glew32 optimized libglew32 debug glew32d debug libglew32d)
else()
	set(GLEW_LIBRARY glew)
endif()

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

if(WIN32)
	add_custom_target(CopyExternalBinaries
	  COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/bin
	  COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/bin/Debug
	  COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/bin/Release
	  COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/bin/MinSizeRel
	  COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/bin/RelWithDebInfo
	  
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/glew/bin/ ${CMAKE_BINARY_DIR}/bin/Debug/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/assimp/bin/ ${CMAKE_BINARY_DIR}/bin/Debug/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/sfml/bin/ ${CMAKE_BINARY_DIR}/bin/Debug/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/tinyxml2/bin/ ${CMAKE_BINARY_DIR}/bin/Debug/
	  
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/glew/bin/ ${CMAKE_BINARY_DIR}/bin/Release/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/assimp/bin/ ${CMAKE_BINARY_DIR}/bin/Release/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/sfml/bin/ ${CMAKE_BINARY_DIR}/bin/Release/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/tinyxml2/bin/ ${CMAKE_BINARY_DIR}/bin/Release/
	  
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/glew/bin/ ${CMAKE_BINARY_DIR}/bin/MinSizeRel/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/assimp/bin/ ${CMAKE_BINARY_DIR}/bin/MinSizeRel/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/sfml/bin/ ${CMAKE_BINARY_DIR}/bin/MinSizeRel/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/tinyxml2/bin/ ${CMAKE_BINARY_DIR}/bin/MinSizeRel/
	  
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/glew/bin/ ${CMAKE_BINARY_DIR}/bin/RelWithDebInfo/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/assimp/bin/ ${CMAKE_BINARY_DIR}/bin/RelWithDebInfo/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/sfml/bin/ ${CMAKE_BINARY_DIR}/bin/RelWithDebInfo/
	  COMMAND cmake -E copy_directory ${PROJECT_SOURCE_DIR}/external/tinyxml2/bin/ ${CMAKE_BINARY_DIR}/bin/RelWithDebInfo/
	)
else()
	add_custom_target(CopyExternalBinaries )
endif()