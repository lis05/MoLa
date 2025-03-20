#ifndef __mola_env_h__
#define __mola_env_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cmap.h"

struct Object;

typedef struct Env {
    map_t(ident, struct Object *) exported_objects, globals;    // globals are global variables, functions, and types
} Env;

int64_t     envGenAvailableId();
struct Env *envGetById(int64_t id);
int64_t     envCreate();
void        envInit();

#endif
