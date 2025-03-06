#include "env.h"
#include "../util.h"

#define MAX_ENVS 10000    // if you need more - go see a doctor

static Env   *envs[MAX_ENVS];
static size_t n_envs = 0;

size_t envGenAvailableId() {
    return n_envs;
}

struct Env *envGetById(size_t id) {
    return NULL;
}

void envCreate() {}

void envInit() {}
