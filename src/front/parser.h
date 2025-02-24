#ifndef __parser_h__
#define __parser_h__

#include "ast.h"
#include "symtab.h"
#include <stdlib.h>
#include <string.h>

void     parserSetFilename(char *str);
void     initParser();
AstNode *runParser();
void     printError(char *msg);

#endif
