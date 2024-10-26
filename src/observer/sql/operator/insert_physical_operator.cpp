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
  if (!view->allow_write()) {
    LOG_ERROR("view %s is not allow to insert", view->name());
    return RC::SCHEMA_FIELD_MISSING;
  }
  RC rc = RC::SUCCESS;
  auto &map_exprs = view->map_exprs();
  std::unordered_map<const BaseTable*, std::vector<size_t>> table_columns;
  vector<size_t> col_ids(map_exprs.size());
  for (size_t i = 0; i < map_exprs.size(); i++) {
    auto field = static_cast<FieldExpr*>(map_exprs[i].get());

    // 查找view中的列在原始表中的位置
    const BaseTable *table = field->table();
    if(table->is_view()){
      LOG_ERROR("should not insert view directly");
      return RC::INTERNAL;
    }
    const int sys_field_num = table->table_meta().sys_field_num();
    int field_idx = table->table_meta().find_field_idx_by_name(field->field_name());
    col_ids[i] = field_idx - sys_field_num;
    
    auto iter = table_columns.find(field->table());
    if (table_columns.end() == iter) {
      table_columns.emplace(field->table(), std::vector<size_t>{i});
    } else {
      iter->second.emplace_back(i);
    }
  }

  // 按顺序对每张表 补齐Value，构造Record
  bool is_fail = false;
  std::unordered_map<Table*, std::vector<Record>> table_records;
  
  for (auto& [base_table, column] : table_columns) {
    // 对一张原始表的插入
    Table *table = static_cast<Table*>(const_cast<BaseTable*>(base_table));
    vector<Record> records;
    table_records.insert({table, std::vector<Record>()});

    for (std::vector<Value>& row_value : values_set_) {
      // 补齐一行数据
      std::vector<Value> fixed_row_value(table->table_meta().field_num() - table->table_meta().sys_field_num(), Value((void*)nullptr));
      for (auto& id : column) {
        fixed_row_value[col_ids[id]] = row_value[id];
      }

      // 插入一行数据
      Record rcd;
      rc = table->make_record(static_cast<int>(fixed_row_value.size()), fixed_row_value.data(), rcd);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record. rc=%s", strrc(rc));
        is_fail = true;
        break;
      }
      rc = trx->insert_record(table, rcd);
      if (rc != RC::SUCCESS) {
        is_fail = true;
        break;  // 插入失败，回滚后应该停止继续插入
      }
      table_records[table].emplace_back(rcd);
    } 
    if(is_fail)break;   
  }

  if(is_fail){
    LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
    // 插入失败，需要回滚之前插入成功的记录
    RC rc2 = RC::SUCCESS;
    for (auto& [table, records] : table_records) {
      for(auto& done_rcd : records){
        rc2 = trx->delete_record(table, done_rcd);
        if (RC::SUCCESS != rc2) {
          LOG_WARN("failed to rollback record after insert failed. rc=%s", strrc(rc2));
          break;
        }
      }
      if(RC::SUCCESS != rc2)break;
    }
  }
  return rc;
}