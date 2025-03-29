#include "object.h"
#include "alloc.h"
#include "gc.h"
#include "types.h"

Object *objectCreate(enum Type type, void *value) {
    Object *obj = memallocObject();
    obj->type   = type;
    obj->value  = value;
    switch (type) {
    case BOOL_TYPE : boolValueRef(value); break;
    case INT_TYPE : intValueRef(value); break;
    case CHAR_TYPE : charValueRef(value); break;
    case FLOAT_TYPE : floatValueRef(value); break;
    case STRING_TYPE : stringValueRef(value); break;
    case ARRAY_TYPE : arrayValueRef(value); break;
    case TYPE_TYPE : typeValueRef(value); break;
    case INSTANCE_TYPE : instanceValueRef(value); break;
    case MOLA_FUNCTION_TYPE : molaFunctionValueRef(value); break;
    case C_FUNCTION_TYPE : cFunctionValueRef(value); break;
    case MODULE_TYPE : moduleValueRef(value); break;
    case NULL_TYPE : nullValueRef(value); break;
    case RETURN_ADDRESS_TYPE : break;    // no need
    }

    obj->ref_count = 0;
    obj->gc_mark   = 0;
    obj->is_rvalue = 0;

    gcTrackObject(obj);

    return obj;
}

void objectDestroy(Object *obj) {
    switch (obj->type) {
    case BOOL_TYPE : boolValueUnref(obj->value); break;
    case INT_TYPE : intValueUnref(obj->value); break;
    case CHAR_TYPE : charValueUnref(obj->value); break;
    case FLOAT_TYPE : floatValueUnref(obj->value); break;
    case STRING_TYPE : stringValueUnref(obj->value); break;
    case ARRAY_TYPE : arrayValueUnref(obj->value); break;
    case TYPE_TYPE : typeValueUnref(obj->value); break;
    case INSTANCE_TYPE : instanceValueUnref(obj->value); break;
    case MOLA_FUNCTION_TYPE : molaFunctionValueUnref(obj->value); break;
    case C_FUNCTION_TYPE : cFunctionValueUnref(obj->value); break;
    case MODULE_TYPE : moduleValueUnref(obj->value); break;
    case NULL_TYPE : nullValueUnref(obj->value); break;
    case RETURN_ADDRESS_TYPE : break;    // no need
    }

    memfreeObject(obj);
}

void ref(Object *unit) {
    unit->ref_count++;
}

void unref(Object *unit) {
    if (--unit->ref_count == 0) {
        // what if unit is not garbage?
        gcDeclareGarbageObject(unit);
    }
}
