#include "env.h"
#include "../util.h"

#define MAX_ENVS 10000    // if you need more - go see a doctor

static Env   *envs[MAX_ENVS];
static size_t n_envs = 0;

int64_t envGenAvailableId() {
    return n_envs;
}

struct Env *envGetById(int64_t id) {
    return NULL;
}

int64_t envCreate() {}

void envInit() {}
