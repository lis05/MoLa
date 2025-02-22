#ifndef __mola_types_h__
#define __mola_types_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cmap.h"

enum Type {
    NONE_TYPE,
    BOOL_TYPE,
    INT_TYPE,
    CHAR_TYPE,
    FLOAT_TYPE,
    STRING_TYPE,
    ARRAY_TYPE,
    TYPE_TYPE,
    INSTANCE_TYPE,
    MOLA_FUNCTION_TYPE,
    C_FUNCTION_TYPE,
    MODULE_TYPE
};

struct ModuleValue;
struct MolaFunctionValue;

struct Object;
struct Env;

// NoneValue is redundant

typedef struct BoolValue {
    int value : 1;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} BoolValue;

BoolValue *boolValueCreate(int value);
BoolValue *boolValueCopyByAuto(BoolValue *val);
void       boolValueDestroy(BoolValue *val);
void       boolValueRef(BoolValue *unit);
void       boolValueUnref(BoolValue *unit);

typedef struct IntValue {
    int64_t value;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} IntValue;

IntValue *intValueCreate(int64_t value);
IntValue *intValueCopyByAuto(IntValue *val);
void      intValueDestroy(IntValue *val);
void      intValueRef(IntValue *unit);
void      intValueUnref(IntValue *unit);

typedef struct CharValue {
    char value;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} CharValue;

CharValue *charValueCreate(char value);
CharValue *charValueCopyByAuto(CharValue *val);
void       charValueDestroy(CharValue *val);
void       charValueRef(CharValue *unit);
void       charValueUnref(CharValue *unit);

typedef struct FloatValue {
    double value;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} FloatValue;

FloatValue *floatValueCreate(double value);
FloatValue *floatValueCopyByAuto(FloatValue *val);
void        floatValueDestroy(FloatValue *val);
void        floatValueRef(FloatValue *unit);
void        floatValueUnref(FloatValue *unit);

typedef struct StringValue {
    size_t length;
    char  *string;    // NULL-terminated, '\0' is not counted in length

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} StringValue;

StringValue   *stringValueCreate(size_t length, char *string);
StringValue   *stringValueCopyByAuto(StringValue *val);
void           stringValueDestroy(StringValue *val);
char           stringValueIndexAccess(StringValue *val, int64_t index);
struct Object *stringValueLookupField(StringValue *val, ident name);
struct Object *stringValueLookupMethod(StringValue *val, ident name);
void           stringValueRef(StringValue *unit);
void           stringValueUnref(StringValue *unit);

typedef struct ArrayValue {
    size_t          length;
    struct Object **array;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} ArrayValue;

ArrayValue    *arrayValueCreate(char *string);
ArrayValue    *arrayValueCopyByAuto(ArrayValue *val);
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
TypeValue     *typeValueCopyByAuto(TypeValue *val);
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
InstanceValue *instanceValueCopyByAuto(InstanceValue *val);
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
    struct ModuleValue *module;
    int64_t             relative_offset;    // offset (relative to the module) of the first function instruction

    size_t  n_args;
    ident  *args;
    int8_t *modes;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} MolaFunctionValue;

MolaFunctionValue *molaFunctionValueCreate(struct ModuleValue *module, int64_t rel_offset, size_t n_args, ident *args, int8_t *modes);
MolaFunctionValue *molaFunctionValueCopyByAuto(MolaFunctionValue *val);
void               molaFunctionValueDestroy(MolaFunctionValue *val);
void               molaFunctionValueRef(MolaFunctionValue *unit);
void               molaFunctionValueUnref(MolaFunctionValue *unit);

typedef struct Object *(*CFunction)(size_t n_args, struct Object **args);

typedef struct CFunctionValue {
    size_t  n_args;
    int8_t *modes;

    CFunction function;

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} CFunctionValue;

CFunctionValue *cFunctionValueCreate(size_t n_args, int8_t *modes, CFunction function);
CFunctionValue *cFunctionValueCopyByAuto(CFunctionValue *val);
void            cFunctionValueDestroy(CFunctionValue *val);
void            cFunctionValueRef(CFunctionValue *unit);
void            cFunctionValueUnref(CFunctionValue *unit);

typedef struct ModuleValue {
    struct Env *env;
    int64_t     absolute_offset;    // offset of the first instruction

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} ModuleValue;

ModuleValue *moduleValueCreate(struct Env *env, int64_t absolute_offset);
ModuleValue *moduleValueCopyByAuto(ModuleValue *val);
void         moduleValueDestroy(ModuleValue *val);
void         moduleValueRef(ModuleValue *unit);
void         moduleValueUnref(ModuleValue *unit);

#endif
