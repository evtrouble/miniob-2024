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

RC CreateTableStmt::create(Db *db, const CreateTableSqlNode &create_table, SelectSqlNode &select_sql, Stmt *&stmt, 
    vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
    tables_t& table_map, int fa)
{
  StorageFormat storage_format = StorageFormat::UNKNOWN_FORMAT;
  if (create_table.storage_format.length() == 0) {
    storage_format = StorageFormat::ROW_FORMAT;
  } else {
    storage_format = get_storage_format(create_table.storage_format.c_str());
  }
  if (storage_format == StorageFormat::UNKNOWN_FORMAT) {
    return RC::INVALID_ARGUMENT;
  }

  // create table select
  if (0 != select_sql.expressions.size()) {
    Stmt *select_stmt = nullptr;
    std::vector<AttrInfoSqlNode> attr_infos;

    RC rc = SelectStmt::create(db, select_sql, select_stmt, depends, select_exprs, table_map);
    if (RC::SUCCESS != rc) {
      delete select_stmt;
      LOG_WARN("failed to create select_stmt when create_table_select, rc=%s", strrc(rc));
      return rc;
    }
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
    }

    if (0 != create_table.attr_infos.size()) {
      if (attr_infos.size() != create_table.attr_infos.size()) {
        delete stmt;
        LOG_ERROR("field size mismatch with output column size of select_stmt");
        return RC::INVALID_ARGUMENT;
      }
      for (size_t i = 0; i < attr_infos.size(); i++) {
        if (attr_infos[i].type != create_table.attr_infos[i].type) {
          LOG_ERROR("create_table info mismatch with sub_query");
          delete stmt;
          return RC::INVALID_ARGUMENT;
        }
      }
      // 指定了列属性、带select
      stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos, storage_format, db, select_stmt);
    } else {
      // 未指定列属性、带select
      stmt = new CreateTableStmt(create_table.relation_name, attr_infos, storage_format, db, select_stmt);
    }
  } else {
    // 指定了列属性、不带select
    stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos, storage_format, db);
  }
  sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}

StorageFormat CreateTableStmt::get_storage_format(const char *format_str) {
  StorageFormat format = StorageFormat::UNKNOWN_FORMAT;
  if (0 == strcasecmp(format_str, "ROW")) {
    format = StorageFormat::ROW_FORMAT;
  } else if (0 == strcasecmp(format_str, "PAX")) {
    format = StorageFormat::PAX_FORMAT;
  } else {
    format = StorageFormat::UNKNOWN_FORMAT;
  }
  return format;
}
