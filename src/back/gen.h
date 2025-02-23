#ifndef __mola_gen_h__
#define __mola_gen_h__

#include "../front/symtab.h"
#include "../util.h"

enum InstructionCode {
    POP_IC,
    SWAP_IC,
    CREATE_ENV_IC,
    SWITCH_ENV_INS_IC,
    SWITCH_ENV_OBJ_IC,
    IMPORT_MODULE_IC,
    EXPORT_OBJECT_IC,
    CREATE_GLOBAL_IC,
    CREATE_FUNCTION_IC,
    CREATE_TYPE_IC,
    CREATE_METHOD_IC,
    CREATE_SCOPE_IC,
    DESTROY_SCOPE_IC,
    JUMP_IF_FALSE_IC,
    JUMP_IC,
    RETURN_IC,
    REGISTER_CATCH_IC,
    DESTROY_CATCH_IC,
    SIGNAL_ERROR_IC,
    CREATE_VAR_IC,
    COPY_BY_VALUE_IC,
    COPY_BY_REFERENCE_IC,
    COPY_BY_AUTO_IC,
    ASSIGNMENT_IC,
    LOGICAL_OR_IC,
    LOGICAL_AND_IC,
    BITWISE_OR_IC,
    BITWISE_XOR_IC,
    BITWISE_AND_IC,
    EQUAL_IC,
    NOT_EQUAL_IC,
    LESS_THAN_IC,
    LESS_EQUAL_IC,
    GREATER_THAN_IC,
    GREATER_EQUAL_IC,
    ADDITION_IC,
    SUBTRACTION_IC,
    LSHIFT_IC,
    RSHIFT_IC,
    MULTIPLICATION_IC,
    DIVISION_IC,
    REMAINDER_IC,
    NEGATION_IC,
    INVERTION_IC,
    LOGICAL_NOT_IC,
    CALL_IC,
    ACCESS_IC,
    LOAD_BOOL_IC,
    LOAD_CHAR_IC,
    LOAD_INT_IC,
    LOAD_FLOAT_IC,
    LOAD_STRING_IC,
    LOAD_NULL_IC,
    LOAD_IC,
    LOAD_FIELD_IC,
    LOAD_METHOD_IC,
    NEW_IC
};

typedef struct Instruction {
    enum InstructionCode code;
    char                *filename;    // taken from the AST.
    size_t               lineno;      // taken from the AST.

    size_t env_id;                    // set when the module is run (or imported)

    size_t   n_args;
    int64_t *args;

    union {
        int64_t int_arg1;      // preferred over args[0] or n_args
        ident   ident_arg1;    // preferred over int_arg1 for identifier
        char    char_arg1;
        double  float_arg1;
        char   *string_arg1;
    };
} Instruction;

#endif
