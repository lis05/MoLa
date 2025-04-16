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

int main() {
    molalog("Starting parser\n");
    initParser();
    parserSetFilename("/home/lis05/Projects/mola/tests/vm.txt");
    AstNode *ast = runParser();
    molalog("Parsing complete\n");

    int64_t builtin_env_id = envCreate(0);
    Env    *builtin_env    = envGetById(builtin_env_id);

    molalog("Compiling ...\n");
    envInit();
    int64_t t_before     = clock();
    ilist   instructions = genCompile(ast);
    int64_t t_after      = clock();

    molalog("Generated %d instructions in %.3f seconds\n", instructions.size, 1.0 * (t_after - t_before) / CLOCKS_PER_SEC);

    molalog("Creating log: compiled.txt ...\n");
    int fd;
    if (instructions.size > 50) {
        fd = dup(1);
        close(1);
        open("/home/lis05/Projects/mola/logs/compiled.txt", O_RDWR | O_CREAT | O_TRUNC);
    }

    ivec    to_execute;
    inode  *node = instructions.head;
    int64_t pos  = 0;
    while (node != NULL) {
        genPrintInstrShort(pos, &node->ins);
        cvector_push_back(to_execute, node->ins);
        node = node->next;
        pos++;
    }
    if (instructions.size > 50) {
        close(1);
        dup2(fd, 1);
    }

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

    t_before = clock();
    vmExecute(to_execute);
    t_after = clock();

    printf("Execution finished after %.3f seconds\n", 1.0 * (t_after - t_before) / CLOCKS_PER_SEC);

    return 0;
}

// TODO: module_path
