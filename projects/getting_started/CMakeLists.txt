# Create executables for each source file in this chapter
file(GLOB MAIN main.cpp)

# Get the file name without extension
get_filename_component(executable_name ${MAIN} NAME_WE)

# Remove the "_main" suffix
string(REPLACE "main" "getting_started" executable_name ${executable_name})

# Create an executable for each source file
add_executable(${executable_name} ${MAIN})

# Link the necessary libraries for your OpenGL project
target_link_libraries(${executable_name} PRIVATE
    SDL3::SDL3
    glad
    glfw
    ${OPENGL_LIBRARIES}
    pch
)

# Add the include directories needed for your project
target_include_directories(${executable_name} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${OPENGL_INCLUDE_DIR}
    ${glfw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern/glad/include
)

# Add precompiled headers
target_precompile_headers(${executable_name} REUSE_FROM pch)