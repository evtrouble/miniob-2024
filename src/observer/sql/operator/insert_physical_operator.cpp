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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/insert_physical_operator.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/table/table.h"
#include "storage/table/view.h"
#include "storage/trx/trx.h"

using namespace std;

InsertPhysicalOperator::InsertPhysicalOperator(BaseTable *base_table, std::vector<std::vector<Value>> &&values_set)
    : base_table_(base_table), values_set_(std::move(values_set))
{}

RC InsertPhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open insert operator");
  if(base_table_->is_table())return insert_table(trx);
  return insert_view(trx);
}

RC InsertPhysicalOperator::next() { return RC::RECORD_EOF; }

RC InsertPhysicalOperator::close() { LOG_INFO("close insert operator"); return RC::SUCCESS; }

RC InsertPhysicalOperator::insert_table(Trx *trx)
{
  Record record;
  RC     rc = RC::SUCCESS;
  Table *table = static_cast<Table*>(base_table_);
  vector<Record>records(values_set_.size());
  for(size_t i = 0; i < values_set_.size(); i++){
    rc = table->make_record(static_cast<int>(values_set_.at(i).size()), values_set_.at(i).data(), records[i]);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      return rc;
    }
  }
  for(auto& record : records){
    rc = trx->insert_record(table, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC InsertPhysicalOperator::insert_view(Trx *trx)
{
  View *view = static_cast<View*>(base_table_);
  if(!view->allow_write())return RC::INVALID_ARGUMENT;
  return RC::SUCCESS;
}