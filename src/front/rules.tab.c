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
  YYSYMBOL_COPY = 19,                      /* COPY  */
  YYSYMBOL_REF = 20,                       /* REF  */
  YYSYMBOL_PASS = 21,                      /* PASS  */
  YYSYMBOL_CONTINUE = 22,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 23,                     /* BREAK  */
  YYSYMBOL_RETURN = 24,                    /* RETURN  */
  YYSYMBOL_VAR = 25,                       /* VAR  */
  YYSYMBOL_TRY = 26,                       /* TRY  */
  YYSYMBOL_CATCH = 27,                     /* CATCH  */
  YYSYMBOL_FINALLY = 28,                   /* FINALLY  */
  YYSYMBOL_SIGNAL = 29,                    /* SIGNAL  */
  YYSYMBOL_BECAUSE = 30,                   /* BECAUSE  */
  YYSYMBOL_IF = 31,                        /* IF  */
  YYSYMBOL_ELSE = 32,                      /* ELSE  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_FOR = 34,                       /* FOR  */
  YYSYMBOL_WHEN = 35,                      /* WHEN  */
  YYSYMBOL_THEN = 36,                      /* THEN  */
  YYSYMBOL_NEW = 37,                       /* NEW  */
  YYSYMBOL_OR = 38,                        /* OR  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_NOT = 40,                       /* NOT  */
  YYSYMBOL_COPIES = 41,                    /* COPIES  */
  YYSYMBOL_REFS = 42,                      /* REFS  */
  YYSYMBOL_AS = 43,                        /* AS  */
  YYSYMBOL_LSHIFT = 44,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 45,                    /* RSHIFT  */
  YYSYMBOL_EQ = 46,                        /* EQ  */
  YYSYMBOL_NE = 47,                        /* NE  */
  YYSYMBOL_LE = 48,                        /* LE  */
  YYSYMBOL_GE = 49,                        /* GE  */
  YYSYMBOL_50_ = 50,                       /* '{'  */
  YYSYMBOL_51_ = 51,                       /* '}'  */
  YYSYMBOL_52_ = 52,                       /* '+'  */
  YYSYMBOL_53_ = 53,                       /* '-'  */
  YYSYMBOL_54_ = 54,                       /* '*'  */
  YYSYMBOL_55_ = 55,                       /* '/'  */
  YYSYMBOL_56_ = 56,                       /* '%'  */
  YYSYMBOL_57_ = 57,                       /* '~'  */
  YYSYMBOL_58_ = 58,                       /* '('  */
  YYSYMBOL_59_ = 59,                       /* ')'  */
  YYSYMBOL_60_ = 60,                       /* '^'  */
  YYSYMBOL_61_ = 61,                       /* '.'  */
  YYSYMBOL_62_ = 62,                       /* ','  */
  YYSYMBOL_63_ = 63,                       /* ';'  */
  YYSYMBOL_64_ = 64,                       /* '='  */
  YYSYMBOL_65_ = 65,                       /* '|'  */
  YYSYMBOL_66_ = 66,                       /* '&'  */
  YYSYMBOL_67_ = 67,                       /* '<'  */
  YYSYMBOL_68_ = 68,                       /* '>'  */
  YYSYMBOL_69_ = 69,                       /* '['  */
  YYSYMBOL_70_ = 70,                       /* ']'  */
  YYSYMBOL_71_ = 71,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_program = 73,                   /* program  */
  YYSYMBOL_import_stmt = 74,               /* import_stmt  */
  YYSYMBOL_module_path = 75,               /* module_path  */
  YYSYMBOL_module_path_upwards = 76,       /* module_path_upwards  */
  YYSYMBOL_module_path_compact = 77,       /* module_path_compact  */
  YYSYMBOL_export_stmt = 78,               /* export_stmt  */
  YYSYMBOL_export_item_list = 79,          /* export_item_list  */
  YYSYMBOL_export_item = 80,               /* export_item  */
  YYSYMBOL_global_variable_stmt = 81,      /* global_variable_stmt  */
  YYSYMBOL_identifier_item_list = 82,      /* identifier_item_list  */
  YYSYMBOL_function_stmt = 83,             /* function_stmt  */
  YYSYMBOL_parameter_list = 84,            /* parameter_list  */
  YYSYMBOL_parameter_item = 85,            /* parameter_item  */
  YYSYMBOL_type_stmt = 86,                 /* type_stmt  */
  YYSYMBOL_member_list = 87,               /* member_list  */
  YYSYMBOL_member_item = 88,               /* member_item  */
  YYSYMBOL_method_stmt = 89,               /* method_stmt  */
  YYSYMBOL_constructor_stmt = 90,          /* constructor_stmt  */
  YYSYMBOL_destructor_stmt = 91,           /* destructor_stmt  */
  YYSYMBOL_stmt = 92,                      /* stmt  */
  YYSYMBOL_block_stmt = 93,                /* block_stmt  */
  YYSYMBOL_stmt_list = 94,                 /* stmt_list  */
  YYSYMBOL_while_stmt = 95,                /* while_stmt  */
  YYSYMBOL_for_stmt = 96,                  /* for_stmt  */
  YYSYMBOL_if_stmt = 97,                   /* if_stmt  */
  YYSYMBOL_continue_stmt = 98,             /* continue_stmt  */
  YYSYMBOL_break_stmt = 99,                /* break_stmt  */
  YYSYMBOL_return_stmt = 100,              /* return_stmt  */
  YYSYMBOL_assignment_stmt = 101,          /* assignment_stmt  */
  YYSYMBOL_try_catch_stmt = 102,           /* try_catch_stmt  */
  YYSYMBOL_catch_item_list = 103,          /* catch_item_list  */
  YYSYMBOL_catch_item = 104,               /* catch_item  */
  YYSYMBOL_signal_stmt = 105,              /* signal_stmt  */
  YYSYMBOL_var_stmt = 106,                 /* var_stmt  */
  YYSYMBOL_assignment_item_list = 107,     /* assignment_item_list  */
  YYSYMBOL_assignment_item = 108,          /* assignment_item  */
  YYSYMBOL_expr = 109,                     /* expr  */
  YYSYMBOL_assignment = 110,               /* assignment  */
  YYSYMBOL_inline_if = 111,                /* inline_if  */
  YYSYMBOL_new = 112,                      /* new  */
  YYSYMBOL_logical_or = 113,               /* logical_or  */
  YYSYMBOL_logical_and = 114,              /* logical_and  */
  YYSYMBOL_bitwise_or = 115,               /* bitwise_or  */
  YYSYMBOL_bitwise_xor = 116,              /* bitwise_xor  */
  YYSYMBOL_bitwise_and = 117,              /* bitwise_and  */
  YYSYMBOL_equality = 118,                 /* equality  */
  YYSYMBOL_relational = 119,               /* relational  */
  YYSYMBOL_sum = 120,                      /* sum  */
  YYSYMBOL_bitwise_shift = 121,            /* bitwise_shift  */
  YYSYMBOL_term = 122,                     /* term  */
  YYSYMBOL_prefix_op = 123,                /* prefix_op  */
  YYSYMBOL_primary = 124,                  /* primary  */
  YYSYMBOL_elementary = 125,               /* elementary  */
  YYSYMBOL_literal = 126,                  /* literal  */
  YYSYMBOL_expr_list = 127                 /* expr_list  */
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
#define YYLAST   609

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  282

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


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
       2,     2,     2,     2,     2,     2,     2,    56,    66,     2,
      58,    59,    54,    52,    62,    53,    61,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    71,    63,
      67,    64,    68,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,    65,    51,    57,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   102,   106,   110,   114,   118,   122,   126,
     130,   134,   141,   147,   150,   153,   159,   162,   168,   171,
     177,   183,   186,   192,   198,   204,   207,   213,   216,   222,
     225,   231,   234,   237,   240,   246,   251,   254,   260,   263,
     269,   275,   278,   284,   290,   293,   296,   299,   302,   305,
     308,   311,   314,   317,   320,   323,   326,   332,   335,   341,
     344,   350,   356,   359,   362,   365,   368,   371,   374,   377,
     383,   386,   392,   398,   404,   407,   410,   413,   419,   422,
     428,   431,   434,   440,   443,   449,   455,   461,   467,   470,
     475,   478,   483,   489,   492,   498,   501,   507,   510,   513,
     519,   522,   528,   531,   537,   540,   546,   549,   555,   558,
     564,   567,   570,   576,   579,   582,   585,   588,   594,   597,
     600,   606,   609,   612,   618,   621,   624,   627,   633,   636,
     639,   642,   645,   651,   654,   657,   660,   663,   666,   672,
     675,   681,   684,   687,   690,   693,   696,   699,   705,   708
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
  "FUNCTION", "TYPE", "METHOD", "CONSTRUCTOR", "DESTRUCTOR", "OF", "COPY",
  "REF", "PASS", "CONTINUE", "BREAK", "RETURN", "VAR", "TRY", "CATCH",
  "FINALLY", "SIGNAL", "BECAUSE", "IF", "ELSE", "WHILE", "FOR", "WHEN",
  "THEN", "NEW", "OR", "AND", "NOT", "COPIES", "REFS", "AS", "LSHIFT",
  "RSHIFT", "EQ", "NE", "LE", "GE", "'{'", "'}'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'~'", "'('", "')'", "'^'", "'.'", "','", "';'", "'='",
  "'|'", "'&'", "'<'", "'>'", "'['", "']'", "':'", "$accept", "program",
  "import_stmt", "module_path", "module_path_upwards",
  "module_path_compact", "export_stmt", "export_item_list", "export_item",
  "global_variable_stmt", "identifier_item_list", "function_stmt",
  "parameter_list", "parameter_item", "type_stmt", "member_list",
  "member_item", "method_stmt", "constructor_stmt", "destructor_stmt",
  "stmt", "block_stmt", "stmt_list", "while_stmt", "for_stmt", "if_stmt",
  "continue_stmt", "break_stmt", "return_stmt", "assignment_stmt",
  "try_catch_stmt", "catch_item_list", "catch_item", "signal_stmt",
  "var_stmt", "assignment_item_list", "assignment_item", "expr",
  "assignment", "inline_if", "new", "logical_or", "logical_and",
  "bitwise_or", "bitwise_xor", "bitwise_and", "equality", "relational",
  "sum", "bitwise_shift", "term", "prefix_op", "primary", "elementary",
  "literal", "expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-173)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -173,   319,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
       8,   532,     4,     9,    28,    33,    -8,    16,  -173,  -173,
     513,    51,    19,   532,   532,   532,    39,    48,   551,   551,
     435,   551,   551,   551,   532,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,    12,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,    36,  -173,     2,  -173,    46,
      64,    49,    61,    56,    40,   -28,    37,    66,    26,  -173,
     -36,  -173,  -173,  -173,    62,    67,    83,   120,  -173,  -173,
      68,    88,    70,  -173,    75,    84,    77,   129,    52,   131,
     532,   532,   532,  -173,    78,  -173,    79,    85,   113,   473,
     473,   146,    81,   109,     0,  -173,  -173,   258,    96,  -173,
    -173,  -173,   105,  -173,   532,   532,   532,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   551,   357,   158,   532,   159,   120,
    -173,   162,  -173,   532,   163,     4,    11,   165,    52,    19,
    -173,   167,   169,   170,   121,   117,    19,  -173,  -173,  -173,
     532,    51,   532,   155,   156,   160,   532,   -14,    12,   473,
     122,   153,    48,   532,  -173,  -173,  -173,  -173,  -173,  -173,
      64,    49,    61,    56,    40,   -28,   -28,    37,    37,    37,
      37,    66,    66,    26,    26,  -173,  -173,  -173,  -173,   130,
     132,  -173,   124,  -173,  -173,  -173,  -173,  -173,  -173,    19,
     136,   138,   -38,  -173,   141,  -173,  -173,  -173,  -173,   179,
      52,  -173,  -173,  -173,   164,   171,   174,  -173,  -173,   473,
      12,   395,   473,   473,   139,   176,   154,   532,  -173,  -173,
    -173,    19,   161,  -173,   165,   194,   207,  -173,   209,   210,
     180,    12,    12,    12,   395,    12,   395,   473,    48,  -173,
    -173,  -173,  -173,  -173,   211,    19,    19,    19,   214,    12,
      12,    12,   395,  -173,    19,  -173,  -173,  -173,    19,    12,
    -173,  -173
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,     1,   142,   143,   144,   145,   146,   147,   141,
       0,     0,     0,     0,     0,     0,     0,     0,    72,    73,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    44,    92,    94,    96,    99,
     101,   103,   105,   107,   109,   112,   117,   120,   123,   127,
     132,   138,   140,    15,    19,    17,     0,     0,    14,    20,
      22,     0,    26,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    77,    91,    87,    89,     0,     0,     0,
       0,     0,     0,     0,    98,   130,    58,    60,     0,   128,
     129,   131,     0,    56,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      16,     0,    13,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,    30,     0,    74,    75,    76,
       0,     0,     0,     0,    82,    84,     0,    71,    61,     0,
       0,     0,     0,     0,    59,    57,   139,    78,    79,    93,
     100,   102,   104,   106,   108,   110,   111,   113,   114,   115,
     116,   118,   119,   121,   122,   124,   125,   126,   134,   149,
       0,   136,     0,   137,    18,    12,    21,    23,    25,     0,
       0,    39,     0,    37,     0,    42,    31,    32,    33,     0,
       0,    43,    90,    88,     0,     0,     0,    83,    86,     0,
      69,    44,     0,     0,     0,     0,     0,     0,   133,   135,
      28,     0,     0,    35,     0,     0,     0,    29,     0,     0,
       0,    70,    66,    67,    44,    68,    44,     0,     0,    97,
     148,    27,    38,    36,     0,     0,     0,     0,     0,    63,
      64,    65,    44,    95,     0,    41,    85,    81,     0,    62,
      40,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,  -173,  -173,   149,   -72,  -173,    82,  -173,  -173,
      92,  -173,  -137,  -173,  -173,  -173,   -18,  -173,  -173,  -173,
      -1,   -20,   126,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,    73,  -173,  -173,  -173,    80,  -173,     3,   111,  -173,
     -24,   201,   125,   133,   140,   119,   123,    -7,   -63,    -9,
      -6,   -25,  -173,  -173,  -173,  -172
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    35,    76,    77,    78,    36,    79,    80,    37,
      83,    38,   154,   155,    39,   212,   213,    40,    41,    42,
     107,    44,   108,    45,    46,    47,    48,    49,    50,    51,
      52,   164,   165,    53,    54,    95,    96,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,   200
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   236,    97,   103,   105,   142,   109,   110,   111,   210,
      87,   214,    82,   243,    81,    73,    74,    84,   229,   150,
     124,   125,   135,    93,   244,   136,    98,    99,   100,   102,
     151,   152,   153,   137,    89,   138,    85,   112,   117,   126,
     127,    86,     3,     4,     5,     6,     7,     8,     9,   113,
      88,     3,     4,     5,     6,     7,     8,     9,   173,    94,
     150,   187,   188,   189,   190,   260,   116,   204,    75,    30,
     209,   151,   152,   153,    27,   113,    28,   114,   115,    29,
     132,   133,   134,   247,   117,    28,   122,   123,    29,   128,
     129,    31,    32,   157,   158,   159,    33,    34,   167,   168,
      31,    32,   101,   118,   170,    33,    34,   195,   196,   197,
     130,   131,   162,   163,   119,   185,   186,   177,   178,   191,
     192,   120,   121,   139,   193,   194,   141,    75,    74,   215,
     143,   144,   145,   146,   147,   148,   221,   149,   199,   156,
     202,   161,   160,   166,   171,   172,    81,   175,   235,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,   222,   176,   224,   201,   203,   230,   228,
     205,   207,   231,   211,   234,   216,   199,   217,   218,   220,
     219,    27,   225,    28,   226,   232,    29,   162,    27,   240,
      28,   238,   237,    29,   239,   241,   242,   246,    31,    32,
     245,   250,   257,    33,    34,    31,    32,   248,   258,   169,
      33,    34,   264,   259,   249,   265,   233,   266,   267,   274,
     262,   261,   278,   268,   140,   206,   263,   179,   251,   104,
     252,   253,   255,   174,   273,   254,   256,   208,   227,   183,
     199,   223,   180,     0,   184,   275,   276,   277,     0,     0,
       0,   181,     0,   269,   280,   270,   271,     0,   281,   182,
     272,     3,     4,     5,     6,     7,     8,     9,     0,     0,
       0,   279,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    19,    20,    21,    22,     0,     0,    23,     0,    24,
       0,    25,    26,    27,     0,    28,     0,     0,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,     0,
      31,    32,     0,     0,     0,    33,    34,     0,     0,     2,
       0,   113,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,    18,    19,    20,    21,    22,     0,     0,    23,     0,
      24,     0,    25,    26,    27,     0,    28,     0,     0,    29,
       3,     4,     5,     6,     7,     8,     9,     0,     0,    30,
       0,    31,    32,     0,     0,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,    28,     0,     0,    29,     3,     4,
       5,     6,     7,     8,     9,     0,     0,     0,     0,    31,
      32,     0,     0,     0,    33,    34,   198,    18,    19,    20,
      21,    22,     0,     0,    23,     0,    24,     0,    25,    26,
      27,     0,    28,     0,     0,    29,   114,   115,     3,     4,
       5,     6,     7,     8,     9,    30,     0,    31,    32,     0,
       0,     0,    33,    34,     0,     0,     0,    18,    19,    20,
      21,    22,     0,     0,    23,     0,    24,     0,    25,    26,
      27,     0,    28,     0,     0,    29,     3,     4,     5,     6,
       7,     8,     9,     0,     0,    30,   106,    31,    32,     0,
       0,     0,    33,    34,     0,    18,    19,    20,    21,    22,
       0,     0,    23,     0,    24,     0,    25,    26,    27,     0,
      28,     0,     0,    29,     0,     0,     3,     4,     5,     6,
       7,     8,     9,    30,     0,    31,    32,     0,     0,     0,
      33,    34,    90,    91,    92,     3,     4,     5,     6,     7,
       8,     9,     0,     0,     0,     0,     0,     0,    27,     0,
      28,     0,     0,    29,     3,     4,     5,     6,     7,     8,
       9,     0,     0,     0,     0,    31,    32,    27,     0,    28,
      33,    34,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,     0,     0,     0,    33,
      34,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,     0,     0,    33,    34
};

static const yytype_int16 yycheck[] =
{
       1,   173,    22,    27,    29,    77,    31,    32,    33,   146,
      18,   148,     8,    51,    11,     7,     8,     8,    32,     8,
      48,    49,    58,    20,    62,    61,    23,    24,    25,    26,
      19,    20,    21,    69,    18,    71,     8,    34,    38,    67,
      68,     8,     3,     4,     5,     6,     7,     8,     9,    63,
      58,     3,     4,     5,     6,     7,     8,     9,    58,     8,
       8,   124,   125,   126,   127,   237,    64,   139,    60,    50,
      59,    19,    20,    21,    35,    63,    37,    41,    42,    40,
      54,    55,    56,   220,    38,    37,    46,    47,    40,    52,
      53,    52,    53,    90,    91,    92,    57,    58,    99,   100,
      52,    53,    63,    39,   101,    57,    58,   132,   133,   134,
      44,    45,    27,    28,    65,   122,   123,   114,   115,   128,
     129,    60,    66,    61,   130,   131,    43,    60,     8,   149,
      62,    43,    62,    58,    50,    58,   156,     8,   135,     8,
     137,    62,    64,    30,    63,    36,   143,    51,   172,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
       7,     8,     9,   160,    59,   162,     8,     8,   169,   166,
       8,     8,   169,     8,   171,     8,   173,     8,     8,    62,
      59,    35,    27,    37,    28,    63,    40,    27,    35,   209,
      37,    59,    62,    40,    70,    59,    58,    18,    52,    53,
      59,    27,    63,    57,    58,    52,    53,    43,    32,    63,
      57,    58,    18,    59,    43,     8,    63,     8,     8,     8,
      59,   241,     8,    43,    75,   143,   244,   116,   229,    28,
     231,   232,   233,   107,   258,   232,   233,   145,   165,   120,
     237,   161,   117,    -1,   121,   265,   266,   267,    -1,    -1,
      -1,   118,    -1,   254,   274,   256,   257,    -1,   278,   119,
     257,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      -1,   272,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    26,    -1,    -1,    29,    -1,    31,
      -1,    33,    34,    35,    -1,    37,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,     0,
      -1,    63,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    -1,    -1,    29,    -1,
      31,    -1,    33,    34,    35,    -1,    37,    -1,    -1,    40,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    50,
      -1,    52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    37,    -1,    -1,    40,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    52,
      53,    -1,    -1,    -1,    57,    58,    59,    22,    23,    24,
      25,    26,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      35,    -1,    37,    -1,    -1,    40,    41,    42,     3,     4,
       5,     6,     7,     8,     9,    50,    -1,    52,    53,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      35,    -1,    37,    -1,    -1,    40,     3,     4,     5,     6,
       7,     8,     9,    -1,    -1,    50,    51,    52,    53,    -1,
      -1,    -1,    57,    58,    -1,    22,    23,    24,    25,    26,
      -1,    -1,    29,    -1,    31,    -1,    33,    34,    35,    -1,
      37,    -1,    -1,    40,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    50,    -1,    52,    53,    -1,    -1,    -1,
      57,    58,    19,    20,    21,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      37,    -1,    -1,    40,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    -1,    -1,    52,    53,    35,    -1,    37,
      57,    58,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,
      58,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    73,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    22,    23,
      24,    25,    26,    29,    31,    33,    34,    35,    37,    40,
      50,    52,    53,    57,    58,    74,    78,    81,    83,    86,
      89,    90,    91,    92,    93,    95,    96,    97,    98,    99,
     100,   101,   102,   105,   106,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,     7,     8,    60,    75,    76,    77,    79,
      80,   109,     8,    82,     8,     8,     8,    18,    58,    18,
      19,    20,    21,   109,     8,   107,   108,    93,   109,   109,
     109,    63,   109,   112,   113,   123,    51,    92,    94,   123,
     123,   123,   109,    63,    41,    42,    64,    38,    39,    65,
      60,    66,    46,    47,    48,    49,    67,    68,    52,    53,
      44,    45,    54,    55,    56,    58,    61,    69,    71,    61,
      76,    43,    77,    62,    43,    62,    58,    50,    58,     8,
       8,    19,    20,    21,    84,    85,     8,   109,   109,   109,
      64,    62,    27,    28,   103,   104,    30,    92,    92,    63,
     109,    63,    36,    58,    94,    51,    59,   109,   109,   110,
     114,   115,   116,   117,   118,   119,   119,   120,   120,   120,
     120,   121,   121,   122,   122,   123,   123,   123,    59,   109,
     127,     8,   109,     8,    77,     8,    79,     8,    82,    59,
      84,     8,    87,    88,    84,    93,     8,     8,     8,    59,
      62,    93,   109,   107,   109,    27,    28,   103,   109,    32,
      92,   109,    63,    63,   109,   112,   127,    62,    59,    70,
      93,    59,    58,    51,    62,    59,    18,    84,    43,    43,
      27,    92,    92,    92,   109,    92,   109,    63,    32,    59,
     127,    93,    59,    88,    18,     8,     8,     8,    43,    92,
      92,    92,   109,   112,     8,    93,    93,    93,     8,    92,
      93,    93
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    75,    75,    75,    76,    76,    77,    77,
      78,    79,    79,    80,    81,    82,    82,    83,    83,    84,
      84,    85,    85,    85,    85,    86,    87,    87,    88,    88,
      89,    90,    90,    91,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    93,    93,    94,
      94,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      97,    97,    98,    99,   100,   100,   100,   100,   101,   101,
     102,   102,   102,   103,   103,   104,   105,   106,   107,   107,
     108,   108,   109,   110,   110,   111,   111,   112,   112,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   117,   117,
     118,   118,   118,   119,   119,   119,   119,   119,   120,   120,
     120,   121,   121,   121,   122,   122,   122,   122,   123,   123,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   125,
     125,   126,   126,   126,   126,   126,   126,   126,   127,   127
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     0,     4,     2,     1,     1,     2,     1,     3,     1,
       2,     3,     1,     3,     2,     3,     1,     6,     5,     3,
       1,     2,     2,     2,     1,     5,     3,     1,     3,     1,
       8,     7,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     2,     2,
       1,     3,     7,     6,     6,     6,     5,     5,     5,     4,
       5,     3,     1,     1,     3,     3,     3,     2,     3,     3,
       8,     7,     3,     2,     1,     5,     4,     2,     3,     1,
       3,     1,     1,     3,     1,     6,     1,     5,     2,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       2,     2,     1,     4,     3,     4,     3,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1
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
#line 98 "rules.y"
                        {
        (yyval.node) = make(PROGRAM_NODE, IMPORT_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1735 "rules.tab.c"
    break;

  case 3: /* program: program export_stmt  */
#line 102 "rules.y"
                          {
        (yyval.node) = make(PROGRAM_NODE, EXPORT_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1744 "rules.tab.c"
    break;

  case 4: /* program: program global_variable_stmt  */
#line 106 "rules.y"
                                   {
        (yyval.node) = make(PROGRAM_NODE, GLOBAL_VARIABLE_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1753 "rules.tab.c"
    break;

  case 5: /* program: program function_stmt  */
#line 110 "rules.y"
                            {
        (yyval.node) = make(PROGRAM_NODE, FUNCTION_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1762 "rules.tab.c"
    break;

  case 6: /* program: program type_stmt  */
#line 114 "rules.y"
                        {
        (yyval.node) = make(PROGRAM_NODE, TYPE_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1771 "rules.tab.c"
    break;

  case 7: /* program: program method_stmt  */
#line 118 "rules.y"
                          {
        (yyval.node) = make(PROGRAM_NODE, METHOD_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1780 "rules.tab.c"
    break;

  case 8: /* program: program constructor_stmt  */
#line 122 "rules.y"
                               {
        (yyval.node) = make(PROGRAM_NODE, CONSTRUCTOR_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1789 "rules.tab.c"
    break;

  case 9: /* program: program destructor_stmt  */
#line 126 "rules.y"
                              {
        (yyval.node) = make(PROGRAM_NODE, DESTRUCTOR_STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1798 "rules.tab.c"
    break;

  case 10: /* program: program stmt  */
#line 130 "rules.y"
                   {
        (yyval.node) = make(PROGRAM_NODE, STMT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
        node_result = (yyval.node);
    }
#line 1807 "rules.tab.c"
    break;

  case 11: /* program: %empty  */
#line 134 "rules.y"
      {
        (yyval.node) = make(PROGRAM_NODE, NO_OPTION, 1, 0);
        node_result = (yyval.node);
    }
#line 1816 "rules.tab.c"
    break;

  case 12: /* import_stmt: IMPORT module_path AS IDENTIFIER  */
#line 141 "rules.y"
                                     {
        (yyval.node) = make(IMPORT_STMT_NODE, DEFAULT_OPTION, (yyvsp[-3].num), 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1824 "rules.tab.c"
    break;

  case 13: /* module_path: module_path_upwards module_path_compact  */
#line 147 "rules.y"
                                            {
        (yyval.node) = make(MODULE_PATH_NODE, MODULE_PATH_COMPACT_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1832 "rules.tab.c"
    break;

  case 14: /* module_path: module_path_compact  */
#line 150 "rules.y"
                          {
        (yyval.node) = make(MODULE_PATH_NODE, MODULE_PATH_COMPACT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1840 "rules.tab.c"
    break;

  case 15: /* module_path: STRING  */
#line 153 "rules.y"
             {
        (yyval.node) = make(MODULE_PATH_NODE, MODULE_PATH_STRING_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1848 "rules.tab.c"
    break;

  case 16: /* module_path_upwards: '^' module_path_upwards  */
#line 159 "rules.y"
                            {
        (yyval.node) = make(MODULE_PATH_UPWARDS_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1856 "rules.tab.c"
    break;

  case 17: /* module_path_upwards: '^'  */
#line 162 "rules.y"
          {
        (yyval.node) = make(MODULE_PATH_UPWARDS_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].num), 0);
    }
#line 1864 "rules.tab.c"
    break;

  case 18: /* module_path_compact: IDENTIFIER '.' module_path_compact  */
#line 168 "rules.y"
                                       {
        (yyval.node) = make(MODULE_PATH_COMPACT_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1872 "rules.tab.c"
    break;

  case 19: /* module_path_compact: IDENTIFIER  */
#line 171 "rules.y"
                 {
        (yyval.node) = make(MODULE_PATH_COMPACT_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1880 "rules.tab.c"
    break;

  case 20: /* export_stmt: EXPORT export_item_list  */
#line 177 "rules.y"
                            {
        (yyval.node) = make(EXPORT_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1888 "rules.tab.c"
    break;

  case 21: /* export_item_list: export_item ',' export_item_list  */
#line 183 "rules.y"
                                     {
        (yyval.node) = make(EXPORT_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1896 "rules.tab.c"
    break;

  case 22: /* export_item_list: export_item  */
#line 186 "rules.y"
                  {
        (yyval.node) = make(EXPORT_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1904 "rules.tab.c"
    break;

  case 23: /* export_item: expr AS IDENTIFIER  */
#line 192 "rules.y"
                       {
        (yyval.node) = make(EXPORT_ITEM_LIST_NODE, DEFAULT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1912 "rules.tab.c"
    break;

  case 24: /* global_variable_stmt: GLOBAL identifier_item_list  */
#line 198 "rules.y"
                                {
        (yyval.node) = make(GLOBAL_VARIABLE_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1920 "rules.tab.c"
    break;

  case 25: /* identifier_item_list: IDENTIFIER ',' identifier_item_list  */
#line 204 "rules.y"
                                        {
        (yyval.node) = make(IDENTIFIER_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1928 "rules.tab.c"
    break;

  case 26: /* identifier_item_list: IDENTIFIER  */
#line 207 "rules.y"
                 {
        (yyval.node) = make(IDENTIFIER_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1936 "rules.tab.c"
    break;

  case 27: /* function_stmt: FUNCTION IDENTIFIER '(' parameter_list ')' block_stmt  */
#line 213 "rules.y"
                                                          {
        (yyval.node) = make(FUNCTION_STMT_NODE, FUNCTION_STMT_OPTION, (yyvsp[-5].num), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1944 "rules.tab.c"
    break;

  case 28: /* function_stmt: FUNCTION IDENTIFIER '(' ')' block_stmt  */
#line 216 "rules.y"
                                             {
        (yyval.node) = make(FUNCTION_STMT_NODE, FUNCTION_STMT_OPTION, (yyvsp[-4].num), 2, (yyvsp[-3].node), (yyvsp[0].node));
    }
#line 1952 "rules.tab.c"
    break;

  case 29: /* parameter_list: parameter_item ',' parameter_list  */
#line 222 "rules.y"
                                      {
        (yyval.node) = make(PARAMETER_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1960 "rules.tab.c"
    break;

  case 30: /* parameter_list: parameter_item  */
#line 225 "rules.y"
                     {
        (yyval.node) = make(PARAMETER_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 1968 "rules.tab.c"
    break;

  case 31: /* parameter_item: COPY IDENTIFIER  */
#line 231 "rules.y"
                    {
        (yyval.node) = make(PARAMETER_ITEM_NODE, PARAM_COPY_MODE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1976 "rules.tab.c"
    break;

  case 32: /* parameter_item: REF IDENTIFIER  */
#line 234 "rules.y"
                     {
        (yyval.node) = make(PARAMETER_ITEM_NODE, PARAM_REF_MODE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1984 "rules.tab.c"
    break;

  case 33: /* parameter_item: PASS IDENTIFIER  */
#line 237 "rules.y"
                      {
        (yyval.node) = make(PARAMETER_ITEM_NODE, PARAM_PASS_MODE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 1992 "rules.tab.c"
    break;

  case 34: /* parameter_item: IDENTIFIER  */
#line 240 "rules.y"
                 {
        (yyval.node) = make(PARAMETER_ITEM_NODE, PARAM_AUTO_MODE_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2000 "rules.tab.c"
    break;

  case 35: /* type_stmt: TYPE IDENTIFIER '{' member_list '}'  */
#line 246 "rules.y"
                                         {
        (yyval.node) = make(TYPE_STMT_NODE, DEFAULT_OPTION, (yyvsp[-4].num), 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2008 "rules.tab.c"
    break;

  case 36: /* member_list: member_list ',' member_item  */
#line 251 "rules.y"
                                {
        (yyval.node) = make(MEMBER_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2016 "rules.tab.c"
    break;

  case 37: /* member_list: member_item  */
#line 254 "rules.y"
                  {
        (yyval.node) = make(MEMBER_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2024 "rules.tab.c"
    break;

  case 38: /* member_item: IDENTIFIER '(' ')'  */
#line 260 "rules.y"
                       {
        (yyval.node) = make(MEMBER_ITEM_NODE, MEMBER_METHOD_OPTION, (yyvsp[-2].node)->lineno, 1, (yyvsp[-2].node));
    }
#line 2032 "rules.tab.c"
    break;

  case 39: /* member_item: IDENTIFIER  */
#line 263 "rules.y"
                 {
        (yyval.node) = make(MEMBER_ITEM_NODE, MEMBER_FIELD_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2040 "rules.tab.c"
    break;

  case 40: /* method_stmt: METHOD IDENTIFIER '(' parameter_list ')' OF IDENTIFIER block_stmt  */
#line 269 "rules.y"
                                                                      {
        (yyval.node) = make(METHOD_STMT_NODE, DEFAULT_OPTION, (yyvsp[-7].num), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2048 "rules.tab.c"
    break;

  case 41: /* constructor_stmt: CONSTRUCTOR '(' parameter_list ')' OF IDENTIFIER block_stmt  */
#line 275 "rules.y"
                                                                {
        (yyval.node) = make(CONSTRUCTOR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-6].num), 3, (yyvsp[-4].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2056 "rules.tab.c"
    break;

  case 42: /* constructor_stmt: CONSTRUCTOR OF IDENTIFIER block_stmt  */
#line 278 "rules.y"
                                           {
        (yyval.node) = make(CONSTRUCTOR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-3].num), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2064 "rules.tab.c"
    break;

  case 43: /* destructor_stmt: DESTRUCTOR OF IDENTIFIER block_stmt  */
#line 284 "rules.y"
                                        {
        (yyval.node) = make(DESTRUCTOR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-3].num), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2072 "rules.tab.c"
    break;

  case 44: /* stmt: expr  */
#line 290 "rules.y"
         {
        (yyval.node) = make(STMT_NODE, EXPR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2080 "rules.tab.c"
    break;

  case 45: /* stmt: block_stmt  */
#line 293 "rules.y"
                 {
        (yyval.node) = make(STMT_NODE, BLOCK_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2088 "rules.tab.c"
    break;

  case 46: /* stmt: while_stmt  */
#line 296 "rules.y"
                 {
        (yyval.node) = make(STMT_NODE, WHILE_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2096 "rules.tab.c"
    break;

  case 47: /* stmt: for_stmt  */
#line 299 "rules.y"
               {
        (yyval.node) = make(STMT_NODE, FOR_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2104 "rules.tab.c"
    break;

  case 48: /* stmt: if_stmt  */
#line 302 "rules.y"
              {
        (yyval.node) = make(STMT_NODE, IF_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2112 "rules.tab.c"
    break;

  case 49: /* stmt: continue_stmt  */
#line 305 "rules.y"
                    {
        (yyval.node) = make(STMT_NODE, CONTINUE_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2120 "rules.tab.c"
    break;

  case 50: /* stmt: break_stmt  */
#line 308 "rules.y"
                 {
        (yyval.node) = make(STMT_NODE, BREAK_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2128 "rules.tab.c"
    break;

  case 51: /* stmt: return_stmt  */
#line 311 "rules.y"
                  {
        (yyval.node) = make(STMT_NODE, RETURN_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2136 "rules.tab.c"
    break;

  case 52: /* stmt: assignment_stmt  */
#line 314 "rules.y"
                      {
        (yyval.node) = make(STMT_NODE, ASSIGNMENT_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2144 "rules.tab.c"
    break;

  case 53: /* stmt: try_catch_stmt  */
#line 317 "rules.y"
                     {
        (yyval.node) = make(STMT_NODE, TRY_CATCH_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2152 "rules.tab.c"
    break;

  case 54: /* stmt: signal_stmt  */
#line 320 "rules.y"
                  {
        (yyval.node) = make(STMT_NODE, SIGNAL_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2160 "rules.tab.c"
    break;

  case 55: /* stmt: var_stmt  */
#line 323 "rules.y"
               {
        (yyval.node) = make(STMT_NODE, VAR_STMT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2168 "rules.tab.c"
    break;

  case 56: /* stmt: stmt ';'  */
#line 326 "rules.y"
               {
        (yyval.node) = make(STMT_NODE, STMT_OPTION, (yyvsp[-1].node)->lineno, 1, (yyvsp[-1].node));
    }
#line 2176 "rules.tab.c"
    break;

  case 57: /* block_stmt: '{' stmt_list '}'  */
#line 332 "rules.y"
                      {
        (yyval.node) = make(BLOCK_STMT_NODE, DEFAULT_OPTION, (yyvsp[-2].num), 1, (yyvsp[-1].node));
    }
#line 2184 "rules.tab.c"
    break;

  case 58: /* block_stmt: '{' '}'  */
#line 335 "rules.y"
              {
        (yyval.node) = make(BLOCK_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 0);
    }
#line 2192 "rules.tab.c"
    break;

  case 59: /* stmt_list: stmt stmt_list  */
#line 341 "rules.y"
                   {
        (yyval.node) = make(STMT_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2200 "rules.tab.c"
    break;

  case 60: /* stmt_list: stmt  */
#line 344 "rules.y"
           {
        (yyval.node) = make(STMT_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2208 "rules.tab.c"
    break;

  case 61: /* while_stmt: WHILE expr stmt  */
#line 350 "rules.y"
                    {
        (yyval.node) = make(WHILE_STMT_NODE, DEFAULT_OPTION, (yyvsp[-2].num), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2216 "rules.tab.c"
    break;

  case 62: /* for_stmt: FOR expr ';' expr ';' expr stmt  */
#line 356 "rules.y"
                                    {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_COND_POST_OPTION, (yyvsp[-6].num), 4, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2224 "rules.tab.c"
    break;

  case 63: /* for_stmt: FOR ';' expr ';' expr stmt  */
#line 359 "rules.y"
                                 {
        (yyval.node) = make(FOR_STMT_NODE, FOR_COND_POST_OPTION, (yyvsp[-5].num), 4, NULL, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2232 "rules.tab.c"
    break;

  case 64: /* for_stmt: FOR expr ';' ';' expr stmt  */
#line 362 "rules.y"
                                 {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_POST_OPTION, (yyvsp[-5].num), 4, (yyvsp[-4].node), NULL, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2240 "rules.tab.c"
    break;

  case 65: /* for_stmt: FOR expr ';' expr ';' stmt  */
#line 365 "rules.y"
                                 {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_COND_OPTION, (yyvsp[-5].num), 4, (yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node));
    }
#line 2248 "rules.tab.c"
    break;

  case 66: /* for_stmt: FOR ';' ';' expr stmt  */
#line 368 "rules.y"
                            {
        (yyval.node) = make(FOR_STMT_NODE, FOR_POST_OPTION, (yyvsp[-4].num), 4, NULL, NULL, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2256 "rules.tab.c"
    break;

  case 67: /* for_stmt: FOR ';' expr ';' stmt  */
#line 371 "rules.y"
                            {
        (yyval.node) = make(FOR_STMT_NODE, FOR_COND_OPTION, (yyvsp[-4].num), 4, NULL, (yyvsp[-2].node), NULL, (yyvsp[0].node));
    }
#line 2264 "rules.tab.c"
    break;

  case 68: /* for_stmt: FOR expr ';' ';' stmt  */
#line 374 "rules.y"
                            {
        (yyval.node) = make(FOR_STMT_NODE, FOR_INIT_OPTION, (yyvsp[-4].num), 4, (yyvsp[-3].node), NULL, NULL, (yyvsp[0].node));
    }
#line 2272 "rules.tab.c"
    break;

  case 69: /* for_stmt: FOR ';' ';' stmt  */
#line 377 "rules.y"
                       {
        (yyval.node) = make(FOR_STMT_NODE, FOR_NOTHING_OPTION, (yyvsp[-3].num), 4, NULL, NULL, NULL, (yyvsp[0].node));
    }
#line 2280 "rules.tab.c"
    break;

  case 70: /* if_stmt: IF expr stmt ELSE stmt  */
#line 383 "rules.y"
                           {
        (yyval.node) = make(IF_STMT_NODE, IF_WITH_ELSE_OPTION, (yyvsp[-4].num), 3, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2288 "rules.tab.c"
    break;

  case 71: /* if_stmt: IF expr stmt  */
#line 386 "rules.y"
                   {
        (yyval.node) = make(IF_STMT_NODE, IF_WITHOUT_ELSE_OPTION, (yyvsp[-2].num), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2296 "rules.tab.c"
    break;

  case 72: /* continue_stmt: CONTINUE  */
#line 392 "rules.y"
             {
        (yyval.node) = make(CONTINUE_STMT_NODE, DEFAULT_OPTION, (yyvsp[0].num), 0);
    }
#line 2304 "rules.tab.c"
    break;

  case 73: /* break_stmt: BREAK  */
#line 398 "rules.y"
          {
        (yyval.node) = make(BREAK_STMT_NODE, DEFAULT_OPTION, (yyvsp[0].num), 0);
    }
#line 2312 "rules.tab.c"
    break;

  case 74: /* return_stmt: RETURN COPY expr  */
#line 404 "rules.y"
                     {
        (yyval.node) = make(RETURN_STMT_NODE, RETURN_COPY_MODE_OPTION, (yyvsp[-2].num), 1, (yyvsp[0].node));
    }
#line 2320 "rules.tab.c"
    break;

  case 75: /* return_stmt: RETURN REF expr  */
#line 407 "rules.y"
                      {
        (yyval.node) = make(RETURN_STMT_NODE, RETURN_REF_MODE_OPTION, (yyvsp[-2].num), 1, (yyvsp[0].node));
    }
#line 2328 "rules.tab.c"
    break;

  case 76: /* return_stmt: RETURN PASS expr  */
#line 410 "rules.y"
                       {
        (yyval.node) = make(RETURN_STMT_NODE, RETURN_PASS_MODE_OPTION, (yyvsp[-2].num), 1, (yyvsp[0].node));
    }
#line 2336 "rules.tab.c"
    break;

  case 77: /* return_stmt: RETURN expr  */
#line 413 "rules.y"
                  {
        (yyval.node) = make(RETURN_STMT_NODE, RETURN_AUTO_MODE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2344 "rules.tab.c"
    break;

  case 78: /* assignment_stmt: expr COPIES expr  */
#line 419 "rules.y"
                     {
        (yyval.node) = make(ASSIGNMENT_STMT_NODE, ASSIGNMENT_COPIES_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2352 "rules.tab.c"
    break;

  case 79: /* assignment_stmt: expr REFS expr  */
#line 422 "rules.y"
                     {
        (yyval.node) = make(ASSIGNMENT_STMT_NODE, ASSIGNMENT_REFS_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2360 "rules.tab.c"
    break;

  case 80: /* try_catch_stmt: TRY block_stmt catch_item_list FINALLY CATCH AS IDENTIFIER block_stmt  */
#line 428 "rules.y"
                                                                          {
        (yyval.node) = make(TRY_CATCH_STMT_NODE, TRY_CATCH_FULL_OPTION, (yyvsp[-7].num), 4, (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2368 "rules.tab.c"
    break;

  case 81: /* try_catch_stmt: TRY block_stmt FINALLY CATCH AS IDENTIFIER block_stmt  */
#line 431 "rules.y"
                                                            {
        (yyval.node) = make(TRY_CATCH_STMT_NODE, TRY_CATCH_ONLY_UNIVERSAL_OPTION, (yyvsp[-6].num), 3, (yyvsp[-5].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2376 "rules.tab.c"
    break;

  case 82: /* try_catch_stmt: TRY block_stmt catch_item_list  */
#line 434 "rules.y"
                                     {
        (yyval.node) = make(TRY_CATCH_STMT_NODE, TRY_CATCH_ONLY_SPECIFIC_OPTION, (yyvsp[-2].num), 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2384 "rules.tab.c"
    break;

  case 83: /* catch_item_list: catch_item catch_item_list  */
#line 440 "rules.y"
                               {
        (yyval.node) = make(CATCH_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-1].node)->lineno, 2, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2392 "rules.tab.c"
    break;

  case 84: /* catch_item_list: catch_item  */
#line 443 "rules.y"
                 {
        (yyval.node) = make(CATCH_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2400 "rules.tab.c"
    break;

  case 85: /* catch_item: CATCH expr AS IDENTIFIER block_stmt  */
#line 449 "rules.y"
                                        {
        (yyval.node) = make(CATCH_ITEM_NODE, DEFAULT_OPTION, (yyvsp[-4].num), 3, (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2408 "rules.tab.c"
    break;

  case 86: /* signal_stmt: SIGNAL expr BECAUSE expr  */
#line 455 "rules.y"
                             {
        (yyval.node) = make(SIGNAL_STMT_NODE, DEFAULT_OPTION, (yyvsp[-3].num), 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2416 "rules.tab.c"
    break;

  case 87: /* var_stmt: VAR assignment_item_list  */
#line 461 "rules.y"
                             {
        (yyval.node) = make(VAR_STMT_NODE, DEFAULT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2424 "rules.tab.c"
    break;

  case 88: /* assignment_item_list: assignment_item ',' assignment_item_list  */
#line 467 "rules.y"
                                             {
        (yyval.node) = make(ASSIGNMENT_ITEM_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2432 "rules.tab.c"
    break;

  case 89: /* assignment_item_list: assignment_item  */
#line 470 "rules.y"
                      {
        (yyval.node) = make(ASSIGNMENT_ITEM_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2440 "rules.tab.c"
    break;

  case 90: /* assignment_item: IDENTIFIER '=' expr  */
#line 475 "rules.y"
                        {
        (yyval.node) = make(ASSIGNMENT_ITEM_NODE, ASSIGNMENT_ITEM_FULL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2448 "rules.tab.c"
    break;

  case 91: /* assignment_item: IDENTIFIER  */
#line 478 "rules.y"
                 {
        (yyval.node) = make(ASSIGNMENT_ITEM_NODE, ASSIGNMENT_ITEM_NAME_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2456 "rules.tab.c"
    break;

  case 92: /* expr: assignment  */
#line 483 "rules.y"
               {
        (yyval.node) = make(EXPR_NODE, DEFAULT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2464 "rules.tab.c"
    break;

  case 93: /* assignment: inline_if '=' assignment  */
#line 489 "rules.y"
                             {
        (yyval.node) = make(ASSIGNMENT_NODE, ASSIGNMENT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2472 "rules.tab.c"
    break;

  case 94: /* assignment: inline_if  */
#line 492 "rules.y"
                {
        (yyval.node) = make(ASSIGNMENT_NODE, INLINE_IF_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2480 "rules.tab.c"
    break;

  case 95: /* inline_if: WHEN new THEN new ELSE new  */
#line 498 "rules.y"
                               {
        (yyval.node) = make(INLINE_IF_NODE, INLINE_IF_OPTION, (yyvsp[-5].num), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2488 "rules.tab.c"
    break;

  case 96: /* inline_if: new  */
#line 501 "rules.y"
          {
        (yyval.node) = make(INLINE_IF_NODE, NEW_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2496 "rules.tab.c"
    break;

  case 97: /* new: NEW logical_or '(' expr_list ')'  */
#line 507 "rules.y"
                                     {
        (yyval.node) = make(NEW_NODE, NEW_OPTION, (yyvsp[-4].num), 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2504 "rules.tab.c"
    break;

  case 98: /* new: NEW logical_or  */
#line 510 "rules.y"
                     {
        (yyval.node) = make(NEW_NODE, NEW_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2512 "rules.tab.c"
    break;

  case 99: /* new: logical_or  */
#line 513 "rules.y"
                 {
        (yyval.node) = make(NEW_NODE, LOGICAL_OR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2520 "rules.tab.c"
    break;

  case 100: /* logical_or: logical_or OR logical_and  */
#line 519 "rules.y"
                              {
        (yyval.node) = make(LOGICAL_OR_NODE, LOGICAL_OR_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2528 "rules.tab.c"
    break;

  case 101: /* logical_or: logical_and  */
#line 522 "rules.y"
                  {
        (yyval.node) = make(LOGICAL_OR_NODE, LOGICAL_AND_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2536 "rules.tab.c"
    break;

  case 102: /* logical_and: logical_and AND bitwise_or  */
#line 528 "rules.y"
                               {
        (yyval.node) = make(LOGICAL_AND_NODE, LOGICAL_AND_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2544 "rules.tab.c"
    break;

  case 103: /* logical_and: bitwise_or  */
#line 531 "rules.y"
                 {
        (yyval.node) = make(LOGICAL_AND_NODE, BITWISE_OR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2552 "rules.tab.c"
    break;

  case 104: /* bitwise_or: bitwise_or '|' bitwise_xor  */
#line 537 "rules.y"
                               {
        (yyval.node) = make(BITWISE_OR_NODE, BITWISE_OR_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2560 "rules.tab.c"
    break;

  case 105: /* bitwise_or: bitwise_xor  */
#line 540 "rules.y"
                  {
        (yyval.node) = make(BITWISE_OR_NODE, BITWISE_XOR_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2568 "rules.tab.c"
    break;

  case 106: /* bitwise_xor: bitwise_xor '^' bitwise_and  */
#line 546 "rules.y"
                                {
        (yyval.node) = make(BITWISE_XOR_NODE, BITWISE_XOR_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2576 "rules.tab.c"
    break;

  case 107: /* bitwise_xor: bitwise_and  */
#line 549 "rules.y"
                  {
        (yyval.node) = make(BITWISE_XOR_NODE, BITWISE_AND_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2584 "rules.tab.c"
    break;

  case 108: /* bitwise_and: bitwise_and '&' equality  */
#line 555 "rules.y"
                             {
        (yyval.node) = make(BITWISE_AND_NODE, BITWISE_AND_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2592 "rules.tab.c"
    break;

  case 109: /* bitwise_and: equality  */
#line 558 "rules.y"
               {
        (yyval.node) = make(BITWISE_AND_NODE, EQUALITY_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2600 "rules.tab.c"
    break;

  case 110: /* equality: equality EQ relational  */
#line 564 "rules.y"
                           {
        (yyval.node) = make(EQUALITY_NODE, EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2608 "rules.tab.c"
    break;

  case 111: /* equality: equality NE relational  */
#line 567 "rules.y"
                             {
        (yyval.node) = make(EQUALITY_NODE, NOT_EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2616 "rules.tab.c"
    break;

  case 112: /* equality: relational  */
#line 570 "rules.y"
                 {
        (yyval.node) = make(EQUALITY_NODE, RELATIONAL_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2624 "rules.tab.c"
    break;

  case 113: /* relational: relational LE sum  */
#line 576 "rules.y"
                      {
        (yyval.node) = make(RELATIONAL_NODE, LESS_EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2632 "rules.tab.c"
    break;

  case 114: /* relational: relational GE sum  */
#line 579 "rules.y"
                        {
        (yyval.node) = make(RELATIONAL_NODE, GREATER_EQUAL_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2640 "rules.tab.c"
    break;

  case 115: /* relational: relational '<' sum  */
#line 582 "rules.y"
                         {
        (yyval.node) = make(RELATIONAL_NODE, LESS_THAN_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2648 "rules.tab.c"
    break;

  case 116: /* relational: relational '>' sum  */
#line 585 "rules.y"
                         {
        (yyval.node) = make(RELATIONAL_NODE, GREATER_THAN_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2656 "rules.tab.c"
    break;

  case 117: /* relational: sum  */
#line 588 "rules.y"
          {
        (yyval.node) = make(RELATIONAL_NODE, SUM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2664 "rules.tab.c"
    break;

  case 118: /* sum: sum '+' bitwise_shift  */
#line 594 "rules.y"
                          {
        (yyval.node) = make(SUM_NODE, ADDITION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2672 "rules.tab.c"
    break;

  case 119: /* sum: sum '-' bitwise_shift  */
#line 597 "rules.y"
                            {
        (yyval.node) = make(SUM_NODE, SUBTRACTION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2680 "rules.tab.c"
    break;

  case 120: /* sum: bitwise_shift  */
#line 600 "rules.y"
                    {
        (yyval.node) = make(SUM_NODE, BITWISE_SHIFT_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2688 "rules.tab.c"
    break;

  case 121: /* bitwise_shift: bitwise_shift LSHIFT term  */
#line 606 "rules.y"
                              {
        (yyval.node) = make(BITWISE_SHIFT_NODE, LSHIFT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2696 "rules.tab.c"
    break;

  case 122: /* bitwise_shift: bitwise_shift RSHIFT term  */
#line 609 "rules.y"
                                {
        (yyval.node) = make(BITWISE_SHIFT_NODE, RSHIFT_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2704 "rules.tab.c"
    break;

  case 123: /* bitwise_shift: term  */
#line 612 "rules.y"
           {
        (yyval.node) = make(BITWISE_SHIFT_NODE, TERM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2712 "rules.tab.c"
    break;

  case 124: /* term: term '*' prefix_op  */
#line 618 "rules.y"
                       {
        (yyval.node) = make(TERM_NODE, MULTIPLICATION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2720 "rules.tab.c"
    break;

  case 125: /* term: term '/' prefix_op  */
#line 621 "rules.y"
                         {
        (yyval.node) = make(TERM_NODE, DIVISION_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2728 "rules.tab.c"
    break;

  case 126: /* term: term '%' prefix_op  */
#line 624 "rules.y"
                         {
        (yyval.node) = make(TERM_NODE, REMAINDER_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2736 "rules.tab.c"
    break;

  case 127: /* term: prefix_op  */
#line 627 "rules.y"
                {
        (yyval.node) = make(TERM_NODE, PREFIX_OP_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2744 "rules.tab.c"
    break;

  case 128: /* prefix_op: '+' prefix_op  */
#line 633 "rules.y"
                  {
        (yyval.node) = make(PREFIX_OP_NODE, POSITIVE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2752 "rules.tab.c"
    break;

  case 129: /* prefix_op: '-' prefix_op  */
#line 636 "rules.y"
                    {
        (yyval.node) = make(PREFIX_OP_NODE, NEGATIVE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2760 "rules.tab.c"
    break;

  case 130: /* prefix_op: NOT prefix_op  */
#line 639 "rules.y"
                    {
        (yyval.node) = make(PREFIX_OP_NODE, NOT_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2768 "rules.tab.c"
    break;

  case 131: /* prefix_op: '~' prefix_op  */
#line 642 "rules.y"
                   {
        (yyval.node) = make(PREFIX_OP_NODE, INVERSE_OPTION, (yyvsp[-1].num), 1, (yyvsp[0].node));
    }
#line 2776 "rules.tab.c"
    break;

  case 132: /* prefix_op: primary  */
#line 645 "rules.y"
              {
        (yyval.node) = make(PREFIX_OP_NODE, PRIMARY_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2784 "rules.tab.c"
    break;

  case 133: /* primary: primary '(' expr_list ')'  */
#line 651 "rules.y"
                              {
        (yyval.node) = make(PRIMARY_NODE, CALL_OPTION, (yyvsp[-3].node)->lineno, 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2792 "rules.tab.c"
    break;

  case 134: /* primary: primary '(' ')'  */
#line 654 "rules.y"
                      {
        (yyval.node) = make(PRIMARY_NODE, CALL_OPTION, (yyvsp[-2].node)->lineno, 1, (yyvsp[-2].node));
    }
#line 2800 "rules.tab.c"
    break;

  case 135: /* primary: primary '[' expr ']'  */
#line 657 "rules.y"
                           {
        (yyval.node) = make(PRIMARY_NODE, INDEX_OPTION, (yyvsp[-3].node)->lineno, 2, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2808 "rules.tab.c"
    break;

  case 136: /* primary: primary '.' IDENTIFIER  */
#line 660 "rules.y"
                             {
        (yyval.node) = make(PRIMARY_NODE, FIELD_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2816 "rules.tab.c"
    break;

  case 137: /* primary: primary ':' IDENTIFIER  */
#line 663 "rules.y"
                             {
        (yyval.node) = make(PRIMARY_NODE, METHOD_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2824 "rules.tab.c"
    break;

  case 138: /* primary: elementary  */
#line 666 "rules.y"
                 {
        (yyval.node) = make(PRIMARY_NODE, ELEMENTARY_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2832 "rules.tab.c"
    break;

  case 139: /* elementary: '(' expr ')'  */
#line 672 "rules.y"
                 {
        (yyval.node) = make(ELEMENTARY_NODE, EXPR_OPTION, (yyvsp[-2].num), 1, (yyvsp[-1].node));
    }
#line 2840 "rules.tab.c"
    break;

  case 140: /* elementary: literal  */
#line 675 "rules.y"
              {
        (yyval.node) = make(ELEMENTARY_NODE, LITERAL_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2848 "rules.tab.c"
    break;

  case 141: /* literal: NULLV  */
#line 681 "rules.y"
          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2856 "rules.tab.c"
    break;

  case 142: /* literal: BOOL  */
#line 684 "rules.y"
           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2864 "rules.tab.c"
    break;

  case 143: /* literal: CHAR  */
#line 687 "rules.y"
           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2872 "rules.tab.c"
    break;

  case 144: /* literal: INT  */
#line 690 "rules.y"
          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2880 "rules.tab.c"
    break;

  case 145: /* literal: FLOAT  */
#line 693 "rules.y"
            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2888 "rules.tab.c"
    break;

  case 146: /* literal: STRING  */
#line 696 "rules.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2896 "rules.tab.c"
    break;

  case 147: /* literal: IDENTIFIER  */
#line 699 "rules.y"
                 {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2904 "rules.tab.c"
    break;

  case 148: /* expr_list: expr ',' expr_list  */
#line 705 "rules.y"
                       {
        (yyval.node) = make(EXPR_LIST_NODE, LIST_RECURSIVE_OPTION, (yyvsp[-2].node)->lineno, 2, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2912 "rules.tab.c"
    break;

  case 149: /* expr_list: expr  */
#line 708 "rules.y"
           {
        (yyval.node) = make(EXPR_LIST_NODE, LIST_BASE_ITEM_OPTION, (yyvsp[0].node)->lineno, 1, (yyvsp[0].node));
    }
#line 2920 "rules.tab.c"
    break;


#line 2924 "rules.tab.c"

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

#line 712 "rules.y"
