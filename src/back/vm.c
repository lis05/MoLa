#include "vm.h"
#include "alloc.h"
#include "cmap.h"
#include "env.h"
#include "error.h"
#include "gc.h"
#include "gen.h"
#include "object.h"
#include "scope.h"
#include "types.h"

static void exec_POP(Instruction *instr);
static void exec_SWAP(Instruction *instr);
static void exec_CREATE_ENV(Instruction *instr);
static void exec_SWITCH_ENV_INS(Instruction *instr);
static void exec_SWITCH_ENV_OBJ(Instruction *instr);
static void exec_IMPORT_MODULE(Instruction *instr);
static void exec_EXPORT_OBJECT(Instruction *instr);
static void exec_CREATE_GLOBAL(Instruction *instr);
static void exec_CREATE_FUNCTION(Instruction *instr);
static void exec_CREATE_TYPE(Instruction *instr);
static void exec_CREATE_METHOD(Instruction *instr);
static void exec_CREATE_SCOPE(Instruction *instr);
static void exec_DESTROY_SCOPE(Instruction *instr);
static void exec_JUMP_IF_FALSE(Instruction *instr);
static void exec_JUMP(Instruction *instr);
static void exec_RETURN(Instruction *instr);
static void exec_REGISTER_CATCH(Instruction *instr);
static void exec_DESTROY_CATCH(Instruction *instr);
static void exec_SIGNAL_ERROR(Instruction *instr);
static void exec_CREATE_VAR(Instruction *instr);
static void exec_COPY_BY_VALUE(Instruction *instr);
static void exec_COPY_BY_REFERENCE(Instruction *instr);
static void exec_COPY_BY_AUTO(Instruction *instr);
static void exec_ASSIGNMENT(Instruction *instr);
static void exec_LOGICAL_OR(Instruction *instr);
static void exec_LOGICAL_AND(Instruction *instr);
static void exec_BITWISE_OR(Instruction *instr);
static void exec_BITWISE_XOR(Instruction *instr);
static void exec_BITWISE_AND(Instruction *instr);
static void exec_EQUAL(Instruction *instr);
static void exec_NOT_EQUAL(Instruction *instr);
static void exec_LESS_THAN(Instruction *instr);
static void exec_LESS_EQUAL(Instruction *instr);
static void exec_GREATER_THAN(Instruction *instr);
static void exec_GREATER_EQUAL(Instruction *instr);
static void exec_ADDITION(Instruction *instr);
static void exec_SUBTRACTION(Instruction *instr);
static void exec_LSHIFT(Instruction *instr);
static void exec_RSHIFT(Instruction *instr);
static void exec_MULTIPLICATION(Instruction *instr);
static void exec_DIVISION(Instruction *instr);
static void exec_REMAINDER(Instruction *instr);
static void exec_POSITIVE(Instruction *instr);
static void exec_NEGATION(Instruction *instr);
static void exec_INVERTION(Instruction *instr);
static void exec_LOGICAL_NOT(Instruction *instr);
static void exec_CALL(Instruction *instr);
static void exec_ACCESS(Instruction *instr);
static void exec_LOAD_BOOL(Instruction *instr);
static void exec_LOAD_CHAR(Instruction *instr);
static void exec_LOAD_INT(Instruction *instr);
static void exec_LOAD_FLOAT(Instruction *instr);
static void exec_LOAD_STRING(Instruction *instr);
static void exec_LOAD_NULL(Instruction *instr);
static void exec_LOAD(Instruction *instr);
static void exec_LOAD_FIELD(Instruction *instr);
static void exec_LOAD_METHOD(Instruction *instr);
static void exec_NEW(Instruction *instr);

typedef struct ErrorHandler {
    int64_t error_code;
    int64_t absolute_offset;
    size_t  stack_frame_size;
    Scope  *scope;
} ErrorHandler;

static int64_t ipointer                                       = 0;
static cvector_vector_type(Object *) objects_stack            = NULL;
static cvector_vector_type(ErrorHandler) error_handlers_stack = NULL;
Env   *current_env                                            = NULL;
Scope *root_scope = NULL, *current_scope = NULL;

void objectsStackPush(Object *obj) {
    ref(obj);
    cvector_push_back(objects_stack, obj);
}

int objectsStackEmpty() {
    return cvector_empty(objects_stack);
}

size_t objectsStackSize() {
    return cvector_size(objects_stack);
}

Object *objectsStackTop() {
    return *cvector_back(objects_stack);
}

void objectsStackPop() {
    // if stack's empty, you're screwed
    unref(*cvector_back(objects_stack));
    cvector_pop_back(objects_stack);
}

static void handleError();

/*
Conventions:

function executing an instruction must update ipointer

an instruction must clean after itself
*/

static ivec instructions_list;

struct Instruction *vmCurrentInstruction() {
    return instructions_list + ipointer;
}

void vmExecute(ivec instructions) {
    instructions_list = instructions;
    while (ipointer < cvector_size(instructions)) {
        Instruction *instr = instructions + ipointer;

        assert(instr != NULL);

        if (setErrorReturnPoint()) {
            // error handler
            handleError();

            // if this code is reached, it means that the program
            // was able to recover from the error
            // and the normal execution should continue;
            continue;
        }

        switch (instr->code) {
        case POP_IC : {
            exec_POP(instr);
            break;
        }
        case SWAP_IC : {
            exec_SWAP(instr);
            break;
        }
        case CREATE_ENV_IC : {
            exec_CREATE_ENV(instr);
            break;
        }
        case SWITCH_ENV_INS_IC : {
            exec_SWITCH_ENV_INS(instr);
            break;
        }
        case SWITCH_ENV_OBJ_IC : {
            exec_SWITCH_ENV_OBJ(instr);
            break;
        }
        case IMPORT_MODULE_IC : {
            exec_IMPORT_MODULE(instr);
            break;
        }
        case EXPORT_OBJECT_IC : {
            exec_EXPORT_OBJECT(instr);
            break;
        }
        case CREATE_GLOBAL_IC : {
            exec_CREATE_GLOBAL(instr);
            break;
        }
        case CREATE_FUNCTION_IC : {
            exec_CREATE_FUNCTION(instr);
            break;
        }
        case CREATE_TYPE_IC : {
            exec_CREATE_TYPE(instr);
            break;
        }
        case CREATE_METHOD_IC : {
            exec_CREATE_METHOD(instr);
            break;
        }
        case CREATE_SCOPE_IC : {
            exec_CREATE_SCOPE(instr);
            break;
        }
        case DESTROY_SCOPE_IC : {
            exec_DESTROY_SCOPE(instr);
            break;
        }
        case JUMP_IF_FALSE_IC : {
            exec_JUMP_IF_FALSE(instr);
            break;
        }
        case JUMP_IC : {
            exec_JUMP(instr);
            break;
        }
        case RETURN_IC : {
            exec_RETURN(instr);
            break;
        }
        case REGISTER_CATCH_IC : {
            exec_REGISTER_CATCH(instr);
            break;
        }
        case DESTROY_CATCH_IC : {
            exec_DESTROY_CATCH(instr);
            break;
        }
        case SIGNAL_ERROR_IC : {
            exec_SIGNAL_ERROR(instr);
            break;
        }
        case CREATE_VAR_IC : {
            exec_CREATE_VAR(instr);
            break;
        }
        case COPY_BY_VALUE_IC : {
            exec_COPY_BY_VALUE(instr);
            break;
        }
        case COPY_BY_REFERENCE_IC : {
            exec_COPY_BY_REFERENCE(instr);
            break;
        }
        case COPY_BY_AUTO_IC : {
            exec_COPY_BY_AUTO(instr);
            break;
        }
        case ASSIGNMENT_IC : {
            exec_ASSIGNMENT(instr);
            break;
        }
        case LOGICAL_OR_IC : {
            exec_LOGICAL_OR(instr);
            break;
        }
        case LOGICAL_AND_IC : {
            exec_LOGICAL_AND(instr);
            break;
        }
        case BITWISE_OR_IC : {
            exec_BITWISE_OR(instr);
            break;
        }
        case BITWISE_XOR_IC : {
            exec_BITWISE_XOR(instr);
            break;
        }
        case BITWISE_AND_IC : {
            exec_BITWISE_AND(instr);
            break;
        }
        case EQUAL_IC : {
            exec_EQUAL(instr);
            break;
        }
        case NOT_EQUAL_IC : {
            exec_NOT_EQUAL(instr);
            break;
        }
        case LESS_THAN_IC : {
            exec_LESS_THAN(instr);
            break;
        }
        case LESS_EQUAL_IC : {
            exec_LESS_EQUAL(instr);
            break;
        }
        case GREATER_THAN_IC : {
            exec_GREATER_THAN(instr);
            break;
        }
        case GREATER_EQUAL_IC : {
            exec_GREATER_EQUAL(instr);
            break;
        }
        case ADDITION_IC : {
            exec_ADDITION(instr);
            break;
        }
        case SUBTRACTION_IC : {
            exec_SUBTRACTION(instr);
            break;
        }
        case LSHIFT_IC : {
            exec_LSHIFT(instr);
            break;
        }
        case RSHIFT_IC : {
            exec_RSHIFT(instr);
            break;
        }
        case MULTIPLICATION_IC : {
            exec_MULTIPLICATION(instr);
            break;
        }
        case DIVISION_IC : {
            exec_DIVISION(instr);
            break;
        }
        case REMAINDER_IC : {
            exec_REMAINDER(instr);
            break;
        }
        case POSITIVE_IC : {
            exec_POSITIVE(instr);
            break;
        }
        case NEGATION_IC : {
            exec_NEGATION(instr);
            break;
        }
        case INVERTION_IC : {
            exec_INVERTION(instr);
            break;
        }
        case LOGICAL_NOT_IC : {
            exec_LOGICAL_NOT(instr);
            break;
        }
        case CALL_IC : {
            exec_CALL(instr);
            break;
        }
        case ACCESS_IC : {
            exec_ACCESS(instr);
            break;
        }
        case LOAD_BOOL_IC : {
            exec_LOAD_BOOL(instr);
            break;
        }
        case LOAD_CHAR_IC : {
            exec_LOAD_CHAR(instr);
            break;
        }
        case LOAD_INT_IC : {
            exec_LOAD_INT(instr);
            break;
        }
        case LOAD_FLOAT_IC : {
            exec_LOAD_FLOAT(instr);
            break;
        }
        case LOAD_STRING_IC : {
            exec_LOAD_STRING(instr);
            break;
        }
        case LOAD_NULL_IC : {
            exec_LOAD_NULL(instr);
            break;
        }
        case LOAD_IC : {
            exec_LOAD(instr);
            break;
        }
        case LOAD_FIELD_IC : {
            exec_LOAD_FIELD(instr);
            break;
        }
        case LOAD_METHOD_IC : {
            exec_LOAD_METHOD(instr);
            break;
        }
        case NEW_IC : {
            exec_NEW(instr);
            break;
        }
        default : {
            signalError(INTERNAL_ERROR_CODE, "unknown instruction");
            exit(-1);    // cleaning after yourself? nah
        }
        }
    }
}

static void exec_POP(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "POP failed: empty objects_stack");
    }

    objectsStackPop();

    ipointer++;
}

static void exec_SWAP(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "SWAP failed: less that 2 elements on objects_stack");
    }

    size_t size = objectsStackSize();

    Object *t               = objects_stack[size - 1];
    objects_stack[size - 1] = objects_stack[size - 2];
    objects_stack[size - 2] = t;

    ipointer++;
}

static void exec_CREATE_ENV(Instruction *instr) {
    current_env = envGetById(envCreate(instr->env_id));

    ipointer++;
}

static void exec_SWITCH_ENV_INS(Instruction *instr) {
    current_env = envGetById(instr->env_id);

    ipointer++;
}

static void exec_SWITCH_ENV_OBJ(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "SWITCH_ENV_OBJ failed: empty objects_stack");
    }

    Object *obj = objectsStackTop();

    if (obj->type != C_FUNCTION_TYPE && obj->type != MOLA_FUNCTION_TYPE) {
        signalError(INTERNAL_ERROR_CODE, "SWITCH_ENV_OBJ failed: object on the stack is not a function");
    }

    if (obj->type == C_FUNCTION_TYPE) {
        current_env = ((CFunctionValue *)obj->value)->env;
    }
    else {
        current_env = ((MolaFunctionValue *)obj->value)->env;
    }

    ipointer++;

    // note: we do not pop the object from the stack!
}

static void exec_IMPORT_MODULE(Instruction *instr) {
    ipointer++;
}

static void exec_EXPORT_OBJECT(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "EXPORT_OBJECT failed: empty objects_stack");
    }

    if (identMapQuery(&current_env->exported_objects, instr->ident_arg1)) {
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Exported object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    identMapSet(&current_env->exported_objects, instr->ident_arg1, objectsStackTop());
    objectsStackPop();

    ipointer++;
}

static void exec_CREATE_GLOBAL(Instruction *instr) {
    if (identMapQuery(&current_env->globals, instr->ident_arg1)) {
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Global object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    NullValue *value = nullValueCreate();
    Object    *obj   = objectCreate(NULL_TYPE, value);
    identMapSet(&current_env->globals, instr->ident_arg1, obj);

    ipointer++;
}

static void exec_CREATE_FUNCTION(Instruction *instr) {
    if (identMapQuery(&current_env->globals, instr->ident_arg1)) {
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Global object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    int64_t offset = ipointer + 2 - current_env->absolute_offset;

    int64_t n_args = instr->n_args;
    ident  *args   = memalloc(n_args * sizeof(ident));
    memcpy(args, instr->args, n_args * sizeof(ident));
    for (int64_t i = 0; i < n_args; i++) {
        args[i] &= (1ll << 60) - 1;    // cancel modes
    }

    int8_t *modes = memalloc(n_args * sizeof(int8_t));
    for (int64_t i = 0; i < n_args; i++) {
        if (instr->args[i] & COPY_MODE_FLAG) {
            modes[i] = FUNCTION_ARG_MODE_COPY;
        }
        else if (instr->args[i] & REF_MODE_FLAG) {
            modes[i] = FUNCTION_ARG_MODE_REF;
        }
        else if (instr->args[i] & PASS_MODE_FLAG) {
            modes[i] = FUNCTION_ARG_MODE_PASS;
        }
        else {
            modes[i] = FUNCTION_ARG_MODE_AUTO;
        }
    }

    MolaFunctionValue *func_value = molaFunctionValueCreate(current_env, offset, n_args, args, modes);

    Object *obj = objectCreate(MOLA_FUNCTION_TYPE, func_value);

    identMapSet(&current_env->globals, instr->ident_arg1, obj);

    ipointer++;
}

static void exec_CREATE_TYPE(Instruction *instr) {
    ipointer++;
}

static void exec_CREATE_METHOD(Instruction *instr) {
    ipointer++;
}

static void exec_CREATE_SCOPE(Instruction *instr) {
    Scope *new_scope = scopeCreate((current_scope == NULL) ? 0 : instr->flags, current_scope);
    current_scope    = new_scope;

    ipointer++;
}

static void exec_DESTROY_SCOPE(Instruction *instr) {
    assert(current_scope != NULL);

    Scope *parent = current_scope->parent;
    scopeDestroy(current_scope);

    current_scope = parent;

    ipointer++;
}

static void exec_JUMP_IF_FALSE(Instruction *instr) {
    gcLock();
    if (objectsStackEmpty()) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "JUMP_IF_FALSE failed: empty objects stack");
    }

    Object *obj = objectsStackTop();
    objectsStackPop();

    if (obj->type != BOOL_TYPE) {
        signalError(VALUE_ERROR_CODE, "Expected a boolean value");
    }

    int value = ((BoolValue *)obj->value)->value;

    if (value) {
        gcUnlock();
        ipointer++;
        return;
    }

    gcMaybeGarbageObject(obj);
    ipointer += instr->int_arg1;
    gcUnlock();
}

static void exec_JUMP(Instruction *instr) {
    ipointer += instr->int_arg1;
}

static void exec_RETURN(Instruction *instr) {
    if (cvector_empty(objects_stack)) {
        signalError(INTERNAL_ERROR_CODE, "RETURN failed: empty objects_stack");
    }
    Object *top = *cvector_back(objects_stack);
    cvector_pop_back(objects_stack);

    if (top->type != RETURN_ADDRESS_TYPE) {
        signalError(INTERNAL_ERROR_CODE, "RETURN failed: object is not a return address");
    }

    int64_t return_address = (int64_t)top->value;

    ipointer = return_address;
}

static void exec_REGISTER_CATCH(Instruction *instr) {
    ipointer++;
}

static void exec_DESTROY_CATCH(Instruction *instr) {
    ipointer++;
}

static void exec_SIGNAL_ERROR(Instruction *instr) {
    ipointer++;
}

static void exec_CREATE_VAR(Instruction *instr) {
    gcLock();
    if (objectsStackEmpty()) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "CREATE_VAR failed: empty objects_stack");
    }

    assert(current_scope != NULL);

    if (identMapQuery(&current_scope->map, instr->ident_arg1)) {
        gcUnlock();
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Local object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    Object *top = objectsStackTop();
    objectsStackPop();

    scopeInsert(current_scope, instr->ident_arg1, top);

    ipointer++;
    gcUnlock();
}

static void exec_COPY_BY_VALUE(Instruction *instr) {
    ipointer++;
}

static void exec_COPY_BY_REFERENCE(Instruction *instr) {
    ipointer++;
}

// TODO: make basic types be stored in object.value
// therefore eliminating the ability to reference basic types :(
static void exec_COPY_BY_AUTO(Instruction *instr) {
    gcLock();
    if (objectsStackEmpty()) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "COPY_BY_AUTO failed: empty objects_stack");
    }

    Object *obj = objectsStackTop();

    // any copy of an rvalue can be the rvalue itself
    if (obj->is_rvalue) {
        gcUnlock();
        ipointer++;
        return;
    }

    objectsStackPop();

    void *value = NULL;

    switch (obj->type) {
    case BOOL_TYPE : value = boolValueCopyByAuto(obj->value); break;
    case INT_TYPE : value = intValueCopyByAuto(obj->value); break;
    case CHAR_TYPE : value = charValueCopyByAuto(obj->value); break;
    case FLOAT_TYPE : value = floatValueCopyByAuto(obj->value); break;
    case STRING_TYPE : value = stringValueCopyByAuto(obj->value); break;
    case ARRAY_TYPE : value = arrayValueCopyByAuto(obj->value); break;
    case TYPE_TYPE : value = typeValueCopyByAuto(obj->value); break;
    case INSTANCE_TYPE : value = instanceValueCopyByAuto(obj->value); break;
    case MOLA_FUNCTION_TYPE : value = molaFunctionValueCopyByAuto(obj->value); break;
    case C_FUNCTION_TYPE : value = cFunctionValueCopyByAuto(obj->value); break;
    case MODULE_TYPE : value = moduleValueCopyByAuto(obj->value); break;
    case NULL_TYPE : value = nullValueCopyByAuto(obj->value); break;
    case RETURN_ADDRESS_TYPE : {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "COPY_BY_AUTO failed: RETURN_ADDRESS_TYPE on the stack");
    }
    }

    assert(value != NULL);
    Object *res = objectCreate(obj->type, value);

    objectsStackPush(res);

    ipointer++;
    gcUnlock();
}

static void exec_ASSIGNMENT(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "ASSIGNMENT failed: less than 2 elements on the stack");
    }

    Object *obj1 = objectsStackTop();
    objectsStackPop();

    Object *obj2 = objectsStackTop();
    objectsStackPop();

    obj1->type  = obj2->type;
    obj1->value = obj2->value;

    objectsStackPush(obj1);

    gcMaybeGarbageObject(obj2);

    ipointer++;
    gcUnlock();
}

static void exec_LOGICAL_OR(Instruction *instr) {
    ipointer++;
}

static void exec_LOGICAL_AND(Instruction *instr) {
    ipointer++;
}

static void exec_BITWISE_OR(Instruction *instr) {
    ipointer++;
}

static void exec_BITWISE_XOR(Instruction *instr) {
    ipointer++;
}

static void exec_BITWISE_AND(Instruction *instr) {
    ipointer++;
}

static void exec_EQUAL(Instruction *instr) {
    ipointer++;
}

static void exec_NOT_EQUAL(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "NOT_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    // temporary
    assert(x->type == INT_TYPE && y->type == INT_TYPE);

    IntValue *xval = x->value, *yval = y->value;

    // this object is not referenced by anything other than the stack
    // so it doesn't need to be copied when we want a copy of it....
    Object *res    = objectCreate(BOOL_TYPE, boolValueCreate(xval->value != yval->value));
    res->is_rvalue = 1;
    objectsStackPush(res);

    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
}

static void exec_LESS_THAN(Instruction *instr) {
    ipointer++;
}

static void exec_LESS_EQUAL(Instruction *instr) {
    ipointer++;
}

static void exec_GREATER_THAN(Instruction *instr) {
    ipointer++;
}

static void exec_GREATER_EQUAL(Instruction *instr) {
    ipointer++;
}

static void exec_ADDITION(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "ADDITION failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    // temporary
    assert(x->type == INT_TYPE && y->type == INT_TYPE);

    IntValue *xval = x->value, *yval = y->value;

    // this object is not referenced by anything other than the stack
    // so it doesn't need to be copied when we want a copy of it....
    Object *res = objectCreate(INT_TYPE, intValueCreate(xval->value + yval->value));
    objectsStackPush(res);
    res->is_rvalue = 1;

    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
}

static void exec_SUBTRACTION(Instruction *instr) {
    ipointer++;
}

static void exec_LSHIFT(Instruction *instr) {
    ipointer++;
}

static void exec_RSHIFT(Instruction *instr) {
    ipointer++;
}

static void exec_MULTIPLICATION(Instruction *instr) {
    ipointer++;
}

static void exec_DIVISION(Instruction *instr) {
    ipointer++;
}

static void exec_REMAINDER(Instruction *instr) {
    ipointer++;
}

static void exec_POSITIVE(Instruction *instr) {
    ipointer++;
}

static void exec_NEGATION(Instruction *instr) {
    ipointer++;
}

static void exec_INVERTION(Instruction *instr) {
    // TEMPORARY PRINTER
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "INVERTION failed: empty objects_stack");
    }

    Object *obj = objectsStackTop();

    if (obj->type == INT_TYPE) {
        molalog("PRINT: Obj value: %lld\n", ((IntValue *)obj->value)->value);
    }

    ipointer++;
}

static void exec_LOGICAL_NOT(Instruction *instr) {
    ipointer++;
}

static void exec_CALL(Instruction *instr) {
    ipointer++;
}

static void exec_ACCESS(Instruction *instr) {
    ipointer++;
}

static void exec_LOAD_BOOL(Instruction *instr) {
    ipointer++;
}

static void exec_LOAD_CHAR(Instruction *instr) {
    ipointer++;
}

static void exec_LOAD_INT(Instruction *instr) {
    IntValue *value = intValueCreate(instr->int_arg1);
    Object   *obj   = objectCreate(INT_TYPE, value);

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_FLOAT(Instruction *instr) {
    FloatValue *value = floatValueCreate(instr->float_arg1);
    Object     *obj   = objectCreate(FLOAT_TYPE, value);

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_STRING(Instruction *instr) {
    StringValue *value = stringValueCreate(strlen(instr->string_arg1), instr->string_arg1);
    Object      *obj   = objectCreate(STRING_TYPE, value);

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_NULL(Instruction *instr) {
    NullValue *value = nullValueCreate();
    Object    *obj   = objectCreate(STRING_TYPE, value);

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD(Instruction *instr) {
    /*
    1. look for a global object
    2. then look for a local object, or report error
    */

    Object *res = identMapGet(&current_env->globals, instr->ident_arg1);
    if (res != NULL) {
        objectsStackPush(res);
        ipointer++;
        return;
    }

    res = scopeRecursiveLookup(current_scope, instr->ident_arg1);

    objectsStackPush(res);
    ipointer++;
    return;
}

static void exec_LOAD_FIELD(Instruction *instr) {
    ipointer++;
}

static void exec_LOAD_METHOD(Instruction *instr) {
    ipointer++;
}

static void exec_NEW(Instruction *instr) {
    ipointer++;
}

static void handleError() {
    ipointer++;
}
