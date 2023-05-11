cmake_minimum_required(VERSION 3.5)

project(ChessClone LANGUAGES CXX)

#setup GLFW and GLEW for compilation with their appropriate cmake
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLEW)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLFW)

#add the include dirs for use in this project
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLEW/include/GL" "${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLFW/include/GLFW")

#shared libs between linux and windows
set(LIBRARIES GLEW glfw)

if(WIN32)#for windows
set(LIBRARIES ${LIBRARIES} opengl32)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Oi -Ox" CACHE STRING "Flags used by the C++ compiler." FORCE)
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT ChessClone)
else()#for linux
set(LIBRARIES ${LIBRARIES} GL)
#set default configuration for linux if no arguments are passed
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug)
endif()
endif()

#set c++ version and make it a requirement
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions(-DGLEW_STATIC)

#set source files and header files
file(GLOB SOURCES "ChessClone/src/*.cpp")
file(GLOB HEADER_FILES "ChessClone/src/*.h")

#set output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE})

#feed the project with source + header files
add_executable(ChessClone ${SOURCES} ${HEADER_FILES})
#add the libraries to link with
target_link_libraries(ChessClone ${LIBRARIES})
 
 
#this is a test to set predefined configurations with a custom one

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
#set(CMAKE_CXX_FLAGS_DEBUGPLUS "-Wall -g -O0" CACHE STRING "Flags used by the C++ compiler for DebugPlus build type" FORCE)
#set(CMAKE_EXE_LINKER_FLAGS_DEBUGPLUS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags used by the C++ compiler for DebugPlus build type" FORCE)
#set(CMAKE_CONFIGURATION_TYPES "Debug;Release;DebugPlus" CACHE STRING "List of supported configuration types." FORCE)
#set(CMAKE_CXX_FLAGS_DEBUGPLUS "${CMAKE_CXX_FLAGS_DEBUGPLUS}" CACHE STRING "Flags used by the C++ compiler for DebugPlus build type" FORCE)