cmake_minimum_required(VERSION 3.25)
project(molalang VERSION 1 LANGUAGES C)

add_subdirectory(src)


#add_compile_options("-O3" "-march=native")

set_property(TARGET molalang PROPERTY C_STANDARD 23)