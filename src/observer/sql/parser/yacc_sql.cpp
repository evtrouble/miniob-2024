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
  YYSYMBOL_VIEW = 13,                      /* VIEW  */
  YYSYMBOL_TABLES = 14,                    /* TABLES  */
  YYSYMBOL_INDEX = 15,                     /* INDEX  */
  YYSYMBOL_CALC = 16,                      /* CALC  */
  YYSYMBOL_SELECT = 17,                    /* SELECT  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_UPDATE = 22,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 26,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 27,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 28,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 29,                     /* INT_T  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 32,                    /* DATE_T  */
  YYSYMBOL_VECTOR_T = 33,                  /* VECTOR_T  */
  YYSYMBOL_TEXT_T = 34,                    /* TEXT_T  */
  YYSYMBOL_HELP = 35,                      /* HELP  */
  YYSYMBOL_EXIT = 36,                      /* EXIT  */
  YYSYMBOL_DOT = 37,                       /* DOT  */
  YYSYMBOL_INTO = 38,                      /* INTO  */
  YYSYMBOL_VALUES = 39,                    /* VALUES  */
  YYSYMBOL_FROM = 40,                      /* FROM  */
  YYSYMBOL_WHERE = 41,                     /* WHERE  */
  YYSYMBOL_INNER = 42,                     /* INNER  */
  YYSYMBOL_JOIN = 43,                      /* JOIN  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_OR = 45,                        /* OR  */
  YYSYMBOL_SET = 46,                       /* SET  */
  YYSYMBOL_ON = 47,                        /* ON  */
  YYSYMBOL_AS = 48,                        /* AS  */
  YYSYMBOL_LOAD = 49,                      /* LOAD  */
  YYSYMBOL_DATA = 50,                      /* DATA  */
  YYSYMBOL_LIKE = 51,                      /* LIKE  */
  YYSYMBOL_NULL_T = 52,                    /* NULL_T  */
  YYSYMBOL_EXISTS = 53,                    /* EXISTS  */
  YYSYMBOL_IN = 54,                        /* IN  */
  YYSYMBOL_IS = 55,                        /* IS  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_INFILE = 57,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 58,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 59,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 60,                    /* FORMAT  */
  YYSYMBOL_EQ = 61,                        /* EQ  */
  YYSYMBOL_LT = 62,                        /* LT  */
  YYSYMBOL_GT = 63,                        /* GT  */
  YYSYMBOL_LE = 64,                        /* LE  */
  YYSYMBOL_GE = 65,                        /* GE  */
  YYSYMBOL_NE = 66,                        /* NE  */
  YYSYMBOL_UNIQUE = 67,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 68,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 69,                     /* FLOAT  */
  YYSYMBOL_ID = 70,                        /* ID  */
  YYSYMBOL_SSS = 71,                       /* SSS  */
  YYSYMBOL_DATE_VALUE = 72,                /* DATE_VALUE  */
  YYSYMBOL_73_ = 73,                       /* '+'  */
  YYSYMBOL_74_ = 74,                       /* '-'  */
  YYSYMBOL_75_ = 75,                       /* '*'  */
  YYSYMBOL_76_ = 76,                       /* '/'  */
  YYSYMBOL_UMINUS = 77,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_commands = 79,                  /* commands  */
  YYSYMBOL_command_wrapper = 80,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 81,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 82,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 83,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 84,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 85,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 86,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 87,           /* drop_table_stmt  */
  YYSYMBOL_show_index_stmt = 88,           /* show_index_stmt  */
  YYSYMBOL_show_tables_stmt = 89,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 90,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 91,         /* create_index_stmt  */
  YYSYMBOL_unique_option = 92,             /* unique_option  */
  YYSYMBOL_drop_index_stmt = 93,           /* drop_index_stmt  */
  YYSYMBOL_create_view_stmt = 94,          /* create_view_stmt  */
  YYSYMBOL_col_list = 95,                  /* col_list  */
  YYSYMBOL_create_table_stmt = 96,         /* create_table_stmt  */
  YYSYMBOL_as_option = 97,                 /* as_option  */
  YYSYMBOL_attr_def_list = 98,             /* attr_def_list  */
  YYSYMBOL_attr_def = 99,                  /* attr_def  */
  YYSYMBOL_nullable = 100,                 /* nullable  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_date_type = 103,                /* date_type  */
  YYSYMBOL_insert_stmt = 104,              /* insert_stmt  */
  YYSYMBOL_values_list = 105,              /* values_list  */
  YYSYMBOL_value_list = 106,               /* value_list  */
  YYSYMBOL_value = 107,                    /* value  */
  YYSYMBOL_storage_format = 108,           /* storage_format  */
  YYSYMBOL_delete_stmt = 109,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 110,              /* update_stmt  */
  YYSYMBOL_key_values = 111,               /* key_values  */
  YYSYMBOL_assign_value = 112,             /* assign_value  */
  YYSYMBOL_select_stmt = 113,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 114,                /* calc_stmt  */
  YYSYMBOL_expression_list = 115,          /* expression_list  */
  YYSYMBOL_expression = 116,               /* expression  */
  YYSYMBOL_rel_attr = 117,                 /* rel_attr  */
  YYSYMBOL_relation = 118,                 /* relation  */
  YYSYMBOL_rel_list = 119,                 /* rel_list  */
  YYSYMBOL_join_list = 120,                /* join_list  */
  YYSYMBOL_alias = 121,                    /* alias  */
  YYSYMBOL_on = 122,                       /* on  */
  YYSYMBOL_where = 123,                    /* where  */
  YYSYMBOL_condition_list = 124,           /* condition_list  */
  YYSYMBOL_condition = 125,                /* condition  */
  YYSYMBOL_comp_op = 126,                  /* comp_op  */
  YYSYMBOL_unary_op = 127,                 /* unary_op  */
  YYSYMBOL_group_by = 128,                 /* group_by  */
  YYSYMBOL_having_node = 129,              /* having_node  */
  YYSYMBOL_having_list = 130,              /* having_list  */
  YYSYMBOL_having_unit = 131,              /* having_unit  */
  YYSYMBOL_order_by = 132,                 /* order_by  */
  YYSYMBOL_order_by_list = 133,            /* order_by_list  */
  YYSYMBOL_order_by_unit = 134,            /* order_by_unit  */
  YYSYMBOL_load_data_stmt = 135,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 136,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 137,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 138             /* opt_semicolon  */
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
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   268

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  262

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
       2,     2,    75,    73,     2,    74,     2,    76,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   241,   241,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   276,   282,   287,   293,   299,
     305,   311,   317,   325,   331,   339,   354,   357,   362,   373,
     380,   399,   402,   415,   436,   454,   466,   469,   474,   477,
     490,   499,   508,   521,   522,   523,   527,   530,   531,   532,
     533,   534,   537,   541,   556,   562,   576,   586,   603,   607,
     611,   618,   625,   631,   634,   641,   653,   671,   678,   693,
     697,   742,   751,   760,   775,   778,   781,   784,   787,   796,
     799,   805,   808,   814,   818,   821,   830,   835,   842,   851,
     856,   872,   903,   906,   933,   936,   939,   945,   948,   957,
     960,   965,   970,   975,   983,   990,  1000,  1001,  1002,  1003,
    1004,  1005,  1006,  1007,  1008,  1009,  1010,  1011,  1015,  1016,
    1022,  1025,  1033,  1036,  1043,  1048,  1054,  1062,  1072,  1075,
    1082,  1088,  1101,  1107,  1113,  1122,  1135,  1143,  1153,  1154
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
  "VIEW", "TABLES", "INDEX", "CALC", "SELECT", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "VECTOR_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "INNER", "JOIN", "AND", "OR", "SET", "ON", "AS", "LOAD", "DATA",
  "LIKE", "NULL_T", "EXISTS", "IN", "IS", "NOT", "INFILE", "EXPLAIN",
  "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE", "NE", "UNIQUE",
  "NUMBER", "FLOAT", "ID", "SSS", "DATE_VALUE", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_index_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "unique_option",
  "drop_index_stmt", "create_view_stmt", "col_list", "create_table_stmt",
  "as_option", "attr_def_list", "attr_def", "nullable", "number", "type",
  "date_type", "insert_stmt", "values_list", "value_list", "value",
  "storage_format", "delete_stmt", "update_stmt", "key_values",
  "assign_value", "select_stmt", "calc_stmt", "expression_list",
  "expression", "rel_attr", "relation", "rel_list", "join_list", "alias",
  "on", "where", "condition_list", "condition", "comp_op", "unary_op",
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

#define YYPACT_NINF (-176)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-47)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     188,    -3,    39,   -33,    80,    80,     3,  -176,     5,    12,
       9,  -176,  -176,  -176,  -176,  -176,    18,    15,   188,    67,
      70,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,    27,    32,  -176,    60,    34,    40,  -176,
      24,  -176,  -176,  -176,    -2,  -176,  -176,    80,  -176,  -176,
    -176,    66,  -176,    41,  -176,    95,    68,    73,    91,    98,
     103,  -176,  -176,  -176,  -176,   -10,    -9,    92,  -176,   114,
     145,   147,   -12,   -41,  -176,   104,  -176,    80,    80,    80,
      80,   154,   110,   111,   133,   141,   117,    37,   118,   121,
    -176,   171,   122,   171,   148,   127,  -176,  -176,  -176,   174,
    -176,  -176,  -176,    25,    25,  -176,  -176,    80,  -176,   -28,
     141,  -176,   177,    59,  -176,   140,   141,  -176,   164,    -6,
     186,  -176,   187,  -176,   143,  -176,  -176,  -176,   175,   211,
      80,  -176,  -176,   166,   102,  -176,    76,    80,    80,  -176,
     208,  -176,  -176,  -176,  -176,  -176,  -176,    -8,    -7,   121,
     197,   152,   201,   203,   184,   204,   224,   221,   207,    11,
    -176,  -176,  -176,   176,    23,  -176,  -176,  -176,  -176,  -176,
    -176,    80,    59,    59,    43,   210,    43,   163,   168,  -176,
     189,  -176,  -176,   186,     2,   187,   190,   169,   110,   110,
      80,    80,   232,   217,    80,  -176,  -176,  -176,    43,  -176,
    -176,   117,  -176,  -176,   219,  -176,  -176,   185,   171,  -176,
    -176,   171,   220,   -28,  -176,  -176,   102,  -176,    78,   243,
    -176,   177,  -176,  -176,    -7,   191,  -176,  -176,  -176,   202,
      80,    80,    80,    80,  -176,  -176,   178,    59,   175,    43,
    -176,  -176,    -5,  -176,   225,  -176,  -176,  -176,  -176,  -176,
      80,  -176
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    36,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     148,    24,    23,    16,    17,    18,    19,     9,    10,    12,
      13,    14,    15,    11,     8,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,    37,     0,     0,     0,    34,
       0,    72,    68,    69,    96,    70,    71,     0,    91,    95,
      81,   104,    90,     0,    33,     0,     0,     0,     0,     0,
       0,   146,     1,   149,     2,    46,     0,     0,    31,     0,
       0,     0,     0,     0,    89,     0,   105,     0,     0,     0,
       0,    82,     0,     0,     0,   109,     0,     0,     0,     0,
      47,     0,     0,     0,     0,     0,    94,    88,    93,     0,
      97,    98,   106,    84,    85,    86,    87,     0,    99,   104,
     109,    32,     0,     0,    75,     0,   109,   147,     0,     0,
      48,    45,    41,    39,     0,    38,    92,    83,   102,   130,
       0,    63,   128,     0,     0,   110,   111,     0,     0,    76,
       0,    57,    58,    59,    62,    60,    61,    53,    53,     0,
       0,     0,     0,     0,     0,   100,     0,   132,     0,    66,
     129,   116,   124,   126,     0,   118,   119,   120,   121,   122,
     123,     0,     0,     0,   115,    77,    79,     0,     0,    54,
       0,    51,    52,    48,    73,    41,     0,     0,     0,     0,
       0,     0,   138,    64,     0,   127,   117,   125,   114,   112,
     113,     0,   145,    56,     0,    55,    49,     0,     0,    43,
      42,     0,     0,   104,   101,   131,     0,   133,   134,     0,
      80,     0,    67,    78,    53,     0,    44,    40,    35,   107,
       0,     0,     0,     0,    65,    50,     0,     0,   102,   137,
     136,   135,   142,   139,   140,    74,   108,   103,   143,   144,
       0,   141
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -176,  -176,   233,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,    58,  -176,    61,
      63,    99,  -154,  -176,  -176,  -176,  -176,    26,    50,   162,
    -176,  -176,  -176,    49,  -176,   -48,  -176,    -4,   -57,  -176,
      64,    62,    16,  -116,  -176,  -104,  -175,  -176,    42,  -176,
    -176,  -176,   -96,  -176,  -176,     6,  -176,  -176,  -176,  -176,
    -176
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    46,    32,    33,   162,    34,   101,
     160,   130,   191,   214,   157,   158,    35,   141,   168,    59,
     219,    36,    37,   126,   185,    38,    39,    60,    61,    62,
     119,   120,   165,    91,   248,   124,   145,   146,   181,   147,
     167,   202,   227,   228,   230,   253,   254,    40,    41,    42,
      74
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    63,    80,   138,   192,   258,   259,   209,   210,    43,
      44,    50,   108,    99,   102,   188,   139,    64,    65,   -46,
      85,    82,   149,   151,   152,   153,   154,   155,   156,   110,
     113,   114,   115,   116,   111,    83,   204,    49,   100,   103,
      51,     5,    86,    66,   189,   189,    81,    50,   190,   190,
     100,    47,    67,   131,    48,   133,    52,    53,    54,    55,
      56,   217,    57,    58,    45,    70,   144,    72,    87,    88,
      89,    90,   256,    73,   206,    77,    51,   207,   109,    68,
     245,    92,    50,   169,    87,    88,    89,    90,    69,    51,
     184,   186,    52,    53,    54,    55,    56,    75,    57,    58,
      89,    90,    76,    50,    78,    52,    53,   239,    55,    56,
      79,    51,   142,   137,    85,   143,    87,    88,    89,    90,
     182,   183,   241,   242,   208,   144,   144,    52,    53,    54,
      55,    56,    51,    57,    58,    93,    86,    96,    94,    87,
      88,    89,    90,    95,   226,   250,   251,   169,    52,    53,
      54,    55,    56,   171,    57,    58,   172,   173,   174,    97,
      98,   105,   104,   175,   176,   177,   178,   179,   180,   106,
     236,   107,   122,   237,   112,    87,    88,    89,    90,   117,
     118,   121,   123,   249,   226,   226,   252,   125,     5,   128,
     144,   129,   132,     1,     2,   134,   225,   135,   136,     3,
     140,   148,   150,   252,     4,     5,     6,     7,     8,     9,
      10,   159,   161,   163,    11,    12,    13,   164,   166,   170,
     187,   194,   195,    14,    15,   196,   197,   198,   200,   199,
     201,   203,   205,   212,    16,   211,   213,    17,   221,   222,
     229,   215,   231,   234,   238,   235,    18,   243,   255,   247,
     260,    71,   246,   220,   232,   218,   216,   244,   193,   127,
     233,   224,   223,     0,   257,     0,   261,     0,   240
};

static const yytype_int16 yycheck[] =
{
      57,     5,    50,   119,   158,    10,    11,   182,   183,    12,
      13,    23,    24,    23,    23,    23,   120,    14,    15,    17,
      48,    23,   126,    29,    30,    31,    32,    33,    34,    70,
      87,    88,    89,    90,    75,    37,    25,    70,    48,    48,
      52,    17,    70,    38,    52,    52,    50,    23,    56,    56,
      48,    12,    40,   101,    15,   103,    68,    69,    70,    71,
      72,    59,    74,    75,    67,    50,   123,     0,    73,    74,
      75,    76,   247,     3,    51,    15,    52,    54,    82,    70,
     234,    40,    23,   140,    73,    74,    75,    76,    70,    52,
     147,   148,    68,    69,    70,    71,    72,    70,    74,    75,
      75,    76,    70,    23,    70,    68,    69,   223,    71,    72,
      70,    52,    53,   117,    48,    56,    73,    74,    75,    76,
      44,    45,    44,    45,   181,   182,   183,    68,    69,    70,
      71,    72,    52,    74,    75,    40,    70,    46,    70,    73,
      74,    75,    76,    70,   201,   241,   242,   204,    68,    69,
      70,    71,    72,    51,    74,    75,    54,    55,    56,    61,
      57,    47,    70,    61,    62,    63,    64,    65,    66,    24,
     218,    24,    39,   221,    70,    73,    74,    75,    76,    25,
      70,    70,    41,   240,   241,   242,   243,    70,    17,    71,
     247,    70,    70,     5,     6,    47,   200,    70,    24,    11,
      23,    61,    38,   260,    16,    17,    18,    19,    20,    21,
      22,    25,    25,    70,    26,    27,    28,    42,     7,    53,
      12,    24,    70,    35,    36,    24,    23,    43,     4,    25,
       9,    24,    56,    70,    46,    25,    68,    49,    48,    70,
       8,    52,    25,    24,    24,    60,    58,     4,    70,    47,
      25,    18,    61,   195,   204,   194,   193,   231,   159,    97,
     211,   199,   198,    -1,   248,    -1,   260,    -1,   226
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    11,    16,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    35,    36,    46,    49,    58,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    93,    94,    96,   104,   109,   110,   113,   114,
     135,   136,   137,    12,    13,    67,    92,    12,    15,    70,
      23,    52,    68,    69,    70,    71,    72,    74,    75,   107,
     115,   116,   117,   115,    14,    15,    38,    40,    70,    70,
      50,    80,     0,     3,   138,    70,    70,    15,    70,    70,
     113,   115,    23,    37,   116,    48,    70,    73,    74,    75,
      76,   121,    40,    40,    70,    70,    46,    61,    57,    23,
      48,    97,    23,    48,    70,    47,    24,    24,    24,   115,
      70,    75,    70,   116,   116,   116,   116,    25,    70,   118,
     119,    70,    39,    41,   123,    70,   111,   107,    71,    70,
      99,   113,    70,   113,    47,    70,    24,   115,   121,   123,
      23,   105,    53,    56,   116,   124,   125,   127,    61,   123,
      38,    29,    30,    31,    32,    33,    34,   102,   103,    25,
      98,    25,    95,    70,    42,   120,     7,   128,   106,   116,
      53,    51,    54,    55,    56,    61,    62,    63,    64,    65,
      66,   126,    44,    45,   116,   112,   116,    12,    23,    52,
      56,   100,   100,    99,    24,    70,    24,    23,    43,    25,
       4,     9,   129,    24,    25,    56,    51,    54,   116,   124,
     124,    25,    70,    68,   101,    52,    98,    59,    97,   108,
      95,    48,    70,   118,   119,   115,   116,   130,   131,     8,
     132,    25,   106,   111,    24,    60,   113,   113,    24,   121,
     126,    44,    45,     4,   105,   100,    61,    47,   122,   116,
     130,   130,   116,   133,   134,    70,   124,   120,    10,    11,
      25,   133
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    92,    93,    94,
      94,    95,    95,    96,    96,    96,    97,    97,    98,    98,
      99,    99,    99,   100,   100,   100,   101,   102,   102,   102,
     102,   102,   103,   104,   105,   105,   106,   106,   107,   107,
     107,   107,   107,   108,   108,   109,   110,   111,   111,   112,
     113,   114,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   117,   117,   118,
     119,   119,   120,   120,   121,   121,   121,   122,   122,   123,
     123,   124,   124,   124,   125,   125,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   130,   131,   132,   132,
     133,   133,   134,   134,   134,   135,   136,   137,   138,   138
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     2,     2,     9,     0,     1,     5,     5,
       9,     0,     3,     8,     9,     5,     0,     1,     0,     3,
       6,     3,     3,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     5,     3,     5,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     4,     5,     3,     5,     1,
       8,     2,     2,     4,     3,     3,     3,     3,     3,     2,
       1,     1,     4,     3,     3,     1,     1,     3,     3,     1,
       3,     5,     0,     6,     0,     1,     2,     0,     2,     0,
       2,     1,     3,     3,     3,     2,     1,     2,     1,     1,
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
#line 242 "yacc_sql.y"
  {
    if((yyvsp[-1].sql_node) != nullptr){
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    }
  }
#line 1856 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 276 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1865 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 282 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1873 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 287 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 293 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 299 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1897 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 305 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1905 "yacc_sql.cpp"
    break;

  case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 311 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1915 "yacc_sql.cpp"
    break;

  case 32: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 318 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 33: /* show_tables_stmt: SHOW TABLES  */
#line 325 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1933 "yacc_sql.cpp"
    break;

  case 34: /* desc_table_stmt: DESC ID  */
#line 331 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1943 "yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE unique_option INDEX ID ON ID LBRACE ID RBRACE  */
#line 340 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.unique = (yyvsp[-7].boolean);
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.attribute_name = (yyvsp[-1].string);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 1959 "yacc_sql.cpp"
    break;

  case 36: /* unique_option: %empty  */
#line 354 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 1967 "yacc_sql.cpp"
    break;

  case 37: /* unique_option: UNIQUE  */
#line 358 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 363 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1987 "yacc_sql.cpp"
    break;

  case 39: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 374 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 1998 "yacc_sql.cpp"
    break;

  case 40: /* create_view_stmt: CREATE VIEW ID LBRACE ID col_list RBRACE AS select_stmt  */
#line 381 "yacc_sql.y"
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
    }
#line 2017 "yacc_sql.cpp"
    break;

  case 41: /* col_list: %empty  */
#line 399 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2025 "yacc_sql.cpp"
    break;

  case 42: /* col_list: COMMA ID col_list  */
#line 403 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 43: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 416 "yacc_sql.y"
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
#line 2064 "yacc_sql.cpp"
    break;

  case 44: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_option select_stmt  */
#line 437 "yacc_sql.y"
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
#line 2086 "yacc_sql.cpp"
    break;

  case 45: /* create_table_stmt: CREATE TABLE ID as_option select_stmt  */
#line 455 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 46: /* as_option: %empty  */
#line 466 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2106 "yacc_sql.cpp"
    break;

  case 47: /* as_option: AS  */
#line 469 "yacc_sql.y"
         { (yyval.boolean) = true; }
#line 2112 "yacc_sql.cpp"
    break;

  case 48: /* attr_def_list: %empty  */
#line 474 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2120 "yacc_sql.cpp"
    break;

  case 49: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 478 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(move(*(yyvsp[-1].attr_info)));
      delete (yyvsp[-1].attr_info);
    }
#line 2134 "yacc_sql.cpp"
    break;

  case 50: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 491 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 51: /* attr_def: ID type nullable  */
#line 500 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2160 "yacc_sql.cpp"
    break;

  case 52: /* attr_def: ID date_type nullable  */
#line 509 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 10;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2173 "yacc_sql.cpp"
    break;

  case 53: /* nullable: %empty  */
#line 521 "yacc_sql.y"
    {(yyval.boolean) = false;}
#line 2179 "yacc_sql.cpp"
    break;

  case 54: /* nullable: NULL_T  */
#line 522 "yacc_sql.y"
             {(yyval.boolean) = true;}
#line 2185 "yacc_sql.cpp"
    break;

  case 55: /* nullable: NOT NULL_T  */
#line 523 "yacc_sql.y"
                 {(yyval.boolean) = false;}
#line 2191 "yacc_sql.cpp"
    break;

  case 56: /* number: NUMBER  */
#line 527 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2197 "yacc_sql.cpp"
    break;

  case 57: /* type: INT_T  */
#line 530 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2203 "yacc_sql.cpp"
    break;

  case 58: /* type: STRING_T  */
#line 531 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2209 "yacc_sql.cpp"
    break;

  case 59: /* type: FLOAT_T  */
#line 532 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2215 "yacc_sql.cpp"
    break;

  case 60: /* type: VECTOR_T  */
#line 533 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2221 "yacc_sql.cpp"
    break;

  case 61: /* type: TEXT_T  */
#line 534 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS);}
#line 2227 "yacc_sql.cpp"
    break;

  case 62: /* date_type: DATE_T  */
#line 537 "yacc_sql.y"
             {(yyval.number) = static_cast<int>(AttrType::DATES);}
#line 2233 "yacc_sql.cpp"
    break;

  case 63: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 542 "yacc_sql.y"
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
#line 2249 "yacc_sql.cpp"
    break;

  case 64: /* values_list: LBRACE value_list RBRACE  */
#line 557 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(move(*(yyvsp[-1].value_list)));
      delete (yyvsp[-1].value_list);
    }
#line 2259 "yacc_sql.cpp"
    break;

  case 65: /* values_list: LBRACE value_list RBRACE COMMA values_list  */
#line 563 "yacc_sql.y"
    {
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.values_list) = (yyvsp[0].values_list);
      } else {
        (yyval.values_list) = new std::vector<std::vector<Value>>;
      }

      (yyval.values_list)->emplace_back(move(*(yyvsp[-3].value_list)));
      delete (yyvsp[-3].value_list);
    }
#line 2274 "yacc_sql.cpp"
    break;

  case 66: /* value_list: expression  */
#line 576 "yacc_sql.y"
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
#line 2289 "yacc_sql.cpp"
    break;

  case 67: /* value_list: expression COMMA value_list  */
#line 586 "yacc_sql.y"
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
#line 2309 "yacc_sql.cpp"
    break;

  case 68: /* value: NUMBER  */
#line 603 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 69: /* value: FLOAT  */
#line 607 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2327 "yacc_sql.cpp"
    break;

  case 70: /* value: SSS  */
#line 611 "yacc_sql.y"
         {
      int len = strlen((yyvsp[0].string))-2;
      char *tmp = common::substr((yyvsp[0].string),1,len);
      (yyval.value) = new Value(tmp, len);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2339 "yacc_sql.cpp"
    break;

  case 71: /* value: DATE_VALUE  */
#line 618 "yacc_sql.y"
                {
      int len = strlen((yyvsp[0].string))-2;
      char *tmp = common::substr((yyvsp[0].string),1,len);
      (yyval.value) = new Value((Date*)tmp, len);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2351 "yacc_sql.cpp"
    break;

  case 72: /* value: NULL_T  */
#line 625 "yacc_sql.y"
            {
      (yyval.value) = new Value((void*)nullptr);
    }
#line 2359 "yacc_sql.cpp"
    break;

  case 73: /* storage_format: %empty  */
#line 631 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2367 "yacc_sql.cpp"
    break;

  case 74: /* storage_format: STORAGE FORMAT EQ ID  */
#line 635 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 75: /* delete_stmt: DELETE FROM ID where  */
#line 642 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        swap((yyval.sql_node)->deletion.conditions, *(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2389 "yacc_sql.cpp"
    break;

  case 76: /* update_stmt: UPDATE ID SET key_values where  */
#line 654 "yacc_sql.y"
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
#line 2408 "yacc_sql.cpp"
    break;

  case 77: /* key_values: ID EQ assign_value  */
#line 672 "yacc_sql.y"
    {
      (yyval.key_values) = new Key_values;
      (yyval.key_values)->relation_list.emplace_back(move((yyvsp[-2].string)));
      free((yyvsp[-2].string));
      (yyval.key_values)->value_list.emplace_back(unique_ptr<Expression>((yyvsp[0].expression)));
    }
#line 2419 "yacc_sql.cpp"
    break;

  case 78: /* key_values: ID EQ assign_value COMMA key_values  */
#line 679 "yacc_sql.y"
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
#line 2435 "yacc_sql.cpp"
    break;

  case 79: /* assign_value: expression  */
#line 693 "yacc_sql.y"
               { (yyval.expression) = (yyvsp[0].expression); }
#line 2441 "yacc_sql.cpp"
    break;

  case 80: /* select_stmt: SELECT expression_list FROM rel_list where group_by having_node order_by  */
#line 698 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-4].join_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap((yyvsp[-4].join_list)->relation_list);
        (yyval.sql_node)->selection.alias.swap((yyvsp[-4].join_list)->alias_list);
        swap((yyval.sql_node)->selection.conditions, (yyvsp[-4].join_list)->condition_list);
        delete (yyvsp[-4].join_list);
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        auto& conditions = (yyval.sql_node)->selection.conditions;
        if(conditions.conditions.size()){
          conditions.conditions.insert(conditions.conditions.begin(),
            std::make_move_iterator((yyvsp[-3].condition_list)->conditions.begin()), 
            std::make_move_iterator((yyvsp[-3].condition_list)->conditions.end()));
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
#line 2487 "yacc_sql.cpp"
    break;

  case 81: /* calc_stmt: CALC expression_list  */
#line 743 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2497 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression alias  */
#line 752 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back(move((yyvsp[-1].expression)));
    }
#line 2510 "yacc_sql.cpp"
    break;

  case 83: /* expression_list: expression alias COMMA expression_list  */
#line 761 "yacc_sql.y"
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
#line 2527 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '+' expression  */
#line 775 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2535 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '-' expression  */
#line 778 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2543 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '*' expression  */
#line 781 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2551 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '/' expression  */
#line 784 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 88: /* expression: LBRACE expression_list RBRACE  */
#line 787 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = ((yyvsp[-1].expression_list)->front()).release();
      } else {
        (yyval.expression) = new ValueListExpr(*(yyvsp[-1].expression_list));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2573 "yacc_sql.cpp"
    break;

  case 89: /* expression: '-' expression  */
#line 796 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2581 "yacc_sql.cpp"
    break;

  case 90: /* expression: rel_attr  */
#line 799 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2592 "yacc_sql.cpp"
    break;

  case 91: /* expression: '*'  */
#line 805 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 92: /* expression: ID LBRACE expression_list RBRACE  */
#line 808 "yacc_sql.y"
                                       {
      if((yyvsp[-1].expression_list)->size() != 1)(yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      else (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression_list)->at(0).release(), sql_string, &(yyloc));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].expression_list);
    }
#line 2611 "yacc_sql.cpp"
    break;

  case 93: /* expression: ID LBRACE RBRACE  */
#line 814 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      free((yyvsp[-2].string));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 94: /* expression: LBRACE select_stmt RBRACE  */
#line 818 "yacc_sql.y"
                                {
      (yyval.expression) = new SelectExpr((yyvsp[-1].sql_node));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 95: /* expression: value  */
#line 821 "yacc_sql.y"
            {
        (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
        (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
        delete (yyvsp[0].value);
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 96: /* rel_attr: ID  */
#line 830 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2648 "yacc_sql.cpp"
    break;

  case 97: /* rel_attr: ID DOT ID  */
#line 835 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 98: /* rel_attr: ID DOT '*'  */
#line 842 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2671 "yacc_sql.cpp"
    break;

  case 99: /* relation: ID  */
#line 851 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 100: /* rel_list: relation alias join_list  */
#line 856 "yacc_sql.y"
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
#line 2700 "yacc_sql.cpp"
    break;

  case 101: /* rel_list: relation alias join_list COMMA rel_list  */
#line 872 "yacc_sql.y"
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
#line 2732 "yacc_sql.cpp"
    break;

  case 102: /* join_list: %empty  */
#line 903 "yacc_sql.y"
    {
      (yyval.join_list) = nullptr;
    }
#line 2740 "yacc_sql.cpp"
    break;

  case 103: /* join_list: INNER JOIN relation alias on join_list  */
#line 907 "yacc_sql.y"
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
#line 2768 "yacc_sql.cpp"
    break;

  case 104: /* alias: %empty  */
#line 933 "yacc_sql.y"
                {
      (yyval.string) = nullptr;
    }
#line 2776 "yacc_sql.cpp"
    break;

  case 105: /* alias: ID  */
#line 936 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2784 "yacc_sql.cpp"
    break;

  case 106: /* alias: AS ID  */
#line 939 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2792 "yacc_sql.cpp"
    break;

  case 107: /* on: %empty  */
#line 945 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2800 "yacc_sql.cpp"
    break;

  case 108: /* on: ON condition_list  */
#line 949 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 109: /* where: %empty  */
#line 957 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2816 "yacc_sql.cpp"
    break;

  case 110: /* where: WHERE condition_list  */
#line 960 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2824 "yacc_sql.cpp"
    break;

  case 111: /* condition_list: condition  */
#line 965 "yacc_sql.y"
              {
      (yyval.condition_list) = new Conditions;
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[0].condition)));
      delete (yyvsp[0].condition);
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 112: /* condition_list: condition AND condition_list  */
#line 970 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 2844 "yacc_sql.cpp"
    break;

  case 113: /* condition_list: condition OR condition_list  */
#line 975 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->and_or = true;
      (yyval.condition_list)->conditions.emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 114: /* condition: expression comp_op expression  */
#line 984 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_expr = unique_ptr<Expression>((yyvsp[-2].expression));
      (yyval.condition)->right_expr = unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 2866 "yacc_sql.cpp"
    break;

  case 115: /* condition: unary_op expression  */
#line 991 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_expr = unique_ptr<Expression>(new ValueExpr(Value((void*)nullptr)));
      (yyval.condition)->right_expr = unique_ptr<Expression>((yyvsp[0].expression));
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 2877 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: LIKE  */
#line 1000 "yacc_sql.y"
         { (yyval.comp) = LIKE_OP; }
#line 2883 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: NOT LIKE  */
#line 1001 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE; }
#line 2889 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: EQ  */
#line 1002 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2895 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: LT  */
#line 1003 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2901 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: GT  */
#line 1004 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2907 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: LE  */
#line 1005 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2913 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: GE  */
#line 1006 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2919 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: NE  */
#line 1007 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2925 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: IN  */
#line 1008 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2931 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: NOT IN  */
#line 1009 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 2937 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: IS  */
#line 1010 "yacc_sql.y"
         { (yyval.comp) = IS_NULL; }
#line 2943 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: IS NOT  */
#line 1011 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_NULL; }
#line 2949 "yacc_sql.cpp"
    break;

  case 128: /* unary_op: EXISTS  */
#line 1015 "yacc_sql.y"
           { (yyval.comp) = EXISTS_OP; }
#line 2955 "yacc_sql.cpp"
    break;

  case 129: /* unary_op: NOT EXISTS  */
#line 1016 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS; }
#line 2961 "yacc_sql.cpp"
    break;

  case 130: /* group_by: %empty  */
#line 1022 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2969 "yacc_sql.cpp"
    break;

  case 131: /* group_by: GROUP BY expression_list  */
#line 1026 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2977 "yacc_sql.cpp"
    break;

  case 132: /* having_node: %empty  */
#line 1033 "yacc_sql.y"
    {
      (yyval.having_list) = nullptr;
    }
#line 2985 "yacc_sql.cpp"
    break;

  case 133: /* having_node: HAVING having_list  */
#line 1037 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 134: /* having_list: having_unit  */
#line 1044 "yacc_sql.y"
    {
      (yyval.having_list) = new HavingNode;
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[0].expression)));
    }
#line 3002 "yacc_sql.cpp"
    break;

  case 135: /* having_list: having_unit OR having_list  */
#line 1049 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[-2].expression)));
      (yyval.having_list)->and_or = true;
    }
#line 3012 "yacc_sql.cpp"
    break;

  case 136: /* having_list: having_unit AND having_list  */
#line 1055 "yacc_sql.y"
    {
      (yyval.having_list) = (yyvsp[0].having_list);
      (yyval.having_list)->having_list.emplace_back(move((yyvsp[-2].expression)));
    }
#line 3021 "yacc_sql.cpp"
    break;

  case 137: /* having_unit: expression comp_op expression  */
#line 1063 "yacc_sql.y"
    {
      unique_ptr<Expression> left((yyvsp[-2].expression));
      unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3031 "yacc_sql.cpp"
    break;

  case 138: /* order_by: %empty  */
#line 1072 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 139: /* order_by: ORDER BY order_by_list  */
#line 1076 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3047 "yacc_sql.cpp"
    break;

  case 140: /* order_by_list: order_by_unit  */
#line 1083 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderByNode>;
      (yyval.order_by_list)->emplace_back(move(*(yyvsp[0].order_by_unit)));
      delete (yyvsp[0].order_by_unit);
    }
#line 3057 "yacc_sql.cpp"
    break;

  case 141: /* order_by_list: order_by_unit COMMA order_by_list  */
#line 1089 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else {
        (yyval.order_by_list) = new std::vector<OrderByNode>;
      }
      (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), move(*(yyvsp[-2].order_by_unit)));
      delete (yyvsp[-2].order_by_unit);
    }
#line 3071 "yacc_sql.cpp"
    break;

  case 142: /* order_by_unit: expression  */
#line 1102 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = unique_ptr<Expression>((yyvsp[0].expression));
    }
#line 3081 "yacc_sql.cpp"
    break;

  case 143: /* order_by_unit: expression ASC  */
#line 1108 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = unique_ptr<Expression>((yyvsp[-1].expression));
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 144: /* order_by_unit: expression DESC  */
#line 1114 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = false;
      (yyval.order_by_unit)->expression = unique_ptr<Expression>((yyvsp[-1].expression));
    }
#line 3101 "yacc_sql.cpp"
    break;

  case 145: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1123 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3115 "yacc_sql.cpp"
    break;

  case 146: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1136 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3124 "yacc_sql.cpp"
    break;

  case 147: /* set_variable_stmt: SET ID EQ value  */
#line 1144 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3136 "yacc_sql.cpp"
    break;


#line 3140 "yacc_sql.cpp"

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

#line 1156 "yacc_sql.y"

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
