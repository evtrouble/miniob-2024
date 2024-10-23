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
#include "storage/table/view.h"

RC FilterStmt::create(Db *db, BaseTable *default_table, tables_t& table_map, Conditions& conditions, 
    FilterStmt *&stmt, vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
    int fa)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;
  FilterStmt *tmp_stmt = new FilterStmt(conditions.and_or);
  
  size_t min_depend = UINT32_MAX;

  auto size = depends.size() - 1;
  vector<unique_ptr<Expression>> bound_expressions;

  auto bind_expression = [&](unique_ptr<Expression> &expr){
    if (nullptr == expr) {
      return RC::SUCCESS;
    }

    switch (expr->type())
    {
      case ExprType::UNBOUND_FIELD:{
        auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expr.get());

        BaseTable *table;
        const FieldMeta *field_meta;

        RC rc = get_table_and_field(db, default_table, table_map, table, field_meta, 
            *unbound_field_expr, &min_depend);
        if(rc != RC::SUCCESS)return rc;

        if(table->is_view()){
          View *view = static_cast<View*>(table);
          Field* field = view->find_field(unbound_field_expr->field_name());
          if (nullptr == field) {
            LOG_INFO("no such field in view: %s.%s", unbound_field_expr->table_name(), unbound_field_expr->field_name());
            return RC::SCHEMA_FIELD_MISSING;
          }
          FieldExpr *field_expr = new FieldExpr(*field);
          field_expr->set_name(field->field_name());
          field_expr->set_alias(expr->alias());
          expr.reset(field_expr);
          return RC::SUCCESS;
        }

        Field      field(table, field_meta);
        FieldExpr *field_expr = new FieldExpr(field);
        field_expr->set_name(unbound_field_expr->field_name());
        expr.reset(field_expr);
      }break;
      case ExprType::SELECT:{
        auto select_expr = static_cast<SelectExpr *>(expr.get());
        select_exprs.emplace_back(select_expr);
        return select_expr->create_stmt(db, depends, select_exprs, table_map, size);
      }break;
      default:return RC::SUCCESS;
    }
    return RC::SUCCESS;
  };
  
  for (auto& cond : conditions.conditions){
    unique_ptr<Expression> expr(new ComparisonExpr(cond.comp, std::move(cond.left_expr), std::move(cond.right_expr)));
    rc = expr->recursion(expr, bind_expression);
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
    depends.at(size).emplace_back(min_depend);

  tmp_stmt->filter_units_.swap(bound_expressions);

  stmt = tmp_stmt;
  return rc;
}

RC FilterStmt::get_table_and_field(Db *db, BaseTable *default_table, tables_t& table_map, BaseTable*& table, const FieldMeta*& field, 
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