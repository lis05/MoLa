#include "scope.h"
#include "alloc.h"
#include "cmap.h"
#include "error.h"
#include "gc.h"
#include "object.h"
#include "stat.h"

Scope *scopeCreate(int can_access_parent, Scope *parent) {
    stat_created_scopes++;
    Scope *scope = allocBytesOrError(sizeof(Scope));
    eassert(scope != NULL);

    scope->map               = identMapCreate();
    scope->can_access_parent = can_access_parent;
    scope->parent            = parent;

    return scope;
}

void scopeInsert(Scope *scope, ident name, struct Object *obj) {
    eassert(scope != NULL);
    if (identMapQuery(&scope->map, name)) {
        signalError(NAME_ERROR_CODE, errstrfmt("Object with name '%s' already exists.", symtabIdentToString(name)));
    }
    identMapSet(&scope->map, name, obj);
}

struct Object *scopeRecursiveLookup(Scope *scope, ident name) {
    if (scope == NULL) {
        goto END_SCOPE;
    }

    while (scope != NULL) {
        Object *res = identMapGet(&scope->map, name);
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
END_SCOPE:
    signalError(NAME_ERROR_CODE, errstrfmt("Cannot locate '%s'.", symtabIdentToString(name)));
    return NULL;
}

void scopeDestroy(Scope *scope) {
    stat_created_scopes--;
    eassert(scope != NULL);

    identMapDestroy(&scope->map);

    freeBytes(scope);
}
