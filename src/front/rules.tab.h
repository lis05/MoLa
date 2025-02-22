/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_RULES_TAB_H_INCLUDED
# define YY_YY_RULES_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BOOL = 258,                    /* BOOL  */
    CHAR = 259,                    /* CHAR  */
    INT = 260,                     /* INT  */
    FLOAT = 261,                   /* FLOAT  */
    STRING = 262,                  /* STRING  */
    IDENTIFIER = 263,              /* IDENTIFIER  */
    NULLV = 264,                   /* NULLV  */
    IMPORT = 265,                  /* IMPORT  */
    EXPORT = 266,                  /* EXPORT  */
    GLOBAL = 267,                  /* GLOBAL  */
    FUNCTION = 268,                /* FUNCTION  */
    TYPE = 269,                    /* TYPE  */
    METHOD = 270,                  /* METHOD  */
    CONSTRUCTOR = 271,             /* CONSTRUCTOR  */
    DESTRUCTOR = 272,              /* DESTRUCTOR  */
    OF = 273,                      /* OF  */
    COPY = 274,                    /* COPY  */
    REF = 275,                     /* REF  */
    PASS = 276,                    /* PASS  */
    CONTINUE = 277,                /* CONTINUE  */
    BREAK = 278,                   /* BREAK  */
    RETURN = 279,                  /* RETURN  */
    VAR = 280,                     /* VAR  */
    TRY = 281,                     /* TRY  */
    CATCH = 282,                   /* CATCH  */
    FINALLY = 283,                 /* FINALLY  */
    SIGNAL = 284,                  /* SIGNAL  */
    BECAUSE = 285,                 /* BECAUSE  */
    IF = 286,                      /* IF  */
    ELSE = 287,                    /* ELSE  */
    WHILE = 288,                   /* WHILE  */
    FOR = 289,                     /* FOR  */
    WHEN = 290,                    /* WHEN  */
    THEN = 291,                    /* THEN  */
    NEW = 292,                     /* NEW  */
    OR = 293,                      /* OR  */
    AND = 294,                     /* AND  */
    NOT = 295,                     /* NOT  */
    COPIES = 296,                  /* COPIES  */
    REFS = 297,                    /* REFS  */
    AS = 298,                      /* AS  */
    LSHIFT = 299,                  /* LSHIFT  */
    RSHIFT = 300,                  /* RSHIFT  */
    EQ = 301,                      /* EQ  */
    NE = 302,                      /* NE  */
    LE = 303,                      /* LE  */
    GE = 304                       /* GE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "rules.y"

    int64_t num;
    nodeptr node;

#line 118 "rules.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_RULES_TAB_H_INCLUDED  */
