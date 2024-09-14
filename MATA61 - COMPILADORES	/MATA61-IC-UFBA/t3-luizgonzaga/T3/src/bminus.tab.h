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

#ifndef YY_YY_BMINUS_TAB_H_INCLUDED
# define YY_YY_BMINUS_TAB_H_INCLUDED
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
    ARRAY = 258,                   /* ARRAY  */
    BOOLEAN = 259,                 /* BOOLEAN  */
    FUNCTION = 260,                /* FUNCTION  */
    INTEGER = 261,                 /* INTEGER  */
    VOID = 262,                    /* VOID  */
    TRUE = 263,                    /* TRUE  */
    FALSE = 264,                   /* FALSE  */
    ELSE = 265,                    /* ELSE  */
    IF = 266,                      /* IF  */
    PRINT = 267,                   /* PRINT  */
    RETURN = 268,                  /* RETURN  */
    WHILE = 269,                   /* WHILE  */
    ID = 270,                      /* ID  */
    NUMBER = 271,                  /* NUMBER  */
    PLUS = 272,                    /* PLUS  */
    MINUS = 273,                   /* MINUS  */
    TIMES = 274,                   /* TIMES  */
    DIV = 275,                     /* DIV  */
    NOT = 276,                     /* NOT  */
    ASSIGN = 277,                  /* ASSIGN  */
    LT = 278,                      /* LT  */
    GT = 279,                      /* GT  */
    SEMIC = 280,                   /* SEMIC  */
    COMMA = 281,                   /* COMMA  */
    COLON = 282,                   /* COLON  */
    OPENP = 283,                   /* OPENP  */
    CLOSEP = 284,                  /* CLOSEP  */
    OPENBK = 285,                  /* OPENBK  */
    CLOSEBK = 286,                 /* CLOSEBK  */
    OPENBRACE = 287,               /* OPENBRACE  */
    CLOSEBRACE = 288,              /* CLOSEBRACE  */
    LTE = 289,                     /* LTE  */
    GTE = 290,                     /* GTE  */
    EQ = 291,                      /* EQ  */
    NEQ = 292,                     /* NEQ  */
    AND = 293,                     /* AND  */
    OR = 294,                      /* OR  */
    ERROR = 295,                   /* ERROR  */
    UMINUS = 296                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "bminus.y"

    struct decl *decl;
    struct stmt *stmt;
    struct expr *expr;
    struct type *type;
    struct param_list *param_list;
    char *name;
    int d;

#line 115 "bminus.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BMINUS_TAB_H_INCLUDED  */
