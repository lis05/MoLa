#include "vm.h"
#include "alloc.h"
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

static int64_t ipointer = 0;
static cvector_vector_type(Object *) objects_stack;
static cvector_vector_type(ErrorHandler) error_handlers_stack;
Env   *current_env;
Scope *root_scope, *current_scope;

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
    if (cvector_empty(objects_stack)) {
        signalError(INTERNAL_ERROR_CODE, "POP failed: empty objects_stack");
    }

    cvector_pop_back(objects_stack);
}

static void exec_SWAP(Instruction *instr) {
    if (cvector_size(objects_stack) < 2) {
        signalError(INTERNAL_ERROR_CODE, "SWAP failed: less that 2 elements on objects_stack");
    }

    size_t size = cvector_size(objects_stack);

    Object *t               = objects_stack[size - 1];
    objects_stack[size - 1] = objects_stack[size - 2];
    objects_stack[size - 2] = t;
}

static void exec_CREATE_ENV(Instruction *instr) {
    current_env = envGetById(envCreate());
}

static void exec_SWITCH_ENV_INS(Instruction *instr) {
    current_env = envGetById(instr->env_id);
}

static void exec_SWITCH_ENV_OBJ(Instruction *instr) {
    if (cvector_empty(objects_stack)) {
        signalError(INTERNAL_ERROR_CODE, "SWITCH_ENV_OBJ failed: empty objects_stack");
    }

    Object *obj = *cvector_back(objects_stack);

    if (obj->type != C_FUNCTION_TYPE && obj->type != MOLA_FUNCTION_TYPE) {
        signalError(INTERNAL_ERROR_CODE, "SWITCH_ENV_OBJ failed: object on the stack is not a function");
    }

    // what if module is NULL? can it even happen?

    if (obj->type == C_FUNCTION_TYPE) {
        current_env = ((CFunctionValue *)obj->value)->module->env;
    }
    else {
        current_env = ((MolaFunctionValue *)obj->value)->module->env;
    }
}

static void exec_IMPORT_MODULE(Instruction *instr) {}

static void exec_EXPORT_OBJECT(Instruction *instr) {}

static void exec_CREATE_GLOBAL(Instruction *instr) {}

static void exec_CREATE_FUNCTION(Instruction *instr) {}

static void exec_CREATE_TYPE(Instruction *instr) {}

static void exec_CREATE_METHOD(Instruction *instr) {}

static void exec_CREATE_SCOPE(Instruction *instr) {}

static void exec_DESTROY_SCOPE(Instruction *instr) {}

static void exec_JUMP_IF_FALSE(Instruction *instr) {}

static void exec_JUMP(Instruction *instr) {
    if (!(0 <= ipointer + instr->int_arg1 && ipointer + instr->int_arg1 < cvector_size(instructions_list))) {
        signalError(INTERNAL_ERROR_CODE, "JUMP failed: address out of bounds");
    }

    ipointer += instr->int_arg1;
}

static void exec_RETURN(Instruction *instr) {}

static void exec_REGISTER_CATCH(Instruction *instr) {}

static void exec_DESTROY_CATCH(Instruction *instr) {}

static void exec_SIGNAL_ERROR(Instruction *instr) {}

static void exec_CREATE_VAR(Instruction *instr) {}

static void exec_COPY_BY_VALUE(Instruction *instr) {}

static void exec_COPY_BY_REFERENCE(Instruction *instr) {}

static void exec_COPY_BY_AUTO(Instruction *instr) {}

static void exec_ASSIGNMENT(Instruction *instr) {}

static void exec_LOGICAL_OR(Instruction *instr) {}

static void exec_LOGICAL_AND(Instruction *instr) {}

static void exec_BITWISE_OR(Instruction *instr) {}

static void exec_BITWISE_XOR(Instruction *instr) {}

static void exec_BITWISE_AND(Instruction *instr) {}

static void exec_EQUAL(Instruction *instr) {}

static void exec_NOT_EQUAL(Instruction *instr) {}

static void exec_LESS_THAN(Instruction *instr) {}

static void exec_LESS_EQUAL(Instruction *instr) {}

static void exec_GREATER_THAN(Instruction *instr) {}

static void exec_GREATER_EQUAL(Instruction *instr) {}

static void exec_ADDITION(Instruction *instr) {}

static void exec_SUBTRACTION(Instruction *instr) {}

static void exec_LSHIFT(Instruction *instr) {}

static void exec_RSHIFT(Instruction *instr) {}

static void exec_MULTIPLICATION(Instruction *instr) {}

static void exec_DIVISION(Instruction *instr) {}

static void exec_REMAINDER(Instruction *instr) {}

static void exec_POSITIVE(Instruction *instr) {}

static void exec_NEGATION(Instruction *instr) {}

static void exec_INVERTION(Instruction *instr) {}

static void exec_LOGICAL_NOT(Instruction *instr) {}

static void exec_CALL(Instruction *instr) {}

static void exec_ACCESS(Instruction *instr) {}

static void exec_LOAD_BOOL(Instruction *instr) {}

static void exec_LOAD_CHAR(Instruction *instr) {}

static void exec_LOAD_INT(Instruction *instr) {}

static void exec_LOAD_FLOAT(Instruction *instr) {}

static void exec_LOAD_STRING(Instruction *instr) {}

static void exec_LOAD_NULL(Instruction *instr) {}

static void exec_LOAD(Instruction *instr) {}

static void exec_LOAD_FIELD(Instruction *instr) {}

static void exec_LOAD_METHOD(Instruction *instr) {}

static void exec_NEW(Instruction *instr) {}

static void handleError() {}
