#include "api.h"
#include <fcntl.h>
#include <sys/unistd.h>
#include <time.h>

int main() {
    molalog("Starting parser\n");
    initParser();
    parserSetFilename("/home/lis05/Projects/mola/tests/vm.txt");
    AstNode *ast = runParser();
    molalog("Parsing complete\n");

    molalog("Compiling ...\n");
    envInit();
    int64_t t_before     = clock();
    ilist   instructions = genCompile(ast);
    int64_t t_after      = clock();

    molalog("Generated %d instructions in %.3f seconds\n",
            instructions.size,
            1.0 * (t_after - t_before) / CLOCKS_PER_SEC);

    molalog("Creating log: compiled.txt ...\n");
    int fd;
    if (instructions.size > 50) {
        fd = dup(1);
        close(1);
        open("/home/lis05/Projects/mola/logs/compiled.txt", O_RDWR | O_CREAT | O_TRUNC);
    }

    ivec    to_execute;
    inode  *node = instructions.head;
    int64_t pos  = 0;
    while (node != NULL) {
        genPrintInstrShort(pos, &node->ins);
        cvector_push_back(to_execute, node->ins);
        node = node->next;
        pos++;
    }
    if (instructions.size > 50) {
        close(1);
        dup2(fd, 1);
    }

    molalog("Starting vm ...\n");

    allocInit();

    t_before = clock();
    vmExecute(to_execute);
    t_after = clock();

    printf("Execution finished after %.3f seconds\n", 1.0 * (t_after - t_before) / CLOCKS_PER_SEC);

    return 0;
}

// TODO: module_path
