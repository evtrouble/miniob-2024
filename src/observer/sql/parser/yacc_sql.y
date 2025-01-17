
%{

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

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        GROUP
        ORDER
        HAVING
        ASC
        DESC
        TABLE
        VIEW
        TABLES
        INDEX
        CALC
        SELECT
        SHOW
        SYNC
        WITH
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        LMBRACE
        RMBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        VECTOR_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        INNER
        JOIN
        AND
        OR
        SET
        ON
        AS
        LOAD
        DATA
        LIKE
        NULL_T
        EXISTS
        IN
        IS
        NOT
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        LIMIT
        EQ
        LT
        GT
        LE
        GE
        NE
        UNIQUE
        L2_DISTANCE
        COSINE_DISTANCE
        INNER_PRODUCT
        DISTANCE                                
        LISTS                              
        TYPE            
        PROBES                
        IVFFLAT      


/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
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
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID_KEY
%token <string> SSS
%token <string> DATE_VALUE


//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <number>              date_type
%type <boolean>             nullable
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <number>              limit
%type <string>              relation
%type <string>              ID
%type <relation_list>       col_list
%type <comp>                comp_op
%type <boolean>             unique_option
%type <boolean>             as_option
%type <comp>                unary_op
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <relation_list>       idx_col_list
%type <values_list>         values_list
%type <value_list>          value_list
%type <key_values>          key_values
%type <expression>          assign_value
%type <condition_list>      where
%type <condition_list>      on
%type <number>              vector_operation
%type <vector_index_type>   vector_index_type
%type <join_list>           join_list
%type <condition_list>      condition_list
%type <string>              storage_format
%type <string>              alias
%type <join_list>           rel_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <having_list>         having_list
%type <having_list>         having_node
%type <expression>          having_unit
%type <order_by_list>       order_by
%type <order_by_list>       order_by_list
%type <order_by_unit>       order_by_unit
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_index_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            create_view_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left OR
%left AND
%left EQ LT GT LE GE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    if($1 != nullptr){
      std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
      sql_result->add_sql_node(std::move(sql_node));
    }
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_index_stmt
  | create_view_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };
show_index_stmt:      /*show index 语句的语法解析树*/
    SHOW INDEX FROM ID
    {
      $$ = new ParsedSqlNode(SCF_SHOW_INDEX);
      $$->show_index.relation_name = $4;
      free($4);
    }
    ;
show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE unique_option INDEX ID ON ID LBRACE ID idx_col_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.unique = $2;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      std::vector<std::string> *idx_cols = $9;
      if (nullptr != idx_cols) {
        create_index.attr_names.swap(*idx_cols);
        delete $9;
      }
      create_index.attr_names.emplace_back($8);
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free($4);
      free($6);
      free($8);
    }
    | CREATE VECTOR_T INDEX ID ON ID LBRACE ID idx_col_list RBRACE WITH LBRACE
      TYPE EQ vector_index_type COMMA DISTANCE EQ vector_operation COMMA LISTS EQ
      NUMBER COMMA PROBES EQ number RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      std::vector<std::string> *idx_cols = $9;
      if (nullptr != idx_cols) {
        create_index.attr_names.swap(*idx_cols);
        delete $9;
      }
      create_index.attr_names.emplace_back($8);
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free($4);
      free($6);
      free($8);

      create_index.vector_index.distance = $19;    
      create_index.vector_index.type = $15;
      create_index.vector_index.lists = $23;
      create_index.vector_index.probes = $27; 
    }
    ;

vector_operation:
    L2_DISTANCE
    {
      $$ = (int)VectorOperationExpr::Type::L2_DISTANCE;
    }
    | COSINE_DISTANCE
    {
      $$ = (int)VectorOperationExpr::Type::COSINE_DISTANCE;
    }
    | INNER_PRODUCT
    {
      $$ = (int)VectorOperationExpr::Type::INNER_PRODUCT;
    }
    ;

vector_index_type:
    IVFFLAT { $$ = VectorIndexType::IVFFLAT; };

idx_col_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID idx_col_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->emplace_back($2);
      free($2);
    }
    ;

col_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | LBRACE ID idx_col_list RBRACE
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->emplace_back($2);
      free($2);      
    }
    ;
unique_option:
    /* empty */
    {
      $$ = false;
    }
    | UNIQUE
    {
      $$ = true;
    }
drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;

create_view_stmt:    /*create view 语句的语法解析树*/
    CREATE VIEW ID AS select_stmt
    {
      $$ = $5;
      $$->flag = SCF_CREATE_VIEW;
      $$->create_view.view_name = $3;
      free($3);
    }
    | CREATE VIEW ID LBRACE ID idx_col_list RBRACE AS select_stmt
    {
      $$ = $9;
      $$->flag = SCF_CREATE_VIEW;
      $$->create_view.view_name = $3;

      std::vector<std::string> &col_names = $$->create_view.col_names;
      if (nullptr != $6) {
        col_names.swap(*$6);
        delete $6;
      }
      col_names.emplace_back($5);
      std::reverse(col_names.begin(), col_names.end());
      free($3);
      free($5);
    }
    ;

create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(move(*$5));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_option select_stmt
    {
      $$ = $9;
      $$->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(move(*$5));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    | CREATE TABLE ID as_option select_stmt
    {
      $$ = $5;
      $$->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);
    }
    ;

as_option:
    /* empty */
    {
      $$ = false;
    }
    | AS { $$ = true; }
    ;

attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(move(*$2));
      delete $2;
    }
    ;

attr_def:
    ID type LBRACE number RBRACE nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = $6;
      free($1);
    }
    | ID type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = $3;
      free($1);
    }
    | ID date_type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 10;
      $$->nullable = $3;
      free($1);
    }
    ;

nullable:
    /* empty */
    { $$ = true; }
    | NULL_T {$$ = true;}
    | NOT NULL_T {$$ = false;}
    ;

number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    | TEXT_T   { $$ = static_cast<int>(AttrType::TEXTS);}
    ;
date_type:
    DATE_T   {$$ = static_cast<int>(AttrType::DATES);}
    ;

insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID col_list VALUES values_list
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;

      if ($6 != nullptr) {
        $$->insertion.values.swap(*$6);
        std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
        delete $6;
      }

      if (nullptr != $4) {
        $$->insertion.attrs_name.swap(*$4);
        std::reverse($$->insertion.attrs_name.begin(), $$->insertion.attrs_name.end());
        delete $4;
      }

      free($3);
    }
    ;

values_list:
    LBRACE value_list RBRACE
    {
      $$ = new std::vector<std::vector<Value>>;
      $$->emplace_back(move(*$2));
      delete $2;
    }
    | LBRACE value_list RBRACE COMMA values_list
    {
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::vector<std::vector<Value>>;
      }

      $$->emplace_back(move(*$2));
      delete $2;
    }
    ;

value_list:
    expression {
      $$ = new std::vector<Value>;
      Value temp;
      if(OB_FAIL($1->try_get_value(temp))){
        yyerror(&@$, sql_string, sql_result, scanner, "error");
        YYERROR;
      }
      $$->emplace_back(temp);
      delete $1;
    }
    | expression COMMA value_list  {
      Value temp;
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      if(OB_FAIL($1->try_get_value(temp))){
        yyerror(&@$, sql_string, sql_result, scanner, "error");
        YYERROR;
      }

      $$->emplace($$->begin(), move(temp));
      delete $1;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      int len = strlen($1)-2;
      char *tmp = common::substr($1,1,len);
      $$ = new Value(tmp, len);
      free(tmp);
      free($1);
    }
    |DATE_VALUE {
      int len = strlen($1)-2;
      char *tmp = common::substr($1,1,len);
      $$ = new Value((Date*)tmp, len);
      free(tmp);
      free($1);
    }
    |NULL_T {
      $$ = new Value((void*)nullptr);
    }
    | LMBRACE value_list RMBRACE {
      $$ = new Value($2);
      delete $2;
    }
    ;
storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;

delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        swap($$->deletion.conditions, *$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET key_values where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_names.swap($4->relation_list);
      $$->update.values.swap($4->value_list);

      delete $4;
      free($2);

      if($5 != nullptr){
        swap($$->update.conditions, *$5);
        delete $5;
      }
    }
    ;

key_values:
    ID EQ assign_value
    {
      $$ = new Key_values;
      $$->relation_list.emplace_back(move($1));
      free($1);
      $$->value_list.emplace_back(unique_ptr<Expression>($3));
    }
    | ID EQ assign_value COMMA key_values
    {
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new Key_values;
      }

      $$->relation_list.emplace_back(move($1));
      free($1);
      $$->value_list.emplace_back(unique_ptr<Expression>($3));
    }
    ;

assign_value:
    expression { $$ = $1; }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM rel_list where group_by having_node order_by limit
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.swap($4->relation_list);
        $$->selection.alias.swap($4->alias_list);
        swap($$->selection.conditions, $4->condition_list);
        delete $4;
      }

      if ($5 != nullptr) {
        auto& conditions = $$->selection.conditions;
        if(conditions.conditions.size()){
          conditions.conditions.insert(conditions.conditions.begin(),
            std::make_move_iterator($5->conditions.begin()), 
            std::make_move_iterator($5->conditions.end()));
          conditions.and_or = $5->and_or;
        }
        else swap(conditions, *$5);
        delete $5;
      }

      if ($6 != nullptr) {
        $$->selection.group_by.swap(*$6);
        delete $6;
      }

      if ($7 != nullptr) {
        swap($$->selection.having_list, *$7);
        delete $7;
      }

      if($8 != nullptr){
        $$->selection.order_by.swap(*$8);
        delete $8;
      }

      $$->selection.limit = $9;
    }
    ;

limit:
    /* empty */
    {
      $$ = -1;
    }
    | LIMIT number
    {
      $$ = $2;
    }

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression alias
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      if($2 != nullptr){
        $1->set_alias($2);
        free($2);
      }
      $$->emplace_back(move($1));
    }
    | expression alias COMMA expression_list
    {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      if($2 != nullptr){
        $1->set_alias($2);
        free($2);
      }
      $$->emplace($$->begin(), move($1));
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | vector_operation LBRACE expression COMMA expression RBRACE{
      $$ = create_operation_expression((VectorOperationExpr::Type)$1, $3, $5, sql_string, &@$);
    }
    | LBRACE expression_list RBRACE {
      if ($2->size() == 1) {
        $$ = ($2->front()).release();
      } else {
        $$ = new ValueListExpr(*$2);
      }
      $$->set_name(token_name(sql_string, &@$));
      delete $2;
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    | ID LBRACE expression_list RBRACE {
      if($3->size() != 1)$$ = create_aggregate_expression("", nullptr, sql_string, &@$);
      else $$ = create_aggregate_expression($1, $3->at(0).release(), sql_string, &@$);
      free($1);
      delete $3;
    }
    | ID LBRACE RBRACE {
      $$ = create_aggregate_expression("", nullptr, sql_string, &@$);
      free($1);
    }
    | LBRACE select_stmt RBRACE {
      $$ = new SelectExpr($2);
    }
    | value {
        $$ = new ValueExpr(*$1);
        $$->set_name(token_name(sql_string, &@$));
        delete $1;
    }
    // your code here
    ;

ID:
    ID_KEY { $$ = $1; }
    | DATA
    {
      $$ = (char *)malloc(sizeof(char) * 5);
      memcpy($$, "data", sizeof(char) * 5);
    }
    | LISTS
    {
      $$ = (char *)malloc(sizeof(char) * 6);
      memcpy($$, "lists", sizeof(char) * 6);
    }
    | TYPE
    {
      $$ = (char *)malloc(sizeof(char) * 5);
      memcpy($$, "type", sizeof(char) * 5);
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    | ID DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = '*';
      free($1);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;
rel_list:
    relation alias join_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new Joins;
      }

      $$->relation_list.emplace($$->relation_list.begin(), $1);
      free($1);
      if($2 != nullptr){
        $$->alias_list.emplace($$->alias_list.begin(), $2);
        free($2);
      } else {
        $$->alias_list.emplace($$->alias_list.begin(), string());
      }
    }
    | relation alias join_list COMMA rel_list{
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new Joins;
      }

      if($3 != nullptr){
        $$->relation_list.insert($$->relation_list.begin(), 
          $3->relation_list.begin(), $3->relation_list.end());
        auto& conditions = $$->condition_list.conditions;
        conditions.insert(conditions.begin(), 
          std::make_move_iterator($3->condition_list.conditions.begin()), 
          std::make_move_iterator($3->condition_list.conditions.end()));
      }

      $$->relation_list.emplace($$->relation_list.begin(), $1);
      if($2 != nullptr){
        $$->alias_list.emplace($$->alias_list.begin(), $2);
        free($2);
      } else {
        $$->alias_list.emplace($$->alias_list.begin(), string());
      }

      delete $3;
      free($1);
    }
    ;

join_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | INNER JOIN relation alias on join_list
    {
      if ($6 != nullptr) {
        $$ = $6;
      } else {
        $$ = new Joins;
      }

      $$->relation_list.emplace($$->relation_list.begin(), $3);
      free($3);
      if($4 != nullptr){
        $$->alias_list.emplace($$->alias_list.begin(), $4);
        free($4);
      } else {
        $$->alias_list.emplace($$->alias_list.begin(), string());
      }

      if($5 != nullptr){
        auto& conditions = $$->condition_list.conditions;
        conditions.insert(conditions.end(), std::make_move_iterator($5->conditions.begin()), 
          std::make_move_iterator($5->conditions.end()));
        delete $5;
      }
    }
    ;

alias:
    /* empty */ {
      $$ = nullptr;
    }
    | ID {
      $$ = $1;
    }
    | AS ID {
      $$ = $2;
    }
    ;

on:
    /* empty */
    {
      $$ = nullptr;
    }
    | ON condition_list
    {
      $$ = $2;
    }
    ;


where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;
    }
    ;
condition_list:
    condition {
      $$ = new Conditions;
      $$->conditions.emplace_back(move(*$1));
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->conditions.emplace_back(move(*$1));
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $$->and_or = true;
      $$->conditions.emplace_back(move(*$1));
      delete $1;
    }
    ;
condition:
    expression comp_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_expr = unique_ptr<Expression>($1);
      $$->right_expr = unique_ptr<Expression>($3);
      $$->comp = $2;
    }
    | unary_op expression
    {
      $$ = new ConditionSqlNode;
      $$->left_expr = unique_ptr<Expression>(new ValueExpr(Value((void*)nullptr)));
      $$->right_expr = unique_ptr<Expression>($2);
      $$->comp = $1;
    }
    ;

comp_op:
    LIKE { $$ = LIKE_OP; }
    | NOT LIKE { $$ = NOT_LIKE; }
    | EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN; }
    | IS { $$ = IS_NULL; }
    | IS NOT { $$ = IS_NOT_NULL; }
    ;

unary_op:
    EXISTS { $$ = EXISTS_OP; }
    | NOT EXISTS { $$ = NOT_EXISTS; }
    ;

// your code here
group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression_list
    {
      $$ = $3;
    }
    ;

having_node:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING having_list
    {
      $$ = $2;
    }
    ;

having_list:
    having_unit
    {
      $$ = new HavingNode;
      $$->having_list.emplace_back(move($1));
    }
    | having_unit OR having_list
    {
      $$ = $3;
      $$->having_list.emplace_back(move($1));
      $$->and_or = true;
    }
    | having_unit AND having_list
    {
      $$ = $3;
      $$->having_list.emplace_back(move($1));
    }
    ;

having_unit:
    expression comp_op expression
    {
      unique_ptr<Expression> left($1);
      unique_ptr<Expression> right($3);
      $$ = new ComparisonExpr($2, std::move(left), std::move(right));
    }
    ;

order_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_list
    {
      $$ = $3;
    }
    ;

order_by_list:
    order_by_unit
    {
      $$ = new std::vector<OrderByNode>;
      $$->emplace_back(move(*$1));
      delete $1;
    }
    | order_by_unit COMMA order_by_list
    {
      if($3 != nullptr){
        $$ = $3;
      } else {
        $$ = new std::vector<OrderByNode>;
      }
      $$->emplace($$->begin(), move(*$1));
      delete $1;
    }
    ;

order_by_unit:
    expression
    {
      $$ = new OrderByNode;
      $$->is_asc = true;
      $$->expression = unique_ptr<Expression>($1);
    }
    | expression ASC
    {
      $$ = new OrderByNode;
      $$->is_asc = true;
      $$->expression = unique_ptr<Expression>($1);
    }
    | expression DESC
    {
      $$ = new OrderByNode;
      $$->is_asc = false;
      $$->expression = unique_ptr<Expression>($1);
    }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);

      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
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
