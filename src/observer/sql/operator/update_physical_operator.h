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

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include <vector>

class UpdateStmt;
class FieldMeta;

/**
 * @brief 更新物理算子
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, std::vector<const FieldMeta *> &&fields, 
    std::vector<unique_ptr<Expression>>&& values);

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }
  RC init(vector<Value> &values);
  // 查找待更新列的序号、偏移量、长度、类型
  RC find_target_columns();

private:
  Table             *table_ = nullptr;
  std::vector<const FieldMeta *> fields_;
  const std::vector<unique_ptr<Expression>> values_;
  Trx                *trx_   = nullptr;
  bool               ctl = false;
};
