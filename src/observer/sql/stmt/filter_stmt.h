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

#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include <unordered_map>
#include <vector>

class Db;
class Table;
class FieldMeta;

struct FilterObj
{
  int  type;
  Field field;
  Value value;
  vector<Value> value_list;
  Stmt* stmt = nullptr;

  void init_attr(const Field &field)
  {
    type     = 1;
    this->field = field;
  }

  void init_value(const Value&& value)
  {
    type     = 0;
    this->value = std::move(value);
  }

  RC init_stmt(Db *db, ParsedSqlNode* sql_node, vector<vector<uint32_t>>* depends, 
    tables_t* tables_map, int fa)
  {
    type     = 2;
    return Stmt::create_stmt(db, *sql_node, this->stmt, depends, tables_map, fa);
  }

  void init_value_list(const vector<Value>&& value_list)
  {
    type     = 3;
    this->value_list = move(value_list);
  }
};

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit() {
    if(left_.stmt != nullptr)delete left_.stmt;
    if(right_.stmt != nullptr)delete right_.stmt;
  }

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  void set_left(const FilterObj &obj) { left_ = obj; }
  void set_right(const FilterObj &obj) { right_ = obj; }

  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }
  FilterObj &left() { return left_; }
  FilterObj &right() { return right_; }

private:
  CompOp    comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }

public:
  static RC create(Db *db, Table *default_table, tables_t* table_map, const ConditionSqlNode *conditions, 
    int condition_num, FilterStmt *&stmt, vector<vector<uint32_t>>* depends, int fa = -1);


  static RC create_filter_unit(Db *db, Table *default_table, tables_t* table_map,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit, size_t *min_depend);

private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
};
