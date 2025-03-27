#include "scope.h"
#include "alloc.h"
#include "cmap.h"
#include "error.h"
#include "object.h"

Scope *scopeCreate(int can_access_parent, Scope *parent) {
    Scope *scope = memalloc(sizeof(Scope));
    assert(scope != NULL);

    map_init(&scope->map, NULL, NULL);
    scope->can_access_parent = can_access_parent;
    scope->parent            = parent;

    return scope;
}

void scopeInsert(Scope *scope, ident name, struct Object *obj) {
    assert(scope != NULL);
    Object *ptr = *map_get(&scope->map, name);
    if (ptr != NULL) {
        signalError(NAME_ERROR_CODE, errstrfmt("Object with name '%s' already exists.", symtabIdentToString(name)));
    }
    map_set(&scope->map, name, obj);
}

struct Object *scopeRecursiveLookup(Scope *scope, ident name) {
    assert(scope != NULL);

    while (1) {
        Object *res = *map_get(&scope->map, name);
        if (res != NULL) {
            return res;
        }

        if (scope->can_access_parent) {
            scope = scope->parent;
        }
        else {
            break;
        }
    }

    signalError(NAME_ERROR_CODE, errstrfmt("Cannot locate '%s'.", symtabIdentToString(name)));
    return NULL;
}

void scopeDestroy(Scope *scope) {
    assert(scope != NULL);
    free(scope);
}
