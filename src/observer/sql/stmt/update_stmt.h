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

#include <unordered_map>

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class Table;
class Db;
class FilterStmt;
class FieldMeta;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, const std::vector<const FieldMeta *>&& fields, 
    const vector<Value>&& values, FilterStmt *filter_stmt, std::unordered_map<size_t, void*>&& stmt_map);
  ~UpdateStmt() override;

  StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt,
    vector<vector<uint32_t>>* depends, tables_t* table_map, int fa = -1);

public:
  Table *table() const { return table_; }
  const std::vector<const FieldMeta *>& fields() const { return fields_; }
  const vector<Value>& values() const { return values_; }
  std::unordered_map<size_t, void*>& stmt_map() { return stmt_map_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }

private:
  Table *table_        = nullptr;
  const std::vector<const FieldMeta *> fields_;
  const vector<Value> values_;
  FilterStmt *filter_stmt_ = nullptr;
  std::unordered_map<size_t, void*> stmt_map_;
};
