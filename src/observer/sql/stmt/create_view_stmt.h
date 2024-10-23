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

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/executor/sql_result.h"
#include "sql/executor/sql_result.h"

class Db;

/**
 * @brief 表示创建视图的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(
      const std::string&& view_name, std::vector<AttrInfoSqlNode>&& attr_infos,
      std::vector<Field>&& map_fields, Stmt* select_stmt, bool allow_write)
      : view_name_(move(view_name)), attr_infos_(move(attr_infos)), map_fields_(move(map_fields)), 
      select_stmt_(unique_ptr<Stmt>(select_stmt)), allow_write_(allow_write)
  {}
  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  const std::string                  &view_name() const { return view_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  std::vector<Field>           &map_fields() { return map_fields_; }
  unique_ptr<Stmt>             &select_stmt() { return select_stmt_; }
  SelectAnalyzer               &analyzer() { return analyzer_; }
  bool                          allow_write() const { return allow_write_; }

  static RC create(Db *db, const CreateViewSqlNode &create_view, 
    Stmt *&stmt, SelectSqlNode &select_sql, vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
    tables_t& table_map, int fa);

private:
  std::string view_name_;
  std::vector<AttrInfoSqlNode> attr_infos_; // 视图列信息
  std::vector<Field> map_fields_;           // col映射到的原始列，里面有table、fieldMeta
  unique_ptr<Stmt> select_stmt_; 
  SelectAnalyzer  analyzer_;
  bool allow_write_ = false;                // 是否允许对视图进行写操作
};