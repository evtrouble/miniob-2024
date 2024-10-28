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
// Created on 2024/10/28.
//

#include "sql/operator/vector_index_scan_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/index/ivfflat_index.h"

using namespace std;

RC VectorIndexScanPhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open vector index scan operator");
  
  tuple_.set_schema(table_, table_->table_meta().field_metas());
  trx_ = trx;

  if(limit_ == -1)return RC::INVALID_ARGUMENT;

  IvfflatIndex* index = static_cast<IvfflatIndex*>(index_);
  records_ = index->ann_search(*base_vector_.get_vector(), limit_);
  current_id_ = 0;
  return RC::SUCCESS;
}

RC VectorIndexScanPhysicalOperator::next()
{
  if(current_id_ == records_.size())return RC::RECORD_EOF;

  RC rc = table_->get_record(records_[current_id_], current_record_);
  if(OB_FAIL(rc))return rc;
  tuple_.set_record(&current_record_);
  current_id_++;

  sql_debug("get a tuple: %s", tuple_.to_string().c_str());
  return rc;
}

RC VectorIndexScanPhysicalOperator::close() { LOG_INFO("close vector index scan operator"); return RC::SUCCESS; }

Tuple *VectorIndexScanPhysicalOperator::current_tuple()
{
  return &tuple_;
}

string VectorIndexScanPhysicalOperator::param() const { return table_->name(); }