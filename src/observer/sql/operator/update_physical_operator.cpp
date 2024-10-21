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
    vector<unique_ptr<Expression>>&& values)
    : table_(table), fields_(std::move(fields)), values_(std::move(values))
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open update operator");
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  rc = find_target_columns();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to find column info: %s", strrc(rc));
    return rc;
  }
  trx_ = trx;

  vector<size_t> select_ids;
  Tuple *tuple = nullptr;
  ctl = true;
  vector<Value> values(values_.size());
  
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

    rc = trx_->update_record(table_, record, fields_, values);
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

RC UpdatePhysicalOperator::find_target_columns()
{
  const int sys_field_num  = table_->table_meta().sys_field_num();
  const int user_field_num = table_->table_meta().field_num() - sys_field_num;

  for (size_t c_idx = 0; c_idx < fields_.size(); c_idx++) {
    const FieldMeta* field_meta = fields_[c_idx];
    std::string attr_name = field_meta->name();

    // 先找到要更新的列，获取该列的 id、FieldMeta(offset、length、type)
    for (int i = 0; i < user_field_num; ++i) {
      const FieldMeta *field_meta = table_->table_meta().field(i + sys_field_num);
      const char      *field_name = field_meta->name();
      if (0 != strcmp(field_name, attr_name.c_str())) {
        continue;
      }

      // 判断 类型是否符合要求
      const AttrType value_type = values_[c_idx]->value_type();
      if (AttrType::NULLS == value_type && field_meta->nullable()) {
        // ok
      } else if (value_type != field_meta->type()) {
        if (AttrType::TEXTS == field_meta->type() && AttrType::CHARS == value_type) {
        } else {
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
                  table_->name(), attr_name.c_str(), field_meta->type(), value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }
      fields_id_.emplace_back(i + sys_field_num);
      fields_meta_.emplace_back(*field_meta);
      break;
    }
  }
  
  return RC::SUCCESS;
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