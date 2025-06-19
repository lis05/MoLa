#include "builtin.h"
#include "../../../molalib/src/api.h"
#include <stdlib.h>
#include <string.h>

Object *builtin__printer(size_t n_args, struct Object **args) {
    for (int i = 0; i < n_args; i++) {
        if (args[i] == NULL) {
            signalError(INTERNAL_ERROR_CODE, "NULL argument");
        }

        Object *obj = args[i];

        switch (obj->type) {
        case NULL_TYPE : {
            printf("null");
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
        case CHAR_TYPE : {
            printf("%c", obj->char_value);
            break;
        }
        case FLOAT_TYPE : {
            printf("%lf", obj->float_value);
            break;
        }
        case STRING_TYPE : {
            printf("%s", get_string(obj)->string);
            break;
        }
        case ARRAY_TYPE : {
            printf("array@%p", obj->value);
            break;
        }
        case TYPE_TYPE : {
            printf("type@%p", obj->value);
            break;
        }
        case INSTANCE_TYPE : {
            printf("instance@%p", obj->value);
            break;
        }
        case MOLA_FUNCTION_TYPE : {
            printf("function@%p", obj->value);
            break;
        }
        case C_FUNCTION_TYPE : {
            printf("cfunction@%p", obj->value);
            break;
        }
        case MODULE_TYPE : {
            printf("module@%p", obj->value);
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

Object *builtin__cmodule_global(size_t n_args, struct Object **args) {
    if (n_args != 1) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, "Expected 1 argument");
    }

    Object *obj = args[0];
    if (obj->type != STRING_TYPE) {
        signalError(VALUE_ERROR_CODE, "Expected a string");
    }

    char *path = get_string(obj)->string;

    int64_t mid = openCModule(path);

    Object *res = objectCreate(INT_TYPE, raw64(mid));
    return res;
}

Object *builtin__cmodule(size_t n_args, struct Object **args) {
    if (n_args != 1) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, "Expected 1 argument");
    }

    Object *obj = args[0];
    if (obj->type != STRING_TYPE) {
        signalError(VALUE_ERROR_CODE, "Expected a string");
    }

    char *modules_path = getenv("MOLA_MODULES_PATH");
    if (modules_path == NULL) {
        signalError(VALUE_ERROR_CODE, "Environmental variable 'MOLA_MODULES_PATH' is unset");
    }

    /*
    apparently, in linux multiple slashes are considered as one
    */

    char buf[1024];
    strcpy(buf, modules_path);
    buf[strlen(modules_path)] = '/';
    strcpy(buf + strlen(modules_path) + 1, get_string(obj)->string);

    int64_t mid = openCModule(buf);

    Object *res = objectCreate(INT_TYPE, raw64(mid));
    return res;
}

Object *builtin__cloadf(size_t n_args, struct Object **args) {
    if (n_args != 2) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, "Expected 2 arguments");
    }

    Object *arg1 = args[0];
    Object *arg2 = args[1];

    if (arg1->type != INT_TYPE) {
        signalError(VALUE_ERROR_CODE, "Module id must be a number");
    }
    if (arg2->type != STRING_TYPE) {
        signalError(VALUE_ERROR_CODE, "Requested name must be a string");
    }

    int64_t mid = arg1->int_value;
    char   *str = get_string(arg2)->string;

    if (get_string(arg2)->length > 200) {
        signalError(VALUE_ERROR_CODE, "Requested name cannot be longer than 200 characters");
    }

    static char buf[256];
    strcpy(buf, "cmodprFUNC__");
    strcpy(buf + strlen("cmodprFUNC__"), str);

    return cModuleRequestFunction(mid, buf);
}

// ############## ############## ############## ##############

static Env *builtin_env;

void addFunctionIntoBuiltinEnv(CFunction func, char *name) {
    CFunctionValue *value  = cFunctionValueCreate(builtin_env, UNLIMITED_ARGS, func);
    value->is_gc_protected = 1;
    Object *obj            = objectCreate(C_FUNCTION_TYPE, raw64(value));
    obj->is_gc_protected   = 1;
    identMapSet(&builtin_env->globals, symtabInsert(lex_symtab, name), obj);
    molalog("Added builtin function: %s\n", name);
}

void init_builtin(Env *env) {
    builtin_env = env;
    addFunctionIntoBuiltinEnv(builtin__printer, "print");
    addFunctionIntoBuiltinEnv(builtin__cmodule_global, "cmodule_global");
    addFunctionIntoBuiltinEnv(builtin__cmodule, "cmodule");
    addFunctionIntoBuiltinEnv(builtin__cloadf, "cloadf");
}
