#include "ident_map.h"
#include "object.h"
#include "stat.h"

IdentMap identMapCreate() {
    stat_created_ident_maps++;
    IdentMap res;
    res.items = NULL;
    cvector_reserve(res.items, 10);

    return res;
}

void identMapSet(IdentMap *map, ident key, void *item) {
    assert(map != NULL);
    if (cvector_size(map->items) < key + 1) {
        cvector_resize(map->items, key + 1, NULL);
    }

    if (map->items[key] != NULL) {
        unref(map->items[key]);
    }
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

void *identMapGet(IdentMap *map, ident key) {
    assert(map != NULL);

    if (cvector_size(map->items) <= key) {
        return NULL;
    }

    return map->items[key];
}

void identMapDestroy(IdentMap *map) {
    stat_created_ident_maps--;
    for (int i = 0; i < cvector_size(map->items); i++) {
        if (map->items[i] != NULL) {
            unref(map->items[i]);
        }
    }

    cvector_free(map->items);
    map->items = NULL;
}
