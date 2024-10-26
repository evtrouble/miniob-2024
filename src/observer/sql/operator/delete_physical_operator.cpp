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
// Created by WangYunlai on 2022/6/27.
//

#include "sql/operator/delete_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/table/view.h"
#include "storage/trx/trx.h"

RC DeletePhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open delete operator");
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  RC rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;
  if(base_table_->is_table())return delete_table();
  return delete_view();
}

RC DeletePhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC DeletePhysicalOperator::close()
{
  LOG_INFO("close delete operator");
  return RC::SUCCESS;
}

RC DeletePhysicalOperator::delete_table()
{
  RC rc = RC::SUCCESS;
  std::unique_ptr<PhysicalOperator> &child = children_[0];
  Table *table = static_cast<Table*>(base_table_);
  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  child->close();

  // 先收集记录再删除
  // 记录的有效性由事务来保证，如果事务不保证删除的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  for (Record &record : records_) {
    rc = trx_->delete_record(table, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC DeletePhysicalOperator::delete_view()
{
  RC rc = RC::SUCCESS;
  std::unique_ptr<PhysicalOperator> &child = children_[0];

  std::unordered_map<const BaseTable*, unordered_set<RID, RIDHash>> table_rids;
  const BaseTable* base_table;
  RID rid;
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_raw_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    int size = tuple->get_tuple_size();
    for(int i = 0; i < size; i++){
      tuple->get_tuple_rid(i, base_table, rid);
      auto iter = table_rids.find(base_table);
      if (table_rids.end() == iter) {
        table_rids.emplace(base_table, unordered_set<RID, RIDHash>{rid});
      } else {
        iter->second.insert(rid);
      }
    
    } // end delete one record from tables
  }
  child->close();

  Record record;
  for (auto& [base_table, rids] : table_rids) {
    // 对一张原始表的插入
    Table *table = static_cast<Table*>(const_cast<BaseTable*>(base_table));

    for(auto& rid : rids){
      table->get_record(rid, record);
      rc = trx_->delete_record(table, record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to delete record: %s", strrc(rc));
        child->close();
        return rc;
      }
    }
  }
  
  return RC::SUCCESS;
}