#include "gen.h"
#include "../front/parser.h"
#include "alloc.h"
#include "env.h"

static void printIdent(ident id) {
    printf("%lld[%s]", id, symtabIdentToString(id));
}

static char *getChar(char c) {
    switch (c) {
    case '\n' : return "'\\n'";
    case '\t' : return "'\\t'";
    case '\v' : return "'\\v'";
    case '\a' : return "'\\a'";
    case '\f' : return "'\\f'";
    case '\b' : return "'\\b'";
    case '\r' : return "'\\r'";
    }

    static char buf[32];
    sprintf(buf, "'%c'", c);
    return buf;
}

void genPrintInstrShort(int64_t pos, Instruction *instr) {
    molalog("%-4d id=%-4d ", pos, instr->id);
    if (instr == NULL) {
        printf("NULL\n");
        return;
    }

    switch (instr->code) {
    case POP_IC : {
        printf("%-20s    ", "POP");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case SWAP_IC : {
        printf("%-20s    ", "SWAP");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case CREATE_ENV_IC : {
        printf("%-20s    ", "CREATE_ENV");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case SWITCH_ENV_INS_IC : {
        printf("%-20s    ", "SWITCH_ENV_INS");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case SWITCH_ENV_OBJ_IC : {
        printf("%-20s    ", "SWITCH_ENV_OBJ");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case IMPORT_MODULE_IC : {
        printf("%-20s    ", "IMPORT_MODULE");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("module_path=%s\t", instr->string_arg1);
        printf("import_as=");
        printIdent(instr->n_args);

        printf("\n");
        return;
    }
    case EXPORT_OBJECT_IC : {
        printf("%-20s    ", "EXPORT_OBJECT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("export_as=");
        printIdent(instr->ident_arg1);

        printf("\n");
        return;
    }
    case CREATE_GLOBAL_IC : {
        printf("%-20s    ", "CREATE_GLOBAL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        printf("\n");
        return;
    }
    case CREATE_FUNCTION_IC : {
        printf("%-20s    ", "CREATE_FUNCTION");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        printf("    args: ");
        for (int i = 0; i < instr->n_args; i++) {
            ident arg = instr->args[i];
            printIdent((arg << 4) >> 4);
            printf(", ");
        }

        printf("\n");
        return;
    }
    case CREATE_TYPE_IC : {
        printf("%-20s    ", "CREATE_TYPE");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        int64_t n_fields  = instr->args[0];
        int64_t n_methods = instr->args[1];

        printf("    fields: ");
        for (int i = 2; i < 2 + n_fields; i++) {
            printIdent(instr->args[i]);
            printf(", ");
        }

        printf("    methods: ");
        for (int i = 2 + n_fields; i < 2 + n_fields + n_methods; i++) {
            printIdent(instr->args[i]);
            printf(", ");
        }

        printf("\n");
        return;
    }
    case CREATE_METHOD_IC : {
        printf("%-20s    ", "CREATE_METHOD");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        printf("    args: ");
        for (int i = 0; i < instr->n_args; i++) {
            ident arg = instr->args[i];
            printIdent((arg << 4) >> 4);
            printf(", ");
        }

        printf("\n");
        return;
    }
    case CREATE_SCOPE_IC : {
        printf("%-20s    ", "CREATE_SCOPE");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf(instr->flags ? "WITH_PARENT_ACCESS" : "WITHOUT_PARENT_ACCESS");

        printf("\n");
        return;
    }
    case DESTROY_SCOPE_IC : {
        printf("%-20s    ", "DESTROY_SCOPE");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case JUMP_IF_FALSE_IC : {
        printf("%-20s    ", "JUMP_IF_FALSE");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("offset=%lld (abs=%lld)", instr->int_arg1, pos + instr->int_arg1);

        printf("\n");
        return;
    }
    case JUMP_IC : {
        printf("%-20s    ", "JUMP");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("offset=%lld (abs=%lld)", instr->int_arg1, pos + instr->int_arg1);

        printf("\n");
        return;
    }
    case RETURN_IC : {
        printf("%-20s    ", "RETURN");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case REGISTER_CATCH_IC : {
        printf("%-20s    ", "REGISTER_CATCH");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case DESTROY_CATCH_IC : {
        printf("%-20s    ", "DESTROY_CATCH");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("n=%lld", instr->int_arg1);

        printf("\n");
        return;
    }
    case SIGNAL_ERROR_IC : {
        printf("%-20s    ", "SIGNAL_ERROR");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case CREATE_VAR_IC : {
        printf("%-20s    ", "CREATE_VAR");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        printf("\n");
        return;
    }
    case COPY_IC : {
        printf("%-20s    ", "COPY_IC");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case ASSIGNMENT_IC : {
        printf("%-20s    ", "ASSIGNMENT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LOGICAL_OR_IC : {
        printf("%-20s    ", "LOGICAL_OR");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LOGICAL_AND_IC : {
        printf("%-20s    ", "LOGICAL_AND");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case BITWISE_OR_IC : {
        printf("%-20s    ", "BITWISE_OR");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case BITWISE_XOR_IC : {
        printf("%-20s    ", "BITWISE_XOR");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case BITWISE_AND_IC : {
        printf("%-20s    ", "BITWISE_AND");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case EQUAL_IC : {
        printf("%-20s    ", "EQUAL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case NOT_EQUAL_IC : {
        printf("%-20s    ", "NOT_EQUAL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LESS_THAN_IC : {
        printf("%-20s    ", "LESS_THAN");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LESS_EQUAL_IC : {
        printf("%-20s    ", "LESS_EQUAL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case GREATER_THAN_IC : {
        printf("%-20s    ", "GREATER_THAN");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case GREATER_EQUAL_IC : {
        printf("%-20s    ", "GREATER_EQUAL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case ADDITION_IC : {
        printf("%-20s    ", "ADDITION");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case SUBTRACTION_IC : {
        printf("%-20s    ", "SUBTRACTION");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LSHIFT_IC : {
        printf("%-20s    ", "LSHIFT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case RSHIFT_IC : {
        printf("%-20s    ", "RSHIFT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case MULTIPLICATION_IC : {
        printf("%-20s    ", "MULTIPLICATION");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case DIVISION_IC : {
        printf("%-20s    ", "DIVISION");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case REMAINDER_IC : {
        printf("%-20s    ", "REMAINDER");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case POSITIVE_IC : {
        printf("%-20s    ", "POSITIVE");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case NEGATION_IC : {
        printf("%-20s    ", "NEGATION");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case INVERTION_IC : {
        printf("%-20s    ", "INVERTION");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LOGICAL_NOT_IC : {
        printf("%-20s    ", "LOGICAL_NOT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case CALL_IC : {
        printf("%-20s    ", "CALL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("n=%lld", instr->int_arg1);

        printf("\n");
        return;
    }
    case ACCESS_IC : {
        printf("%-20s    ", "ACCESS");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LOAD_BOOL_IC : {
        printf("%-20s    ", "LOAD_BOOL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("value=%s", instr->int_arg1 ? "true" : "false");

        printf("\n");
        return;
    }
    case LOAD_CHAR_IC : {
        printf("%-20s    ", "LOAD_BOOL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("value=%s", getChar(instr->char_arg1));

        printf("\n");
        return;
    }
    case LOAD_INT_IC : {
        printf("%-20s    ", "LOAD_INT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("value=%lld", instr->int_arg1);

        printf("\n");
        return;
    }
    case LOAD_FLOAT_IC : {
        printf("%-20s    ", "LOAD_FLOAT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("value=%e", instr->float_arg1);

        printf("\n");
        return;
    }
    case LOAD_STRING_IC : {
        printf("%-20s    ", "LOAD_STRING");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("value=\"%s\"", instr->string_arg1);

        printf("\n");
        return;
    }
    case LOAD_NULL_IC : {
        printf("%-20s    ", "LOAD_NULL");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case LOAD_IC : {
        printf("%-20s    ", "LOAD");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        printf("\n");
        return;
    }
    case LOAD_FIELD_IC : {
        printf("%-20s    ", "LOAD_FIELD");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        printf("\n");
        return;
    }
    case LOAD_METHOD_IC : {
        printf("%-20s    ", "LOAD_METHOD");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("name=");
        printIdent(instr->ident_arg1);

        printf("\n");
        return;
    }
    case NEW_IC : {
        printf("%-20s    ", "NEW");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    case HALT_IC : {
        printf("%-20s    ", "HALT");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    default : {
        printf("%-20s    ", "INVALID");
        printf("lineno=%-4lld ", instr->lineno);
        printf("n_args=%-4lld ", instr->n_args);
        printf("env=%-4lld ", instr->env_id);

        printf("\n");
        return;
    }
    }
}

static int64_t instr_id = 0;

Instruction genInsPOP(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = POP_IC;
    return res;
}

Instruction genInsSWAP(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = SWAP_IC;
    return res;
}

Instruction genInsCREATE_ENV(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = CREATE_ENV_IC;
    return res;
}

Instruction genInsSWITCH_ENV_INS(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = SWITCH_ENV_INS_IC;
    return res;
}

Instruction genInsSWITCH_ENV_OBJ(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = SWITCH_ENV_OBJ_IC;
    return res;
}

Instruction genInsIMPORT_MODULE(char *filename, size_t lineno, int64_t env_id, char *module_path, ident name) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;

    res.code        = IMPORT_MODULE_IC;
    res.string_arg1 = module_path;
    res.n_args      = name;    // ugly and might brake things but ok
    return res;
}

Instruction genInsEXPORT_OBJECT(char *filename, size_t lineno, int64_t env_id, ident name) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code       = EXPORT_OBJECT_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genInsCREATE_GLOBAL(char *filename, size_t lineno, int64_t env_id, ident name) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code       = CREATE_GLOBAL_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genInsCREATE_FUNCTION(char *filename, size_t lineno, int64_t env_id, ident name, size_t n_args, ident *args) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;

    res.code       = CREATE_FUNCTION_IC;
    res.ident_arg1 = name;
    res.n_args     = n_args;
    res.args       = args;
    return res;
}

Instruction genInsCREATE_TYPE(char   *filename,
                              size_t  lineno,
                              int64_t env_id,
                              ident   name,
                              size_t  n_fields,
                              ident  *fields,
                              size_t  n_methods,
                              ident  *methods) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;

    res.code       = CREATE_TYPE_IC;
    res.ident_arg1 = name;
    res.n_args     = n_fields + n_methods + 2;
    res.args       = allocBytesOrError(res.n_args * sizeof(ident));
    res.args[0]    = (int64_t)n_fields;
    res.args[1]    = (int64_t)n_methods;
    memcpy(res.args + 2, fields, n_fields * sizeof(ident));
    memcpy(res.args + 2 + n_fields, methods, n_methods * sizeof(ident));

    freeBytes(fields);
    freeBytes(methods);
    return res;
}

Instruction genInsCREATE_METHOD(char *filename, size_t lineno, int64_t env_id, ident name, size_t n_args, ident *args) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;

    res.code       = CREATE_METHOD_IC;
    res.ident_arg1 = name;
    res.n_args     = n_args;
    res.args       = args;
    return res;
}

Instruction genInsCREATE_SCOPE(char *filename, size_t lineno, int64_t env_id, int8_t access_mode) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code  = CREATE_SCOPE_IC;
    res.flags = access_mode;
    return res;
}

Instruction genInsDESTROY_SCOPE(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = DESTROY_SCOPE_IC;
    return res;
}

Instruction genInsJUMP_IF_FALSE(char *filename, size_t lineno, int64_t env_id, int64_t offset) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code     = JUMP_IF_FALSE_IC;
    res.int_arg1 = offset;
    return res;
}

Instruction genInsJUMP(char *filename, size_t lineno, int64_t env_id, int64_t offset) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code     = JUMP_IC;
    res.int_arg1 = offset;
    return res;
}

Instruction genInsRETURN(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = RETURN_IC;
    return res;
}

Instruction genInsREGISTER_CATCH(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = REGISTER_CATCH_IC;
    return res;
}

Instruction genInsDESTROY_CATCH(char *filename, size_t lineno, int64_t env_id, int64_t n) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code     = DESTROY_CATCH_IC;
    res.int_arg1 = n;
    return res;
}

Instruction genInsSIGNAL_ERROR(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = SIGNAL_ERROR_IC;
    return res;
}

Instruction genInsCREATE_VAR(char *filename, size_t lineno, int64_t env_id, ident name) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code       = CREATE_VAR_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genInsCOPY(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = COPY_IC;
    return res;
}

Instruction genInsASSIGNMENT(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = ASSIGNMENT_IC;
    return res;
}

Instruction genInsLOGICAL_OR(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = LOGICAL_OR_IC;
    return res;
}

Instruction genInsLOGICAL_AND(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = LOGICAL_AND_IC;
    return res;
}

Instruction genInsBITWISE_OR(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = BITWISE_OR_IC;
    return res;
}

Instruction genInsBITWISE_XOR(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = BITWISE_XOR_IC;
    return res;
}

Instruction genInsBITWISE_AND(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = BITWISE_AND_IC;
    return res;
}

Instruction genInsEQUAL(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = EQUAL_IC;
    return res;
}

Instruction genInsNOT_EQUAL(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = NOT_EQUAL_IC;
    return res;
}

Instruction genInsLESS_THAN(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = LESS_THAN_IC;
    return res;
}

Instruction genInsLESS_EQUAL(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = LESS_EQUAL_IC;
    return res;
}

Instruction genInsGREATER_THAN(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = GREATER_THAN_IC;
    return res;
}

Instruction genInsGREATER_EQUAL(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = GREATER_EQUAL_IC;
    return res;
}

Instruction genInsADDITION(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = ADDITION_IC;
    return res;
}

Instruction genInsSUBTRACTION(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = SUBTRACTION_IC;
    return res;
}

Instruction genInsLSHIFT(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = LSHIFT_IC;
    return res;
}

Instruction genInsRSHIFT(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = RSHIFT_IC;
    return res;
}

Instruction genInsMULTIPLICATION(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = MULTIPLICATION_IC;
    return res;
}

Instruction genInsDIVISION(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = DIVISION_IC;
    return res;
}

Instruction genInsREMAINDER(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = REMAINDER_IC;
    return res;
}

Instruction genInsPOSITIVE(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = POSITIVE_IC;
    return res;
}

Instruction genInsNEGATION(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = NEGATION_IC;
    return res;
}

Instruction genInsINVERTION(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = INVERTION_IC;
    return res;
}

Instruction genInsLOGICAL_NOT(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = LOGICAL_NOT_IC;
    return res;
}

Instruction genInsCALL(char *filename, size_t lineno, int64_t env_id, int64_t n) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code     = CALL_IC;
    res.int_arg1 = n;
    return res;
}

Instruction genInsACCESS(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = ACCESS_IC;
    return res;
}

Instruction genInsLOAD_BOOL(char *filename, size_t lineno, int64_t env_id, int8_t value) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code     = LOAD_BOOL_IC;
    res.int_arg1 = value;
    return res;
}

Instruction genInsLOAD_CHAR(char *filename, size_t lineno, int64_t env_id, char value) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code      = LOAD_CHAR_IC;
    res.char_arg1 = value;
    return res;
}

Instruction genInsLOAD_INT(char *filename, size_t lineno, int64_t env_id, int64_t value) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code     = LOAD_INT_IC;
    res.int_arg1 = value;
    return res;
}

Instruction genInsLOAD_FLOAT(char *filename, size_t lineno, int64_t env_id, double value) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code       = LOAD_FLOAT_IC;
    res.float_arg1 = value;
    return res;
}

Instruction genInsLOAD_STRING(char *filename, size_t lineno, int64_t env_id, char *value) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code        = LOAD_STRING_IC;
    res.string_arg1 = value;
    return res;
}

Instruction genInsLOAD_NULL(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = LOAD_NULL_IC;
    return res;
}

Instruction genInsLOAD(char *filename, size_t lineno, int64_t env_id, ident name) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code       = LOAD_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genInsLOAD_FIELD(char *filename, size_t lineno, int64_t env_id, ident name) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code       = LOAD_FIELD_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genInsLOAD_METHOD(char *filename, size_t lineno, int64_t env_id, ident name) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code       = LOAD_METHOD_IC;
    res.ident_arg1 = name;
    return res;
}

Instruction genInsNEW(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = NEW_IC;
    return res;
}

Instruction genInsHALT(char *filename, size_t lineno, int64_t env_id) {
    Instruction res;
    res.id       = instr_id++;
    res.filename = filename;
    res.lineno   = lineno;
    res.env_id   = env_id;
    res.n_args   = 0;

    res.code = HALT_IC;
    return res;
}

ilist ilistCreate() {
    ilist res;
    res.head = res.tail = NULL;
    res.size            = 0;
    return res;
}

static void __inodeLink(inode *first, inode *second) {
    first->next = second;
}

void ilistLink(ilist *first, ilist *second) {
    first->size  += second->size;
    second->size  = 0;
    if (first->head == NULL) {
        first->head  = second->head;
        first->tail  = second->tail;
        second->head = second->tail = NULL;
        return;
    }

    if (second->head == NULL) {
        return;
    }

    __inodeLink(first->tail, second->head);
    first->tail  = second->tail;
    second->head = second->tail = NULL;
}

void ilistSwap(ilist *first, ilist *second) {
    ilist temp = *first;
    *first     = *second;
    *second    = temp;
}

void ilistAppend(ilist *list, Instruction ins) {
    inode *node = allocBytesOrError(sizeof(inode));
    node->ins   = ins;
    node->next  = NULL;

    if (list->head == NULL) {
        list->head = list->tail = node;
        list->size              = 1;
        return;
    }

    list->tail->next = node;
    list->tail       = node;
    list->size++;
}

void ilistDestroy(ilist *list) {
    inode *node = list->head;
    while (node != NULL) {
        inode *prev = node;
        node        = node->next;
        freeBytes(prev);
    }
}

static ilist gen(AstNode *node);

static size_t curEnvId;
#define info(node) (node)->filename, (node)->lineno, curEnvId

ilist genCompile(AstNode *node) {
    assert(node != NULL);

    // we assume that node is the root node of the entire program
    curEnvId     = envGenAvailableId();
    ilist result = ilistCreate();

    // will create an env with id curEnvId
    ilistAppend(&result, genInsCREATE_ENV(info(node)));
    ilistAppend(&result, genInsCREATE_SCOPE(info(node), 0));

    ilist tail = gen(node);
    ilistLink(&result, &tail);
    ilistAppend(&result, genInsDESTROY_SCOPE(info(node)));

    ilistAppend(&result, genInsHALT(info(node)));

    return result;
}

static ilist gen_program(AstNode *node);
static ilist gen_import_stmt(AstNode *node);
static ilist gen_export_stmt(AstNode *node);
static ilist gen_global_variable_stmt(AstNode *node);
static ilist gen_function_stmt(AstNode *node);
static ilist gen_parameter_list(AstNode *node);
static ilist gen_parameter_item(AstNode *node);
static ilist gen_type_stmt(AstNode *node);
static ilist gen_method_stmt(AstNode *node);
static ilist gen_constructor_stmt(AstNode *node);
static ilist gen_destructor_stmt(AstNode *node);
static ilist gen_stmt(AstNode *node);
static ilist gen_block_stmt(AstNode *node);
static ilist gen_stmt_list(AstNode *node);
static ilist gen_while_stmt(AstNode *node);
static ilist gen_for_stmt(AstNode *node);
static ilist gen_if_stmt(AstNode *node);
static ilist gen_continue_stmt(AstNode *node);
static ilist gen_break_stmt(AstNode *node);
static ilist gen_return_stmt(AstNode *node);
static ilist gen_try_catch_stmt(AstNode *node);
static ilist gen_signal_stmt(AstNode *node);
static ilist gen_var_stmt(AstNode *node);
static ilist gen_expr(AstNode *node);
static ilist gen_assignment(AstNode *node);
static ilist gen_inline_if(AstNode *node);
static ilist gen_new(AstNode *node);
static ilist gen_logical_or(AstNode *node);
static ilist gen_logical_and(AstNode *node);
static ilist gen_bitwise_or(AstNode *node);
static ilist gen_bitwise_xor(AstNode *node);
static ilist gen_bitwise_and(AstNode *node);
static ilist gen_equality(AstNode *node);
static ilist gen_relational(AstNode *node);
static ilist gen_sum(AstNode *node);
static ilist gen_bitwise_shift(AstNode *node);
static ilist gen_term(AstNode *node);
static ilist gen_prefix_op(AstNode *node);
static ilist gen_primary(AstNode *node);
static ilist gen_elementary(AstNode *node);
static ilist gen_literal(AstNode *node);
static ilist gen_module_path(AstNode *node);
static ilist gen_module_path_upwards(AstNode *node);
static ilist gen_module_path_compact(AstNode *node);
static ilist gen_expr_list(AstNode *node);

static ilist gen(AstNode *node) {
    assert(node != NULL);
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

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
    case GLOBAL_VARIABLE_STMT_NODE : {
        return gen_global_variable_stmt(node);
    }
    case FUNCTION_STMT_NODE : {
        return gen_function_stmt(node);
    }
    case TYPE_STMT_NODE : {
        return gen_type_stmt(node);
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
    case TRY_CATCH_STMT_NODE : {
        return gen_try_catch_stmt(node);
    }
    case SIGNAL_STMT_NODE : {
        return gen_signal_stmt(node);
    }
    case VAR_STMT_NODE : {
        return gen_var_stmt(node);
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
    default : {
        return ilistCreate();
    }
    }
}

static int64_t ctx_open_scopes_since_function = 0;
static int     ctx_is_inside_function         = 0;

static cvector_vector_type(int64_t) ctx_open_scopes_since_loop = NULL;

static ilist gen_program(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    switch (node->option) {
    case NO_OPTION : {
        /*
        >

        root of the entire program. no action needed, it is handled in genCompile

        <
        */
        return ilistCreate();
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
        ilistLink(&output, &temp);

        temp = gen(something);
        ilistLink(&output, &temp);

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
            char  *id = symtabIdentToString(body->nodes[0]->ident_value);
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

static ilist gen_import_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > IMPORT module_path AS IDENTIFIER

    module_path is constructed using dfs

    < IMPORT_MODULE module_path IDENTIFIER
    */

    charvec module_path = NULL;
    constructModulePath(node->nodes[0], &module_path);
    cvector_push_back(module_path, '\0');                                      // for copying

    Instruction ins = genInsIMPORT_MODULE(info(node), strdup(module_path), node->nodes[1]->ident_value);
    ins.flags       = node->nodes[0]->option == MODULE_PATH_COMPACT_OPTION;    // disgusting, but it works

    ilistAppend(&output, ins);

    return output;
}

static ilist gen_export_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > EXPORT e1 as n1, ..., ek as nk

    < gen(e1)
    < EXPORT_OBJECT n1
    ...
    < gen(ek)
    < EXPORT_OBJECT nk
    */

    AstNode *list = node->nodes[0];
    while (list != NULL) {
        AstNode *export_item = list->nodes[0];
        temp                 = gen(export_item->nodes[0]);
        ilistLink(&output, &temp);

        ilistAppend(&output, genInsEXPORT_OBJECT(info(node), export_item->nodes[1]->ident_value));

        if (list->n_nodes == 2) {
            list = list->nodes[1];
        }
        else {
            list = NULL;
        }
    }

    return output;
}

static ilist gen_global_variable_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > GLOBAL a, b, c, d

    < CREATE_GLOBAL a
    ...
    < CREATE_GLOBAL d
    */

    AstNode *list = node->nodes[0];
    while (list != NULL) {
        AstNode *global_item = list->nodes[0];

        ilistAppend(&output, genInsCREATE_GLOBAL(info(node), global_item->ident_value));

        if (list->n_nodes == 2) {
            list = list->nodes[1];
        }
        else {
            list = NULL;
        }
    }

    return output;
}

static ilist gen_function_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > FUNCTION name '(' m1 p1 ... mn pn ')' block_stmt

    < CREATE_FUNCTION name m1 p1 ... mn pn
    < JUMP REL@1
    < gen(block_stmt)
    < LOAD_NULL
    < SWAP
    < RETURN
    1
    */

    struct AstNode *name       = node->nodes[0];
    struct AstNode *args       = node->nodes[1];
    struct AstNode *block_stmt = node->nodes[2];

    cvector_vector_type(ident) params = NULL;
    while (args != NULL) {
        struct AstNode *item  = args->nodes[0];
        ident           value = item->nodes[0]->ident_value;

        cvector_push_back(params, value);

        if (args->n_nodes == 2) {
            args = args->nodes[1];
        }
        else {
            args = NULL;
        }
    }
    size_t n_args = cvector_size(params);
    ident *margs  = allocBytesOrError(sizeof(ident) * n_args);
    memcpy(margs, params, sizeof(ident) * n_args);
    cvector_free(params);

    ilistAppend(&output, genInsCREATE_FUNCTION(info(node), name->ident_value, n_args, margs));

    char *name_str = symtabIdentToString(node->ident_value);

    if (strcmp(name_str, "constructor") == 0 || strcmp(name_str, "destructor") == 0) {
        // should print an error. however, i dont yet have a way to handle compile time errors
        // so let's lust set instruction flag as FAILURE, so that an error gets signalled during runtime
        output.tail->ins.flags = 1;    // failure
    }

    ctx_is_inside_function         = 1;
    ctx_open_scopes_since_function = 0;
    ilist block                    = gen(block_stmt);
    ctx_is_inside_function         = 0;
    ctx_is_inside_function         = 0;

    ilistAppend(&output, genInsJUMP(info(node), block.size + 4));

    ilistLink(&output, &block);

    ilistAppend(&output, genInsLOAD_NULL(info(node)));
    ilistAppend(&output, genInsSWAP(info(node)));
    ilistAppend(&output, genInsRETURN(info(node)));

    return output;
}

extern Symtab *lex_symtab;

static ilist gen_type_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > type name {f1 ... fn m1 ... mk}

    < CREATE_TYPE name n k f1 ... fn m1 ... mn
    */

    AstNode *name = node->nodes[0];

    cvector_vector_type(ident) fields  = NULL;
    cvector_vector_type(ident) methods = NULL;

    cvector_push_back(methods, symtabInsert(lex_symtab, "constructor"));
    cvector_push_back(methods, symtabInsert(lex_symtab, "destructor"));
    AstNode *params = node->nodes[1];
    while (params != NULL) {
        AstNode *item = params->nodes[0];

        if (item->option == MEMBER_METHOD_OPTION) {
            cvector_push_back(methods, item->nodes[0]->ident_value);
        }
        else {
            cvector_push_back(fields, item->nodes[0]->ident_value);
        }

        if (params->n_nodes == 2) {
            params = params->nodes[1];
        }
        else {
            params = NULL;
        }
    }

    ident *fields_copy = allocBytesOrError(cvector_size(fields) * sizeof(ident));
    memcpy(fields_copy, fields, cvector_size(fields) * sizeof(ident));
    ident *methods_copy = allocBytesOrError(cvector_size(methods) * sizeof(ident));
    memcpy(methods_copy, methods, cvector_size(methods) * sizeof(ident));

    ilistAppend(
    &output,
    genInsCREATE_TYPE(info(node), name->ident_value, cvector_size(fields), fields_copy, cvector_size(methods), methods_copy));

    cvector_free(fields);
    cvector_free(methods);
    return output;
}

extern Symtab *lex_symtab;

static ilist gen_method_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > method name '(' m1 p1 ... mn pn ')' of type block_stmt

    > LOAD type
    < CREATE_METHOD name ref 'this' m1 p1 ... mn pn
    < JUMP REL@1
    < gen(block_stmt)
    < LOAD_NULL
    < SWAP
    < RETURN
    1
    */

    struct AstNode *name       = node->nodes[0];
    struct AstNode *args       = node->nodes[1];
    struct AstNode *type       = node->nodes[2];
    struct AstNode *block_stmt = node->nodes[3];

    cvector_vector_type(ident) params = NULL;
    cvector_push_back(params, symtabInsert(lex_symtab, "this"));

    while (args != NULL) {
        struct AstNode *item  = args->nodes[0];
        ident           value = item->nodes[0]->ident_value;

        cvector_push_back(params, value);

        if (args->n_nodes == 2) {
            args = args->nodes[1];
        }
        else {
            args = NULL;
        }
    }
    size_t n_args = cvector_size(params);
    ident *margs  = allocBytesOrError(sizeof(ident) * n_args);
    memcpy(margs, params, sizeof(ident) * n_args);
    cvector_free(params);

    ilistAppend(&output, genInsLOAD(info(node), type->ident_value));

    ilistAppend(&output, genInsCREATE_METHOD(info(node), name->ident_value, n_args, margs));

    ctx_is_inside_function         = 1;
    ctx_open_scopes_since_function = 0;
    ilist block                    = gen(block_stmt);
    ctx_is_inside_function         = 0;
    ctx_is_inside_function         = 0;

    ilistAppend(&output, genInsJUMP(info(node), block.size + 4));

    ilistLink(&output, &block);

    ilistAppend(&output, genInsLOAD_NULL(info(node)));
    ilistAppend(&output, genInsSWAP(info(node)));
    ilistAppend(&output, genInsRETURN(info(node)));

    return output;
}

static ilist gen_constructor_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > constructor '(' m1 p1 ... mn pn ')' of type block_stmt

    > LOAD type
    < CREATE_METHOD 'constructor' ref 'this' m1 p1 ... mn pn
    < JUMP REL@1
    < gen(block_stmt)
    < LOAD_NULL
    < SWAP
    < RETURN
    1
    */

    struct AstNode *args       = node->nodes[0];
    struct AstNode *type       = node->nodes[1];
    struct AstNode *block_stmt = node->nodes[2];

    cvector_vector_type(ident) params = NULL;
    cvector_push_back(params, symtabInsert(lex_symtab, "this"));

    while (args != NULL) {
        struct AstNode *item  = args->nodes[0];
        ident           value = item->nodes[0]->ident_value;

        cvector_push_back(params, value);

        if (args->n_nodes == 2) {
            args = args->nodes[1];
        }
        else {
            args = NULL;
        }
    }
    size_t n_args = cvector_size(params);
    ident *margs  = allocBytesOrError(sizeof(ident) * n_args);
    memcpy(margs, params, sizeof(ident) * n_args);
    cvector_free(params);

    ilistAppend(&output, genInsLOAD(info(node), type->ident_value));

    ilistAppend(&output, genInsCREATE_METHOD(info(node), symtabInsert(lex_symtab, "constructor"), n_args, margs));

    ctx_is_inside_function         = 1;
    ctx_open_scopes_since_function = 0;
    ilist block                    = gen(block_stmt);
    ctx_is_inside_function         = 0;
    ctx_is_inside_function         = 0;

    ilistAppend(&output, genInsJUMP(info(node), block.size + 4));

    ilistLink(&output, &block);

    ilistAppend(&output, genInsLOAD_NULL(info(node)));
    ilistAppend(&output, genInsSWAP(info(node)));
    ilistAppend(&output, genInsRETURN(info(node)));

    return output;
}

static ilist gen_destructor_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > destructor of type block_stmt

    > LOAD type
    < CREATE_METHOD 'destructor' ref 'this'
    < JUMP REL@1
    < gen(block_stmt)
    < LOAD_NULL
    < SWAP
    < RETURN
    1
    */

    struct AstNode *type       = node->nodes[0];
    struct AstNode *block_stmt = node->nodes[1];

    cvector_vector_type(ident) params = NULL;
    cvector_push_back(params, symtabInsert(lex_symtab, "this"));

    size_t n_args = cvector_size(params);
    ident *margs  = allocBytesOrError(sizeof(ident) * n_args);
    memcpy(margs, params, sizeof(ident) * n_args);
    cvector_free(params);

    ilistAppend(&output, genInsLOAD(info(node), type->ident_value));

    ilistAppend(&output, genInsCREATE_METHOD(info(node), symtabInsert(lex_symtab, "destructor"), n_args, margs));

    ctx_is_inside_function         = 1;
    ctx_open_scopes_since_function = 0;
    ilist block                    = gen(block_stmt);
    ctx_is_inside_function         = 0;
    ctx_is_inside_function         = 0;

    ilistAppend(&output, genInsJUMP(info(node), block.size + 4));

    ilistLink(&output, &block);

    ilistAppend(&output, genInsLOAD_NULL(info(node)));
    ilistAppend(&output, genInsSWAP(info(node)));
    ilistAppend(&output, genInsRETURN(info(node)));

    return output;
}

static ilist gen_stmt(AstNode *node) {
    // i wish all code was like this....
    // ^ well no one restricts you, so go ahead, wish as much as you want lol

    /*

    > something OR something ';'

    if it is an expression, we have to pop the object because otherwise it will break things

    < gen(something)
    < POP if expr

    */

    ilist res = gen(node->nodes[0]);
    if (node->option == EXPR_OPTION) {
        ilistAppend(&res, genInsPOP(info(node)));
    }
    return res;
}

static ilist gen_block_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();
    /*
    > '{' stmt '}'
    < CREATE_SCOPE WITH_PARENT_ACCESS
    < gen(stmt)
    < DESTROY_SCOPE

    or

    > '{' '}'
    <
    */

    if (node->n_nodes == 1) {
        ilistAppend(&output, genInsCREATE_SCOPE(info(node), 1));

        if (!cvector_empty(ctx_open_scopes_since_loop)) {
            (*cvector_back(ctx_open_scopes_since_loop))++;
        }

        ctx_open_scopes_since_function++;

        temp = gen(node->nodes[0]);

        if (!cvector_empty(ctx_open_scopes_since_loop)) {
            (*cvector_back(ctx_open_scopes_since_loop))--;
        }

        ctx_open_scopes_since_function--;

        ilistLink(&output, &temp);

        ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));
        return output;
    }

    return ilistCreate();
}

static ilist gen_stmt_list(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();
    /*
    > s1 ... sn
    < gen(s1)
    ...
    < gen(sn)
    */

    while (node != NULL) {
        temp = gen(node->nodes[0]);
        ilistLink(&output, &temp);

        if (node->n_nodes == 2) {
            node = node->nodes[1];
        }
        else {
            node = NULL;
        }
    }
    return output;
}

static ilist gen_while_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    > while e s

    1 gen(e)
    < JUMP_IF_FALSE REL@2
    < gen(s)
    < JUMP REL@1
    2

    also we have to handle continue/break statements
    they are JUMP statements with offset=0 and LOOP_CONTINUE_FLAG / LOOP_BREAK_FLAG
    */

    cvector_push_back(ctx_open_scopes_since_loop, 0);

    ilist e = gen(node->nodes[0]);
    ilist s = gen(node->nodes[1]);

    int64_t total = e.size + s.size;

    ilistLink(&output, &e);
    ilistAppend(&output, genInsJUMP_IF_FALSE(info(node->nodes[0]), s.size + 2));
    ilistLink(&output, &s);
    ilistAppend(&output, genInsJUMP(info(node), -(total + 1)));

    cvector_pop_back(ctx_open_scopes_since_loop);

    int64_t offset = 0;
    for (inode *nd = output.head; nd->next != NULL; nd = nd->next, offset++) {
        Instruction *ins = &nd->ins;
        if (ins->code != JUMP_IC || ins->int_arg1 != 0) {
            continue;
        }

        if (ins->flags == LOOP_CONTINUE_FLAG) {
            ins->int_arg1 = -offset;
        }
        else if (ins->flags == LOOP_BREAK_FLAG) {
            ins->int_arg1 = (int64_t)output.size - offset;
        }
        else {
            molalog("Strange instruction (JUMP, offset = 0) in %s, line %d\n", ins->filename, ins->lineno);
        }
    }

    return output;
}

static ilist gen_for_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    AstNode *init = node->nodes[0];    // may be NULL
    AstNode *cond = node->nodes[1];    // may be NULL
    AstNode *step = node->nodes[2];    // may be NULL
    AstNode *stmt = node->nodes[3];

    if (cond != NULL) {
        /*
        > for init; cond; step stmt

        <   CREATE_SCOPE WITH_PARENT_ACCESS
        <   gen(init)
        1   gen(cond)
        <   JUMP_IF_FALSE REL@2
        <   gen(stmt)
        <   gen(step)
        <   JUMP REL@1
        2   DESTROY_SCOPE

        also we have to handle continue/break statements
        they are JUMP statements with offset=0 and LOOP_CONTINUE_FLAG / LOOP_BREAK_FLAG
        */
        cvector_push_back(ctx_open_scopes_since_loop, 1);
        ctx_open_scopes_since_function++;

        ilist ini = init != NULL ? gen(init) : ilistCreate();
        ilist con = cond != NULL ? gen(cond) : ilistCreate();
        ilist ste = step != NULL ? gen(step) : ilistCreate();
        ilist stm = stmt != NULL ? gen(stmt) : ilistCreate();

        int64_t stmsize = stm.size;
        int64_t stesize = ste.size;
        int64_t consize = con.size;

        ilistAppend(&output, genInsCREATE_SCOPE(info(node), 1));
        ilistLink(&output, &ini);
        ilistLink(&output, &con);
        ilistAppend(&output, genInsJUMP_IF_FALSE(info(cond), stmsize + stesize + 2));
        ilistLink(&output, &stm);
        ilistLink(&output, &ste);
        ilistAppend(&output, genInsJUMP(info(node), -((int64_t)stesize + stmsize + 1 + consize)));
        ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));

        ctx_open_scopes_since_function--;
        cvector_pop_back(ctx_open_scopes_since_loop);

        int64_t offset = 0;
        for (inode *nd = output.head; nd->next != NULL; nd = nd->next, offset++) {
            Instruction *ins = &nd->ins;
            if (ins->code != JUMP_IC || ins->int_arg1 != 0) {
                continue;
            }

            if (ins->flags == LOOP_CONTINUE_FLAG) {
                ins->int_arg1 = -offset + 1 + ini.size;
            }
            else if (ins->flags == LOOP_BREAK_FLAG) {
                ins->int_arg1 = (int64_t)output.size - offset - 1;
            }
            else {
                molalog("Strange instruction (JUMP, offset = 0) in %s, line %d\n", ins->filename, ins->lineno);
            }
        }

        return output;
    }

    /*
    > for init; ; step stmt

    <   CREATE_SCOPE WITH_PARENT_ACCESS
    <   gen(init)
    1   gen(stmt)
    <   gen(step)
    <   JUMP REL@1
    <   DESTROY_SCOPE

    also we have to handle continue/break statements
    they are JUMP statements with offset=0 and LOOP_CONTINUE_FLAG / LOOP_BREAK_FLAG
    */
    cvector_push_back(ctx_open_scopes_since_loop, 1);
    ctx_open_scopes_since_function++;

    ilist ini = init != NULL ? gen(init) : ilistCreate();
    ilist ste = step != NULL ? gen(step) : ilistCreate();
    ilist stm = stmt != NULL ? gen(stmt) : ilistCreate();

    int64_t stmsize = stm.size;
    int64_t stesize = ste.size;
    int64_t inisize = ini.size;

    ilistAppend(&output, genInsCREATE_SCOPE(info(node), 1));
    ilistLink(&output, &ini);
    ilistLink(&output, &stm);
    ilistLink(&output, &ste);
    ilistAppend(&output, genInsJUMP(info(node), -((int64_t)stesize + stmsize)));
    ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));

    ctx_open_scopes_since_function--;
    cvector_pop_back(ctx_open_scopes_since_loop);

    int64_t offset = 0;
    for (inode *nd = output.head; nd->next != NULL; nd = nd->next, offset++) {
        Instruction *ins = &nd->ins;
        if (ins->code != JUMP_IC || ins->int_arg1 != 0) {
            continue;
        }

        if (ins->flags == LOOP_CONTINUE_FLAG) {
            ins->int_arg1 = -offset + 1 + inisize;
        }
        else if (ins->flags == LOOP_BREAK_FLAG) {
            ins->int_arg1 = (int64_t)output.size - offset - 1;
        }
        else {
            molalog("Strange instruction (JUMP, offset = 0) in %s, line %d\n", ins->filename, ins->lineno);
        }
    }

    return output;
}

static ilist gen_if_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    AstNode *cond       = node->nodes[0];
    AstNode *block      = node->nodes[1];
    AstNode *else_block = node->nodes[2];

    if (else_block != NULL) {
        /*
        >   if cond block else else_block

        <   gen(cond)
        <   JUMP_IF_FALSE REL@1
        <   gen(block)
        <   JUMP REL@2
        1   gen(else_block)
        2
        */

        ilist gen_cond       = gen(cond);
        ilist gen_block      = gen(block);
        ilist gen_else_block = gen(else_block);

        ilistLink(&output, &gen_cond);
        ilistAppend(&output, genInsJUMP_IF_FALSE(info(cond), gen_block.size + 2));
        ilistLink(&output, &gen_block);
        ilistAppend(&output, genInsJUMP(info(node), gen_else_block.size + 1));
        ilistLink(&output, &gen_else_block);

        return output;
    }

    /*
    >   if cond block

    <   gen(cond)
    <   JUMP_IF_FALSE REL@1
    <   gen(block)
    1
    */

    ilist gen_cond  = gen(cond);
    ilist gen_block = gen(block);

    ilistLink(&output, &gen_cond);
    ilistAppend(&output, genInsJUMP_IF_FALSE(info(cond), gen_block.size + 1));
    ilistLink(&output, &gen_block);

    return output;
}

static ilist gen_continue_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    >   continue

    <   DESTROY_SCOPE
        ...
    <   DESTROY_SCOPE
    <   JUMP REL@...?

    */

    if (cvector_empty(ctx_open_scopes_since_loop)) {
        return output;
    }

    for (int64_t i = 0; i < *cvector_back(ctx_open_scopes_since_loop); i++) {
        ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));
    }
    Instruction i = genInsJUMP(info(node), 0);
    i.flags       = LOOP_CONTINUE_FLAG;    // will be handled later
    ilistAppend(&output, i);

    return output;
}

static ilist gen_break_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    >   break

    <   DESTROY_SCOPE
        ...
    <   DESTROY_SCOPE
    <   JUMP REL@...?

    */

    if (cvector_empty(ctx_open_scopes_since_loop)) {
        return output;
    }

    for (int64_t i = 0; i < *cvector_back(ctx_open_scopes_since_loop); i++) {
        ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));
    }
    Instruction i = genInsJUMP(info(node), 0);
    i.flags       = LOOP_BREAK_FLAG;    // will be handled later
    ilistAppend(&output, i);

    return output;
}

static ilist gen_return_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (!ctx_is_inside_function) {
        return output;
    }

    /*
    >   return mode expr

    calling a function always creates an additional scope
    which serves only one function: forbid parent access
    therefore that scope will be destroyed, so SWAP is necessary

    <   gen(expr)
    <   DESTROY_SCOPE
        ...
    <   DESTROY_SCOPE
    <   COPY_BY_mode // if mode != pass
    <   SWAP
    <   RETURN
    */

    temp = gen(node->nodes[0]);
    ilistLink(&output, &temp);

    for (int64_t i = 0; i < ctx_open_scopes_since_function; i++) {
        ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));
    }

    ilistAppend(&output, genInsCOPY(info(node)));

    ilistAppend(&output, genInsSWAP(info(node)));
    ilistAppend(&output, genInsRETURN(info(node)));

    return output;
}

static ilist gen_try_catch_stmt(AstNode *node) {
    ilist output  = ilistCreate();
    ilist temp    = ilistCreate();
    ilist handler = ilistCreate();

    /*
    Kowalski, Analysis!

    >   try try_stmt
    >   catch expr1 as name1 catch_stmt1
    >   ...
    >   catch exprk as namek catch_stmtk
    >   catch * as namef catch_stmtf

    Handlers are generated in reversed order (final, k, ..., 1)
    This is needed because handlers are crated on the stack, meaning
    that the order of them is reversed. - * - = +

    Handler:
    >   gen(expr)            // LOAD_INT -1 if final (universal) handler
    >   REGISTER_CATCH
    >   JUMP REL@1
    >   DESTROY_CATCH 1  // current one
    >   SWITCH_ENV_INS
    >   CREATE_SCOPE    WITH_PARENT_ACCESS
    >   CREATE_VAR name
    >   gen(block_stmt)
    >   DESTROY_SCOPE
    >   DESTROY_CATCH *total handlers - pos of this one*    // all others
    >   JUMP REL@*first instruction after the try-catch statement* = X
    1

    Each handler must destroy all other handlers after successful execution.
    If an error happens inside the handler, the vm will jump to the "next" one
    which is going to be right above this one.

    The last instructions are:
    >   gen(try_block)
    >   DESTROY_CATCH *total number of handlers*
    X

    */

    AstNode *try_stmt        = node->nodes[0];
    AstNode *handlers_list   = node->nodes[1];
    AstNode *universal_name  = node->nodes[2];
    AstNode *universal_block = node->nodes[3];

    int64_t  n_handlers = universal_name != NULL;
    AstNode *tnode      = handlers_list;
    while (tnode != NULL) {
        n_handlers++;
        if (tnode->n_nodes == 2) {
            tnode = tnode->nodes[1];
        }
        else {
            tnode = NULL;
        }
    }

    // try_stmt
    temp = gen(try_stmt);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsDESTROY_CATCH(info(node), n_handlers));

    int64_t handler_index = 0;

    // normal handlers
    tnode = handlers_list;
    while (tnode != NULL) {
        handler_index++;
        AstNode *item       = tnode->nodes[0];
        AstNode *expr_node  = item->nodes[0];
        AstNode *name_node  = item->nodes[1];
        AstNode *block_node = item->nodes[2];

        ilist expr  = gen(expr_node);
        ilist block = gen(block_node);

        ilistLink(&handler, &expr);
        ilistAppend(&handler, genInsREGISTER_CATCH(info(name_node)));
        ilistAppend(&handler, genInsJUMP(info(block_node), 7 + block.size + 1));
        ilistAppend(&handler, genInsDESTROY_CATCH(info(block_node), 1));
        ilistAppend(&handler, genInsSWITCH_ENV_INS(info(block_node)));
        ilistAppend(&handler, genInsCREATE_SCOPE(info(block_node), 1));
        ilistAppend(&handler, genInsCREATE_VAR(info(name_node), name_node->ident_value));
        ilistLink(&handler, &block);
        ilistAppend(&handler, genInsDESTROY_SCOPE(info(block_node)));
        ilistAppend(&handler, genInsDESTROY_CATCH(info(block_node), n_handlers - handler_index));
        ilistAppend(&handler, genInsJUMP(info(block_node), output.size + 1));

        ilistLink(&handler, &output);
        ilistSwap(&handler, &output);

        if (tnode->n_nodes == 2) {
            tnode = tnode->nodes[1];
        }
        else {
            tnode = NULL;
        }
    }

    // universal handler
    if (universal_name != NULL) {
        ilist block = gen(universal_block);

        ilistAppend(&handler, genInsLOAD_INT(info(universal_name), -1));
        ilistAppend(&handler, genInsREGISTER_CATCH(info(universal_name)));
        ilistAppend(&handler, genInsJUMP(info(universal_block), 7 + block.size + 1));
        ilistAppend(&handler, genInsDESTROY_CATCH(info(universal_block), 1));
        ilistAppend(&handler, genInsSWITCH_ENV_INS(info(universal_block)));
        ilistAppend(&handler, genInsCREATE_SCOPE(info(universal_block), 1));
        ilistAppend(&handler, genInsCREATE_VAR(info(universal_name), universal_name->ident_value));
        ilistLink(&handler, &block);
        ilistAppend(&handler, genInsDESTROY_SCOPE(info(universal_block)));
        ilistAppend(&handler, genInsJUMP(info(universal_block), output.size + 1));

        ilistLink(&handler, &output);
        ilistSwap(&handler, &output);
    }

    return output;
}

static ilist gen_signal_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    >   signal a because b

    <   gen(b)
    <   gen(a)
    <   SIGNAL_ERROR
    */

    temp = gen(node->nodes[1]);
    ilistLink(&output, &temp);

    temp = gen(node->nodes[0]);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsSIGNAL_ERROR(info(node)));

    return output;
}

static ilist gen_var_stmt(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    /*
    >   var a = b, c = d, ..., e, ...

    <   gen(b)
    <   COPY_BY_AUTO
    <   CREATE_VAR a
    <   gen(d)
    <   COPY_BY_AUTO
    <   CREATE_VAR c
        ...
    <   LOAD_NULL
    <   CREATE_VAR e
        ...
    */

    AstNode *list = node->nodes[0];

    while (list != NULL) {
        AstNode *item = list->nodes[0];

        if (item->nodes[1] == NULL) {
            ilistAppend(&output, genInsLOAD_NULL(info(item)));
            ilistAppend(&output, genInsCREATE_VAR(info(item), item->nodes[0]->ident_value));
        }
        else {
            temp = gen(item->nodes[1]);
            ilistLink(&output, &temp);
            ilistAppend(&output, genInsCOPY(info(item)));
            ilistAppend(&output, genInsCREATE_VAR(info(item), item->nodes[0]->ident_value));
        }

        if (list->n_nodes == 2) {
            list = list->nodes[1];
        }
        else {
            list = NULL;
        }
    }

    return output;
}

static ilist gen_expr(AstNode *node) {
    return gen_assignment(node->nodes[0]);    // satisfaction
}

static ilist gen_assignment(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == INLINE_IF_OPTION) {
        return gen_inline_if(node->nodes[0]);
    }

    /*
    > A = B

    < gen(B)
    < COPY_BY_AUTO
    < gen(A)
    < ASSIGNMENT
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_assignment(B);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsCOPY(info(node)));

    temp = gen_inline_if(A);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsASSIGNMENT(info(node)));

    return output;
}

static ilist gen_inline_if(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == NEW_OPTION) {
        return gen_new(node->nodes[0]);
    }

    /*
    > when A then B else C

    < gen(A)
    < JUMP_IF_FALSE REL@1
    < gen(B)
    < JUMP REL@2
    1 gen(C)
    2
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];
    AstNode *C = node->nodes[2];

    ilist a = gen_new(A);
    ilist b = gen_new(B);
    ilist c = gen_new(C);

    ilistLink(&output, &a);
    ilistAppend(&output, genInsJUMP_IF_FALSE(info(node), b.size + 2));
    ilistLink(&output, &b);
    ilistAppend(&output, genInsJUMP(info(node), c.size + 1));
    ilistLink(&output, &c);

    return output;
}

static ilist gen_new(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == LOGICAL_OR_OPTION) {
        return gen_logical_or(node->nodes[0]);
    }

    /*
    >   new A (B1 ... Bn)

    <   gen(B_1)
        ...
    <   gen(B_n)
    <   gen(A)
    <   NEW
    <   LOAD_METHOD constructor
    <   SWITCH_ENV *env of the function A*
    <   CREATE_SCOPE WITHOUT_PARENT_ACCESS
    <   CALL n
    <   DESTROY_SCOPE
    <   SWITCH_ENV
    */

    int64_t n = 0;
    if (node->n_nodes == 2) {
        temp = gen_expr_list(node->nodes[1]);
        ilistLink(&output, &temp);

        AstNode *args = node->nodes[1];

        while (args != NULL) {
            temp = gen(args->nodes[0]);
            n++;

            if (args->n_nodes == 2) {
                args = args->nodes[1];
            }
            else {
                args = NULL;
            }
        }
    }

    temp = gen_elementary(node->nodes[0]);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsNEW(info(node)));
    ilistAppend(&output, genInsLOAD_METHOD(info(node), symtabInsert(lex_symtab, "constructor")));
    ilistAppend(&output, genInsSWITCH_ENV_OBJ(info(node)));
    ilistAppend(&output, genInsCREATE_SCOPE(info(node), 0));
    ilistAppend(&output, genInsCALL(info(node), n));
    ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));
    ilistAppend(&output, genInsSWITCH_ENV_INS(info(node)));

    return output;
}

static ilist gen_logical_or(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == LOGICAL_AND_OPTION) {
        return gen_logical_and(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_logical_or(A);
    ilistLink(&output, &temp);

    temp = gen_logical_and(B);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsLOGICAL_OR(info(node)));

    return output;
}

static ilist gen_logical_and(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == BITWISE_OR_OPTION) {
        return gen_bitwise_or(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_logical_and(A);
    ilistLink(&output, &temp);

    temp = gen_bitwise_or(B);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsLOGICAL_AND(info(node)));

    return output;
}

static ilist gen_bitwise_or(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == BITWISE_XOR_OPTION) {
        return gen_bitwise_xor(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_bitwise_or(A);
    ilistLink(&output, &temp);

    temp = gen_bitwise_xor(B);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsBITWISE_XOR(info(node)));

    return output;
}

static ilist gen_bitwise_xor(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == BITWISE_AND_OPTION) {
        return gen_bitwise_and(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_bitwise_xor(A);
    ilistLink(&output, &temp);

    temp = gen_bitwise_and(B);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsBITWISE_XOR(info(node)));

    return output;
}

static ilist gen_bitwise_and(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == EQUALITY_OPTION) {
        return gen_equality(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_bitwise_and(A);
    ilistLink(&output, &temp);

    temp = gen_equality(B);
    ilistLink(&output, &temp);

    ilistAppend(&output, genInsBITWISE_AND(info(node)));

    return output;
}

static ilist gen_equality(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == RELATIONAL_OPTION) {
        return gen_relational(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_equality(A);
    ilistLink(&output, &temp);

    temp = gen_relational(B);
    ilistLink(&output, &temp);

    if (node->option == EQUAL_OPTION) {
        ilistAppend(&output, genInsEQUAL(info(node)));
    }
    else {
        ilistAppend(&output, genInsNOT_EQUAL(info(node)));
    }

    return output;
}

static ilist gen_relational(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == SUM_OPTION) {
        return gen_sum(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_relational(A);
    ilistLink(&output, &temp);

    temp = gen_sum(B);
    ilistLink(&output, &temp);

    if (node->option == LESS_EQUAL_OPTION) {
        ilistAppend(&output, genInsLESS_EQUAL(info(node)));
    }
    else if (node->option == GREATER_EQUAL_OPTION) {
        ilistAppend(&output, genInsGREATER_EQUAL(info(node)));
    }
    else if (node->option == LESS_THAN_OPTION) {
        ilistAppend(&output, genInsLESS_THAN(info(node)));
    }
    else {
        ilistAppend(&output, genInsGREATER_THAN(info(node)));
    }

    return output;
}

static ilist gen_sum(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == BITWISE_SHIFT_OPTION) {
        return gen_bitwise_shift(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_sum(A);
    ilistLink(&output, &temp);

    temp = gen_bitwise_shift(B);
    ilistLink(&output, &temp);

    if (node->option == ADDITION_OPTION) {
        ilistAppend(&output, genInsADDITION(info(node)));
    }
    else {
        ilistAppend(&output, genInsSUBTRACTION(info(node)));
    }

    return output;
}

static ilist gen_bitwise_shift(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == TERM_OPTION) {
        return gen_term(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_bitwise_shift(A);
    ilistLink(&output, &temp);

    temp = gen_term(B);
    ilistLink(&output, &temp);

    if (node->option == LSHIFT_OPTION) {
        ilistAppend(&output, genInsLSHIFT(info(node)));
    }
    else {
        ilistAppend(&output, genInsRSHIFT(info(node)));
    }

    return output;
}

static ilist gen_term(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == PREFIX_OP_OPTION) {
        return gen_prefix_op(node->nodes[0]);
    }

    /*
    > A op B

    < gen(A)
    < gen(B)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    temp = gen_term(A);
    ilistLink(&output, &temp);

    temp = gen_prefix_op(B);
    ilistLink(&output, &temp);

    if (node->option == MULTIPLICATION_OPTION) {
        ilistAppend(&output, genInsMULTIPLICATION(info(node)));
    }
    else if (node->option == DIVISION_OPTION) {
        ilistAppend(&output, genInsDIVISION(info(node)));
    }
    else {
        ilistAppend(&output, genInsREMAINDER(info(node)));
    }

    return output;
}

static ilist gen_prefix_op(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == PRIMARY_OPTION) {
        return gen_primary(node->nodes[0]);
    }

    /*
    > op A

    < gen(A)
    < INS corresponding to op
    */

    AstNode *A = node->nodes[0];

    temp = gen_prefix_op(A);
    ilistLink(&output, &temp);

    if (node->option == POSITIVE_OPTION) {
        ilistAppend(&output, genInsPOSITIVE(info(node)));
    }
    else if (node->option == NEGATIVE_OPTION) {
        ilistAppend(&output, genInsNEGATION(info(node)));
    }
    else if (node->option == NOT_OPTION) {
        ilistAppend(&output, genInsLOGICAL_NOT(info(node)));
    }
    else {
        ilistAppend(&output, genInsINVERTION(info(node)));
    }

    return output;
}

static ilist gen_primary(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    if (node->option == ELEMENTARY_OPTION) {
        return gen_elementary(node->nodes[0]);
    }

    if (node->option == CALL_OPTION) {
        /*
        < A (B1 ... Bn)

        > gen(B1)
        ...
        > gen(Bn)
        > gen(A)
        > SWITCH_ENV_OBJ
        > CREATE_SCOPE WITHOUT_PARENT_ACCESS
        > CALL n
        > DESTROY_SCOPE
        > SWITCH_ENV_INS
        */

        int64_t n = 0;
        if (node->n_nodes == 2) {
            temp = gen_expr_list(node->nodes[1]);
            ilistLink(&output, &temp);

            AstNode *args = node->nodes[1];

            while (args != NULL) {
                temp = gen(args->nodes[0]);
                n++;

                if (args->n_nodes == 2) {
                    args = args->nodes[1];
                }
                else {
                    args = NULL;
                }
            }
        }

        temp = gen_primary(node->nodes[0]);
        ilistLink(&output, &temp);

        ilistAppend(&output, genInsSWITCH_ENV_OBJ(info(node)));
        ilistAppend(&output, genInsCREATE_SCOPE(info(node), 0));
        ilistAppend(&output, genInsCALL(info(node), n));
        ilistAppend(&output, genInsDESTROY_SCOPE(info(node)));
        ilistAppend(&output, genInsSWITCH_ENV_INS(info(node)));

        return output;
    }

    AstNode *A = node->nodes[0];
    AstNode *B = node->nodes[1];

    if (node->option == INDEX_OPTION) {
        temp = gen_primary(A);
        ilistLink(&output, &temp);

        temp = gen_expr(B);
        ilistLink(&output, &temp);

        ilistAppend(&output, genInsACCESS(info(node)));

        return output;
    }

    if (node->option == FIELD_OPTION) {
        temp = gen_primary(A);
        ilistLink(&output, &temp);

        ilistAppend(&output, genInsLOAD_FIELD(info(node), B->ident_value));

        return output;
    }

    if (node->option == METHOD_OPTION) {
        temp = gen_primary(A);
        ilistLink(&output, &temp);

        ilistAppend(&output, genInsLOAD_METHOD(info(node), B->ident_value));

        return output;
    }

    // womp womp no execution flow? skill issue noob
}

static ilist gen_elementary(AstNode *node) {
    if (node->option == EXPR_OPTION) {
        return gen_expr(node->nodes[0]);
    }
    return gen_literal(node->nodes[0]);
}

static ilist gen_literal(AstNode *node) {
    ilist output = ilistCreate();
    // if because switch is boring
    if (node->option == NULL_OPTION) {
        ilistAppend(&output, genInsLOAD_NULL(info(node)));
        return output;
    }
    if (node->option == BOOL_OPTION) {
        ilistAppend(&output, genInsLOAD_BOOL(info(node), node->bool_value));
        return output;
    }
    if (node->option == CHAR_OPTION) {
        ilistAppend(&output, genInsLOAD_CHAR(info(node), node->char_value));
        return output;
    }
    if (node->option == INT_OPTION) {
        ilistAppend(&output, genInsLOAD_INT(info(node), node->int_value));
        return output;
    }
    if (node->option == FLOAT_OPTION) {
        ilistAppend(&output, genInsLOAD_FLOAT(info(node), node->float_value));
        return output;
    }
    if (node->option == STRING_OPTION) {
        ilistAppend(&output, genInsLOAD_STRING(info(node), node->string_value));
        return output;
    }
    if (node->option == IDENTIFIER_OPTION) {
        ilistAppend(&output, genInsLOAD(info(node), node->ident_value));
        return output;
    }
}

static ilist gen_module_path(AstNode *node) {}

static ilist gen_module_path_upwards(AstNode *node) {}

static ilist gen_module_path_compact(AstNode *node) {}

static ilist gen_expr_list(AstNode *node) {
    ilist output = ilistCreate();
    ilist temp   = ilistCreate();

    while (node != NULL) {
        temp = gen(node->nodes[0]);
        ilistLink(&output, &temp);

        if (node->n_nodes == 2) {
            node = node->nodes[1];
        }
        else {
            node = NULL;
        }
    }

    return output;
}
