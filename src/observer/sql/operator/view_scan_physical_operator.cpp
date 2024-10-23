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

using namespace std;

RC ViewScanPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  // LOG_INFO("open table scan operator");
  // RC rc = view_->get_record_scanner(record_scanner_, trx, mode_);
  // if (rc == RC::SUCCESS) {
  //   tuple_.set_schema(table_, table_->table_meta().field_metas());
  // }
  trx_ = trx;
  return rc;
}

RC ViewScanPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;

  // bool filter_result = false;
  // while (OB_SUCC(rc = record_scanner_.next(current_record_))) {
  //   LOG_TRACE("got a record. rid=%s", current_record_.rid().to_string().c_str());
    
  //   tuple_.set_record(&current_record_);
  //   rc = filter(tuple_, filter_result);
  //   if (rc != RC::SUCCESS) {
  //     LOG_TRACE("record filtered failed=%s", strrc(rc));
  //     return rc;
  //   }

  //   if (filter_result) {
  //     sql_debug("get a tuple: %s", tuple_.to_string().c_str());
  //     break;
  //   } else {
  //     sql_debug("a tuple is filtered: %s", tuple_.to_string().c_str());
  //   }
  // }
  return rc;
}

RC ViewScanPhysicalOperator::next(Tuple *upper_tuple)
{
  RC rc = RC::SUCCESS;
  // JoinedTuple join_tuple;
  // join_tuple.set_left(upper_tuple);

  // bool filter_result = false;
  // while (OB_SUCC(rc = record_scanner_.next(current_record_))) {
  //   LOG_TRACE("got a record. rid=%s", current_record_.rid().to_string().c_str());
    
  //   tuple_.set_record(&current_record_);
    
  //   join_tuple.set_right(&tuple_);

  //   rc = filter(join_tuple, filter_result);
  //   if (rc != RC::SUCCESS) {
  //     LOG_TRACE("record filtered failed=%s", strrc(rc));
  //     return rc;
  //   }

  //   if (filter_result) {
  //     sql_debug("get a tuple: %s", tuple_.to_string().c_str());
  //     break;
  //   } else {
  //     sql_debug("a tuple is filtered: %s", tuple_.to_string().c_str());
  //   }
  // }
  return rc;
}

RC ViewScanPhysicalOperator::close() { LOG_INFO("close table scan operator"); return RC::SUCCESS; }

Tuple *ViewScanPhysicalOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

string ViewScanPhysicalOperator::param() const { return view_->name(); }

void ViewScanPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC ViewScanPhysicalOperator::filter(Tuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  // Value value;
  // for (unique_ptr<Expression> &expr : predicates_) {
  //   rc = expr->get_value(tuple, value);
  //   if (rc != RC::SUCCESS) {
  //     return rc;
  //   }

  //   bool tmp_result = value.get_boolean();
  //   if (!tmp_result) {
  //     result = false;
  //     return rc;
  //   }
  // }

  result = true;
  return rc;
}
