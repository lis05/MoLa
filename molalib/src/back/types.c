#include "types.h"
#include "../front/api.h"
#include "../util.h"
#include "alloc.h"
#include "error.h"
#include "gc.h"
#include "object.h"
#include "stat.h"

static int64_t cnt = 0;


TypeValue *typeValueCreate(size_t n_fields, ident *fields, size_t n_methods, ident *methods) {
    stat_created_types++;
    TypeValue *res = allocOrError(sizeof(TypeValue));

    res->n_fields = n_fields;
    res->fields   = allocOrError(sizeof(ident) * n_fields);
    memcpy(res->fields, fields, sizeof(ident) * n_fields);

    res->n_methods    = n_methods;
    res->method_names = allocOrError(sizeof(ident) * n_methods);
    memcpy(res->method_names, methods, sizeof(ident) * n_methods);

    res->methods = identMapCreate();

    res->gc_mark         = gc_mark;
    res->ref_count       = 0;
    res->is_gc_protected = 0;

    gcTrackTypeValue(res);

    return res;
}

TypeValue *typeValueCopy(TypeValue *val) {
    return val;
}

void typeValueDestroy(TypeValue *val) {
    stat_created_types--;
    freeBytes(val->fields);
    freeBytes(val->method_names);
    identMapDestroy(&val->methods);
    freeBytes(val);
    gcUntrackTypeValue(val);
}

void typeValueGCOnlyUnref(TypeValue *val) {
    identMapGCOnlyUnref(&val->methods);
}

void typeValueGCDestroy(TypeValue *val) {
    stat_created_types--;
    freeBytes(val->fields);
    freeBytes(val->method_names);
    identMapGCDestroy(&val->methods);
    freeBytes(val);
    gcUntrackTypeValue(val);
}

void typeValueAddMethod(TypeValue *val, ident name, struct Object *method) {
    if (identMapQuery(&val->methods, name)) {
        signalError(NAME_COLLISION_ERROR_CODE, "Method with this name has already been defined");
    }

    // slow, but who cares (i do care (well i don't (go kill yourself)))
    int flag = 0;
    for (size_t i = 0; i < val->n_methods; i++) {
        if (val->method_names[i] == name) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        signalError(NAME_ERROR_CODE, "Invalid method name");
    }

    identMapSet(&val->methods, name, method);
}

struct Object *typeValueLookupMethod(TypeValue *val, ident name) {
    void *res = identMapGet(&val->methods, name);
    if (res == NULL) {
        signalError(NAME_COLLISION_ERROR_CODE, errstrfmt("Failed to locate method '%s'", symtabIdentToString(name)));
    }

    return res;
}

void typeValueRef(TypeValue *unit) {
    unit->ref_count++;
}

void typeValueUnref(TypeValue *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageTypeValue(unit);
    }
}

InstanceValue *instanceValueCreate(struct TypeValue *type) {
    stat_created_instances++;
    InstanceValue *res = allocOrError(sizeof(InstanceValue));

    res->type   = type;
    res->fields = identMapCreate();
    for (size_t i = 0; i < type->n_fields; i++) {
        identMapSet(&res->fields, type->fields[i], objectCreate(NULL_TYPE, 0));
    }

    res->ref_count       = 0;
    res->gc_mark         = gc_mark;
    res->is_gc_protected = 0;

    gcTrackInstanceValue(res);

    return res;
}

InstanceValue *instanceValueCopy(InstanceValue *val) {
    return val;
}

void instanceValueDestroy(InstanceValue *val) {
    stat_created_instances--;
    identMapDestroy(&val->fields);
    freeBytes(val);
    gcUntrackInstanceValue(val);
}

void instanceValueGCOnlyUnref(InstanceValue *val) {
    identMapGCOnlyUnref(&val->fields);
}

void instanceValueGCDestroy(InstanceValue *val) {
    stat_created_instances--;
    identMapGCDestroy(&val->fields);
    freeBytes(val);
    gcUntrackInstanceValue(val);
}

struct Object *instanceValueLookupField(InstanceValue *val, ident name) {
    void *res = identMapGet(&val->fields, name);
    if (res == NULL) {
        signalError(NAME_COLLISION_ERROR_CODE, "Failed to locate a field with this name");
    }

    return res;
}

struct Object *instanceValueLookupMethod(InstanceValue *val, ident name) {
    return typeValueLookupMethod(val->type, name);
}

void instanceValueSetField(InstanceValue *val, ident name, Object *obj) {
    instanceValueLookupField(val, name);    // to check if it could exist
    identMapSet(&val->fields, name, obj);
}

void instanceValueRef(InstanceValue *unit) {
    unit->ref_count++;
}

void instanceValueUnref(InstanceValue *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageInstanceValue(unit);
    }
}

MolaFunctionValue *molaFunctionValueCreate(struct Env *env, int64_t rel_offset, size_t n_args, ident *args) {
    stat_created_mola_functions++;
    MolaFunctionValue *res = allocOrError(sizeof(MolaFunctionValue));
    res->env               = env;
    res->relative_offset   = rel_offset;
    res->n_args            = n_args;
    res->args              = args;

    res->ref_count       = 0;
    res->gc_mark         = gc_mark;
    res->is_method       = 0;
    res->is_gc_protected = 0;

    gcTrackMolaFunctionValue(res);

    return res;
}

MolaFunctionValue *molaFunctionValueCopy(MolaFunctionValue *val) {
    return val;    // copy by ref
}

void molaFunctionValueDestroy(MolaFunctionValue *val) {
    stat_created_mola_functions--;
    freeBytes(val->args);
    freeBytes(val);
    gcUntrackMolaFunctionValue(val);
}

void molaFunctionValueGCOnlyUnref(MolaFunctionValue *val) {}

void molaFunctionValueGCDestroy(MolaFunctionValue *val) {
    stat_created_mola_functions--;
    freeBytes(val->args);
    freeBytes(val);
    gcUntrackMolaFunctionValue(val);
}

void molaFunctionValueRef(MolaFunctionValue *unit) {
    unit->ref_count++;
}

void molaFunctionValueUnref(MolaFunctionValue *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageMolaFunctionValue(unit);
    }
}

CFunctionValue *cFunctionValueCreate(struct Env *env, size_t n_args, CFunction function) {
    stat_created_c_functions++;
    CFunctionValue *res = allocOrError(sizeof(CFunctionValue));
    res->env            = env;
    res->n_args         = n_args;
    res->function       = function;

    res->ref_count       = 0;
    res->gc_mark         = gc_mark;
    res->is_method       = 0;
    res->is_gc_protected = 0;

    gcTrackCFunctionValue(res);

    return res;
}

CFunctionValue *cFunctionValueCopy(CFunctionValue *val) {
    return val;
}

void cFunctionValueDestroy(CFunctionValue *val) {
    stat_created_c_functions--;
    freeBytes(val);
    gcUntrackCFunctionValue(val);
}

void cFunctionValueGCOnlyUnref(CFunctionValue *val) {}

void cFunctionValueGCDestroy(CFunctionValue *val) {
    stat_created_c_functions--;
    freeBytes(val);
    gcUntrackCFunctionValue(val);
}

void cFunctionValueRef(CFunctionValue *unit) {
    unit->ref_count++;
}

void cFunctionValueUnref(CFunctionValue *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageCFunctionValue(unit);
    }
}

// ============================================
// Methods



void initTypes() {
    init_array();
    init_string();
}
