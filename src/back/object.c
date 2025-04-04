#include "object.h"
#include "alloc.h"
#include "gc.h"
#include "types.h"

Object *objectCreate(enum Type type, uint64_t value) {
    Object *obj = memallocObject();

    obj->type  = type;
    obj->value = (void *)value;

    switch (type) {
    case BOOL_TYPE : obj->bool_value = (int)value; break;
    case INT_TYPE : obj->int_value = (int64_t)value; break;
    case CHAR_TYPE : obj->char_value = (char)value; break;
    case FLOAT_TYPE : obj->float_value = (double)value; break;
    case STRING_TYPE : stringValueRef((void *)value); break;
    case ARRAY_TYPE : arrayValueRef((void *)value); break;
    case TYPE_TYPE : typeValueRef((void *)value); break;
    case INSTANCE_TYPE : instanceValueRef((void *)value); break;
    case MOLA_FUNCTION_TYPE : molaFunctionValueRef((void *)value); break;
    case C_FUNCTION_TYPE : cFunctionValueRef((void *)value); break;
    case MODULE_TYPE : obj->value = (void *)value; break;
    case NULL_TYPE : obj->return_address = (int64_t)value;
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
    case BOOL_TYPE : break;
    case INT_TYPE : break;
    case CHAR_TYPE : break;
    case FLOAT_TYPE : break;
    case STRING_TYPE : stringValueUnref(obj->value); break;
    case ARRAY_TYPE : arrayValueUnref(obj->value); break;
    case TYPE_TYPE : typeValueUnref(obj->value); break;
    case INSTANCE_TYPE : instanceValueUnref(obj->value); break;
    case MOLA_FUNCTION_TYPE : molaFunctionValueUnref(obj->value); break;
    case C_FUNCTION_TYPE : cFunctionValueUnref(obj->value); break;
    case MODULE_TYPE : break;
    case NULL_TYPE : break;
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
