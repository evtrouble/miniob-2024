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
// Created by WangYunlai on 2022/11/18.
//

#include "sql/executor/sql_result.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "session/session.h"
#include "storage/trx/trx.h"

SqlResult::SqlResult(Session *session) : session_(session) {}

void SqlResult::set_tuple_schema(const TupleSchema &schema) { tuple_schema_ = schema; }

RC SqlResult::open()
{
  RC rc = RC::SUCCESS;
  if (nullptr == operator_) {
    return RC::INVALID_ARGUMENT;
  }

  Trx *trx = session_->current_trx();
  trx->start_if_need();

  if(analyzer_.select_exprs_ != nullptr){
    for(auto& select_expr : *analyzer_.select_exprs_){
      select_expr->set_trx(trx);
    }

    rc = analyzer_.pretreatment();
    if(rc != RC::SUCCESS)return rc;
  }

  return operator_->open(trx);
}

RC SqlResult::close()
{
  if (nullptr == operator_) {
    return RC::INVALID_ARGUMENT;
  }
  RC rc = operator_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close operator. rc=%s", strrc(rc));
  }

  operator_.reset();

  if (session_ && !session_->is_trx_multi_operation_mode()) {
    if (rc == RC::SUCCESS) {
      rc = session_->current_trx()->commit();
    } else {
      RC rc2 = session_->current_trx()->rollback();
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("rollback failed. rc=%s", strrc(rc2));
      }
    }
  }
  return rc;
}

RC SqlResult::next_tuple(Tuple *&tuple)
{
  RC rc = operator_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  tuple = operator_->current_tuple();
  return rc;
}

RC SqlResult::next_chunk(Chunk &chunk)
{
  RC rc = operator_->next(chunk);
  return rc;
}

void SqlResult::set_operator(std::unique_ptr<PhysicalOperator> oper)
{
  ASSERT(operator_ == nullptr, "current operator is not null. Result is not closed?");
  operator_ = std::move(oper);
  operator_->tuple_schema(tuple_schema_);
}

void SqlResult::set_depends(unique_ptr<vector<vector<uint32_t>>> depends)
{
  analyzer_.depends_ = std::move(depends); 
}

void SqlResult::set_exprs(unique_ptr<vector<SelectExpr*>> select_exprs)
{
  analyzer_.select_exprs_ = std::move(select_exprs); 
}