#include "api.h"
#include <fcntl.h>
#include <sys/unistd.h>
#include <time.h>

Object *printer(size_t n_args, struct Object **args) {
    for (int i = 0; i < n_args; i++) {
        if (args[i] == NULL) {
            signalError(INTERNAL_ERROR_CODE, "NULL argument");
        }

        Object *obj = args[i];

        switch (obj->type) {
        case NULL_TYPE : {
            printf("NULL");
            break;
        }
        case INT_TYPE : {
            printf("%lld", obj->int_value);
            break;
        }
        case FLOAT_TYPE : {
            printf("%lf", obj->float_value);
            break;
        }
        case STRING_TYPE : {
            printf("%s", ((StringValue *)obj->value)->string);
            break;
        }
        }
        if (i + 1 == n_args) {
            printf("\n");
        }
        else {
            printf(" ");
        }
    }

    return objectCreate(NULL_TYPE, 0);
}

extern Symtab *lex_symtab;

void *array_type_ptr;

TypeValue *error_type;

int main() {
    molalog("Starting MoLa\n");
    initParser();
    envInit();

    Env *builtin_env = envGetById(envCreate(0, "MOLA_BUILTIN"));

    int64_t env_id;
    ivec    instructions = compileProgram("/home/lis05/Projects/mola/tests/vm.txt", &env_id);

    assert(env_id == 1);

    molalog("Starting vm ...\n");

    allocInit();
    initTypes();
    {
        CFunctionValue *builtin_printer_func = cFunctionValueCreate(builtin_env, UNLIMITED_ARGS, printer);
        Object         *builtin_printer      = objectCreate(C_FUNCTION_TYPE, raw64(builtin_printer_func));
        identMapSet(&builtin_env->globals, symtabInsert(lex_symtab, "print"), builtin_printer);
    }

    {
        array_type_ptr             = typeValueCreate(0, NULL, 0, NULL);
        Object *builtin_array_type = objectCreate(TYPE_TYPE, raw64(array_type_ptr));
        identMapSet(&builtin_env->globals, symtabInsert(lex_symtab, "Array"), builtin_array_type);
    }

    {
        ident fields[4];
        fields[0]  = symtabInsert(lex_symtab, "code");
        fields[1]  = symtabInsert(lex_symtab, "reason");
        fields[2]  = symtabInsert(lex_symtab, "module");
        fields[3]  = symtabInsert(lex_symtab, "line");
        error_type = typeValueCreate(4, fields, 0, NULL);
        // Object *builtin_error = objectCreate(TYPE_TYPE, raw64(error_type));
        // identMapSet(&builtin_env->globals, symtabInsert(lex_symtab, "Error"), error_type);
    }

    clock_t t_before = clock();
    vmExecute(instructions);
    clock_t t_after = clock();

    printf("Execution finished after %.3f seconds\n", 1.0 * (t_after - t_before) / CLOCKS_PER_SEC);

    return 0;
}

// TODO: module_path
