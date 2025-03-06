#include "api.h"

int main() {
    molalog("Starting parser\n");
    initParser();
    parserSetFilename("/home/lis05/Projects/mola/tests/gen.txt");
    AstNode *ast = runParser();
    molalog("Parsing complete\n");

    envInit();
    ivec instructions = genCompile(ast);
    molalog("Generated %d instructions\n", cvector_size(instructions));

    for (int i = 0; i < cvector_size(instructions); i++) {
        genPrintInstrShort(&instructions[i]);
    }
    return 0;
}

// TODO: module_path
