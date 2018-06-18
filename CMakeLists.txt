cmake_minimum_required(VERSION 3.2.2)

project("VCT")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Pull, build and include all external projects
include(PullExternal.cmake)

## Required libraries (Search handled by CMake)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)


## Addind definition to fail on first error. Makes it easier to read.
add_definitions( -Wfatal-errors )

add_subdirectory(sge_lib)
include_directories(sge_lib)

add_subdirectory(sge_sfml_app)

## Copy shader files to executable directory
#file(GLOB SHADER_FILES "${VOLUME_RENDERER_SRC}*.txt")
#file(COPY ${SHADER_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
