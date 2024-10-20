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

RC FilterStmt::create(Db *db, Table *default_table, tables_t& table_map, const Conditions& conditions, 
    FilterStmt *&stmt, unique_ptr<vector<vector<uint32_t>>>& depends, unique_ptr<vector<SelectExpr*>>& select_exprs, 
    int fa)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;
  FilterStmt *tmp_stmt = new FilterStmt(conditions.and_or);
  
  size_t min_depend = UINT32_MAX;

  auto size = depends->size() - 1;
  vector<unique_ptr<Expression>> bound_expressions;

  function<RC(std::unique_ptr<Expression>&)> bind_expression = 
    [&](unique_ptr<Expression> &expr){
    if (nullptr == expr) {
      return RC::SUCCESS;
    }

    switch (expr->type())
    {
      case ExprType::ARITHMETIC:{
        auto arithmetic_expr = static_cast<ArithmeticExpr *>(expr.get());

        unique_ptr<Expression>        &left_expr  = arithmetic_expr->left();
        unique_ptr<Expression>        &right_expr = arithmetic_expr->right();

        RC rc = bind_expression(left_expr);
        if (OB_FAIL(rc)) {
          return rc;
        }

        rc = bind_expression(right_expr);
        if (OB_FAIL(rc)) {
          return rc;
        }
        return RC::SUCCESS;
      }break;
      case ExprType::COMPARISON:{
        auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());
        unique_ptr<Expression> child_bound_expression;
        unique_ptr<Expression>        &left_expr  = comparison_expr->left();
        unique_ptr<Expression>        &right_expr = comparison_expr->right();
  
        RC rc = bind_expression(left_expr);
        if (rc != RC::SUCCESS) {
          return rc;
        }

        rc = bind_expression(right_expr);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        return RC::SUCCESS;
      }break;
      case ExprType::UNBOUND_FIELD:{
        auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expr.get());

        Table *table;
        const FieldMeta *field_meta;

        RC rc = get_table_and_field(db, default_table, table_map, table, field_meta, 
            *unbound_field_expr, &min_depend);
        if(rc != RC::SUCCESS)return rc;

        Field      field(table, field_meta);
        FieldExpr *field_expr = new FieldExpr(field);
        field_expr->set_name(unbound_field_expr->field_name());
        expr.reset(field_expr);
      }break;
      case ExprType::SELECT:{
        auto select_expr = static_cast<SelectExpr *>(expr.get());
        select_exprs->emplace_back(select_expr);
        return select_expr->create_stmt(db, depends, select_exprs, table_map, size);
      }break;
      default:return RC::SUCCESS;
    }
    return RC::SUCCESS;
  };
  
  for (auto& cond : conditions.conditions){
    unique_ptr<Expression> left(cond.left_expr);
    unique_ptr<Expression> right(cond.right_expr);

    unique_ptr<Expression> expr(new ComparisonExpr(cond.comp, std::move(left), std::move(right)));
    rc = bind_expression(expr);
    if(rc != RC::SUCCESS){
        delete tmp_stmt;
        return rc;
    }
    bound_expressions.emplace_back(std::move(expr));
  }

  if(rc != RC::SUCCESS){
    delete tmp_stmt;
    return rc;
  }

  if(fa >= 0 && min_depend < size)
    depends->at(size).emplace_back(min_depend);

  tmp_stmt->filter_units_.swap(bound_expressions);

  stmt = tmp_stmt;
  return rc;
}

RC FilterStmt::get_table_and_field(Db *db, Table *default_table, tables_t& table_map, Table*& table, const FieldMeta*& field, 
    UnboundFieldExpr& expr, size_t *min_depend)
{
  table = nullptr;
  const char *table_name = expr.table_name();
  const char *field_name = expr.field_name();
  if (common::is_blank(table_name)) {
    table = default_table;
  } else {
    auto iter = table_map.find(table_name);
    if (iter != table_map.end()) {
      table = iter->second.first;
      *min_depend = std::min(*min_depend, iter->second.second);
    }
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(field_name);
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), field_name);
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}