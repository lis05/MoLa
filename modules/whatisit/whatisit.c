#include "../../molalib/src/api.h"

Object *func(size_t n_args, struct Object **args) {
    printf("What is it? Mola!\n");
    return objectCreate(NULL_TYPE, 0);
}
CFunctionValue *cmodprFUNC__whatisit(Env *env) {
    return cFunctionValueCreate(env, 0, func);
}