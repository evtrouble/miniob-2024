#include "sql/stmt/create_view_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "event/sql_debug.h"

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
// Created by Wangyunlai on 2023/6/13.
//

#include "common/log/log.h"
#include "common/types.h"
#include "sql/stmt/create_table_stmt.h"
#include "event/sql_debug.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, 
    Stmt *&stmt, SelectSqlNode &select_sql, vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
    tables_t& table_map, int fa)
{
    // create view
    if (0 == select_sql.expressions.size())return RC::INVALID_ARGUMENT;
    Stmt *select_stmt = nullptr;
    std::vector<AttrInfoSqlNode> attr_infos;

    RC rc = SelectStmt::create(db, select_sql, select_stmt, depends, select_exprs, table_map);
    if (RC::SUCCESS != rc) {
      delete select_stmt;
      LOG_WARN("failed to create select_stmt when create_table_select, rc=%s", strrc(rc));
      return rc;
    }

    std::vector<unique_ptr<Expression>> map_exprs;
    bool allow_write = true;

    for (std::unique_ptr<Expression> &attr_expr : static_cast<SelectStmt*>(select_stmt)->query_expressions()) {
      AttrInfoSqlNode attr_info;
      if (0 != attr_expr->alias().length()) {
        size_t pos = attr_expr->alias().find('.');
        if (std::string::npos == pos) {
          attr_info.name = attr_expr->alias();
        } else {
          attr_info.name = attr_expr->alias().substr(pos + 1);
        }
      } else {
        attr_info.name = attr_expr->name();
      }
      attr_info.type = attr_expr->value_type();

      if (ExprType::FIELD == attr_expr->type()) {
        FieldExpr *field_expr = dynamic_cast<FieldExpr*>(attr_expr.get());
        FieldMeta field = *(field_expr->field().meta());
        attr_info.length = field.len();
        attr_info.nullable = field.nullable();
      } else {
        allow_write = false;
        if (ExprType::VALUE == attr_expr->type()) {
          ValueExpr *value_expr = dynamic_cast<ValueExpr*>(attr_expr.get());
          attr_info.length = value_expr->get_value().length();
        } else {
          attr_info.length = Value::ATTR_TYPE_LENGTH[(int)attr_expr->value_type()];
        }
        // 遍历子表达式，有nullable的FieldExpr时，才允许为NULL
        bool nullable = false;
        auto check_expr_nullable = [&nullable](unique_ptr<Expression> &expr) {
          if (ExprType::FIELD == expr->type()) {
            FieldMeta field = *static_cast<FieldExpr*>(expr.get())->field().meta();
            if (field.nullable()) {
              nullable = true;
            } 
          }
          return RC::SUCCESS;
        };
        attr_expr->recursion(attr_expr, check_expr_nullable);
        attr_info.nullable = nullable;
      }
      attr_infos.emplace_back(attr_info);
      map_exprs.emplace_back(move(attr_expr->deep_copy()));
    }

    if (!create_view.col_names.empty()) {
        for (size_t i = 0; i < create_view.col_names.size(); i++) {
            attr_infos[i].name = create_view.col_names[i];
        }
    }

  CreateViewStmt *temp = new CreateViewStmt(std::move(create_view.view_name), 
                            std::move(attr_infos), std::move(map_exprs), select_stmt, allow_write);
  temp->analyzer_.depends_.swap(depends);
  temp->analyzer_.select_exprs_.swap(select_exprs);
  stmt = temp;

  sql_debug("create table statement: table name %s", create_view.view_name.c_str());
  return RC::SUCCESS;
}