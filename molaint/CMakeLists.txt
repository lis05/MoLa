add_executable(molaint 
src/molaint.c

src/builtin/builtin.h
src/builtin/builtin.c

)

target_link_libraries(molaint PRIVATE molalib)