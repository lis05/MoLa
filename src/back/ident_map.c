#include "ident_map.h"
#include "object.h"

IdentMap identMapCreate() {
    IdentMap res;
    res.items = NULL;
    cvector_reserve(res.items, 10);

    return res;
}

void identMapSet(IdentMap *map, ident key, struct Object *item) {
    assert(map != NULL);
    cvector_resize(map->items, 2 * key + 1, NULL);

    map->items[key] = item;
    ref(item);
}

int identMapQuery(IdentMap *map, ident key) {
    assert(map != NULL);

    if (cvector_size(map->items) <= key) {
        return 0;
    }

    return map->items[key] != NULL;
}

Object *identMapGet(IdentMap *map, ident key) {
    assert(map != NULL);

    if (cvector_size(map->items) <= key) {
        return NULL;
    }

    return map->items[key];
}

void identMapDestroy(IdentMap *map) {
    for (int i = 0; i < cvector_size(map->items); i++) {
        if (map->items[i] != NULL) {
            unref(map->items[i]);
        }
    }

    cvector_free(map->items);
    map->items = NULL;
}
