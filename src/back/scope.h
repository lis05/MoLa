#ifndef __mola_scope_h__
#define __mola_scope_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cmap.h"

struct Object;

typedef struct Scope {
    map_t(ident, struct Object *) map;
    struct Scope *parent;
    int           can_access_parent : 1;
} Scope;

Scope         *scopeCreate(int can_access_parent, Scope *parent);
void           scopeInsert(Scope *scope, ident name, struct Object *obj);
struct Object *scopeRecursiveLookup(Scope *scope, ident name);    // NULL if the object is missing
void           scopeDestroy(Scope *scope);

#endif
