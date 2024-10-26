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
// Created on 2024/10/15.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include <vector>

/**
 * @brief 更新物理算子
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>>&& order_by, std::vector<bool>&& is_asc);

  virtual ~OrderByPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  RC next(Tuple *upper_tuple) override;

  Tuple *current_tuple() override;

private:
  RC fetch_next();

private:
  std::vector<std::unique_ptr<Expression>> order_by_;
  std::vector<bool>                        is_asc_;
  bool                                     first_emited_ = false;  /// 第一条数据是否已经输出
  bool                                     have_value = false;
  vector<ValueListTuple>                   value_list_;
  vector<size_t>                           ids_;              
  size_t                                   current_id_;
};
