#include "../../molalib/src/api.h"
#include "builtin/builtin.h"
#include <fcntl.h>
#include <sys/unistd.h>
#include <time.h>

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

    init_builtin(builtin_env);

    clock_t t_before = clock();
    vmExecute(instructions);
    clock_t t_after = clock();

    printf("Execution finished after %.3f seconds\n", 1.0 * (t_after - t_before) / CLOCKS_PER_SEC);

    closeAllCModules();
    return 0;
}

// TODO: module_path
