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
# - Adds a per-target custom dependency that runs on every build of the target, ensuring assets are copied whenever you build the application.
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

    # Create a stamp-based custom command that re-runs when any asset changes
    # Enumerate asset files (tracks additions/removals with CONFIGURE_DEPENDS)
    file(GLOB_RECURSE _asset_files CONFIGURE_DEPENDS "${ASSETS_DIR}/*")
    set(_stamp "${CMAKE_CURRENT_BINARY_DIR}/copy_assets_${TARGET_NAME}.stamp")

    add_custom_command(OUTPUT "${_stamp}"
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${_dest}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_dest}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${_dest}"
        COMMAND ${CMAKE_COMMAND} -E touch "${_stamp}"
        DEPENDS ${_asset_files}
        COMMENT "Copying assets for ${TARGET_NAME}: '${ASSETS_DIR}' -> '${_dest}'"
        VERBATIM)

    # Create a custom target that depends on the stamp, and make the app depend on it
    set(_copy_target "copy_assets_${TARGET_NAME}")
    add_custom_target(${_copy_target} DEPENDS "${_stamp}")
    add_dependencies(${TARGET_NAME} ${_copy_target})

    # Improve Visual Studio debugging experience
    if (MSVC)
        set_property(TARGET ${TARGET_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")
    endif()
endfunction()
