add_executable(Shaders main.cpp)
target_link_libraries(Shaders PRIVATE GLCore)

# Copy the local assets directory next to the built executable for run/debug
include(CopyAssets)
copy_assets(Shaders "${CMAKE_CURRENT_SOURCE_DIR}/assets")