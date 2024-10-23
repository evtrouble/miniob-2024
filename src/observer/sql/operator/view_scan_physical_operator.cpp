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
// Created on 2024/10/23.
//

#include "sql/operator/view_scan_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/table/view.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"

using namespace std;

RC ViewScanPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  LOG_INFO("open view scan operator");

  auto& analyzer = view_->analyzer();//->select_exprs();
  if(physical_oper_ == nullptr){
    LogicalPlanGenerator logical_plan_generator;
    for(int id = analyzer.select_exprs_.size() - 1; id >= 0; id--){
      rc = analyzer.select_exprs_[id]->logical_generate();
    }
    if (rc != RC::SUCCESS) return rc;
    std::unique_ptr<LogicalOperator> logical_oper;
    rc = logical_plan_generator.create(view_->select_stmt().get(), logical_oper);
    if (RC::SUCCESS != rc) {
      LOG_WARN("failed to create select_logical_oper when view_scan open, rc=%s", strrc(rc));
      return rc;
    }

    PhysicalPlanGenerator physical_plan_generator;
    rc = physical_plan_generator.create(*logical_oper, physical_oper_);
    if (RC::SUCCESS != rc) {
      LOG_WARN("failed to create select_physical_oper when view_scan open, rc=%s", strrc(rc));
      return rc;
    }
    for(auto& select_expr : analyzer.select_exprs_){
      rc = select_expr->physical_generate();
    }
    if (RC::SUCCESS != rc) {
      LOG_WARN("failed to create select_physical_oper when view_scan open, rc=%s", strrc(rc));
      return rc;
    }
  }

  rc = analyzer.pretreatment();
  if(OB_FAIL(rc))return rc;

  rc = physical_oper_->open(trx);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to open select_physical_oper when view_scan open, rc=%s", strrc(rc));
    return rc;
  }

  trx_ = trx;
  return rc;
}

RC ViewScanPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;

  bool filter_result = false;
  while (OB_SUCC(rc = physical_oper_->next())) {
    tuple_ = physical_oper_->current_tuple();
    if (nullptr == tuple_) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      physical_oper_->close();
      return rc;
    }
    
    rc = filter(*tuple_, filter_result);
    if (rc != RC::SUCCESS) {
      LOG_TRACE("record filtered failed=%s", strrc(rc));
      return rc;
    }

    if (filter_result) {
      sql_debug("get a tuple: %s", tuple_->to_string().c_str());
      break;
    } else {
      sql_debug("a tuple is filtered: %s", tuple_->to_string().c_str());
    }
  }
  return rc;
}

RC ViewScanPhysicalOperator::next(Tuple *upper_tuple)
{
  RC rc = RC::SUCCESS;
  JoinedTuple join_tuple;
  join_tuple.set_left(upper_tuple);

  bool filter_result = false;
  while (OB_SUCC(rc = physical_oper_->next(upper_tuple))) {
    tuple_ = physical_oper_->current_tuple();
    if (nullptr == tuple_) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      physical_oper_->close();
      return rc;
    }

    join_tuple.set_right(tuple_);
    
    rc = filter(join_tuple, filter_result);
    if (rc != RC::SUCCESS) {
      LOG_TRACE("record filtered failed=%s", strrc(rc));
      return rc;
    }

    if (filter_result) {
      sql_debug("get a tuple: %s", tuple_->to_string().c_str());
      break;
    } else {
      sql_debug("a tuple is filtered: %s", tuple_->to_string().c_str());
    }
  }
  return rc;
}

RC ViewScanPhysicalOperator::close() { LOG_INFO("close table scan operator"); return RC::SUCCESS; }

Tuple *ViewScanPhysicalOperator::current_tuple()
{
  return tuple_;
}

string ViewScanPhysicalOperator::param() const { return view_->name(); }

void ViewScanPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC ViewScanPhysicalOperator::filter(Tuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}
