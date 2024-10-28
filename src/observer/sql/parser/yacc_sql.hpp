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

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
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
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    ORDER = 263,                   /* ORDER  */
    HAVING = 264,                  /* HAVING  */
    ASC = 265,                     /* ASC  */
    DESC = 266,                    /* DESC  */
    TABLE = 267,                   /* TABLE  */
    VIEW = 268,                    /* VIEW  */
    TABLES = 269,                  /* TABLES  */
    INDEX = 270,                   /* INDEX  */
    CALC = 271,                    /* CALC  */
    SELECT = 272,                  /* SELECT  */
    SHOW = 273,                    /* SHOW  */
    SYNC = 274,                    /* SYNC  */
    WITH = 275,                    /* WITH  */
    INSERT = 276,                  /* INSERT  */
    DELETE = 277,                  /* DELETE  */
    UPDATE = 278,                  /* UPDATE  */
    LBRACE = 279,                  /* LBRACE  */
    RBRACE = 280,                  /* RBRACE  */
    LMBRACE = 281,                 /* LMBRACE  */
    RMBRACE = 282,                 /* RMBRACE  */
    COMMA = 283,                   /* COMMA  */
    TRX_BEGIN = 284,               /* TRX_BEGIN  */
    TRX_COMMIT = 285,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 286,            /* TRX_ROLLBACK  */
    INT_T = 287,                   /* INT_T  */
    STRING_T = 288,                /* STRING_T  */
    FLOAT_T = 289,                 /* FLOAT_T  */
    DATE_T = 290,                  /* DATE_T  */
    VECTOR_T = 291,                /* VECTOR_T  */
    TEXT_T = 292,                  /* TEXT_T  */
    HELP = 293,                    /* HELP  */
    EXIT = 294,                    /* EXIT  */
    DOT = 295,                     /* DOT  */
    INTO = 296,                    /* INTO  */
    VALUES = 297,                  /* VALUES  */
    FROM = 298,                    /* FROM  */
    WHERE = 299,                   /* WHERE  */
    INNER = 300,                   /* INNER  */
    JOIN = 301,                    /* JOIN  */
    AND = 302,                     /* AND  */
    OR = 303,                      /* OR  */
    SET = 304,                     /* SET  */
    ON = 305,                      /* ON  */
    AS = 306,                      /* AS  */
    LOAD = 307,                    /* LOAD  */
    DATA = 308,                    /* DATA  */
    LIKE = 309,                    /* LIKE  */
    NULL_T = 310,                  /* NULL_T  */
    EXISTS = 311,                  /* EXISTS  */
    IN = 312,                      /* IN  */
    IS = 313,                      /* IS  */
    NOT = 314,                     /* NOT  */
    INFILE = 315,                  /* INFILE  */
    EXPLAIN = 316,                 /* EXPLAIN  */
    STORAGE = 317,                 /* STORAGE  */
    FORMAT = 318,                  /* FORMAT  */
    LIMIT = 319,                   /* LIMIT  */
    EQ = 320,                      /* EQ  */
    LT = 321,                      /* LT  */
    GT = 322,                      /* GT  */
    LE = 323,                      /* LE  */
    GE = 324,                      /* GE  */
    NE = 325,                      /* NE  */
    UNIQUE = 326,                  /* UNIQUE  */
    L2_DISTANCE = 327,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 328,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 329,           /* INNER_PRODUCT  */
    DISTANCE = 330,                /* DISTANCE  */
    LISTS = 331,                   /* LISTS  */
    TYPE = 332,                    /* TYPE  */
    PROBES = 333,                  /* PROBES  */
    IVFFLAT = 334,                 /* IVFFLAT  */
    NUMBER = 335,                  /* NUMBER  */
    FLOAT = 336,                   /* FLOAT  */
    ID_KEY = 337,                  /* ID_KEY  */
    SSS = 338,                     /* SSS  */
    DATE_VALUE = 339,              /* DATE_VALUE  */
    UMINUS = 340                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 159 "yacc_sql.y"

  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  HavingNode *                               having_list;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<OrderByNode> *                 order_by_list;
  OrderByNode *                              order_by_unit;
  std::vector<Value> *                       value_list;
  std::vector<std::vector<Value>> *          values_list;
  Conditions *                               condition_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;
  Joins *                                    join_list;
  Key_values *                               key_values;
  enum VectorIndexType                       vector_index_type;

#line 176 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
