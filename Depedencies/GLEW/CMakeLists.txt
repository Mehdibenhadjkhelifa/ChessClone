cmake_minimum_required(VERSION 3.1)
project(GLEW)
# Add the GLEW source files
file(GLOB GLEW_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB GLEW_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/GL/*.h)
# Add the GLEW include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_definitions(-DGLEW_STATIC)
# Build GLEW as a static library
add_library(GLEW STATIC ${GLEW_SOURCE_FILES} ${GLEW_HEADER_FILES})
