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
    int64_t pos = 0;
    while (node != NULL) {
        genPrintInstrShort(pos, &node->ins);
        node = node->next;
        pos++;
    }

    return 0;
}

// TODO: module_path
