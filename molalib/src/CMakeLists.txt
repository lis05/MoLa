# Get all source files in the current directory
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Add the sources to the target 'molalib'
target_sources(molalib PRIVATE ${SRC_SOURCES})

add_subdirectory(front)
add_subdirectory(back)