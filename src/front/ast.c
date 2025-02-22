#include "ast.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Node *make(int type, int flag, size_t lineno, size_t n_nodes, ...) {
    Node *node    = (Node *)malloc(sizeof(Node));
    node->type    = type;
    node->flag    = flag;
    node->lineno  = lineno;
    node->n_nodes = n_nodes;

    Node **list = (Node **)calloc(n_nodes, sizeof(Node *));

    va_list ap;
    va_start(ap, n_nodes);
    for (int i = 0; i < n_nodes; i++) {
        list[i] = va_arg(ap, Node *);
    }

    node->nodes = list;

    va_end(ap);
    return node;
}