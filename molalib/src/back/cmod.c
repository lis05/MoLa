#include "cmod.h"
#include "../error.h"
#include "api.h"
#include <dlfcn.h>

int64_t      module_id = 0;
static void *imported_modules[1024];
static Env  *envs[1024];

extern Symtab *lex_symtab;

int64_t openCModule(char *path) {
    imported_modules[module_id] = dlopen(path, RTLD_LAZY);

    if (!imported_modules[module_id]) {
        signalError(INTERNAL_ERROR_CODE, errstrfmt("Failed to dlopen %s: %s", path, dlerror()));
    }

    envs[module_id] = envCreate(0, "CMODULE");

    return module_id++;
}

void closeAllCModules() {
    for (int i = 0; i < module_id; i++) {
        dlclose(imported_modules[i]);
        // destroyEnv(envs[i]);
    }
}

Object *cModuleRequestFunction(int64_t mid, char *name) {
    if (mid >= module_id) {
        signalError(VALUE_ERROR_CODE, "Cannot request a function from an unexistent c module");
    }

    molalog("requesting: %s from module %lld\n", name, mid);

    CFunction *(*handle)(Env *env);
    handle = dlsym(imported_modules[mid], name);

    if (!handle) {
        signalError(VALUE_ERROR_CODE, "The requested function is not present in the c module");
    }

    CFunction *cf = handle(envs[mid]);
    Object *obj = objectCreate(C_FUNCTION_TYPE, raw64(cf));

    return obj;
}

Object *cModuleRequestType(int64_t mid, char *name) {}
