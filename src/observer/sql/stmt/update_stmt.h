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

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class Table;
class Db;
class FilterStmt;
class FieldMeta;
class Expression;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(BaseTable *table, std::vector<const FieldMeta *>&& fields, 
    vector<unique_ptr<Expression>>&& values, FilterStmt *filter_stmt);
  ~UpdateStmt() override;

  StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt,
    vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
    tables_t& table_map, int fa);

public:
  BaseTable *table() const { return table_; }
  const std::vector<const FieldMeta *>& fields() const { return fields_; }
  vector<unique_ptr<Expression>>& values() { return values_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }

private:
  BaseTable *table_        = nullptr;
  const std::vector<const FieldMeta *> fields_;
  vector<unique_ptr<Expression>> values_;
  FilterStmt *filter_stmt_ = nullptr;
};
