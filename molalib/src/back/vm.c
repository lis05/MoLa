#include "vm.h"
#include "../front/api.h"
#include "alloc.h"
#include "cmap.h"
#include "env.h"
#include "error.h"
#include "gc.h"
#include "gen.h"
#include "object.h"
#include "scope.h"
#include "stat.h"
#include "sys/unistd.h"
#include "types.h"
#include <fcntl.h>
#include <libgen.h>
#include <time.h>

#define RECYCLING_DELAY 20

extern Symtab *lex_symtab;

static void exec_POP(Instruction *instr);
static void exec_SWAP(Instruction *instr);
static void exec_CREATE_ENV(Instruction *instr);
static void exec_SWITCH_ENV_INS(Instruction *instr);
static void exec_SWITCH_ENV_OBJ(Instruction *instr);
static void exec_IMPORT_MODULE(Instruction *instr);
static void exec_EXPORT_OBJECT(Instruction *instr);
static void exec_CREATE_GLOBAL(Instruction *instr);
static void exec_CREATE_FUNCTION(Instruction *instr);
static void exec_CREATE_TYPE(Instruction *instr);
static void exec_CREATE_METHOD(Instruction *instr);
static void exec_CREATE_SCOPE(Instruction *instr);
static void exec_DESTROY_SCOPE(Instruction *instr);
static void exec_JUMP_IF_FALSE(Instruction *instr);
static void exec_JUMP(Instruction *instr);
static void exec_RETURN(Instruction *instr);
static void exec_REGISTER_CATCH(Instruction *instr);
static void exec_DESTROY_CATCH(Instruction *instr);
static void exec_SIGNAL_ERROR(Instruction *instr);
static void exec_CREATE_VAR(Instruction *instr);
static void exec_COPY(Instruction *instr);
static void exec_ASSIGNMENT(Instruction *instr);
static void exec_LOGICAL_OR(Instruction *instr);
static void exec_LOGICAL_AND(Instruction *instr);
static void exec_BITWISE_OR(Instruction *instr);
static void exec_BITWISE_XOR(Instruction *instr);
static void exec_BITWISE_AND(Instruction *instr);
static void exec_EQUAL(Instruction *instr);
static void exec_NOT_EQUAL(Instruction *instr);
static void exec_LESS_THAN(Instruction *instr);
static void exec_LESS_EQUAL(Instruction *instr);
static void exec_GREATER_THAN(Instruction *instr);
static void exec_GREATER_EQUAL(Instruction *instr);
static void exec_ADDITION(Instruction *instr);
static void exec_SUBTRACTION(Instruction *instr);
static void exec_LSHIFT(Instruction *instr);
static void exec_RSHIFT(Instruction *instr);
static void exec_MULTIPLICATION(Instruction *instr);
static void exec_DIVISION(Instruction *instr);
static void exec_REMAINDER(Instruction *instr);
static void exec_POSITIVE(Instruction *instr);
static void exec_NEGATION(Instruction *instr);
static void exec_INVERTION(Instruction *instr);
static void exec_LOGICAL_NOT(Instruction *instr);
static void exec_CALL(Instruction *instr);
static void exec_ACCESS(Instruction *instr);
static void exec_LOAD_BOOL(Instruction *instr);
static void exec_LOAD_CHAR(Instruction *instr);
static void exec_LOAD_INT(Instruction *instr);
static void exec_LOAD_FLOAT(Instruction *instr);
static void exec_LOAD_STRING(Instruction *instr);
static void exec_LOAD_NULL(Instruction *instr);
static void exec_LOAD(Instruction *instr);
static void exec_LOAD_FIELD(Instruction *instr);
static void exec_LOAD_METHOD(Instruction *instr);
static void exec_NEW(Instruction *instr);
static void exec_HALT(Instruction *instr);
static void exec_UNREF(Instruction *instr);

extern TypeValue *error_type;

typedef struct ErrorHandler {
    int64_t error_code;
    int64_t absolute_offset;
    size_t  stack_frame_size;
    size_t  error_checkpoints_size;
    Scope  *scope;
} ErrorHandler;

int64_t molaErrorCode;
char   *molaErrorReason;    // NULL-terminated

static int64_t ipointer                                       = 0;
cvector_vector_type(Object *) objects_stack                   = NULL;
static cvector_vector_type(ErrorHandler) error_handlers_stack = NULL;
Env   *current_env                                            = NULL;
Scope *root_scope = NULL, *current_scope = NULL;

cvector_vector_type(int64_t) error_checkpoints;
int64_t env_offset = 0;    // set when imported

cvector_vector_type(Env *) imported_modules;

cvector_vector_type(ReferencedObject) referenced_stack;

void checkpoint() {
    cvector_push_back(error_checkpoints, ipointer);
}

void destroyCheckpoint() {
    cvector_pop_back(error_checkpoints);
}

void objectsStackPush(Object *obj) {
    ref(obj);
    cvector_push_back(objects_stack, obj);
}

int objectsStackEmpty() {
    return cvector_empty(objects_stack);
}

size_t objectsStackSize() {
    return cvector_size(objects_stack);
}

Object *objectsStackTop() {
    return *cvector_back(objects_stack);
}

void objectsStackPop() {
    // if stack's empty, you're screwed
    unref(*cvector_back(objects_stack));
    cvector_pop_back(objects_stack);
}

static void handleError();

/*
Conventions:

function executing an instruction must update ipointer

an instruction must clean after itself
*/

static ivec instructions_list;

struct Instruction *vmCurrentInstruction() {
    return instructions_list + ipointer;
}

struct Instruction *vmInstruction(int64_t ip) {
    return instructions_list + ip;
}

extern cvector_vector_type(Object *) objects_trash;
extern cvector_vector_type(StringValue *) strings_trash;
extern cvector_vector_type(ArrayValue *) arrays_trash;
extern cvector_vector_type(TypeValue *) types_trash;
extern cvector_vector_type(InstanceValue *) instances_trash;
extern cvector_vector_type(MolaFunctionValue *) mola_functions_trash;
extern cvector_vector_type(CFunctionValue *) c_functions_trash;
extern cvector_vector_type(Object *) objects_maybe_trash;
extern cvector_vector_type(StringValue *) strings_maybe_trash;
extern cvector_vector_type(ArrayValue *) arrays_maybe_trash;
extern cvector_vector_type(TypeValue *) types_maybe_trash;
extern cvector_vector_type(InstanceValue *) instances_maybe_trash;
extern cvector_vector_type(MolaFunctionValue *) mola_functions_maybe_trash;
extern cvector_vector_type(CFunctionValue *) c_functions_maybe_trash;
extern map_t(Object *, int8_t) objects_tracked;
extern map_t(StringValue *, int8_t) strings_tracked;
extern map_t(ArrayValue *, int8_t) arrays_tracked;
extern map_t(TypeValue *, int8_t) types_tracked;
extern map_t(InstanceValue *, int8_t) instances_tracked;
extern map_t(MolaFunctionValue *, int8_t) mola_functions_tracked;
extern map_t(CFunctionValue *, int8_t) c_functions_tracked;

#define map_size(map)                                                                                                            \
    ({                                                                                                                           \
        size_t     res = 0;                                                                                                      \
        void      *key;                                                                                                          \
        map_iter_t iter = map_iter(map);                                                                                         \
        while (map_next(map, &iter, &key)) {                                                                                     \
            res++;                                                                                                               \
        }                                                                                                                        \
        res;                                                                                                                     \
    })
int64_t vmloops = 0;

void vmExecute(ivec instructions) {
    for (int i = 0; i < cvector_size(instructions); i++) {
        cvector_push_back(instructions_list, instructions[i]);
    }
    while ((0 <= ipointer && ipointer < cvector_size(instructions_list))) {
        vmloops++;

        Instruction *instr = instructions_list + ipointer;

        eassert(instr != NULL);

        if (setErrorReturnPoint()) {
            // error handler
            handleError();

            // if this code is reached, it means that the program
            // was able to recover from the error
            // and the normal execution should continue;

            if (instr->code == RETURN_IC) {
                destroyCheckpoint();
                destroyCheckpoint();
            }
            else if (instr->code != CALL_IC) {
                destroyCheckpoint();
            }

            continue;
        }

        int n_destroy = 1;
        checkpoint();
        switch (instr->code) {
        case POP_IC : {
            exec_POP(instr);
            break;
        }
        case SWAP_IC : {
            exec_SWAP(instr);
            break;
        }
        case CREATE_ENV_IC : {
            exec_CREATE_ENV(instr);
            break;
        }
        case SWITCH_ENV_INS_IC : {
            exec_SWITCH_ENV_INS(instr);
            break;
        }
        case SWITCH_ENV_OBJ_IC : {
            exec_SWITCH_ENV_OBJ(instr);
            break;
        }
        case IMPORT_MODULE_IC : {
            exec_IMPORT_MODULE(instr);
            break;
        }
        case EXPORT_OBJECT_IC : {
            exec_EXPORT_OBJECT(instr);
            break;
        }
        case CREATE_GLOBAL_IC : {
            exec_CREATE_GLOBAL(instr);
            break;
        }
        case CREATE_FUNCTION_IC : {
            exec_CREATE_FUNCTION(instr);
            break;
        }
        case CREATE_TYPE_IC : {
            exec_CREATE_TYPE(instr);
            break;
        }
        case CREATE_METHOD_IC : {
            exec_CREATE_METHOD(instr);
            break;
        }
        case CREATE_SCOPE_IC : {
            exec_CREATE_SCOPE(instr);
            break;
        }
        case DESTROY_SCOPE_IC : {
            exec_DESTROY_SCOPE(instr);
            break;
        }
        case JUMP_IF_FALSE_IC : {
            exec_JUMP_IF_FALSE(instr);
            break;
        }
        case JUMP_IC : {
            exec_JUMP(instr);
            break;
        }
        case RETURN_IC : {
            exec_RETURN(instr);
            n_destroy = 2;
            break;
        }
        case REGISTER_CATCH_IC : {
            exec_REGISTER_CATCH(instr);
            break;
        }
        case DESTROY_CATCH_IC : {
            exec_DESTROY_CATCH(instr);
            break;
        }
        case SIGNAL_ERROR_IC : {
            exec_SIGNAL_ERROR(instr);
            break;
        }
        case CREATE_VAR_IC : {
            exec_CREATE_VAR(instr);
            break;
        }
        case COPY_IC : {
            exec_COPY(instr);
            break;
        }
        case ASSIGNMENT_IC : {
            exec_ASSIGNMENT(instr);
            break;
        }
        case LOGICAL_OR_IC : {
            exec_LOGICAL_OR(instr);
            break;
        }
        case LOGICAL_AND_IC : {
            exec_LOGICAL_AND(instr);
            break;
        }
        case BITWISE_OR_IC : {
            exec_BITWISE_OR(instr);
            break;
        }
        case BITWISE_XOR_IC : {
            exec_BITWISE_XOR(instr);
            break;
        }
        case BITWISE_AND_IC : {
            exec_BITWISE_AND(instr);
            break;
        }
        case EQUAL_IC : {
            exec_EQUAL(instr);
            break;
        }
        case NOT_EQUAL_IC : {
            exec_NOT_EQUAL(instr);
            break;
        }
        case LESS_THAN_IC : {
            exec_LESS_THAN(instr);
            break;
        }
        case LESS_EQUAL_IC : {
            exec_LESS_EQUAL(instr);
            break;
        }
        case GREATER_THAN_IC : {
            exec_GREATER_THAN(instr);
            break;
        }
        case GREATER_EQUAL_IC : {
            exec_GREATER_EQUAL(instr);
            break;
        }
        case ADDITION_IC : {
            exec_ADDITION(instr);
            break;
        }
        case SUBTRACTION_IC : {
            exec_SUBTRACTION(instr);
            break;
        }
        case LSHIFT_IC : {
            exec_LSHIFT(instr);
            break;
        }
        case RSHIFT_IC : {
            exec_RSHIFT(instr);
            break;
        }
        case MULTIPLICATION_IC : {
            exec_MULTIPLICATION(instr);
            break;
        }
        case DIVISION_IC : {
            exec_DIVISION(instr);
            break;
        }
        case REMAINDER_IC : {
            exec_REMAINDER(instr);
            break;
        }
        case POSITIVE_IC : {
            exec_POSITIVE(instr);
            break;
        }
        case NEGATION_IC : {
            exec_NEGATION(instr);
            break;
        }
        case INVERTION_IC : {
            exec_INVERTION(instr);
            break;
        }
        case LOGICAL_NOT_IC : {
            exec_LOGICAL_NOT(instr);
            break;
        }
        case CALL_IC : {
            exec_CALL(instr);
            n_destroy = 0;
            break;
        }
        case ACCESS_IC : {
            exec_ACCESS(instr);
            break;
        }
        case LOAD_BOOL_IC : {
            exec_LOAD_BOOL(instr);
            break;
        }
        case LOAD_CHAR_IC : {
            exec_LOAD_CHAR(instr);
            break;
        }
        case LOAD_INT_IC : {
            exec_LOAD_INT(instr);
            break;
        }
        case LOAD_FLOAT_IC : {
            exec_LOAD_FLOAT(instr);
            break;
        }
        case LOAD_STRING_IC : {
            exec_LOAD_STRING(instr);
            break;
        }
        case LOAD_NULL_IC : {
            exec_LOAD_NULL(instr);
            break;
        }
        case LOAD_IC : {
            exec_LOAD(instr);
            break;
        }
        case LOAD_FIELD_IC : {
            exec_LOAD_FIELD(instr);
            break;
        }
        case LOAD_METHOD_IC : {
            exec_LOAD_METHOD(instr);
            break;
        }
        case NEW_IC : {
            exec_NEW(instr);
            break;
        }
        case HALT_IC : {
            while (n_destroy--) {
                destroyCheckpoint();
                molalog("HALT\n");
            }
            return;
        }
        case UNREF_IC : {
            exec_UNREF(instr);
            break;
        }

        default : {
            signalError(INTERNAL_ERROR_CODE, "unknown instruction");
            exit(-1);    // cleaning after yourself? nah
        }
        }
        while (n_destroy--) {
            destroyCheckpoint();
        }
        static int recycling_counter = 0;
        recycling_counter++;
        if (recycling_counter == RECYCLING_DELAY) {
            recycling_counter = 0;
            gcRecycle(getRecycleAmount());
        }

        instructions_since_gc_cycle++;
        if (instructions_since_gc_cycle >= getGCCycleThreshold()) {
            instructions_since_gc_cycle = 0;
            molalog("Performing gc cycle.... Before = %lfmb\n", getAllocatedBytes() / 1e6);
            gcRunCycle();
            molalog("Performed gc cycle....  After = %lfmb\n", getAllocatedBytes() / 1e6);
        }

        static clock_t clocks = 0;
        if (clock() - clocks >= 0.5 * CLOCKS_PER_SEC) {
            clocks = clock();
            molalog("Execution log: ip=%zu | allocated memory: %.2lfmb | isgc=%zu | gcthresh=%zu | vmloops = %lld\n",
                    ipointer,
                    getAllocatedBytes() / 1e6,
                    instructions_since_gc_cycle,
                    getGCCycleThreshold(),
                    vmloops);
            molalog("  Objects on stack: %zu | error handlers: %zu | error checkpoints: %zu \n",
                    cvector_size(objects_stack),
                    cvector_size(error_handlers_stack),
                    cvector_size(error_checkpoints));
            molalog("  Imported modules: %zu | referenced_stack: %zu\n",
                    cvector_size(imported_modules),
                    cvector_size(referenced_stack));
            molalog("  O:%lld N:%lld B:%lld C:%lld I:%lld F:%lld S:%lld A:%lld T:%lld IN:%lld MF:%lld CF:%lld\n",
                    stat_created_objects,
                    stat_created_nulls,
                    stat_created_bools,
                    stat_created_chars,
                    stat_created_ints,
                    stat_created_floats,
                    stat_created_strings,
                    stat_created_arrays,
                    stat_created_types,
                    stat_created_instances,
                    stat_created_mola_functions,
                    stat_created_c_functions);
            molalog("  SC:%lld IM:%lld\n", stat_created_scopes, stat_created_ident_maps);
            molalog("  TRASH: O:%zu S:%zu A:%zu T:%zu IN:%zu MF:%zu CF:%zu\n",
                    cvector_size(objects_trash),
                    cvector_size(strings_trash),
                    cvector_size(arrays_trash),
                    cvector_size(types_trash),
                    cvector_size(instances_trash),
                    cvector_size(mola_functions_trash),
                    cvector_size(c_functions_trash));
            molalog("  MAYBE: O:%zu S:%zu A:%zu T:%zu IN:%zu MF:%zu CF:%zu\n",
                    cvector_size(objects_maybe_trash),
                    cvector_size(strings_maybe_trash),
                    cvector_size(arrays_maybe_trash),
                    cvector_size(types_maybe_trash),
                    cvector_size(instances_maybe_trash),
                    cvector_size(mola_functions_maybe_trash),
                    cvector_size(c_functions_maybe_trash));
            molalog("  TRACKED: O:%zu S:%zu A:%zu T:%zu IN:%zu MF:%zu CF:%zu\n",
                    map_size(&objects_tracked),
                    map_size(&strings_tracked),
                    map_size(&arrays_tracked),
                    map_size(&types_tracked),
                    map_size(&instances_tracked),
                    map_size(&mola_functions_tracked),
                    map_size(&c_functions_tracked));
            molalog("\n");
        }
    }
}

static void exec_POP(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "POP failed: empty objects_stack");
    }

    objectsStackPop();

    ipointer++;
}

static void exec_SWAP(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "SWAP failed: less that 2 elements on objects_stack");
    }

    size_t size = objectsStackSize();

    Object *t               = objects_stack[size - 1];
    objects_stack[size - 1] = objects_stack[size - 2];
    objects_stack[size - 2] = t;

    ipointer++;
}

static void exec_CREATE_ENV(Instruction *instr) {
    current_env = envGetById(envCreate(env_offset, instr->filename));

    // each time CREATE_ENV is executed, a new module is imported
    cvector_push_back(imported_modules, current_env);

    ipointer++;
}

static void exec_SWITCH_ENV_INS(Instruction *instr) {
    current_env = envGetById(instr->env_id);

    ipointer++;
}

static void exec_SWITCH_ENV_OBJ(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "SWITCH_ENV_OBJ failed: empty objects_stack");
    }

    Object *obj = objectsStackTop();

    if (obj->type != C_FUNCTION_TYPE && obj->type != MOLA_FUNCTION_TYPE) {
        signalError(INTERNAL_ERROR_CODE, "SWITCH_ENV_OBJ failed: object on the stack is not a function");
    }

    if (obj->type == C_FUNCTION_TYPE) {
        current_env = ((CFunctionValue *)obj->value)->env;
    }
    else {
        current_env = ((MolaFunctionValue *)obj->value)->env;
    }

    ipointer++;

    // note: we do not pop the object from the stack!
}

static void exec_IMPORT_MODULE(Instruction *instr) {
    /*
    we replace each '^' symbol with '../'

    compact:
        a.b.c (with optional ^ at the beginning)
        mola.a.b.c
    string: "a/b/c.mola"
    */

    cvector_vector_type(char) constructed_path = NULL;    // we will construct it step by step

    char *arg_path  = instr->string_arg1;
    ident import_as = instr->n_args;                      // wrath

    if (instr->flags == 1) {                              // compact
        int can_be_builtin = *arg_path != '^';
        int is_builtin     = 0;

        if (can_be_builtin) {
            // check for mola
            if (*arg_path == 'm' && *(arg_path + 1) == 'o' && *(arg_path + 2) == 'l' && *(arg_path + 3) == 'a'
                && *(arg_path + 4) == '.')
            {
                // builtin
                is_builtin  = 1;
                arg_path   += 5;

                char *MOLA_MODULES_PATH = getenv("MOLA_MODULES_PATH");
                if (MOLA_MODULES_PATH == NULL || strlen(MOLA_MODULES_PATH) == 0) {
                    signalError(
                    IMPORT_ERROR_CODE,
                    "Could not find the requested builtin module: MOLA_MODULES_PATH environment variable is missing or empty");
                }

                while (*MOLA_MODULES_PATH != '\0') {
                    cvector_push_back(constructed_path, *MOLA_MODULES_PATH);
                    MOLA_MODULES_PATH++;
                }

                if (*(MOLA_MODULES_PATH - 1) != '/') {
                    cvector_push_back(constructed_path, '/');
                }
            }
        }

        if (!is_builtin) {
            char *current_file = current_env->path;

            while (*current_file != '\0') {
                cvector_push_back(constructed_path, *current_file);
                current_file++;
            }

            // remove the last part of the current path
            while (!cvector_empty(constructed_path) && *cvector_back(constructed_path) != '/') {
                cvector_pop_back(constructed_path);
            }

            while (*arg_path == '^') {
                can_be_builtin = 0;
                cvector_push_back(constructed_path, '.');
                cvector_push_back(constructed_path, '.');
                cvector_push_back(constructed_path, '/');
                arg_path++;
            }
        }

        while (*arg_path != '\0') {
            if (*arg_path == '.') {
                cvector_push_back(constructed_path, '/');
            }
            else {
                cvector_push_back(constructed_path, *arg_path);
            }
            arg_path++;
        }

        cvector_push_back(constructed_path, '.');
        cvector_push_back(constructed_path, 'm');
        cvector_push_back(constructed_path, 'o');
        cvector_push_back(constructed_path, 'l');
        cvector_push_back(constructed_path, 'a');
        cvector_push_back(constructed_path, '\0');
    }
    else {
        char *current_file = current_env->path;

        while (*current_file != '\0') {
            cvector_push_back(constructed_path, *current_file);
            current_file++;
        }

        // remove the last part of the current path
        while (!cvector_empty(constructed_path) && *cvector_back(constructed_path) != '/') {
            cvector_pop_back(constructed_path);
        }

        while (*arg_path != '\0') {
            cvector_push_back(constructed_path, *arg_path);
            arg_path++;
        }
        cvector_push_back(constructed_path, '\0');
    }

    static char real_path[4096];
    realpath(constructed_path, real_path);
    cvector_free(constructed_path);

    molalog("Importing module: %s as %s\n", real_path, symtabIdentToString(import_as));

    if (identMapQuery(&current_env->globals, import_as)) {
        signalError(IMPORT_ERROR_CODE,
                    errstrfmt("A global object with name '%s' already exists", symtabIdentToString(import_as)));
    }

    if (access(real_path, F_OK) != 0) {
        signalError(IMPORT_ERROR_CODE, "invalid module");
    }

    for (int i = 0; i < cvector_size(imported_modules); i++) {
        if (strcmp(imported_modules[i]->path, real_path) == 0) {
            // already imported
            Object *obj = objectCreate(MODULE_TYPE, raw64(imported_modules[i]));
            identMapSet(&current_env->globals, import_as, obj);
            goto END;
        }
    }

    // first, we have to save the current C environment
    // and create a new one

    int64_t old_ipointer = ipointer;
    ipointer             = cvector_size(instructions_list);

    cvector_vector_type(Object *) old_objects_stack = objects_stack;
    objects_stack                                   = NULL;

    // error handlers should remain even when executing the imported program

    Env *old_current_env = current_env;
    current_env          = NULL;

    Scope *old_root_scope = root_scope;
    root_scope            = NULL;

    Scope *old_current_scope = current_scope;
    current_scope            = NULL;

    // error checkpoints should remain as well

    int64_t old_env_offset = env_offset;
    env_offset             = env_offset + cvector_size(instructions_list);

    // imported modules must remain as well

    // instruction_list must remain or it will all segfault

    int64_t env_id;
    ivec    compiled_module = compileProgram(real_path, &env_id);

    vmExecute(compiled_module);

    cvector_free(compiled_module);

    // nice!
    // restore the old C environment
    ipointer      = old_ipointer;
    objects_stack = old_objects_stack;
    current_env   = old_current_env;
    root_scope    = old_root_scope;
    current_scope = old_current_scope;
    env_offset    = old_env_offset;

    Env    *env = envGetById(env_id);
    Object *obj = objectCreate(MODULE_TYPE, raw64(env));
    identMapSet(&current_env->globals, import_as, obj);

    // TODO add . operator for modules

END:;
    ipointer++;
}

static void exec_EXPORT_OBJECT(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "EXPORT_OBJECT failed: empty objects_stack");
    }

    if (identMapQuery(&current_env->exported_objects, instr->ident_arg1)) {
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Exported object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    identMapSet(&current_env->exported_objects, instr->ident_arg1, objectsStackTop());
    objectsStackPop();

    ipointer++;
}

static void exec_CREATE_GLOBAL(Instruction *instr) {
    if (identMapQuery(&current_env->globals, instr->ident_arg1)) {
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Global object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    Object *obj = objectCreate(NULL_TYPE, 0);
    identMapSet(&current_env->globals, instr->ident_arg1, obj);

    ipointer++;
}

static void exec_CREATE_FUNCTION(Instruction *instr) {
    if (identMapQuery(&current_env->globals, instr->ident_arg1)) {
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Global object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    int64_t offset = ipointer + 2 - current_env->absolute_offset;

    int64_t n_args = instr->n_args;
    ident  *args   = allocOrError(n_args * sizeof(ident));
    memcpy(args, instr->args, n_args * sizeof(ident));

    MolaFunctionValue *func_value = molaFunctionValueCreate(current_env, offset, n_args, args);

    Object *obj = objectCreate(MOLA_FUNCTION_TYPE, raw64(func_value));

    identMapSet(&current_env->globals, instr->ident_arg1, obj);

    ipointer++;
}

static void exec_CREATE_TYPE(Instruction *instr) {
    size_t n_fields  = instr->args[0];
    size_t n_methods = instr->args[1];

    ident *fields  = instr->args + 2;
    ident *methods = instr->args + 2 + n_fields;

    TypeValue *type = typeValueCreate(n_fields, fields, n_methods, methods);

    Object *obj = objectCreate(TYPE_TYPE, raw64(type));

    identMapSet(&current_env->globals, instr->ident_arg1, obj);

    ipointer++;
}

static void exec_CREATE_METHOD(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "CREATE_METHOD failed: empty objects stack");
    }

    Object *type = objectsStackTop();
    objectsStackPop();

    if (type->type != TYPE_TYPE) {
        signalError(INTERNAL_ERROR_CODE, "CREATE_METHOD failed: the object on the stack is not a type");
    }

    int64_t offset = ipointer + 2 - current_env->absolute_offset;

    int64_t n_args = instr->n_args;
    ident  *args   = allocOrError(n_args * sizeof(ident));
    memcpy(args, instr->args, n_args * sizeof(ident));

    MolaFunctionValue *func_value = molaFunctionValueCreate(current_env, offset, n_args, args);
    func_value->is_method         = 1;

    Object *obj = objectCreate(MOLA_FUNCTION_TYPE, raw64(func_value));

    typeValueAddMethod(type->value, instr->ident_arg1, obj);

    ipointer++;
}

static void exec_CREATE_SCOPE(Instruction *instr) {
    Scope *new_scope = scopeCreate((current_scope == NULL) ? 0 : instr->flags, current_scope);
    current_scope    = new_scope;

    ipointer++;
}

static void exec_DESTROY_SCOPE(Instruction *instr) {
    eassert(current_scope != NULL);

    // we have to remove all of the error handlers created in this scope
    while (!cvector_empty(error_handlers_stack)) {
        if (cvector_back(error_handlers_stack)->scope == current_scope) {
            cvector_pop_back(error_handlers_stack);
        }
        else {
            break;
        }
    }

    Scope *parent = current_scope->parent;
    scopeDestroy(current_scope);

    current_scope = parent;

    ipointer++;
}

static void exec_JUMP_IF_FALSE(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "JUMP_IF_FALSE failed: empty objects stack");
    }

    Object *obj = objectsStackTop();
    objectsStackPop();

    if (obj->type != BOOL_TYPE) {
        signalError(VALUE_ERROR_CODE, "Expected a boolean value");
    }

    if (obj->bool_value) {
        ipointer++;
        return;
    }

    ipointer += instr->int_arg1;
}

static void exec_JUMP(Instruction *instr) {
    ipointer += instr->int_arg1;
}

static void exec_RETURN(Instruction *instr) {
    if (cvector_empty(objects_stack)) {
        signalError(INTERNAL_ERROR_CODE, "RETURN failed: empty objects_stack");
    }

    Object *top = objectsStackTop();
    objectsStackPop();

    if (top->type != RETURN_ADDRESS_TYPE) {
        signalError(INTERNAL_ERROR_CODE, "RETURN failed: object is not a return address");
    }

    int64_t return_address = (int64_t)top->value;

    ipointer = return_address;
}

static void exec_REGISTER_CATCH(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "REGISTER_CATCH failed: empty objects_stack");
    }

    Object *obj = objectsStackTop();
    if (obj->type != INT_TYPE) {
        signalError(VALUE_ERROR_CODE, "Not an integer");
    }

    ErrorHandler h;
    h.error_code       = obj->int_value;
    h.absolute_offset  = ipointer + 2;    // assuming that importing modules adds the instructions at the end of instructions_list
    h.stack_frame_size = objectsStackSize();
    h.error_checkpoints_size = cvector_size(error_checkpoints);
    h.scope                  = current_scope;

    cvector_push_back(error_handlers_stack, h);

    ipointer++;
}

static void exec_DESTROY_CATCH(Instruction *instr) {
    if (cvector_size(error_handlers_stack) < instr->int_arg1) {
        signalError(INTERNAL_ERROR_CODE, "DESTROY_CATCH failed: not enough elements on the stack");
    }

    for (int64_t i = 0; i < instr->int_arg1; i++) {
        cvector_pop_back(error_handlers_stack);    // could be done faster, but who cares
    }

    ipointer++;
}

static void exec_SIGNAL_ERROR(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "SIGNAL_ERROR failed: not enough elements on the stack");
    }

    Object *code = objectsStackTop();
    objectsStackPop();

    Object *msg = objectsStackTop();
    objectsStackPop();

    if (code->type != INT_TYPE) {
        signalError(VALUE_ERROR_CODE, "Expected an integer error code");
    }

    if (msg->type != STRING_TYPE) {
        signalError(VALUE_ERROR_CODE, "Expected a string error code");
    }

    signalError(code->int_value, ((StringValue *)msg->value)->string);
}

static void exec_CREATE_VAR(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "CREATE_VAR failed: empty objects_stack");
    }

    eassert(current_scope != NULL);

    if (identMapQuery(&current_scope->map, instr->ident_arg1)) {
        signalError(NAME_COLLISION_ERROR_CODE,
                    errstrfmt("Local object with name '%s' already exists", symtabIdentToString(instr->ident_arg1)));
    }

    Object *top = objectsStackTop();
    objectsStackPop();

    scopeInsert(current_scope, instr->ident_arg1, top);

    ipointer++;
}

static void exec_COPY(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "COPY failed: empty objects_stack");
    }

    Object *obj = objectsStackTop();

    // any copy of an rvalue can be the rvalue itself
    if (obj->is_rvalue) {
        ipointer++;
        return;
    }

    objectsStackPop();

    uint64_t value = 0;

    void *ptr;

    switch (obj->type) {
    case BOOL_TYPE : value = raw64(obj->bool_value); break;
    case INT_TYPE : value = raw64(obj->int_value); break;
    case CHAR_TYPE : value = raw64(obj->char_value); break;
    case FLOAT_TYPE : value = raw64(obj->float_value); break;
    case STRING_TYPE :
        ptr   = (stringValueCopy(obj->value));
        value = raw64(ptr);
        break;
    case ARRAY_TYPE :
        ptr   = (arrayValueCopy(obj->value));
        value = raw64(ptr);
        break;
    case TYPE_TYPE :
        ptr   = (typeValueCopy(obj->value));
        value = raw64(ptr);
        break;
    case INSTANCE_TYPE :
        ptr   = (instanceValueCopy(obj->value));
        value = raw64(ptr);
        break;
    case MOLA_FUNCTION_TYPE :
        ptr   = (molaFunctionValueCopy(obj->value));
        value = raw64(ptr);
        break;
    case C_FUNCTION_TYPE :
        ptr   = (cFunctionValueCopy(obj->value));
        value = raw64(ptr);
        break;
    case MODULE_TYPE : value = raw64(obj->value); break;
    case NULL_TYPE : break;
    case RETURN_ADDRESS_TYPE : {
        signalError(INTERNAL_ERROR_CODE, "COPY_BY_AUTO failed: RETURN_ADDRESS_TYPE on the stack");
    }
    }

    Object *res    = objectCreate(obj->type, value);
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_ASSIGNMENT(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "ASSIGNMENT failed: less than 2 elements on the stack");
    }

    Object *obj1 = objectsStackTop();
    objectsStackPop();

    Object *obj2 = objectsStackTop();
    objectsStackPop();

    if (obj1->type == NULL_TYPE) {
        stat_created_nulls--;
    }
    else if (obj1->type == BOOL_TYPE) {
        stat_created_bools--;
    }
    else if (obj1->type == CHAR_TYPE) {
        stat_created_chars--;
    }
    else if (obj1->type == INT_TYPE) {
        stat_created_ints--;
    }
    else if (obj1->type == FLOAT_TYPE) {
        stat_created_floats--;
    }
    else if (obj1->type == STRING_TYPE) {
        stringValueUnref(obj1->value);
    }
    else if (obj1->type == ARRAY_TYPE) {
        arrayValueUnref(obj1->value);
    }
    else if (obj1->type == TYPE_TYPE) {
        typeValueUnref(obj1->value);
    }
    else if (obj1->type == INSTANCE_TYPE) {
        instanceValueUnref(obj1->value);
    }
    else if (obj1->type == MOLA_FUNCTION_TYPE) {
        molaFunctionValueUnref(obj1->value);
    }
    else if (obj1->type == C_FUNCTION_TYPE) {
        cFunctionValueUnref(obj1->value);
    }

    obj1->type = obj2->type;

    // this works because we basically copy the entire union of obj2 into obj1
    obj1->value = obj2->value;

    if (obj1->type == NULL_TYPE) {
        stat_created_nulls++;
    }
    else if (obj1->type == BOOL_TYPE) {
        stat_created_bools++;
    }
    else if (obj1->type == CHAR_TYPE) {
        stat_created_chars++;
    }
    else if (obj1->type == INT_TYPE) {
        stat_created_ints++;
    }
    else if (obj1->type == FLOAT_TYPE) {
        stat_created_floats++;
    }
    else if (obj1->type == STRING_TYPE) {
        stringValueRef(obj1->value);
    }
    else if (obj1->type == ARRAY_TYPE) {
        arrayValueRef(obj1->value);
    }
    else if (obj1->type == TYPE_TYPE) {
        typeValueRef(obj1->value);
    }
    else if (obj1->type == INSTANCE_TYPE) {
        instanceValueRef(obj1->value);
    }
    else if (obj1->type == MOLA_FUNCTION_TYPE) {
        molaFunctionValueRef(obj1->value);
    }
    else if (obj1->type == C_FUNCTION_TYPE) {
        cFunctionValueRef(obj1->value);
    }

    objectsStackPush(obj1);

    ipointer++;
}

/*

When evaluation A op B, A and B are promoted to the highest common type:

String
^
Float
^
Integer
^
Character
^
Boolean
^
Null

All other types cause an error.

All other (arythmetical) operators are handled separatelly.
*/

/*
Arythmetic operations are executed on ints, floats, or strings
Promotions take place
*/

#define promoteToINT()                                                                                                           \
    switch (x->type) {                                                                                                           \
    case NULL_TYPE : {                                                                                                           \
        x_int = (int64_t)0;                                                                                                      \
        break;                                                                                                                   \
    }                                                                                                                            \
    case BOOL_TYPE : {                                                                                                           \
        x_int = (int64_t)x->bool_value;                                                                                          \
        break;                                                                                                                   \
    }                                                                                                                            \
    case CHAR_TYPE : {                                                                                                           \
        x_int = (int64_t)x->char_value;                                                                                          \
        break;                                                                                                                   \
    }                                                                                                                            \
    case INT_TYPE : {                                                                                                            \
        x_int = (int64_t)x->int_value;                                                                                           \
        break;                                                                                                                   \
    }                                                                                                                            \
    }                                                                                                                            \
    switch (y->type) {                                                                                                           \
    case NULL_TYPE : {                                                                                                           \
        y_int = (int64_t)0;                                                                                                      \
        break;                                                                                                                   \
    }                                                                                                                            \
    case BOOL_TYPE : {                                                                                                           \
        y_int = (int64_t)y->bool_value;                                                                                          \
        break;                                                                                                                   \
    }                                                                                                                            \
    case CHAR_TYPE : {                                                                                                           \
        y_int = (int64_t)y->char_value;                                                                                          \
        break;                                                                                                                   \
    }                                                                                                                            \
    case INT_TYPE : {                                                                                                            \
        y_int = (int64_t)y->int_value;                                                                                           \
        break;                                                                                                                   \
    }                                                                                                                            \
    }

#define promoteToFLOAT()                                                                                                         \
    switch (x->type) {                                                                                                           \
    case NULL_TYPE : {                                                                                                           \
        x_float = (double)0;                                                                                                     \
        break;                                                                                                                   \
    }                                                                                                                            \
    case BOOL_TYPE : {                                                                                                           \
        x_float = (double)x->bool_value;                                                                                         \
        break;                                                                                                                   \
    }                                                                                                                            \
    case CHAR_TYPE : {                                                                                                           \
        x_float = (double)x->char_value;                                                                                         \
        break;                                                                                                                   \
    }                                                                                                                            \
    case INT_TYPE : {                                                                                                            \
        x_float = (double)x->int_value;                                                                                          \
        break;                                                                                                                   \
    }                                                                                                                            \
    case FLOAT_TYPE : {                                                                                                          \
        x_float = (double)x->float_value;                                                                                        \
        break;                                                                                                                   \
    }                                                                                                                            \
    }                                                                                                                            \
    switch (y->type) {                                                                                                           \
    case NULL_TYPE : {                                                                                                           \
        y_float = (double)0;                                                                                                     \
        break;                                                                                                                   \
    }                                                                                                                            \
    case BOOL_TYPE : {                                                                                                           \
        y_float = (double)y->bool_value;                                                                                         \
        break;                                                                                                                   \
    }                                                                                                                            \
    case CHAR_TYPE : {                                                                                                           \
        y_float = (double)y->char_value;                                                                                         \
        break;                                                                                                                   \
    }                                                                                                                            \
    case INT_TYPE : {                                                                                                            \
        y_float = (double)y->int_value;                                                                                          \
        break;                                                                                                                   \
    }                                                                                                                            \
    case FLOAT_TYPE : {                                                                                                          \
        y_float = (double)y->float_value;                                                                                        \
        break;                                                                                                                   \
    }                                                                                                                            \
    }

static void exec_LOGICAL_OR(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "LOGICAl_OR failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object   *res;
    static int64_t   x_int, y_int;
    static enum Type type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_TYPE) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int || y_int;
    res   = objectCreate(INT_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_LOGICAL_AND(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "LOGICAL_AND failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object   *res;
    static int64_t   x_int, y_int;
    static enum Type type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_TYPE) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int && y_int;
    res   = objectCreate(BOOL_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_BITWISE_OR(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "BITWISE_OR failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object   *res;
    static int64_t   x_int, y_int;
    static enum Type type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_TYPE) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int | y_int;
    res   = objectCreate(BOOL_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_BITWISE_XOR(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "BITWISE_XOR failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object   *res;
    static int64_t   x_int, y_int;
    static enum Type type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_TYPE) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int ^ y_int;
    res   = objectCreate(INT_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_BITWISE_AND(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "BITWISE_AND failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object   *res;
    static int64_t   x_int, y_int;
    static enum Type type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_TYPE) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int & y_int;
    res   = objectCreate(INT_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

// -1 x=y, 0 x>y, 1 x<y, 2 x!=y (uncomparable)
static int compare(Object *x, Object *y) {
    // fix this shit
    Object *res;
    if (x->type != y->type) {
        return 2;
    }

    switch (x->type) {
    case NULL_TYPE : {
        return -1;
    } break;
    case BOOL_TYPE : {
        if (x->bool_value == y->bool_value) {
            return -1;
        }
        return x->bool_value < y->bool_value;
    } break;
    case CHAR_TYPE : {
        if (x->char_value == y->char_value) {
            return -1;
        }
        return x->char_value < y->char_value;
    } break;
    case INT_TYPE : {
        if (x->int_value == y->int_value) {
            return -1;
        }
        return x->int_value < y->int_value;
    } break;
    case FLOAT_TYPE : {
        if (x->float_value == y->float_value) {
            return -1;
        }
        return x->float_value < y->float_value;
    } break;
    case STRING_TYPE : {
        int r = stringCompare(x->value, y->value);
        if (r == 0) {
            return -1;
        }
        return (r == -1) ? 1 : 0;
    } break;
    case ARRAY_TYPE : {
        ArrayValue *X = x->value, *Y = y->value;
        int64_t     x_length = cvector_size(X->data);
        int64_t     y_length = cvector_size(Y->data);
        size_t      m        = (x_length < y_length) ? x_length : y_length;

        for (size_t i = 0; i < m; i++) {
            int r = compare(X->data[i], Y->data[i]);
            if (r == 2) {
                return 2;
            }
            if (r != -1) {
                return r;    // 0 or 1
            }
        }

        if (x_length < y_length) {
            return 1;
        }
        else if (x_length > y_length) {
            return 0;
        }
        return -1;
    } break;
    case TYPE_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case INSTANCE_TYPE : {
        return 2;    // TODO
    } break;
    case MOLA_FUNCTION_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case C_FUNCTION_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case MODULE_TYPE : {
        return x->value == y->value ? -1 : 2;
    } break;
    case RETURN_ADDRESS_TYPE : {
        return 2;    // lol
    } break;
    }
}

static void exec_EQUAL(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int     r      = compare(x, y) == -1;
    Object *res    = objectCreate(BOOL_TYPE, raw64(r));
    res->is_rvalue = 1;

    objectsStackPush(res);

    ipointer++;
}

static void exec_NOT_EQUAL(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "NOT_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int     r      = compare(x, y) != -1;
    Object *res    = objectCreate(BOOL_TYPE, raw64(r));
    res->is_rvalue = 1;

    objectsStackPush(res);

    ipointer++;
}

static void exec_LESS_THAN(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "LESS_THAN failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int     r      = compare(x, y) == 1;
    Object *res    = objectCreate(BOOL_TYPE, raw64(r));
    res->is_rvalue = 1;

    objectsStackPush(res);

    ipointer++;
}

static void exec_LESS_EQUAL(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "LESS_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int r          = compare(x, y);
    r              = (r == 1 || r == -1);
    Object *res    = objectCreate(BOOL_TYPE, raw64(r));
    res->is_rvalue = 1;

    objectsStackPush(res);

    ipointer++;
}

static void exec_GREATER_THAN(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "LESS_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int     r      = compare(x, y) == 0;
    Object *res    = objectCreate(BOOL_TYPE, raw64(r));
    res->is_rvalue = 1;

    objectsStackPush(res);

    ipointer++;
}

static void exec_GREATER_EQUAL(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "LESS_EQUAL failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    int r          = compare(x, y);
    r              = r == 0 || r == -1;
    Object *res    = objectCreate(BOOL_TYPE, raw64(r));
    res->is_rvalue = 1;

    objectsStackPush(res);

    ipointer++;
}

static void exec_ADDITION(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "ADDITION failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object      *res;
    static int64_t      x_int, y_int;
    static double       x_float, y_float;
    static StringValue *x_string, *y_string;
    static enum Type    type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type > STRING_TYPE) {
        goto OP_ERROR;
    }

    if (type == INT_TYPE) {
        promoteToINT();

        x_int = x_int + y_int;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    else if (type == FLOAT_TYPE) {
        promoteToFLOAT();

        x_float = x_float + y_float;
        res     = objectCreate(FLOAT_TYPE, raw64(x_float));
        goto OP_END;
    }
    else {
        if (x->type != STRING_TYPE || y->type != STRING_TYPE) {
            goto OP_ERROR;
        }
        x_string = (StringValue *)x->value;
        y_string = (StringValue *)y->value;

        x_string = stringConcat(x_string, y_string);
        res      = objectCreate(STRING_TYPE, raw64(x_string));
        goto OP_END;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_SUBTRACTION(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "SUBTRACTION failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object      *res;
    static int64_t      x_int, y_int;
    static double       x_float, y_float;
    static StringValue *x_string, *y_string;
    static enum Type    type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= STRING_TYPE) {
        goto OP_ERROR;
    }

    if (type == INT_TYPE) {
        promoteToINT();

        x_int = x_int - y_int;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    else {
        promoteToFLOAT();

        x_float = x_float - y_float;
        res     = objectCreate(FLOAT_TYPE, raw64(x_float));
        goto OP_END;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_LSHIFT(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "LSHIFT failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object      *res;
    static int64_t      x_int, y_int;
    static double       x_float, y_float;
    static StringValue *x_string, *y_string;
    static enum Type    type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_OPTION) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int << y_int;
    res   = objectCreate(INT_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_RSHIFT(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "RSHIFT failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object      *res;
    static int64_t      x_int, y_int;
    static double       x_float, y_float;
    static StringValue *x_string, *y_string;
    static enum Type    type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_TYPE) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int >> y_int;
    res   = objectCreate(INT_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_MULTIPLICATION(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "MULTIPLICATION failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object      *res;
    static int64_t      x_int, y_int;
    static double       x_float, y_float;
    static StringValue *x_string, *y_string;
    static enum Type    type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= STRING_TYPE) {
        goto OP_ERROR;
    }

    if (type == INT_TYPE) {
        promoteToINT();

        x_int = x_int * y_int;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    else {
        promoteToFLOAT();

        x_float = x_float * y_float;
        res     = objectCreate(FLOAT_TYPE, raw64(x_float));
        goto OP_END;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_DIVISION(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "DIVISION failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object      *res;
    static int64_t      x_int, y_int;
    static double       x_float, y_float;
    static StringValue *x_string, *y_string;
    static enum Type    type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= STRING_TYPE) {
        goto OP_ERROR;
    }

    if (type == INT_TYPE) {
        promoteToINT();

        if (y_int == 0) {
            signalError(ZERO_DIVISION_ERROR_CODE, "Division by zero");
        }

        x_int = x_int / y_int;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    else {
        promoteToFLOAT();

        x_float = x_float / y_float;
        res     = objectCreate(FLOAT_TYPE, raw64(x_float));
        goto OP_END;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_REMAINDER(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "REMAINDER failed: less than 2 elements on the stack");
    }

    Object *y = objectsStackTop();
    objectsStackPop();

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object      *res;
    static int64_t      x_int, y_int;
    static double       x_float, y_float;
    static StringValue *x_string, *y_string;
    static enum Type    type;

    type = x->type > y->type ? x->type : y->type;
    if (type < INT_TYPE) {
        type = INT_TYPE;
    }

    if (type >= FLOAT_TYPE) {
        goto OP_ERROR;
    }

    promoteToINT();

    x_int = x_int % y_int;
    res   = objectCreate(INT_TYPE, raw64(x_int));
    goto OP_END;

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_POSITIVE(Instruction *instr) {
    if (objectsStackSize() < 1) {
        signalError(INTERNAL_ERROR_CODE, "POSITIVE failed: less than 1 element on the stack");
    }

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object *res;
    int64_t        x_int;
    double         x_float;

    switch (x->type) {
    case NULL_TYPE : {
        x_int = 0;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case BOOL_TYPE : {
        x_int = x->bool_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case CHAR_TYPE : {
        x_int = x->char_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case INT_TYPE : {
        x_int = x->int_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case FLOAT_TYPE : {
        x_float = x->float_value;
        res     = objectCreate(FLOAT_TYPE, raw64(x_float));
        goto OP_END;
    }
    default : goto OP_ERROR;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_NEGATION(Instruction *instr) {
    if (objectsStackSize() < 1) {
        signalError(INTERNAL_ERROR_CODE, "NEGATIVE failed: less than 1 element on the stack");
    }

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object *res;
    int64_t        x_int;
    double         x_float;

    switch (x->type) {
    case NULL_TYPE : {
        x_int = -0;    // lmfao
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case BOOL_TYPE : {
        x_int = -x->bool_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case CHAR_TYPE : {
        x_int = -x->char_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case INT_TYPE : {
        x_int = -x->int_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case FLOAT_TYPE : {
        x_float = -x->float_value;
        res     = objectCreate(FLOAT_TYPE, raw64(x_float));
        goto OP_END;
    }
    default : goto OP_ERROR;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_INVERTION(Instruction *instr) {
    if (objectsStackSize() < 1) {
        signalError(INTERNAL_ERROR_CODE, "INVERTION failed: less than 1 element on the stack");
    }

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object *res;
    int64_t        x_int;
    double         x_float;

    switch (x->type) {
    case NULL_TYPE : {
        x_int = ~0;    // lmfao
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case BOOL_TYPE : {
        x_int = ~x->bool_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case CHAR_TYPE : {
        x_int = ~x->char_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    case INT_TYPE : {
        x_int = ~x->int_value;
        res   = objectCreate(INT_TYPE, raw64(x_int));
        goto OP_END;
    }
    default : goto OP_ERROR;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

static void exec_LOGICAL_NOT(Instruction *instr) {
    if (objectsStackSize() < 1) {
        signalError(INTERNAL_ERROR_CODE, "LOGICAL_NOT failed: less than 1 element on the stack");
    }

    Object *x = objectsStackTop();
    objectsStackPop();

    static Object *res;
    int64_t        x_int;
    double         x_float;

    switch (x->type) {
    case NULL_TYPE : {
        x_int = 1;
        res   = objectCreate(BOOL_TYPE, raw64(x_int));
        goto OP_END;
    }
    case BOOL_TYPE : {
        x_int = !x->bool_value;
        res   = objectCreate(BOOL_TYPE, raw64(x_int));
        goto OP_END;
    }
    case CHAR_TYPE : {
        x_int = !x->char_value;
        res   = objectCreate(BOOL_TYPE, raw64(x_int));
        goto OP_END;
    }
    case INT_TYPE : {
        x_int = !x->int_value;
        res   = objectCreate(BOOL_TYPE, raw64(x_int));
        goto OP_END;
    }
    case FLOAT_TYPE : {
        x_int = !x->float_value;
        res   = objectCreate(BOOL_TYPE, raw64(x_int));
        goto OP_END;
    }
    case STRING_TYPE : {
        x_int = ((StringValue *)x->value)->length == 0;
        res   = objectCreate(BOOL_TYPE, raw64(x_int));
        goto OP_END;
    }
    default : goto OP_ERROR;
    }

OP_ERROR:

    signalError(VALUE_ERROR_CODE, "Unsupported operation");

OP_END:
    res->is_rvalue = 1;
    objectsStackPush(res);

    ipointer++;
}

/* when executiong A:B, caller is set to A
so that it is possible to pass it as the owner in case we want to call the retrieved method*/
Object *caller = NULL;

static void exec_CALL(Instruction *instr) {
    static int64_t n = 0;
    n                = instr->int_arg1;

    static MolaFunctionValue *mola_function = NULL;
    static CFunctionValue    *c_function    = NULL;

    if (objectsStackSize() < n + 1) {
        signalError(INTERNAL_ERROR_CODE, "CALL failed: too few objects on the stack");
    }

    static Object *f = NULL;
    f                = objects_stack[objectsStackSize() - 1];
    mola_function    = (MolaFunctionValue *)f->value;
    c_function       = (CFunctionValue *)f->value;

    if (f->type != C_FUNCTION_TYPE && f->type != MOLA_FUNCTION_TYPE) {
        signalError(VALUE_ERROR_CODE, "Not callable");
    }

    if (f->type == C_FUNCTION_TYPE && c_function->n_args != UNLIMITED_ARGS && c_function->n_args != n + c_function->is_method) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, errstrfmt("Expected %d arguments, got %d", c_function->n_args, n));
    }
    else if (f->type == MOLA_FUNCTION_TYPE && mola_function->n_args != n + mola_function->is_method) {
        signalError(WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE, errstrfmt("Expected %d arguments, got %d", mola_function->n_args, n));
    }

    static Object **args        = NULL;
    size_t          passed_args = 0;
    if (f->type == MOLA_FUNCTION_TYPE) {
        int offset = 0;
        if (mola_function->is_method) {
            scopeInsert(current_scope, mola_function->args[0], caller);

            ReferencedObject r;
            r.obj = caller;
            r.ip  = ipointer + 1;
            cvector_push_back(referenced_stack, r);
            caller = NULL;

            offset = 1;
        }
        for (int64_t i = 0; i < n; i++) {
            Object *arg = objects_stack[objectsStackSize() - 2 - (n - i - 1)];

            scopeInsert(current_scope, mola_function->args[i + offset], arg);
        }
    }
    else {
        passed_args = n + c_function->is_method;
        args        = allocOrError(sizeof(Object *) * passed_args);
        int offset  = 0;
        if (c_function->is_method) {
            args[0] = caller;

            ReferencedObject r;
            r.obj = caller;
            r.ip  = ipointer + 1;
            cvector_push_back(referenced_stack, r);
            caller = NULL;

            offset = 1;
        }
        for (int64_t i = 0; i < n; i++) {
            args[i + offset] = objects_stack[objectsStackSize() - 2 - (n - i - 1)];
        }
    }

    for (int i = 0; i < n + 1; i++) {
        objectsStackPop();
    }

    if (f->type == MOLA_FUNCTION_TYPE) {
        int64_t r   = ipointer + 1;
        Object *ret = objectCreate(RETURN_ADDRESS_TYPE, raw64(r));
        objectsStackPush(ret);

        ipointer = mola_function->relative_offset + current_env->absolute_offset;
    }
    else {
        Object *res = c_function->function(passed_args, args);
        freeBytes(args);

        objectsStackPush(res);

        ipointer++;

        destroyCheckpoint();    // since there is not going to be a RETURN statement for this call
    }
}

static void exec_ACCESS(Instruction *instr) {
    if (objectsStackSize() < 2) {
        signalError(INTERNAL_ERROR_CODE, "ACCESS failed: not enough objects on the stack");
    }

    Object *index = objectsStackTop();
    objectsStackPop();
    Object *obj = objectsStackTop();
    objectsStackPop();

    if ((obj->type != ARRAY_TYPE && obj->type != STRING_TYPE) || index->type >= FLOAT_TYPE) {
        signalError(VALUE_ERROR_CODE, "Unsupported operation");
    }

    int64_t x_int;
    switch (index->type) {
    case NULL_TYPE : {
        x_int = (int64_t)0;
        break;
    }
    case BOOL_TYPE : {
        x_int = (int64_t)index->bool_value;
        break;
    }
    case CHAR_TYPE : {
        x_int = (int64_t)index->char_value;
        break;
    }
    case INT_TYPE : {
        x_int = (int64_t)index->int_value;
        break;
    }
    }

    Object *res;

    if (obj->type == ARRAY_TYPE) {
        res = arrayValueIndexAccess(obj->value, x_int);
    }
    else {
        char c = stringValueIndexAccess(obj->value, x_int);
        res    = objectCreate(CHAR_TYPE, raw64(c));
    }

    objectsStackPush(res);

    ipointer++;
}

static void exec_LOAD_BOOL(Instruction *instr) {
    Object *obj    = objectCreate(BOOL_TYPE, raw64(instr->int_arg1));
    obj->is_rvalue = 1;

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_CHAR(Instruction *instr) {
    Object *obj    = objectCreate(CHAR_TYPE, raw64(instr->int_arg1));
    obj->is_rvalue = 1;

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_INT(Instruction *instr) {
    Object *obj    = objectCreate(INT_TYPE, raw64(instr->int_arg1));
    obj->is_rvalue = 1;

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_FLOAT(Instruction *instr) {
    Object *obj    = objectCreate(FLOAT_TYPE, raw64(instr->float_arg1));
    obj->is_rvalue = 1;

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_STRING(Instruction *instr) {
    StringValue *value = stringValueCreate(strlen(instr->string_arg1), instr->string_arg1);
    Object      *obj   = objectCreate(STRING_TYPE, raw64(value));

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD_NULL(Instruction *instr) {
    Object *obj    = objectCreate(NULL_TYPE, 0);
    obj->is_rvalue = 1;

    objectsStackPush(obj);
    ipointer++;
}

static void exec_LOAD(Instruction *instr) {
    /*
    0. look for a global object in the builtin(0) environment
    1. look for a global object
    2. then look for a local object, or report error
    */

    Object *res = identMapGet(&envGetById(0)->globals, instr->ident_arg1);
    if (res != NULL) {
        objectsStackPush(res);
        ipointer++;

        return;
    }

    res = identMapGet(&current_env->globals, instr->ident_arg1);
    if (res != NULL) {
        objectsStackPush(res);
        ipointer++;

        return;
    }

    res = scopeRecursiveLookup(current_scope, instr->ident_arg1);

    objectsStackPush(res);
    ipointer++;
}

static void exec_LOAD_FIELD(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "LOAD_FIELD failed: empty objects stack");
    }
    Object *obj = objectsStackTop();
    objectsStackPop();

    // handle strings and arrays?

    if (obj->type == MODULE_TYPE) {
        Env    *env = (Env *)obj->value;
        Object *res = identMapGet(&env->exported_objects, instr->ident_arg1);

        if (res == NULL) {
            signalError(NAME_ERROR_CODE, "Failed to locate an exported object with this name");
        }
        objectsStackPush(res);
        ipointer++;

        return;
    }
    if (obj->type != INSTANCE_TYPE) {
        signalError(VALUE_ERROR_CODE, "Unsupported operation");
    }

    Object *field = instanceValueLookupField(obj->value, instr->ident_arg1);
    objectsStackPush(field);

    ipointer++;
}

static void exec_LOAD_METHOD(Instruction *instr) {
    // TODO: handle string and array

    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "LOAD_METHOD failed: empty objects stack");
    }
    Object *obj = objectsStackTop();
    objectsStackPop();

    if (obj->type == ARRAY_TYPE) {
        Object *method = arrayValueLookupMethod(obj->value, instr->ident_arg1);

        objectsStackPush(method);
        if (caller != NULL) {
            unref(caller);
        }
        caller = obj;
        ref(caller);
        ipointer++;

        return;
    }
    else if (obj->type == STRING_TYPE) {
        Object *method = stringValueLookupMethod(obj->value, instr->ident_arg1);

        objectsStackPush(method);
        if (caller != NULL) {
            unref(caller);
        }
        caller = obj;
        ref(caller);
        ipointer++;

        return;
    }

    if (obj->type != INSTANCE_TYPE) {
        signalError(VALUE_ERROR_CODE, "Unsupported operation");
    }

    Object *method = instanceValueLookupMethod(obj->value, instr->ident_arg1);
    objectsStackPush(method);

    if (caller != NULL) {
        unref(caller);
    }
    caller = obj;
    ref(caller);

    ipointer++;
}

extern TypeValue *array_type_ptr;    // used to create an array via NEW

static void exec_NEW(Instruction *instr) {
    if (objectsStackEmpty()) {
        signalError(INTERNAL_ERROR_CODE, "NEW failed: objects stack empty");
    }

    Object *type = objectsStackTop();
    objectsStackPop();

    if (type->value == array_type_ptr) {
        ArrayValue *array = arrayValueCreate();
        Object     *obj   = objectCreate(ARRAY_TYPE, raw64(array));
        objectsStackPush(obj);

        ipointer++;

        return;
    }

    if (type->type != TYPE_TYPE) {
        signalError(VALUE_ERROR_CODE, "Not a type");
    }

    InstanceValue *instance = instanceValueCreate(type->value);
    Object        *obj      = objectCreate(INSTANCE_TYPE, raw64(instance));
    objectsStackPush(obj);

    ipointer++;
}

static void exec_UNREF(Instruction *instr) {
    if (!cvector_empty(referenced_stack)) {
        ReferencedObject top = *cvector_back(referenced_stack);

        if (top.ip == ipointer) {
            unref(top.obj);
            cvector_pop_back(referenced_stack);
        }
    }

    ipointer++;
}

static void handleError() {
    Instruction  *instr = vmCurrentInstruction();
    ErrorHandler *h     = NULL;
    while (!cvector_empty(error_handlers_stack)) {
        h = cvector_back(error_handlers_stack);

        if (h->error_code == molaErrorCode || h->error_code == -1) {
            break;
        }

        h = NULL;
        cvector_pop_back(error_handlers_stack);
    }

    if (h == NULL) {
        // failed to find an error handler
        printError(molaErrorCode, molaErrorReason);
    }

    // found a respective handler

    cvector_resize(objects_stack, h->stack_frame_size, NULL);
    cvector_resize(error_checkpoints, h->error_checkpoints_size, 0);
    current_scope = h->scope;
    ipointer      = h->absolute_offset;

    InstanceValue *error = instanceValueCreate(error_type);

    instanceValueSetField(error, symtabInsert(lex_symtab, "code"), objectCreate(INT_TYPE, raw64(molaErrorCode)));
    StringValue *reason = stringValueCreate(strlen(molaErrorReason), molaErrorReason);
    instanceValueSetField(error, symtabInsert(lex_symtab, "reason"), objectCreate(STRING_TYPE, raw64(reason)));
    StringValue *module = stringValueCreate(strlen(instr->filename), instr->filename);
    instanceValueSetField(error, symtabInsert(lex_symtab, "module"), objectCreate(STRING_TYPE, raw64(module)));
    instanceValueSetField(error, symtabInsert(lex_symtab, "line"), objectCreate(INT_TYPE, raw64(instr->lineno)));
    Object *error_obj = objectCreate(INSTANCE_TYPE, raw64(error));

    objectsStackPush(error_obj);
}

ivec compileProgram(char *filename, int64_t *env_id) {
    molalog("Compiling %s\n", filename);
    parserSetFilename(filename);
    AstNode *ast = runParser();
    molalog("Parsing complete\n");

    *env_id = envGenAvailableId();

    molalog("Compiling (env=%lld)...\n", *env_id);
    int64_t t_before     = clock();
    ilist   instructions = genCompile(ast);
    int64_t t_after      = clock();

    molalog("Generated %d instructions in %.3f seconds\n", instructions.size, 1.0 * (t_after - t_before) / CLOCKS_PER_SEC);

    molalog("Creating log\n");
    int fd;
    if (instructions.size > 1000) {
        fd = dup(1);
        close(1);
        static char buf[1024];
        sprintf(buf, "/home/lis05/Projects/mola/logs/compiled_%s.txt", basename(filename));
        open(buf, O_RDWR | O_CREAT | O_TRUNC, "644");
    }

    ivec    to_execute = NULL;
    inode  *node       = instructions.head;
    int64_t pos        = env_offset;
    while (node != NULL) {
        genPrintInstrShort(pos, &node->ins);
        cvector_push_back(to_execute, node->ins);
        node = node->next;
        pos++;
    }
    if (instructions.size > 1000) {
        close(1);
        dup2(fd, 1);
    }

    return to_execute;
}
