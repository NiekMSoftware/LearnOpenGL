# Reusable function to copy an assets directory next to a target's binary after build
#
# Usage:
#   copy_assets(<TARGET_NAME> <ASSETS_DIR> [DESTINATION <dest_dir>])
#
# - <TARGET_NAME>: Name of an existing CMake target (executable or library).
# - <ASSETS_DIR>: Source directory with assets to copy.
# - DESTINATION: Optional destination directory. Defaults to "$<TARGET_FILE_DIR:<TARGET_NAME>>/assets".
#
# Notes:
# - Adds a POST_BUILD step so assets are available for run/debug.
# - For MSVC, sets VS_DEBUGGER_WORKING_DIRECTORY to the target's output directory for better F5 experience.
#
function(copy_assets TARGET_NAME ASSETS_DIR)
    set(options)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs)
    cmake_parse_arguments(CA "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT TARGET ${TARGET_NAME})
        message(FATAL_ERROR "copy_assets: target '${TARGET_NAME}' does not exist")
    endif()

    if (NOT EXISTS "${ASSETS_DIR}")
        message(WARNING "copy_assets: assets directory '${ASSETS_DIR}' not found; skipping copy step for target '${TARGET_NAME}'")
        return()
    endif()

    if (CA_DESTINATION)
        set(_dest "${CA_DESTINATION}")
    else()
        set(_dest "$<TARGET_FILE_DIR:${TARGET_NAME}>/assets")
    endif()

    # Ensure destination is recreated and copy contents
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${_dest}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_dest}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${_dest}"
        COMMENT "Copying assets for ${TARGET_NAME}: '${ASSETS_DIR}' -> '${_dest}'")

    # Improve Visual Studio debugging experience
    if (MSVC)
        set_property(TARGET ${TARGET_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")
    endif()
endfunction()
