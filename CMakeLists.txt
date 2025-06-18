cmake_minimum_required(VERSION 3.25)
project(molalang VERSION 1 LANGUAGES C)



#add_compile_options("-O3" "-march=native")

add_subdirectory(molalib)
add_subdirectory(molaint)
add_subdirectory(modules)