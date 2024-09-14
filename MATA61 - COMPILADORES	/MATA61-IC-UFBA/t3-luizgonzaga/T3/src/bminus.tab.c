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
#line 1 "bminus.y"

/* includes, C defs */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

struct decl *parser_result = 0;
extern int yylineno;
extern char* yytext;
int yylex();
void yyerror(const char *s);


#line 86 "bminus.tab.c"

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

#include "bminus.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ARRAY = 3,                      /* ARRAY  */
  YYSYMBOL_BOOLEAN = 4,                    /* BOOLEAN  */
  YYSYMBOL_FUNCTION = 5,                   /* FUNCTION  */
  YYSYMBOL_INTEGER = 6,                    /* INTEGER  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_TRUE = 8,                       /* TRUE  */
  YYSYMBOL_FALSE = 9,                      /* FALSE  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_PRINT = 12,                     /* PRINT  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_ID = 15,                        /* ID  */
  YYSYMBOL_NUMBER = 16,                    /* NUMBER  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_TIMES = 19,                     /* TIMES  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_LT = 23,                        /* LT  */
  YYSYMBOL_GT = 24,                        /* GT  */
  YYSYMBOL_SEMIC = 25,                     /* SEMIC  */
  YYSYMBOL_COMMA = 26,                     /* COMMA  */
  YYSYMBOL_COLON = 27,                     /* COLON  */
  YYSYMBOL_OPENP = 28,                     /* OPENP  */
  YYSYMBOL_CLOSEP = 29,                    /* CLOSEP  */
  YYSYMBOL_OPENBK = 30,                    /* OPENBK  */
  YYSYMBOL_CLOSEBK = 31,                   /* CLOSEBK  */
  YYSYMBOL_OPENBRACE = 32,                 /* OPENBRACE  */
  YYSYMBOL_CLOSEBRACE = 33,                /* CLOSEBRACE  */
  YYSYMBOL_LTE = 34,                       /* LTE  */
  YYSYMBOL_GTE = 35,                       /* GTE  */
  YYSYMBOL_EQ = 36,                        /* EQ  */
  YYSYMBOL_NEQ = 37,                       /* NEQ  */
  YYSYMBOL_AND = 38,                       /* AND  */
  YYSYMBOL_OR = 39,                        /* OR  */
  YYSYMBOL_ERROR = 40,                     /* ERROR  */
  YYSYMBOL_UMINUS = 41,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_program = 43,                   /* program  */
  YYSYMBOL_declaration_list = 44,          /* declaration_list  */
  YYSYMBOL_declaration = 45,               /* declaration  */
  YYSYMBOL_simple_type = 46,               /* simple_type  */
  YYSYMBOL_array_type = 47,                /* array_type  */
  YYSYMBOL_literal_list = 48,              /* literal_list  */
  YYSYMBOL_literal = 49,                   /* literal  */
  YYSYMBOL_var_declaration = 50,           /* var_declaration  */
  YYSYMBOL_params = 51,                    /* params  */
  YYSYMBOL_param_list = 52,                /* param_list  */
  YYSYMBOL_param = 53,                     /* param  */
  YYSYMBOL_function_declaration = 54,      /* function_declaration  */
  YYSYMBOL_block = 55,                     /* block  */
  YYSYMBOL_var_declaration_list = 56,      /* var_declaration_list  */
  YYSYMBOL_statement_list = 57,            /* statement_list  */
  YYSYMBOL_statement = 58,                 /* statement  */
  YYSYMBOL_expression_stmt = 59,           /* expression_stmt  */
  YYSYMBOL_print_stmt = 60,                /* print_stmt  */
  YYSYMBOL_selection_stmt = 61,            /* selection_stmt  */
  YYSYMBOL_iteration_stmt = 62,            /* iteration_stmt  */
  YYSYMBOL_return_stmt = 63,               /* return_stmt  */
  YYSYMBOL_expression = 64,                /* expression  */
  YYSYMBOL_var = 65,                       /* var  */
  YYSYMBOL_conditional_expression_or = 66, /* conditional_expression_or  */
  YYSYMBOL_conditional_expression_and = 67, /* conditional_expression_and  */
  YYSYMBOL_simple_expression = 68,         /* simple_expression  */
  YYSYMBOL_arithmetic_expression = 69,     /* arithmetic_expression  */
  YYSYMBOL_term = 70,                      /* term  */
  YYSYMBOL_factor = 71,                    /* factor  */
  YYSYMBOL_call = 72,                      /* call  */
  YYSYMBOL_arg_list = 73                   /* arg_list  */
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
typedef yytype_uint8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    71,    71,    75,    76,    80,    81,    85,    86,    87,
      91,    95,    96,   100,   101,   102,   106,   107,   108,   109,
     113,   114,   118,   119,   122,   123,   127,   131,   132,   133,
     134,   138,   139,   143,   144,   148,   149,   150,   151,   152,
     153,   157,   158,   161,   165,   166,   170,   174,   175,   179,
     180,   184,   185,   189,   190,   194,   195,   199,   200,   201,
     202,   203,   204,   205,   209,   210,   211,   215,   216,   217,
     221,   222,   223,   224,   225,   226,   227,   228,   232,   233,
     237,   238
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ARRAY", "BOOLEAN",
  "FUNCTION", "INTEGER", "VOID", "TRUE", "FALSE", "ELSE", "IF", "PRINT",
  "RETURN", "WHILE", "ID", "NUMBER", "PLUS", "MINUS", "TIMES", "DIV",
  "NOT", "ASSIGN", "LT", "GT", "SEMIC", "COMMA", "COLON", "OPENP",
  "CLOSEP", "OPENBK", "CLOSEBK", "OPENBRACE", "CLOSEBRACE", "LTE", "GTE",
  "EQ", "NEQ", "AND", "OR", "ERROR", "UMINUS", "$accept", "program",
  "declaration_list", "declaration", "simple_type", "array_type",
  "literal_list", "literal", "var_declaration", "params", "param_list",
  "param", "function_declaration", "block", "var_declaration_list",
  "statement_list", "statement", "expression_stmt", "print_stmt",
  "selection_stmt", "iteration_stmt", "return_stmt", "expression", "var",
  "conditional_expression_or", "conditional_expression_and",
  "simple_expression", "arithmetic_expression", "term", "factor", "call",
  "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -10,    -4,    17,   -10,   -70,   -70,   -70,   224,   -70,   -70,
      -2,   -70,    43,   -70,   -70,    -9,    46,    32,    24,    22,
     -70,    33,   -70,    66,    -3,    96,   -70,   -70,   -70,    84,
      22,    43,   103,   -70,    78,   -70,    91,   -70,   -15,   -70,
     -70,   107,   124,   -70,    61,   -70,    22,   119,   126,   -70,
     -70,   -70,   -70,   121,   130,   180,   131,    57,   -70,   198,
     198,   -70,   198,   -70,   -70,   -70,    87,   113,   -70,   -70,
     -70,   -70,   -70,   -70,   136,   140,   127,   125,   -70,   186,
      71,   -70,   -70,   -70,   -70,   134,   198,   198,    53,   -70,
     143,   198,   129,     6,   198,   -70,   -70,   -70,   141,   -70,
     -70,   139,   -70,   -70,   -70,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,    43,   146,
     153,   -70,   155,   -70,   -70,   111,   138,   -70,   -70,   -70,
     125,   -70,    71,    71,    99,    99,    99,    99,    99,    99,
     -70,   -70,   -70,   165,   160,   165,   198,   -70,   -70,   177,
     -70,   -70,   -70,   165,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     4,     5,     6,     0,     1,     3,
       0,     7,     0,     8,     9,     0,     0,     0,     0,     0,
      16,     0,    18,     0,     0,     0,    13,    14,    15,     0,
       0,     0,     0,    20,     0,    22,     0,    17,     0,    11,
      10,     0,     0,    21,     0,    26,     0,     0,     0,    24,
      23,    72,    71,     0,     0,     0,     0,    51,    70,     0,
       0,    42,     0,    30,    32,    36,     0,     0,    34,    35,
      40,    37,    38,    39,     0,    73,    50,    53,    55,    63,
      66,    69,    74,    12,    19,     0,     0,     0,    51,    48,
       0,     0,     0,     0,     0,    73,    75,    76,     0,    28,
      31,     0,    29,    33,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    47,     0,    79,    81,     0,     0,    77,    27,    49,
      54,    56,    64,    65,    59,    61,    60,    62,    57,    58,
      67,    68,    25,     0,     0,     0,     0,    78,    52,    44,
      43,    46,    80,     0,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   188,   -12,   -70,   -70,   -26,   -41,   -70,
     -70,   150,   -70,   158,   -70,   133,   -65,   -70,   -70,   -70,
     -70,   -70,   -54,   -53,   -70,    94,    95,   -69,    34,   -50,
     -70,   -70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    15,    16,    38,    29,     5,    25,
      34,    35,     6,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   125
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      18,    90,   103,    64,    39,     1,    95,    95,    98,    96,
      97,    46,    32,    19,    51,    52,    20,     8,    47,    40,
      83,    88,    58,     7,    59,   100,    33,    60,    17,    49,
      26,    27,   119,   120,    62,   123,   103,   122,    28,   124,
     126,   134,   135,   136,   137,   138,   139,    11,    23,    13,
      14,   129,    24,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    30,   140,   141,    21,    51,
      52,    22,    53,    54,    55,    56,    57,    58,   149,    59,
     151,    93,    60,    94,    92,    93,    61,    94,   154,    62,
     116,   117,   152,    44,    63,    51,    52,    31,    53,    54,
      55,    56,    57,    58,    42,    59,   142,    43,    60,    37,
      48,    11,    61,    13,    14,    62,   108,   109,    36,    44,
      99,    51,    52,    44,    53,    54,    55,    56,    88,    58,
      41,    59,    10,    11,    60,    13,    14,   146,    61,    32,
     147,    62,   132,   133,    84,    44,   102,    51,    52,    86,
      53,    54,    55,    56,    88,    58,    85,    59,    87,    91,
      60,   104,   105,   107,    61,   118,   106,    62,   121,   148,
     127,    44,   128,    51,    52,   143,    53,    54,    55,    56,
      88,    58,   144,    59,   145,   150,    60,   153,    51,    52,
      61,     9,    50,    62,    45,    88,    58,    44,    59,   101,
     130,    60,   131,   108,   109,    89,    51,    52,    62,   110,
     111,     0,     0,    88,    58,     0,    59,     0,     0,    60,
     112,   113,   114,   115,     0,     0,    62,    10,    11,    12,
      13,    14
};

static const yytype_int16 yycheck[] =
{
      12,    55,    67,    44,    30,    15,    59,    60,    62,    59,
      60,    26,    15,    22,     8,     9,    25,     0,    33,    31,
      46,    15,    16,    27,    18,    66,    29,    21,    30,    41,
       8,     9,    86,    87,    28,    29,   101,    91,    16,    93,
      94,   110,   111,   112,   113,   114,   115,     4,    16,     6,
       7,   105,    28,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    32,   116,   117,    22,     8,
       9,    25,    11,    12,    13,    14,    15,    16,   143,    18,
     145,    28,    21,    30,    27,    28,    25,    30,   153,    28,
      19,    20,   146,    32,    33,     8,     9,    31,    11,    12,
      13,    14,    15,    16,    26,    18,   118,    29,    21,    25,
       3,     4,    25,     6,     7,    28,    17,    18,    22,    32,
      33,     8,     9,    32,    11,    12,    13,    14,    15,    16,
      27,    18,     3,     4,    21,     6,     7,    26,    25,    15,
      29,    28,   108,   109,    25,    32,    33,     8,     9,    28,
      11,    12,    13,    14,    15,    16,    30,    18,    28,    28,
      21,    25,    22,    38,    25,    31,    39,    28,    25,    31,
      29,    32,    33,     8,     9,    29,    11,    12,    13,    14,
      15,    16,    29,    18,    29,    25,    21,    10,     8,     9,
      25,     3,    42,    28,    36,    15,    16,    32,    18,    66,
     106,    21,   107,    17,    18,    25,     8,     9,    28,    23,
      24,    -1,    -1,    15,    16,    -1,    18,    -1,    -1,    21,
      34,    35,    36,    37,    -1,    -1,    28,     3,     4,     5,
       6,     7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    15,    43,    44,    45,    50,    54,    27,     0,    45,
       3,     4,     5,     6,     7,    46,    47,    30,    46,    22,
      25,    22,    25,    16,    28,    51,     8,     9,    16,    49,
      32,    31,    15,    29,    52,    53,    22,    25,    48,    49,
      46,    27,    26,    29,    32,    55,    26,    33,     3,    46,
      53,     8,     9,    11,    12,    13,    14,    15,    16,    18,
      21,    25,    28,    33,    50,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    49,    25,    30,    28,    28,    15,    25,
      64,    28,    27,    28,    30,    65,    71,    71,    64,    33,
      50,    57,    33,    58,    25,    22,    39,    38,    17,    18,
      23,    24,    34,    35,    36,    37,    19,    20,    31,    64,
      64,    25,    64,    29,    64,    73,    64,    29,    33,    64,
      67,    68,    70,    70,    69,    69,    69,    69,    69,    69,
      71,    71,    46,    29,    29,    29,    26,    29,    31,    58,
      25,    58,    64,    10,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    46,
      47,    48,    48,    49,    49,    49,    50,    50,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    55,    55,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    61,    61,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    69,    69,    69,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    72,    72,
      73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     1,     1,     1,     4,     6,     4,     8,
       2,     3,     1,     3,     3,     6,     7,     4,     3,     3,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     5,     5,     7,     5,     3,     2,     3,
       1,     1,     4,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     4,     3,
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
  case 2: /* program: declaration_list  */
#line 71 "bminus.y"
                   { parser_result = (yyvsp[0].decl); }
#line 1269 "bminus.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 75 "bminus.y"
                                { (yyval.decl) = insert_decl((yyvsp[-1].decl), (yyvsp[0].decl)); }
#line 1275 "bminus.tab.c"
    break;

  case 7: /* simple_type: BOOLEAN  */
#line 85 "bminus.y"
          { (yyval.type) = type_create(TYPE_BOOLEAN,0,0); }
#line 1281 "bminus.tab.c"
    break;

  case 8: /* simple_type: INTEGER  */
#line 86 "bminus.y"
          { (yyval.type) = type_create(TYPE_INTEGER,0,0); }
#line 1287 "bminus.tab.c"
    break;

  case 9: /* simple_type: VOID  */
#line 87 "bminus.y"
          { (yyval.type) = type_create(TYPE_VOID,0,0); }
#line 1293 "bminus.tab.c"
    break;

  case 10: /* array_type: ARRAY OPENBK NUMBER CLOSEBK simple_type  */
#line 91 "bminus.y"
                                          { (yyval.type) = type_create(TYPE_ARRAY, (yyvsp[0].type), 0); }
#line 1299 "bminus.tab.c"
    break;

  case 12: /* literal_list: literal_list COMMA literal  */
#line 96 "bminus.y"
                             { (yyval.expr) = insert_expr((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1305 "bminus.tab.c"
    break;

  case 13: /* literal: TRUE  */
#line 100 "bminus.y"
       { (yyval.expr) = expr_create_boolean(1); }
#line 1311 "bminus.tab.c"
    break;

  case 14: /* literal: FALSE  */
#line 101 "bminus.y"
        { (yyval.expr) = expr_create_boolean(0); }
#line 1317 "bminus.tab.c"
    break;

  case 15: /* literal: NUMBER  */
#line 102 "bminus.y"
         { (yyval.expr) = expr_create_integer(atoi(yytext)); }
#line 1323 "bminus.tab.c"
    break;

  case 16: /* var_declaration: ID COLON simple_type SEMIC  */
#line 106 "bminus.y"
                             { (yyval.decl) = var_decl_create((yyvsp[-3].name), (yyvsp[-1].type)); }
#line 1329 "bminus.tab.c"
    break;

  case 17: /* var_declaration: ID COLON simple_type ASSIGN literal SEMIC  */
#line 107 "bminus.y"
                                            { (yyval.decl) = var_decl_create((yyvsp[-5].name), (yyvsp[-3].type)); (yyval.decl)->expr = (yyvsp[-1].expr); }
#line 1335 "bminus.tab.c"
    break;

  case 18: /* var_declaration: ID COLON array_type SEMIC  */
#line 108 "bminus.y"
                            { (yyval.decl) = array_decl_create((yyvsp[-3].name), (yyvsp[-1].type), 0); }
#line 1341 "bminus.tab.c"
    break;

  case 19: /* var_declaration: ID COLON array_type ASSIGN OPENBRACE literal_list CLOSEBRACE SEMIC  */
#line 109 "bminus.y"
                                                                     { (yyval.decl) = array_decl_create((yyvsp[-7].name), (yyvsp[-5].type), 0); (yyval.decl)->expr = (yyvsp[-2].expr); }
#line 1347 "bminus.tab.c"
    break;

  case 20: /* params: OPENP CLOSEP  */
#line 113 "bminus.y"
               { (yyval.param_list) = 0; }
#line 1353 "bminus.tab.c"
    break;

  case 21: /* params: OPENP param_list CLOSEP  */
#line 114 "bminus.y"
                          { (yyval.param_list) = (yyvsp[-1].param_list); }
#line 1359 "bminus.tab.c"
    break;

  case 23: /* param_list: param_list COMMA param  */
#line 119 "bminus.y"
                          { (yyvsp[-2].param_list) = insert_param((yyvsp[-2].param_list), (yyvsp[0].param_list)); (yyval.param_list) = (yyvsp[-2].param_list); }
#line 1365 "bminus.tab.c"
    break;

  case 24: /* param: ID COLON simple_type  */
#line 122 "bminus.y"
                       { (yyval.param_list) = param_create((yyvsp[-2].name),(yyvsp[0].type)); }
#line 1371 "bminus.tab.c"
    break;

  case 25: /* param: ID COLON ARRAY OPENBK CLOSEBK simple_type  */
#line 123 "bminus.y"
                                            { (yyval.param_list) = param_array_create((yyvsp[-5].name), (yyvsp[0].type)); }
#line 1377 "bminus.tab.c"
    break;

  case 26: /* function_declaration: ID COLON FUNCTION simple_type params ASSIGN block  */
#line 127 "bminus.y"
                                                    { (yyval.decl) = func_decl_create((yyvsp[-6].name),(yyvsp[-3].type),(yyvsp[-2].param_list),(yyvsp[0].stmt)); }
#line 1383 "bminus.tab.c"
    break;

  case 27: /* block: OPENBRACE var_declaration_list statement_list CLOSEBRACE  */
#line 131 "bminus.y"
                                                             { (yyval.stmt) = compound_stmt_create(STMT_BLOCK, (yyvsp[-2].decl), (yyvsp[-1].stmt)); }
#line 1389 "bminus.tab.c"
    break;

  case 28: /* block: OPENBRACE var_declaration_list CLOSEBRACE  */
#line 132 "bminus.y"
                                            { (yyval.stmt) = compound_stmt_create(STMT_BLOCK, (yyvsp[-1].decl), 0); }
#line 1395 "bminus.tab.c"
    break;

  case 29: /* block: OPENBRACE statement_list CLOSEBRACE  */
#line 133 "bminus.y"
                                      { (yyval.stmt) = compound_stmt_create(STMT_BLOCK, 0, (yyvsp[-1].stmt)); }
#line 1401 "bminus.tab.c"
    break;

  case 30: /* block: OPENBRACE CLOSEBRACE  */
#line 134 "bminus.y"
                       { (yyval.stmt) = compound_stmt_create(STMT_BLOCK, 0, 0); }
#line 1407 "bminus.tab.c"
    break;

  case 31: /* var_declaration_list: var_declaration_list var_declaration  */
#line 138 "bminus.y"
                                       { (yyval.decl) = insert_decl((yyvsp[-1].decl), (yyvsp[0].decl)); }
#line 1413 "bminus.tab.c"
    break;

  case 33: /* statement_list: statement_list statement  */
#line 143 "bminus.y"
                           { (yyval.stmt) = insert_stmt((yyvsp[-1].stmt), (yyvsp[0].stmt)); }
#line 1419 "bminus.tab.c"
    break;

  case 41: /* expression_stmt: expression SEMIC  */
#line 157 "bminus.y"
                   { (yyval.stmt) = stmt_create(STMT_EXPR, 0, 0, (yyvsp[-1].expr), 0, 0, 0, 0); }
#line 1425 "bminus.tab.c"
    break;

  case 42: /* expression_stmt: SEMIC  */
#line 158 "bminus.y"
        { (yyval.stmt) = 0; }
#line 1431 "bminus.tab.c"
    break;

  case 43: /* print_stmt: PRINT OPENP expression CLOSEP SEMIC  */
#line 161 "bminus.y"
                                      { (yyval.stmt) = stmt_create(STMT_PRINT, 0, 0, (yyvsp[-2].expr), 0, 0, 0, 0); }
#line 1437 "bminus.tab.c"
    break;

  case 44: /* selection_stmt: IF OPENP expression CLOSEP statement  */
#line 165 "bminus.y"
                                       { (yyval.stmt) = if_create((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1443 "bminus.tab.c"
    break;

  case 45: /* selection_stmt: IF OPENP expression CLOSEP statement ELSE statement  */
#line 166 "bminus.y"
                                                      { (yyval.stmt) = if_else_create((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 1449 "bminus.tab.c"
    break;

  case 46: /* iteration_stmt: WHILE OPENP expression CLOSEP statement  */
#line 170 "bminus.y"
                                          { (yyval.stmt) = while_create((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1455 "bminus.tab.c"
    break;

  case 47: /* return_stmt: RETURN expression SEMIC  */
#line 174 "bminus.y"
                          { (yyval.stmt) = stmt_create(STMT_RETURN, 0, 0, (yyvsp[-1].expr), 0, 0, 0, 0); }
#line 1461 "bminus.tab.c"
    break;

  case 48: /* return_stmt: RETURN SEMIC  */
#line 175 "bminus.y"
               { (yyval.stmt) = stmt_create(STMT_RETURN, 0, 0, 0, 0, 0, 0, 0); }
#line 1467 "bminus.tab.c"
    break;

  case 49: /* expression: var ASSIGN expression  */
#line 179 "bminus.y"
                        { (yyval.expr) = expr_create(EXPR_ASSIGN, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1473 "bminus.tab.c"
    break;

  case 51: /* var: ID  */
#line 184 "bminus.y"
     { (yyval.expr) = expr_create_var((yyvsp[0].name)); }
#line 1479 "bminus.tab.c"
    break;

  case 52: /* var: ID OPENBK expression CLOSEBK  */
#line 185 "bminus.y"
                               { (yyval.expr) = expr_create_array((yyvsp[-3].name),(yyvsp[-1].expr)); }
#line 1485 "bminus.tab.c"
    break;

  case 54: /* conditional_expression_or: conditional_expression_or OR conditional_expression_and  */
#line 190 "bminus.y"
                                                           { (yyval.expr) = expr_create(EXPR_OR, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1491 "bminus.tab.c"
    break;

  case 56: /* conditional_expression_and: conditional_expression_and AND simple_expression  */
#line 195 "bminus.y"
                                                   { (yyval.expr) = expr_create(EXPR_AND, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1497 "bminus.tab.c"
    break;

  case 57: /* simple_expression: arithmetic_expression EQ arithmetic_expression  */
#line 199 "bminus.y"
                                                 { (yyval.expr) = expr_create(EXPR_EQ, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1503 "bminus.tab.c"
    break;

  case 58: /* simple_expression: arithmetic_expression NEQ arithmetic_expression  */
#line 200 "bminus.y"
                                                  { (yyval.expr) = expr_create(EXPR_NEQ, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1509 "bminus.tab.c"
    break;

  case 59: /* simple_expression: arithmetic_expression LT arithmetic_expression  */
#line 201 "bminus.y"
                                                 { (yyval.expr) = expr_create(EXPR_LT, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1515 "bminus.tab.c"
    break;

  case 60: /* simple_expression: arithmetic_expression LTE arithmetic_expression  */
#line 202 "bminus.y"
                                                  { (yyval.expr) = expr_create(EXPR_LTEQ, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1521 "bminus.tab.c"
    break;

  case 61: /* simple_expression: arithmetic_expression GT arithmetic_expression  */
#line 203 "bminus.y"
                                                 { (yyval.expr) = expr_create(EXPR_GT, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1527 "bminus.tab.c"
    break;

  case 62: /* simple_expression: arithmetic_expression GTE arithmetic_expression  */
#line 204 "bminus.y"
                                                  { (yyval.expr) = expr_create(EXPR_GTEQ, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1533 "bminus.tab.c"
    break;

  case 64: /* arithmetic_expression: arithmetic_expression PLUS term  */
#line 209 "bminus.y"
                                  { (yyval.expr) = expr_create(EXPR_ADD, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1539 "bminus.tab.c"
    break;

  case 65: /* arithmetic_expression: arithmetic_expression MINUS term  */
#line 210 "bminus.y"
                                    { (yyval.expr) = expr_create(EXPR_SUB, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1545 "bminus.tab.c"
    break;

  case 67: /* term: term TIMES factor  */
#line 215 "bminus.y"
                    { (yyval.expr) = expr_create(EXPR_MUL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1551 "bminus.tab.c"
    break;

  case 68: /* term: term DIV factor  */
#line 216 "bminus.y"
                  { (yyval.expr) = expr_create(EXPR_DIV, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1557 "bminus.tab.c"
    break;

  case 70: /* factor: NUMBER  */
#line 221 "bminus.y"
         { (yyval.expr) = expr_create_integer(atoi(yytext)); }
#line 1563 "bminus.tab.c"
    break;

  case 71: /* factor: FALSE  */
#line 222 "bminus.y"
         { (yyval.expr) = expr_create_boolean(0); }
#line 1569 "bminus.tab.c"
    break;

  case 72: /* factor: TRUE  */
#line 223 "bminus.y"
         { (yyval.expr) = expr_create_boolean(1); }
#line 1575 "bminus.tab.c"
    break;

  case 75: /* factor: MINUS factor  */
#line 226 "bminus.y"
                            { (yyval.expr) = expr_create(EXPR_SUB,expr_create_integer(0),(yyvsp[0].expr)); }
#line 1581 "bminus.tab.c"
    break;

  case 76: /* factor: NOT factor  */
#line 227 "bminus.y"
             { (yyval.expr) = expr_create(EXPR_NOT, (yyvsp[0].expr), 0); }
#line 1587 "bminus.tab.c"
    break;

  case 77: /* factor: OPENP expression CLOSEP  */
#line 228 "bminus.y"
                          { (yyval.expr) = (yyvsp[-1].expr); }
#line 1593 "bminus.tab.c"
    break;

  case 78: /* call: ID OPENP arg_list CLOSEP  */
#line 232 "bminus.y"
                           { (yyval.expr) = expr_create_call((yyvsp[-3].name),(yyvsp[-1].expr)); }
#line 1599 "bminus.tab.c"
    break;

  case 79: /* call: ID OPENP CLOSEP  */
#line 233 "bminus.y"
                  { (yyval.expr) = expr_create_call((yyvsp[-2].name), 0); }
#line 1605 "bminus.tab.c"
    break;

  case 80: /* arg_list: arg_list COMMA expression  */
#line 237 "bminus.y"
                            { (yyval.expr) = insert_expr((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1611 "bminus.tab.c"
    break;


#line 1615 "bminus.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 241 "bminus.y"

void yyerror(const char *s)
{
   fprintf(stderr, "erro sintático.\n");
}
