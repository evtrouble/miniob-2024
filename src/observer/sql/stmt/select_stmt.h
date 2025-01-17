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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, 
    vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
    tables_t& table_map, int fa = -1);

public:
  const std::vector<std::pair<BaseTable *, std::string>> &tables() const { return tables_; }
  FilterStmt                 *filter_stmt() const { return filter_stmt_; }

  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }
  std::vector<std::unique_ptr<Expression>> &order_by() { return order_by_; }
  std::vector<std::unique_ptr<Expression>> &having_list() { return having_list_; }
  std::vector<bool>                        &is_asc() { return is_asc_; }
  bool                                      and_or() { return and_or_; }
  int                                       limit() { return limit_; }

private:
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  std::vector<std::pair<BaseTable *, std::string>>        tables_;
  FilterStmt                              *filter_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> group_by_;
  std::vector<std::unique_ptr<Expression>> order_by_;
  std::vector<std::unique_ptr<Expression>> having_list_;
  bool                                     and_or_ = false;
  std::vector<bool>                        is_asc_; // 升序为true
  int                                      limit_ = -1;
};