#include "gc.h"
#include "alloc.h"
#include "object.h"

cvector_vector_type(Object *) objects_trash;
cvector_vector_type(StringValue *) strings_trash;
cvector_vector_type(StringValue *) strings_trash;
cvector_vector_type(ArrayValue *) arrays_trash;
cvector_vector_type(TypeValue *) types_trash;
cvector_vector_type(InstanceValue *) instances_trash;
cvector_vector_type(MolaFunctionValue *) mola_functions_trash;
cvector_vector_type(CFunctionValue *) c_functions_trash;

cvector_vector_type(Object *) objects_maybe_trash;
cvector_vector_type(StringValue *) strings_maybe_trash;
cvector_vector_type(StringValue *) strings_maybe_trash;
cvector_vector_type(ArrayValue *) arrays_maybe_trash;
cvector_vector_type(TypeValue *) types_maybe_trash;
cvector_vector_type(InstanceValue *) instances_maybe_trash;
cvector_vector_type(MolaFunctionValue *) mola_functions_maybe_trash;
cvector_vector_type(CFunctionValue *) c_functions_maybe_trash;

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

cvector_vector_type(Object *) objects_tracked;
cvector_vector_type(StringValue *) strings_tracked;
cvector_vector_type(StringValue *) strings_tracked;
cvector_vector_type(ArrayValue *) arrays_tracked;
cvector_vector_type(TypeValue *) types_tracked;
cvector_vector_type(InstanceValue *) instances_tracked;
cvector_vector_type(MolaFunctionValue *) mola_functions_tracked;
cvector_vector_type(CFunctionValue *) c_functions_tracked;

void gcTrackObject(struct Object *unit) {
    //cvector_push_back(objects_tracked, unit);
}

void gcTrackStringValue(struct StringValue *unit) {
    //cvector_push_back(strings_tracked, unit);
}

void gcTrackArrayValue(struct ArrayValue *unit) {
    //cvector_push_back(arrays_tracked, unit);
}

void gcTrackTypeValue(struct TypeValue *unit) {
    //cvector_push_back(types_tracked, unit);
}

void gcTrackInstanceValue(struct InstanceValue *unit) {
    //cvector_push_back(instances_tracked, unit);
}

void gcTrackMolaFunctionValue(struct MolaFunctionValue *unit) {
    //cvector_push_back(mola_functions_tracked, unit);
}

void gcTrackCFunctionValue(struct CFunctionValue *unit) {
    //cvector_push_back(c_functions_tracked, unit);
}

void gcInit(struct VM *vm) {}

// warning!: this code relies on ...Destroy not allocating any new memory
void gcRecycle(size_t bytes) {
    for (size_t i = 0; i < cvector_size(objects_maybe_trash); i++) {
        if (objects_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(objects_trash, objects_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(instances_maybe_trash); i++) {
        if (instances_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(instances_trash, instances_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(strings_maybe_trash); i++) {
        if (strings_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(strings_trash, strings_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(arrays_maybe_trash); i++) {
        if (arrays_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(arrays_trash, arrays_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(types_maybe_trash); i++) {
        if (types_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(types_trash, types_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(mola_functions_maybe_trash); i++) {
        if (mola_functions_maybe_trash[i]->ref_count == 0) {
            cvector_push_back(mola_functions_trash, mola_functions_maybe_trash[i]);
        }
    }
    for (size_t i = 0; i < cvector_size(c_functions_maybe_trash); i++) {
        if (c_functions_maybe_trash[i]->ref_count == 0) {
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
    printf("===================\n");
     for (int i = 0; i < cvector_size(objects_trash); i++) {
         printf("%p\n", objects_trash[i]);
         fflush(stdout);
     }
    while (recycled < bytes + 1000) {
        if (!cvector_empty(objects_trash)) {
            size_t before = getAllocatedBytes();         // !
            objectDestroy(*cvector_back(objects_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(objects_trash);
            continue;
        }
        else if (!cvector_empty(instances_trash)) {
            size_t before = getAllocatedBytes();         // !
            instanceValueDestroy(*cvector_back(instances_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(instances_trash);
            continue;
        }
        else if (!cvector_empty(strings_trash)) {
            size_t before = getAllocatedBytes();         // !
            stringValueDestroy(*cvector_back(strings_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(strings_trash);
            continue;
        }
        else if (!cvector_empty(arrays_trash)) {
            size_t before = getAllocatedBytes();         // !
            arrayValueDestroy(*cvector_back(arrays_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(arrays_trash);
            continue;
        }
        else if (!cvector_empty(types_trash)) {
            size_t before = getAllocatedBytes();         // !
            typeValueDestroy(*cvector_back(types_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(types_trash);
            continue;
        }
        else if (!cvector_empty(mola_functions_trash)) {
            size_t before = getAllocatedBytes();         // !
            molaFunctionValueDestroy(*cvector_back(mola_functions_trash));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(mola_functions_trash);
            continue;
        }
        else if (!cvector_empty(c_functions_trash)) {
            size_t before = getAllocatedBytes();         // !
            cFunctionValueDestroy(*cvector_back(c_functions_tracked));
            recycled += before - getAllocatedBytes();    // !

            cvector_pop_back(c_functions_tracked);
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
    if (recycled != 0) {
        //molalog("Recycled %zu / %zu bytes (%d%%)\n", recycled, bytes, (recycled * 100 / bytes));
    }
}

void gcRunCycle(struct VM *vm) {}
