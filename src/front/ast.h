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
#define ASSIGNMENT_STMT_NODE      25
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
#define EXPR_LIST_NODE            53
#define IDENTIFIER_LIST_NODE      54

// flags (index of the chosen alternative in a production)
#define DEFAULT_OPTION                  1
#define IMPORT_STMT_OPTION              2
#define MODULE_PATH_COMPACT_OPTION      3
#define MODULE_PATH_STRING_OPTION       4
#define EXPORT_STMT_OPTION              5
#define FUNCTION_STMT_OPTION            6
#define TYPE_STMT_OPTION                7
#define METHOD_STMT_OPTION              8
#define CONSTRUCTOR_STMT_OPTION         9
#define DESTRUCTOR_STMT_OPTION          10
#define STMT_OPTION                     11
#define NO_OPTION                       12
#define LIST_BASE_ITEM_OPTION           13
#define LIST_RECURSIVE_OPTION           14
#define NO_FUNC_PARAMS_OPTION           15
#define PARAM_COPY_MODE_OPTION          16
#define PARAM_REF_MODE_OPTION           17
#define PARAM_PASS_MODE_OPTION          18
#define PARAM_AUTO_MODE_OPTION          19
#define MEMBER_FIELD_OPTION             20
#define MEMBER_METHOD_OPTION            21
#define EXPR_OPTION                     22
#define BLOCK_STMT_OPTION               23
#define WHILE_STMT_OPTION               24
#define FOR_STMT_OPTION                 25
#define IF_STMT_OPTION                  26
#define CONTINUE_STMT_OPTION            27
#define BREAK_STMT_OPTION               28
#define RETURN_STMT_OPTION              29
#define ASSIGNMENT_STMT_OPTION          30
#define TRY_CATCH_STMT_OPTION           31
#define SIGNAL_STMT_OPTION              32
#define VAR_STMT_OPTION                 33
#define ASSIGNMENT_ITEM_FULL_OPTION     34
#define ASSIGNMENT_ITEM_NAME_OPTION     35
#define FOR_INIT_COND_POST_OPTION       36
#define FOR_COND_POST_OPTION            37
#define FOR_INIT_POST_OPTION            38
#define FOR_INIT_COND_OPTION            39
#define FOR_POST_OPTION                 40
#define FOR_COND_OPTION                 41
#define FOR_INIT_OPTION                 42
#define FOR_NOTHING_OPTION              43
#define IF_WITH_ELSE_OPTION             44
#define IF_WITHOUT_ELSE_OPTION          45
#define RETURN_COPY_MODE_OPTION         46
#define RETURN_REF_MODE_OPTION          47
#define RETURN_PASS_MODE_OPTION         48
#define RETURN_AUTO_MODE_OPTION         49
#define ASSIGNMENT_COPIES_OPTION        50
#define ASSIGNMENT_REFS_OPTION          51
#define TRY_CATCH_FULL_OPTION           52
#define TRY_CATCH_ONLY_UNIVERSAL_OPTION 53
#define TRY_CATCH_ONLY_SPECIFIC_OPTION  54
#define ASSIGNMENT_OPTION               55
#define INLINE_IF_OPTION                56
#define NEW_OPTION                      57
#define LOGICAL_OR_OPTION               58
#define LOGICAL_AND_OPTION              59
#define BITWISE_OR_OPTION               60
#define BITWISE_XOR_OPTION              61
#define BITWISE_AND_OPTION              62
#define EQUALITY_OPTION                 63
#define EQUAL_OPTION                    64
#define NOT_EQUAL_OPTION                65
#define RELATIONAL_OPTION               66
#define LESS_EQUAL_OPTION               67
#define GREATER_EQUAL_OPTION            68
#define LESS_THAN_OPTION                69
#define GREATER_THAN_OPTION             70
#define SUM_OPTION                      71
#define ADDITION_OPTION                 72
#define SUBTRACTION_OPTION              73
#define BITWISE_SHIFT_OPTION            74
#define LSHIFT_OPTION                   75
#define RSHIFT_OPTION                   76
#define TERM_OPTION                     77
#define MULTIPLICATION_OPTION           78
#define DIVISION_OPTION                 79
#define REMAINDER_OPTION                80
#define PREFIX_OP_OPTION                81
#define POSITIVE_OPTION                 82
#define NEGATIVE_OPTION                 83
#define NOT_OPTION                      84
#define INVERSE_OPTION                  85
#define PRIMARY_OPTION                  86
#define CALL_OPTION                     87
#define INDEX_OPTION                    88
#define FIELD_OPTION                    89
#define METHOD_OPTION                   90
#define ELEMENTARY_OPTION               91
#define LITERAL_OPTION                  92
#define NULL_OPTION                     93
#define BOOL_OPTION                     94
#define CHAR_OPTION                     95
#define INT_OPTION                      96
#define FLOAT_OPTION                    97
#define STRING_OPTION                   98
#define IDENTIFIER_OPTION               99
#define METHOD_PATH_OPTION              100

typedef uint64_t ident;

/**
 * @brief Node representing a grammar nonterminal.
 */
typedef struct Node {
    int type : 8;
    int flag : 8;

    size_t        n_nodes;
    struct Node **nodes;

    size_t lineno;
    char  *filename;

    union {
        int8_t  bool_value;
        char    char_value;
        int64_t int_value;
        double  float_value;
        char   *string_value;
        ident   identifier_value;
    };
} Node;

typedef Node *nodeptr;
typedef char *charptr;
Node         *make(int type, int flag, size_t lineno, size_t n_nodes, ...);

#endif
