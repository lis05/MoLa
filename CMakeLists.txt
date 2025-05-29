cmake_minimum_required(VERSION 3.25)
project(molalang VERSION 1 LANGUAGES C)

# Enable debugging and some optimization (good for Valgrind)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g")

# Set the C standard to C23
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable verbose output and compile_commands.json
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source directory
add_subdirectory(src)
