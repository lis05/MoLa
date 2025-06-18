#ifndef __mola_scope_h__
#define __mola_scope_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cmap.h"
#include "ident_map.h"

struct Object;

typedef struct Scope {
    IdentMap      map;
    struct Scope *parent;
    uint           can_access_parent : 1;
} Scope;

Scope         *scopeCreate(int can_access_parent, Scope *parent);
void           scopeInsert(Scope *scope, ident name, struct Object *obj);
struct Object *scopeRecursiveLookup(Scope *scope, ident name);    // NULL if the object is missing
void           scopeDestroy(Scope *scope);

#endif
