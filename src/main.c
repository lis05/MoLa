#include "front/parser.h"

int main() {
    printf("... Starting parser ...\n");
    initParser();
    parserSetFilename("/home/lis05/Projects/mola/tests/parser.txt");
    Node *res = runParser();
    printf("... Parsing complete ...\n");
    return 0;
}

// TODO: module_path
