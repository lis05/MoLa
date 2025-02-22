#ifndef __mola_env_h__
#define __mola_env_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cmap.h"

struct Object;

typedef struct Env {
    map_t(ident, Object *) exported_objects;
    
} Env;

#endif
