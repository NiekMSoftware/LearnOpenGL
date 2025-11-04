add_library(glad src/glad.c)
target_sources(glad PRIVATE include/glad/glad.h)
target_include_directories(glad PUBLIC include)