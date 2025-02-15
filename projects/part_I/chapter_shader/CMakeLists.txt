get_filename_component(executable_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${executable_name} main.cpp)

# Link necessary libraries
target_link_libraries(${executable_name} PRIVATE
    SDL3::SDL3
    glad
    glfw
    ${OPENGL_LIBRARIES}
    pch
)

# Add include directories
target_include_directories(${executable_name} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${OPENGL_INCLUDE_DIR}
    ${glfw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern/glad/include
)

# Add precompiled headers
target_precompile_headers(${executable_name} REUSE_FROM pch)

add_custom_command(TARGET ${executable_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    ${CMAKE_CURRENT_BINARY_DIR}/shaders
)