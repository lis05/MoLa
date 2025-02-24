#include "parser.h"

char filename[1024];

extern int      lineno;
extern int      column;
extern FILE    *yyin;
extern char    *yytext;
extern int      yyleng;
extern AstNode *node_result;
extern int      yyparse();

extern Symtab *lex_symtab;

static FILE *openFilename() {
    FILE *res = fopen(filename, "r");
    if (res == NULL) {
        fprintf(stderr, "Failed to open %s: ", filename);
        perror("");
        exit(1);
    }

    return res;
}

void parserSetFilename(char *str) {
    strcpy(filename, str);
}

static void propagateFilename(AstNode *root, char *const f) {
    if (root == NULL) {
        return;
    }

    root->filename = f;
    for (int i = 0; i < root->n_nodes; i++) {
        propagateFilename(root->nodes[i], f);
    }
}

void initParser() {
    lex_symtab = symtabCreate();
}

AstNode *runParser() {
    yyin   = openFilename();
    lineno = 1;
    column = 1;
    yyparse();
    fclose(yyin);
    yyin = NULL;

    // we have to insert a filename pointer into each node
    // this pointer will be the same one for all nodes
    // and therefore has to be freed only ones (for the root, for example)

    char *f = strdup(filename);
    propagateFilename(node_result, f);

    return node_result;
}

void printError(char *message) {
    FILE *file = openFilename();

    int line = 1, col = 1;
    while (line != lineno) {
        while (fgetc(file) != '\n') {
            col++;
        }
        line++;
    }

    fprintf(stderr, "Error in %s (line %d, column %d):\n", filename, lineno, column);
    static char str[64] = {};
    sprintf(str, "  %d | ", lineno);
    fprintf(stderr, str);

    char c;
    while (1) {
        c = fgetc(file);
        if (c == '\n' || c == EOF) {
            break;
        }
        fprintf(stderr, "%c", c);
    }
    fprintf(stderr, "\n");

    for (int i = 0; i < strlen(str) - 2; i++) {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "| ");
    for (int i = 1; i < column; i++) {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "^");
    for (int i = 0; i < yyleng - 1; i++) {
        fprintf(stderr, "~");
    }
    fprintf(stderr, " %s\n", message);
    exit(1);
}

void yyerror(const char *str) {
    printError((char *)str);
}
