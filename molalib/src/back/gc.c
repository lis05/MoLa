#include "gc.h"
#include "alloc.h"
#include "cmap.h"
#include "env.h"
#include "error.h"
#include "object.h"
#include "scope.h"
#include "types.h"
#include "vm.h"

// TODO: make cmap and cvector use alloc.h

cvector_vector_type(Object *) objects_trash                   = NULL;
cvector_vector_type(StringValue *) strings_trash              = NULL;
cvector_vector_type(ArrayValue *) arrays_trash                = NULL;
cvector_vector_type(TypeValue *) types_trash                  = NULL;
cvector_vector_type(InstanceValue *) instances_trash          = NULL;
cvector_vector_type(MolaFunctionValue *) mola_functions_trash = NULL;
cvector_vector_type(CFunctionValue *) c_functions_trash       = NULL;

cvector_vector_type(Object *) objects_maybe_trash                   = NULL;
cvector_vector_type(StringValue *) strings_maybe_trash              = NULL;
cvector_vector_type(ArrayValue *) arrays_maybe_trash                = NULL;
cvector_vector_type(TypeValue *) types_maybe_trash                  = NULL;
cvector_vector_type(InstanceValue *) instances_maybe_trash          = NULL;
cvector_vector_type(MolaFunctionValue *) mola_functions_maybe_trash = NULL;
cvector_vector_type(CFunctionValue *) c_functions_maybe_trash       = NULL;

void gcDeclareGarbageObject(struct Object *unit) {
    cvector_push_back(objects_maybe_trash, unit);
}

void gcDeclareGarbageStringValue(struct StringValue *unit) {
    cvector_push_back(strings_maybe_trash, unit);
}

void gcDeclareGarbageArrayValue(struct ArrayValue *unit) {
    cvector_push_back(arrays_maybe_trash, unit);
}

void gcDeclareGarbageTypeValue(struct TypeValue *unit) {
    cvector_push_back(types_maybe_trash, unit);
}

void gcDeclareGarbageInstanceValue(struct InstanceValue *unit) {
    cvector_push_back(instances_maybe_trash, unit);
}

void gcDeclareGarbageMolaFunctionValue(struct MolaFunctionValue *unit) {
    cvector_push_back(mola_functions_maybe_trash, unit);
}

void gcDeclareGarbageCFunctionValue(struct CFunctionValue *unit) {
    cvector_push_back(c_functions_maybe_trash, unit);
}

map_t(Object *, int8_t) objects_tracked;
map_t(StringValue *, int8_t) strings_tracked;
map_t(ArrayValue *, int8_t) arrays_tracked;
map_t(TypeValue *, int8_t) types_tracked;
map_t(InstanceValue *, int8_t) instances_tracked;
map_t(MolaFunctionValue *, int8_t) mola_functions_tracked;
map_t(CFunctionValue *, int8_t) c_functions_tracked;

void gcTrackObject(struct Object *unit) {
    map_set(&objects_tracked, unit, 0);
}

void gcTrackStringValue(struct StringValue *unit) {
    map_set(&strings_tracked, unit, 0);
}

void gcTrackArrayValue(struct ArrayValue *unit) {
    map_set(&arrays_tracked, unit, 0);
}

void gcTrackTypeValue(struct TypeValue *unit) {
    map_set(&types_tracked, unit, 0);
}

void gcTrackInstanceValue(struct InstanceValue *unit) {
    map_set(&instances_tracked, unit, 0);
}

void gcTrackMolaFunctionValue(struct MolaFunctionValue *unit) {
    map_set(&mola_functions_tracked, unit, 0);
}

void gcTrackCFunctionValue(struct CFunctionValue *unit) {
    map_set(&c_functions_tracked, unit, 0);
}

void gcUntrackObject(struct Object *unit) {
    map_remove(&objects_tracked, unit);
}

void gcUntrackStringValue(struct StringValue *unit) {
    map_remove(&strings_tracked, unit);
}

void gcUntrackArrayValue(struct ArrayValue *unit) {
    map_remove(&arrays_tracked, unit);
}

void gcUntrackTypeValue(struct TypeValue *unit) {
    map_remove(&types_tracked, unit);
}

void gcUntrackInstanceValue(struct InstanceValue *unit) {
    map_remove(&instances_tracked, unit);
}

void gcUntrackMolaFunctionValue(struct MolaFunctionValue *unit) {
    map_remove(&mola_functions_tracked, unit);
}

void gcUntrackCFunctionValue(struct CFunctionValue *unit) {
    map_remove(&c_functions_tracked, unit);
}

void gcInit() {
    map_init(&objects_tracked, NULL, NULL);
    map_init(&strings_tracked, NULL, NULL);
    map_init(&arrays_tracked, NULL, NULL);
    map_init(&types_tracked, NULL, NULL);
    map_init(&instances_tracked, NULL, NULL);
    map_init(&mola_functions_tracked, NULL, NULL);
    map_init(&c_functions_tracked, NULL, NULL);
}

// warning!: this code relies on ...Destroy not allocating any new memory
void gcRecycle(size_t bytes) {
    for (size_t i = 0; i < cvector_size(objects_maybe_trash); i++) {
        if (map_get(&objects_tracked, objects_maybe_trash[i]) != NULL && objects_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(objects_trash, objects_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(instances_maybe_trash); i++) {
        if (map_get(&instances_tracked, instances_maybe_trash[i]) != NULL && instances_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(instances_trash, instances_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(strings_maybe_trash); i++) {
        if (map_get(&strings_tracked, strings_maybe_trash[i]) != NULL && strings_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(strings_trash, strings_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(arrays_maybe_trash); i++) {
        if (map_get(&arrays_tracked, arrays_maybe_trash[i]) != NULL && arrays_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(arrays_trash, arrays_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(types_maybe_trash); i++) {
        if (map_get(&types_tracked, types_maybe_trash[i]) != NULL && types_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(types_trash, types_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(mola_functions_maybe_trash); i++) {
        if (map_get(&mola_functions_tracked, mola_functions_maybe_trash[i]) != NULL
            && mola_functions_maybe_trash[i]->ref_count == 0)
        {
            cvector_push_back(mola_functions_trash, mola_functions_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(c_functions_maybe_trash); i++) {
        if (map_get(&c_functions_tracked, c_functions_maybe_trash[i]) != NULL && c_functions_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(c_functions_trash, c_functions_maybe_trash[i]);
        }
    }

    cvector_clear(objects_maybe_trash);
    cvector_clear(strings_maybe_trash);
    cvector_clear(arrays_maybe_trash);
    cvector_clear(types_maybe_trash);
    cvector_clear(instances_maybe_trash);
    cvector_clear(mola_functions_maybe_trash);
    cvector_clear(c_functions_maybe_trash);

    size_t recycled = 0;
    /*printf("=================== %zu\n", cvector_size(arrays_trash));
    for (int i = 0; i < cvector_size(objects_trash); i++) {
        printf("%p\n", objects_trash[i]);
        fflush(stdout);
    }*/
    while (recycled < bytes) {
        if (!cvector_empty(objects_trash)) {
            Object *obj = *cvector_back(objects_trash);
            if (map_get(&objects_tracked, *cvector_back(objects_trash)) == NULL) {
                cvector_pop_back(objects_trash);
                continue;
            }
            size_t before = getAllocatedBytes();         // !
            objectDestroy(*cvector_back(objects_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(objects_trash);
            continue;
        }
        else if (!cvector_empty(instances_trash)) {
            if (map_get(&instances_tracked, *cvector_back(instances_trash)) == NULL) {
                cvector_pop_back(instances_trash);
                continue;
            }
            size_t before = getAllocatedBytes();         // !
            instanceValueDestroy(*cvector_back(instances_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(instances_trash);
            continue;
        }
        else if (!cvector_empty(strings_trash)) {
            if (map_get(&strings_tracked, *cvector_back(strings_trash)) == NULL) {
                cvector_pop_back(strings_trash);
                continue;
            }
            size_t before = getAllocatedBytes();         // !
            stringValueDestroy(*cvector_back(strings_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(strings_trash);
            continue;
        }
        else if (!cvector_empty(arrays_trash)) {
            if (map_get(&arrays_tracked, *cvector_back(arrays_trash)) == NULL) {
                cvector_pop_back(arrays_trash);
                continue;
            }
            size_t before = getAllocatedBytes();         // !
            arrayValueDestroy(*cvector_back(arrays_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(arrays_trash);
            continue;
        }
        else if (!cvector_empty(types_trash)) {
            if (map_get(&types_tracked, *cvector_back(types_trash)) == NULL) {
                cvector_pop_back(types_trash);
                continue;
            }
            size_t before = getAllocatedBytes();         // !
            typeValueDestroy(*cvector_back(types_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(types_trash);
            continue;
        }
        else if (!cvector_empty(mola_functions_trash)) {
            if (map_get(&mola_functions_tracked, *cvector_back(mola_functions_trash)) == NULL) {
                cvector_pop_back(mola_functions_trash);
                continue;
            }
            size_t before = getAllocatedBytes();         // !
            molaFunctionValueDestroy(*cvector_back(mola_functions_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(mola_functions_trash);
            continue;
        }
        else if (!cvector_empty(c_functions_trash)) {
            if (map_get(&c_functions_tracked, *cvector_back(c_functions_trash)) == NULL) {
                cvector_pop_back(c_functions_trash);
                continue;
            }
            size_t before = getAllocatedBytes();         // !
            cFunctionValueDestroy(*cvector_back(c_functions_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(c_functions_trash);
            continue;
        }
        else {
            break;
        }
    }
    /*printf("list:\n");
    for (int i = 0; i < cvector_size(objects_trash); i++) {
        printf("%p\n", objects_trash[i]);
        fflush(stdout);
    }
    printf("end:\n");*/
    if (0 && recycled != 0) {
        molalog("Recycled %zu / %zu bytes (%d%%)\n", recycled, bytes, (recycled * 100 / bytes));
    }
}

/*

if an object has this gc_mark, it hasn't been visited yet

*/
uint   gc_mark                     = 0;
size_t instructions_since_gc_cycle = 0;

static void dfsObject(Object *unit);
static void dfsStringValue(StringValue *unit);
static void dfsArrayValue(ArrayValue *unit);
static void dfsTypeValue(TypeValue *unit);
static void dfsInstanceValue(InstanceValue *unit);
static void dfsMolaFunctionValue(MolaFunctionValue *unit);
static void dfsCFunctionValue(CFunctionValue *unit);

static void dfsObject(Object *unit) {
    eassert(unit != NULL);
    if (unit->gc_mark != gc_mark) {
        return;
    }
    if (unit->is_gc_protected) {
        return;
    }
    unit->gc_mark = 1 - gc_mark;

    switch (unit->type) {
    case NULL_TYPE : break;
    case BOOL_TYPE : break;
    case INT_TYPE : break;
    case CHAR_TYPE : break;
    case FLOAT_TYPE : break;
    case STRING_TYPE : dfsStringValue(unit->value); break;
    case ARRAY_TYPE : dfsArrayValue(unit->value); break;
    case TYPE_TYPE : dfsTypeValue(unit->value); break;
    case INSTANCE_TYPE : dfsInstanceValue(unit->value); break;
    case MOLA_FUNCTION_TYPE : dfsMolaFunctionValue(unit->value); break;
    case C_FUNCTION_TYPE : dfsCFunctionValue(unit->value); break;
    case MODULE_TYPE : {
        Env *env = unit->value;
        identMapApply(&env->globals, dfsObject);
        identMapApply(&env->exported_objects, dfsObject);
        break;
    }
    case RETURN_ADDRESS_TYPE : break;
    }
}

static void dfsStringValue(StringValue *unit) {
    eassert(unit != NULL);
    if (unit->gc_mark != gc_mark) {
        return;
    }
    if (unit->is_gc_protected) {
        return;
    }
    unit->gc_mark = 1 - gc_mark;
}

static void dfsArrayValue(ArrayValue *unit) {
    eassert(unit != NULL);
    if (unit->gc_mark != gc_mark) {
        return;
    }
    if (unit->is_gc_protected) {
        return;
    }
    unit->gc_mark = 1 - gc_mark;

    for (size_t i = 0; i < cvector_size(unit->data); i++) {
        dfsObject(unit->data[i]);
    }
}

static void dfsTypeValue(TypeValue *unit) {
    eassert(unit != NULL);
    if (unit->gc_mark != gc_mark) {
        return;
    }
    if (unit->is_gc_protected) {
        return;
    }
    unit->gc_mark = 1 - gc_mark;

    identMapApply(&unit->methods, dfsObject);
}

static void dfsInstanceValue(InstanceValue *unit) {
    eassert(unit != NULL);
    if (unit->gc_mark != gc_mark) {
        return;
    }
    if (unit->is_gc_protected) {
        return;
    }
    unit->gc_mark = 1 - gc_mark;

    identMapApply(&unit->fields, dfsObject);
    dfsTypeValue(unit->type);
}

static void dfsMolaFunctionValue(MolaFunctionValue *unit) {
    eassert(unit != NULL);
    if (unit->gc_mark != gc_mark) {
        return;
    }
    if (unit->is_gc_protected) {
        return;
    }
    unit->gc_mark = 1 - gc_mark;

    identMapApply(&unit->env->globals, dfsObject);
    identMapApply(&unit->env->exported_objects, dfsObject);
}

static void dfsCFunctionValue(CFunctionValue *unit) {
    eassert(unit != NULL);
    if (unit->gc_mark != gc_mark) {
        return;
    }
    if (unit->is_gc_protected) {
        return;
    }
    unit->gc_mark = 1 - gc_mark;

    identMapApply(&unit->env->globals, dfsObject);
    identMapApply(&unit->env->exported_objects, dfsObject);
}

// roots
extern cvector_vector_type(Object *) objects_stack;
extern cvector_vector_type(ReferencedObject) referenced_stack;
extern Scope *current_scope;
extern cvector_vector_type(Env *) imported_modules;
extern Object *caller;

void gcRunCycle() {
    /*
    after object A is destroyed, object B might get the same address as A
    so after B gets out of scope entirely, it will become trash
    -- now there are 2 similar addresses in trash, error
    */
    gcRecycle(ALLOCATION_LIMIT);

    cvector_vector_type(Object *) objects_to_be_destroyed                   = NULL;
    cvector_vector_type(StringValue *) strings_to_be_destroyed              = NULL;
    cvector_vector_type(ArrayValue *) arrays_to_be_destroyed                = NULL;
    cvector_vector_type(TypeValue *) types_to_be_destroyed                  = NULL;
    cvector_vector_type(InstanceValue *) instances_to_be_destroyed          = NULL;
    cvector_vector_type(MolaFunctionValue *) mola_functions_to_be_destroyed = NULL;
    cvector_vector_type(CFunctionValue *) c_functions_to_be_destroyed       = NULL;

    // dfs

    for (size_t i = 0; i < cvector_size(objects_stack); i++) {
        dfsObject(objects_stack[i]);
    }

    for (size_t i = 0; i < cvector_size(referenced_stack); i++) {
        dfsObject(referenced_stack[i].obj);
    }

    {
        Scope *scope = current_scope;
        while (scope != NULL) {
            identMapApply(&scope->map, dfsObject);
            scope = scope->parent;
        }
    }

    for (size_t i = 0; i < cvector_size(imported_modules); i++) {
        identMapApply(&imported_modules[i]->globals, dfsObject);
        identMapApply(&imported_modules[i]->exported_objects, dfsObject);
    }

    if (caller != NULL) {
        dfsObject(caller);
    }

    // now we can destroy unvisited objects

    {
        Object    *key;
        map_iter_t iter = map_iter(&objects_tracked);

        while (map_next(&objects_tracked, &iter, &key)) {
            if (key->is_gc_protected) {
                continue;
            }

            if (key->gc_mark == gc_mark) {
                cvector_push_back(objects_to_be_destroyed, key);
            }
        }
    }

    {
        StringValue *key;
        map_iter_t   iter = map_iter(&strings_tracked);

        while (map_next(&strings_tracked, &iter, &key)) {
            if (key->is_gc_protected) {
                continue;
            }

            if (key->gc_mark == gc_mark) {
                cvector_push_back(strings_to_be_destroyed, key);
            }
        }
    }

    {
        ArrayValue *key;
        map_iter_t  iter = map_iter(&arrays_tracked);

        while (map_next(&arrays_tracked, &iter, &key)) {
            if (key->is_gc_protected) {
                continue;
            }

            if (key->gc_mark == gc_mark) {
                cvector_push_back(arrays_to_be_destroyed, key);
            }
        }
    }

    {
        TypeValue *key;
        map_iter_t iter = map_iter(&types_tracked);

        while (map_next(&types_tracked, &iter, &key)) {
            if (key->is_gc_protected) {
                continue;
            }

            if (key->gc_mark == gc_mark) {
                cvector_push_back(types_to_be_destroyed, key);
            }
        }
    }

    {
        InstanceValue *key;
        map_iter_t     iter = map_iter(&instances_tracked);

        while (map_next(&instances_tracked, &iter, &key)) {
            if (key->is_gc_protected) {
                continue;
            }

            if (key->gc_mark == gc_mark) {
                cvector_push_back(instances_to_be_destroyed, key);
            }
        }
    }

    {
        MolaFunctionValue *key;
        map_iter_t         iter = map_iter(&mola_functions_tracked);

        while (map_next(&mola_functions_tracked, &iter, &key)) {
            if (key->is_gc_protected) {
                continue;
            }

            if (key->gc_mark == gc_mark) {
                cvector_push_back(mola_functions_to_be_destroyed, key);
            }
        }
    }

    {
        CFunctionValue *key;
        map_iter_t      iter = map_iter(&c_functions_tracked);

        while (map_next(&c_functions_tracked, &iter, &key)) {
            if (key->is_gc_protected) {
                continue;
            }

            if (key->gc_mark == gc_mark) {
                cvector_push_back(c_functions_to_be_destroyed, key);
            }
        }
    }

    // now we actually destroy them. i need to learn some english

    for (size_t i = 0; i < cvector_size(objects_to_be_destroyed); i++) {
        objectGCOnlyUnref(objects_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(strings_to_be_destroyed); i++) {
        stringValueGCOnlyUnref(strings_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(arrays_to_be_destroyed); i++) {
        arrayValueGCOnlyUnref(arrays_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(types_to_be_destroyed); i++) {
        typeValueGCOnlyUnref(types_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(instances_to_be_destroyed); i++) {
        instanceValueGCOnlyUnref(instances_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(mola_functions_to_be_destroyed); i++) {
        molaFunctionValueGCOnlyUnref(mola_functions_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(c_functions_to_be_destroyed); i++) {
        cFunctionValueGCOnlyUnref(c_functions_to_be_destroyed[i]);
    }

    // destroy this shit

    for (size_t i = 0; i < cvector_size(objects_to_be_destroyed); i++) {
        objectGCDestroy(objects_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(strings_to_be_destroyed); i++) {
        stringValueGCDestroy(strings_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(arrays_to_be_destroyed); i++) {
        arrayValueGCDestroy(arrays_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(types_to_be_destroyed); i++) {
        typeValueGCDestroy(types_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(instances_to_be_destroyed); i++) {
        instanceValueGCDestroy(instances_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(mola_functions_to_be_destroyed); i++) {
        molaFunctionValueGCDestroy(mola_functions_to_be_destroyed[i]);
    }

    for (size_t i = 0; i < cvector_size(c_functions_to_be_destroyed); i++) {
        cFunctionValueGCDestroy(c_functions_to_be_destroyed[i]);
    }

    cvector_free(objects_to_be_destroyed);
    cvector_free(strings_to_be_destroyed);
    cvector_free(arrays_to_be_destroyed);
    cvector_free(types_to_be_destroyed);
    cvector_free(instances_to_be_destroyed);
    cvector_free(mola_functions_to_be_destroyed);
    cvector_free(c_functions_to_be_destroyed);

    gc_mark = 1 - gc_mark;
}
