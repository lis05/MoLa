#ifndef __mola_env_h__
#define __mola_env_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cmap.h"
#include "ident_map.h"

struct Object;

typedef struct Env {
    IdentMap exported_objects, globals;    // globals are global variables, functions, and types
    int64_t  absolute_offset;              // of the first instruction in the module

} Env;

int64_t     envGenAvailableId();
struct Env *envGetById(int64_t id);
int64_t     envCreate(int64_t absolute_offset);
void        envInit();

#endif
