#pragma once

#include "../../front/api.h"
#include "../../util.h"

typedef struct ArrayValue {
    cvector_vector_type(struct Object *) data;

    uint32_t ref_count;
    uint32_t gc_mark         : 1;
    uint32_t is_gc_protected : 1;
} ArrayValue;

#define get_array(obj) ((ArrayValue *)((obj)->value))

ArrayValue    *arrayValueCreate();
ArrayValue    *arrayValueCopy(ArrayValue *val);
void           arrayValueDestroy(ArrayValue *val);
void           arrayValueGCOnlyUnref(ArrayValue *val);
void           arrayValueGCDestroy(ArrayValue *val);
struct Object *arrayValueIndexAccess(ArrayValue *val, int64_t index);
struct Object *arrayValueLookupMethod(ArrayValue *val, ident name);
void           arrayValueRef(ArrayValue *unit);
void           arrayValueUnref(ArrayValue *unit);

void init_array();
