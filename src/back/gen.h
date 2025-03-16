#ifndef __mola_gen_h__
#define __mola_gen_h__

#include "../front/symtab.h"
#include "../util.h"
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
    POSITIVE_IC,
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

    int64_t  flags;
    size_t   n_args;
    int64_t *args;

    union {
        int64_t int_arg1;      // preferred over args[0] and n_args
        ident   ident_arg1;    // preferred over int_arg1 for identifier
        char    char_arg1;
        double  float_arg1;
        char   *string_arg1;
    };
} Instruction;

typedef cvector_vector_type(Instruction) ivec;

void genPrintInstrShort(int64_t pos, Instruction *instr);

/*
continue and break statements will initially have rel_offset equal to 0.
After the compilations is complete, a loop will locate all loops and continue/break statements,
changing the rel_offset afterwards.
*/

/* these consume any pointers. */
Instruction genInsPOP(char *filename, size_t lineno);
Instruction genInsSWAP(char *filename, size_t lineno);
Instruction genInsCREATE_ENV(char *filename, size_t lineno);
Instruction genInsSWITCH_ENV_INS(char *filename, size_t lineno);
Instruction genInsSWITCH_ENV_OBJ(char *filename, size_t lineno);
Instruction genInsIMPORT_MODULE(char *filename, size_t lineno, char *module_path, ident name);
Instruction genInsEXPORT_OBJECT(char *filename, size_t lineno, ident name);
Instruction genInsCREATE_GLOBAL(char *filename, size_t lineno, ident name);
// first 4 bits of args are mode flags.
Instruction genInsCREATE_FUNCTION(char *filename, size_t lineno, ident name, size_t n_args, ident *args);
Instruction genInsCREATE_TYPE(char  *filename,
                              size_t lineno,
                              ident  name,
                              size_t n_fields,
                              ident *fields,
                              size_t n_methods,
                              ident *methods);
// first 4 bits of args are mode flags.
Instruction genInsCREATE_METHOD(char *filename, size_t lineno, ident name, size_t n_args, ident *args);
Instruction genInsCREATE_SCOPE(char *filename, size_t lineno, int8_t access_mode);
Instruction genInsDESTROY_SCOPE(char *filename, size_t lineno);
Instruction genInsJUMP_IF_FALSE(char *filename, size_t lineno, int64_t offset);
Instruction genInsJUMP(char *filename, size_t lineno, int64_t offset);
Instruction genInsRETURN(char *filename, size_t lineno);
Instruction genInsREGISTER_CATCH(char *filename, size_t lineno);
Instruction genInsDESTROY_CATCH(char *filename, size_t lineno, int64_t n);
Instruction genInsSIGNAL_ERROR(char *filename, size_t lineno);
Instruction genInsCREATE_VAR(char *filename, size_t lineno, ident name);
Instruction genInsCOPY_BY_VALUE(char *filename, size_t lineno);
Instruction genInsCOPY_BY_REFERENCE(char *filename, size_t lineno);
Instruction genInsCOPY_BY_AUTO(char *filename, size_t lineno);
Instruction genInsASSIGNMENT(char *filename, size_t lineno);
Instruction genInsLOGICAL_OR(char *filename, size_t lineno);
Instruction genInsLOGICAL_AND(char *filename, size_t lineno);
Instruction genInsBITWISE_OR(char *filename, size_t lineno);
Instruction genInsBITWISE_XOR(char *filename, size_t lineno);
Instruction genInsBITWISE_AND(char *filename, size_t lineno);
Instruction genInsEQUAL(char *filename, size_t lineno);
Instruction genInsNOT_EQUAL(char *filename, size_t lineno);
Instruction genInsLESS_THAN(char *filename, size_t lineno);
Instruction genInsLESS_EQUAL(char *filename, size_t lineno);
Instruction genInsGREATER_THAN(char *filename, size_t lineno);
Instruction genInsGREATER_EQUAL(char *filename, size_t lineno);
Instruction genInsADDITION(char *filename, size_t lineno);
Instruction genInsSUBTRACTION(char *filename, size_t lineno);
Instruction genInsLSHIFT(char *filename, size_t lineno);
Instruction genInsRSHIFT(char *filename, size_t lineno);
Instruction genInsMULTIPLICATION(char *filename, size_t lineno);
Instruction genInsDIVISION(char *filename, size_t lineno);
Instruction genInsREMAINDER(char *filename, size_t lineno);
Instruction genInsPOSITIVE(char *filename, size_t lineno);
Instruction genInsNEGATION(char *filename, size_t lineno);
Instruction genInsINVERTION(char *filename, size_t lineno);
Instruction genInsLOGICAL_NOT(char *filename, size_t lineno);
Instruction genInsCALL(char *filename, size_t lineno, int64_t n);
Instruction genInsACCESS(char *filename, size_t lineno);
Instruction genInsLOAD_BOOL(char *filename, size_t lineno, int8_t value);
Instruction genInsLOAD_CHAR(char *filename, size_t lineno, char value);
Instruction genInsLOAD_INT(char *filename, size_t lineno, int64_t value);
Instruction genInsLOAD_FLOAT(char *filename, size_t lineno, double value);
Instruction genInsLOAD_STRING(char *filename, size_t lineno, char *value);
Instruction genInsLOAD_NULL(char *filename, size_t lineno);
Instruction genInsLOAD(char *filename, size_t lineno, ident name);
Instruction genInsLOAD_FIELD(char *filename, size_t lineno, ident name);
Instruction genInsLOAD_METHOD(char *filename, size_t lineno, ident name);
Instruction genInsNEW(char *filename, size_t lineno);

struct AstNode;

typedef struct inode {
    Instruction ins;

    struct inode *next;
} inode;

typedef struct ilist {
    inode *head, *tail;
    size_t size;
} ilist;

ilist ilistCreate();
void  ilistLink(ilist *first, ilist *second);    // first -> second
void  ilistSwap(ilist *first, ilist *second);
void  ilistAppend(ilist *list, Instruction ins);
void  ilistDestroy(ilist *list);

ilist genCompile(struct AstNode *node);

#endif
