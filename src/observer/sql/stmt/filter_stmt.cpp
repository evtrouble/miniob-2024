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
// Created by Wangyunlai on 2022/5/22.
//


#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

RC FilterStmt::create(Db *db, Table *default_table, BinderContext& table_map, const Conditions& conditions, 
    FilterStmt *&stmt, vector<vector<uint32_t>>* depends, int fa)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;
  FilterStmt *tmp_stmt = new FilterStmt(conditions.and_or);
  
  size_t min_depend = UINT32_MAX;
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(table_map);
  for (auto& cond : conditions.conditions) {
    if(cond.left_expr->type() == ExprType::UNBOUND_FIELD){
      UnboundFieldExpr* temp = static_cast<UnboundFieldExpr*>(cond.left_expr);
      rc = get_table_and_field(db, default_table, table_map, temp->table_name(), temp->field_name(), &min_depend);
      if(rc != RC::SUCCESS){
        delete tmp_stmt;
        return rc;
      }
    }
    if(cond.right_expr->type() == ExprType::UNBOUND_FIELD){
      UnboundFieldExpr* temp = static_cast<UnboundFieldExpr*>(cond.right_expr);
      rc = get_table_and_field(db, default_table, table_map, temp->table_name(), temp->field_name(), &min_depend);
      if(rc != RC::SUCCESS){
        delete tmp_stmt;
        return rc;
      }
    }
  }

  auto size = depends->size() - 1;
  if(fa >= 0 && min_depend < size)
    depends->at(size).push_back(min_depend);
  
  for (auto& cond : conditions.conditions){
    unique_ptr<Expression> left(cond.left_expr);
    unique_ptr<Expression> right(cond.right_expr);
    if(left->type() == ExprType::SELECT){
      rc = static_cast<SelectExpr*>(left.get())->create_stmt(db, depends, table_map, size);
    }
    if(rc != RC::SUCCESS){
        delete tmp_stmt;
        return rc;
    }

    if(right->type() == ExprType::SELECT){
      rc = static_cast<SelectExpr*>(right.get())->create_stmt(db, depends, table_map, size);
    }
    if(rc != RC::SUCCESS){
        delete tmp_stmt;
        return rc;
    }

    unique_ptr<Expression> expr(new ComparisonExpr(cond.comp, std::move(left), std::move(right)));
    rc = expression_binder.bind_expression(expr, bound_expressions);
    if(rc != RC::SUCCESS){
        delete tmp_stmt;
        return rc;
    }
  }

  tmp_stmt->filter_units_.swap(bound_expressions);

  stmt = tmp_stmt;
  return rc;
}

RC FilterStmt::get_table_and_field(Db *db, Table *default_table, BinderContext& table_map,
    const char* relation_name, const char* attribute_name, size_t *min_depend)
{
  Table* table = nullptr;
  if (common::is_blank(relation_name)) {
    table = default_table;
  } else {
    auto iter = table_map.find_table(relation_name);
    if (iter != nullptr) {
      *min_depend = std::min(*min_depend, table_map.get_id(relation_name));
    }
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", relation_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  const FieldMeta* field = table->table_meta().field(attribute_name);
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attribute_name);
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}