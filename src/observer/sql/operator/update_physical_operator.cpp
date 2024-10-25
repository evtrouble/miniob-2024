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
#include "storage/table/view.h"
#include "storage/trx/trx.h"
#include "sql/expr/expression.h"

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(BaseTable *base_table, vector<const FieldMeta *> &&fields,
    vector<unique_ptr<Expression>>&& values)
    : base_table_(base_table), fields_(std::move(fields)), values_(std::move(values))
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open update operator");
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  RC rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  if(base_table_->is_table())return update_table();
  return update_view();
}

RC UpdatePhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  LOG_INFO("close update operator");
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::init(vector<Value> &values)
{
  RC rc = RC::SUCCESS;

  for(size_t id = 0; id < values_.size(); id++){
    rc = values_[id]->try_get_value(values[id]);
    if(rc == RC::NULL_TUPLE)rc = RC::SUCCESS;
    if(rc != RC::SUCCESS)return rc;
  }
  return rc;
}

RC UpdatePhysicalOperator::update_table()
{
  RC rc = RC::SUCCESS;
  Tuple *tuple = nullptr;
  ctl = true;
  vector<Value> values(values_.size());
  std::unique_ptr<PhysicalOperator> &child = children_[0];
  Table *table = static_cast<Table*>(base_table_);

  // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  while (OB_SUCC(rc = child->next())) {
    tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      child->close();
      return rc;
    }

    if(ctl){
      rc = init(values);
      ctl = false;
      if(rc != RC::SUCCESS)
        return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();

    rc = trx_->update_record(table, record, fields_, values);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      child->close();
      return rc;
    }
  }

  if(rc == RC::RECORD_EOF)
    rc = RC::SUCCESS;

  child->close();
  return rc;
}

RC UpdatePhysicalOperator::update_view()
{
  View *view = static_cast<View*>(base_table_);
  if (!view->allow_write()) {
    LOG_ERROR("view %s is not allow to insert", view->name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  RC rc = RC::SUCCESS;
  const std::vector<Field> &map_fields = view->map_fields();
  std::unordered_map<const BaseTable*, std::vector<size_t>> table_columns;

  Tuple *tuple = nullptr;
  ctl = true;
  vector<Value> values(values_.size());
  std::unique_ptr<PhysicalOperator> &child = children_[0];

  std::unordered_map<const BaseTable*, unordered_set<RID, RIDHash>> table_rids;

  const BaseTable* base_table;
  RID rid;
  const int sys_field_num = base_table_->table_meta().sys_field_num();
  // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  while (OB_SUCC(rc = child->next())) {
    tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      child->close();
      return rc;
    }

    if(ctl){
      for (size_t i = 0; i < fields_.size(); i++) {
        const FieldMeta *field = fields_[i];

        // 原始表要更新的列有哪些
        const BaseTable *table = map_fields[field->field_id() - sys_field_num].table();
        if(table->is_view()){
          LOG_ERROR("should not update view directly");
          return RC::INTERNAL;
        }
    
        auto iter = table_columns.find(table);
        if (table_columns.end() == iter) {
          table_columns.emplace(table, std::vector<size_t>{i});
        } else {
          iter->second.emplace_back(i);
        }
      }   
      rc = init(values);
      ctl = false;
      if(rc != RC::SUCCESS)
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
    }
  }
  if(rc != RC::RECORD_EOF)return rc;

  Record record;
  for (auto& [base_table, column] : table_columns) {
    // 对一张原始表的插入
    Table *table = static_cast<Table*>(const_cast<BaseTable*>(base_table));
    vector<Value> temp_values;
    vector<const FieldMeta*> fieldmetas;

    for (auto& id : column) {
      temp_values.emplace_back(move(values[id]));
      fieldmetas.emplace_back(fields_[id]);
    }
    for(auto& rid : table_rids[base_table]){
      table->get_record(rid, record);
      rc = trx_->update_record(table, record, fieldmetas, temp_values);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to update record: %s", strrc(rc));
        child->close();
        return rc;
      }
    }
  }
    
  child->close();
  return RC::SUCCESS;
}