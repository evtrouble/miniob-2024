/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

InsertStmt::InsertStmt(BaseTable *table, vector<vector<Value>>&& values_set)
    : table_(table), values_set_(std::move(values_set))
{}

RC InsertStmt::create(Db *db, InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  BaseTable *table = db->find_base_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();

  vector<vector<Value>> row_values(inserts.values);
  vector<size_t> cols_id;
  if(inserts.attrs_name.size() != 0){
    cols_id.resize(inserts.attrs_name.size());
    for(size_t id = 0; id < cols_id.size(); id++){
      auto field = table_meta.field(inserts.attrs_name[id].c_str());
      cols_id[id] = field->field_id() - table_meta.sys_field_num();
    }
  }

  for(size_t id = 0; id < inserts.values.size(); id++){
    auto& values = inserts.values[id];
    const int        value_num  = static_cast<int>(values.size());
    auto& row_value = row_values[id];

    if(inserts.attrs_name.size() != 0){
      row_value.resize(field_num, Value((void*)nullptr));
      for(size_t i = 0; i < cols_id.size(); i++){
        row_value[cols_id[i]] = values[i];
      }
      continue;
    }

    if (field_num != value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // 检查TEXT的长度
    for (int i = 0; i < field_num; i++) {
      const FieldMeta *field_meta = table_meta.field(i + table_meta.sys_field_num());
      const AttrType field_type = field_meta->type();
      const AttrType value_type = values[i].attr_type();
      if (AttrType::TEXTS == field_type && AttrType::CHARS == value_type) {
        if (MAX_TEXT_LENGTH < values[i].length()) {
          LOG_WARN("Text length:%d, over max_length 65535", values[i].length());
          return RC::INVALID_ARGUMENT;
        }
      }
    }

    row_value.swap(inserts.values[id]);
  }

  // everything alright
  stmt = new InsertStmt(table, std::move(row_values));
  return RC::SUCCESS;
}
