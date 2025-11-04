cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

# custom library
add_subdirectory(GLCore)

# LearnOpenGL - Learning Sources
add_subdirectory(LearnOpenGL/creating_a_window)