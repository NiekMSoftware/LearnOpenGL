cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

# Make custom CMake modules available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

# custom library
add_subdirectory(GLCore)

# LearnOpenGL - Learning Sources
add_subdirectory(LearnOpenGL)