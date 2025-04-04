#ifndef __mola_types_h__
#define __mola_types_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cmap.h"

// order is important for type promotion!
enum Type {
    NULL_TYPE   = 0,
    BOOL_TYPE   = 1,
    CHAR_TYPE   = 2,
    INT_TYPE    = 3,
    FLOAT_TYPE  = 4,
    STRING_TYPE = 5,
    ARRAY_TYPE,
    TYPE_TYPE,
    INSTANCE_TYPE,
    MOLA_FUNCTION_TYPE,
    C_FUNCTION_TYPE,
    MODULE_TYPE,
    RETURN_ADDRESS_TYPE
};

struct ModuleValue;
struct MolaFunctionValue;

struct Object;
struct Env;

typedef struct StringValue {
    size_t length;
    char  *string;    // NULL terminated, length doesnt count the NULL character

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} StringValue;

StringValue   *stringValueCreate(size_t length, char *string);
StringValue   *stringValueCopy(StringValue *val);
void           stringValueDestroy(StringValue *val);
char           stringValueIndexAccess(StringValue *val, int64_t index);
struct Object *stringValueLookupField(StringValue *val, ident name);
struct Object *stringValueLookupMethod(StringValue *val, ident name);
int            stringCompare(StringValue *first, StringValue *second);    // like strcmp
void           stringValueRef(StringValue *unit);
void           stringValueUnref(StringValue *unit);

typedef struct ArrayValue {
    size_t          length;
    struct Object **array;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} ArrayValue;

ArrayValue    *arrayValueCreate(char *string);
ArrayValue    *arrayValueCopy(ArrayValue *val);
void           arrayValueDestroy(ArrayValue *val);
struct Object *arrayValueIndexAccess(ArrayValue *val, int64_t index);
struct Object *arrayValueLookupField(ArrayValue *val, ident name);
struct Object *arrayValueLookupMethod(ArrayValue *val, ident name);
void           arrayValueRef(ArrayValue *unit);
void           arrayValueUnref(ArrayValue *unit);

typedef struct TypeValue {
    size_t n_fields;
    ident *fields;
    map_t(ident, struct MolaFunctionValue *) methods;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} TypeValue;

TypeValue     *typeValueCreate();
TypeValue     *typeValueCopy(TypeValue *val);
void           typeValueDestroy(TypeValue *val);
void           typeValueAddMethod(TypeValue *val, ident name, struct MolaFunctionValue *method);
struct Object *typeValueLookupMethod(TypeValue *val, ident name);
void           typeValueRef(TypeValue *unit);
void           typeValueUnref(TypeValue *unit);

typedef struct InstanceValue {
    struct TypeValue *type;
    map_t(ident, struct Object *) fields;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} InstanceValue;

InstanceValue *instanceValueCreate(struct TypeValue *type);
InstanceValue *instanceValueCopy(InstanceValue *val);
void           instanceValueDestroy(InstanceValue *val);
struct Object *instanceValueLookupField(InstanceValue *val, ident name);
struct Object *instanceValueLookupMethod(InstanceValue *val, ident name);
void           instanceValueRef(InstanceValue *unit);
void           instanceValueUnref(InstanceValue *unit);

#define FUNCTION_ARG_MODE_COPY 0
#define FUNCTION_ARG_MODE_REF  1
#define FUNCTION_ARG_MODE_PASS 2
#define FUNCTION_ARG_MODE_AUTO 3

typedef struct MolaFunctionValue {
    struct Env *env;
    int64_t     relative_offset;    // offset (relative to the module) of the first function instruction

    size_t n_args;
    ident *args;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} MolaFunctionValue;

MolaFunctionValue *molaFunctionValueCreate(struct Env *env, int64_t rel_offset, size_t n_args, ident *args);
MolaFunctionValue *molaFunctionValueCopy(MolaFunctionValue *val);
void               molaFunctionValueDestroy(MolaFunctionValue *val);
void               molaFunctionValueRef(MolaFunctionValue *unit);
void               molaFunctionValueUnref(MolaFunctionValue *unit);

typedef struct Object *(*CFunction)(size_t n_args, struct Object **args);

typedef struct CFunctionValue {
    struct Env *env;
    size_t      n_args;

    CFunction function;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} CFunctionValue;

CFunctionValue *cFunctionValueCreate(struct Env *env, size_t n_args, CFunction function);
CFunctionValue *cFunctionValueCopy(CFunctionValue *val);
void            cFunctionValueDestroy(CFunctionValue *val);
void            cFunctionValueRef(CFunctionValue *unit);
void            cFunctionValueUnref(CFunctionValue *unit);

#endif
