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

VectorOperationExpr *create_operation_expression(VectorOperationExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  VectorOperationExpr *expr = new VectorOperationExpr(type, left, right);
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


#line 137 "yacc_sql.cpp"

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
  YYSYMBOL_VIEW = 13,                      /* VIEW  */
  YYSYMBOL_TABLES = 14,                    /* TABLES  */
  YYSYMBOL_INDEX = 15,                     /* INDEX  */
  YYSYMBOL_CALC = 16,                      /* CALC  */
  YYSYMBOL_SELECT = 17,                    /* SELECT  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_WITH = 20,                      /* WITH  */
  YYSYMBOL_INSERT = 21,                    /* INSERT  */
  YYSYMBOL_DELETE = 22,                    /* DELETE  */
  YYSYMBOL_UPDATE = 23,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_LMBRACE = 26,                   /* LMBRACE  */
  YYSYMBOL_RMBRACE = 27,                   /* RMBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 29,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 30,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 31,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 32,                     /* INT_T  */
  YYSYMBOL_STRING_T = 33,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 34,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 35,                    /* DATE_T  */
  YYSYMBOL_VECTOR_T = 36,                  /* VECTOR_T  */
  YYSYMBOL_TEXT_T = 37,                    /* TEXT_T  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_WHERE = 44,                     /* WHERE  */
  YYSYMBOL_INNER = 45,                     /* INNER  */
  YYSYMBOL_JOIN = 46,                      /* JOIN  */
  YYSYMBOL_AND = 47,                       /* AND  */
  YYSYMBOL_OR = 48,                        /* OR  */
  YYSYMBOL_SET = 49,                       /* SET  */
  YYSYMBOL_ON = 50,                        /* ON  */
  YYSYMBOL_AS = 51,                        /* AS  */
  YYSYMBOL_LOAD = 52,                      /* LOAD  */
  YYSYMBOL_DATA = 53,                      /* DATA  */
  YYSYMBOL_LIKE = 54,                      /* LIKE  */
  YYSYMBOL_NULL_T = 55,                    /* NULL_T  */
  YYSYMBOL_EXISTS = 56,                    /* EXISTS  */
  YYSYMBOL_IN = 57,                        /* IN  */
  YYSYMBOL_IS = 58,                        /* IS  */
  YYSYMBOL_NOT = 59,                       /* NOT  */
  YYSYMBOL_INFILE = 60,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 61,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 62,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 63,                    /* FORMAT  */
  YYSYMBOL_LIMIT = 64,                     /* LIMIT  */
  YYSYMBOL_EQ = 65,                        /* EQ  */
  YYSYMBOL_LT = 66,                        /* LT  */
  YYSYMBOL_GT = 67,                        /* GT  */
  YYSYMBOL_LE = 68,                        /* LE  */
  YYSYMBOL_GE = 69,                        /* GE  */
  YYSYMBOL_NE = 70,                        /* NE  */
  YYSYMBOL_UNIQUE = 71,                    /* UNIQUE  */
  YYSYMBOL_L2_DISTANCE = 72,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 73,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 74,             /* INNER_PRODUCT  */
  YYSYMBOL_DISTANCE = 75,                  /* DISTANCE  */
  YYSYMBOL_LISTS = 76,                     /* LISTS  */
  YYSYMBOL_TYPE = 77,                      /* TYPE  */
  YYSYMBOL_PROBES = 78,                    /* PROBES  */
  YYSYMBOL_IVFFLAT = 79,                   /* IVFFLAT  */
  YYSYMBOL_NUMBER = 80,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 81,                     /* FLOAT  */
  YYSYMBOL_ID_KEY = 82,                    /* ID_KEY  */
  YYSYMBOL_SSS = 83,                       /* SSS  */
  YYSYMBOL_DATE_VALUE = 84,                /* DATE_VALUE  */
  YYSYMBOL_85_ = 85,                       /* '+'  */
  YYSYMBOL_86_ = 86,                       /* '-'  */
  YYSYMBOL_87_ = 87,                       /* '*'  */
  YYSYMBOL_88_ = 88,                       /* '/'  */
  YYSYMBOL_UMINUS = 89,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 90,                  /* $accept  */
  YYSYMBOL_commands = 91,                  /* commands  */
  YYSYMBOL_command_wrapper = 92,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 93,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 94,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 95,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 96,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 97,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 98,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 99,           /* drop_table_stmt  */
  YYSYMBOL_show_index_stmt = 100,          /* show_index_stmt  */
  YYSYMBOL_show_tables_stmt = 101,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 102,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 103,        /* create_index_stmt  */
  YYSYMBOL_vector_operation = 104,         /* vector_operation  */
  YYSYMBOL_vector_index_type = 105,        /* vector_index_type  */
  YYSYMBOL_idx_col_list = 106,             /* idx_col_list  */
  YYSYMBOL_col_list = 107,                 /* col_list  */
  YYSYMBOL_unique_option = 108,            /* unique_option  */
  YYSYMBOL_drop_index_stmt = 109,          /* drop_index_stmt  */
  YYSYMBOL_create_view_stmt = 110,         /* create_view_stmt  */
  YYSYMBOL_create_table_stmt = 111,        /* create_table_stmt  */
  YYSYMBOL_as_option = 112,                /* as_option  */
  YYSYMBOL_attr_def_list = 113,            /* attr_def_list  */
  YYSYMBOL_attr_def = 114,                 /* attr_def  */
  YYSYMBOL_nullable = 115,                 /* nullable  */
  YYSYMBOL_number = 116,                   /* number  */
  YYSYMBOL_type = 117,                     /* type  */
  YYSYMBOL_date_type = 118,                /* date_type  */
  YYSYMBOL_insert_stmt = 119,              /* insert_stmt  */
  YYSYMBOL_values_list = 120,              /* values_list  */
  YYSYMBOL_value_list = 121,               /* value_list  */
  YYSYMBOL_value = 122,                    /* value  */
  YYSYMBOL_storage_format = 123,           /* storage_format  */
  YYSYMBOL_delete_stmt = 124,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 125,              /* update_stmt  */
  YYSYMBOL_key_values = 126,               /* key_values  */
  YYSYMBOL_assign_value = 127,             /* assign_value  */
  YYSYMBOL_select_stmt = 128,              /* select_stmt  */
  YYSYMBOL_limit = 129,                    /* limit  */
  YYSYMBOL_calc_stmt = 130,                /* calc_stmt  */
  YYSYMBOL_expression_list = 131,          /* expression_list  */
  YYSYMBOL_expression = 132,               /* expression  */
  YYSYMBOL_ID = 133,                       /* ID  */
  YYSYMBOL_rel_attr = 134,                 /* rel_attr  */
  YYSYMBOL_relation = 135,                 /* relation  */
  YYSYMBOL_rel_list = 136,                 /* rel_list  */
  YYSYMBOL_join_list = 137,                /* join_list  */
  YYSYMBOL_alias = 138,                    /* alias  */
  YYSYMBOL_on = 139,                       /* on  */
  YYSYMBOL_where = 140,                    /* where  */
  YYSYMBOL_condition_list = 141,           /* condition_list  */
  YYSYMBOL_condition = 142,                /* condition  */
  YYSYMBOL_comp_op = 143,                  /* comp_op  */
  YYSYMBOL_unary_op = 144,                 /* unary_op  */
  YYSYMBOL_group_by = 145,                 /* group_by  */
  YYSYMBOL_having_node = 146,              /* having_node  */
  YYSYMBOL_having_list = 147,              /* having_list  */
  YYSYMBOL_having_unit = 148,              /* having_unit  */
  YYSYMBOL_order_by = 149,                 /* order_by  */
  YYSYMBOL_order_by_list = 150,            /* order_by_list  */
  YYSYMBOL_order_by_unit = 151,            /* order_by_unit  */
  YYSYMBOL_load_data_stmt = 152,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 153,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 154,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 155             /* opt_semicolon  */
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
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   404

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  315

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   340


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
       2,     2,    87,    85,     2,    86,     2,    88,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      89
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   270,   270,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   305,   311,   316,   322,   328,
     334,   340,   346,   354,   360,   368,   386,   413,   417,   421,
     428,   432,   435,   449,   452,   465,   468,   473,   484,   491,
     510,   531,   549,   561,   564,   569,   572,   585,   594,   603,
     616,   617,   618,   622,   625,   626,   627,   628,   629,   632,
     636,   658,   664,   678,   688,   705,   709,   713,   720,   727,
     730,   737,   740,   747,   759,   777,   784,   799,   803,   851,
     854,   860,   869,   878,   893,   896,   899,   902,   905,   908,
     917,   920,   926,   929,   935,   939,   942,   951,   952,   957,
     962,   970,   975,   982,   991,   996,  1012,  1043,  1046,  1073,
    1076,  1079,  1086,  1089,  1098,  1101,  1106,  1111,  1116,  1124,
    1131,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,  1149,
    1150,  1151,  1152,  1156,  1157,  1163,  1166,  1174,  1177,  1184,
    1189,  1195,  1203,  1213,  1216,  1223,  1229,  1242,  1248,  1254,
    1263,  1276,  1284,  1294,  1295
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
  "VIEW", "TABLES", "INDEX", "CALC", "SELECT", "SHOW", "SYNC", "WITH",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "LMBRACE", "RMBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "VECTOR_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO",
  "VALUES", "FROM", "WHERE", "INNER", "JOIN", "AND", "OR", "SET", "ON",
  "AS", "LOAD", "DATA", "LIKE", "NULL_T", "EXISTS", "IN", "IS", "NOT",
  "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "LIMIT", "EQ", "LT", "GT",
  "LE", "GE", "NE", "UNIQUE", "L2_DISTANCE", "COSINE_DISTANCE",
  "INNER_PRODUCT", "DISTANCE", "LISTS", "TYPE", "PROBES", "IVFFLAT",
  "NUMBER", "FLOAT", "ID_KEY", "SSS", "DATE_VALUE", "'+'", "'-'", "'*'",
  "'/'", "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_index_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "vector_operation",
  "vector_index_type", "idx_col_list", "col_list", "unique_option",
  "drop_index_stmt", "create_view_stmt", "create_table_stmt", "as_option",
  "attr_def_list", "attr_def", "nullable", "number", "type", "date_type",
  "insert_stmt", "values_list", "value_list", "value", "storage_format",
  "delete_stmt", "update_stmt", "key_values", "assign_value",
  "select_stmt", "limit", "calc_stmt", "expression_list", "expression",
  "ID", "rel_attr", "relation", "rel_list", "join_list", "alias", "on",
  "where", "condition_list", "condition", "comp_op", "unary_op",
  "group_by", "having_node", "having_list", "having_unit", "order_by",
  "order_by_list", "order_by_unit", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-237)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     338,    20,    16,   -39,   255,   255,    78,  -237,   -25,   -22,
     -39,  -237,  -237,  -237,  -237,  -237,   -39,   -24,   338,    35,
      41,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,   -39,   -39,    32,  -237,    38,   -39,   -39,
    -237,  -237,  -237,  -237,  -237,   109,   255,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,   255,  -237,    27,  -237,  -237,
     165,    -6,  -237,    29,  -237,    39,   -39,   -39,    63,    55,
      65,  -237,  -237,  -237,  -237,    -2,    -1,   -39,   -39,  -237,
      77,   111,   114,   113,   -17,  -237,   255,   -39,   255,   255,
     255,   255,  -237,   116,   220,    66,   -39,   -39,   117,   101,
     -39,    74,    73,   -39,  -237,   129,   -39,   129,   110,   118,
     -39,  -237,  -237,  -237,   255,    36,  -237,    18,    18,  -237,
    -237,   255,  -237,   134,  -237,  -237,  -237,    96,   101,  -237,
     -39,   119,   184,  -237,   101,    98,  -237,   128,   143,   166,
    -237,   151,  -237,   -39,   -39,  -237,  -237,   255,  -237,  -237,
     139,   190,   151,   180,  -237,   149,   316,  -237,    61,   255,
    -237,   255,   194,   -39,   182,  -237,  -237,  -237,  -237,  -237,
    -237,    -7,   -29,   -39,   186,   188,   189,     2,   168,   187,
     213,   212,   199,   255,  -237,  -237,  -237,  -237,   167,   -15,
    -237,  -237,  -237,  -237,  -237,  -237,   255,   184,   184,    89,
     197,    89,   -39,   143,     3,   152,  -237,   176,  -237,  -237,
     151,   185,   -39,   -39,  -237,   -39,   -39,   255,   255,   225,
    -237,   224,  -237,  -237,  -237,    89,  -237,  -237,   -39,  -237,
    -237,   192,   129,  -237,  -237,   234,  -237,  -237,   129,   151,
     151,    96,  -237,  -237,   316,  -237,    67,   258,   205,   235,
    -237,   209,  -237,   -29,  -237,   251,   252,   228,   255,   255,
     255,   255,   152,  -237,   180,   -39,  -237,   260,  -237,   184,
     139,    89,  -237,  -237,    -8,  -237,   254,  -237,  -237,  -237,
     259,  -237,  -237,  -237,  -237,   255,   210,  -237,   219,    25,
     261,   211,   221,   208,  -237,   262,   215,   230,   218,   271,
     227,   244,   152,   286,  -237
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    45,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     163,    24,    23,    16,    17,    18,    19,     9,    10,    12,
      13,    14,    15,    11,     8,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,    46,     0,     0,     0,
     108,   109,   110,   107,    34,     0,     0,    79,    37,    38,
      39,    75,    76,    77,    78,     0,   102,     0,   106,    91,
     119,   111,   101,     0,    33,     0,     0,     0,     0,     0,
       0,   161,     1,   164,     2,    53,     0,     0,     0,    31,
       0,     0,     0,     0,    73,   100,     0,     0,     0,     0,
       0,     0,   120,    92,     0,     0,     0,     0,    43,   124,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
       0,   105,    99,    80,     0,     0,   121,    94,    95,    96,
      97,     0,   104,     0,   113,   112,   114,   119,   124,    32,
       0,     0,     0,    83,   124,     0,   162,     0,    55,     0,
      52,    41,    48,     0,     0,    47,    74,     0,    93,   103,
     117,   145,    41,     0,   143,     0,     0,   125,   126,     0,
      84,     0,     0,     0,     0,    64,    65,    66,    69,    67,
      68,    60,    60,     0,     0,     0,     0,     0,     0,   115,
       0,   147,     0,     0,    70,   144,   131,   139,   141,     0,
     133,   134,   135,   136,   137,   138,     0,     0,     0,   130,
      85,    87,     0,    55,    81,     0,    61,     0,    58,    59,
      41,     0,     0,     0,    98,     0,     0,     0,     0,   153,
      44,     0,   142,   132,   140,   129,   127,   128,     0,   160,
      56,     0,     0,    50,    63,     0,    62,    42,     0,    41,
      41,   119,   116,   146,     0,   148,   149,     0,    89,    71,
      86,     0,    51,    60,    49,     0,     0,   122,     0,     0,
       0,     0,     0,    88,     0,     0,    57,     0,    35,     0,
     117,   152,   151,   150,   157,   154,   155,    90,    72,    82,
       0,   123,   118,   158,   159,     0,     0,   156,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -237,  -237,   294,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,    14,  -237,  -154,  -237,  -237,  -237,
    -237,  -237,   100,   102,   144,  -177,  -236,  -237,  -237,  -237,
      42,  -118,   207,  -237,  -237,  -237,    81,  -237,   -54,  -237,
    -237,     7,   -41,    -3,  -237,    95,    97,    44,  -133,  -237,
    -119,  -198,  -237,    68,  -237,  -237,  -237,  -138,  -237,  -237,
      26,  -237,  -237,  -237,  -237,  -237
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    67,   305,   184,   141,    47,    32,
      33,    34,   115,   174,   148,   218,   245,   181,   182,    35,
     194,    93,    68,   243,    36,    37,   144,   210,    38,   273,
      39,    69,    70,    71,    72,   137,   138,   189,   103,   280,
     143,   167,   168,   206,   169,   191,   229,   255,   256,   258,
     285,   286,    40,    41,    42,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,    91,   293,   294,   160,   219,   156,    78,   192,   236,
     237,   124,    73,    79,    50,    94,    76,   215,   104,   161,
     -53,    77,   113,   116,    95,   170,   216,   224,    48,    80,
     217,    49,    43,    44,   105,    82,   287,    51,    52,   233,
      85,    86,   234,    53,    83,    89,    90,    87,   216,   114,
     117,    96,   217,    88,   114,   125,    45,   127,   128,   129,
     130,   150,    92,   152,   157,   241,   247,   102,    98,    99,
     100,   101,   106,   108,   109,   231,   313,    98,    99,   100,
     101,   291,   107,    94,   118,   119,   276,    98,    99,   100,
     101,    46,    74,    75,   126,   265,   266,    58,    59,    60,
      56,   166,   135,   136,   139,   100,   101,   145,   207,   208,
     149,   133,   110,   151,   269,   270,   187,   155,   267,    50,
     111,    98,    99,   100,   101,   112,     5,   120,   209,    57,
     211,   282,   283,    55,   102,    56,   121,   162,   158,   122,
     123,   140,    51,    52,   131,   142,     5,    97,    53,    50,
     185,   186,    94,   134,    61,    62,   147,    63,    64,   159,
     153,   163,    50,   171,    57,   235,   166,   166,   154,   172,
     149,   173,    51,    52,    98,    99,   100,   101,    53,   183,
     220,    58,    59,    60,   188,    51,    52,   254,   262,    61,
      62,    53,    63,    64,   264,    65,    66,   190,   175,   176,
     177,   178,   179,   180,   193,   195,   212,   214,    55,   239,
      56,   221,   222,   223,   225,   226,    97,   227,    50,   249,
     250,   228,   136,   136,   230,   238,   232,   281,   254,   254,
     284,   246,   244,   257,   253,   145,   248,    50,   166,    57,
     164,    51,    52,   165,    55,   132,    56,    53,   102,   259,
      98,    99,   100,   101,   284,   261,    58,    59,    60,   263,
      51,    52,   271,   274,    61,    62,    53,    63,    64,   272,
      65,    66,   289,    50,   275,    57,   277,   278,   279,    55,
     290,    56,   295,   296,   299,   298,   303,   304,   302,   301,
     306,   307,    58,    59,    60,   308,    51,    52,   309,   310,
      61,    62,    53,    63,    64,   311,    65,    66,    50,   312,
      57,   314,    81,   300,   242,   240,   288,   213,   146,   260,
     251,   297,   268,   252,   292,     0,     0,    58,    59,    60,
       0,    51,    52,     0,     0,    61,    62,    53,    63,    64,
       0,    65,    66,     1,     2,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     4,     5,     6,     7,     0,     8,
       9,    10,     0,     0,     0,     0,     0,    11,    12,    13,
     196,     0,     0,   197,   198,   199,    14,    15,     0,     0,
       0,   200,   201,   202,   203,   204,   205,    16,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,    18,
       0,    98,    99,   100,   101
};

static const yytype_int16 yycheck[] =
{
       3,    55,    10,    11,   137,   182,   124,    10,   162,   207,
     208,    28,     5,    16,    53,    56,    41,    24,    24,   138,
      17,    43,    24,    24,    65,   144,    55,    25,    12,    53,
      59,    15,    12,    13,    40,     0,   272,    76,    77,    54,
      43,    44,    57,    82,     3,    48,    49,    15,    55,    51,
      51,    24,    59,    15,    51,    96,    36,    98,    99,   100,
     101,   115,    55,   117,    28,    62,   220,    70,    85,    86,
      87,    88,    43,    76,    77,   193,   312,    85,    86,    87,
      88,   279,    43,   124,    87,    88,   263,    85,    86,    87,
      88,    71,    14,    15,    97,   249,   250,    72,    73,    74,
      26,   142,   105,   106,   107,    87,    88,   110,    47,    48,
     113,   104,    49,   116,    47,    48,   157,   120,   251,    53,
      65,    85,    86,    87,    88,    60,    17,    50,   169,    55,
     171,   269,   270,    24,   137,    26,    25,   140,   131,    25,
      27,    24,    76,    77,    28,    44,    17,    51,    82,    53,
     153,   154,   193,    87,    80,    81,    83,    83,    84,    25,
      50,    42,    53,    65,    55,   206,   207,   208,    50,    41,
     173,    28,    76,    77,    85,    86,    87,    88,    82,    28,
     183,    72,    73,    74,    45,    76,    77,   228,   242,    80,
      81,    82,    83,    84,   248,    86,    87,     7,    32,    33,
      34,    35,    36,    37,    24,    56,    12,    25,    24,   212,
      26,    25,    24,    24,    46,    28,    51,     4,    53,   222,
     223,     9,   225,   226,    25,    28,    59,   268,   269,   270,
     271,    55,    80,     8,   227,   238,    51,    53,   279,    55,
      56,    76,    77,    59,    24,    25,    26,    82,   251,    25,
      85,    86,    87,    88,   295,    63,    72,    73,    74,    25,
      76,    77,     4,    28,    80,    81,    82,    83,    84,    64,
      86,    87,   275,    53,    65,    55,    25,    25,    50,    24,
      20,    26,    28,    24,    65,    75,    65,    79,    77,    28,
      28,    76,    72,    73,    74,    65,    76,    77,    80,    28,
      80,    81,    82,    83,    84,    78,    86,    87,    53,    65,
      55,    25,    18,   299,   214,   213,   274,   173,   111,   238,
     225,   295,   254,   226,   280,    -1,    -1,    72,    73,    74,
      -1,    76,    77,    -1,    -1,    80,    81,    82,    83,    84,
      -1,    86,    87,     5,     6,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    -1,    21,
      22,    23,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      54,    -1,    -1,    57,    58,    59,    38,    39,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70,    49,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    85,    86,    87,    88
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    11,    16,    17,    18,    19,    21,    22,
      23,    29,    30,    31,    38,    39,    49,    52,    61,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   109,   110,   111,   119,   124,   125,   128,   130,
     152,   153,   154,    12,    13,    36,    71,   108,    12,    15,
      53,    76,    77,    82,   133,    24,    26,    55,    72,    73,
      74,    80,    81,    83,    84,    86,    87,   104,   122,   131,
     132,   133,   134,   131,    14,    15,    41,    43,   133,   133,
      53,    92,     0,     3,   155,   133,   133,    15,    15,   133,
     133,   128,   131,   121,   132,   132,    24,    51,    85,    86,
      87,    88,   133,   138,    24,    40,    43,    43,   133,   133,
      49,    65,    60,    24,    51,   112,    24,    51,   133,   133,
      50,    25,    25,    27,    28,   132,   133,   132,   132,   132,
     132,    28,    25,   131,    87,   133,   133,   135,   136,   133,
      24,   107,    44,   140,   126,   133,   122,    83,   114,   133,
     128,   133,   128,    50,    50,   133,   121,    28,   131,    25,
     138,   140,   133,    42,    56,    59,   132,   141,   142,   144,
     140,    65,    41,    28,   113,    32,    33,    34,    35,    36,
      37,   117,   118,    28,   106,   133,   133,   132,    45,   137,
       7,   145,   106,    24,   120,    56,    54,    57,    58,    59,
      65,    66,    67,    68,    69,    70,   143,    47,    48,   132,
     127,   132,    12,   114,    25,    24,    55,    59,   115,   115,
     133,    25,    24,    24,    25,    46,    28,     4,     9,   146,
      25,   121,    59,    54,    57,   132,   141,   141,    28,   133,
     113,    62,   112,   123,    80,   116,    55,   106,    51,   133,
     133,   135,   136,   131,   132,   147,   148,     8,   149,    25,
     126,    63,   128,    25,   128,   106,   106,   138,   143,    47,
      48,     4,    64,   129,    28,    65,   115,    25,    25,    50,
     139,   132,   147,   147,   132,   150,   151,   116,   120,   133,
      20,   141,   137,    10,    11,    28,    24,   150,    75,    65,
     104,    28,    77,    65,    79,   105,    28,    76,    65,    80,
      28,    78,    65,   116,    25
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   103,   104,   104,   104,
     105,   106,   106,   107,   107,   108,   108,   109,   110,   110,
     111,   111,   111,   112,   112,   113,   113,   114,   114,   114,
     115,   115,   115,   116,   117,   117,   117,   117,   117,   118,
     119,   120,   120,   121,   121,   122,   122,   122,   122,   122,
     122,   123,   123,   124,   125,   126,   126,   127,   128,   129,
     129,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   133,   133,
     133,   134,   134,   134,   135,   136,   136,   137,   137,   138,
     138,   138,   139,   139,   140,   140,   141,   141,   141,   142,
     142,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   144,   144,   145,   145,   146,   146,   147,
     147,   147,   148,   149,   149,   150,   150,   151,   151,   151,
     152,   153,   154,   155,   155
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     2,     2,    10,    28,     1,     1,     1,
       1,     0,     3,     0,     4,     0,     1,     5,     5,     9,
       8,     9,     5,     0,     1,     0,     3,     6,     3,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       6,     3,     5,     1,     3,     1,     1,     1,     1,     1,
       3,     0,     4,     4,     5,     3,     5,     1,     9,     0,
       2,     2,     2,     4,     3,     3,     3,     3,     6,     3,
       2,     1,     1,     4,     3,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     5,     0,     6,     0,
       1,     2,     0,     2,     0,     2,     1,     3,     3,     3,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     0,     3,     0,     2,     1,
       3,     3,     3,     0,     3,     1,     3,     1,     2,     2,
       7,     2,     4,     0,     1
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
#line 271 "yacc_sql.y"
  {
    if((yyvsp[-1].sql_node) != nullptr){
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
  }
#line 1938 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 305 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1947 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 311 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1955 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 316 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1963 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 322 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1971 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 328 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1979 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 334 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1987 "yacc_sql.cpp"
    break;

  case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 340 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1997 "yacc_sql.cpp"
    break;

  case 32: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 347 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2007 "yacc_sql.cpp"
    break;

  case 33: /* show_tables_stmt: SHOW TABLES  */
#line 354 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2015 "yacc_sql.cpp"
    break;

  case 34: /* desc_table_stmt: DESC ID  */
#line 360 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2025 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE unique_option INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 369 "yacc_sql.y"
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
#line 2047 "yacc_sql.cpp"
    break;

  case 36: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE ID idx_col_list RBRACE WITH LBRACE DISTANCE EQ vector_operation COMMA TYPE EQ vector_index_type COMMA LISTS EQ NUMBER COMMA PROBES EQ number RBRACE  */
#line 389 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-24].string);
      create_index.relation_name = (yyvsp[-22].string);
      std::vector<std::string> *idx_cols = (yyvsp[-19].relation_list);
      if (nullptr != idx_cols) {
        create_index.attr_names.swap(*idx_cols);
        delete (yyvsp[-19].relation_list);
      }
      create_index.attr_names.emplace_back((yyvsp[-20].string));
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free((yyvsp[-24].string));
      free((yyvsp[-22].string));
      free((yyvsp[-20].string));

      create_index.vector_index.distance = (yyvsp[-13].number);    
      create_index.vector_index.type = (yyvsp[-9].vector_index_type);
      create_index.vector_index.lists = (yyvsp[-5].number);
      create_index.vector_index.probes = (yyvsp[-1].number); 
    }
#line 2073 "yacc_sql.cpp"
    break;

  case 37: /* vector_operation: L2_DISTANCE  */
#line 414 "yacc_sql.y"
    {
      (yyval.number) = (int)VectorOperationExpr::Type::L2_DISTANCE;
    }
#line 2081 "yacc_sql.cpp"
    break;

  case 38: /* vector_operation: COSINE_DISTANCE  */
#line 418 "yacc_sql.y"
    {
      (yyval.number) = (int)VectorOperationExpr::Type::COSINE_DISTANCE;
    }
#line 2089 "yacc_sql.cpp"
    break;

  case 39: /* vector_operation: INNER_PRODUCT  */
#line 422 "yacc_sql.y"
    {
      (yyval.number) = (int)VectorOperationExpr::Type::INNER_PRODUCT;
    }
#line 2097 "yacc_sql.cpp"
    break;

  case 40: /* vector_index_type: IVFFLAT  */
#line 428 "yacc_sql.y"
            { (yyval.vector_index_type) = VectorIndexType::IVFFLAT; }
#line 2103 "yacc_sql.cpp"
    break;

  case 41: /* idx_col_list: %empty  */
#line 432 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2111 "yacc_sql.cpp"
    break;

  case 42: /* idx_col_list: COMMA ID idx_col_list  */
#line 436 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2125 "yacc_sql.cpp"
    break;

  case 43: /* col_list: %empty  */
#line 449 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2133 "yacc_sql.cpp"
    break;

  case 44: /* col_list: LBRACE ID idx_col_list RBRACE  */
#line 453 "yacc_sql.y"
    {
      if ((yyvsp[-1].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[-1].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-2].string));
      free((yyvsp[-2].string));      
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 45: /* unique_option: %empty  */
#line 465 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2155 "yacc_sql.cpp"
    break;

  case 46: /* unique_option: UNIQUE  */
#line 469 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 47: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 474 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2175 "yacc_sql.cpp"
    break;

  case 48: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 485 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 2186 "yacc_sql.cpp"
    break;

  case 49: /* create_view_stmt: CREATE VIEW ID LBRACE ID idx_col_list RBRACE AS select_stmt  */
#line 492 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      (yyval.sql_node)->create_view.view_name = (yyvsp[-6].string);

      std::vector<std::string> &col_names = (yyval.sql_node)->create_view.col_names;
      if (nullptr != (yyvsp[-3].relation_list)) {
        col_names.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }
      col_names.emplace_back((yyvsp[-4].string));
      std::reverse(col_names.begin(), col_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
    }
#line 2206 "yacc_sql.cpp"
    break;

  case 50: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 511 "yacc_sql.y"
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
#line 2231 "yacc_sql.cpp"
    break;

  case 51: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_option select_stmt  */
#line 532 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(move(*(yyvsp[-4].attr_info)));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
    }
#line 2253 "yacc_sql.cpp"
    break;

  case 52: /* create_table_stmt: CREATE TABLE ID as_option select_stmt  */
#line 550 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 2265 "yacc_sql.cpp"
    break;

  case 53: /* as_option: %empty  */
#line 561 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2273 "yacc_sql.cpp"
    break;

  case 54: /* as_option: AS  */
#line 564 "yacc_sql.y"
         { (yyval.boolean) = true; }
#line 2279 "yacc_sql.cpp"
    break;

  case 55: /* attr_def_list: %empty  */
#line 569 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 56: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 573 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(move(*(yyvsp[-1].attr_info)));
      delete (yyvsp[-1].attr_info);
    }
#line 2301 "yacc_sql.cpp"
    break;

  case 57: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 586 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 58: /* attr_def: ID type nullable  */
#line 595 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2327 "yacc_sql.cpp"
    break;

  case 59: /* attr_def: ID date_type nullable  */
#line 604 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 10;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 60: /* nullable: %empty  */
#line 616 "yacc_sql.y"
    { (yyval.boolean) = true; }
#line 2346 "yacc_sql.cpp"
    break;

  case 61: /* nullable: NULL_T  */
#line 617 "yacc_sql.y"
             {(yyval.boolean) = true;}
#line 2352 "yacc_sql.cpp"
    break;

  case 62: /* nullable: NOT NULL_T  */
#line 618 "yacc_sql.y"
                 {(yyval.boolean) = false;}
#line 2358 "yacc_sql.cpp"
    break;

  case 63: /* number: NUMBER  */
#line 622 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2364 "yacc_sql.cpp"
    break;

  case 64: /* type: INT_T  */
#line 625 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2370 "yacc_sql.cpp"
    break;

  case 65: /* type: STRING_T  */
#line 626 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2376 "yacc_sql.cpp"
    break;

  case 66: /* type: FLOAT_T  */
#line 627 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2382 "yacc_sql.cpp"
    break;

  case 67: /* type: VECTOR_T  */
#line 628 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2388 "yacc_sql.cpp"
    break;

  case 68: /* type: TEXT_T  */
#line 629 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS);}
#line 2394 "yacc_sql.cpp"
    break;

  case 69: /* date_type: DATE_T  */
#line 632 "yacc_sql.y"
             {(yyval.number) = static_cast<int>(AttrType::DATES);}
#line 2400 "yacc_sql.cpp"
    break;

  case 70: /* insert_stmt: INSERT INTO ID col_list VALUES values_list  */
#line 637 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-3].string);

      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].values_list));
        std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
        delete (yyvsp[0].values_list);
      }

      if (nullptr != (yyvsp[-2].relation_list)) {
        (yyval.sql_node)->insertion.attrs_name.swap(*(yyvsp[-2].relation_list));
        std::reverse((yyval.sql_node)->insertion.attrs_name.begin(), (yyval.sql_node)->insertion.attrs_name.end());
        delete (yyvsp[-2].relation_list);
      }

      free((yyvsp[-3].string));
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 71: /* values_list: LBRACE value_list RBRACE  */
#line 659 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(move(*(yyvsp[-1].value_list)));
      delete (yyvsp[-1].value_list);
    }
#line 2433 "yacc_sql.cpp"
    break;

  case 72: /* values_list: LBRACE value_list RBRACE COMMA values_list  */
#line 665 "yacc_sql.y"
    {
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.values_list) = (yyvsp[0].values_list);
      } else {
        (yyval.values_list) = new std::vector<std::vector<Value>>;
      }

      (yyval.values_list)->emplace_back(move(*(yyvsp[-3].value_list)));
      delete (yyvsp[-3].value_list);
    }
#line 2448 "yacc_sql.cpp"
    break;

  case 73: /* value_list: expression  */
#line 678 "yacc_sql.y"
               {
      (yyval.value_list) = new std::vector<Value>;
      Value temp;
      if(OB_FAIL((yyvsp[0].expression)->try_get_value(temp))){
        yyerror(&(yyloc), sql_string, sql_result, scanner, "error");
        YYERROR;
      }
      (yyval.value_list)->emplace_back(temp);
      delete (yyvsp[0].expression);
    }
#line 2463 "yacc_sql.cpp"
    break;

  case 74: /* value_list: expression COMMA value_list  */
#line 688 "yacc_sql.y"
                                   {
      Value temp;
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      if(OB_FAIL((yyvsp[-2].expression)->try_get_value(temp))){
        yyerror(&(yyloc), sql_string, sql_result, scanner, "error");
        YYERROR;
      }

      (yyval.value_list)->emplace((yyval.value_list)->begin(), move(temp));
      delete (yyvsp[-2].expression);
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 75: /* value: NUMBER  */
#line 705 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2492 "yacc_sql.cpp"
    break;

  case 76: /* value: FLOAT  */
#line 709 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2501 "yacc_sql.cpp"
    break;

  case 77: /* value: SSS  */
#line 713 "yacc_sql.y"
         {
      int len = strlen((yyvsp[0].string))-2;
      char *tmp = common::substr((yyvsp[0].string),1,len);
      (yyval.value) = new Value(tmp, len);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2513 "yacc_sql.cpp"
    break;

  case 78: /* value: DATE_VALUE  */
#line 720 "yacc_sql.y"
                {
      int len = strlen((yyvsp[0].string))-2;
      char *tmp = common::substr((yyvsp[0].string),1,len);
      (yyval.value) = new Value((Date*)tmp, len);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2525 "yacc_sql.cpp"
    break;

  case 79: /* value: NULL_T  */
#line 727 "yacc_sql.y"
            {
      (yyval.value) = new Value((void*)nullptr);
    }
#line 2533 "yacc_sql.cpp"
    break;

  case 80: /* value: LMBRACE value_list RMBRACE  */
#line 730 "yacc_sql.y"
                                 {
      (yyval.value) = new Value((yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2542 "yacc_sql.cpp"
    break;

  case 81: /* storage_format: %empty  */
#line 737 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2550 "yacc_sql.cpp"
    break;

  case 82: /* storage_format: STORAGE FORMAT EQ ID  */
#line 741 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2558 "yacc_sql.cpp"
    break;

  case 83: /* delete_stmt: DELETE FROM ID where  */
#line 748 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        swap((yyval.sql_node)->deletion.conditions, *(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 84: /* update_stmt: UPDATE ID SET key_values where  */
#line 760 "yacc_sql.y"
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
#line 2591 "yacc_sql.cpp"
    break;

  case 85: /* key_values: ID EQ assign_value  */
#line 778 "yacc_sql.y"
    {
      (yyval.key_values) = new Key_values;
      (yyval.key_values)->relation_list.emplace_back(move((yyvsp[-2].string)));
      free((yyvsp[-2].string));
      (yyval.key_values)->value_list.emplace_back(unique_ptr<Expression>((yyvsp[0].expression)));
    }
#line 2602 "yacc_sql.cpp"
    break;

  case 86: /* key_values: ID EQ assign_value COMMA key_values  */
#line 785 "yacc_sql.y"
    {
      if ((yyvsp[0].key_values) != nullptr) {
        (yyval.key_values) = (yyvsp[0].key_values);
      } else {
        (yyval.key_values) = new Key_values;
      }

      (yyval.key_values)->relation_list.emplace_back(move((yyvsp[-4].string)));
      free((yyvsp[-4].string));
      (yyval.key_values)->value_list.emplace_back(unique_ptr<Expression>((yyvsp[-2].expression)));
    }
#line 2618 "yacc_sql.cpp"
    break;

  case 87: /* assign_value: expression  */
#line 799 "yacc_sql.y"
               { (yyval.expression) = (yyvsp[0].expression); }
#line 2624 "yacc_sql.cpp"
    break;

  case 88: /* select_stmt: SELECT expression_list FROM rel_list where group_by having_node order_by limit  */
#line 804 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].join_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap((yyvsp[-5].join_list)->relation_list);
        (yyval.sql_node)->selection.alias.swap((yyvsp[-5].join_list)->alias_list);
        swap((yyval.sql_node)->selection.conditions, (yyvsp[-5].join_list)->condition_list);
        delete (yyvsp[-5].join_list);
      }

      if ((yyvsp[-4].condition_list) != nullptr) {
        auto& conditions = (yyval.sql_node)->selection.conditions;
        if(conditions.conditions.size()){
          conditions.conditions.insert(conditions.conditions.begin(),
            std::make_move_iterator((yyvsp[-4].condition_list)->conditions.begin()), 
            std::make_move_iterator((yyvsp[-4].condition_list)->conditions.end()));
          conditions.and_or = (yyvsp[-4].condition_list)->and_or;
        }
        else swap(conditions, *(yyvsp[-4].condition_list));
        delete (yyvsp[-4].condition_list);
      }

      if ((yyvsp[-3].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].expression_list));
        delete (yyvsp[-3].expression_list);
      }

      if ((yyvsp[-2].having_list) != nullptr) {
        swap((yyval.sql_node)->selection.having_list, *(yyvsp[-2].having_list));
        delete (yyvsp[-2].having_list);
      }

      if((yyvsp[-1].order_by_list) != nullptr){
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[-1].order_by_list));
        delete (yyvsp[-1].order_by_list);
      }

      (yyval.sql_node)->selection.limit = (yyvsp[0].number);
    }
#line 2672 "yacc_sql.cpp"
    break;

  case 89: /* limit: %empty  */
#line 851 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 2680 "yacc_sql.cpp"
    break;

  case 90: /* limit: LIMIT number  */
#line 855 "yacc_sql.y"
    {
      (yyval.number) = (yyvsp[0].number);
    }
#line 2688 "yacc_sql.cpp"
    break;

  case 91: /* calc_stmt: CALC expression_list  */
#line 861 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2698 "yacc_sql.cpp"
    break;

  case 92: /* expression_list: expression alias  */
#line 870 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back(move((yyvsp[-1].expression)));
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 93: /* expression_list: expression alias COMMA expression_list  */
#line 879 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      if((yyvsp[-2].string) != nullptr){
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
        free((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), move((yyvsp[-3].expression)));
    }
#line 2728 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '+' expression  */
#line 893 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2736 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '-' expression  */
#line 896 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 96: /* expression: expression '*' expression  */
#line 899 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2752 "yacc_sql.cpp"
    break;

  case 97: /* expression: expression '/' expression  */
#line 902 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 98: /* expression: vector_operation LBRACE expression COMMA expression RBRACE  */
#line 905 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_operation_expression((VectorOperationExpr::Type)(yyvsp[-5].number), (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2768 "yacc_sql.cpp"
    break;

  case 99: /* expression: LBRACE expression_list RBRACE  */
#line 908 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = ((yyvsp[-1].expression_list)->front()).release();
      } else {
        (yyval.expression) = new ValueListExpr(*(yyvsp[-1].expression_list));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2782 "yacc_sql.cpp"
    break;

  case 100: /* expression: '-' expression  */
#line 917 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2790 "yacc_sql.cpp"
    break;

  case 101: /* expression: rel_attr  */
#line 920 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2801 "yacc_sql.cpp"
    break;

  case 102: /* expression: '*'  */
#line 926 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2809 "yacc_sql.cpp"
    break;

  case 103: /* expression: ID LBRACE expression_list RBRACE  */
#line 929 "yacc_sql.y"
                                       {
      if((yyvsp[-1].expression_list)->size() != 1)(yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      else (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression_list)->at(0).release(), sql_string, &(yyloc));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].expression_list);
    }
#line 2820 "yacc_sql.cpp"
    break;

  case 104: /* expression: ID LBRACE RBRACE  */
#line 935 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      free((yyvsp[-2].string));
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 105: /* expression: LBRACE select_stmt RBRACE  */
#line 939 "yacc_sql.y"
                                {
      (yyval.expression) = new SelectExpr((yyvsp[-1].sql_node));
    }
#line 2837 "yacc_sql.cpp"
    break;

  case 106: /* expression: value  */
#line 942 "yacc_sql.y"
            {
        (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
        (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
        delete (yyvsp[0].value);
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 107: /* ID: ID_KEY  */
#line 951 "yacc_sql.y"
           { (yyval.string) = (yyvsp[0].string); }
#line 2853 "yacc_sql.cpp"
    break;

  case 108: /* ID: DATA  */
#line 953 "yacc_sql.y"
    {
      (yyval.string) = (char *)malloc(sizeof(char) * 5);
      memcpy((yyval.string), "data", sizeof(char) * 5);
    }
#line 2862 "yacc_sql.cpp"
    break;

  case 109: /* ID: LISTS  */
#line 958 "yacc_sql.y"
    {
      (yyval.string) = (char *)malloc(sizeof(char) * 6);
      memcpy((yyval.string), "lists", sizeof(char) * 6);
    }
#line 2871 "yacc_sql.cpp"
    break;

  case 110: /* ID: TYPE  */
#line 963 "yacc_sql.y"
    {
      (yyval.string) = (char *)malloc(sizeof(char) * 5);
      memcpy((yyval.string), "type", sizeof(char) * 5);
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 111: /* rel_attr: ID  */
#line 970 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 112: /* rel_attr: ID DOT ID  */
#line 975 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2902 "yacc_sql.cpp"
    break;

  case 113: /* rel_attr: ID DOT '*'  */
#line 982 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2913 "yacc_sql.cpp"
    break;

  case 114: /* relation: ID  */
#line 991 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2921 "yacc_sql.cpp"
    break;

  case 115: /* rel_list: relation alias join_list  */
#line 996 "yacc_sql.y"
                             {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
      }

      (yyval.join_list)->relation_list.emplace((yyval.join_list)->relation_list.begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
      if((yyvsp[-1].string) != nullptr){
        (yyval.join_list)->alias_list.emplace((yyval.join_list)->alias_list.begin(), (yyvsp[-1].string));
        free((yyvsp[-1].string));
      } else {
        (yyval.join_list)->alias_list.emplace((yyval.join_list)->alias_list.begin(), string());
      }
    }
#line 2942 "yacc_sql.cpp"
    break;

  case 116: /* rel_list: relation alias join_list COMMA rel_list  */
#line 1012 "yacc_sql.y"
                                             {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
      }

      if((yyvsp[-2].join_list) != nullptr){
        (yyval.join_list)->relation_list.insert((yyval.join_list)->relation_list.begin(), 
          (yyvsp[-2].join_list)->relation_list.begin(), (yyvsp[-2].join_list)->relation_list.end());
        auto& conditions = (yyval.join_list)->condition_list.conditions;
        conditions.insert(conditions.begin(), 
          std::make_move_iterator((yyvsp[-2].join_list)->condition_list.conditions.begin()), 
          std::make_move_iterator((yyvsp[-2].join_list)->condition_list.conditions.end()));
      }

      (yyval.join_list)->relation_list.emplace((yyval.join_list)->relation_list.begin(), (yyvsp[-4].string));
      if((yyvsp[-3].string) != nullptr){
        (yyval.join_list)->alias_list.emplace((yyval.join_list)->alias_list.begin(), (yyvsp[-3].string));
        free((yyvsp[-3].string));
      } else {
        (yyval.join_list)->alias_list.emplace((yyval.join_list)->alias_list.begin(), string());
      }

      delete (yyvsp[-2].join_list);
      free((yyvsp[-4].string));
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 117: /* join_list: %empty  */
#line 1043 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 2982 "yacc_sql.cpp"
    break;

  case 118: /* join_list: INNER JOIN relation alias on join_list  */
#line 1047 "yacc_sql.y"
    {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
      }

      (yyval.join_list)->relation_list.emplace((yyval.join_list)->relation_list.begin(), (yyvsp[-3].string));
      free((yyvsp[-3].string));
      if((yyvsp[-2].string) != nullptr){
        (yyval.join_list)->alias_list.emplace((yyval.join_list)->alias_list.begin(), (yyvsp[-2].string));
        free((yyvsp[-2].string));
      } else {
        (yyval.join_list)->alias_list.emplace((yyval.join_list)->alias_list.begin(), string());
      }

      if((yyvsp[-1].condition_list) != nullptr){
        auto& conditions = (yyval.join_list)->condition_list.conditions;
        conditions.insert(conditions.end(), std::make_move_iterator((yyvsp[-1].condition_list)->conditions.begin()), 
          std::make_move_iterator((yyvsp[-1].condition_list)->conditions.end()));
        delete (yyvsp[-1].condition_list);
      }
    }
#line 3010 "yacc_sql.cpp"
    break;

  case 119: /* alias: %empty  */
#line 1073 "yacc_sql.y"
                {
      (yyval.string) = nullptr;
    }
#line 3018 "yacc_sql.cpp"
    break;

  case 120: /* alias: ID  */
#line 1076 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3026 "yacc_sql.cpp"
    break;

  case 121: /* alias: AS ID  */
#line 1079 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3034 "yacc_sql.cpp"
    break;

  case 122: /* on: %empty  */
#line 1086 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3042 "yacc_sql.cpp"
    break;

  case 123: /* on: ON condition_list  */
#line 1090 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3050 "yacc_sql.cpp"
    break;

  case 124: /* where: %empty  */
#line 1098 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3058 "yacc_sql.cpp"
    break;

  case 125: /* where: WHERE condition_list  */
#line 1101 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3066 "yacc_sql.cpp"
    break;

  case 126: /* condition_list: condition  */
#line 1106 "yacc_sql.y"
              {
      (yyval.condition_list) = new Conditions;
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[0].condition)));
      delete (yyvsp[0].condition);
    }
#line 3076 "yacc_sql.cpp"
    break;

  case 127: /* condition_list: condition AND condition_list  */
#line 1111 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 3086 "yacc_sql.cpp"
    break;

  case 128: /* condition_list: condition OR condition_list  */
#line 1116 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->and_or = true;
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 3097 "yacc_sql.cpp"
    break;

  case 129: /* condition: expression comp_op expression  */
#line 1125 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_expr = unique_ptr<Expression>((yyvsp[-2].expression));
      (yyval.condition)->right_expr = unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 130: /* condition: unary_op expression  */
#line 1132 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_expr = unique_ptr<Expression>(new ValueExpr(Value((void*)nullptr)));
      (yyval.condition)->right_expr = unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3119 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: LIKE  */
#line 1141 "yacc_sql.y"
         { (yyval.comp) = LIKE_OP; }
#line 3125 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: NOT LIKE  */
#line 1142 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE; }
#line 3131 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: EQ  */
#line 1143 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3137 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: LT  */
#line 1144 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3143 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: GT  */
#line 1145 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3149 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: LE  */
#line 1146 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3155 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: GE  */
#line 1147 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3161 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: NE  */
#line 1148 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3167 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: IN  */
#line 1149 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3173 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: NOT IN  */
#line 1150 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 3179 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: IS  */
#line 1151 "yacc_sql.y"
         { (yyval.comp) = IS_NULL; }
#line 3185 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: IS NOT  */
#line 1152 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_NULL; }
#line 3191 "yacc_sql.cpp"
    break;

  case 143: /* unary_op: EXISTS  */
#line 1156 "yacc_sql.y"
           { (yyval.comp) = EXISTS_OP; }
#line 3197 "yacc_sql.cpp"
    break;

  case 144: /* unary_op: NOT EXISTS  */
#line 1157 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS; }
#line 3203 "yacc_sql.cpp"
    break;

  case 145: /* group_by: %empty  */
#line 1163 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3211 "yacc_sql.cpp"
    break;

  case 146: /* group_by: GROUP BY expression_list  */
#line 1167 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3219 "yacc_sql.cpp"
    break;

  case 147: /* having_node: %empty  */
#line 1174 "yacc_sql.y"
    {
      (yyval.having_list) = nullptr;
    }
#line 3227 "yacc_sql.cpp"
    break;

  case 148: /* having_node: HAVING having_list  */
#line 1178 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
    }
#line 3235 "yacc_sql.cpp"
    break;

  case 149: /* having_list: having_unit  */
#line 1185 "yacc_sql.y"
    {
      (yyval.having_list) = new HavingNode;
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[0].expression)));
    }
#line 3244 "yacc_sql.cpp"
    break;

  case 150: /* having_list: having_unit OR having_list  */
#line 1190 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[-2].expression)));
      (yyval.having_list)->and_or = true;
    }
#line 3254 "yacc_sql.cpp"
    break;

  case 151: /* having_list: having_unit AND having_list  */
#line 1196 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[-2].expression)));
    }
#line 3263 "yacc_sql.cpp"
    break;

  case 152: /* having_unit: expression comp_op expression  */
#line 1204 "yacc_sql.y"
    {
      unique_ptr<Expression> left((yyvsp[-2].expression));
      unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3273 "yacc_sql.cpp"
    break;

  case 153: /* order_by: %empty  */
#line 1213 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3281 "yacc_sql.cpp"
    break;

  case 154: /* order_by: ORDER BY order_by_list  */
#line 1217 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3289 "yacc_sql.cpp"
    break;

  case 155: /* order_by_list: order_by_unit  */
#line 1224 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderByNode>;
      (yyval.order_by_list)->emplace_back(move(*(yyvsp[0].order_by_unit)));
      delete (yyvsp[0].order_by_unit);
    }
#line 3299 "yacc_sql.cpp"
    break;

  case 156: /* order_by_list: order_by_unit COMMA order_by_list  */
#line 1230 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else {
        (yyval.order_by_list) = new std::vector<OrderByNode>;
      }
      (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), move(*(yyvsp[-2].order_by_unit)));
      delete (yyvsp[-2].order_by_unit);
    }
#line 3313 "yacc_sql.cpp"
    break;

  case 157: /* order_by_unit: expression  */
#line 1243 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = unique_ptr<Expression>((yyvsp[0].expression));
    }
#line 3323 "yacc_sql.cpp"
    break;

  case 158: /* order_by_unit: expression ASC  */
#line 1249 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = unique_ptr<Expression>((yyvsp[-1].expression));
    }
#line 3333 "yacc_sql.cpp"
    break;

  case 159: /* order_by_unit: expression DESC  */
#line 1255 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = false;
      (yyval.order_by_unit)->expression = unique_ptr<Expression>((yyvsp[-1].expression));
    }
#line 3343 "yacc_sql.cpp"
    break;

  case 160: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1264 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3357 "yacc_sql.cpp"
    break;

  case 161: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1277 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3366 "yacc_sql.cpp"
    break;

  case 162: /* set_variable_stmt: SET ID EQ value  */
#line 1285 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3378 "yacc_sql.cpp"
    break;


#line 3382 "yacc_sql.cpp"

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

#line 1297 "yacc_sql.y"

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
