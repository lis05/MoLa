#include "types.h"
#include "../front/api.h"
#include "../util.h"
#include "alloc.h"
#include "error.h"
#include "gc.h"
#include "object.h"
#include "stat.h"

StringValue *stringValueCreate(size_t length, char *string) {
    stat_created_strings++;
    StringValue *res = allocOrError(sizeof(StringValue));
    res->length      = length;
    res->string      = allocOrError(sizeof(char) * length + 1);
    strcpy(res->string, string);

    res->gc_mark         = gc_mark;
    res->ref_count       = 0;
    res->is_gc_protected = 0;

    gcTrackStringValue(res);

    return res;
}

StringValue *stringValueCopy(StringValue *val) {
    return stringValueCreate(val->length, val->string);
}

void stringValueDestroy(StringValue *val) {
    stat_created_strings--;
    freeBytes(val->string);
    freeBytes(val);
    gcUntrackStringValue(val);
}

void stringValueGCOnlyUnref(StringValue *val) {}

void stringValueGCDestroy(StringValue *val) {
    stat_created_strings--;
    freeBytes(val->string);
    freeBytes(val);
    gcUntrackStringValue(val);
}

char stringValueIndexAccess(StringValue *val, int64_t index) {
    if (!(0 <= index && index < val->length)) {
        // what if I was called without a gc lock?
        signalError(OUT_OF_BOUNDS_ERROR_CODE, "Index out of bounds");
    }
    return val->string[index];
}

struct Object *stringValueLookupField(StringValue *val, ident name) {}

struct Object *stringValueLookupMethod(StringValue *val, ident name) {}

int stringCompare(StringValue *first, StringValue *second) {
    size_t m = (first->length < second->length) ? first->length : second->length;
    for (size_t i = 0; i < m; i++) {
        if (first->string[i] < second->string[i]) {
            return -1;
        }
        else if (first->string[i] > second->string[i]) {
            return 1;
        }
    }
    if (first->length < second->length) {
        return -1;
    }
    else if (first->length > second->length) {
        return 1;
    }
    return 0;
}

StringValue *stringConcat(StringValue *first, StringValue *second) {
    char *str = allocOrError(first->length + second->length + 1);
    memcpy(str, first->string, first->length);
    memcpy(str + first->length, second->string, second->length);
    str[first->length + second->length] = '\0';

    StringValue *res = stringValueCreate(first->length + second->length, str);
    freeBytes(str);
    return res;
}

void stringValueRef(StringValue *unit) {
    unit->ref_count++;
}

void stringValueUnref(StringValue *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageStringValue(unit);
    }
}

static int64_t cnt = 0;

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

void initTypes() {
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
