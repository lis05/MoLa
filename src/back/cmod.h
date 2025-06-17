#ifndef __mola_cmod_h__
#define __mola_cmod_h__

#include "types.h"

/*

the following functions are only used when importing a C module from Mola

the whole process looks as follows:
1. in mola, we first create a C module: num = cmodule("module.so")
    the underlying C functiln calls openCModule("module.so")
2. then, we request a member: cloadf(num, "foo")
    the underlying C function calls cModuleRequestFunction(num, "foo")
    an object is returned
3. after the ENTIRE program (with all modules) finishes, closeAllCModules() is called

for types, the interaction is similar

for a C module to provide a function "NAME" at a request, it has to do the following:
1. implement the function "cmodule_init" which will be called during cmodule("module.so")
2. implement a function "cmodule_provide_function_NAME" which will return a CFunction object
    for type, the name is "cmodule_provide_type_NAME"


cmodule(file) - filepath from MOLA_MODULES_PATH
cmodule_local(file) - filepath from the file in which this function is called
cmodule_global(file) - global filepath

*/

/*

path must be global path

*/
int64_t openCModule(char *path);

void closeAllCModules();

struct Object; 
struct Object *cModuleRequestFunction(int64_t mid, char *name);
struct Object *cModuleRequestType(int64_t mid, char *name);

#endif
