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
// Created on 2024/9/13.
//

#pragma once

#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

class FieldMeta;

/**
 * @brief 更新逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const std::vector<const FieldMeta *>&& fields, 
    const std::vector<Value>&& values, std::unordered_map<size_t, SelectExpr*>&& stmt_map);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table                    *table() const { return table_; }
  const std::vector<const FieldMeta *> &fields() const { return fields_; }
  std::vector<const FieldMeta *>       &fields() { return fields_; }
  const std::vector<Value> &values() const { return values_; }
  std::vector<Value>       &values() { return values_; }
  const std::unordered_map<size_t, SelectExpr*>& stmt_map() const { return stmt_map_; }
  std::unordered_map<size_t, SelectExpr*>& stmt_map() { return stmt_map_; }

private:
  Table             *table_ = nullptr;
  std::vector<const FieldMeta *> fields_;
  std::vector<Value> values_;
  std::unordered_map<size_t, SelectExpr*> stmt_map_;
};