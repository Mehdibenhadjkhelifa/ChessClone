cmake_minimum_required(VERSION 3.5)

project(ChessClone LANGUAGES CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLEW)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLFW)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLEW/include/GL" "${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLFW/include/GLFW")
#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/Depedencies/GLFW/lib-vc2022")
        
        
set(LIBRARIES
GLEW
 glfw  
 opengl32
 )

 set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /Ox" CACHE STRING "Flags used by the C++ compiler." FORCE)
 
 set(CMAKE_CXX_STANDARD 20)
 set(CMAKE_CXX_STANDARD_REQUIRED ON)

 add_definitions(-DGLEW_STATIC)
 set_directory_properties(PROPERTIES VS_STARTUP_PROJECT ChessClone)

 file(GLOB SOURCES "ChessClone/src/*.cpp")
 file(GLOB HEADER_FILES "ChessClone/src/*.h")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE})

add_executable(ChessClone ${SOURCES} ${HEADER_FILES})
target_link_libraries(ChessClone ${LIBRARIES})
 
 
 
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
#set(CMAKE_CXX_FLAGS_DEBUGPLUS "-Wall -g -O0" CACHE STRING "Flags used by the C++ compiler for DebugPlus build type" FORCE)
#set(CMAKE_EXE_LINKER_FLAGS_DEBUGPLUS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags used by the C++ compiler for DebugPlus build type" FORCE)
#set(CMAKE_CONFIGURATION_TYPES "Debug;Release;DebugPlus" CACHE STRING "List of supported configuration types." FORCE)
#set(CMAKE_CXX_FLAGS_DEBUGPLUS "${CMAKE_CXX_FLAGS_DEBUGPLUS}" CACHE STRING "Flags used by the C++ compiler for DebugPlus build type" FORCE)