# LearnOpenGL - add all lesson subdirectories as separate projects
# Each subdirectory should have its own CMakeLists.txt defining an executable/library
# and link against GLCore within that subdirectory.

# Discover all immediate child directories that contain a CMakeLists.txt
file(GLOB CHILD_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(child ${CHILD_DIRS})
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${child}/CMakeLists.txt)
        add_subdirectory(${child})
    endif()
endforeach()