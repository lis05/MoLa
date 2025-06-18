%{
    #include <stdlib.h>
    #include <stdint.h>
    #include "ast.h"
    #include "symtab.h"
    #include "rules.tab.h"

    void yyerror(const char *);
    static void comment();
    static char parseChar(char *data);
    static char *parseString(char *data);
    static void count();
    int lineno;
    int column;
    static int column_add = 0;
    Symtab *lex_symtab;
%}

D			        [0-9]
L			        [a-zA-Z_]


%%
\/\/.*              { count(); }

"/*"([^*]|\*+[^*/])*\*+"/" { count(); }

"import"            { count(); yylval.num = lineno; return IMPORT; }
"export"            { count(); yylval.num = lineno; return EXPORT; }
"global"            { count(); yylval.num = lineno; return GLOBAL; }
"function"          { count(); yylval.num = lineno; return FUNCTION; }
"type"              { count(); yylval.num = lineno; return TYPE; }
"method"            { count(); yylval.num = lineno; return METHOD; }
"constructor"       { count(); yylval.num = lineno; return CONSTRUCTOR; }
"destructor"        { count(); yylval.num = lineno; return DESTRUCTOR; }
"of"                { count(); yylval.num = lineno; return OF; }
"while"             { count(); yylval.num = lineno; return WHILE; }
"for"               { count(); yylval.num = lineno; return FOR; }
"if"                { count(); yylval.num = lineno; return IF; }
"else"              { count(); yylval.num = lineno; return ELSE; }
"continue"          { count(); yylval.num = lineno; return CONTINUE; }
"break"             { count(); yylval.num = lineno; return BREAK; }
"return"            { count(); yylval.num = lineno; return RETURN; }
"try"               { count(); yylval.num = lineno; return TRY; }
"catch"             { count(); yylval.num = lineno; return CATCH; }
"finally"           { count(); yylval.num = lineno; return FINALLY; }
"as"                { count(); yylval.num = lineno; return AS; }
"signal"            { count(); yylval.num = lineno; return SIGNAL; }
"because"           { count(); yylval.num = lineno; return BECAUSE; }
"var"               { count(); yylval.num = lineno; return VAR; }
"when"              { count(); yylval.num = lineno; return WHEN; }
"then"              { count(); yylval.num = lineno; return THEN; }
"new"               { count(); yylval.num = lineno; return NEW; }
"or"                { count(); yylval.num = lineno; return OR; }
"and"               { count(); yylval.num = lineno; return AND; }
"lshift"            { count(); yylval.num = lineno; return LSHIFT; }
"rshift"            { count(); yylval.num = lineno; return RSHIFT; }
"not"               { count(); yylval.num = lineno; return NOT; }
"=="                { count(); yylval.num = lineno; return EQ; }       
"!="                { count(); yylval.num = lineno; return NE; }       
"<="                { count(); yylval.num = lineno; return LE; }       
">="                { count(); yylval.num = lineno; return GE; }   
"("                 { count(); yylval.num = lineno; return '('; }  
")"                 { count(); yylval.num = lineno; return ')'; }  
"{"                 { count(); yylval.num = lineno; return '{'; } 
"}"                 { count(); yylval.num = lineno; return '}'; }  
"["                 { count(); yylval.num = lineno; return '['; } 
"]"                 { count(); yylval.num = lineno; return ']'; } 
","                 { count(); yylval.num = lineno; return ','; } 
";"                 { count(); yylval.num = lineno; return ';'; } 
"*"                 { count(); yylval.num = lineno; return '*'; } 
"/"                 { count(); yylval.num = lineno; return '/'; } 
"%"                 { count(); yylval.num = lineno; return '%'; } 
"+"                 { count(); yylval.num = lineno; return '+'; } 
"-"                 { count(); yylval.num = lineno; return '-'; } 
"~"                 { count(); yylval.num = lineno; return '~'; } 
"="                 { count(); yylval.num = lineno; return '='; } 
"|"                 { count(); yylval.num = lineno; return '|'; } 
"^"                 { count(); yylval.num = lineno; return '^'; } 
"&"                 { count(); yylval.num = lineno; return '&'; } 
"<"                 { count(); yylval.num = lineno; return '<'; } 
">"                 { count(); yylval.num = lineno; return '>'; } 
"."                 { count(); yylval.num = lineno; return '.'; } 
":"                 { count(); yylval.num = lineno; return ':'; } 


"null"              { 
                        count(); 
                        yylval.node = make(LITERAL_NODE, NULL_OPTION, lineno, 0);
                        return NULLV;                    
}

"true"|"false"      { 
                        count(); 
                        yylval.node = make(LITERAL_NODE, BOOL_OPTION, lineno, 0);
                        yylval.node->bool_value = *yytext == 't';
                        return BOOL;                    
}

'([^\\']|\\(['"\\abfnrtv]|x[0-9A-Fa-f]+|[0-7]{1,3}))' { 
                        count(); 
                        yylval.node = make(LITERAL_NODE, CHAR_OPTION, lineno, 0);
                        yylval.node->char_value = parseChar(yytext);
                        return CHAR;                    
}

("+"|"-")?{D}+      { 
                        count(); 
                        yylval.node = make(LITERAL_NODE, INT_OPTION, lineno, 0);
                        yylval.node->int_value = atoll(yytext);
                        return INT;                    
}

[+-]?([0-9]*[.])?[0-9]+([eE][+-]?[0-9]+)? { 
                        count(); 
                        yylval.node = make(LITERAL_NODE, FLOAT_OPTION, lineno, 0);
                        yylval.node->float_value = strtod(yytext, NULL);
                        return FLOAT;                    
}

\"([^\"\\]|\\.)*\" { 
                        count(); 
                        yylval.node = make(LITERAL_NODE, STRING_OPTION, lineno, 0);
                        yylval.node->string_value = parseString(yytext);
                        return STRING;                    
}

{L}({L}|{D})*		{ 
                        count(); 
                        yylval.node = make(LITERAL_NODE, IDENTIFIER_OPTION, lineno, 0);
                        yylval.node->ident_value = symtabInsert(lex_symtab, yytext);
                        return IDENTIFIER;                    
}

[ \t\v\f\n]         { count(); }

.                   yyerror("invalid character");

%%

// stolen from https://www.lysator.liu.se/c/ANSI-C-grammar-l.html
static void count()
{
	int i;

    column += column_add;
    column_add = 0;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n') {
			column = 1;
            column_add = 0;
            lineno++;
        }
		else if (yytext[i] == '\t')
			column_add += 8 - (column % 8);
		else
			column_add++;
}

static char parseChar(char *data) {
    if (data[1] == '\\') {  
        switch (data[2]) {
            case 'n': return '\n';
            case 't': return '\t';
            case 'r': return '\r';
            case '\\': return '\\';
            case '\'': return '\'';
            default:
                yyerror("Unsupported escape sequence.\n");
        }
    }

    return data[1];
}
static char *parseString(char *data) {
    char *res   = strdup(data);
    int   res_i = 0;
    char *ptr   = data;
    ptr++;    // double quote
    while (*ptr != '"') {
        if (ptr[0] == '\\') {
            ptr++;
            switch (*ptr) {
            case 'n' : res[res_i++] = '\n'; break;
            case 't' : res[res_i++] = '\t'; break;
            case 'r' : res[res_i++] = '\r'; break;
            case '\\' : res[res_i++] = '\\'; break;
            case '\'' : res[res_i++] = '\''; break;
            case '\"' : res[res_i++] = '\"'; break;
            default : yyerror("Unsupported escape sequence.\n");
            }
        }
        else {
            res[res_i++] = *ptr;
        }
        ptr++;
    }

    res[res_i++] = '\0';

    char *new_res = malloc(sizeof(char) * res_i);
    memcpy(new_res, res, sizeof(char) * res_i);
    free(res);

    return new_res;
}
int yywrap(void) {
    column += column_add;
    column_add = 0;
    return 1;
}