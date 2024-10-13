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

#include "sql/operator/update_physical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/expr/expression.h"

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, vector<const FieldMeta *> &&fields,
    vector<Value> &&values, std::unordered_map<size_t, void*>&& select_map)
    : table_(table), fields_(std::move(fields)), values_(std::move(values)), select_map_(move(select_map))
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  vector<size_t> select_ids;

  Tuple *tuple = nullptr;
  for(size_t id = 0; id < values_.size(); id++){
    if(select_map_.count(id)){
      SelectExpr* temp = (SelectExpr*)select_map_[id];
      if(temp->check()){
        temp->get_value(*tuple, values_[id]); 
        if(rc != RC::SUCCESS)return rc;
      }
      else select_ids.emplace_back(id);
    }
  }

  // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  while (OB_SUCC(rc = child->next())) {
    tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    for(auto& id : select_ids){
      rc = ((SelectExpr*)select_map_[id])->get_value(*tuple, values_[id]);
      if(rc != RC::SUCCESS)return rc;
    }

    rc = trx_->update_record(table_, record, fields_, values_);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  child->close();
  
  return RC::SUCCESS;
}


RC UpdatePhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  return RC::SUCCESS;
}

UpdatePhysicalOperator::~UpdatePhysicalOperator() 
{
  for(auto& [id, select] : select_map_){
    delete (SelectExpr*)select;
  }
  select_map_.clear();
}