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
    COPY_IC,
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
    NEW_IC,
    HALT_IC
};

// instructions where the continue/break statements have to jump
#define LOOP_CONTINUE_FLAG 1
#define LOOP_BREAK_FLAG    2

typedef struct Instruction {
    int64_t              id;
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
