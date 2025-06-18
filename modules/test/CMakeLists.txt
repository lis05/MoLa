cmake_minimum_required(VERSION 3.0)

# Set the project name 
project(cmodule_test)

# Add the source file
set(SOURCE_FILE test.c)

# Create a shared library
add_library(test SHARED ${SOURCE_FILE})

# Set the output directory for the shared library
set_target_properties(test PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)