#include "error.h"
#include "gen.h"
#include "vm.h"
#include <stdio.h>

jmp_buf __mola_errorbuf;
char    __mola_errstrfmtbuf[1024];

#define RANGE 3
extern cvector_vector_type(int64_t) error_checkpoints;

void reportLine(FILE *file, int64_t instr_ip, char *reason, int64_t index) {
    fseek(file, 0, SEEK_SET);
    Instruction *cur = vmInstruction(instr_ip);

    int     line = 1, col = 1;
    int64_t L = cur->lineno - RANGE;
    if (L < 1) {
        L = 1;
    }
    while (line != L) {
        while (fgetc(file) != '\n') {
            col++;
        }
        line++;
    }

    fprintf(stderr, "Traceback %ld, %s: %s (line %d):\n", index, reason, cur->filename, cur->lineno);
    for (int i = 0; i < cur->lineno - L; i++) {
        static char str[64] = {};
        sprintf(str, "  %d | ", L + i);
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
    }
    static char str[64] = {};
    sprintf(str, "  %d | ", cur->lineno);
    fprintf(stderr, str);

    fprintf(stderr, "\e[41m");
    char c;
    while (1) {
        c = fgetc(file);
        if (c == '\n' || c == EOF) {
            break;
        }
        fprintf(stderr, "%c", c);
    }
    fprintf(stderr, "\e[0m");
    fprintf(stderr, "\n");

    for (int i = 0; i < RANGE; i++) {
        static char str[64] = {};
        sprintf(str, "  %d | ", cur->lineno + i + 1);
        fprintf(stderr, str);

        char c;
        while (1) {
            c = fgetc(file);
            if (c == '\n') {
                break;
            }
            if (c == EOF) {
                fprintf(stderr, "\n");
                goto END;
            }
            fprintf(stderr, "%c", c);
        }
        fprintf(stderr, "\n");
    }
END:;
}

void signalError(int64_t code, char *reason) {
    // TODO: rename this to printError, signalError should handle try/catch 

    // TODO: proper error handling
    Instruction *cur = vmCurrentInstruction();

    FILE *file = fopen(cur->filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open %s: ", cur->filename);
        perror("");
        exit(1);
    }

    int64_t index = 1;
    for (int64_t i = 0; i + 1 < cvector_size(error_checkpoints); i++) {
        reportLine(file, error_checkpoints[i], "the error below happened while executing the following", index++);
    }

    reportLine(file, *cvector_back(error_checkpoints), "Runtime error", 0);

    fprintf(stderr, "\n >>> ");

    switch (code) {
    case INTERNAL_ERROR_CODE : fprintf(stderr, "InternalError:"); break;
    case IMPORT_ERROR_CODE : fprintf(stderr, "ImportError:"); break;
    case NAME_COLLISION_ERROR_CODE : fprintf(stderr, "NameCollisionError:"); break;
    case DUPLICATE_NAME_ERROR_CODE : fprintf(stderr, "DuplicateNameError:"); break;
    case VALUE_ERROR_CODE : fprintf(stderr, "ValueError:"); break;
    case NAME_ERROR_CODE : fprintf(stderr, "NameError:"); break;
    case WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE : fprintf(stderr, "WrongNumberOfArgumentsError:"); break;
    case OUT_OF_BOUNDS_ERROR_CODE : fprintf(stderr, "OutOfBoundsError:"); break;
    }
    fprintf(stderr, " %s\n", reason);
    exit(1);
}
