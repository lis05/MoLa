#include "gen.h"
#include "../front/parser.h"
#include "alloc.h"
#include "cvector.h"

Instruction genCreateInstructionPOP(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = POP_IC;
}

Instruction genCreateInstructionSWAP(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SWAP_IC;
}

Instruction genCreateInstructionCREATE_ENV(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = CREATE_ENV_IC;
}

Instruction genCreateInstructionSWITCH_ENV_INS(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SWITCH_ENV_INS_IC;
}

Instruction genCreateInstructionSWITCH_ENV_OBJ(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SWITCH_ENV_OBJ_IC;
}

Instruction genCreateInstructionIMPORT_MODULE(char *filename, size_t lineno, char *module_path, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code        = IMPORT_MODULE_IC;
    res.string_arg1 = module_path;
    res.n_args      = name;    // ugly and might brake things (no way) ikr
}

Instruction genCreateInstructionEXPORT_OBJECT(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = EXPORT_OBJECT_IC;
    res.ident_arg1 = name;
}

Instruction genCreateInstructionCREATE_GLOBAL(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_GLOBAL_IC;
    res.ident_arg1 = name;
}

Instruction genCreateInstructionCREATE_FUNCTION(char *filename, size_t lineno, ident name, size_t n_args, ident *args) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_FUNCTION_IC;
    res.ident_arg1 = name;
    res.n_args     = n_args;
    res.args       = args;
}

Instruction genCreateInstructionCREATE_TYPE(char  *filename,
                                            size_t lineno,
                                            ident  name,
                                            size_t n_fields,
                                            ident *fields,
                                            size_t n_methods,
                                            ident *methods) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_TYPE_IC;
    res.ident_arg1 = name;
    res.n_args     = n_fields + n_methods + 2;
    res.args       = memalloc(res.n_args * sizeof(ident));
    res.args[0]    = n_fields;
    res.args[1]    = n_methods;
    memcpy(res.args + 2, fields, n_fields * sizeof(ident));
    memcpy(res.args + 2 + n_fields * sizeof(ident), methods, n_methods * sizeof(ident));

    memfree(fields);
    memfree(methods);
}

Instruction genCreateInstructionCREATE_METHOD(char *filename, size_t lineno, ident name, size_t n_args, ident *args) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_METHOD_IC;
    res.ident_arg1 = name;
    res.n_args     = n_args;
    res.args       = args;
}

Instruction genCreateInstructionCREATE_SCOPE(char *filename, size_t lineno, int8_t access_mode) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code  = CREATE_SCOPE_IC;
    res.flags = access_mode;
}

Instruction genCreateInstructionDESTROY_SCOPE(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = DESTROY_SCOPE_IC;
}

Instruction genCreateInstructionJUMP_IF_FALSE(char *filename, size_t lineno, int64_t offset) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = JUMP_IF_FALSE_IC;
    res.int_arg1 = offset;
}

Instruction genCreateInstructionJUMP(char *filename, size_t lineno, int64_t offset) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = JUMP_IC;
    res.int_arg1 = offset;
}

Instruction genCreateInstructionRETURN(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = RETURN_IC;
}

Instruction genCreateInstructionREGISTER_CATCH(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = REGISTER_CATCH_IC;
}

Instruction genCreateInstructionDESTROY_CATCH(char *filename, size_t lineno, int64_t n) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = DESTROY_CATCH_IC;
    res.int_arg1 = n;
}

Instruction genCreateInstructionSIGNAL_ERROR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SIGNAL_ERROR_IC;
}

Instruction genCreateInstructionCREATE_VAR(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_VAR_IC;
    res.ident_arg1 = name;
}

Instruction genCreateInstructionCOPY_BY_VALUE(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = COPY_BY_VALUE_IC;
}

Instruction genCreateInstructionCOPY_BY_REFERENCE(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = COPY_BY_REFERENCE_IC;
}

Instruction genCreateInstructionCOPY_BY_AUTO(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = COPY_BY_AUTO_IC;
}

Instruction genCreateInstructionASSIGNMENT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = ASSIGNMENT_IC;
}

Instruction genCreateInstructionLOGICAL_OR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOGICAL_OR_IC;
}

Instruction genCreateInstructionLOGICAL_AND(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOGICAL_AND_IC;
}

Instruction genCreateInstructionBITWISE_OR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = BITWISE_OR_IC;
}

Instruction genCreateInstructionBITWISE_XOR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = BITWISE_XOR_IC;
}

Instruction genCreateInstructionBITWISE_AND(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = BITWISE_AND_IC;
}

Instruction genCreateInstructionEQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = EQUAL_IC;
}

Instruction genCreateInstructionNOT_EQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = NOT_EQUAL_IC;
}

Instruction genCreateInstructionLESS_THAN(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LESS_THAN_IC;
}

Instruction genCreateInstructionLESS_EQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LESS_EQUAL_IC;
}

Instruction genCreateInstructionGREATER_THAN(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = GREATER_THAN_IC;
}

Instruction genCreateInstructionGREATER_EQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = GREATER_EQUAL_IC;
}

Instruction genCreateInstructionADDITION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = ADDITION_IC;
}

Instruction genCreateInstructionSUBTRACTION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SUBTRACTION_IC;
}

Instruction genCreateInstructionLSHIFT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LSHIFT_IC;
}

Instruction genCreateInstructionRSHIFT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = RSHIFT_IC;
}

Instruction genCreateInstructionMULTIPLICATION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = MULTIPLICATION_IC;
}

Instruction genCreateInstructionDIVISION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = DIVISION_IC;
}

Instruction genCreateInstructionREMAINDER(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = REMAINDER_IC;
}

Instruction genCreateInstructionNEGATION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = NEGATION_IC;
}

Instruction genCreateInstructionINVERTION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = INVERTION_IC;
}

Instruction genCreateInstructionLOGICAL_NOT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOGICAL_NOT_IC;
}

Instruction genCreateInstructionCALL(char *filename, size_t lineno, int64_t n) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = CALL_IC;
    res.int_arg1 = n;
}

Instruction genCreateInstructionACCESS(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = ACCESS_IC;
}

Instruction genCreateInstructionLOAD_BOOL(char *filename, size_t lineno, int8_t value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = LOAD_BOOL_IC;
    res.int_arg1 = value;
}

Instruction genCreateInstructionLOAD_CHAR(char *filename, size_t lineno, char value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code      = LOAD_CHAR_IC;
    res.char_arg1 = value;
}

Instruction genCreateInstructionLOAD_INT(char *filename, size_t lineno, int64_t value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = LOAD_INT_IC;
    res.int_arg1 = value;
}

Instruction genCreateInstructionLOAD_FLOAT(char *filename, size_t lineno, double value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_FLOAT_IC;
    res.float_arg1 = value;
}

Instruction genCreateInstructionLOAD_STRING(char *filename, size_t lineno, char *value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code        = LOAD_STRING_IC;
    res.string_arg1 = value;
}

Instruction genCreateInstructionLOAD_NULL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOAD_NULL_IC;
}

Instruction genCreateInstructionLOAD(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_IC;
    res.ident_arg1 = name;
}

Instruction genCreateInstructionLOAD_FIELD(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_FIELD_IC;
    res.ident_arg1 = name;
}

Instruction genCreateInstructionLOAD_METHOD(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_METHOD_IC;
    res.ident_arg1 = name;
}

Instruction genCreateInstructionNEW(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = NEW_IC;
    res.int_arg1 = name;
}

#define pushall(dest, src)                                                                                             \
    for (int i = 0; i < cvector_size(src); i++) {                                                                      \
        cvector_push_back(dest, src[i]);                                                                               \
    }

static ivec gen(struct AstNode *node);

ivec genCompile(struct AstNode *node) {
    assert(node != NULL);

    // we assume that node is the root node of the entire program

    // TODO: add functions to create instructions conviniently + update codegen part of mola.md

    return gen(node);
}

static ivec gen(struct AstNode *node) {
    assert(node != NULL);
    ivec output = NULL;

    switch (node->type) {
    case PROGRAM_NODE : {
        break;
    }
    case IMPORT_STMT_NODE : {
        break;
    }
    case EXPORT_STMT_NODE : {
        break;
    }
    case EXPORT_ITEM_LIST_NODE : {
        break;
    }
    case EXPORT_ITEM_NODE : {
        break;
    }
    case GLOBAL_VARIABLE_STMT_NODE : {
        break;
    }
    case FUNCTION_STMT_NODE : {
        break;
    }
    case PARAMETER_LIST_NODE : {
        break;
    }
    case PARAMETER_ITEM_NODE : {
        break;
    }
    case TYPE_STMT_NODE : {
        break;
    }
    case MEMBER_LIST_NODE : {
        break;
    }
    case MEMBER_ITEM_NODE : {
        break;
    }
    case METHOD_STMT_NODE : {
        break;
    }
    case CONSTRUCTOR_STMT_NODE : {
        break;
    }
    case DESTRUCTOR_STMT_NODE : {
        break;
    }
    case STMT_NODE : {
        break;
    }
    case BLOCK_STMT_NODE : {
        break;
    }
    case STMT_LIST_NODE : {
        break;
    }
    case WHILE_STMT_NODE : {
        break;
    }
    case FOR_STMT_NODE : {
        break;
    }
    case IF_STMT_NODE : {
        break;
    }
    case CONTINUE_STMT_NODE : {
        break;
    }
    case BREAK_STMT_NODE : {
        break;
    }
    case RETURN_STMT_NODE : {
        break;
    }
    case ASSIGNMENT_STMT_NODE : {
        break;
    }
    case TRY_CATCH_STMT_NODE : {
        break;
    }
    case CATCH_ITEM_LIST_NODE : {
        break;
    }
    case CATCH_ITEM_NODE : {
        break;
    }
    case SIGNAL_STMT_NODE : {
        break;
    }
    case VAR_STMT_NODE : {
        break;
    }
    case ASSIGNMENT_ITEM_LIST_NODE : {
        break;
    }
    case ASSIGNMENT_ITEM_NODE : {
        break;
    }
    case EXPR_NODE : {
        break;
    }
    case ASSIGNMENT_NODE : {
        break;
    }
    case INLINE_IF_NODE : {
        break;
    }
    case NEW_NODE : {
        break;
    }
    case LOGICAL_OR_NODE : {
        break;
    }
    case LOGICAL_AND_NODE : {
        break;
    }
    case BITWISE_OR_NODE : {
        break;
    }
    case BITWISE_XOR_NODE : {
        break;
    }
    case BITWISE_AND_NODE : {
        break;
    }
    case EQUALITY_NODE : {
        break;
    }
    case RELATIONAL_NODE : {
        break;
    }
    case SUM_NODE : {
        break;
    }
    case BITWISE_SHIFT_NODE : {
        break;
    }
    case TERM_NODE : {
        break;
    }
    case PREFIX_OP_NODE : {
        break;
    }
    case PRIMARY_NODE : {
        break;
    }
    case ELEMENTARY_NODE : {
        break;
    }
    case LITERAL_NODE : {
        break;
    }
    case MODULE_PATH_NODE : {
        break;
    }
    case MODULE_PATH_COMPACT_NODE : {
        break;
    }
    case EXPR_LIST_NODE : {
        break;
    }
    case IDENTIFIER_LIST_NODE : {
        break;
    }
    default : {
        break;
    }
    }
}
