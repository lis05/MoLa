#include "env.h"
#include "../util.h"
#include "alloc.h"
#include "object.h"

#define MAX_ENVS 10000    // if you need more - go see a doctor

static Env   *envs[MAX_ENVS];
static size_t n_envs = 0;

int64_t envGenAvailableId() {
    return n_envs;
}

struct Env *envGetById(int64_t id) {
    return envs[id];
}

int64_t envCreate(int64_t absolute_offset, char *path) {
    Env *env              = allocBytesOrError(sizeof(Env));
    env->absolute_offset  = absolute_offset;
    env->exported_objects = identMapCreate();
    env->globals          = identMapCreate();
    env->path             = strdup(path);

    int64_t id = envGenAvailableId();
    envs[id]   = env;
    n_envs++;

    return id;
}

void envInit() {
    memset(envs, 0, sizeof(envs));
}
