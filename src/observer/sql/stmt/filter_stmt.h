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

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  FilterStmt(bool and_or) : and_or_(and_or){}
  virtual ~FilterStmt() = default;

public:
  std::vector<unique_ptr<Expression>> &filter_units() { return filter_units_; }
  const bool and_or() const { return and_or_; }

public:
  static RC create(Db *db, Table *default_table, tables_t& table_map, Conditions& conditions, 
    FilterStmt *&stmt, unique_ptr<vector<vector<uint32_t>>>& depends, unique_ptr<vector<SelectExpr*>>& select_exprs, 
    int fa);

  static RC get_table_and_field(Db *db, Table *default_table, tables_t& table_map, Table*& table, const FieldMeta*& field, 
    UnboundFieldExpr& expr, size_t *min_depend);

private:
  std::vector<unique_ptr<Expression>> filter_units_;  // 默认当前都是AND关系
  bool    and_or_ = false;            //false为and，true为or
};
