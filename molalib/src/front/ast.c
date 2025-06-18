#include "ast.h"
#include "../back/alloc.h"    // this is shit
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

AstNode *make(int type, int option, size_t lineno, size_t n_nodes, ...) {
    AstNode *node = (AstNode *)allocOrError(sizeof(AstNode));
    node->type    = type;
    node->option  = option;
    node->lineno  = lineno;
    node->n_nodes = n_nodes;

    AstNode **list = (AstNode **)allocOrError(n_nodes * sizeof(AstNode *));

    va_list ap;
    va_start(ap, n_nodes);
    for (int i = 0; i < n_nodes; i++) {
        list[i] = va_arg(ap, AstNode *);
    }

    node->nodes = list;

    va_end(ap);
    return node;
}
