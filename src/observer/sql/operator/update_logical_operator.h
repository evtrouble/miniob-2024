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
  UpdateLogicalOperator(BaseTable *table, const std::vector<const FieldMeta *>&& fields, 
    std::vector<unique_ptr<Expression>>&& values);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  BaseTable                    *table() const { return table_; }
  const std::vector<const FieldMeta *> &fields() const { return fields_; }
  std::vector<const FieldMeta *>       &fields() { return fields_; }
  const std::vector<unique_ptr<Expression>> &values() const { return values_; }
  std::vector<unique_ptr<Expression>>       &values() { return values_; }

private:
  BaseTable             *table_ = nullptr;
  std::vector<const FieldMeta *> fields_;
  std::vector<unique_ptr<Expression>> values_;
};