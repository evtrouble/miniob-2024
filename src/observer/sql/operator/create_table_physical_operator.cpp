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
// Created by on 2024/10/22.
//

#include "sql/operator/create_table_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "storage/db/db.h"

CreateTablePhysicalOperator::CreateTablePhysicalOperator(Db *db, string &&table_name, std::vector<AttrInfoSqlNode>&& attr_infos, 
    const StorageFormat storage_format)
    : db_(db), table_name_(std::move(table_name)), attr_infos_(std::move(attr_infos)), storage_format_(storage_format)
{}

RC CreateTablePhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open create table operator");
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
  rc = db_->create_table(table_name_.c_str(), attr_infos_, storage_format_);
  if(rc != RC::SUCCESS)return rc;

  Table *table = db_->find_table(table_name_.c_str());
  Record record;
  std::vector<Value> values;

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    values.resize(tuple->cell_num());
    for (int i = 0; i < tuple->cell_num(); i++) {
        tuple->cell_at(i, values[i]);
    }
    rc = table->make_record(values.size(), values.data(), record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      return rc;
    }

    rc = trx->insert_record(table, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
    }

  }

  if (RC::RECORD_EOF == rc) rc = RC::SUCCESS;
  child->close();

  return RC::SUCCESS;
}

RC CreateTablePhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC CreateTablePhysicalOperator::close()
{
    LOG_INFO("close create table operator");
    return RC::SUCCESS;
}
