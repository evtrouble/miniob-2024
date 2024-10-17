/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

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
  YYSYMBOL_TEXT_T = 32,                    /* TEXT_T  */
  YYSYMBOL_HELP = 33,                      /* HELP  */
  YYSYMBOL_EXIT = 34,                      /* EXIT  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_INTO = 36,                      /* INTO  */
  YYSYMBOL_VALUES = 37,                    /* VALUES  */
  YYSYMBOL_FROM = 38,                      /* FROM  */
  YYSYMBOL_WHERE = 39,                     /* WHERE  */
  YYSYMBOL_INNER = 40,                     /* INNER  */
  YYSYMBOL_JOIN = 41,                      /* JOIN  */
  YYSYMBOL_AND = 42,                       /* AND  */
  YYSYMBOL_OR = 43,                        /* OR  */
  YYSYMBOL_SET = 44,                       /* SET  */
  YYSYMBOL_ON = 45,                        /* ON  */
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
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_DATE_VALUE = 68,                /* DATE_VALUE  */
  YYSYMBOL_69_ = 69,                       /* '+'  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '*'  */
  YYSYMBOL_72_ = 72,                       /* '/'  */
  YYSYMBOL_UMINUS = 73,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command_wrapper = 76,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 77,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 78,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 79,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 80,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 81,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 82,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 83,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 84,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 85,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 86,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 87,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 88,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 89,             /* attr_def_list  */
  YYSYMBOL_attr_def = 90,                  /* attr_def  */
  YYSYMBOL_is_null = 91,                   /* is_null  */
  YYSYMBOL_number = 92,                    /* number  */
  YYSYMBOL_type = 93,                      /* type  */
  YYSYMBOL_date_type = 94,                 /* date_type  */
  YYSYMBOL_insert_stmt = 95,               /* insert_stmt  */
  YYSYMBOL_values_list = 96,               /* values_list  */
  YYSYMBOL_value_list = 97,                /* value_list  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_storage_format = 99,            /* storage_format  */
  YYSYMBOL_delete_stmt = 100,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 101,              /* update_stmt  */
  YYSYMBOL_key_values = 102,               /* key_values  */
  YYSYMBOL_assign_value = 103,             /* assign_value  */
  YYSYMBOL_select_stmt = 104,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 105,                /* calc_stmt  */
  YYSYMBOL_expression_list = 106,          /* expression_list  */
  YYSYMBOL_expression = 107,               /* expression  */
  YYSYMBOL_rel_attr = 108,                 /* rel_attr  */
  YYSYMBOL_relation = 109,                 /* relation  */
  YYSYMBOL_rel_list = 110,                 /* rel_list  */
  YYSYMBOL_join_list = 111,                /* join_list  */
  YYSYMBOL_on = 112,                       /* on  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_condition_list = 114,           /* condition_list  */
  YYSYMBOL_condition = 115,                /* condition  */
  YYSYMBOL_comp_op = 116,                  /* comp_op  */
  YYSYMBOL_unary_op = 117,                 /* unary_op  */
  YYSYMBOL_group_by = 118,                 /* group_by  */
  YYSYMBOL_having_list = 119,              /* having_list  */
  YYSYMBOL_order_by = 120,                 /* order_by  */
  YYSYMBOL_order_by_list = 121,            /* order_by_list  */
  YYSYMBOL_order_by_unit = 122,            /* order_by_unit  */
  YYSYMBOL_load_data_stmt = 123,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 124,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 125,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 126             /* opt_semicolon  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  140
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  252

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


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
       2,     2,    71,    69,     2,    70,     2,    72,     2,     2,
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
      65,    66,    67,    68,    73
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   224,   224,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   257,   263,   268,   274,   280,   286,   292,
     299,   305,   313,   327,   337,   361,   364,   377,   386,   395,
     408,   409,   410,   414,   417,   418,   419,   420,   423,   427,
     442,   448,   462,   467,   478,   482,   486,   492,   499,   505,
     508,   515,   527,   545,   553,   569,   570,   577,   614,   623,
     628,   639,   642,   645,   648,   651,   655,   658,   663,   669,
     672,   678,   686,   691,   698,   707,   712,   719,   731,   747,
     770,   784,   806,   809,   818,   821,   827,   830,   835,   840,
     847,   859,   871,   883,   895,   906,   917,   926,   937,   948,
     957,   968,   979,   994,   995,   996,   997,   998,   999,  1000,
    1001,  1002,  1003,  1007,  1008,  1014,  1017,  1025,  1028,  1036,
    1039,  1046,  1052,  1065,  1071,  1077,  1086,  1099,  1107,  1117,
    1118
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
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "INNER",
  "JOIN", "AND", "OR", "SET", "ON", "LOAD", "DATA", "LIKE", "NULL_T",
  "EXISTS", "IN", "IS", "NOT", "INFILE", "EXPLAIN", "STORAGE", "FORMAT",
  "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS",
  "DATE_VALUE", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_index_stmt",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "is_null", "number", "type", "date_type", "insert_stmt", "values_list",
  "value_list", "value", "storage_format", "delete_stmt", "update_stmt",
  "key_values", "assign_value", "select_stmt", "calc_stmt",
  "expression_list", "expression", "rel_attr", "relation", "rel_list",
  "join_list", "on", "where", "condition_list", "condition", "comp_op",
  "unary_op", "group_by", "having_list", "order_by", "order_by_list",
  "order_by_unit", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,    43,
      45,    42,    47,   324
};
#endif

#define YYPACT_NINF (-172)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     114,    14,    33,   -20,   123,   123,    51,  -172,    29,    35,
      12,  -172,  -172,  -172,  -172,  -172,    22,    42,   114,    76,
      93,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,    31,    32,    36,    38,  -172,   123,  -172,  -172,  -172,
      -5,  -172,  -172,   123,  -172,  -172,  -172,   -14,  -172,    61,
    -172,    39,    40,    57,    49,    55,  -172,  -172,  -172,  -172,
      95,    73,  -172,    79,    15,   100,   -48,  -172,   123,   123,
     123,   123,   123,    60,    84,    88,    71,    46,    75,    72,
      77,    78,  -172,  -172,   127,  -172,  -172,  -172,   -51,   -51,
    -172,  -172,  -172,   -11,    88,   124,   131,  -172,    94,    88,
    -172,   115,   204,   130,   133,  -172,  -172,    60,   116,   132,
     152,    46,  -172,   145,  -172,   112,   128,   216,   200,  -172,
      10,   153,   182,  -172,   162,  -172,  -172,  -172,  -172,  -172,
     -10,   -22,    72,   154,   110,  -172,    60,    60,   178,   176,
     169,   177,   179,  -172,  -172,  -172,     3,  -172,  -172,  -172,
    -172,  -172,  -172,   151,    -9,   156,   131,   131,   145,   145,
    -172,   183,   140,   144,  -172,   160,  -172,  -172,   130,   155,
     189,   168,  -172,   123,   131,   206,   213,    46,   216,  -172,
    -172,   145,  -172,  -172,  -172,   181,    26,  -172,  -172,  -172,
    -172,   215,   217,    71,  -172,  -172,   218,  -172,  -172,   185,
    -172,  -172,   131,   199,  -172,  -172,   239,  -172,   124,  -172,
     161,   221,  -172,   222,   231,  -172,  -172,  -172,   -22,   197,
    -172,  -172,   123,  -172,   145,  -172,  -172,  -172,  -172,  -172,
    -172,   190,    -2,  -172,   233,   242,  -172,  -172,  -172,   123,
    -172,  -172
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     139,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,    31,     0,    58,    54,    55,
      82,    56,    57,     0,    79,    77,    68,    69,    78,     0,
      30,     0,     0,     0,     0,     0,   137,     1,   140,     2,
       0,     0,    29,     0,     0,     0,     0,    76,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,    75,    81,     0,    83,    84,    70,    71,    72,
      73,    74,    85,    86,    94,     0,    96,    61,     0,    94,
     138,     0,     0,    35,     0,    33,    80,     0,     0,    88,
     125,     0,    49,     0,   123,     0,    82,     0,     0,    95,
      97,     0,     0,    62,     0,    44,    45,    46,    48,    47,
      40,    40,     0,     0,     0,    87,     0,     0,     0,   127,
       0,    52,     0,   124,   113,   121,     0,   115,   116,   117,
     118,   119,   120,     0,     0,     0,    96,    96,     0,     0,
      65,    63,     0,     0,    41,     0,    38,    39,    35,    59,
       0,    92,    89,     0,    96,   129,    50,     0,     0,   114,
     122,     0,   101,   103,   107,     0,     0,   100,   102,    98,
      99,     0,     0,     0,   136,    43,     0,    42,    36,     0,
      34,    32,    96,    90,   126,   128,     0,    67,     0,    53,
       0,     0,   108,     0,     0,   106,    66,    64,    40,     0,
      93,    91,     0,    51,     0,   110,   111,   105,   112,   104,
      37,     0,   133,   130,   131,     0,    60,   134,   135,     0,
     109,   132
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,   248,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,    90,   129,  -136,  -172,  -172,
    -172,  -172,    52,  -171,   -84,  -172,  -172,  -172,    69,  -172,
    -119,  -172,    -4,   -46,  -104,   134,  -106,    68,  -172,   -85,
    -152,  -172,  -122,  -172,  -172,  -172,  -172,    24,  -172,  -172,
    -172,  -172,  -172
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   143,   113,   176,   206,   140,
     141,    33,   122,   150,    55,   210,    34,    35,   109,   171,
      36,    37,    56,    57,    58,   103,   104,   119,   213,   107,
     129,   130,   163,   131,   149,   185,   217,   243,   244,    38,
      39,    40,    69
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      74,    59,   128,   110,   152,   177,   165,    77,   247,   248,
      78,   145,   173,   117,   199,   200,   219,    75,    95,   120,
      81,    82,   127,    96,   133,   223,    41,   174,    42,   118,
      76,   175,   215,    98,    99,   100,   101,   151,    92,   174,
     194,   182,     5,   175,   195,    43,    45,    44,   170,   201,
     202,   189,   166,   167,   190,    79,    80,    81,    82,   193,
     230,   198,   128,   128,    60,    61,   220,    79,    80,    81,
      82,    94,   221,    62,    97,    47,    67,   224,    63,   192,
     128,   197,   127,   127,    79,    80,    81,    82,    64,    65,
      48,    49,   240,    51,    52,    47,    68,    70,    71,    83,
     127,    86,    72,   151,    73,    84,    85,    87,   128,    88,
      48,    49,   151,    51,    52,   245,   236,    89,    90,     1,
       2,   105,    46,    93,    91,     3,   102,   106,   127,     4,
       5,     6,     7,     8,     9,    10,   235,   108,   112,    11,
      12,    13,   111,   114,   115,    46,   121,    14,    15,    47,
     116,   134,   132,   123,   142,   144,   147,   146,    16,   148,
      17,     5,   153,    76,    48,    49,    50,    51,    52,    18,
      53,    54,    47,   191,   172,   168,   180,   179,   196,   214,
      47,   124,   183,   234,   125,   184,   242,    48,    49,    50,
      51,    52,   186,    53,    54,    48,    49,   126,    51,    52,
      47,   187,   188,   242,   169,    47,   204,   203,   205,   207,
      47,   209,   211,   212,   216,    48,    49,   126,    51,    52,
      48,    49,   126,    51,    52,    48,    49,   126,    51,    52,
     222,    47,   135,   136,   137,   138,   139,   218,   225,   118,
     226,   228,   229,   232,   237,   238,    48,    49,   154,    51,
      52,   155,   164,   156,   239,   241,   246,   249,   157,   158,
     159,   160,   161,   162,   154,   250,    66,   155,   208,   156,
     233,   178,   227,   251,   157,   158,   159,   160,   161,   162,
     181,   231
};

static const yytype_uint8 yycheck[] =
{
      46,     5,   106,    87,   123,   141,   128,    53,    10,    11,
      24,   117,    22,    24,   166,   167,   187,    22,    66,   104,
      71,    72,   106,    71,   109,   196,    12,    49,    14,    40,
      35,    53,   184,    79,    80,    81,    82,   121,    23,    49,
      49,   147,    16,    53,    53,    12,    66,    14,   132,   168,
     169,    48,    42,    43,    51,    69,    70,    71,    72,   163,
     212,   165,   166,   167,    13,    36,   188,    69,    70,    71,
      72,    75,   191,    38,    78,    49,     0,   196,    66,   163,
     184,   165,   166,   167,    69,    70,    71,    72,    66,    47,
      64,    65,   228,    67,    68,    49,     3,    66,    66,    38,
     184,    44,    66,   187,    66,    66,    66,    58,   212,    54,
      64,    65,   196,    67,    68,   234,   220,    22,    45,     5,
       6,    37,    22,    23,    45,    11,    66,    39,   212,    15,
      16,    17,    18,    19,    20,    21,   220,    66,    66,    25,
      26,    27,    67,    66,    66,    22,    22,    33,    34,    49,
      23,    36,    58,    22,    24,    22,    24,    41,    44,     7,
      46,    16,    50,    35,    64,    65,    66,    67,    68,    55,
      70,    71,    49,    22,    12,    22,    66,    23,    22,   183,
      49,    50,     4,    22,    53,     9,   232,    64,    65,    66,
      67,    68,    23,    70,    71,    64,    65,    66,    67,    68,
      49,    24,    23,   249,    22,    49,    66,    24,    64,    49,
      49,    56,    23,    45,     8,    64,    65,    66,    67,    68,
      64,    65,    66,    67,    68,    64,    65,    66,    67,    68,
      49,    49,    28,    29,    30,    31,    32,    24,    23,    40,
      23,    23,    57,     4,    23,    23,    64,    65,    48,    67,
      68,    51,    52,    53,    23,    58,    66,    24,    58,    59,
      60,    61,    62,    63,    48,    23,    18,    51,   178,    53,
     218,   142,   203,   249,    58,    59,    60,    61,    62,    63,
     146,   213
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     6,    11,    15,    16,    17,    18,    19,    20,
      21,    25,    26,    27,    33,    34,    44,    46,    55,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    95,   100,   101,   104,   105,   123,   124,
     125,    12,    14,    12,    14,    66,    22,    49,    64,    65,
      66,    67,    68,    70,    71,    98,   106,   107,   108,   106,
      13,    36,    38,    66,    66,    47,    76,     0,     3,   126,
      66,    66,    66,    66,   107,    22,    35,   107,    24,    69,
      70,    71,    72,    38,    66,    66,    44,    58,    54,    22,
      45,    45,    23,    23,   106,    66,    71,   106,   107,   107,
     107,   107,    66,   109,   110,    37,    39,   113,    66,   102,
      98,    67,    66,    90,    66,    66,    23,    24,    40,   111,
     113,    22,    96,    22,    50,    53,    66,    98,   108,   114,
     115,   117,    58,   113,    36,    28,    29,    30,    31,    32,
      93,    94,    24,    89,    22,   110,    41,    24,     7,   118,
      97,    98,   104,    50,    48,    51,    53,    58,    59,    60,
      61,    62,    63,   116,    52,   116,    42,    43,    22,    22,
      98,   103,    12,    22,    49,    53,    91,    91,    90,    23,
      66,   109,   110,     4,     9,   119,    23,    24,    23,    48,
      51,    22,    98,   108,    49,    53,    22,    98,   108,   114,
     114,   104,   104,    24,    66,    64,    92,    49,    89,    56,
      99,    23,    45,   112,   106,   114,     8,   120,    24,    97,
     116,   104,    49,    97,   104,    23,    23,   102,    23,    57,
     114,   111,     4,    96,    22,    98,   108,    23,    23,    23,
      91,    58,   107,   121,   122,   104,    66,    10,    11,    24,
      23,   121
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    89,    90,    90,    90,
      91,    91,    91,    92,    93,    93,    93,    93,    94,    95,
      96,    96,    97,    97,    98,    98,    98,    98,    98,    99,
      99,   100,   101,   102,   102,   103,   103,   104,   105,   106,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   108,   109,   110,   110,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   114,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   122,   123,   124,   125,   126,
     126
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     5,     8,     0,     3,     6,     3,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     5,
       3,     5,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     4,     5,     3,     5,     1,     3,     8,     2,     1,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       4,     3,     1,     3,     3,     1,     1,     3,     2,     4,
       4,     5,     0,     2,     0,     2,     0,     1,     3,     3,
       3,     3,     3,     3,     5,     5,     4,     3,     4,     7,
       5,     5,     5,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     0,     3,     0,     2,     0,
       3,     1,     3,     1,     2,     2,     7,     2,     4,     0,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


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
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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

  YY_LOCATION_PRINT (yyo, *yylocationp);
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
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 225 "yacc_sql.y"
  {
    if((yyvsp[-1].sql_node) != nullptr){
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      sql_result->add_sql_node(std::move(sql_node));
    } 
  }
#line 1825 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 257 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1834 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 263 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1842 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 268 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1850 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 274 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1858 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 280 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1866 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 286 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1874 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 292 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1884 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 299 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1892 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 305 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1902 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID RBRACE  */
#line 314 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.attribute_name = (yyvsp[-1].string);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 1917 "yacc_sql.cpp"
    break;

  case 33: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 328 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1929 "yacc_sql.cpp"
    break;

  case 34: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 338 "yacc_sql.y"
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
#line 1954 "yacc_sql.cpp"
    break;

  case 35: /* attr_def_list: %empty  */
#line 361 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 365 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(move(*(yyvsp[-1].attr_info)));
      delete (yyvsp[-1].attr_info);
    }
#line 1976 "yacc_sql.cpp"
    break;

  case 37: /* attr_def: ID type LBRACE number RBRACE is_null  */
#line 378 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->is_null = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 1989 "yacc_sql.cpp"
    break;

  case 38: /* attr_def: ID type is_null  */
#line 387 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->is_null = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID date_type is_null  */
#line 396 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 10;
      (yyval.attr_info)->is_null = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2015 "yacc_sql.cpp"
    break;

  case 40: /* is_null: %empty  */
#line 408 "yacc_sql.y"
    {(yyval.boolean) = false;}
#line 2021 "yacc_sql.cpp"
    break;

  case 41: /* is_null: NULL_T  */
#line 409 "yacc_sql.y"
             {(yyval.boolean) = true;}
#line 2027 "yacc_sql.cpp"
    break;

  case 42: /* is_null: NOT NULL_T  */
#line 410 "yacc_sql.y"
                 {(yyval.boolean) = false;}
#line 2033 "yacc_sql.cpp"
    break;

  case 43: /* number: NUMBER  */
#line 414 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2039 "yacc_sql.cpp"
    break;

  case 44: /* type: INT_T  */
#line 417 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2045 "yacc_sql.cpp"
    break;

  case 45: /* type: STRING_T  */
#line 418 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2051 "yacc_sql.cpp"
    break;

  case 46: /* type: FLOAT_T  */
#line 419 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2057 "yacc_sql.cpp"
    break;

  case 47: /* type: TEXT_T  */
#line 420 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS);}
#line 2063 "yacc_sql.cpp"
    break;

  case 48: /* date_type: DATE_T  */
#line 423 "yacc_sql.y"
             {(yyval.number) = static_cast<int>(AttrType::DATES);}
#line 2069 "yacc_sql.cpp"
    break;

  case 49: /* insert_stmt: INSERT INTO ID VALUES values_list  */
#line 428 "yacc_sql.y"
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
#line 2085 "yacc_sql.cpp"
    break;

  case 50: /* values_list: LBRACE value_list RBRACE  */
#line 443 "yacc_sql.y"
    {
      (yyval.values_list) = new std::vector<std::vector<Value>>;
      (yyval.values_list)->emplace_back(move(*(yyvsp[-1].value_list)));
      delete (yyvsp[-1].value_list);
    }
#line 2095 "yacc_sql.cpp"
    break;

  case 51: /* values_list: LBRACE value_list RBRACE COMMA values_list  */
#line 449 "yacc_sql.y"
    {
      if ((yyvsp[0].values_list) != nullptr) {
        (yyval.values_list) = (yyvsp[0].values_list);
      } else {
        (yyval.values_list) = new std::vector<std::vector<Value>>;
      }

      (yyval.values_list)->emplace_back(move(*(yyvsp[-3].value_list)));
      delete (yyvsp[-3].value_list);
    }
#line 2110 "yacc_sql.cpp"
    break;

  case 52: /* value_list: value  */
#line 462 "yacc_sql.y"
          {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(move(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
    }
#line 2120 "yacc_sql.cpp"
    break;

  case 53: /* value_list: value COMMA value_list  */
#line 467 "yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace((yyval.value_list)->begin(), move(*(yyvsp[-2].value)));
      delete (yyvsp[-2].value);
    }
#line 2134 "yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 478 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2143 "yacc_sql.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 482 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2152 "yacc_sql.cpp"
    break;

  case 56: /* value: SSS  */
#line 486 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 57: /* value: DATE_VALUE  */
#line 492 "yacc_sql.y"
                {
      int len = strlen((yyvsp[0].string))-2;
      char *tmp = common::substr((yyvsp[0].string),1,len);
      (yyval.value) = new Value((Date*)tmp, len);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2175 "yacc_sql.cpp"
    break;

  case 58: /* value: NULL_T  */
#line 499 "yacc_sql.y"
            {
      (yyval.value) = new Value((void*)nullptr);
    }
#line 2183 "yacc_sql.cpp"
    break;

  case 59: /* storage_format: %empty  */
#line 505 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2191 "yacc_sql.cpp"
    break;

  case 60: /* storage_format: STORAGE FORMAT EQ ID  */
#line 509 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 61: /* delete_stmt: DELETE FROM ID where  */
#line 516 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2213 "yacc_sql.cpp"
    break;

  case 62: /* update_stmt: UPDATE ID SET key_values where  */
#line 528 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.attribute_names.swap((yyvsp[-1].key_values)->relation_list);
      (yyval.sql_node)->update.values.swap((yyvsp[-1].key_values)->value_list);
      
      delete (yyvsp[-1].key_values);
      free((yyvsp[-3].string));

      if((yyvsp[0].condition_list) != nullptr){
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
    }
#line 2232 "yacc_sql.cpp"
    break;

  case 63: /* key_values: ID EQ assign_value  */
#line 546 "yacc_sql.y"
    {
      (yyval.key_values) = new Key_values;
      (yyval.key_values)->relation_list.emplace_back(move((yyvsp[-2].string)));
      free((yyvsp[-2].string));
      (yyval.key_values)->value_list.emplace_back(move(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
    }
#line 2244 "yacc_sql.cpp"
    break;

  case 64: /* key_values: ID EQ assign_value COMMA key_values  */
#line 554 "yacc_sql.y"
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
#line 2261 "yacc_sql.cpp"
    break;

  case 65: /* assign_value: value  */
#line 569 "yacc_sql.y"
          { (yyval.value) = (yyvsp[0].value); }
#line 2267 "yacc_sql.cpp"
    break;

  case 66: /* assign_value: LBRACE select_stmt RBRACE  */
#line 571 "yacc_sql.y"
    {
      (yyval.value) = new Value((yyvsp[-1].sql_node));
    }
#line 2275 "yacc_sql.cpp"
    break;

  case 67: /* select_stmt: SELECT expression_list FROM rel_list where group_by having_list order_by  */
#line 578 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-4].join_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*((yyvsp[-4].join_list)->relation_list));
        (yyval.sql_node)->selection.conditions.swap(*((yyvsp[-4].join_list)->condition_list));
        delete (yyvsp[-4].join_list)->relation_list;
        delete (yyvsp[-4].join_list)->condition_list;
        delete (yyvsp[-4].join_list);
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        if((yyval.sql_node)->selection.conditions.size())
          (yyval.sql_node)->selection.conditions.insert((yyval.sql_node)->selection.conditions.begin(), 
            (yyvsp[-3].condition_list)->begin(), (yyvsp[-3].condition_list)->end());
        else (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
    }
#line 2313 "yacc_sql.cpp"
    break;

  case 68: /* calc_stmt: CALC expression_list  */
#line 615 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 69: /* expression_list: expression  */
#line 624 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back(move((yyvsp[0].expression)));
    }
#line 2332 "yacc_sql.cpp"
    break;

  case 70: /* expression_list: expression COMMA expression_list  */
#line 629 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), move((yyvsp[-2].expression)));
    }
#line 2345 "yacc_sql.cpp"
    break;

  case 71: /* expression: expression '+' expression  */
#line 639 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2353 "yacc_sql.cpp"
    break;

  case 72: /* expression: expression '-' expression  */
#line 642 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2361 "yacc_sql.cpp"
    break;

  case 73: /* expression: expression '*' expression  */
#line 645 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2369 "yacc_sql.cpp"
    break;

  case 74: /* expression: expression '/' expression  */
#line 648 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2377 "yacc_sql.cpp"
    break;

  case 75: /* expression: LBRACE expression RBRACE  */
#line 651 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2386 "yacc_sql.cpp"
    break;

  case 76: /* expression: '-' expression  */
#line 655 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2394 "yacc_sql.cpp"
    break;

  case 77: /* expression: value  */
#line 658 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2404 "yacc_sql.cpp"
    break;

  case 78: /* expression: rel_attr  */
#line 663 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2415 "yacc_sql.cpp"
    break;

  case 79: /* expression: '*'  */
#line 669 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 80: /* expression: ID LBRACE expression_list RBRACE  */
#line 672 "yacc_sql.y"
                                       {
      if((yyvsp[-1].expression_list)->size() != 1)(yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      else (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression_list)->at(0).release(), sql_string, &(yyloc));
      free((yyvsp[-3].string));
      delete (yyvsp[-1].expression_list);
    }
#line 2434 "yacc_sql.cpp"
    break;

  case 81: /* expression: ID LBRACE RBRACE  */
#line 678 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("", nullptr, sql_string, &(yyloc));
      free((yyvsp[-2].string));
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 82: /* rel_attr: ID  */
#line 686 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 83: /* rel_attr: ID DOT ID  */
#line 691 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2465 "yacc_sql.cpp"
    break;

  case 84: /* rel_attr: ID DOT '*'  */
#line 698 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2476 "yacc_sql.cpp"
    break;

  case 85: /* relation: ID  */
#line 707 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2484 "yacc_sql.cpp"
    break;

  case 86: /* rel_list: relation  */
#line 712 "yacc_sql.y"
             {
      (yyval.join_list) = new Joins;
      (yyval.join_list)->relation_list = new std::vector<std::string>;
      (yyval.join_list)->condition_list = new std::vector<ConditionSqlNode>;
      (yyval.join_list)->relation_list->push_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2496 "yacc_sql.cpp"
    break;

  case 87: /* rel_list: relation COMMA rel_list  */
#line 719 "yacc_sql.y"
                              {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
        (yyval.join_list)->relation_list = new std::vector<std::string>;
        (yyval.join_list)->condition_list = new std::vector<ConditionSqlNode>;
      }

      (yyval.join_list)->relation_list->insert((yyval.join_list)->relation_list->begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2513 "yacc_sql.cpp"
    break;

  case 88: /* rel_list: relation join_list  */
#line 731 "yacc_sql.y"
                         {
      (yyval.join_list) = new Joins;
      (yyval.join_list)->relation_list = new std::vector<std::string>;
      (yyval.join_list)->condition_list = new std::vector<ConditionSqlNode>;

      (yyval.join_list)->relation_list->emplace_back(move((yyvsp[-1].string)));
      (yyval.join_list)->relation_list->insert((yyval.join_list)->relation_list->end(), 
        (yyvsp[0].join_list)->relation_list->begin(), (yyvsp[0].join_list)->relation_list->end());
      (yyval.join_list)->condition_list->insert((yyval.join_list)->condition_list->begin(), 
        (yyvsp[0].join_list)->condition_list->begin(), (yyvsp[0].join_list)->condition_list->end());

      delete (yyvsp[0].join_list)->relation_list;
      delete (yyvsp[0].join_list)->condition_list;
      delete (yyvsp[0].join_list);
      free((yyvsp[-1].string));
    }
#line 2534 "yacc_sql.cpp"
    break;

  case 89: /* rel_list: relation join_list COMMA rel_list  */
#line 747 "yacc_sql.y"
                                       {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
        (yyval.join_list)->relation_list = new std::vector<std::string>;
        (yyval.join_list)->condition_list = new std::vector<ConditionSqlNode>;
      }

      (yyval.join_list)->relation_list->insert((yyval.join_list)->relation_list->begin(), 
        (yyvsp[-2].join_list)->relation_list->begin(), (yyvsp[-2].join_list)->relation_list->end());
      (yyval.join_list)->relation_list->insert((yyval.join_list)->relation_list->begin(), (yyvsp[-3].string));
      (yyval.join_list)->condition_list->insert((yyval.join_list)->condition_list->begin(), 
        (yyvsp[-2].join_list)->condition_list->begin(), (yyvsp[-2].join_list)->condition_list->end());

      delete (yyvsp[-2].join_list)->relation_list;
      delete (yyvsp[-2].join_list)->condition_list;
      delete (yyvsp[-2].join_list);
      free((yyvsp[-3].string));
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 90: /* join_list: INNER JOIN relation on  */
#line 771 "yacc_sql.y"
    {
      (yyval.join_list) = new Joins;
      (yyval.join_list)->relation_list = new std::vector<std::string>;
      (yyval.join_list)->condition_list = new std::vector<ConditionSqlNode>;
      (yyval.join_list)->relation_list->emplace_back(move((yyvsp[-1].string)));

      free((yyvsp[-1].string));
      if((yyvsp[0].condition_list) != nullptr){
        (yyval.join_list)->condition_list->insert((yyval.join_list)->condition_list->end(), (yyvsp[0].condition_list)->begin(), (yyvsp[0].condition_list)->end());
        delete (yyvsp[0].condition_list);
      }
      
    }
#line 2577 "yacc_sql.cpp"
    break;

  case 91: /* join_list: INNER JOIN relation on join_list  */
#line 785 "yacc_sql.y"
    {
      if ((yyvsp[0].join_list) != nullptr) {
        (yyval.join_list) = (yyvsp[0].join_list);
      } else {
        (yyval.join_list) = new Joins;
        (yyval.join_list)->relation_list = new std::vector<std::string>;
        (yyval.join_list)->condition_list = new std::vector<ConditionSqlNode>;
      }

      (yyval.join_list)->relation_list->emplace((yyval.join_list)->relation_list->begin(), move((yyvsp[-2].string)));
      free((yyvsp[-2].string));

      if((yyvsp[-1].condition_list) != nullptr){
        (yyval.join_list)->condition_list->insert((yyval.join_list)->condition_list->end(), (yyvsp[-1].condition_list)->begin(), (yyvsp[-1].condition_list)->end());
        delete (yyvsp[-1].condition_list);
      }
    }
#line 2599 "yacc_sql.cpp"
    break;

  case 92: /* on: %empty  */
#line 806 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 93: /* on: ON condition_list  */
#line 810 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2615 "yacc_sql.cpp"
    break;

  case 94: /* where: %empty  */
#line 818 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 95: /* where: WHERE condition_list  */
#line 821 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 96: /* condition_list: %empty  */
#line 827 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 97: /* condition_list: condition  */
#line 830 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(move(*(yyvsp[0].condition)));
      delete (yyvsp[0].condition);
    }
#line 2649 "yacc_sql.cpp"
    break;

  case 98: /* condition_list: condition AND condition_list  */
#line 835 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 99: /* condition_list: condition OR condition_list  */
#line 840 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(move(*(yyvsp[-2].condition)));
      delete (yyvsp[-2].condition);
    }
#line 2669 "yacc_sql.cpp"
    break;

  case 100: /* condition: rel_attr comp_op value  */
#line 848 "yacc_sql.y"
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
#line 2685 "yacc_sql.cpp"
    break;

  case 101: /* condition: value comp_op value  */
#line 860 "yacc_sql.y"
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
#line 2701 "yacc_sql.cpp"
    break;

  case 102: /* condition: rel_attr comp_op rel_attr  */
#line 872 "yacc_sql.y"
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
#line 2717 "yacc_sql.cpp"
    break;

  case 103: /* condition: value comp_op rel_attr  */
#line 884 "yacc_sql.y"
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
#line 2733 "yacc_sql.cpp"
    break;

  case 104: /* condition: rel_attr comp_op LBRACE select_stmt RBRACE  */
#line 896 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].rel_attr);
    }
#line 2748 "yacc_sql.cpp"
    break;

  case 105: /* condition: value comp_op LBRACE select_stmt RBRACE  */
#line 907 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 0;
      (yyval.condition)->left_value = *(yyvsp[-4].value);
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);

      delete (yyvsp[-4].value);
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 106: /* condition: unary_op LBRACE select_stmt RBRACE  */
#line 918 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->left_type = 0;
      (yyval.condition)->left_value = Value((void*)nullptr);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2776 "yacc_sql.cpp"
    break;

  case 107: /* condition: rel_attr IS NULL_T  */
#line 927 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_type = 0;
      (yyval.condition)->right_value = Value((void*)nullptr);
      (yyval.condition)->left_type = 1;
      (yyval.condition)->comp = IS_NULL;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);

      delete (yyvsp[-2].rel_attr);
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 108: /* condition: rel_attr IS NOT NULL_T  */
#line 938 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_type = 0;
      (yyval.condition)->right_value = Value((void*)nullptr);
      (yyval.condition)->left_type = 1;
      (yyval.condition)->comp = IS_NOT_NULL;
      (yyval.condition)->left_attr = *(yyvsp[-3].rel_attr);

      delete (yyvsp[-3].rel_attr);
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 109: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 949 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 2;
      (yyval.condition)->left_select = unique_ptr<ParsedSqlNode>((yyvsp[-5].sql_node));
      (yyval.condition)->right_type = 2;
      (yyval.condition)->right_select = unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 110: /* condition: LBRACE select_stmt RBRACE comp_op value  */
#line 958 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 2;
      (yyval.condition)->left_select = unique_ptr<ParsedSqlNode>((yyvsp[-3].sql_node));
      (yyval.condition)->right_type = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].value);
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 111: /* condition: LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 969 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = 2;
      (yyval.condition)->left_select = unique_ptr<ParsedSqlNode>((yyvsp[-3].sql_node));
      (yyval.condition)->right_type = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[0].rel_attr);
    }
#line 2849 "yacc_sql.cpp"
    break;

  case 112: /* condition: rel_attr comp_op LBRACE value_list RBRACE  */
#line 980 "yacc_sql.y"
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
#line 2865 "yacc_sql.cpp"
    break;

  case 113: /* comp_op: LIKE  */
#line 994 "yacc_sql.y"
         { (yyval.comp) = LIKE_OP; }
#line 2871 "yacc_sql.cpp"
    break;

  case 114: /* comp_op: NOT LIKE  */
#line 995 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE; }
#line 2877 "yacc_sql.cpp"
    break;

  case 115: /* comp_op: EQ  */
#line 996 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2883 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: LT  */
#line 997 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2889 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: GT  */
#line 998 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2895 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: LE  */
#line 999 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2901 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: GE  */
#line 1000 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2907 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: NE  */
#line 1001 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2913 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: IN  */
#line 1002 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2919 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: NOT IN  */
#line 1003 "yacc_sql.y"
             { (yyval.comp) = NOT_IN; }
#line 2925 "yacc_sql.cpp"
    break;

  case 123: /* unary_op: EXISTS  */
#line 1007 "yacc_sql.y"
           { (yyval.comp) = EXISTS_OP; }
#line 2931 "yacc_sql.cpp"
    break;

  case 124: /* unary_op: NOT EXISTS  */
#line 1008 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS; }
#line 2937 "yacc_sql.cpp"
    break;

  case 125: /* group_by: %empty  */
#line 1014 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2945 "yacc_sql.cpp"
    break;

  case 126: /* group_by: GROUP BY expression_list  */
#line 1018 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 127: /* having_list: %empty  */
#line 1025 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2961 "yacc_sql.cpp"
    break;

  case 128: /* having_list: HAVING condition_list  */
#line 1029 "yacc_sql.y"
    {
      (yyval.condition_list) =(yyvsp[0].condition_list);
    }
#line 2969 "yacc_sql.cpp"
    break;

  case 129: /* order_by: %empty  */
#line 1036 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2977 "yacc_sql.cpp"
    break;

  case 130: /* order_by: ORDER BY order_by_list  */
#line 1040 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2985 "yacc_sql.cpp"
    break;

  case 131: /* order_by_list: order_by_unit  */
#line 1047 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderByNode>;
      (yyval.order_by_list)->emplace_back(move(*(yyvsp[0].order_by_unit)));
      delete (yyvsp[0].order_by_unit);
    }
#line 2995 "yacc_sql.cpp"
    break;

  case 132: /* order_by_list: order_by_unit COMMA order_by_list  */
#line 1053 "yacc_sql.y"
    {
      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.order_by_list) = (yyvsp[0].order_by_list);
      } else {
        (yyval.order_by_list) = new std::vector<OrderByNode>;
      }
      (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), move(*(yyvsp[-2].order_by_unit)));
      delete (yyvsp[-2].order_by_unit);
    }
#line 3009 "yacc_sql.cpp"
    break;

  case 133: /* order_by_unit: expression  */
#line 1066 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = (yyvsp[0].expression);
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 134: /* order_by_unit: expression ASC  */
#line 1072 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = true;
      (yyval.order_by_unit)->expression = (yyvsp[-1].expression);
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 135: /* order_by_unit: expression DESC  */
#line 1078 "yacc_sql.y"
    {
      (yyval.order_by_unit) = new OrderByNode;
      (yyval.order_by_unit)->is_asc = false;
      (yyval.order_by_unit)->expression = (yyvsp[-1].expression);
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 136: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1087 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3053 "yacc_sql.cpp"
    break;

  case 137: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1100 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3062 "yacc_sql.cpp"
    break;

  case 138: /* set_variable_stmt: SET ID EQ value  */
#line 1108 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3074 "yacc_sql.cpp"
    break;


#line 3078 "yacc_sql.cpp"

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
          goto yyexhaustedlab;
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 1120 "yacc_sql.y"

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
