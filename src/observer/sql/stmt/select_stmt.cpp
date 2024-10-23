/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/base_table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, 
  vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
  tables_t& table_map, int fa)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  std::unordered_map<std::string, std::string> table_alias_map; // <table alias name, table src name>
  BinderContext binder_context(table_alias_map);

  // collect tables in `from` statement
  vector<BaseTable *>                tables;
  auto size = depends.size();
 
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    string& table_alias = select_sql.alias[i];
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    BaseTable *table = db->find_base_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    
    if(!table_map.count(table_name)){
      auto temp = make_pair(table, size);
      table_map.insert({table_name, temp});
    }
    if(!table_alias.empty()){
      if(table_alias_map.count(table_alias))return RC::INVALID_ARGUMENT;
      table_alias_map.insert({table_alias, select_sql.relations[i]});
      auto temp = make_pair(table, size);
      table_map.insert({table_alias, temp});
    }
  }

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    if(expression->type() == ExprType::STAR){
      StarExpr* star_expr = static_cast<StarExpr*>(expression.get());
      if(!star_expr->alias().empty())return RC::INVALID_ARGUMENT;
    }
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

   for (auto& expr : bound_expressions) {
    if (expr->type() == ExprType::FIELD) {
      FieldExpr *field_expr = static_cast<FieldExpr*>(expr.get());
      const char *table_name = field_expr->table_name();
      const char *field_name = field_expr->field_name();
      ASSERT(!common::is_blank(field_name), "Parse ERROR!");
      auto& temp = select_sql.relations;
      size_t id = find(temp.begin(), temp.end(), table_name) - temp.begin();
      if(id != temp.size() && !select_sql.alias[id].empty()){
        field_expr->set_table_alias(select_sql.alias[id].c_str());
      }
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  BaseTable *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  depends.emplace_back(vector<uint32_t>());
  if(fa >= 0){
    depends.at(fa).emplace_back(size);
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;

  RC          rc          = FilterStmt::create(db,
      default_table,
      table_map,
      select_sql.conditions, filter_stmt, depends, select_exprs, fa);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  vector<unique_ptr<Expression>> having_list_expressions;
  for (unique_ptr<Expression> &expression : select_sql.having_list.having_list) {
    RC rc = expression_binder.bind_expression(expression, having_list_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if(table_map.at(table_name).second == size){
      table_map.erase(table_name);
    }
    string& table_alias = select_sql.alias[i];
    if(!table_alias.empty())
      table_map.erase(table_alias);
  }

  vector<unique_ptr<Expression>> order_by_expressions;
  vector<bool> is_asc;

  for (auto& [expr, asc] : select_sql.order_by) {
    RC rc = expression_binder.bind_expression(expr, order_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
    is_asc.emplace_back(asc);
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_expressions);
  select_stmt->is_asc_.swap(is_asc);
  select_stmt->having_list_.swap(having_list_expressions);
  select_stmt->and_or_ = select_sql.having_list.and_or;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}