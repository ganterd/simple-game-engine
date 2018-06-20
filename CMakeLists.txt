cmake_minimum_required(VERSION 3.2.2)

project("VCT")



set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Pull, build and include all external projects
include(PullExternal.cmake)

## Required libraries (Search handled by CMake)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)


## Addind definition to fail on first error. Makes it easier to read.
if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	add_definitions( -Wfatal-errors -std=c++11 )
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

## This sucks... Making symbolic link to resources directory
if(WIN32)
	file(TO_NATIVE_PATH ${CMAKE_BINARY_DIR} WINDOWS_CMAKE_BINARY_DIR)
	file(TO_NATIVE_PATH ${PROJECT_SOURCE_DIR} WINDOWS_PROJECT_DIR)
	message(${WINDOWS_CMAKE_BINARY_DIR})
	message(${WINDOWS_PROJECT_DIR})
	add_custom_target(LinkResources
	  COMMAND rmdir ${WINDOWS_CMAKE_BINARY_DIR}\\sge_sfml_app\\resources\\ /Q
	  COMMAND mklink ${WINDOWS_CMAKE_BINARY_DIR}\\sge_sfml_app\\resources\\ ${WINDOWS_PROJECT_DIR}\\resources\\ /D
	)
endif()

add_subdirectory(sge_lib)
include_directories(sge_lib)

add_subdirectory(sge_sfml_app)

## Copy shader files to executable directory
#file(GLOB SHADER_FILES "${VOLUME_RENDERER_SRC}*.txt")
#file(COPY ${SHADER_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
