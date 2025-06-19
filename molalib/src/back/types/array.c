#include "../api.h"

/*
size()
resize(n)
append(x)
prepend(x)
poplast()
popfirst()
first()
last()
empty()
clear()
copy()
filter(f)
apply(f)
reverse()
sort(f)
findfirstf(f)
findlastf(f)
locatefirstf(f)
locatelastf(f)
findfirst(x)
findlast(x)
locatefirst(x)
locatelast(x)
all(f)
any(f)
none(f)
countf()
count()
slice(index, count)

*/

ArrayValue *arrayValueCreate() {
    stat_created_arrays++;
    ArrayValue *arr = allocOrError(sizeof(ArrayValue));
    arr->data       = NULL;    // todo, make this allocate using allocOrError

    arr->gc_mark         = gc_mark;
    arr->ref_count       = 0;
    arr->is_gc_protected = 0;

    gcTrackArrayValue(arr);

    return arr;
}

ArrayValue *arrayValueCopy(ArrayValue *val) {
    return val;
}

void arrayValueDestroy(ArrayValue *val) {
    stat_created_arrays--;
    for (size_t i = 0; i < cvector_size(val->data); i++) {
        unref(val->data[i]);
    }
    cvector_free(val->data);
    freeBytes(val);
    gcUntrackArrayValue(val);
}

void arrayValueGCOnlyUnref(ArrayValue *val) {
    for (size_t i = 0; i < cvector_size(val->data); i++) {
        unref(val->data[i]);
    }
}

void arrayValueGCDestroy(ArrayValue *val) {
    stat_created_arrays--;
    cvector_free(val->data);
    freeBytes(val);
    gcUntrackArrayValue(val);
}

struct Object *arrayValueIndexAccess(ArrayValue *val, int64_t index) {
    if (!(0 <= index && index < cvector_size(val->data))) {
        signalError(OUT_OF_BOUNDS_ERROR_CODE, "Index out of bounds");
    }

    return val->data[index];
}

ident          ARRAY_METHOD_CONSTRUCTOR_IDENT;
struct Object *ARRAY_METHOD_CONSTRUCTOR_OBJECT;
ident          ARRAY_METHOD_RESIZE_IDENT;
struct Object *ARRAY_METHOD_RESIZE_OBJECT;

struct Object *arrayValueLookupMethod(ArrayValue *val, ident name) {
    if (name == ARRAY_METHOD_CONSTRUCTOR_IDENT) {
        return ARRAY_METHOD_CONSTRUCTOR_OBJECT;
    }
    if (name == ARRAY_METHOD_RESIZE_IDENT) {
        return ARRAY_METHOD_RESIZE_OBJECT;    // it can be overwritten, fix later
    }

    signalError(NAME_COLLISION_ERROR_CODE, errstrfmt("Failed to locate method '%s'", symtabIdentToString(name)));
}

void arrayValueRef(ArrayValue *unit) {
    unit->ref_count++;
}

void arrayValueUnref(ArrayValue *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageArrayValue(unit);
    }
}

// methods -=============

Object *arrayResizeMethod(size_t n_args, struct Object **args) {
    // TODO: add unreferencing when resizing to smaller size
    if (n_args != 2) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, errstrfmt("Expected one argument, got %d", n_args - 1));
    }

    Object *obj = args[0];
    eassert(obj->type == ARRAY_TYPE);
    ArrayValue *array = obj->value;

    Object *size = args[1];

    if (size->type >= FLOAT_TYPE) {
        signalError(VALUE_ERROR_CODE, "Unsupported operation");
    }

    int64_t x_int;
    switch (size->type) {
    case NULL_TYPE : {
        x_int = (int64_t)0;
        break;
    }
    case BOOL_TYPE : {
        x_int = (int64_t)size->bool_value;
        break;
    }
    case CHAR_TYPE : {
        x_int = (int64_t)size->char_value;
        break;
    }
    case INT_TYPE : {
        x_int = (int64_t)size->int_value;
        break;
    }
    }

    if (size < 0) {
        signalError(VALUE_ERROR_CODE, "Cannot resize to negative size");
    }

    cvector_resize(array->data, x_int, NULL);
    for (size_t i = 0; i < x_int; i++) {
        if (array->data[i] == NULL) {
            array->data[i] = objectCreate(NULL_TYPE, 0);
            ref(array->data[i]);
        }
    }

    return obj;
}

Object *arrayConstructorMethod(size_t n_args, struct Object **args) {
    if (n_args == 1) {
        return args[0];
    }
    if (n_args != 2) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, errstrfmt("Expected zero or one arguments, got %d", n_args - 1));
    }

    Object *obj = args[0];
    eassert(obj->type == ARRAY_TYPE);
    ArrayValue *array = obj->value;

    Object *size = args[1];

    if (size->type >= FLOAT_TYPE) {
        signalError(VALUE_ERROR_CODE, "Unsupported operation");
    }

    int64_t x_int;
    switch (size->type) {
    case NULL_TYPE : {
        x_int = (int64_t)0;
        break;
    }
    case BOOL_TYPE : {
        x_int = (int64_t)size->bool_value;
        break;
    }
    case CHAR_TYPE : {
        x_int = (int64_t)size->char_value;
        break;
    }
    case INT_TYPE : {
        x_int = (int64_t)size->int_value;
        break;
    }
    }

    if (size < 0) {
        signalError(VALUE_ERROR_CODE, "Cannot resize to negative size");
    }

    cvector_resize(array->data, x_int, NULL);
    for (size_t i = 0; i < x_int; i++) {
        if (array->data[i] == NULL) {
            array->data[i] = objectCreate(NULL_TYPE, 0);
            ref(array->data[i]);
        }
    }

    return obj;
}

void init_array() {
    CFunctionValue *method;
    {
        ARRAY_METHOD_RESIZE_IDENT                   = symtabInsert(lex_symtab, "resize");
        method                                      = cFunctionValueCreate(0, 2, arrayResizeMethod);
        method->is_method                           = 1;
        method->is_gc_protected                     = 1;
        ARRAY_METHOD_RESIZE_OBJECT                  = objectCreate(C_FUNCTION_TYPE, raw64(method));
        ARRAY_METHOD_RESIZE_OBJECT->is_gc_protected = 1;
        cFunctionValueRef(method);
        ref(ARRAY_METHOD_RESIZE_OBJECT);
    }

    {
        ARRAY_METHOD_CONSTRUCTOR_IDENT                   = symtabInsert(lex_symtab, "constructor");
        method                                           = cFunctionValueCreate(0, UNLIMITED_ARGS, arrayConstructorMethod);
        method->is_gc_protected                          = 1;
        method->is_method                                = 1;
        ARRAY_METHOD_CONSTRUCTOR_OBJECT                  = objectCreate(C_FUNCTION_TYPE, raw64(method));
        ARRAY_METHOD_CONSTRUCTOR_OBJECT->is_gc_protected = 1;
        cFunctionValueRef(method);
        ref(ARRAY_METHOD_CONSTRUCTOR_OBJECT);
    }
}
