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
    inc/pch.cpp
    inc/pch.h
)
target_precompile_headers(pch PUBLIC
    inc/pch.h
)

add_library(glad STATIC extern/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/extern/glad/include)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${OPENGL_INCLUDE_DIR}
    ${glfw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern/glad/include
)

# Add subdirectories for each chapter or section
add_subdirectory(projects/getting_started)

# Link pch with glfw and glad
target_link_libraries(pch PUBLIC glfw glad)