# Add third-party dependencies
add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)

# Create GLCore library
add_library(GLCore
        src/App.cpp
        src/Window.cpp

        include/GLCore/App.h
        include/GLCore/Window.h
)

target_include_directories(GLCore PUBLIC include)
target_link_libraries(GLCore PUBLIC glfw glad glm)