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
// Created by WangYunlai on 2024/05/30.
//

#include "common/log/log.h"
#include "sql/operator/scalar_group_by_physical_operator.h"
#include "sql/expr/expression_tuple.h"
#include "sql/expr/composite_tuple.h"

using namespace std;
using namespace common;

ScalarGroupByPhysicalOperator::ScalarGroupByPhysicalOperator(vector<Expression *> &&expressions)
    : GroupByPhysicalOperator(std::move(expressions))
{}

RC ScalarGroupByPhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open scalar group by operator");
  ASSERT(children_.size() == 1, "group by operator only support one child, but got %d", children_.size());

  PhysicalOperator &child = *children_[0];
  RC                rc    = child.open(trx);
  if (OB_FAIL(rc)) {
    LOG_INFO("failed to open child operator. rc=%s", strrc(rc));
    return rc;
  }

  have_value = false;
  return rc;
}

RC ScalarGroupByPhysicalOperator::next()
{
  if(!have_value){
    ExpressionTuple<Expression *> group_value_expression_tuple(value_expressions_);

    ValueListTuple group_by_evaluated_tuple;
    PhysicalOperator &child = *children_[0];
    RC rc = RC::SUCCESS;

    while (OB_SUCC(rc = child.next())) {
      rc = collect(group_value_expression_tuple, group_by_evaluated_tuple);
      if(rc != RC::SUCCESS)return rc;
    }

    if (RC::RECORD_EOF == rc) {
      rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
      LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
      return rc;
    }

    // 得到最终聚合后的值
    if (group_value_ == nullptr) {
      AggregatorList aggregator_list;
      create_aggregator_list(aggregator_list);
      group_value_ = make_unique<GroupValueType>(std::move(aggregator_list), CompositeTuple());
    }
    rc = evaluate(*group_value_, false);
    if(rc != RC::SUCCESS)return rc;

    emitted_ = false;
    have_value = true;
  }

  if (group_value_ == nullptr || emitted_) {
    return RC::RECORD_EOF;
  }

  emitted_ = true;

  return RC::SUCCESS;
}

RC ScalarGroupByPhysicalOperator::next(Tuple *upper_tuple)
{
  if(!have_value){
    ExpressionTuple<Expression *> group_value_expression_tuple(value_expressions_);

    ValueListTuple group_by_evaluated_tuple;
    PhysicalOperator &child = *children_[0];
    RC rc = RC::SUCCESS;

    while (OB_SUCC(rc = child.next(upper_tuple))) {
      rc = collect(group_value_expression_tuple, group_by_evaluated_tuple);
      if(rc != RC::SUCCESS)return rc;
    }

    if (RC::RECORD_EOF == rc) {
      rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
      LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
      return rc;
    }

    // 得到最终聚合后的值
    if (group_value_ == nullptr) {
      AggregatorList aggregator_list;
      create_aggregator_list(aggregator_list);
      group_value_ = make_unique<GroupValueType>(std::move(aggregator_list), CompositeTuple());
    }
    rc = evaluate(*group_value_, false);
    if(rc != RC::SUCCESS)return rc;

    emitted_ = false;
    have_value = true;
  }

  if (group_value_ == nullptr || emitted_) {
    return RC::RECORD_EOF;
  }

  emitted_ = true;

  return RC::SUCCESS;
}

RC ScalarGroupByPhysicalOperator::close()
{
  group_value_.reset();
  emitted_ = false;
  children_[0]->close();
  LOG_INFO("close scalar group by operator");
  return RC::SUCCESS;
}

Tuple *ScalarGroupByPhysicalOperator::current_tuple()
{
  if (group_value_ == nullptr) {
    return nullptr;
  }

  return &get<1>(*group_value_);
}

RC ScalarGroupByPhysicalOperator::collect(ExpressionTuple<Expression *> &group_value_expression_tuple, 
  ValueListTuple &group_by_evaluated_tuple)
{
  RC rc = RC::SUCCESS;
  Tuple *child_tuple = (*children_[0]).current_tuple();
  if (nullptr == child_tuple) {
    LOG_WARN("failed to get tuple from child operator. rc=%s", strrc(rc));
    return RC::INTERNAL;
  }

  // 计算需要做聚合的值
  group_value_expression_tuple.set_tuple(child_tuple);

  // 计算聚合值
  if (group_value_ == nullptr) {
    AggregatorList aggregator_list;
    create_aggregator_list(aggregator_list);

    ValueListTuple child_tuple_to_value;
    rc = ValueListTuple::make(*child_tuple, child_tuple_to_value);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to make tuple to value list. rc=%s", strrc(rc));
      return rc;
    }

    CompositeTuple composite_tuple;
    composite_tuple.add_tuple(make_unique<ValueListTuple>(std::move(child_tuple_to_value)));
    group_value_ = make_unique<GroupValueType>(std::move(aggregator_list), std::move(composite_tuple));
  }
    
  rc = aggregate(get<0>(*group_value_), group_value_expression_tuple);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to aggregate values. rc=%s", strrc(rc));
    return rc;
  }

  return rc;
}