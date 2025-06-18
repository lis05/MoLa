#ifndef __ast_h__
#define __ast_h__

#include <stdint.h>
#include <stdio.h>

// productions
#define PROGRAM_NODE              1
#define IMPORT_STMT_NODE          2
#define EXPORT_STMT_NODE          3
#define EXPORT_ITEM_LIST_NODE     4
#define EXPORT_ITEM_NODE          5
#define GLOBAL_VARIABLE_STMT_NODE 6
#define FUNCTION_STMT_NODE        7
#define PARAMETER_LIST_NODE       8
#define PARAMETER_ITEM_NODE       9
#define TYPE_STMT_NODE            10
#define MEMBER_LIST_NODE          11
#define MEMBER_ITEM_NODE          12
#define METHOD_STMT_NODE          13
#define CONSTRUCTOR_STMT_NODE     14
#define DESTRUCTOR_STMT_NODE      15
#define STMT_NODE                 16
#define BLOCK_STMT_NODE           17
#define STMT_LIST_NODE            18
#define WHILE_STMT_NODE           19
#define FOR_STMT_NODE             20
#define IF_STMT_NODE              21
#define CONTINUE_STMT_NODE        22
#define BREAK_STMT_NODE           23
#define RETURN_STMT_NODE          24
#define TRY_CATCH_STMT_NODE       26
#define CATCH_ITEM_LIST_NODE      27
#define CATCH_ITEM_NODE           28
#define SIGNAL_STMT_NODE          29
#define VAR_STMT_NODE             30
#define ASSIGNMENT_ITEM_LIST_NODE 31
#define ASSIGNMENT_ITEM_NODE      32
#define EXPR_NODE                 33
#define ASSIGNMENT_NODE           34
#define INLINE_IF_NODE            35
#define NEW_NODE                  36
#define LOGICAL_OR_NODE           37
#define LOGICAL_AND_NODE          38
#define BITWISE_OR_NODE           39
#define BITWISE_XOR_NODE          40
#define BITWISE_AND_NODE          41
#define EQUALITY_NODE             42
#define RELATIONAL_NODE           43
#define SUM_NODE                  44
#define BITWISE_SHIFT_NODE        45
#define TERM_NODE                 46
#define PREFIX_OP_NODE            47
#define PRIMARY_NODE              48
#define ELEMENTARY_NODE           49
#define LITERAL_NODE              50
#define MODULE_PATH_NODE          51
#define MODULE_PATH_COMPACT_NODE  52
#define MODULE_PATH_UPWARDS_NODE  53
#define EXPR_LIST_NODE            54
#define IDENTIFIER_LIST_NODE      55

// options (index of the chosen alternative in a production)
#define DEFAULT_OPTION                  1
#define IMPORT_STMT_OPTION              2
#define MODULE_PATH_COMPACT_OPTION      3
#define MODULE_PATH_STRING_OPTION       4
#define EXPORT_STMT_OPTION              5
#define GLOBAL_VARIABLE_OPTION          6
#define FUNCTION_STMT_OPTION            7
#define TYPE_STMT_OPTION                8
#define METHOD_STMT_OPTION              9
#define CONSTRUCTOR_STMT_OPTION         10
#define DESTRUCTOR_STMT_OPTION          11
#define STMT_OPTION                     12
#define NO_OPTION                       13
#define LIST_BASE_ITEM_OPTION           14
#define LIST_RECURSIVE_OPTION           15
#define NO_FUNC_PARAMS_OPTION           16
#define MEMBER_FIELD_OPTION             21
#define MEMBER_METHOD_OPTION            22
#define EXPR_OPTION                     23
#define BLOCK_STMT_OPTION               24
#define WHILE_STMT_OPTION               25
#define FOR_STMT_OPTION                 26
#define IF_STMT_OPTION                  27
#define CONTINUE_STMT_OPTION            28
#define BREAK_STMT_OPTION               29
#define RETURN_STMT_OPTION              30
#define ASSIGNMENT_STMT_OPTION          31
#define TRY_CATCH_STMT_OPTION           32
#define SIGNAL_STMT_OPTION              33
#define VAR_STMT_OPTION                 34
#define ASSIGNMENT_ITEM_FULL_OPTION     35
#define ASSIGNMENT_ITEM_NAME_OPTION     36
#define FOR_INIT_COND_POST_OPTION       37
#define FOR_COND_POST_OPTION            38
#define FOR_INIT_POST_OPTION            39
#define FOR_INIT_COND_OPTION            40
#define FOR_POST_OPTION                 41
#define FOR_COND_OPTION                 42
#define FOR_INIT_OPTION                 43
#define FOR_NOTHING_OPTION              44
#define IF_WITH_ELSE_OPTION             45
#define IF_WITHOUT_ELSE_OPTION          46
#define TRY_CATCH_FULL_OPTION           53
#define TRY_CATCH_ONLY_UNIVERSAL_OPTION 54
#define TRY_CATCH_ONLY_SPECIFIC_OPTION  55
#define ASSIGNMENT_OPTION               56
#define INLINE_IF_OPTION                57
#define NEW_OPTION                      58
#define LOGICAL_OR_OPTION               59
#define LOGICAL_AND_OPTION              60
#define BITWISE_OR_OPTION               61
#define BITWISE_XOR_OPTION              62
#define BITWISE_AND_OPTION              63
#define EQUALITY_OPTION                 64
#define EQUAL_OPTION                    65
#define NOT_EQUAL_OPTION                66
#define RELATIONAL_OPTION               67
#define LESS_EQUAL_OPTION               68
#define GREATER_EQUAL_OPTION            69
#define LESS_THAN_OPTION                70
#define GREATER_THAN_OPTION             71
#define SUM_OPTION                      72
#define ADDITION_OPTION                 73
#define SUBTRACTION_OPTION              74
#define BITWISE_SHIFT_OPTION            75
#define LSHIFT_OPTION                   76
#define RSHIFT_OPTION                   77
#define TERM_OPTION                     78
#define MULTIPLICATION_OPTION           79
#define DIVISION_OPTION                 80
#define REMAINDER_OPTION                81
#define PREFIX_OP_OPTION                82
#define POSITIVE_OPTION                 83
#define NEGATIVE_OPTION                 84
#define NOT_OPTION                      85
#define INVERSE_OPTION                  86
#define PRIMARY_OPTION                  87
#define CALL_OPTION                     88
#define INDEX_OPTION                    89
#define FIELD_OPTION                    90
#define METHOD_OPTION                   91
#define ELEMENTARY_OPTION               92
#define LITERAL_OPTION                  93
#define NULL_OPTION                     94
#define BOOL_OPTION                     95
#define CHAR_OPTION                     96
#define INT_OPTION                      97
#define FLOAT_OPTION                    98
#define STRING_OPTION                   99
#define IDENTIFIER_OPTION               100
#define METHOD_PATH_OPTION              101

typedef uint64_t ident;    // in reality, only least significant half of the bits is used.

/**
 * @brief AstNode representing a grammar nonterminal.
 */
typedef struct AstNode {
    int type   : 8;
    int option : 8;

    size_t           n_nodes;
    struct AstNode **nodes;

    size_t lineno;
    char  *filename;

    union {
        int8_t  bool_value;
        char    char_value;
        int64_t int_value;
        double  float_value;
        char   *string_value;
        ident   ident_value;
    };
} AstNode;

typedef AstNode *nodeptr;
typedef char    *charptr;
AstNode         *make(int type, int option, size_t lineno, size_t n_nodes, ...);

#endif
