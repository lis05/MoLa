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
        case BOOL_TYPE : {
            printf("%s", obj->bool_value ? "true" : "false");
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

Object *cmodule_global(size_t n_args, struct Object **args) {
    if (n_args != 1) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, "Expected 1 argument");
    }

    Object *obj = args[0];
    if (obj->type != STRING_TYPE) {
        signalError(VALUE_ERROR_CODE, "Expected a string");
    }

    char *path = ((StringValue *)obj->value)->string;

    int64_t mid = openCModule(path);

    Object *res = objectCreate(INT_TYPE, raw64(mid));
    return res;
}

extern Symtab *lex_symtab;

TypeValue *array_type_ptr;

TypeValue *error_type;

int main() {
    molalog("Starting MoLa\n");
    initParser();
    envInit();

    Env *builtin_env = envGetById(envCreate(0, "MOLA_BUILTIN"));

    int64_t env_id;
    ivec    instructions = compileProgram("/home/lis05/Projects/mola/tests/vm.mola", &env_id);

    eassert(env_id == 1);

    molalog("Starting vm ...\n");

    gcInit();
    allocInit();
    initTypes();
    {
        CFunctionValue *builtin_printer_func  = cFunctionValueCreate(builtin_env, UNLIMITED_ARGS, printer);
        builtin_printer_func->is_gc_protected = 1;
        Object *builtin_printer               = objectCreate(C_FUNCTION_TYPE, raw64(builtin_printer_func));
        builtin_printer->is_gc_protected      = 1;
        identMapSet(&builtin_env->globals, symtabInsert(lex_symtab, "print"), builtin_printer);
    }
    {
        CFunctionValue *cmodule_global_func     = cFunctionValueCreate(builtin_env, UNLIMITED_ARGS, cmodule_global);
        cmodule_global_func->is_gc_protected    = 1;
        Object *builtin_cmodule_global          = objectCreate(C_FUNCTION_TYPE, raw64(cmodule_global_func));
        builtin_cmodule_global->is_gc_protected = 1;
        identMapSet(&builtin_env->globals, symtabInsert(lex_symtab, "cmodule_global"), builtin_cmodule_global);
    }

    {
        array_type_ptr                      = typeValueCreate(0, NULL, 0, NULL);
        array_type_ptr->is_gc_protected     = 1;
        Object *builtin_array_type          = objectCreate(TYPE_TYPE, raw64(array_type_ptr));
        builtin_array_type->is_gc_protected = 1;
        identMapSet(&builtin_env->globals, symtabInsert(lex_symtab, "Array"), builtin_array_type);
    }

    {
        ident fields[4];
        fields[0]                   = symtabInsert(lex_symtab, "code");
        fields[1]                   = symtabInsert(lex_symtab, "reason");
        fields[2]                   = symtabInsert(lex_symtab, "module");
        fields[3]                   = symtabInsert(lex_symtab, "line");
        error_type                  = typeValueCreate(4, fields, 0, NULL);
        error_type->is_gc_protected = 1;
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
