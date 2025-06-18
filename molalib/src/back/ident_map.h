#ifndef __mola_ident_map_h__
#define __mola_ident_map_h__

#include "../front/symtab.h"
#include "../util.h"

// TODO: improve

struct Object;

typedef struct IdentMap {
    cvector_vector_type(struct Object *) items;
} IdentMap;

IdentMap identMapCreate();
void     identMapSet(IdentMap *map, ident key, struct Object *item);
int      identMapQuery(IdentMap *map, ident key);
void    *identMapGet(IdentMap *map, ident key);                       // NULL if absent
void     identMapDestroy(IdentMap *map);
void     identMapGCOnlyUnref(IdentMap *map);
void     identMapGCDestroy(IdentMap *map);
void     identMapApply(IdentMap *map, void (*f)(struct Object *));    // used by gc

#endif
