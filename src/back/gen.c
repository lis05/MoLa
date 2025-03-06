#include "gen.h"
#include "../front/parser.h"
#include "alloc.h"
#include "env.h"

static void printIdent(ident id) {
    printf("%d[%s]", id, symtabIdentToString(id));
}

void genPrintInstrShort(Instruction *instr) {
    molalog(""); 
    if (instr == NULL) {
        printf("NULL\n");
        return;
    }

    switch (instr->code) {
    case CREATE_ENV_IC : {
        printf("%-20s    ", "CREATE_ENV_IC");
        printf("lineno=%-4d ", instr->lineno);
        printf("n_args=%-4d ", instr->n_args);

        printf("\n");
        return;
    }
    case IMPORT_MODULE_IC : {
        printf("%-20s    ", "IMPORT_MODULE_IC");
        printf("lineno=%-4d ", instr->lineno);
        printf("n_args=%-4d ", instr->n_args);

        printf("module_path=%s\t", instr->string_arg1);
        printf("import_as=");
        printIdent(instr->n_args);

        printf("\n");
        return;
    }
    default : {
        printf("%-20s    ", "INVALID");
        printf("lineno=%-4d ", instr->lineno);
        printf("n_args=%-4d ", instr->n_args);

        printf("\n");
        return;
    }
    }
}

Instruction genCreateInstructionPOP(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = POP_IC;
    return res;
}

Instruction genCreateInstructionSWAP(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SWAP_IC;
    return res;
}

Instruction genCreateInstructionCREATE_ENV(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = CREATE_ENV_IC;
    return res;
}

Instruction genCreateInstructionSWITCH_ENV_INS(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SWITCH_ENV_INS_IC;
    return res;
}

Instruction genCreateInstructionSWITCH_ENV_OBJ(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SWITCH_ENV_OBJ_IC;
    return res;
}

Instruction genCreateInstructionIMPORT_MODULE(char *filename, size_t lineno, char *module_path, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code        = IMPORT_MODULE_IC;
    res.string_arg1 = module_path;
    res.n_args      = name;    // ugly and might brake things but ok
    return res;
}

Instruction genCreateInstructionEXPORT_OBJECT(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = EXPORT_OBJECT_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genCreateInstructionCREATE_GLOBAL(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_GLOBAL_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genCreateInstructionCREATE_FUNCTION(char *filename, size_t lineno, ident name, size_t n_args, ident *args) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_FUNCTION_IC;
    res.ident_arg1 = name;
    res.n_args     = n_args;
    res.args       = args;
    return res;
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
    return res;
}

Instruction genCreateInstructionCREATE_METHOD(char *filename, size_t lineno, ident name, size_t n_args, ident *args) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_METHOD_IC;
    res.ident_arg1 = name;
    res.n_args     = n_args;
    res.args       = args;
    return res;
}

Instruction genCreateInstructionCREATE_SCOPE(char *filename, size_t lineno, int8_t access_mode) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code  = CREATE_SCOPE_IC;
    res.flags = access_mode;
    return res;
}

Instruction genCreateInstructionDESTROY_SCOPE(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = DESTROY_SCOPE_IC;
    return res;
}

Instruction genCreateInstructionJUMP_IF_FALSE(char *filename, size_t lineno, int64_t offset) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = JUMP_IF_FALSE_IC;
    res.int_arg1 = offset;
    return res;
}

Instruction genCreateInstructionJUMP(char *filename, size_t lineno, int64_t offset) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = JUMP_IC;
    res.int_arg1 = offset;
    return res;
}

Instruction genCreateInstructionRETURN(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = RETURN_IC;
    return res;
}

Instruction genCreateInstructionREGISTER_CATCH(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = REGISTER_CATCH_IC;
    return res;
}

Instruction genCreateInstructionDESTROY_CATCH(char *filename, size_t lineno, int64_t n) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = DESTROY_CATCH_IC;
    res.int_arg1 = n;
    return res;
}

Instruction genCreateInstructionSIGNAL_ERROR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SIGNAL_ERROR_IC;
    return res;
}

Instruction genCreateInstructionCREATE_VAR(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = CREATE_VAR_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genCreateInstructionCOPY_BY_VALUE(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = COPY_BY_VALUE_IC;
    return res;
}

Instruction genCreateInstructionCOPY_BY_REFERENCE(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = COPY_BY_REFERENCE_IC;
    return res;
}

Instruction genCreateInstructionCOPY_BY_AUTO(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = COPY_BY_AUTO_IC;
    return res;
}

Instruction genCreateInstructionASSIGNMENT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = ASSIGNMENT_IC;
    return res;
}

Instruction genCreateInstructionLOGICAL_OR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOGICAL_OR_IC;
    return res;
}

Instruction genCreateInstructionLOGICAL_AND(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOGICAL_AND_IC;
    return res;
}

Instruction genCreateInstructionBITWISE_OR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = BITWISE_OR_IC;
    return res;
}

Instruction genCreateInstructionBITWISE_XOR(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = BITWISE_XOR_IC;
    return res;
}

Instruction genCreateInstructionBITWISE_AND(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = BITWISE_AND_IC;
    return res;
}

Instruction genCreateInstructionEQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = EQUAL_IC;
    return res;
}

Instruction genCreateInstructionNOT_EQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = NOT_EQUAL_IC;
    return res;
}

Instruction genCreateInstructionLESS_THAN(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LESS_THAN_IC;
    return res;
}

Instruction genCreateInstructionLESS_EQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LESS_EQUAL_IC;
    return res;
}

Instruction genCreateInstructionGREATER_THAN(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = GREATER_THAN_IC;
    return res;
}

Instruction genCreateInstructionGREATER_EQUAL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = GREATER_EQUAL_IC;
    return res;
}

Instruction genCreateInstructionADDITION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = ADDITION_IC;
    return res;
}

Instruction genCreateInstructionSUBTRACTION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = SUBTRACTION_IC;
    return res;
}

Instruction genCreateInstructionLSHIFT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LSHIFT_IC;
    return res;
}

Instruction genCreateInstructionRSHIFT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = RSHIFT_IC;
    return res;
}

Instruction genCreateInstructionMULTIPLICATION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = MULTIPLICATION_IC;
    return res;
}

Instruction genCreateInstructionDIVISION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = DIVISION_IC;
    return res;
}

Instruction genCreateInstructionREMAINDER(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = REMAINDER_IC;
    return res;
}

Instruction genCreateInstructionNEGATION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = NEGATION_IC;
    return res;
}

Instruction genCreateInstructionINVERTION(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = INVERTION_IC;
    return res;
}

Instruction genCreateInstructionLOGICAL_NOT(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOGICAL_NOT_IC;
    return res;
}

Instruction genCreateInstructionCALL(char *filename, size_t lineno, int64_t n) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = CALL_IC;
    res.int_arg1 = n;
    return res;
}

Instruction genCreateInstructionACCESS(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = ACCESS_IC;
    return res;
}

Instruction genCreateInstructionLOAD_BOOL(char *filename, size_t lineno, int8_t value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = LOAD_BOOL_IC;
    res.int_arg1 = value;
    return res;
}

Instruction genCreateInstructionLOAD_CHAR(char *filename, size_t lineno, char value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code      = LOAD_CHAR_IC;
    res.char_arg1 = value;
    return res;
}

Instruction genCreateInstructionLOAD_INT(char *filename, size_t lineno, int64_t value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = LOAD_INT_IC;
    res.int_arg1 = value;
    return res;
}

Instruction genCreateInstructionLOAD_FLOAT(char *filename, size_t lineno, double value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_FLOAT_IC;
    res.float_arg1 = value;
    return res;
}

Instruction genCreateInstructionLOAD_STRING(char *filename, size_t lineno, char *value) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code        = LOAD_STRING_IC;
    res.string_arg1 = value;
    return res;
}

Instruction genCreateInstructionLOAD_NULL(char *filename, size_t lineno) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code = LOAD_NULL_IC;
    return res;
}

Instruction genCreateInstructionLOAD(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genCreateInstructionLOAD_FIELD(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_FIELD_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genCreateInstructionLOAD_METHOD(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code       = LOAD_METHOD_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genCreateInstructionNEW(char *filename, size_t lineno, ident name) {
    Instruction res;
    res.filename = filename;
    res.lineno   = lineno;

    res.code     = NEW_IC;
    res.int_arg1 = name;
    return res;
}

#define pushall(dest, src)                                                                                             \
    for (int i = 0; i < cvector_size(src); i++) {                                                                      \
        cvector_push_back(dest, src[i]);                                                                               \
    }

static ivec gen(AstNode *node);

static size_t curEnvId;
#define info(node) (node)->filename, (node)->lineno

ivec genCompile(AstNode *node) {
    assert(node != NULL);

    // we assume that node is the root node of the entire program
    curEnvId    = envGenAvailableId();
    ivec result = NULL;

    // will create an env with id curEnvId
    cvector_push_back(result, genCreateInstructionCREATE_ENV(info(node)));

    ivec tail = gen(node);
    pushall(result, tail);
    cvector_free(tail);

    return result;
}

static ivec gen_program(AstNode *node);
static ivec gen_import_stmt(AstNode *node);
static ivec gen_export_stmt(AstNode *node);
static ivec gen_export_item_list(AstNode *node);
static ivec gen_export_item(AstNode *node);
static ivec gen_global_variable_stmt(AstNode *node);
static ivec gen_function_stmt(AstNode *node);
static ivec gen_parameter_list(AstNode *node);
static ivec gen_parameter_item(AstNode *node);
static ivec gen_type_stmt(AstNode *node);
static ivec gen_member_list(AstNode *node);
static ivec gen_member_item(AstNode *node);
static ivec gen_method_stmt(AstNode *node);
static ivec gen_constructor_stmt(AstNode *node);
static ivec gen_destructor_stmt(AstNode *node);
static ivec gen_stmt(AstNode *node);
static ivec gen_block_stmt(AstNode *node);
static ivec gen_stmt_list(AstNode *node);
static ivec gen_while_stmt(AstNode *node);
static ivec gen_for_stmt(AstNode *node);
static ivec gen_if_stmt(AstNode *node);
static ivec gen_continue_stmt(AstNode *node);
static ivec gen_break_stmt(AstNode *node);
static ivec gen_return_stmt(AstNode *node);
static ivec gen_assignment_stmt(AstNode *node);
static ivec gen_try_catch_stmt(AstNode *node);
static ivec gen_catch_item_list(AstNode *node);
static ivec gen_catch_item(AstNode *node);
static ivec gen_signal_stmt(AstNode *node);
static ivec gen_var_stmt(AstNode *node);
static ivec gen_assignment_item_list(AstNode *node);
static ivec gen_assignment_item(AstNode *node);
static ivec gen_expr(AstNode *node);
static ivec gen_assignment(AstNode *node);
static ivec gen_inline_if(AstNode *node);
static ivec gen_new(AstNode *node);
static ivec gen_logical_or(AstNode *node);
static ivec gen_logical_and(AstNode *node);
static ivec gen_bitwise_or(AstNode *node);
static ivec gen_bitwise_xor(AstNode *node);
static ivec gen_bitwise_and(AstNode *node);
static ivec gen_equality(AstNode *node);
static ivec gen_relational(AstNode *node);
static ivec gen_sum(AstNode *node);
static ivec gen_bitwise_shift(AstNode *node);
static ivec gen_term(AstNode *node);
static ivec gen_prefix_op(AstNode *node);
static ivec gen_primary(AstNode *node);
static ivec gen_elementary(AstNode *node);
static ivec gen_literal(AstNode *node);
static ivec gen_module_path(AstNode *node);
static ivec gen_module_path_upwards(AstNode *node);
static ivec gen_module_path_compact(AstNode *node);
static ivec gen_expr_list(AstNode *node);
static ivec gen_identifier_list(AstNode *node);

static ivec gen(AstNode *node) {
    assert(node != NULL);
    ivec output = NULL;
    ivec temp   = NULL;

    switch (node->type) {
    case PROGRAM_NODE : {
        return gen_program(node);
    }
    case IMPORT_STMT_NODE : {
        return gen_import_stmt(node);
    }
    case EXPORT_STMT_NODE : {
        return gen_export_stmt(node);
    }
    case EXPORT_ITEM_LIST_NODE : {
        return gen_export_item_list(node);
    }
    case EXPORT_ITEM_NODE : {
        return gen_export_item(node);
    }
    case GLOBAL_VARIABLE_STMT_NODE : {
        return gen_global_variable_stmt(node);
    }
    case FUNCTION_STMT_NODE : {
        return gen_function_stmt(node);
    }
    case PARAMETER_LIST_NODE : {
        return gen_parameter_list(node);
    }
    case PARAMETER_ITEM_NODE : {
        return gen_parameter_item(node);
    }
    case TYPE_STMT_NODE : {
        return gen_type_stmt(node);
    }
    case MEMBER_LIST_NODE : {
        return gen_member_list(node);
    }
    case MEMBER_ITEM_NODE : {
        return gen_member_item(node);
    }
    case METHOD_STMT_NODE : {
        return gen_method_stmt(node);
    }
    case CONSTRUCTOR_STMT_NODE : {
        return gen_constructor_stmt(node);
    }
    case DESTRUCTOR_STMT_NODE : {
        return gen_destructor_stmt(node);
    }
    case STMT_NODE : {
        return gen_stmt(node);
    }
    case BLOCK_STMT_NODE : {
        return gen_block_stmt(node);
    }
    case STMT_LIST_NODE : {
        return gen_stmt_list(node);
    }
    case WHILE_STMT_NODE : {
        return gen_while_stmt(node);
    }
    case FOR_STMT_NODE : {
        return gen_for_stmt(node);
    }
    case IF_STMT_NODE : {
        return gen_if_stmt(node);
    }
    case CONTINUE_STMT_NODE : {
        return gen_continue_stmt(node);
    }
    case BREAK_STMT_NODE : {
        return gen_break_stmt(node);
    }
    case RETURN_STMT_NODE : {
        return gen_return_stmt(node);
    }
    case ASSIGNMENT_STMT_NODE : {
        return gen_assignment_stmt(node);
    }
    case TRY_CATCH_STMT_NODE : {
        return gen_try_catch_stmt(node);
    }
    case CATCH_ITEM_LIST_NODE : {
        return gen_catch_item_list(node);
    }
    case CATCH_ITEM_NODE : {
        return gen_catch_item(node);
    }
    case SIGNAL_STMT_NODE : {
        return gen_signal_stmt(node);
    }
    case VAR_STMT_NODE : {
        return gen_var_stmt(node);
    }
    case ASSIGNMENT_ITEM_LIST_NODE : {
        return gen_assignment_item_list(node);
    }
    case ASSIGNMENT_ITEM_NODE : {
        return gen_assignment_item(node);
    }
    case EXPR_NODE : {
        return gen_expr(node);
    }
    case ASSIGNMENT_NODE : {
        return gen_assignment(node);
    }
    case INLINE_IF_NODE : {
        return gen_inline_if(node);
    }
    case NEW_NODE : {
        return gen_new(node);
    }
    case LOGICAL_OR_NODE : {
        return gen_logical_or(node);
    }
    case LOGICAL_AND_NODE : {
        return gen_logical_and(node);
    }
    case BITWISE_OR_NODE : {
        return gen_bitwise_or(node);
    }
    case BITWISE_XOR_NODE : {
        return gen_bitwise_xor(node);
    }
    case BITWISE_AND_NODE : {
        return gen_bitwise_and(node);
    }
    case EQUALITY_NODE : {
        return gen_equality(node);
    }
    case RELATIONAL_NODE : {
        return gen_relational(node);
    }
    case SUM_NODE : {
        return gen_sum(node);
    }
    case BITWISE_SHIFT_NODE : {
        return gen_bitwise_shift(node);
    }
    case TERM_NODE : {
        return gen_term(node);
    }
    case PREFIX_OP_NODE : {
        return gen_prefix_op(node);
    }
    case PRIMARY_NODE : {
        return gen_primary(node);
    }
    case ELEMENTARY_NODE : {
        return gen_elementary(node);
    }
    case LITERAL_NODE : {
        return gen_literal(node);
    }
    case MODULE_PATH_NODE : {
        return gen_module_path(node);
    }
    case MODULE_PATH_UPWARDS_NODE : {
        return gen_module_path_upwards(node);
    }
    case MODULE_PATH_COMPACT_NODE : {
        return gen_module_path_compact(node);
    }
    case EXPR_LIST_NODE : {
        return gen_expr_list(node);
    }
    case IDENTIFIER_LIST_NODE : {
        return gen_identifier_list(node);
    }
    default : {
        return NULL;
    }
    }
}

static ivec gen_program(AstNode *node) {
    ivec output = NULL, temp = NULL;

    switch (node->option) {
    case NO_OPTION : {
        /*
        >

        root of the entire program. no action needed, it is handled in genCompile

        <
        */
        return NULL;
        break;
    }
    default : {
        /*
        > program something

        since all productions (expect the last one) looks the same
        we can just handle them here

        < gen(program)
        < gen(something)
        */

        AstNode *program   = node->nodes[0];
        AstNode *something = node->nodes[1];

        temp = gen(program);
        pushall(output, temp);
        cvector_free(temp);

        temp = gen(something);
        pushall(output, temp);
        cvector_free(temp);

        return output;
        break;
    } break;
    }
}

static void constructModulePath(AstNode *node, charvec *res) {
    assert(node != NULL);
    assert(node->type == MODULE_PATH_NODE);

    if (node->option == MODULE_PATH_COMPACT_OPTION) {
        AstNode *arrows = NULL;
        AstNode *body   = NULL;
        if (node->n_nodes == 2) {
            arrows = node->nodes[0];
            body   = node->nodes[1];
        }
        else {
            body = node->nodes[0];
        }

        while (arrows != NULL) {
            cvector_push_back(*res, '^');

            if (arrows->n_nodes != 0) {
                arrows = arrows->nodes[0];
            }
            else {
                arrows = NULL;
            }
        }

        while (body != NULL) {
            // a.b.c.d
            char  *id = symtabIdentToString(body->nodes[0]->identifier_value);
            size_t n  = strlen(id);
            for (size_t i = 0; i < n; i++) {
                cvector_push_back(*res, id[i]);
            }

            if (body->n_nodes != 1) {
                cvector_push_back(*res, '.');
                body = body->nodes[1];
            }
            else {
                body = NULL;
            }
        }

        return;
    }
    else {
        size_t n = strlen(node->nodes[0]->string_value);
        for (size_t i = 0; i < n; i++) {
            cvector_push_back(*res, node->nodes[0]->string_value[i]);
        }
        return;
    }
}

static ivec gen_import_stmt(AstNode *node) {
    ivec output = NULL, temp = NULL;

    /*
    > IMPORT module_path AS IDENTIFIER

    module_path is constructed using dfs

    < IMPORT_MODULE module_path IDENTIFIER
    */

    charvec module_path = NULL;
    constructModulePath(node->nodes[0], &module_path);
    cvector_push_back(module_path, '\0');    // for copying

    ivec res = NULL;
    cvector_push_back(
    res,
    genCreateInstructionIMPORT_MODULE(info(node), strdup(module_path), node->nodes[1]->identifier_value));

    return res;
}

static ivec gen_export_stmt(AstNode *node) {}

static ivec gen_export_item_list(AstNode *node) {}

static ivec gen_export_item(AstNode *node) {}

static ivec gen_global_variable_stmt(AstNode *node) {}

static ivec gen_function_stmt(AstNode *node) {}

static ivec gen_parameter_list(AstNode *node) {}

static ivec gen_parameter_item(AstNode *node) {}

static ivec gen_type_stmt(AstNode *node) {}

static ivec gen_member_list(AstNode *node) {}

static ivec gen_member_item(AstNode *node) {}

static ivec gen_method_stmt(AstNode *node) {}

static ivec gen_constructor_stmt(AstNode *node) {}

static ivec gen_destructor_stmt(AstNode *node) {}

static ivec gen_stmt(AstNode *node) {}

static ivec gen_block_stmt(AstNode *node) {}

static ivec gen_stmt_list(AstNode *node) {}

static ivec gen_while_stmt(AstNode *node) {}

static ivec gen_for_stmt(AstNode *node) {}

static ivec gen_if_stmt(AstNode *node) {}

static ivec gen_continue_stmt(AstNode *node) {}

static ivec gen_break_stmt(AstNode *node) {}

static ivec gen_return_stmt(AstNode *node) {}

static ivec gen_assignment_stmt(AstNode *node) {}

static ivec gen_try_catch_stmt(AstNode *node) {}

static ivec gen_catch_item_list(AstNode *node) {}

static ivec gen_catch_item(AstNode *node) {}

static ivec gen_signal_stmt(AstNode *node) {}

static ivec gen_var_stmt(AstNode *node) {}

static ivec gen_assignment_item_list(AstNode *node) {}

static ivec gen_assignment_item(AstNode *node) {}

static ivec gen_expr(AstNode *node) {}

static ivec gen_assignment(AstNode *node) {}

static ivec gen_inline_if(AstNode *node) {}

static ivec gen_new(AstNode *node) {}

static ivec gen_logical_or(AstNode *node) {}

static ivec gen_logical_and(AstNode *node) {}

static ivec gen_bitwise_or(AstNode *node) {}

static ivec gen_bitwise_xor(AstNode *node) {}

static ivec gen_bitwise_and(AstNode *node) {}

static ivec gen_equality(AstNode *node) {}

static ivec gen_relational(AstNode *node) {}

static ivec gen_sum(AstNode *node) {}

static ivec gen_bitwise_shift(AstNode *node) {}

static ivec gen_term(AstNode *node) {}

static ivec gen_prefix_op(AstNode *node) {}

static ivec gen_primary(AstNode *node) {}

static ivec gen_elementary(AstNode *node) {}

static ivec gen_literal(AstNode *node) {}

static ivec gen_module_path(AstNode *node) {}

static ivec gen_module_path_upwards(AstNode *node) {}

static ivec gen_module_path_compact(AstNode *node) {}

static ivec gen_expr_list(AstNode *node) {}

static ivec gen_identifier_list(AstNode *node) {}
