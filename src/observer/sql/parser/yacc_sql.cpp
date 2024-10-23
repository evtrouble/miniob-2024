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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <utility>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 126 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_ORDER = 8,                      /* ORDER  */
  YYSYMBOL_HAVING = 9,                     /* HAVING  */
  YYSYMBOL_ASC = 10,                       /* ASC  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_TABLE = 12,                     /* TABLE  */
  YYSYMBOL_TABLES = 13,                    /* TABLES  */
  YYSYMBOL_INDEX = 14,                     /* INDEX  */
  YYSYMBOL_CALC = 15,                      /* CALC  */
  YYSYMBOL_SELECT = 16,                    /* SELECT  */
  YYSYMBOL_SHOW = 17,                      /* SHOW  */
  YYSYMBOL_SYNC = 18,                      /* SYNC  */
  YYSYMBOL_INSERT = 19,                    /* INSERT  */
  YYSYMBOL_DELETE = 20,                    /* DELETE  */
  YYSYMBOL_UPDATE = 21,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 22,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 23,                    /* RBRACE  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 25,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 26,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 27,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 28,                     /* INT_T  */
  YYSYMBOL_STRING_T = 29,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 30,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 31,                    /* DATE_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_INTO = 35,                      /* INTO  */
  YYSYMBOL_VALUES = 36,                    /* VALUES  */
  YYSYMBOL_FROM = 37,                      /* FROM  */
  YYSYMBOL_WHERE = 38,                     /* WHERE  */
  YYSYMBOL_INNER = 39,                     /* INNER  */
  YYSYMBOL_JOIN = 40,                      /* JOIN  */
  YYSYMBOL_AND = 41,                       /* AND  */
  YYSYMBOL_OR = 42,                        /* OR  */
  YYSYMBOL_SET = 43,                       /* SET  */
  YYSYMBOL_ON = 44,                        /* ON  */
  YYSYMBOL_AS = 45,                        /* AS  */
  YYSYMBOL_LOAD = 46,                      /* LOAD  */
  YYSYMBOL_DATA = 47,                      /* DATA  */
  YYSYMBOL_LIKE = 48,                      /* LIKE  */
  YYSYMBOL_NULL_T = 49,                    /* NULL_T  */
  YYSYMBOL_EXISTS = 50,                    /* EXISTS  */
  YYSYMBOL_IN = 51,                        /* IN  */
  YYSYMBOL_IS = 52,                        /* IS  */
  YYSYMBOL_NOT = 53,                       /* NOT  */
  YYSYMBOL_INFILE = 54,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 55,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 56,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 57,                    /* FORMAT  */
  YYSYMBOL_EQ = 58,                        /* EQ  */
  YYSYMBOL_LT = 59,                        /* LT  */
  YYSYMBOL_GT = 60,                        /* GT  */
  YYSYMBOL_LE = 61,                        /* LE  */
  YYSYMBOL_GE = 62,                        /* GE  */
  YYSYMBOL_NE = 63,                        /* NE  */
  YYSYMBOL_UNIQUE = 64,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 65,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 66,                     /* FLOAT  */
  YYSYMBOL_ID = 67,                        /* ID  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_DATE_VALUE = 69,                /* DATE_VALUE  */
  YYSYMBOL_70_ = 70,                       /* '+'  */
  YYSYMBOL_71_ = 71,                       /* '-'  */
  YYSYMBOL_72_ = 72,                       /* '*'  */
  YYSYMBOL_73_ = 73,                       /* '/'  */
  YYSYMBOL_UMINUS = 74,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_commands = 76,                  /* commands  */
  YYSYMBOL_command_wrapper = 77,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 78,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 79,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 80,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 81,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 82,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 83,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 84,           /* drop_table_stmt  */
  YYSYMBOL_show_index_stmt = 85,           /* show_index_stmt  */
  YYSYMBOL_show_tables_stmt = 86,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 87,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 88,         /* create_index_stmt  */
  YYSYMBOL_idx_col_list = 89,              /* idx_col_list  */
  YYSYMBOL_unique_option = 90,             /* unique_option  */
  YYSYMBOL_drop_index_stmt = 91,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 92,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 93,             /* attr_def_list  */
  YYSYMBOL_attr_def = 94,                  /* attr_def  */
  YYSYMBOL_is_null = 95,                   /* is_null  */
  YYSYMBOL_number = 96,                    /* number  */
  YYSYMBOL_type = 97,                      /* type  */
  YYSYMBOL_date_type = 98,                 /* date_type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_values_list = 100,              /* values_list  */
  YYSYMBOL_value_list = 101,               /* value_list  */
  YYSYMBOL_value = 102,                    /* value  */
  YYSYMBOL_storage_format = 103,           /* storage_format  */
  YYSYMBOL_delete_stmt = 104,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 105,              /* update_stmt  */
  YYSYMBOL_key_values = 106,               /* key_values  */
  YYSYMBOL_assign_value = 107,             /* assign_value  */
  YYSYMBOL_select_stmt = 108,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 109,                /* calc_stmt  */
  YYSYMBOL_expression_list = 110,          /* expression_list  */
  YYSYMBOL_expression = 111,               /* expression  */
  YYSYMBOL_rel_attr = 112,                 /* rel_attr  */
  YYSYMBOL_relation = 113,                 /* relation  */
  YYSYMBOL_rel_list = 114,                 /* rel_list  */
  YYSYMBOL_join_list = 115,                /* join_list  */
  YYSYMBOL_on = 116,                       /* on  */
  YYSYMBOL_where = 117,                    /* where  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_comp_op = 120,                  /* comp_op  */
  YYSYMBOL_unary_op = 121,                 /* unary_op  */
  YYSYMBOL_group_by = 122,                 /* group_by  */
  YYSYMBOL_having_node = 123,              /* having_node  */
  YYSYMBOL_having_list = 124,              /* having_list  */
  YYSYMBOL_having_unit = 125,              /* having_unit  */
  YYSYMBOL_order_by = 126,                 /* order_by  */
  YYSYMBOL_order_by_list = 127,            /* order_by_list  */
  YYSYMBOL_order_by_unit = 128,            /* order_by_unit  */
  YYSYMBOL_load_data_stmt = 129,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 130,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 131,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 132             /* opt_semicolon  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  267

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


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
       2,     2,    72,    70,     2,    71,     2,    73,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    74
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   232,   232,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   266,   272,   277,   283,   289,   295,
     301,   307,   315,   321,   329,   350,   353,   366,   369,   374,
     384,   408,   411,   424,   433,   442,   455,   456,   457,   461,
     464,   465,   466,   469,   473,   488,   494,   508,   513,   524,
     528,   532,   538,   545,   551,   554,   561,   573,   591,   599,
     615,   616,   623,   666,   675,   680,   691,   694,   697,   700,
     703,   707,   710,   715,   721,   724,   730,   738,   743,   750,
     759,   764,   769,   779,   793,   814,   827,   848,   851,   860,
     863,   869,   872,   877,   882,   890,   902,   914,   926,   938,
     949,   960,   969,   978,   989,  1000,  1015,  1016,  1017,  1018,
    1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1030,  1031,
    1037,  1040,  1048,  1051,  1058,  1063,  1069,  1077,  1087,  1090,
    1097,  1103,  1116,  1122,  1128,  1137,  1150,  1158,  1168,  1169
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "ORDER", "HAVING", "ASC", "DESC", "TABLE",
  "TABLES", "INDEX", "CALC", "SELECT", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "INNER", "JOIN", "AND", "OR",
  "SET", "ON", "AS", "LOAD", "DATA", "LIKE", "NULL_T", "EXISTS", "IN",
  "IS", "NOT", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT", "GT",
  "LE", "GE", "NE", "UNIQUE", "NUMBER", "FLOAT", "ID", "SSS", "DATE_VALUE",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_index_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_index_stmt",
  "idx_col_list", "unique_option", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "is_null", "number", "type", "date_type",
  "insert_stmt", "values_list", "value_list", "value", "storage_format",
  "delete_stmt", "update_stmt", "key_values", "assign_value",
  "select_stmt", "calc_stmt", "expression_list", "expression", "rel_attr",
  "relation", "rel_list", "join_list", "on", "where", "condition_list",
  "condition", "comp_op", "unary_op", "group_by", "having_node",
  "having_list", "having_unit", "order_by", "order_by_list",
  "order_by_unit", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-174)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     127,     2,    30,   -47,    29,    29,    46,  -174,     6,    11,
     -14,  -174,  -174,  -174,  -174,  -174,     8,    52,   127,    90,
      99,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,    26,  -174,    98,    54,    59,  -174,    29,  -174,
    -174,  -174,    -7,  -174,  -174,    29,  -174,  -174,  -174,    43,
    -174,    91,  -174,    92,    63,    67,    93,    77,    85,  -174,
    -174,  -174,  -174,   119,    83,  -174,   107,   -15,   100,   -22,
    -174,    29,    29,    29,    29,    29,    88,    89,   128,   123,
      96,   -36,   111,   113,   137,   120,  -174,  -174,   176,  -174,
    -174,  -174,    16,    16,  -174,  -174,  -174,    -8,   123,  -174,
     188,   135,  -174,   153,   123,  -174,   177,    76,   190,   148,
    -174,  -174,    88,   178,   193,   212,   -36,  -174,   204,  -174,
     173,   192,   207,   207,  -174,    68,   200,   172,  -174,   213,
    -174,  -174,  -174,  -174,   -10,   -32,   113,   201,   205,  -174,
      88,    88,   224,   225,   222,   211,   223,  -174,  -174,  -174,
     183,    28,  -174,  -174,  -174,  -174,  -174,  -174,   109,   140,
     135,   135,   204,   204,  -174,   232,   180,   206,  -174,   199,
    -174,  -174,   190,   216,   208,   229,  -174,    29,    29,   249,
     250,   -36,   207,  -174,  -174,  -174,   204,  -174,  -174,     3,
    -174,  -174,  -174,  -174,   253,   254,    96,  -174,  -174,   255,
    -174,  -174,   226,  -174,   256,   135,   240,  -174,   191,  -174,
      78,   277,  -174,   188,  -174,   164,   259,   261,   262,  -174,
    -174,  -174,   -32,   228,   220,   265,  -174,  -174,    29,    29,
      29,    29,  -174,   204,  -174,  -174,  -174,  -174,  -174,  -174,
     227,   256,  -174,   125,  -174,  -174,    14,  -174,   266,   268,
    -174,  -174,  -174,  -174,    29,  -174,  -174
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    37,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     148,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,    14,     8,     5,     7,     6,     4,     3,    19,
      20,    21,     0,    38,     0,     0,     0,    33,     0,    63,
      59,    60,    87,    61,    62,     0,    84,    82,    73,    74,
      83,     0,    32,     0,     0,     0,     0,     0,     0,   146,
       1,   149,     2,     0,     0,    30,     0,     0,     0,     0,
      81,     0,     0,     0,     0,     0,     0,     0,     0,    99,
       0,     0,     0,     0,     0,     0,    80,    86,     0,    88,
      89,    75,    76,    77,    78,    79,    90,    91,    99,    31,
       0,   101,    66,     0,    99,   147,     0,     0,    41,     0,
      39,    85,     0,     0,    93,   130,     0,    54,     0,   128,
       0,    87,     0,     0,   100,   102,     0,     0,    67,     0,
      50,    51,    52,    53,    46,    46,     0,     0,     0,    92,
       0,     0,     0,   132,     0,    57,     0,   129,   116,   124,
     126,     0,   118,   119,   120,   121,   122,   123,     0,     0,
     101,   101,     0,     0,    70,    68,     0,     0,    47,     0,
      44,    45,    41,    64,     0,    97,    94,     0,     0,   138,
      55,     0,     0,   127,   117,   125,     0,   106,   108,     0,
     105,   107,   103,   104,     0,     0,     0,   145,    49,     0,
      48,    42,     0,    40,    35,   101,    95,   131,     0,   133,
     134,     0,    72,     0,    58,     0,     0,     0,     0,   111,
      71,    69,    46,     0,     0,     0,    98,    96,     0,     0,
       0,     0,    56,     0,   113,   114,   110,   115,   109,    43,
       0,    35,    34,   137,   136,   135,   142,   139,   140,     0,
      65,    36,   143,   144,     0,   112,   141
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,   271,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,    41,  -174,  -174,  -174,   114,   147,
    -140,  -174,  -174,  -174,  -174,    72,  -173,   -88,  -174,  -174,
    -174,    94,  -174,  -126,  -174,    -4,   -48,  -107,   149,  -111,
      81,  -174,   -86,  -161,  -174,  -127,  -174,  -174,  -174,  -115,
    -174,  -174,    34,  -174,  -174,  -174,  -174,  -174
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   235,    44,    32,    33,   147,   118,
     180,   209,   144,   145,    34,   127,   154,    57,   213,    35,
      36,   114,   175,    37,    38,    58,    59,    60,   107,   108,
     124,   216,   112,   134,   135,   168,   136,   153,   189,   219,
     220,   222,   257,   258,    39,    40,    41,    72
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    61,   156,   115,   133,   181,   169,    80,    96,   202,
     203,   149,   177,    49,    42,    78,   122,   178,   224,     5,
      47,   179,   125,   132,   262,   263,   227,    79,   138,    50,
      51,   123,    53,    54,   102,   103,   104,   105,   155,   178,
     186,    64,    45,   179,    46,    99,   204,   205,    65,   174,
     100,    48,    49,    66,   236,    82,    83,    84,    85,    62,
      63,   198,   201,   133,   133,   225,    43,    81,    50,    51,
     226,    53,    54,   228,    98,    67,   194,   101,    49,   195,
     197,   200,   132,   132,    82,    83,    84,    85,    84,    85,
      70,   238,   249,    73,    50,    51,    52,    53,    54,    68,
      55,    56,    71,   155,   140,   141,   142,   143,   133,   170,
     171,   155,    74,    82,    83,    84,    85,   259,   245,   239,
     240,    75,    48,    97,   254,   255,    76,   132,    86,    87,
      88,   196,     1,     2,    89,    91,    90,   244,     3,    92,
     218,    93,     4,     5,     6,     7,     8,     9,    10,    49,
      94,    95,    11,    12,    13,   106,   109,   128,    49,    14,
      15,   111,   199,   113,   110,    50,    51,    52,    53,    54,
      16,    55,    56,    17,    50,    51,   131,    53,    54,   116,
     117,   119,    18,   217,    49,   129,   243,   120,   130,    49,
     253,   218,   218,   256,   173,    82,    83,    84,    85,   121,
      50,    51,   131,    53,    54,    50,    51,   131,    53,    54,
     126,   137,   139,    49,   146,   148,   256,   151,   150,   152,
       5,    49,   172,   157,   183,   176,    79,   184,   187,    50,
      51,   131,    53,    54,   188,   191,   193,    50,    51,   158,
      53,    54,   159,   160,   161,   190,   192,   207,   210,   162,
     163,   164,   165,   166,   167,   158,   206,   221,   159,   160,
     161,    82,    83,    84,    85,   162,   163,   164,   165,   166,
     167,   208,   212,   215,   223,   214,   229,   230,   232,   123,
     234,   241,   246,   233,   247,   248,   250,   251,   252,    69,
     264,   265,   261,   182,   260,   242,   211,   237,   266,   185,
     231
};

static const yytype_int16 yycheck[] =
{
      48,     5,   128,    91,   111,   145,   133,    55,    23,   170,
     171,   122,    22,    49,    12,    22,    24,    49,   191,    16,
      67,    53,   108,   111,    10,    11,   199,    34,   114,    65,
      66,    39,    68,    69,    82,    83,    84,    85,   126,    49,
     151,    35,    12,    53,    14,    67,   172,   173,    37,   137,
      72,    22,    49,    67,   215,    70,    71,    72,    73,    13,
      14,   168,   169,   170,   171,   192,    64,    24,    65,    66,
     196,    68,    69,   199,    78,    67,    48,    81,    49,    51,
     168,   169,   170,   171,    70,    71,    72,    73,    72,    73,
       0,   218,   232,    67,    65,    66,    67,    68,    69,    47,
      71,    72,     3,   191,    28,    29,    30,    31,   215,    41,
      42,   199,    14,    70,    71,    72,    73,   243,   225,    41,
      42,    67,    22,    23,   239,   240,    67,   215,    37,    37,
      67,    22,     5,     6,    67,    58,    43,   225,    11,    54,
     188,    22,    15,    16,    17,    18,    19,    20,    21,    49,
      67,    44,    25,    26,    27,    67,    67,    22,    49,    32,
      33,    38,    22,    67,    36,    65,    66,    67,    68,    69,
      43,    71,    72,    46,    65,    66,    67,    68,    69,    68,
      67,    44,    55,   187,    49,    50,    22,    67,    53,    49,
     238,   239,   240,   241,    22,    70,    71,    72,    73,    23,
      65,    66,    67,    68,    69,    65,    66,    67,    68,    69,
      22,    58,    35,    49,    24,    67,   264,    24,    40,     7,
      16,    49,    22,    50,    23,    12,    34,    22,     4,    65,
      66,    67,    68,    69,     9,    24,    53,    65,    66,    48,
      68,    69,    51,    52,    53,    23,    23,    67,    49,    58,
      59,    60,    61,    62,    63,    48,    24,     8,    51,    52,
      53,    70,    71,    72,    73,    58,    59,    60,    61,    62,
      63,    65,    56,    44,    24,    67,    23,    23,    23,    39,
      24,     4,    23,    57,    23,    23,    58,    67,    23,    18,
      24,    23,   251,   146,    67,   223,   182,   216,   264,   150,
     206
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    11,    15,    16,    17,    18,    19,    20,
      21,    25,    26,    27,    32,    33,    43,    46,    55,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    91,    92,    99,   104,   105,   108,   109,   129,
     130,   131,    12,    64,    90,    12,    14,    67,    22,    49,
      65,    66,    67,    68,    69,    71,    72,   102,   110,   111,
     112,   110,    13,    14,    35,    37,    67,    67,    47,    77,
       0,     3,   132,    67,    14,    67,    67,   111,    22,    34,
     111,    24,    70,    71,    72,    73,    37,    37,    67,    67,
      43,    58,    54,    22,    67,    44,    23,    23,   110,    67,
      72,   110,   111,   111,   111,   111,    67,   113,   114,    67,
      36,    38,   117,    67,   106,   102,    68,    67,    94,    44,
      67,    23,    24,    39,   115,   117,    22,   100,    22,    50,
      53,    67,   102,   112,   118,   119,   121,    58,   117,    35,
      28,    29,    30,    31,    97,    98,    24,    93,    67,   114,
      40,    24,     7,   122,   101,   102,   108,    50,    48,    51,
      52,    53,    58,    59,    60,    61,    62,    63,   120,   120,
      41,    42,    22,    22,   102,   107,    12,    22,    49,    53,
      95,    95,    94,    23,    22,   113,   114,     4,     9,   123,
      23,    24,    23,    53,    48,    51,    22,   102,   112,    22,
     102,   112,   118,   118,   108,   108,    24,    67,    65,    96,
      49,    93,    56,   103,    67,    44,   116,   110,   111,   124,
     125,     8,   126,    24,   101,   120,   108,   101,   108,    23,
      23,   106,    23,    57,    24,    89,   118,   115,   120,    41,
      42,     4,   100,    22,   102,   112,    23,    23,    23,    95,
      58,    67,    23,   111,   124,   124,   111,   127,   128,   108,
      67,    89,    10,    11,    24,    23,   127
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    89,    90,    90,    91,
      92,    93,    93,    94,    94,    94,    95,    95,    95,    96,
      97,    97,    97,    98,    99,   100,   100,   101,   101,   102,
     102,   102,   102,   102,   103,   103,   104,   105,   106,   106,
     107,   107,   108,   109,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   112,   112,
     113,   114,   114,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   118,   118,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   124,   124,   125,   126,   126,
     127,   127,   128,   128,   128,   129,   130,   131,   132,   132
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     2,     2,    10,     0,     3,     0,     1,     5,
       8,     0,     3,     6,     3,     3,     0,     1,     2,     1,
       1,     1,     1,     1,     5,     3,     5,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     4,     5,     3,     5,
       1,     3,     8,     2,     1,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     1,     4,     3,     1,     3,     3,
       1,     1,     3,     2,     4,     4,     5,     0,     2,     0,
       2,     0,     1,     3,     3,     3,     3,     3,     3,     5,
       5,     4,     7,     5,     5,     5,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     2,
       0,     3,     0,     2,     1,     3,     3,     3,     0,     3,
       1,     3,     1,     2,     2,     7,     2,     4,     0,     1
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
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
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
  YYLTYPE *yylloc;
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 233 "yacc_sql.y"
  {
    if((yyvsp[-1].sql_node) != nullptr){
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
  }
#line 1855 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 266 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1864 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 272 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1872 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 277 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1880 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 283 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1888 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 289 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 295 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 301 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 31: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 308 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1924 "yacc_sql.cpp"
    break;

  case 32: /* show_tables_stmt: SHOW TABLES  */
#line 315 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1932 "yacc_sql.cpp"
    break;

  case 33: /* desc_table_stmt: DESC ID  */
#line 321 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1942 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE unique_option INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 330 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.unique = (yyvsp[-8].boolean);
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      std::vector<std::string> *idx_cols = (yyvsp[-1].relation_list);
      if (nullptr != idx_cols) {
        create_index.attr_names.swap(*idx_cols);
        delete (yyvsp[-1].relation_list);
      }
      create_index.attr_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1964 "yacc_sql.cpp"
    break;

  case 35: /* idx_col_list: %empty  */
#line 350 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 1972 "yacc_sql.cpp"
    break;

  case 36: /* idx_col_list: COMMA ID idx_col_list  */
#line 354 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 1986 "yacc_sql.cpp"
    break;

  case 37: /* unique_option: %empty  */
#line 366 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 1994 "yacc_sql.cpp"
    break;

  case 38: /* unique_option: UNIQUE  */
#line 370 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 39: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 375 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 385 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(move(*(yyvsp[-3].attr_info)));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 408 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2047 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 412 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(move(*(yyvsp[-1].attr_info)));
      delete (yyvsp[-1].attr_info);
    }
#line 2061 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE is_null  */
#line 425 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->is_null = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 2074 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type is_null  */
#line 434 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->is_null = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID date_type is_null  */
#line 443 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 10;
      (yyval.attr_info)->is_null = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2100 "yacc_sql.cpp"
    break;

  case 46: /* is_null: %empty  */
#line 455 "yacc_sql.y"
    {(yyval.boolean) = false;}
#line 2106 "yacc_sql.cpp"
    break;

  case 47: /* is_null: NULL_T  */
#line 456 "yacc_sql.y"
             {(yyval.boolean) = true;}
#line 2112 "yacc_sql.cpp"
    break;

  case 48: /* is_null: NOT NULL_T  */
#line 457 "yacc_sql.y"
                 {(yyval.boolean) = false;}
#line 2118 "yacc_sql.cpp"
    break;

  case 49: /* number: NUMBER  */
#line 461 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2124 "yacc_sql.cpp"
    break;

  case 50: /* type: INT_T  */
#line 464 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2130 "yacc_sql.cpp"
    break;

  case 51: /* type: STRING_T  */
#line 465 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2136 "yacc_sql.cpp"
    break;

  case 52: /* type: FLOAT_T  */
#line 466 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2142 "yacc_sql.cpp"
    break;

  case 53: /* date_type: DATE_T  */
#line 469 "yacc_sql.y"
             {(yyval.number) = static_cast<int>(AttrType::DATES);}
#line 2148 "yacc_sql.cpp"
    break;

  case 54: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 474 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-2].string);
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].values_list));
        std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
        delete (yyvsp[0].values_list);
      }

      free((yyvsp[-2].string));
    }
#line 2164 "yacc_sql.cpp"
    break;

  case 55: /* values_list: LBRACE value_list RBRACE  */
#line 489 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(move(*(yyvsp[-1].value_list)));
      delete (yyvsp[-1].value_list);
    }
#line 2174 "yacc_sql.cpp"
    break;

  case 56: /* values_list: LBRACE value_list RBRACE COMMA values_list  */
#line 495 "yacc_sql.y"
    {
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.values_list) = (yyvsp[0].values_list);
      } else {
        (yyval.values_list) = new std::vector<std::vector<Value>>;
      }

      (yyval.values_list)->emplace_back(move(*(yyvsp[-3].value_list)));
      delete (yyvsp[-3].value_list);
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 57: /* value_list: value  */
#line 508 "yacc_sql.y"
          {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(move(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 58: /* value_list: value COMMA value_list  */
#line 513 "yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace((yyval.value_list)->begin(), move(*(yyvsp[-2].value)));
      delete (yyvsp[-2].value);
    }
#line 2213 "yacc_sql.cpp"
    break;

  case 59: /* value: NUMBER  */
#line 524 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 60: /* value: FLOAT  */
#line 528 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2231 "yacc_sql.cpp"
    break;

  case 61: /* value: SSS  */
#line 532 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2242 "yacc_sql.cpp"
    break;

  case 62: /* value: DATE_VALUE  */
#line 538 "yacc_sql.y"
                {
      int len = strlen((yyvsp[0].string))-2;
      char *tmp = common::substr((yyvsp[0].string),1,len);
      (yyval.value) = new Value((Date*)tmp, len);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2254 "yacc_sql.cpp"
    break;

  case 63: /* value: NULL_T  */
#line 545 "yacc_sql.y"
            {
      (yyval.value) = new Value((void*)nullptr);
    }
#line 2262 "yacc_sql.cpp"
    break;

  case 64: /* storage_format: %empty  */
#line 551 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2270 "yacc_sql.cpp"
    break;

  case 65: /* storage_format: STORAGE FORMAT EQ ID  */
#line 555 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2278 "yacc_sql.cpp"
    break;

  case 66: /* delete_stmt: DELETE FROM ID where  */
#line 562 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        swap((yyval.sql_node)->deletion.conditions, *(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 67: /* update_stmt: UPDATE ID SET key_values where  */
#line 574 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.attribute_names.swap((yyvsp[-1].key_values)->relation_list);
      (yyval.sql_node)->update.values.swap((yyvsp[-1].key_values)->value_list);

      delete (yyvsp[-1].key_values);
      free((yyvsp[-3].string));

      if((yyvsp[0].condition_list) != nullptr){
        swap((yyval.sql_node)->update.conditions, *(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
    }
#line 2311 "yacc_sql.cpp"
    break;

  case 68: /* key_values: ID EQ assign_value  */
#line 592 "yacc_sql.y"
    {
      (yyval.key_values) = new Key_values;
      (yyval.key_values)->relation_list.emplace_back(move((yyvsp[-2].string)));
      free((yyvsp[-2].string));
      (yyval.key_values)->value_list.emplace_back(move(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 69: /* key_values: ID EQ assign_value COMMA key_values  */
#line 600 "yacc_sql.y"
    {
      if ((yyvsp[0].key_values) != nullptr) {
        (yyval.key_values) = (yyvsp[0].key_values);
      } else {
        (yyval.key_values) = new Key_values;
      }

      (yyval.key_values)->relation_list.emplace_back(move((yyvsp[-4].string)));
      free((yyvsp[-4].string));
      (yyval.key_values)->value_list.emplace_back(move(*(yyvsp[-2].value)));
      delete (yyvsp[-2].value);
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 70: /* assign_value: value  */
#line 615 "yacc_sql.y"
          { (yyval.value) = (yyvsp[0].value); }
#line 2346 "yacc_sql.cpp"
    break;

  case 71: /* assign_value: LBRACE select_stmt RBRACE  */
#line 617 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[-1].sql_node));
    }
#line 2354 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT expression_list FROM rel_list where group_by having_node order_by  */
#line 624 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-4].join_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap((yyvsp[-4].join_list)->relation_list);
        swap((yyval.sql_node)->selection.conditions, (yyvsp[-4].join_list)->condition_list);
        delete (yyvsp[-4].join_list);
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        auto& conditions = (yyval.sql_node)->selection.conditions;
        if(conditions.conditions.size()){
          conditions.conditions.insert(conditions.conditions.begin(),
            (yyvsp[-3].condition_list)->conditions.begin(), (yyvsp[-3].condition_list)->conditions.end());
          conditions.and_or = (yyvsp[-3].condition_list)->and_or;
        }
        else swap(conditions, *(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if ((yyvsp[-1].having_list) != nullptr) {
        swap((yyval.sql_node)->selection.having_list, *(yyvsp[-1].having_list));
        delete (yyvsp[-1].having_list);
      }

      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
    }
#line 2398 "yacc_sql.cpp"
    break;

  case 73: /* calc_stmt: CALC expression_list  */
#line 667 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2408 "yacc_sql.cpp"
    break;

  case 74: /* expression_list: expression  */
#line 676 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back(move((yyvsp[0].expression)));
    }
#line 2417 "yacc_sql.cpp"
    break;

  case 75: /* expression_list: expression COMMA expression_list  */
#line 681 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), move((yyvsp[-2].expression)));
    }
#line 2430 "yacc_sql.cpp"
    break;

  case 76: /* expression: expression '+' expression  */
#line 691 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2438 "yacc_sql.cpp"
    break;

  case 77: /* expression: expression '-' expression  */
#line 694 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2446 "yacc_sql.cpp"
    break;

  case 78: /* expression: expression '*' expression  */
#line 697 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2454 "yacc_sql.cpp"
    break;

  case 79: /* expression: expression '/' expression  */
#line 700 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2462 "yacc_sql.cpp"
    break;

  case 80: /* expression: LBRACE expression RBRACE  */
#line 703 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2471 "yacc_sql.cpp"
    break;

  case 81: /* expression: '-' expression  */
#line 707 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2479 "yacc_sql.cpp"
    break;

  case 82: /* expression: value  */
#line 710 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2489 "yacc_sql.cpp"
    break;

  case 83: /* expression: rel_attr  */
#line 715 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2500 "yacc_sql.cpp"
    break;

  case 84: /* expression: '*'  */
#line 721 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2508 "yacc_sql.cpp"
    break;

  case 85: /* expression: ID LBRACE expression_list RBRACE  */
#line 724 "yacc_sql.y"
                                       {
      if((yyvsp[-1].expression_list)->size() != 1)(yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      else (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression_list)->at(0).release(), sql_string, &(yyloc));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].expression_list);
    }
#line 2519 "yacc_sql.cpp"
    break;

  case 86: /* expression: ID LBRACE RBRACE  */
#line 730 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      free((yyvsp[-2].string));
    }
#line 2528 "yacc_sql.cpp"
    break;

  case 87: /* rel_attr: ID  */
#line 738 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 88: /* rel_attr: ID DOT ID  */
#line 743 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2550 "yacc_sql.cpp"
    break;

  case 89: /* rel_attr: ID DOT '*'  */
#line 750 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 90: /* relation: ID  */
#line 759 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2569 "yacc_sql.cpp"
    break;

  case 91: /* rel_list: relation  */
#line 764 "yacc_sql.y"
             {
      (yyval.join_list) = new Joins;
      (yyval.join_list)->relation_list.push_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2579 "yacc_sql.cpp"
    break;

  case 92: /* rel_list: relation COMMA rel_list  */
#line 769 "yacc_sql.y"
                              {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
      }

      (yyval.join_list)->relation_list.insert((yyval.join_list)->relation_list.begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2594 "yacc_sql.cpp"
    break;

  case 93: /* rel_list: relation join_list  */
#line 779 "yacc_sql.y"
                         {
      (yyval.join_list) = new Joins;

      (yyval.join_list)->relation_list.emplace_back(move((yyvsp[-1].string)));
      (yyval.join_list)->relation_list.insert((yyval.join_list)->relation_list.end(),
        (yyvsp[0].join_list)->relation_list.begin(), (yyvsp[0].join_list)->relation_list.end());

      auto& conditions = (yyval.join_list)->condition_list.conditions;
      conditions.insert(conditions.begin(),
        (yyvsp[0].join_list)->condition_list.conditions.begin(), (yyvsp[0].join_list)->condition_list.conditions.end());

      delete (yyvsp[0].join_list);
      free((yyvsp[-1].string));
    }
#line 2613 "yacc_sql.cpp"
    break;

  case 94: /* rel_list: relation join_list COMMA rel_list  */
#line 793 "yacc_sql.y"
                                       {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
      }

      (yyval.join_list)->relation_list.insert((yyval.join_list)->relation_list.begin(),
        (yyvsp[-2].join_list)->relation_list.begin(), (yyvsp[-2].join_list)->relation_list.end());
      (yyval.join_list)->relation_list.insert((yyval.join_list)->relation_list.begin(), (yyvsp[-3].string));

      auto& conditions = (yyval.join_list)->condition_list.conditions;
      conditions.insert(conditions.begin(),
        (yyvsp[-2].join_list)->condition_list.conditions.begin(), (yyvsp[-2].join_list)->condition_list.conditions.end());

      delete (yyvsp[-2].join_list);
      free((yyvsp[-3].string));
    }
#line 2636 "yacc_sql.cpp"
    break;

  case 95: /* join_list: INNER JOIN relation on  */
#line 815 "yacc_sql.y"
    {
      (yyval.join_list) = new Joins;
      (yyval.join_list)->relation_list.emplace_back(move((yyvsp[-1].string)));

      free((yyvsp[-1].string));
      if((yyvsp[0].condition_list) != nullptr){
        auto& conditions = (yyval.join_list)->condition_list.conditions;
        conditions.insert(conditions.end(), (yyvsp[0].condition_list)->conditions.begin(), (yyvsp[0].condition_list)->conditions.end());
        delete (yyvsp[0].condition_list);
      }

    }
#line 2653 "yacc_sql.cpp"
    break;

  case 96: /* join_list: INNER JOIN relation on join_list  */
#line 828 "yacc_sql.y"
    {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
      }

      (yyval.join_list)->relation_list.emplace((yyval.join_list)->relation_list.begin(), move((yyvsp[-2].string)));
      free((yyvsp[-2].string));

      if((yyvsp[-1].condition_list) != nullptr){
        auto& conditions = (yyval.join_list)->condition_list.conditions;
        conditions.insert(conditions.end(), (yyvsp[-1].condition_list)->conditions.begin(), (yyvsp[-1].condition_list)->conditions.end());
        delete (yyvsp[-1].condition_list);
      }
    }
#line 2674 "yacc_sql.cpp"
    break;

  case 97: /* on: %empty  */
#line 848 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2682 "yacc_sql.cpp"
    break;

  case 98: /* on: ON condition_list  */
#line 852 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2690 "yacc_sql.cpp"
    break;

  case 99: /* where: %empty  */
#line 860 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2698 "yacc_sql.cpp"
    break;

  case 100: /* where: WHERE condition_list  */
#line 863 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2706 "yacc_sql.cpp"
    break;

  case 101: /* condition_list: %empty  */
#line 869 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 102: /* condition_list: condition  */
#line 872 "yacc_sql.y"
                {
      (yyval.condition_list) = new Conditions;
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[0].condition)));
      delete (yyvsp[0].condition);
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 103: /* condition_list: condition AND condition_list  */
#line 877 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 104: /* condition_list: condition OR condition_list  */
#line 882 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->and_or = true;
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 105: /* condition: rel_attr comp_op value  */
#line 891 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_type = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2761 "yacc_sql.cpp"
    break;

  case 106: /* condition: value comp_op value  */
#line 903 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_type = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2777 "yacc_sql.cpp"
    break;

  case 107: /* condition: rel_attr comp_op rel_attr  */
#line 915 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_type = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 108: /* condition: value comp_op rel_attr  */
#line 927 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_type = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2809 "yacc_sql.cpp"
    break;

  case 109: /* condition: rel_attr comp_op LBRACE select_stmt RBRACE  */
#line 939 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].rel_attr);
    }
#line 2824 "yacc_sql.cpp"
    break;

  case 110: /* condition: value comp_op LBRACE select_stmt RBRACE  */
#line 950 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 0;
      (yyval.condition)->left_value = *(yyvsp[-4].value);
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].value);
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 111: /* condition: unary_op LBRACE select_stmt RBRACE  */
#line 961 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->left_type = 0;
      (yyval.condition)->left_value = Value((void*)nullptr);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2852 "yacc_sql.cpp"
    break;

  case 112: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 970 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 2;
      (yyval.condition)->left_select = unique_ptr<ParsedSqlNode>((yyvsp[-5].sql_node));
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2865 "yacc_sql.cpp"
    break;

  case 113: /* condition: LBRACE select_stmt RBRACE comp_op value  */
#line 979 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 2;
      (yyval.condition)->left_select = unique_ptr<ParsedSqlNode>((yyvsp[-3].sql_node));
      (yyval.condition)->right_type = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 114: /* condition: LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 990 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 2;
      (yyval.condition)->left_select = unique_ptr<ParsedSqlNode>((yyvsp[-3].sql_node));
      (yyval.condition)->right_type = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 115: /* condition: rel_attr comp_op LBRACE value_list RBRACE  */
#line 1001 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_type = 3;
      (yyval.condition)->right_value_list.swap(*(yyvsp[-1].value_list));
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].rel_attr);
      delete (yyvsp[-1].value_list);
    }
#line 2911 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: LIKE  */
#line 1015 "yacc_sql.y"
         { (yyval.comp) = LIKE_OP; }
#line 2917 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: NOT LIKE  */
#line 1016 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE; }
#line 2923 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: EQ  */
#line 1017 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2929 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: LT  */
#line 1018 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2935 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: GT  */
#line 1019 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2941 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: LE  */
#line 1020 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2947 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: GE  */
#line 1021 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2953 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: NE  */
#line 1022 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2959 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: IN  */
#line 1023 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2965 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: NOT IN  */
#line 1024 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 2971 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: IS  */
#line 1025 "yacc_sql.y"
         { (yyval.comp) = IS_NULL; }
#line 2977 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: IS NOT  */
#line 1026 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_NULL; }
#line 2983 "yacc_sql.cpp"
    break;

  case 128: /* unary_op: EXISTS  */
#line 1030 "yacc_sql.y"
           { (yyval.comp) = EXISTS_OP; }
#line 2989 "yacc_sql.cpp"
    break;

  case 129: /* unary_op: NOT EXISTS  */
#line 1031 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS; }
#line 2995 "yacc_sql.cpp"
    break;

  case 130: /* group_by: %empty  */
#line 1037 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3003 "yacc_sql.cpp"
    break;

  case 131: /* group_by: GROUP BY expression_list  */
#line 1041 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3011 "yacc_sql.cpp"
    break;

  case 132: /* having_node: %empty  */
#line 1048 "yacc_sql.y"
    {
      (yyval.having_list) = nullptr;
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 133: /* having_node: HAVING having_list  */
#line 1052 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
    }
#line 3027 "yacc_sql.cpp"
    break;

  case 134: /* having_list: having_unit  */
#line 1059 "yacc_sql.y"
    {
      (yyval.having_list) = new HavingNode;
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[0].expression)));
    }
#line 3036 "yacc_sql.cpp"
    break;

  case 135: /* having_list: having_unit OR having_list  */
#line 1064 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[-2].expression)));
      (yyval.having_list)->and_or = true;
    }
#line 3046 "yacc_sql.cpp"
    break;

  case 136: /* having_list: having_unit AND having_list  */
#line 1070 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[-2].expression)));
    }
#line 3055 "yacc_sql.cpp"
    break;

  case 137: /* having_unit: expression comp_op expression  */
#line 1078 "yacc_sql.y"
    {
      unique_ptr<Expression> left((yyvsp[-2].expression));
      unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3065 "yacc_sql.cpp"
    break;

  case 138: /* order_by: %empty  */
#line 1087 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3073 "yacc_sql.cpp"
    break;

  case 139: /* order_by: ORDER BY order_by_list  */
#line 1091 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3081 "yacc_sql.cpp"
    break;

  case 140: /* order_by_list: order_by_unit  */
#line 1098 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderByNode>;
      (yyval.order_by_list)->emplace_back(move(*(yyvsp[0].order_by_unit)));
      delete (yyvsp[0].order_by_unit);
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 141: /* order_by_list: order_by_unit COMMA order_by_list  */
#line 1104 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else {
        (yyval.order_by_list) = new std::vector<OrderByNode>;
      }
      (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), move(*(yyvsp[-2].order_by_unit)));
      delete (yyvsp[-2].order_by_unit);
    }
#line 3105 "yacc_sql.cpp"
    break;

  case 142: /* order_by_unit: expression  */
#line 1117 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = (yyvsp[0].expression);
    }
#line 3115 "yacc_sql.cpp"
    break;

  case 143: /* order_by_unit: expression ASC  */
#line 1123 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = (yyvsp[-1].expression);
    }
#line 3125 "yacc_sql.cpp"
    break;

  case 144: /* order_by_unit: expression DESC  */
#line 1129 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = false;
      (yyval.order_by_unit)->expression = (yyvsp[-1].expression);
    }
#line 3135 "yacc_sql.cpp"
    break;

  case 145: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1138 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3149 "yacc_sql.cpp"
    break;

  case 146: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1151 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3158 "yacc_sql.cpp"
    break;

  case 147: /* set_variable_stmt: SET ID EQ value  */
#line 1159 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3170 "yacc_sql.cpp"
    break;


#line 3174 "yacc_sql.cpp"

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
  *++yylsp = yyloc;

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
          = {yyssp, yytoken, &yylloc};
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
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
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

#line 1171 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
