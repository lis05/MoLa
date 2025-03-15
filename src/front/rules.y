%{
    #include "ast.h"
    #include <stdint.h>

    int yylex();
    void yyerror(const char *str);

    AstNode *node_result;
%}

%define parse.error verbose

%union {
    int64_t num;
    nodeptr node;
}
%start program
%token <node> BOOL
%token <node> CHAR
%token <node> INT
%token <node> FLOAT
%token <node> STRING
%token <node> IDENTIFIER
%token <node> NULLV

%token <num> IMPORT EXPORT GLOBAL FUNCTION TYPE METHOD CONSTRUCTOR DESTRUCTOR
%token <num> OF
%token <num> COPY REF PASS
%token <num> CONTINUE BREAK RETURN VAR
%token <num> TRY CATCH FINALLY SIGNAL BECAUSE
%token <num> IF ELSE WHILE FOR
%token <num> WHEN THEN NEW
%token <num> OR AND NOT
%token <num> COPIES REFS
%token <num> AS
%token <num> LSHIFT RSHIFT
%token <num> EQ NE LE GE
%token <num> '{' '}' '+' '-' '*' '/' '%' '~' '(' ')' '^'

%type <node> program
%type <node> import_stmt
%type <node> module_path
%type <node> module_path_compact
%type <node> module_path_upwards
%type <node> export_stmt
%type <node> export_item_list
%type <node> export_item
%type <node> global_variable_stmt
%type <node> identifier_item_list
%type <node> function_stmt
%type <node> parameter_list
%type <node> parameter_item
%type <node> type_stmt
%type <node> member_list
%type <node> member_item
%type <node> method_stmt
%type <node> constructor_stmt
%type <node> destructor_stmt
%type <node> stmt
%type <node> block_stmt
%type <node> stmt_list
%type <node> while_stmt
%type <node> for_stmt
%type <node> if_stmt
%type <node> continue_stmt
%type <node> break_stmt
%type <node> return_stmt
%type <node> assignment_stmt
%type <node> try_catch_stmt
%type <node> catch_item_list
%type <node> catch_item
%type <node> signal_stmt
%type <node> var_stmt
%type <node> assignment_item_list
%type <node> assignment_item
%type <node> expr
%type <node> assignment
%type <node> inline_if
%type <node> new
%type <node> logical_or
%type <node> logical_and
%type <node> bitwise_or
%type <node> bitwise_xor
%type <node> bitwise_and
%type <node> equality
%type <node> relational
%type <node> sum
%type <node> bitwise_shift
%type <node> term
%type <node> prefix_op
%type <node> primary
%type <node> elementary
%type <node> literal
%type <node> expr_list

%%
program:
    program import_stmt {
        $$ = make(PROGRAM_NODE, IMPORT_STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }
    | program export_stmt {
        $$ = make(PROGRAM_NODE, EXPORT_STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }
    | program global_variable_stmt {
        $$ = make(PROGRAM_NODE, GLOBAL_VARIABLE_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }
    | program function_stmt {
        $$ = make(PROGRAM_NODE, FUNCTION_STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    } 
    | program type_stmt {
        $$ = make(PROGRAM_NODE, TYPE_STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }  
    | program method_stmt {
        $$ = make(PROGRAM_NODE, METHOD_STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }  
    | program constructor_stmt {
        $$ = make(PROGRAM_NODE, CONSTRUCTOR_STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }  
    | program destructor_stmt {
        $$ = make(PROGRAM_NODE, DESTRUCTOR_STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }  
    | program stmt {
        $$ = make(PROGRAM_NODE, STMT_OPTION, $1->lineno, 2, $1, $2);
        node_result = $$;
    }  
    | {
        $$ = make(PROGRAM_NODE, NO_OPTION, 1, 0);
        node_result = $$;
    } 
    ;

import_stmt:
    IMPORT module_path AS IDENTIFIER {
        $$ = make(IMPORT_STMT_NODE, DEFAULT_OPTION, $1, 2, $2, $4);
    }
    ;

module_path:
    module_path_upwards module_path_compact {
        $$ = make(MODULE_PATH_NODE, MODULE_PATH_COMPACT_OPTION, $1->lineno, 2, $1, $2);
    }
    | module_path_compact {
        $$ = make(MODULE_PATH_NODE, MODULE_PATH_COMPACT_OPTION, $1->lineno, 1, $1);
    }
    | STRING {
        $$ = make(MODULE_PATH_NODE, MODULE_PATH_STRING_OPTION, $1->lineno, 1, $1);
    }
    ;

module_path_upwards:
    '^' module_path_upwards {
        $$ = make(MODULE_PATH_UPWARDS_NODE, LIST_RECURSIVE_OPTION, $1, 1, $2);
    }
    | '^' {
        $$ = make(MODULE_PATH_UPWARDS_NODE, LIST_BASE_ITEM_OPTION, $1, 0);
    }
    ;

module_path_compact:
    IDENTIFIER '.' module_path_compact {
        $$ = make(MODULE_PATH_COMPACT_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $3);
    }
    | IDENTIFIER {
        $$ = make(MODULE_PATH_COMPACT_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    ;

export_stmt:
    EXPORT export_item_list {
        $$ = make(EXPORT_STMT_NODE, DEFAULT_OPTION, $1, 1, $2);
    }
    ;

export_item_list:
    export_item ',' export_item_list {
        $$ = make(EXPORT_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $3);
    }  
    | export_item {
        $$ = make(EXPORT_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    ;

export_item:
    expr AS IDENTIFIER {
        $$ = make(EXPORT_ITEM_LIST_NODE, DEFAULT_OPTION, $1->lineno, 2, $1, $3);
    }
    ;

global_variable_stmt:
    GLOBAL identifier_item_list {
        $$ = make(GLOBAL_VARIABLE_STMT_NODE, DEFAULT_OPTION, $1, 1, $2);
    }
    ;

identifier_item_list:
    IDENTIFIER ',' identifier_item_list {
        $$ = make(IDENTIFIER_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $3);
    }
    | IDENTIFIER {
        $$ = make(IDENTIFIER_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    

function_stmt:
    FUNCTION IDENTIFIER '(' parameter_list ')' block_stmt {
        $$ = make(FUNCTION_STMT_NODE, FUNCTION_STMT_OPTION, $1, 3, $2, $4, $6);
    }
    | FUNCTION IDENTIFIER '(' ')' block_stmt {
        $$ = make(FUNCTION_STMT_NODE, FUNCTION_STMT_OPTION, $1, 3, $2, NULL, $5);
    }
    ;

parameter_list:
    parameter_item ',' parameter_list {
        $$ = make(PARAMETER_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $3);
    }
    | parameter_item {
        $$ = make(PARAMETER_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    ;

parameter_item:
    COPY IDENTIFIER {
        $$ = make(PARAMETER_ITEM_NODE, PARAM_COPY_MODE_OPTION, $1, 1, $2);
    }
    | REF IDENTIFIER {
        $$ = make(PARAMETER_ITEM_NODE, PARAM_REF_MODE_OPTION, $1, 1, $2);
    }
    | PASS IDENTIFIER {
        $$ = make(PARAMETER_ITEM_NODE, PARAM_PASS_MODE_OPTION, $1, 1, $2);
    } 
    | IDENTIFIER {
        $$ = make(PARAMETER_ITEM_NODE, PARAM_AUTO_MODE_OPTION, $1->lineno, 1, $1);
    }
    ;

type_stmt:
    TYPE IDENTIFIER '{' member_list  '}' {
        $$ = make(TYPE_STMT_NODE, DEFAULT_OPTION, $1, 2, $2, $4);
    }

member_list:
    member_item ',' member_list {
        $$ = make(MEMBER_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $3);
    }
    | member_item {
        $$ = make(MEMBER_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    ;

member_item:
    IDENTIFIER '(' ')' {
        $$ = make(MEMBER_ITEM_NODE, MEMBER_METHOD_OPTION, $1->lineno, 1, $1);
    }
    | IDENTIFIER {
        $$ = make(MEMBER_ITEM_NODE, MEMBER_FIELD_OPTION, $1->lineno, 1, $1);
    }
    ;

method_stmt:
    METHOD IDENTIFIER '(' parameter_list ')' OF IDENTIFIER block_stmt {
        $$ = make(METHOD_STMT_NODE, DEFAULT_OPTION, $1, 4, $2, $4, $7, $8);
    } 
    | METHOD IDENTIFIER '(' ')' OF IDENTIFIER block_stmt {
        $$ = make(METHOD_STMT_NODE, DEFAULT_OPTION, $1, 4, $2, NULL, $6, $7);
    }
    ;

constructor_stmt:
    CONSTRUCTOR '(' parameter_list ')' OF IDENTIFIER block_stmt {
        $$ = make(CONSTRUCTOR_STMT_NODE, DEFAULT_OPTION, $1, 3, $3, $6, $7);
    }
    | CONSTRUCTOR '(' ')' OF IDENTIFIER block_stmt {
        $$ = make(CONSTRUCTOR_STMT_NODE, DEFAULT_OPTION, $1, 3, NULL, $5, $6);
    }
    ;

destructor_stmt:
    DESTRUCTOR OF IDENTIFIER block_stmt {
        $$ = make(DESTRUCTOR_STMT_NODE, DEFAULT_OPTION, $1, 2, $3, $4);
    }
    ;

stmt:
    expr {
        $$ = make(STMT_NODE, EXPR_OPTION, $1->lineno, 1, $1);
    }
    | block_stmt {
        $$ = make(STMT_NODE, BLOCK_STMT_OPTION, $1->lineno, 1, $1);
    }
    | while_stmt {
        $$ = make(STMT_NODE, WHILE_STMT_OPTION, $1->lineno, 1, $1);
    }
    | for_stmt {
        $$ = make(STMT_NODE, FOR_STMT_OPTION, $1->lineno, 1, $1);
    }
    | if_stmt {
        $$ = make(STMT_NODE, IF_STMT_OPTION, $1->lineno, 1, $1);
    }
    | continue_stmt {
        $$ = make(STMT_NODE, CONTINUE_STMT_OPTION, $1->lineno, 1, $1);
    }
    | break_stmt {
        $$ = make(STMT_NODE, BREAK_STMT_OPTION, $1->lineno, 1, $1);
    }
    | return_stmt {
        $$ = make(STMT_NODE, RETURN_STMT_OPTION, $1->lineno, 1, $1);
    }
    | assignment_stmt {
        $$ = make(STMT_NODE, ASSIGNMENT_STMT_OPTION, $1->lineno, 1, $1);
    }
    | try_catch_stmt {
        $$ = make(STMT_NODE, TRY_CATCH_STMT_OPTION, $1->lineno, 1, $1);
    }
    | signal_stmt {
        $$ = make(STMT_NODE, SIGNAL_STMT_OPTION, $1->lineno, 1, $1);
    }
    | var_stmt {
        $$ = make(STMT_NODE, VAR_STMT_OPTION, $1->lineno, 1, $1);
    }
    | stmt ';' {
        $$ = make(STMT_NODE, STMT_OPTION, $1->lineno, 1, $1);
    }
    ;

block_stmt:
    '{' stmt_list '}' {
        $$ = make(BLOCK_STMT_NODE, DEFAULT_OPTION, $1, 1, $2);
    }
    | '{' '}' {
        $$ = make(BLOCK_STMT_NODE, DEFAULT_OPTION, $1, 0);
    }
    ;

stmt_list:
    stmt stmt_list {
        $$ = make(STMT_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $2);
    }
    | stmt {
        $$ = make(STMT_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    ;

while_stmt:
    WHILE expr stmt {
        $$ = make(WHILE_STMT_NODE, DEFAULT_OPTION, $1, 2, $2, $3);
    }
    ;

for_stmt:
    FOR expr ';' expr ';' expr stmt {
        $$ = make(FOR_STMT_NODE, FOR_INIT_COND_POST_OPTION, $1, 4, $2, $4, $6, $7);
    }
    | FOR ';' expr ';' expr stmt {
        $$ = make(FOR_STMT_NODE, FOR_COND_POST_OPTION, $1, 4, NULL, $3, $5, $6);
    }
    | FOR expr ';' ';' expr stmt {
        $$ = make(FOR_STMT_NODE, FOR_INIT_POST_OPTION, $1, 4, $2, NULL, $5, $6);
    }
    | FOR expr ';' expr ';' stmt {
        $$ = make(FOR_STMT_NODE, FOR_INIT_COND_OPTION, $1, 4, $2, $4, NULL, $6);
    }
    | FOR ';' ';' expr stmt {
        $$ = make(FOR_STMT_NODE, FOR_POST_OPTION, $1, 4, NULL, NULL, $4, $5);
    }
    | FOR ';' expr ';' stmt {
        $$ = make(FOR_STMT_NODE, FOR_COND_OPTION, $1, 4, NULL, $3, NULL, $5);
    }
    | FOR expr ';' ';' stmt {
        $$ = make(FOR_STMT_NODE, FOR_INIT_OPTION, $1, 4, $2, NULL, NULL, $5);
    }
    | FOR ';' ';' stmt {
        $$ = make(FOR_STMT_NODE, FOR_NOTHING_OPTION, $1, 4, NULL, NULL, NULL, $4);
    }
    ;

if_stmt:
    IF expr stmt ELSE stmt {
        $$ = make(IF_STMT_NODE, IF_WITH_ELSE_OPTION, $1, 3, $2, $3, $5);
    }
    | IF expr stmt {
        $$ = make(IF_STMT_NODE, IF_WITHOUT_ELSE_OPTION, $1, 3, $2, $3, NULL);
    }
    ;

continue_stmt:
    CONTINUE {
        $$ = make(CONTINUE_STMT_NODE, DEFAULT_OPTION, $1, 0);
    }
    ;

break_stmt:
    BREAK {
        $$ = make(BREAK_STMT_NODE, DEFAULT_OPTION, $1, 0);
    }
    ;

return_stmt:
    RETURN COPY expr {
        $$ = make(RETURN_STMT_NODE, RETURN_COPY_MODE_OPTION, $1, 1, $3);
    }
    | RETURN REF expr {
        $$ = make(RETURN_STMT_NODE, RETURN_REF_MODE_OPTION, $1, 1, $3);
    }
    | RETURN PASS expr {
        $$ = make(RETURN_STMT_NODE, RETURN_PASS_MODE_OPTION, $1, 1, $3);
    }
    | RETURN expr {
        $$ = make(RETURN_STMT_NODE, RETURN_AUTO_MODE_OPTION, $1, 1, $2);
    }
    ;

assignment_stmt:
    expr COPIES expr {
        $$ = make(ASSIGNMENT_STMT_NODE, ASSIGNMENT_COPIES_OPTION, $1->lineno, 2, $1, $3);
    }
    | expr REFS expr {
        $$ = make(ASSIGNMENT_STMT_NODE, ASSIGNMENT_REFS_OPTION, $1->lineno, 2, $1, $3);
    }
    ;

try_catch_stmt:
    TRY block_stmt catch_item_list FINALLY CATCH AS IDENTIFIER block_stmt {
        $$ = make(TRY_CATCH_STMT_NODE, TRY_CATCH_FULL_OPTION, $1, 4, $2, $3, $7, $8);
    }
    | TRY block_stmt FINALLY CATCH AS IDENTIFIER block_stmt {
        $$ = make(TRY_CATCH_STMT_NODE, TRY_CATCH_ONLY_UNIVERSAL_OPTION, $1, 3, $2, $6, $7);
    }
    | TRY block_stmt catch_item_list {
        $$ = make(TRY_CATCH_STMT_NODE, TRY_CATCH_ONLY_SPECIFIC_OPTION, $1, 2, $2, $3);
    }
    ;

catch_item_list:
    catch_item catch_item_list {
        $$ = make(CATCH_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $2);
    }
    | catch_item {
        $$ = make(CATCH_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    ;

catch_item:
    CATCH expr AS IDENTIFIER block_stmt {
        $$ = make(CATCH_ITEM_NODE, DEFAULT_OPTION, $1, 3, $2, $4, $5);
    }
    ;

signal_stmt:
    SIGNAL expr BECAUSE expr {
        $$ = make(SIGNAL_STMT_NODE, DEFAULT_OPTION, $1, 2, $2, $4);
    }
    ;

var_stmt: 
    VAR assignment_item_list {
        $$ = make(VAR_STMT_NODE, DEFAULT_OPTION, $1, 1, $2);
    }
    ;

assignment_item_list:
    assignment_item ',' assignment_item_list {
        $$ = make(ASSIGNMENT_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $3);
    }
    | assignment_item {
        $$ = make(ASSIGNMENT_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }

assignment_item:
    IDENTIFIER '=' expr {
        $$ = make(ASSIGNMENT_ITEM_NODE, ASSIGNMENT_ITEM_FULL_OPTION, $1->lineno, 2, $1, $3);
    }
    | IDENTIFIER {
        $$ = make(ASSIGNMENT_ITEM_NODE, ASSIGNMENT_ITEM_NAME_OPTION, $1->lineno, 1, $1);
    }

expr:
    assignment {
        $$ = make(EXPR_NODE, DEFAULT_OPTION, $1->lineno, 1, $1);
    }
    ;

assignment:
    inline_if '=' assignment {
        $$ = make(ASSIGNMENT_NODE, ASSIGNMENT_OPTION, $1->lineno, 2, $1, $3);
    }
    | inline_if {
        $$ = make(ASSIGNMENT_NODE, INLINE_IF_OPTION, $1->lineno, 1, $1);
    }
    ;

inline_if:
    WHEN new THEN new ELSE new {
        $$ = make(INLINE_IF_NODE, INLINE_IF_OPTION, $1, 3, $2, $4, $6);
    }
    | new {
        $$ = make(INLINE_IF_NODE, NEW_OPTION, $1->lineno, 1, $1);
    }
    ;

new:
    NEW logical_or '(' expr_list ')' {
        $$ = make(NEW_NODE, NEW_OPTION, $1, 2, $2, $4);
    }
    | NEW logical_or {
        $$ = make(NEW_NODE, NEW_OPTION, $1, 1, $2);
    }
    | logical_or {
        $$ = make(NEW_NODE, LOGICAL_OR_OPTION, $1->lineno, 1, $1);
    }
    ;

logical_or:
    logical_or OR logical_and {
        $$ = make(LOGICAL_OR_NODE, LOGICAL_OR_OPTION, $1->lineno, 2, $1, $3);
    }
    | logical_and {
        $$ = make(LOGICAL_OR_NODE, LOGICAL_AND_OPTION, $1->lineno, 1, $1);
    }
    ;

logical_and:
    logical_and AND bitwise_or {
        $$ = make(LOGICAL_AND_NODE, LOGICAL_AND_OPTION, $1->lineno, 2, $1, $3);
    }
    | bitwise_or {
        $$ = make(LOGICAL_AND_NODE, BITWISE_OR_OPTION, $1->lineno, 1, $1);
    }
    ;

bitwise_or:
    bitwise_or '|' bitwise_xor {
        $$ = make(BITWISE_OR_NODE, BITWISE_OR_OPTION, $1->lineno, 2, $1, $3);
    }
    | bitwise_xor {
        $$ = make(BITWISE_OR_NODE, BITWISE_XOR_OPTION, $1->lineno, 1, $1);
    }
    ;

bitwise_xor:
    bitwise_xor '^' bitwise_and {
        $$ = make(BITWISE_XOR_NODE, BITWISE_XOR_OPTION, $1->lineno, 2, $1, $3);
    }
    | bitwise_and {
        $$ = make(BITWISE_XOR_NODE, BITWISE_AND_OPTION, $1->lineno, 1, $1);
    }
    ;

bitwise_and:
    bitwise_and '&' equality {
        $$ = make(BITWISE_AND_NODE, BITWISE_AND_OPTION, $1->lineno, 2, $1, $3);
    }
    | equality {
        $$ = make(BITWISE_AND_NODE, EQUALITY_OPTION, $1->lineno, 1, $1);
    }
    ;

equality:
    equality EQ relational {
        $$ = make(EQUALITY_NODE, EQUAL_OPTION, $1->lineno, 2, $1, $3);
    }
    | equality NE relational {
        $$ = make(EQUALITY_NODE, NOT_EQUAL_OPTION, $1->lineno, 2, $1, $3);
    }
    | relational {
        $$ = make(EQUALITY_NODE, RELATIONAL_OPTION, $1->lineno, 1, $1);
    }
    ;

relational:
    relational LE sum {
        $$ = make(RELATIONAL_NODE, LESS_EQUAL_OPTION, $1->lineno, 2, $1, $3);
    }
    | relational GE sum {
        $$ = make(RELATIONAL_NODE, GREATER_EQUAL_OPTION, $1->lineno, 2, $1, $3);
    }
    | relational '<' sum {
        $$ = make(RELATIONAL_NODE, LESS_THAN_OPTION, $1->lineno, 2, $1, $3);
    }
    | relational '>' sum {
        $$ = make(RELATIONAL_NODE, GREATER_THAN_OPTION, $1->lineno, 2, $1, $3);
    }
    | sum {
        $$ = make(RELATIONAL_NODE, SUM_OPTION, $1->lineno, 1, $1);
    }
    ;

sum:
    sum '+' bitwise_shift {
        $$ = make(SUM_NODE, ADDITION_OPTION, $1->lineno, 2, $1, $3);
    }
    | sum '-' bitwise_shift {
        $$ = make(SUM_NODE, SUBTRACTION_OPTION, $1->lineno, 2, $1, $3);
    }
    | bitwise_shift {
        $$ = make(SUM_NODE, BITWISE_SHIFT_OPTION, $1->lineno, 1, $1);
    }
    ;

bitwise_shift:
    bitwise_shift LSHIFT term {
        $$ = make(BITWISE_SHIFT_NODE, LSHIFT_OPTION, $1->lineno, 2, $1, $3);
    }
    | bitwise_shift RSHIFT term {
        $$ = make(BITWISE_SHIFT_NODE, RSHIFT_OPTION, $1->lineno, 2, $1, $3);
    }
    | term {
        $$ = make(BITWISE_SHIFT_NODE, TERM_OPTION, $1->lineno, 1, $1);
    }
    ;

term:
    term '*' prefix_op {
        $$ = make(TERM_NODE, MULTIPLICATION_OPTION, $1->lineno, 2, $1, $3);
    }
    | term '/' prefix_op {
        $$ = make(TERM_NODE, DIVISION_OPTION, $1->lineno, 2, $1, $3);
    }
    | term '%' prefix_op {
        $$ = make(TERM_NODE, REMAINDER_OPTION, $1->lineno, 2, $1, $3);
    }
    | prefix_op {
        $$ = make(TERM_NODE, PREFIX_OP_OPTION, $1->lineno, 1, $1);
    }
    ;

prefix_op:
    '+' prefix_op {
        $$ = make(PREFIX_OP_NODE, POSITIVE_OPTION, $1, 1, $2);
    } 
    | '-' prefix_op {
        $$ = make(PREFIX_OP_NODE, NEGATIVE_OPTION, $1, 1, $2);
    } 
    | NOT prefix_op {
        $$ = make(PREFIX_OP_NODE, NOT_OPTION, $1, 1, $2);
    } 
    | '~' prefix_op{
        $$ = make(PREFIX_OP_NODE, INVERSE_OPTION, $1, 1, $2);
    } 
    | primary {
        $$ = make(PREFIX_OP_NODE, PRIMARY_OPTION, $1->lineno, 1, $1);
    }
    ;

primary:
    primary '(' expr_list ')' {
        $$ = make(PRIMARY_NODE, CALL_OPTION, $1->lineno, 2, $1, $3);
    }
    | primary '(' ')' {
        $$ = make(PRIMARY_NODE, CALL_OPTION, $1->lineno, 1, $1);
    }
    | primary '[' expr ']' {
        $$ = make(PRIMARY_NODE, INDEX_OPTION, $1->lineno, 2, $1, $3);
    }
    | primary '.' IDENTIFIER {
        $$ = make(PRIMARY_NODE, FIELD_OPTION, $1->lineno, 2, $1, $3);
    }
    | primary ':' IDENTIFIER {
        $$ = make(PRIMARY_NODE, METHOD_OPTION, $1->lineno, 2, $1, $3);
    }
    | elementary {
        $$ = make(PRIMARY_NODE, ELEMENTARY_OPTION, $1->lineno, 1, $1);
    }
    ;

elementary:
    '(' expr ')' {
        $$ = make(ELEMENTARY_NODE, EXPR_OPTION, $1, 1, $2);
    }
    | literal {
        $$ = make(ELEMENTARY_NODE, LITERAL_OPTION, $1->lineno, 1, $1);
    }
    ;

literal:
    NULLV {
        $$ = $1;
    }
    | BOOL {
        $$ = $1;
    }
    | CHAR {
        $$ = $1;
    }
    | INT {
        $$ = $1;
    }
    | FLOAT {
        $$ = $1;
    }
    | STRING {
        $$ = $1;
    }
    | IDENTIFIER {
        $$ = $1;
    }
    ;

expr_list: 
    expr ',' expr_list {
        $$ = make(EXPR_LIST_NODE, LIST_RECURSIVE_OPTION, $1->lineno, 2, $1, $3);
    }
    | expr {
        $$ = make(EXPR_LIST_NODE, LIST_BASE_ITEM_OPTION, $1->lineno, 1, $1);
    }
    ;
%%