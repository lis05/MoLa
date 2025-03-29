/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "rules.y"

    #include "ast.h"
    #include <stdint.h>

    int yylex();
    void yyerror(const char *str);

    AstNode *node_result;

#line 81 "rules.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "rules.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BOOL = 3,                       /* BOOL  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_IDENTIFIER = 8,                 /* IDENTIFIER  */
  YYSYMBOL_NULLV = 9,                      /* NULLV  */
  YYSYMBOL_IMPORT = 10,                    /* IMPORT  */
  YYSYMBOL_EXPORT = 11,                    /* EXPORT  */
  YYSYMBOL_GLOBAL = 12,                    /* GLOBAL  */
  YYSYMBOL_FUNCTION = 13,                  /* FUNCTION  */
  YYSYMBOL_TYPE = 14,                      /* TYPE  */
  YYSYMBOL_METHOD = 15,                    /* METHOD  */
  YYSYMBOL_CONSTRUCTOR = 16,               /* CONSTRUCTOR  */
  YYSYMBOL_DESTRUCTOR = 17,                /* DESTRUCTOR  */
  YYSYMBOL_OF = 18,                        /* OF  */
  YYSYMBOL_CONTINUE = 19,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 20,                     /* BREAK  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_VAR = 22,                       /* VAR  */
  YYSYMBOL_TRY = 23,                       /* TRY  */
  YYSYMBOL_CATCH = 24,                     /* CATCH  */
  YYSYMBOL_FINALLY = 25,                   /* FINALLY  */
  YYSYMBOL_SIGNAL = 26,                    /* SIGNAL  */
  YYSYMBOL_BECAUSE = 27,                   /* BECAUSE  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_FOR = 31,                       /* FOR  */
  YYSYMBOL_WHEN = 32,                      /* WHEN  */
  YYSYMBOL_THEN = 33,                      /* THEN  */
  YYSYMBOL_NEW = 34,                       /* NEW  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_NOT = 37,                       /* NOT  */
  YYSYMBOL_AS = 38,                        /* AS  */
  YYSYMBOL_LSHIFT = 39,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 40,                    /* RSHIFT  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_NE = 42,                        /* NE  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_45_ = 45,                       /* '{'  */
  YYSYMBOL_46_ = 46,                       /* '}'  */
  YYSYMBOL_47_ = 47,                       /* '+'  */
  YYSYMBOL_48_ = 48,                       /* '-'  */
  YYSYMBOL_49_ = 49,                       /* '*'  */
  YYSYMBOL_50_ = 50,                       /* '/'  */
  YYSYMBOL_51_ = 51,                       /* '%'  */
  YYSYMBOL_52_ = 52,                       /* '~'  */
  YYSYMBOL_53_ = 53,                       /* '('  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_55_ = 55,                       /* '^'  */
  YYSYMBOL_56_ = 56,                       /* '.'  */
  YYSYMBOL_57_ = 57,                       /* ','  */
  YYSYMBOL_58_ = 58,                       /* ';'  */
  YYSYMBOL_59_ = 59,                       /* '='  */
  YYSYMBOL_60_ = 60,                       /* '|'  */
  YYSYMBOL_61_ = 61,                       /* '&'  */
  YYSYMBOL_62_ = 62,                       /* '<'  */
  YYSYMBOL_63_ = 63,                       /* '>'  */
  YYSYMBOL_64_ = 64,                       /* '['  */
  YYSYMBOL_65_ = 65,                       /* ']'  */
  YYSYMBOL_66_ = 66,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_program = 68,                   /* program  */
  YYSYMBOL_import_stmt = 69,               /* import_stmt  */
  YYSYMBOL_module_path = 70,               /* module_path  */
  YYSYMBOL_module_path_upwards = 71,       /* module_path_upwards  */
  YYSYMBOL_module_path_compact = 72,       /* module_path_compact  */
  YYSYMBOL_export_stmt = 73,               /* export_stmt  */
  YYSYMBOL_export_item_list = 74,          /* export_item_list  */
  YYSYMBOL_export_item = 75,               /* export_item  */
  YYSYMBOL_global_variable_stmt = 76,      /* global_variable_stmt  */
  YYSYMBOL_identifier_item_list = 77,      /* identifier_item_list  */
  YYSYMBOL_function_stmt = 78,             /* function_stmt  */
  YYSYMBOL_parameter_list = 79,            /* parameter_list  */
  YYSYMBOL_parameter_item = 80,            /* parameter_item  */
  YYSYMBOL_type_stmt = 81,                 /* type_stmt  */
  YYSYMBOL_member_list = 82,               /* member_list  */
  YYSYMBOL_member_item = 83,               /* member_item  */
  YYSYMBOL_method_stmt = 84,               /* method_stmt  */
  YYSYMBOL_constructor_stmt = 85,          /* constructor_stmt  */
  YYSYMBOL_destructor_stmt = 86,           /* destructor_stmt  */
  YYSYMBOL_stmt = 87,                      /* stmt  */
  YYSYMBOL_block_stmt = 88,                /* block_stmt  */
  YYSYMBOL_stmt_list = 89,                 /* stmt_list  */
  YYSYMBOL_while_stmt = 90,                /* while_stmt  */
  YYSYMBOL_for_stmt = 91,                  /* for_stmt  */
  YYSYMBOL_if_stmt = 92,                   /* if_stmt  */
  YYSYMBOL_continue_stmt = 93,             /* continue_stmt  */
  YYSYMBOL_break_stmt = 94,                /* break_stmt  */
  YYSYMBOL_return_stmt = 95,               /* return_stmt  */
  YYSYMBOL_try_catch_stmt = 96,            /* try_catch_stmt  */
  YYSYMBOL_catch_item_list = 97,           /* catch_item_list  */
  YYSYMBOL_catch_item = 98,                /* catch_item  */
  YYSYMBOL_signal_stmt = 99,               /* signal_stmt  */
  YYSYMBOL_var_stmt = 100,                 /* var_stmt  */
  YYSYMBOL_assignment_item_list = 101,     /* assignment_item_list  */
  YYSYMBOL_assignment_item = 102,          /* assignment_item  */
  YYSYMBOL_expr = 103,                     /* expr  */
  YYSYMBOL_assignment = 104,               /* assignment  */
  YYSYMBOL_inline_if = 105,                /* inline_if  */
  YYSYMBOL_new = 106,                      /* new  */
  YYSYMBOL_logical_or = 107,               /* logical_or  */
  YYSYMBOL_logical_and = 108,              /* logical_and  */
  YYSYMBOL_bitwise_or = 109,               /* bitwise_or  */
  YYSYMBOL_bitwise_xor = 110,              /* bitwise_xor  */
  YYSYMBOL_bitwise_and = 111,              /* bitwise_and  */
  YYSYMBOL_equality = 112,                 /* equality  */
  YYSYMBOL_relational = 113,               /* relational  */
  YYSYMBOL_sum = 114,                      /* sum  */
  YYSYMBOL_bitwise_shift = 115,            /* bitwise_shift  */
  YYSYMBOL_term = 116,                     /* term  */
  YYSYMBOL_prefix_op = 117,                /* prefix_op  */
  YYSYMBOL_primary = 118,                  /* primary  */
  YYSYMBOL_elementary = 119,               /* elementary  */
  YYSYMBOL_literal = 120,                  /* literal  */
  YYSYMBOL_expr_list = 121                 /* expr_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   511

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  141
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  270

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    51,    61,     2,
      53,    54,    49,    47,    57,    48,    56,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    66,    58,
      62,    59,    63,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,    60,    46,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,    99,   103,   107,   111,   115,   119,   123,
     127,   131,   138,   144,   147,   150,   156,   159,   165,   168,
     174,   180,   183,   189,   195,   201,   204,   210,   213,   219,
     222,   228,   234,   239,   242,   248,   251,   257,   260,   266,
     269,   275,   281,   284,   287,   290,   293,   296,   299,   302,
     305,   308,   311,   314,   320,   323,   329,   332,   338,   344,
     347,   350,   353,   356,   359,   362,   365,   371,   374,   380,
     386,   392,   398,   401,   404,   410,   413,   419,   425,   431,
     437,   440,   445,   448,   453,   459,   462,   468,   471,   477,
     480,   483,   489,   492,   498,   501,   507,   510,   516,   519,
     525,   528,   534,   537,   540,   546,   549,   552,   555,   558,
     564,   567,   570,   576,   579,   582,   588,   591,   594,   597,
     603,   606,   609,   612,   615,   621,   624,   627,   630,   633,
     636,   642,   645,   651,   654,   657,   660,   663,   666,   669,
     675,   678
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BOOL", "CHAR", "INT",
  "FLOAT", "STRING", "IDENTIFIER", "NULLV", "IMPORT", "EXPORT", "GLOBAL",
  "FUNCTION", "TYPE", "METHOD", "CONSTRUCTOR", "DESTRUCTOR", "OF",
  "CONTINUE", "BREAK", "RETURN", "VAR", "TRY", "CATCH", "FINALLY",
  "SIGNAL", "BECAUSE", "IF", "ELSE", "WHILE", "FOR", "WHEN", "THEN", "NEW",
  "OR", "AND", "NOT", "AS", "LSHIFT", "RSHIFT", "EQ", "NE", "LE", "GE",
  "'{'", "'}'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'('", "')'",
  "'^'", "'.'", "','", "';'", "'='", "'|'", "'&'", "'<'", "'>'", "'['",
  "']'", "':'", "$accept", "program", "import_stmt", "module_path",
  "module_path_upwards", "module_path_compact", "export_stmt",
  "export_item_list", "export_item", "global_variable_stmt",
  "identifier_item_list", "function_stmt", "parameter_list",
  "parameter_item", "type_stmt", "member_list", "member_item",
  "method_stmt", "constructor_stmt", "destructor_stmt", "stmt",
  "block_stmt", "stmt_list", "while_stmt", "for_stmt", "if_stmt",
  "continue_stmt", "break_stmt", "return_stmt", "try_catch_stmt",
  "catch_item_list", "catch_item", "signal_stmt", "var_stmt",
  "assignment_item_list", "assignment_item", "expr", "assignment",
  "inline_if", "new", "logical_or", "logical_and", "bitwise_or",
  "bitwise_xor", "bitwise_and", "equality", "relational", "sum",
  "bitwise_shift", "term", "prefix_op", "primary", "elementary", "literal",
  "expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-155)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -155,   300,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,
       9,   441,     4,    16,    30,    36,    19,    32,  -155,  -155,
     441,    47,    17,   441,   441,   441,    26,   458,   101,   101,
     371,   101,   101,   101,   441,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,    34,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,    41,  -155,    40,    77,
      55,    69,    64,     0,    33,    22,    58,   -30,  -155,   -13,
    -155,  -155,  -155,    71,    73,    94,   129,  -155,  -155,   100,
     113,   103,  -155,   105,   117,   111,     5,   157,  -155,   107,
    -155,   110,    87,   141,   406,   406,    82,   115,   136,   -17,
    -155,  -155,   244,   125,  -155,  -155,  -155,   122,  -155,   441,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   335,   169,
     441,   170,   129,  -155,   171,  -155,   441,   172,     4,     7,
     173,    14,  -155,   164,   130,   126,    17,   441,    47,   441,
     163,   167,   165,   441,   -19,    34,   406,   135,   138,   458,
     441,  -155,  -155,  -155,  -155,    77,    55,    69,    64,     0,
      33,    33,    22,    22,    22,    22,    58,    58,   -30,   -30,
    -155,  -155,  -155,  -155,   131,   140,  -155,   132,  -155,  -155,
    -155,  -155,  -155,  -155,    17,   144,   142,   153,   143,   183,
     148,   195,   187,   198,  -155,  -155,  -155,   174,   178,   184,
    -155,  -155,   406,    34,   406,   406,   406,   149,   180,   168,
     441,  -155,  -155,  -155,    17,   176,  -155,   173,   209,   203,
      17,   216,  -155,   217,   218,   189,    34,    34,    34,   406,
      34,   406,   406,   458,  -155,  -155,  -155,  -155,  -155,    17,
     220,  -155,    17,    17,    17,   223,    34,    34,    34,   406,
    -155,  -155,    17,  -155,  -155,  -155,    17,    34,  -155,  -155
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,     1,   134,   135,   136,   137,   138,   139,   133,
       0,     0,     0,     0,     0,     0,     0,     0,    69,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    42,    84,    86,    88,    91,    93,
      95,    97,    99,   101,   104,   109,   112,   115,   119,   124,
     130,   132,    15,    19,    17,     0,     0,    14,    20,    22,
       0,    26,    24,     0,     0,     0,     0,     0,    71,    83,
      79,    81,     0,     0,     0,     0,     0,     0,     0,    90,
     122,    55,    57,     0,   120,   121,   123,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     0,    13,     0,     0,     0,     0,
       0,     0,    31,     0,     0,    30,     0,     0,     0,     0,
       0,    74,    76,     0,    68,    58,     0,     0,     0,     0,
       0,    56,    54,   131,    85,    92,    94,    96,    98,   100,
     102,   103,   105,   106,   107,   108,   110,   111,   113,   114,
     116,   117,   118,   126,   141,     0,   128,     0,   129,    18,
      12,    21,    23,    25,     0,     0,    36,     0,    34,     0,
       0,     0,     0,     0,    41,    82,    80,     0,     0,     0,
      75,    78,     0,    66,    42,     0,     0,     0,     0,     0,
       0,   125,   127,    28,     0,     0,    32,     0,     0,     0,
       0,     0,    29,     0,     0,     0,    67,    63,    64,    42,
      65,    42,     0,     0,    89,   140,    27,    35,    33,     0,
       0,    40,     0,     0,     0,     0,    60,    61,    62,    42,
      87,    38,     0,    39,    77,    73,     0,    59,    37,    72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,  -155,   161,   -65,  -155,   108,  -155,  -155,
      98,  -155,  -138,  -155,  -155,    10,  -155,  -155,  -155,  -155,
      -1,   -20,   137,  -155,  -155,  -155,  -155,  -155,  -155,  -155,
      91,  -155,  -155,  -155,   106,  -155,     3,   146,  -155,   -23,
     228,   147,   150,   156,   158,   145,     2,   -37,     1,    -3,
     -24,  -155,  -155,  -155,  -154
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    35,    75,    76,    77,    36,    78,    79,    37,
      82,    38,   144,   145,    39,   197,   198,    40,    41,    42,
     102,    44,   103,    45,    46,    47,    48,    49,    50,    51,
     151,   152,    52,    53,    90,    91,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,   185
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   195,    92,   200,    98,   100,   219,   104,   105,   106,
     212,   135,    81,   142,    80,   142,    72,    73,   110,   125,
     126,   127,   142,    88,    83,    97,    93,    94,    95,     3,
       4,     5,     6,     7,     8,     9,   160,   107,    84,   108,
     128,   115,   116,   129,    85,    18,    19,    20,    21,    22,
      87,   130,    23,   131,    24,    89,    25,    26,    27,   143,
      28,   194,    30,    29,    74,   232,   245,   189,   199,   121,
     122,    30,    86,    31,    32,   110,   117,   118,    33,    34,
     172,   173,   174,   175,    96,     3,     4,     5,     6,     7,
       8,     9,   108,   154,   155,   119,   120,   123,   124,   157,
     109,   180,   181,   182,     3,     4,     5,     6,     7,     8,
       9,   149,   150,   111,    27,   112,    28,   170,   171,    29,
     178,   179,   176,   177,   113,   114,   204,   132,    74,    31,
      32,   184,   134,   187,    33,    34,   218,    73,    29,    80,
     156,     3,     4,     5,     6,     7,     8,     9,    31,    32,
     205,   137,   207,    33,    34,   213,   211,   136,   139,   214,
     138,   217,   140,   184,   141,   146,   147,   148,   153,   159,
      27,   162,    28,   158,   223,    29,   163,   186,   188,   190,
     192,   196,   201,   203,   202,    31,    32,   208,   220,   149,
      33,    34,   209,   215,   221,   225,   216,   222,   224,   226,
     227,   228,   229,   230,   246,   231,   142,   242,   235,   243,
     251,   236,   233,   237,   238,   240,   234,   249,   239,   241,
     260,   250,   244,   184,   252,   253,   254,   255,   262,   261,
     247,   266,   263,   264,   265,   133,   193,   248,   256,   161,
     257,   258,   268,   210,   191,   259,   269,     3,     4,     5,
       6,     7,     8,     9,   206,   164,    99,   165,   267,   169,
       0,   166,     0,    18,    19,    20,    21,    22,   167,     0,
      23,   168,    24,     0,    25,    26,    27,     0,    28,     0,
       0,    29,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    31,    32,     0,     0,     0,    33,    34,     0,     0,
       2,     0,   108,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,    18,
      19,    20,    21,    22,     0,     0,    23,     0,    24,     0,
      25,    26,    27,     0,    28,     0,     0,    29,     3,     4,
       5,     6,     7,     8,     9,    30,     0,    31,    32,     0,
       0,     0,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,    28,
       0,     0,    29,     0,     3,     4,     5,     6,     7,     8,
       9,     0,    31,    32,     0,     0,     0,    33,    34,   183,
      18,    19,    20,    21,    22,     0,     0,    23,     0,    24,
       0,    25,    26,    27,     0,    28,     0,     0,    29,     3,
       4,     5,     6,     7,     8,     9,    30,   101,    31,    32,
       0,     0,     0,    33,    34,    18,    19,    20,    21,    22,
       0,     0,    23,     0,    24,     0,    25,    26,    27,     0,
      28,     0,     0,    29,     3,     4,     5,     6,     7,     8,
       9,    30,     0,    31,    32,     0,     0,     0,    33,    34,
       0,     3,     4,     5,     6,     7,     8,     9,     0,     0,
       0,     0,     0,    27,     0,    28,     0,     0,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,    28,    33,    34,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,     0,     0,
      33,    34
};

static const yytype_int16 yycheck[] =
{
       1,   139,    22,   141,    27,    29,   160,    31,    32,    33,
      29,    76,     8,     8,    11,     8,     7,     8,    35,    49,
      50,    51,     8,    20,     8,    26,    23,    24,    25,     3,
       4,     5,     6,     7,     8,     9,    53,    34,     8,    58,
      53,    41,    42,    56,     8,    19,    20,    21,    22,    23,
      18,    64,    26,    66,    28,     8,    30,    31,    32,    54,
      34,    54,    45,    37,    55,   203,   220,   132,    54,    47,
      48,    45,    53,    47,    48,    35,    43,    44,    52,    53,
     117,   118,   119,   120,    58,     3,     4,     5,     6,     7,
       8,     9,    58,    94,    95,    62,    63,    39,    40,    96,
      59,   125,   126,   127,     3,     4,     5,     6,     7,     8,
       9,    24,    25,    36,    32,    60,    34,   115,   116,    37,
     123,   124,   121,   122,    55,    61,   146,    56,    55,    47,
      48,   128,    38,   130,    52,    53,   159,     8,    37,   136,
      58,     3,     4,     5,     6,     7,     8,     9,    47,    48,
     147,    38,   149,    52,    53,   156,   153,    57,    53,   156,
      57,   158,    45,   160,    53,     8,    59,    57,    27,    33,
      32,    46,    34,    58,   194,    37,    54,     8,     8,     8,
       8,     8,    18,    57,    54,    47,    48,    24,    57,    24,
      52,    53,    25,    58,    54,    53,    58,    65,    54,    46,
      57,    18,    54,     8,   224,    18,     8,    58,    24,    29,
     230,   212,    38,   214,   215,   216,    38,     8,   215,   216,
     243,    18,    54,   220,     8,     8,     8,    38,     8,   249,
      54,     8,   252,   253,   254,    74,   138,   227,   239,   102,
     241,   242,   262,   152,   136,   242,   266,     3,     4,     5,
       6,     7,     8,     9,   148,   109,    28,   110,   259,   114,
      -1,   111,    -1,    19,    20,    21,    22,    23,   112,    -1,
      26,   113,    28,    -1,    30,    31,    32,    -1,    34,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    47,    48,    -1,    -1,    -1,    52,    53,    -1,    -1,
       0,    -1,    58,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    -1,    -1,    26,    -1,    28,    -1,
      30,    31,    32,    -1,    34,    -1,    -1,    37,     3,     4,
       5,     6,     7,     8,     9,    45,    -1,    47,    48,    -1,
      -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,
      -1,    -1,    37,    -1,     3,     4,     5,     6,     7,     8,
       9,    -1,    47,    48,    -1,    -1,    -1,    52,    53,    54,
      19,    20,    21,    22,    23,    -1,    -1,    26,    -1,    28,
      -1,    30,    31,    32,    -1,    34,    -1,    -1,    37,     3,
       4,     5,     6,     7,     8,     9,    45,    46,    47,    48,
      -1,    -1,    -1,    52,    53,    19,    20,    21,    22,    23,
      -1,    -1,    26,    -1,    28,    -1,    30,    31,    32,    -1,
      34,    -1,    -1,    37,     3,     4,     5,     6,     7,     8,
       9,    45,    -1,    47,    48,    -1,    -1,    -1,    52,    53,
      -1,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    34,    52,    53,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      52,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    19,    20,
      21,    22,    23,    26,    28,    30,    31,    32,    34,    37,
      45,    47,    48,    52,    53,    69,    73,    76,    78,    81,
      84,    85,    86,    87,    88,    90,    91,    92,    93,    94,
      95,    96,    99,   100,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,     7,     8,    55,    70,    71,    72,    74,    75,
     103,     8,    77,     8,     8,     8,    53,    18,   103,     8,
     101,   102,    88,   103,   103,   103,    58,    87,   106,   107,
     117,    46,    87,    89,   117,   117,   117,   103,    58,    59,
      35,    36,    60,    55,    61,    41,    42,    43,    44,    62,
      63,    47,    48,    39,    40,    49,    50,    51,    53,    56,
      64,    66,    56,    71,    38,    72,    57,    38,    57,    53,
      45,    53,     8,    54,    79,    80,     8,    59,    57,    24,
      25,    97,    98,    27,    87,    87,    58,   103,    58,    33,
      53,    89,    46,    54,   104,   108,   109,   110,   111,   112,
     113,   113,   114,   114,   114,   114,   115,   115,   116,   116,
     117,   117,   117,    54,   103,   121,     8,   103,     8,    72,
       8,    74,     8,    77,    54,    79,     8,    82,    83,    54,
      79,    18,    54,    57,    88,   103,   101,   103,    24,    25,
      97,   103,    29,    87,   103,    58,    58,   103,   106,   121,
      57,    54,    65,    88,    54,    53,    46,    57,    18,    54,
       8,    18,    79,    38,    38,    24,    87,    87,    87,   103,
      87,   103,    58,    29,    54,   121,    88,    54,    82,     8,
      18,    88,     8,     8,     8,    38,    87,    87,    87,   103,
     106,    88,     8,    88,    88,    88,     8,    87,    88,    88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    70,    70,    70,    71,    71,    72,    72,
      73,    74,    74,    75,    76,    77,    77,    78,    78,    79,
      79,    80,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    88,    89,    89,    90,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    93,
      94,    95,    96,    96,    96,    97,    97,    98,    99,   100,
     101,   101,   102,   102,   103,   104,   104,   105,   105,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   112,   113,   113,   113,   113,   113,
     114,   114,   114,   115,   115,   115,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   119,   119,   120,   120,   120,   120,   120,   120,   120,
     121,   121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     0,     4,     2,     1,     1,     2,     1,     3,     1,
       2,     3,     1,     3,     2,     3,     1,     6,     5,     3,
       1,     1,     5,     3,     1,     3,     1,     8,     7,     7,
       6,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     2,     2,     1,     3,     7,
       6,     6,     6,     5,     5,     5,     4,     5,     3,     1,
       1,     2,     8,     7,     3,     2,     1,     5,     4,     2,
       3,     1,     3,     1,     1,     3,     1,     6,     1,     5,
       2,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     2,     2,     1,     4,     3,     4,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: program import_stmt  */
#line 95 "rules.y"
                        {
        (yyval.node) = make(PROGRAM_NODE, IMPORT_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1704 "rules.tab.c"
    break;

  case 3: /* program: program export_stmt  */
#line 99 "rules.y"
                          {
        (yyval.node) = make(PROGRAM_NODE, EXPORT_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1713 "rules.tab.c"
    break;

  case 4: /* program: program global_variable_stmt  */
#line 103 "rules.y"
                                   {
        (yyval.node) = make(PROGRAM_NODE, GLOBAL_VARIABLE_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1722 "rules.tab.c"
    break;

  case 5: /* program: program function_stmt  */
#line 107 "rules.y"
                            {
        (yyval.node) = make(PROGRAM_NODE, FUNCTION_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1731 "rules.tab.c"
    break;

  case 6: /* program: program type_stmt  */
#line 111 "rules.y"
                        {
        (yyval.node) = make(PROGRAM_NODE, TYPE_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1740 "rules.tab.c"
    break;

  case 7: /* program: program method_stmt  */
#line 115 "rules.y"
                          {
        (yyval.node) = make(PROGRAM_NODE, METHOD_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1749 "rules.tab.c"
    break;

  case 8: /* program: program constructor_stmt  */
#line 119 "rules.y"
                               {
        (yyval.node) = make(PROGRAM_NODE, CONSTRUCTOR_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1758 "rules.tab.c"
    break;

  case 9: /* program: program destructor_stmt  */
#line 123 "rules.y"
                              {
        (yyval.node) = make(PROGRAM_NODE, DESTRUCTOR_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1767 "rules.tab.c"
    break;

  case 10: /* program: program stmt  */
#line 127 "rules.y"
                   {
        (yyval.node) = make(PROGRAM_NODE, STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1776 "rules.tab.c"
    break;

  case 11: /* program: %empty  */
#line 131 "rules.y"
      {
        (yyval.node) = make(PROGRAM_NODE, NO_OPTION, 1, 0);
        node_result = (yyval.node);
    }
#line 1785 "rules.tab.c"
    break;

  case 12: /* import_stmt: IMPORT module_path AS IDENTIFIER  */
#line 138 "rules.y"
                                     {
        (yyval.node) = make(IMPORT_STMT_NODE, DEFAULT_OPTION, (yyvsp[-3].num), 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1793 "rules.tab.c"
    break;

  case 13: /* module_path: module_path_upwards module_path_compact  */
#line 144 "rules.y"
                                            {
        (yyval.node) = make(MODULE_PATH_NODE, MODULE_PATH_COMPACT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1801 "rules.tab.c"
    break;

  case 14: /* module_path: module_path_compact  */
#line 147 "rules.y"
                          {
        (yyval.node) = make(MODULE_PATH_NODE, MODULE_PATH_COMPACT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1809 "rules.tab.c"
    break;

  case 15: /* module_path: STRING  */
#line 150 "rules.y"
             {
        (yyval.node) = make(MODULE_PATH_NODE, MODULE_PATH_STRING_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1817 "rules.tab.c"
    break;

  case 16: /* module_path_upwards: '^' module_path_upwards  */
#line 156 "rules.y"
                            {
        (yyval.node) = make(MODULE_PATH_UPWARDS_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1825 "rules.tab.c"
    break;

  case 17: /* module_path_upwards: '^'  */
#line 159 "rules.y"
          {
        (yyval.node) = make(MODULE_PATH_UPWARDS_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].num), 0);
    }
#line 1833 "rules.tab.c"
    break;

  case 18: /* module_path_compact: IDENTIFIER '.' module_path_compact  */
#line 165 "rules.y"
                                       {
        (yyval.node) = make(MODULE_PATH_COMPACT_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1841 "rules.tab.c"
    break;

  case 19: /* module_path_compact: IDENTIFIER  */
#line 168 "rules.y"
                 {
        (yyval.node) = make(MODULE_PATH_COMPACT_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1849 "rules.tab.c"
    break;

  case 20: /* export_stmt: EXPORT export_item_list  */
#line 174 "rules.y"
                            {
        (yyval.node) = make(EXPORT_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1857 "rules.tab.c"
    break;

  case 21: /* export_item_list: export_item ',' export_item_list  */
#line 180 "rules.y"
                                     {
        (yyval.node) = make(EXPORT_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1865 "rules.tab.c"
    break;

  case 22: /* export_item_list: export_item  */
#line 183 "rules.y"
                  {
        (yyval.node) = make(EXPORT_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1873 "rules.tab.c"
    break;

  case 23: /* export_item: expr AS IDENTIFIER  */
#line 189 "rules.y"
                       {
        (yyval.node) = make(EXPORT_ITEM_LIST_NODE, DEFAULT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1881 "rules.tab.c"
    break;

  case 24: /* global_variable_stmt: GLOBAL identifier_item_list  */
#line 195 "rules.y"
                                {
        (yyval.node) = make(GLOBAL_VARIABLE_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1889 "rules.tab.c"
    break;

  case 25: /* identifier_item_list: IDENTIFIER ',' identifier_item_list  */
#line 201 "rules.y"
                                        {
        (yyval.node) = make(IDENTIFIER_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1897 "rules.tab.c"
    break;

  case 26: /* identifier_item_list: IDENTIFIER  */
#line 204 "rules.y"
                 {
        (yyval.node) = make(IDENTIFIER_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1905 "rules.tab.c"
    break;

  case 27: /* function_stmt: FUNCTION IDENTIFIER '(' parameter_list ')' block_stmt  */
#line 210 "rules.y"
                                                          {
        (yyval.node) = make(FUNCTION_STMT_NODE, FUNCTION_STMT_OPTION, (yyvsp[-5].num), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1913 "rules.tab.c"
    break;

  case 28: /* function_stmt: FUNCTION IDENTIFIER '(' ')' block_stmt  */
#line 213 "rules.y"
                                             {
        (yyval.node) = make(FUNCTION_STMT_NODE, FUNCTION_STMT_OPTION, (yyvsp[-4].num), 3, (yyvsp[-3].node), NULL, (yyvsp[0].node));
    }
#line 1921 "rules.tab.c"
    break;

  case 29: /* parameter_list: parameter_item ',' parameter_list  */
#line 219 "rules.y"
                                      {
        (yyval.node) = make(PARAMETER_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1929 "rules.tab.c"
    break;

  case 30: /* parameter_list: parameter_item  */
#line 222 "rules.y"
                     {
        (yyval.node) = make(PARAMETER_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1937 "rules.tab.c"
    break;

  case 31: /* parameter_item: IDENTIFIER  */
#line 228 "rules.y"
               {
        (yyval.node) = make(PARAMETER_ITEM_NODE, DEFAULT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1945 "rules.tab.c"
    break;

  case 32: /* type_stmt: TYPE IDENTIFIER '{' member_list '}'  */
#line 234 "rules.y"
                                         {
        (yyval.node) = make(TYPE_STMT_NODE, DEFAULT_OPTION, (yyvsp[-4].num), 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 1953 "rules.tab.c"
    break;

  case 33: /* member_list: member_item ',' member_list  */
#line 239 "rules.y"
                                {
        (yyval.node) = make(MEMBER_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1961 "rules.tab.c"
    break;

  case 34: /* member_list: member_item  */
#line 242 "rules.y"
                  {
        (yyval.node) = make(MEMBER_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1969 "rules.tab.c"
    break;

  case 35: /* member_item: IDENTIFIER '(' ')'  */
#line 248 "rules.y"
                       {
        (yyval.node) = make(MEMBER_ITEM_NODE, MEMBER_METHOD_OPTION, (yyvsp[-2].node)->lineno, 1, (yyvsp[-2].node));
    }
#line 1977 "rules.tab.c"
    break;

  case 36: /* member_item: IDENTIFIER  */
#line 251 "rules.y"
                 {
        (yyval.node) = make(MEMBER_ITEM_NODE, MEMBER_FIELD_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1985 "rules.tab.c"
    break;

  case 37: /* method_stmt: METHOD IDENTIFIER '(' parameter_list ')' OF IDENTIFIER block_stmt  */
#line 257 "rules.y"
                                                                      {
        (yyval.node) = make(METHOD_STMT_NODE, DEFAULT_OPTION, (yyvsp[-7].num), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1993 "rules.tab.c"
    break;

  case 38: /* method_stmt: METHOD IDENTIFIER '(' ')' OF IDENTIFIER block_stmt  */
#line 260 "rules.y"
                                                         {
        (yyval.node) = make(METHOD_STMT_NODE, DEFAULT_OPTION, (yyvsp[-6].num), 4, (yyvsp[-5].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2001 "rules.tab.c"
    break;

  case 39: /* constructor_stmt: CONSTRUCTOR '(' parameter_list ')' OF IDENTIFIER block_stmt  */
#line 266 "rules.y"
                                                                {
        (yyval.node) = make(CONSTRUCTOR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-6].num), 3, (yyvsp[-4].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2009 "rules.tab.c"
    break;

  case 40: /* constructor_stmt: CONSTRUCTOR '(' ')' OF IDENTIFIER block_stmt  */
#line 269 "rules.y"
                                                   {
        (yyval.node) = make(CONSTRUCTOR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-5].num), 3, NULL, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2017 "rules.tab.c"
    break;

  case 41: /* destructor_stmt: DESTRUCTOR OF IDENTIFIER block_stmt  */
#line 275 "rules.y"
                                        {
        (yyval.node) = make(DESTRUCTOR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-3].num), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2025 "rules.tab.c"
    break;

  case 42: /* stmt: expr  */
#line 281 "rules.y"
         {
        (yyval.node) = make(STMT_NODE, EXPR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2033 "rules.tab.c"
    break;

  case 43: /* stmt: block_stmt  */
#line 284 "rules.y"
                 {
        (yyval.node) = make(STMT_NODE, BLOCK_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2041 "rules.tab.c"
    break;

  case 44: /* stmt: while_stmt  */
#line 287 "rules.y"
                 {
        (yyval.node) = make(STMT_NODE, WHILE_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2049 "rules.tab.c"
    break;

  case 45: /* stmt: for_stmt  */
#line 290 "rules.y"
               {
        (yyval.node) = make(STMT_NODE, FOR_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2057 "rules.tab.c"
    break;

  case 46: /* stmt: if_stmt  */
#line 293 "rules.y"
              {
        (yyval.node) = make(STMT_NODE, IF_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2065 "rules.tab.c"
    break;

  case 47: /* stmt: continue_stmt  */
#line 296 "rules.y"
                    {
        (yyval.node) = make(STMT_NODE, CONTINUE_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2073 "rules.tab.c"
    break;

  case 48: /* stmt: break_stmt  */
#line 299 "rules.y"
                 {
        (yyval.node) = make(STMT_NODE, BREAK_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2081 "rules.tab.c"
    break;

  case 49: /* stmt: return_stmt  */
#line 302 "rules.y"
                  {
        (yyval.node) = make(STMT_NODE, RETURN_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2089 "rules.tab.c"
    break;

  case 50: /* stmt: try_catch_stmt  */
#line 305 "rules.y"
                     {
        (yyval.node) = make(STMT_NODE, TRY_CATCH_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2097 "rules.tab.c"
    break;

  case 51: /* stmt: signal_stmt  */
#line 308 "rules.y"
                  {
        (yyval.node) = make(STMT_NODE, SIGNAL_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2105 "rules.tab.c"
    break;

  case 52: /* stmt: var_stmt  */
#line 311 "rules.y"
               {
        (yyval.node) = make(STMT_NODE, VAR_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2113 "rules.tab.c"
    break;

  case 53: /* stmt: stmt ';'  */
#line 314 "rules.y"
               {
        (yyval.node) = make(STMT_NODE, STMT_OPTION, (yyvsp[-1].node)->lineno, 1, (yyvsp[-1].node));
    }
#line 2121 "rules.tab.c"
    break;

  case 54: /* block_stmt: '{' stmt_list '}'  */
#line 320 "rules.y"
                      {
        (yyval.node) = make(BLOCK_STMT_NODE, DEFAULT_OPTION, (yyvsp[-2].num), 1, (yyvsp[-1].node));
    }
#line 2129 "rules.tab.c"
    break;

  case 55: /* block_stmt: '{' '}'  */
#line 323 "rules.y"
              {
        (yyval.node) = make(BLOCK_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 0);
    }
#line 2137 "rules.tab.c"
    break;

  case 56: /* stmt_list: stmt stmt_list  */
#line 329 "rules.y"
                   {
        (yyval.node) = make(STMT_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2145 "rules.tab.c"
    break;

  case 57: /* stmt_list: stmt  */
#line 332 "rules.y"
           {
        (yyval.node) = make(STMT_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2153 "rules.tab.c"
    break;

  case 58: /* while_stmt: WHILE expr stmt  */
#line 338 "rules.y"
                    {
        (yyval.node) = make(WHILE_STMT_NODE, DEFAULT_OPTION, (yyvsp[-2].num), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2161 "rules.tab.c"
    break;

  case 59: /* for_stmt: FOR stmt ';' expr ';' expr stmt  */
#line 344 "rules.y"
                                    {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_COND_POST_OPTION, (yyvsp[-6].num), 4, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2169 "rules.tab.c"
    break;

  case 60: /* for_stmt: FOR ';' expr ';' expr stmt  */
#line 347 "rules.y"
                                 {
        (yyval.node) = make(FOR_STMT_NODE, FOR_COND_POST_OPTION, (yyvsp[-5].num), 4, NULL, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2177 "rules.tab.c"
    break;

  case 61: /* for_stmt: FOR stmt ';' ';' expr stmt  */
#line 350 "rules.y"
                                 {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_POST_OPTION, (yyvsp[-5].num), 4, (yyvsp[-4].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2185 "rules.tab.c"
    break;

  case 62: /* for_stmt: FOR stmt ';' expr ';' stmt  */
#line 353 "rules.y"
                                 {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_COND_OPTION, (yyvsp[-5].num), 4, (yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node));
    }
#line 2193 "rules.tab.c"
    break;

  case 63: /* for_stmt: FOR ';' ';' expr stmt  */
#line 356 "rules.y"
                            {
        (yyval.node) = make(FOR_STMT_NODE, FOR_POST_OPTION, (yyvsp[-4].num), 4, NULL, NULL, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2201 "rules.tab.c"
    break;

  case 64: /* for_stmt: FOR ';' expr ';' stmt  */
#line 359 "rules.y"
                            {
        (yyval.node) = make(FOR_STMT_NODE, FOR_COND_OPTION, (yyvsp[-4].num), 4, NULL, (yyvsp[-2].node), NULL, (yyvsp[0].node));
    }
#line 2209 "rules.tab.c"
    break;

  case 65: /* for_stmt: FOR stmt ';' ';' stmt  */
#line 362 "rules.y"
                            {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_OPTION, (yyvsp[-4].num), 4, (yyvsp[-3].node), NULL, NULL, (yyvsp[0].node));
    }
#line 2217 "rules.tab.c"
    break;

  case 66: /* for_stmt: FOR ';' ';' stmt  */
#line 365 "rules.y"
                       {
        (yyval.node) = make(FOR_STMT_NODE, FOR_NOTHING_OPTION, (yyvsp[-3].num), 4, NULL, NULL, NULL, (yyvsp[0].node));
    }
#line 2225 "rules.tab.c"
    break;

  case 67: /* if_stmt: IF expr stmt ELSE stmt  */
#line 371 "rules.y"
                           {
        (yyval.node) = make(IF_STMT_NODE, IF_WITH_ELSE_OPTION, (yyvsp[-4].num), 3, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2233 "rules.tab.c"
    break;

  case 68: /* if_stmt: IF expr stmt  */
#line 374 "rules.y"
                   {
        (yyval.node) = make(IF_STMT_NODE, IF_WITHOUT_ELSE_OPTION, (yyvsp[-2].num), 3, (yyvsp[-1].node), (yyvsp[0].node), NULL);
    }
#line 2241 "rules.tab.c"
    break;

  case 69: /* continue_stmt: CONTINUE  */
#line 380 "rules.y"
             {
        (yyval.node) = make(CONTINUE_STMT_NODE, DEFAULT_OPTION, (yyvsp[0].num), 0);
    }
#line 2249 "rules.tab.c"
    break;

  case 70: /* break_stmt: BREAK  */
#line 386 "rules.y"
          {
        (yyval.node) = make(BREAK_STMT_NODE, DEFAULT_OPTION, (yyvsp[0].num), 0);
    }
#line 2257 "rules.tab.c"
    break;

  case 71: /* return_stmt: RETURN expr  */
#line 392 "rules.y"
                {
        (yyval.node) = make(RETURN_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2265 "rules.tab.c"
    break;

  case 72: /* try_catch_stmt: TRY block_stmt catch_item_list FINALLY CATCH AS IDENTIFIER block_stmt  */
#line 398 "rules.y"
                                                                          {
        (yyval.node) = make(TRY_CATCH_STMT_NODE, TRY_CATCH_FULL_OPTION, (yyvsp[-7].num), 4, (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2273 "rules.tab.c"
    break;

  case 73: /* try_catch_stmt: TRY block_stmt FINALLY CATCH AS IDENTIFIER block_stmt  */
#line 401 "rules.y"
                                                            {
        (yyval.node) = make(TRY_CATCH_STMT_NODE, TRY_CATCH_ONLY_UNIVERSAL_OPTION, (yyvsp[-6].num), 4, (yyvsp[-5].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2281 "rules.tab.c"
    break;

  case 74: /* try_catch_stmt: TRY block_stmt catch_item_list  */
#line 404 "rules.y"
                                     {
        (yyval.node) = make(TRY_CATCH_STMT_NODE, TRY_CATCH_ONLY_SPECIFIC_OPTION, (yyvsp[-2].num), 4, (yyvsp[-1].node), (yyvsp[0].node), NULL, NULL);
    }
#line 2289 "rules.tab.c"
    break;

  case 75: /* catch_item_list: catch_item catch_item_list  */
#line 410 "rules.y"
                               {
        (yyval.node) = make(CATCH_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2297 "rules.tab.c"
    break;

  case 76: /* catch_item_list: catch_item  */
#line 413 "rules.y"
                 {
        (yyval.node) = make(CATCH_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2305 "rules.tab.c"
    break;

  case 77: /* catch_item: CATCH expr AS IDENTIFIER block_stmt  */
#line 419 "rules.y"
                                        {
        (yyval.node) = make(CATCH_ITEM_NODE, DEFAULT_OPTION, (yyvsp[-4].num), 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2313 "rules.tab.c"
    break;

  case 78: /* signal_stmt: SIGNAL expr BECAUSE expr  */
#line 425 "rules.y"
                             {
        (yyval.node) = make(SIGNAL_STMT_NODE, DEFAULT_OPTION, (yyvsp[-3].num), 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2321 "rules.tab.c"
    break;

  case 79: /* var_stmt: VAR assignment_item_list  */
#line 431 "rules.y"
                             {
        (yyval.node) = make(VAR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2329 "rules.tab.c"
    break;

  case 80: /* assignment_item_list: assignment_item ',' assignment_item_list  */
#line 437 "rules.y"
                                             {
        (yyval.node) = make(ASSIGNMENT_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2337 "rules.tab.c"
    break;

  case 81: /* assignment_item_list: assignment_item  */
#line 440 "rules.y"
                      {
        (yyval.node) = make(ASSIGNMENT_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2345 "rules.tab.c"
    break;

  case 82: /* assignment_item: IDENTIFIER '=' expr  */
#line 445 "rules.y"
                        {
        (yyval.node) = make(ASSIGNMENT_ITEM_NODE, ASSIGNMENT_ITEM_FULL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2353 "rules.tab.c"
    break;

  case 83: /* assignment_item: IDENTIFIER  */
#line 448 "rules.y"
                 {
        (yyval.node) = make(ASSIGNMENT_ITEM_NODE, ASSIGNMENT_ITEM_NAME_OPTION, (yyvsp[0].node)->lineno, 2, (yyvsp[0].node), NULL);
    }
#line 2361 "rules.tab.c"
    break;

  case 84: /* expr: assignment  */
#line 453 "rules.y"
               {
        (yyval.node) = make(EXPR_NODE, DEFAULT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2369 "rules.tab.c"
    break;

  case 85: /* assignment: inline_if '=' assignment  */
#line 459 "rules.y"
                             {
        (yyval.node) = make(ASSIGNMENT_NODE, ASSIGNMENT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2377 "rules.tab.c"
    break;

  case 86: /* assignment: inline_if  */
#line 462 "rules.y"
                {
        (yyval.node) = make(ASSIGNMENT_NODE, INLINE_IF_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2385 "rules.tab.c"
    break;

  case 87: /* inline_if: WHEN new THEN new ELSE new  */
#line 468 "rules.y"
                               {
        (yyval.node) = make(INLINE_IF_NODE, INLINE_IF_OPTION, (yyvsp[-5].num), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2393 "rules.tab.c"
    break;

  case 88: /* inline_if: new  */
#line 471 "rules.y"
          {
        (yyval.node) = make(INLINE_IF_NODE, NEW_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2401 "rules.tab.c"
    break;

  case 89: /* new: NEW logical_or '(' expr_list ')'  */
#line 477 "rules.y"
                                     {
        (yyval.node) = make(NEW_NODE, NEW_OPTION, (yyvsp[-4].num), 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2409 "rules.tab.c"
    break;

  case 90: /* new: NEW logical_or  */
#line 480 "rules.y"
                     {
        (yyval.node) = make(NEW_NODE, NEW_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2417 "rules.tab.c"
    break;

  case 91: /* new: logical_or  */
#line 483 "rules.y"
                 {
        (yyval.node) = make(NEW_NODE, LOGICAL_OR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2425 "rules.tab.c"
    break;

  case 92: /* logical_or: logical_or OR logical_and  */
#line 489 "rules.y"
                              {
        (yyval.node) = make(LOGICAL_OR_NODE, LOGICAL_OR_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2433 "rules.tab.c"
    break;

  case 93: /* logical_or: logical_and  */
#line 492 "rules.y"
                  {
        (yyval.node) = make(LOGICAL_OR_NODE, LOGICAL_AND_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2441 "rules.tab.c"
    break;

  case 94: /* logical_and: logical_and AND bitwise_or  */
#line 498 "rules.y"
                               {
        (yyval.node) = make(LOGICAL_AND_NODE, LOGICAL_AND_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2449 "rules.tab.c"
    break;

  case 95: /* logical_and: bitwise_or  */
#line 501 "rules.y"
                 {
        (yyval.node) = make(LOGICAL_AND_NODE, BITWISE_OR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2457 "rules.tab.c"
    break;

  case 96: /* bitwise_or: bitwise_or '|' bitwise_xor  */
#line 507 "rules.y"
                               {
        (yyval.node) = make(BITWISE_OR_NODE, BITWISE_OR_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2465 "rules.tab.c"
    break;

  case 97: /* bitwise_or: bitwise_xor  */
#line 510 "rules.y"
                  {
        (yyval.node) = make(BITWISE_OR_NODE, BITWISE_XOR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2473 "rules.tab.c"
    break;

  case 98: /* bitwise_xor: bitwise_xor '^' bitwise_and  */
#line 516 "rules.y"
                                {
        (yyval.node) = make(BITWISE_XOR_NODE, BITWISE_XOR_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2481 "rules.tab.c"
    break;

  case 99: /* bitwise_xor: bitwise_and  */
#line 519 "rules.y"
                  {
        (yyval.node) = make(BITWISE_XOR_NODE, BITWISE_AND_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2489 "rules.tab.c"
    break;

  case 100: /* bitwise_and: bitwise_and '&' equality  */
#line 525 "rules.y"
                             {
        (yyval.node) = make(BITWISE_AND_NODE, BITWISE_AND_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2497 "rules.tab.c"
    break;

  case 101: /* bitwise_and: equality  */
#line 528 "rules.y"
               {
        (yyval.node) = make(BITWISE_AND_NODE, EQUALITY_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2505 "rules.tab.c"
    break;

  case 102: /* equality: equality EQ relational  */
#line 534 "rules.y"
                           {
        (yyval.node) = make(EQUALITY_NODE, EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2513 "rules.tab.c"
    break;

  case 103: /* equality: equality NE relational  */
#line 537 "rules.y"
                             {
        (yyval.node) = make(EQUALITY_NODE, NOT_EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2521 "rules.tab.c"
    break;

  case 104: /* equality: relational  */
#line 540 "rules.y"
                 {
        (yyval.node) = make(EQUALITY_NODE, RELATIONAL_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2529 "rules.tab.c"
    break;

  case 105: /* relational: relational LE sum  */
#line 546 "rules.y"
                      {
        (yyval.node) = make(RELATIONAL_NODE, LESS_EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2537 "rules.tab.c"
    break;

  case 106: /* relational: relational GE sum  */
#line 549 "rules.y"
                        {
        (yyval.node) = make(RELATIONAL_NODE, GREATER_EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2545 "rules.tab.c"
    break;

  case 107: /* relational: relational '<' sum  */
#line 552 "rules.y"
                         {
        (yyval.node) = make(RELATIONAL_NODE, LESS_THAN_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2553 "rules.tab.c"
    break;

  case 108: /* relational: relational '>' sum  */
#line 555 "rules.y"
                         {
        (yyval.node) = make(RELATIONAL_NODE, GREATER_THAN_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2561 "rules.tab.c"
    break;

  case 109: /* relational: sum  */
#line 558 "rules.y"
          {
        (yyval.node) = make(RELATIONAL_NODE, SUM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2569 "rules.tab.c"
    break;

  case 110: /* sum: sum '+' bitwise_shift  */
#line 564 "rules.y"
                          {
        (yyval.node) = make(SUM_NODE, ADDITION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2577 "rules.tab.c"
    break;

  case 111: /* sum: sum '-' bitwise_shift  */
#line 567 "rules.y"
                            {
        (yyval.node) = make(SUM_NODE, SUBTRACTION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2585 "rules.tab.c"
    break;

  case 112: /* sum: bitwise_shift  */
#line 570 "rules.y"
                    {
        (yyval.node) = make(SUM_NODE, BITWISE_SHIFT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2593 "rules.tab.c"
    break;

  case 113: /* bitwise_shift: bitwise_shift LSHIFT term  */
#line 576 "rules.y"
                              {
        (yyval.node) = make(BITWISE_SHIFT_NODE, LSHIFT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2601 "rules.tab.c"
    break;

  case 114: /* bitwise_shift: bitwise_shift RSHIFT term  */
#line 579 "rules.y"
                                {
        (yyval.node) = make(BITWISE_SHIFT_NODE, RSHIFT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2609 "rules.tab.c"
    break;

  case 115: /* bitwise_shift: term  */
#line 582 "rules.y"
           {
        (yyval.node) = make(BITWISE_SHIFT_NODE, TERM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2617 "rules.tab.c"
    break;

  case 116: /* term: term '*' prefix_op  */
#line 588 "rules.y"
                       {
        (yyval.node) = make(TERM_NODE, MULTIPLICATION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2625 "rules.tab.c"
    break;

  case 117: /* term: term '/' prefix_op  */
#line 591 "rules.y"
                         {
        (yyval.node) = make(TERM_NODE, DIVISION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2633 "rules.tab.c"
    break;

  case 118: /* term: term '%' prefix_op  */
#line 594 "rules.y"
                         {
        (yyval.node) = make(TERM_NODE, REMAINDER_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2641 "rules.tab.c"
    break;

  case 119: /* term: prefix_op  */
#line 597 "rules.y"
                {
        (yyval.node) = make(TERM_NODE, PREFIX_OP_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2649 "rules.tab.c"
    break;

  case 120: /* prefix_op: '+' prefix_op  */
#line 603 "rules.y"
                  {
        (yyval.node) = make(PREFIX_OP_NODE, POSITIVE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2657 "rules.tab.c"
    break;

  case 121: /* prefix_op: '-' prefix_op  */
#line 606 "rules.y"
                    {
        (yyval.node) = make(PREFIX_OP_NODE, NEGATIVE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2665 "rules.tab.c"
    break;

  case 122: /* prefix_op: NOT prefix_op  */
#line 609 "rules.y"
                    {
        (yyval.node) = make(PREFIX_OP_NODE, NOT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2673 "rules.tab.c"
    break;

  case 123: /* prefix_op: '~' prefix_op  */
#line 612 "rules.y"
                   {
        (yyval.node) = make(PREFIX_OP_NODE, INVERSE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2681 "rules.tab.c"
    break;

  case 124: /* prefix_op: primary  */
#line 615 "rules.y"
              {
        (yyval.node) = make(PREFIX_OP_NODE, PRIMARY_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2689 "rules.tab.c"
    break;

  case 125: /* primary: primary '(' expr_list ')'  */
#line 621 "rules.y"
                              {
        (yyval.node) = make(PRIMARY_NODE, CALL_OPTION, (yyvsp[-3].node)->lineno, 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2697 "rules.tab.c"
    break;

  case 126: /* primary: primary '(' ')'  */
#line 624 "rules.y"
                      {
        (yyval.node) = make(PRIMARY_NODE, CALL_OPTION, (yyvsp[-2].node)->lineno, 1, (yyvsp[-2].node));
    }
#line 2705 "rules.tab.c"
    break;

  case 127: /* primary: primary '[' expr ']'  */
#line 627 "rules.y"
                           {
        (yyval.node) = make(PRIMARY_NODE, INDEX_OPTION, (yyvsp[-3].node)->lineno, 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2713 "rules.tab.c"
    break;

  case 128: /* primary: primary '.' IDENTIFIER  */
#line 630 "rules.y"
                             {
        (yyval.node) = make(PRIMARY_NODE, FIELD_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2721 "rules.tab.c"
    break;

  case 129: /* primary: primary ':' IDENTIFIER  */
#line 633 "rules.y"
                             {
        (yyval.node) = make(PRIMARY_NODE, METHOD_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2729 "rules.tab.c"
    break;

  case 130: /* primary: elementary  */
#line 636 "rules.y"
                 {
        (yyval.node) = make(PRIMARY_NODE, ELEMENTARY_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2737 "rules.tab.c"
    break;

  case 131: /* elementary: '(' expr ')'  */
#line 642 "rules.y"
                 {
        (yyval.node) = make(ELEMENTARY_NODE, EXPR_OPTION, (yyvsp[-2].num), 1, (yyvsp[-1].node));
    }
#line 2745 "rules.tab.c"
    break;

  case 132: /* elementary: literal  */
#line 645 "rules.y"
              {
        (yyval.node) = make(ELEMENTARY_NODE, LITERAL_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2753 "rules.tab.c"
    break;

  case 133: /* literal: NULLV  */
#line 651 "rules.y"
          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2761 "rules.tab.c"
    break;

  case 134: /* literal: BOOL  */
#line 654 "rules.y"
           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2769 "rules.tab.c"
    break;

  case 135: /* literal: CHAR  */
#line 657 "rules.y"
           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2777 "rules.tab.c"
    break;

  case 136: /* literal: INT  */
#line 660 "rules.y"
          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2785 "rules.tab.c"
    break;

  case 137: /* literal: FLOAT  */
#line 663 "rules.y"
            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2793 "rules.tab.c"
    break;

  case 138: /* literal: STRING  */
#line 666 "rules.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2801 "rules.tab.c"
    break;

  case 139: /* literal: IDENTIFIER  */
#line 669 "rules.y"
                 {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2809 "rules.tab.c"
    break;

  case 140: /* expr_list: expr ',' expr_list  */
#line 675 "rules.y"
                       {
        (yyval.node) = make(EXPR_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2817 "rules.tab.c"
    break;

  case 141: /* expr_list: expr  */
#line 678 "rules.y"
           {
        (yyval.node) = make(EXPR_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2825 "rules.tab.c"
    break;


#line 2829 "rules.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 682 "rules.y"
