#include "symtab.h"
#include "../util.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// otherwise the world explodes
#define MAX_IDENTS 10000

static char *ident2str[MAX_IDENTS];

static Symtab *newNode() {
    Symtab *node = (Symtab *)malloc(sizeof(Symtab));
    node->value  = -1;
    for (int i = 0; i < TRIE_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

static int getpos(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A';
    }
    else if ('a' <= c && c <= 'z') {
        return 26 + c - 'a';
    }
    else if ('0' <= c && c <= '9') {
        return 52 + c - '0';
    }
    else if (c == '_') {
        return 62;
    }

    assert(0);
}

Symtab *symtabCreate() {
    Symtab *root = newNode();
    root->value  = 0;
    return root;
}

ident symtabInsert(Symtab *root, char *str) {
    assert(root != NULL);
    assert(str != NULL);
    assert(*str != '\0');

    Symtab *node    = root;
    char   *origstr = str;
    while (*str != '\0') {
        int pos = getpos(*str);
        str++;
        if (node->children[pos] != NULL) {
            node = node->children[pos];
        }
        else {
            node = node->children[pos] = newNode();
        }
    }

    if (node->value == -1) {
        if (root->value + 1 >= MAX_IDENTS) {
            // rough and ready
            fprintf(stderr, "Stupid error: too many identifiers\n");
            exit(1);
        }

        node->value = root->value++;
        molalog("New ident %d[%s]\n", node->value, origstr);
        ident2str[node->value] = strdup(origstr);
    }
    return node->value;
}

/**
 * @return -1 if str is not present in the symtab, otherwise the associated identifier.
 */
ident symtabLookup(Symtab *root, char *str) {
    assert(root != NULL);
    assert(str != NULL);
    assert(*str != '\0');

    Symtab *node = root;
    while (*str != '\0') {
        int pos = getpos(*str);
        str++;
        if (node->children[pos] != NULL) {
            node = node->children[pos];
        }
        else {
            return -1;
        }
    }

    return node->value;
}

void symtabDestroy(Symtab *root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < TRIE_CHILDREN; i++) {
        symtabDestroy(root->children[i]);
    }

    free(root);
}

char *symtabIdentToString(ident value) {
    if (value >= MAX_IDENTS) {
        fprintf(stderr, "Stupid error: identifier too big\n");
        exit(1);
    }

    return ident2str[value];
}
