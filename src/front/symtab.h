#ifndef __symtab_h__
#define __symtab_h__

#include "ast.h"

#define TRIE_CHILDREN (26 + 26 + 1 + 10)    // a-zA-Z_0-9

typedef struct Symtab {
    struct Symtab *children[TRIE_CHILDREN];

    // if this is the root node, then value stores the size of the trie (counter)
    // if there are no strings ending at this node, value is -1
    ident value;

} Symtab;

Symtab *symtabCreate();
ident   symtabInsert(Symtab *root, char *str);
/**
 * @return -1 if str is not present in the symtab, otherwise the associated identifier.
 */
ident   symtabLookup(Symtab *root, char *str);
void    symtabDestroy(Symtab *root);

char *symtabIdentToString(ident value);

#endif
