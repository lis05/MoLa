cmake_minimum_required(VERSION 3.0)

# Set the project name 
project(cmodule_whatisit)

# Add the source file
set(SOURCE_FILE whatisit.c)

# Create a shared library
add_library(whatisit SHARED ${SOURCE_FILE})

# Set the output directory for the shared library
set_target_properties(whatisit PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)