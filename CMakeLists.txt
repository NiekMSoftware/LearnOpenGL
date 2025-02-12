cmake_minimum_required(VERSION 3.20)
project(LudusCore)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Configure SDL
include(FetchContent)

# Configure GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# Configure build options before making content available
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Configure SDL
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.0
)

FetchContent_MakeAvailable(SDL glfw)

# Add precompiled header
add_library(pch STATIC
    src/pch.cpp
    inc/pch.h
)
target_precompile_headers(pch PUBLIC
    inc/pch.h
)

add_library(glad STATIC extern/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/extern/glad/include)

# Include all source and header files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
file(GLOB_RECURSE HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h"
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${OPENGL_INCLUDE_DIR}
    ${glfw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern/glad/include
)

# Link OpenGL libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    glad
    glfw
    ${OPENGL_LIBRARIES}
    pch
)
add_subdirectory(src/getting_started)

target_link_libraries(pch PUBLIC glfw glad)