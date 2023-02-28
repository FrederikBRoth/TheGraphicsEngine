# CMakeList.txt : CMake project for TheGraphicsEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

project(TheGraphicsEngine)
set(CMAKE_CXX_STANDARD 17)
# Add source to this project's executable.
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp
	${CMAKE_SOURCE_DIR}/shaders/*.vert
	${CMAKE_SOURCE_DIR}/shaders/*.frag
	${CMAKE_SOURCE_DIR}/assets/*)
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})


# TODO: Add tests and install targets if needed.
link_directories(${CMAKE_SOURCE_DIR}/lib)
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    configure_file(src/helpers/RenderDistanceDebug.h.in src/helpers/RenderDistance.h)
else()
    configure_file(src/helpers/RenderDistanceRelease.h.in src/helpers/RenderDistance.h)
endif()
include_directories(${CMAKE_BINARY_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/headers)
include_directories(${CMAKE_BINARY_DIR}/shaders)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# ASSIMP
find_package(ASSIMP REQUIRED)

# FREETYPE
find_package(FREETYPE REQUIRED)

# IRRKLANG
find_package(IRRKLANG REQUIRED)

# STB_IMAGE
add_library(STB_IMAGE "thirdparty/stb_image.cpp")

# GLAD
add_library(GLAD "thirdparty/glad.c")



#add_custom_target(Assets ALL
#    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
#)
#add_dependencies(Assets TheGraphicsEngine)
# Put all libraries into a variable
set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS} ${ASSIMP_LIBRARY} STB_IMAGE ${FREETYPE_LIBRARY} ${IRRKLANG_LIBRARY})
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/headers"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/include/glad"
	"${CMAKE_SOURCE_DIR}/include/glm"

)
# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})
