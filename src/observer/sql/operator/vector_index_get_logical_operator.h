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
// Created by Wangyunlai on 2022/12/07.
//
#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"
#include "common/types.h"

/**
 * @brief 表示从向量索引中获取数据的算子
 * @details 比如使用全表扫描、通过索引获取数据等
 * @ingroup LogicalOperator
 */
class VectorIndexGetLogicalOperator : public LogicalOperator
{
public:
  VectorIndexGetLogicalOperator(Index *index, Value&& base_vector, Table *table, int limit);
  virtual ~VectorIndexGetLogicalOperator() = default;

    LogicalOperatorType type() const override { return LogicalOperatorType::VECTOR_INDEX_GET; }

    Index       *index() const { return index_; }
    Value       &value() { return base_vector_; }
    Table       *table() const { return table_; }
    int          limit() const { return limit_; }

private:
    Index             *index_          = nullptr;
    Value              base_vector_;
    Table             *table_ = nullptr;
    int                limit_ = 0;
};
