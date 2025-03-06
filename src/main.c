#include "api.h"

int main() {
    molalog("Starting parser\n");
    initParser();
    parserSetFilename("/home/lis05/Projects/mola/tests/gen.txt");
    AstNode *ast = runParser();
    molalog("Parsing complete\n");

    envInit();
    ilist instructions = genCompile(ast);
    molalog("Generated %d instructions\n", instructions.size);

    inode *node = instructions.head;
    while (node != NULL) {
        genPrintInstrShort(&node->ins);
        node = node->next;
    }

    return 0;
}

// TODO: module_path
