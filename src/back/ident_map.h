#ifndef __mola_ident_map_h__
#define __mola_ident_map_h__

#include "../front/symtab.h"
#include "../util.h"

// This will have to be improved significantly in the future

struct Object;

typedef struct IdentMap {
    cvector_vector_type(struct Object *) items;
} IdentMap;

IdentMap       identMapCreate();
void           identMapSet(IdentMap *map, ident key, struct Object *item);
int            identMapQuery(IdentMap *map, ident key);
struct Object *identMapGet(IdentMap *map, ident key);    // NULL if absent
void           identMapDestroy(IdentMap *map);

#endif
