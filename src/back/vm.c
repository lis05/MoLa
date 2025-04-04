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
static void exec_COPY(Instruction *instr);
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
        case COPY_IC : {
            exec_COPY(instr);
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

    Object *obj = objectCreate(NULL_TYPE, 0);
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

    MolaFunctionValue *func_value = molaFunctionValueCreate(current_env, offset, n_args, args);

    Object *obj = objectCreate(MOLA_FUNCTION_TYPE, (uint64_t)func_value);

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

    if (obj->bool_value) {
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
    gcLock();
    if (cvector_empty(objects_stack)) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "RETURN failed: empty objects_stack");
    }

    Object *top = objectsStackTop();
    objectsStackPop();

    if (top->type != RETURN_ADDRESS_TYPE) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "RETURN failed: object is not a return address");
    }

    int64_t return_address = (int64_t)top->value;

    ipointer = return_address;
    gcUnlock();
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

static void exec_COPY(Instruction *instr) {
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

    uint64_t value = 0;

    switch (obj->type) {
    case BOOL_TYPE : value = (uint64_t)obj->bool_value; break;
    case INT_TYPE : value = (uint64_t)obj->int_value; break;
    case CHAR_TYPE : value = (uint64_t)obj->char_value; break;
    case FLOAT_TYPE : value = (uint64_t)obj->float_value; break;
    case STRING_TYPE : value = (uint64_t)stringValueCopy(obj->value); break;
    case ARRAY_TYPE : value = (uint64_t)arrayValueCopy(obj->value); break;
    case TYPE_TYPE : value = (uint64_t)typeValueCopy(obj->value); break;
    case INSTANCE_TYPE : value = (uint64_t)instanceValueCopy(obj->value); break;
    case MOLA_FUNCTION_TYPE : value = (uint64_t)molaFunctionValueCopy(obj->value); break;
    case C_FUNCTION_TYPE : value = (uint64_t)cFunctionValueCopy(obj->value); break;
    case MODULE_TYPE : value = (uint64_t)obj->value; break;
    case NULL_TYPE : break;
    case RETURN_ADDRESS_TYPE : {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "COPY_BY_AUTO failed: RETURN_ADDRESS_TYPE on the stack");
    }
    }

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

    obj1->type = obj2->type;

    // this works because we basically copy the entire union of obj2 into obj1
    obj1->value = obj2->value;

    objectsStackPush(obj1);

    gcMaybeGarbageObject(obj2);

    ipointer++;
    gcUnlock();
}

/*

When evaluation A op B, A and B are promoted to the highest common type:

String
^
Float
^
Integer
^
Character
^
Boolean
^
Null

All other types cause an error.

All other (arythmetical) operators are handled separatelly.
*/

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

// -1 x=y, 0 x>y, 1 x<y, 2 x!=y (uncomparable)
static int compare(Object *x, Object *y) {
    Object *res;
    if (x->type != y->type) {
        return 2;
    }

    switch (x->type) {
    case NULL_TYPE : {
        return -1;
    } break;
    case BOOL_TYPE : {
        if (x->bool_value == y->bool_value) {
            return -1;
        }
        return x->bool_value < y->bool_value;
    } break;
    case CHAR_TYPE : {
        if (x->char_value == y->char_value) {
            return -1;
        }
        return x->char_value < y->char_value;
    } break;
    case INT_TYPE : {
        if (x->int_value == y->int_value) {
            return -1;
        }
        return x->int_value < y->int_value;
    } break;
    case FLOAT_TYPE : {
        if (x->float_value == y->float_value) {
            return -1;
        }
        return x->float_value < y->float_value;
    } break;
    case STRING_TYPE : {
        int r = stringCompare(x->value, y->value);
        if (r == 0) {
            return -1;
        }
        return (r == -1) ? 1 : 0;
    } break;
    case ARRAY_TYPE : {
        ArrayValue *X = x->value, *Y = y->value;
        size_t      m = (X->length < Y->length) ? X->length : Y->length;

        for (size_t i = 0; i < m; i++) {
            int r = compare(X->array[i], Y->array[i]);
            if (r == 2) {
                return 2;
            }
            if (r != -1) {
                return r;    // 0 or 1
            }
        }

        if (X->length < Y->length) {
            return 1;
        }
        else if (X->length > Y->length) {
            return 0;
        }
        return -1;
    } break;
    case TYPE_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case INSTANCE_TYPE : {
        return 2;    // TODO
    } break;
    case MOLA_FUNCTION_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case C_FUNCTION_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case MODULE_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case RETURN_ADDRESS_TYPE : {
        return 2;    // lol
    } break;
    }
}

static void exec_EQUAL(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    Object *res    = objectCreate(BOOL_TYPE, (uint64_t)(compare(x, y) == -1));
    res->is_rvalue = 1;

    objectsStackPush(res);
    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
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

    Object *res    = objectCreate(BOOL_TYPE, (uint64_t)(compare(x, y) != -1));
    res->is_rvalue = 1;

    objectsStackPush(res);
    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
}

static void exec_LESS_THAN(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "LESS_THAN failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    Object *res    = objectCreate(BOOL_TYPE, (uint64_t)(compare(x, y) == 1));
    res->is_rvalue = 1;

    objectsStackPush(res);
    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
}

static void exec_LESS_EQUAL(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "LESS_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int     r      = compare(x, y);
    Object *res    = objectCreate(BOOL_TYPE, (uint64_t)(r == 1 || r == -1));
    res->is_rvalue = 1;

    objectsStackPush(res);
    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
}

static void exec_GREATER_THAN(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "LESS_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int     r      = compare(x, y);
    Object *res    = objectCreate(BOOL_TYPE, (uint64_t)(r == 0));
    res->is_rvalue = 1;

    objectsStackPush(res);
    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
}

static void exec_GREATER_EQUAL(Instruction *instr) {
    gcLock();
    if (objectsStackSize() < 2) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "LESS_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int     r      = compare(x, y);
    Object *res    = objectCreate(BOOL_TYPE, (uint64_t)(r == 0 || r == -1));
    res->is_rvalue = 1;

    objectsStackPush(res);
    gcMaybeGarbageObject(x);
    gcMaybeGarbageObject(y);

    ipointer++;
    gcUnlock();
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

    /*
     */

    // temporary
    assert(x->type == INT_TYPE && y->type == INT_TYPE);

    // this object is not referenced by anything other than the stack
    // so it doesn't need to be copied when we want a copy of it....
    Object *res    = objectCreate(INT_TYPE, (uint64_t)(x->int_value + y->int_value));
    res->is_rvalue = 1;
    objectsStackPush(res);

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

    switch (obj->type) {
    case INT_TYPE : {
        molalog("PRINT: INT    value: %lld\n", obj->int_value);
        break;
    }
    case STRING_TYPE : {
        molalog("PRINT: STRING value: %s\n", ((StringValue *)obj->value)->string);
        break;
    }
    }

    ipointer++;
}

static void exec_LOGICAL_NOT(Instruction *instr) {
    ipointer++;
}

static void exec_CALL(Instruction *instr) {
    gcLock();

    int64_t n = instr->int_arg1;

    if (objectsStackSize() < n + 1) {
        gcUnlock();
        signalError(INTERNAL_ERROR_CODE, "CALL failed: too few objects on the stack");
    }

    Object *f = objects_stack[objectsStackSize() - 1];
    if (f->type != C_FUNCTION_TYPE && f->type != MOLA_FUNCTION_TYPE) {
        gcUnlock();
        signalError(VALUE_ERROR_CODE, "Not callable");
    }

    if (f->type == C_FUNCTION_TYPE && ((CFunctionValue *)f->value)->n_args != n) {
        gcUnlock();
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE,
                    errstrfmt("Expected %d arguments, got %d", ((CFunctionValue *)f->value)->n_args, n));
    }
    else if (f->type == MOLA_FUNCTION_TYPE && ((MolaFunctionValue *)f->value)->n_args != n) {
        gcUnlock();
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE,
                    errstrfmt("Expected %d arguments, got %d", ((MolaFunctionValue *)f->value)->n_args, n));
    }

    for (int i = 0; i < n; i++) {
        Object *arg = objects_stack[objectsStackSize() - 2 - (n - i - 1)];

        if (f->type == MOLA_FUNCTION_TYPE) {
            scopeInsert(current_scope, ((MolaFunctionValue *)f->value)->args[i], arg);
        }
        else {
            // TODO
        }
    }

    for (int i = 0; i < n + 1; i++) {
        objectsStackPop();
    }

    Object *ret = objectCreate(RETURN_ADDRESS_TYPE, ipointer + 1);
    objectsStackPush(ret);

    gcUnlock();
    if (f->type == MOLA_FUNCTION_TYPE) {
        ipointer = ((MolaFunctionValue *)f->value)->relative_offset + current_env->absolute_offset;
    }
    else {
        // TODO
    }
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
    Object *obj    = objectCreate(INT_TYPE, (uint64_t)instr->int_arg1);
    obj->is_rvalue = 1;

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_FLOAT(Instruction *instr) {
    Object *obj    = objectCreate(FLOAT_TYPE, (uint64_t)instr->float_arg1);
    obj->is_rvalue = 1;

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_STRING(Instruction *instr) {
    StringValue *value = stringValueCreate(strlen(instr->string_arg1), instr->string_arg1);
    Object      *obj   = objectCreate(STRING_TYPE, (uint64_t)value);

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_NULL(Instruction *instr) {
    Object *obj    = objectCreate(NULL_TYPE, 0);
    obj->is_rvalue = 1;

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
