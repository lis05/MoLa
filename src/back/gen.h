#ifndef __mola_gen_h__
#define __mola_gen_h__

#include "../front/symtab.h"
#include "../util.h"
#include "cvector.h"
#include "gen.h"

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

// instructions where the continue/break statements have to jump
#define LOOP_CONTINUE_FLAG 1
#define LOOP_BREAK_FLAG    2

#define COPY_MODE_FLAG (1ull << 63)
#define REF_MODE_FLAG  (1ull << 62)
#define PASS_MODE_FLAG (1ull << 61)
#define AUTO_MODE_FLAG (1ull << 60)

typedef struct Instruction {
    enum InstructionCode code;
    char                *filename;    // taken from the AST.
    size_t               lineno;      // taken from the AST.

    size_t env_id;                    // set when the module is run (or imported)

    int8_t   flags : 2;
    size_t   n_args: sizeof(size_t) - 2;
    int64_t *args;

    union {
        int64_t int_arg1;      // preferred over args[0] and n_args
        ident   ident_arg1;    // preferred over int_arg1 for identifier
        char    char_arg1;
        double  float_arg1;
        char   *string_arg1;
    };
} Instruction;

/*
continue and break statements will initially have rel_offset equal to 0.
After the compilations is complete, a loop will locate all loops and continue/break statements,
changing the rel_offset afterwards.
*/

/* these consume any pointers. */
Instruction genCreateInstructionPOP(char *filename, size_t lineno);
Instruction genCreateInstructionSWAP(char *filename, size_t lineno);
Instruction genCreateInstructionCREATE_ENV(char *filename, size_t lineno);
Instruction genCreateInstructionSWITCH_ENV_INS(char *filename, size_t lineno);
Instruction genCreateInstructionSWITCH_ENV_OBJ(char *filename, size_t lineno);
Instruction genCreateInstructionIMPORT_MODULE(char *filename, size_t lineno, char *module_path, ident name);
Instruction genCreateInstructionEXPORT_OBJECT(char *filename, size_t lineno, ident name);
Instruction genCreateInstructionCREATE_GLOBAL(char *filename, size_t lineno, ident name);
// first 4 bits of args are mode flags.
Instruction genCreateInstructionCREATE_FUNCTION(char *filename, size_t lineno, ident name, size_t n_args, ident *args);
Instruction genCreateInstructionCREATE_TYPE(char  *filename,
                                            size_t lineno,
                                            ident  name,
                                            size_t n_fields,
                                            ident *fields,
                                            size_t n_methods,
                                            ident *methods);
// first 4 bits of args are mode flags.
Instruction genCreateInstructionCREATE_METHOD(char *filename, size_t lineno, ident name, size_t n_args, ident *args);
Instruction genCreateInstructionCREATE_SCOPE(char *filename, size_t lineno, int8_t access_mode);
Instruction genCreateInstructionDESTROY_SCOPE(char *filename, size_t lineno);
Instruction genCreateInstructionJUMP_IF_FALSE(char *filename, size_t lineno, int64_t offset);
Instruction genCreateInstructionJUMP(char *filename, size_t lineno, int64_t offset);
Instruction genCreateInstructionRETURN(char *filename, size_t lineno);
Instruction genCreateInstructionREGISTER_CATCH(char *filename, size_t lineno);
Instruction genCreateInstructionDESTROY_CATCH(char *filename, size_t lineno, int64_t n);
Instruction genCreateInstructionSIGNAL_ERROR(char *filename, size_t lineno);
Instruction genCreateInstructionCREATE_VAR(char *filename, size_t lineno, ident name);
Instruction genCreateInstructionCOPY_BY_VALUE(char *filename, size_t lineno);
Instruction genCreateInstructionCOPY_BY_REFERENCE(char *filename, size_t lineno);
Instruction genCreateInstructionCOPY_BY_AUTO(char *filename, size_t lineno);
Instruction genCreateInstructionASSIGNMENT(char *filename, size_t lineno);
Instruction genCreateInstructionLOGICAL_OR(char *filename, size_t lineno);
Instruction genCreateInstructionLOGICAL_AND(char *filename, size_t lineno);
Instruction genCreateInstructionBITWISE_OR(char *filename, size_t lineno);
Instruction genCreateInstructionBITWISE_XOR(char *filename, size_t lineno);
Instruction genCreateInstructionBITWISE_AND(char *filename, size_t lineno);
Instruction genCreateInstructionEQUAL(char *filename, size_t lineno);
Instruction genCreateInstructionNOT_EQUAL(char *filename, size_t lineno);
Instruction genCreateInstructionLESS_THAN(char *filename, size_t lineno);
Instruction genCreateInstructionLESS_EQUAL(char *filename, size_t lineno);
Instruction genCreateInstructionGREATER_THAN(char *filename, size_t lineno);
Instruction genCreateInstructionGREATER_EQUAL(char *filename, size_t lineno);
Instruction genCreateInstructionADDITION(char *filename, size_t lineno);
Instruction genCreateInstructionSUBTRACTION(char *filename, size_t lineno);
Instruction genCreateInstructionLSHIFT(char *filename, size_t lineno);
Instruction genCreateInstructionRSHIFT(char *filename, size_t lineno);
Instruction genCreateInstructionMULTIPLICATION(char *filename, size_t lineno);
Instruction genCreateInstructionDIVISION(char *filename, size_t lineno);
Instruction genCreateInstructionREMAINDER(char *filename, size_t lineno);
Instruction genCreateInstructionNEGATION(char *filename, size_t lineno);
Instruction genCreateInstructionINVERTION(char *filename, size_t lineno);
Instruction genCreateInstructionLOGICAL_NOT(char *filename, size_t lineno);
Instruction genCreateInstructionCALL(char *filename, size_t lineno, int64_t n);
Instruction genCreateInstructionACCESS(char *filename, size_t lineno);
Instruction genCreateInstructionLOAD_BOOL(char *filename, size_t lineno, int8_t value);
Instruction genCreateInstructionLOAD_CHAR(char *filename, size_t lineno, char value);
Instruction genCreateInstructionLOAD_INT(char *filename, size_t lineno, int64_t value);
Instruction genCreateInstructionLOAD_FLOAT(char *filename, size_t lineno, double value);
Instruction genCreateInstructionLOAD_STRING(char *filename, size_t lineno, char *value);
Instruction genCreateInstructionLOAD_NULL(char *filename, size_t lineno);
Instruction genCreateInstructionLOAD(char *filename, size_t lineno, ident name);
Instruction genCreateInstructionLOAD_FIELD(char *filename, size_t lineno, ident name);
Instruction genCreateInstructionLOAD_METHOD(char *filename, size_t lineno, ident name);
Instruction genCreateInstructionNEW(char *filename, size_t lineno, ident name);

struct AstNode;

/*
New instructions will be appended to the instructions list when modules are imported.
For this reason, they will be stored in vectors, which can append new instructions faster.
*/
typedef cvector_vector_type(Instruction) ivec;    // Instruction*

ivec genCompile(struct AstNode *node);

#endif
