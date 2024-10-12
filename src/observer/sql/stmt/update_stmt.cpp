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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, const std::vector<const FieldMeta *>&& fields, 
  const vector<Value>&& values, FilterStmt *filter_stmt, std::unordered_map<size_t, void*>&& stmt_map)
  : table_(table), fields_(move(fields)), values_(move(values)), filter_stmt_(filter_stmt), stmt_map_(move(stmt_map))
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt, 
  vector<vector<uint32_t>>* depends, tables_t* table_map, int fa)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || update.attribute_names.empty() || 
    update.attribute_names.size() != update.values.size()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, attribute_num=%d value_num=%d",
        db, table_name, update.attribute_names.size(), update.values.size());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields existence
  const TableMeta &table_meta = table->table_meta();
  const FieldMeta *field;

  std::vector<const FieldMeta *> fields;

  auto size = depends->size();
  for(auto& attribute_name : update.attribute_names){
    field = table_meta.field(attribute_name.c_str());
    if (nullptr == field) {
      LOG_WARN("schema mismatch. field %s doesn't exist.", attribute_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.emplace_back(field);
  }
    
  if(!table_map->count(table_name)){
    auto temp = std::make_pair(table, size);
    table_map->insert({table_name, temp});
  }

  depends->push_back(vector<uint32_t>());

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), 
      filter_stmt, depends, fa);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  std::unordered_map<size_t, void*> stmt_map;
  vector<Value> values;
  Stmt* sub_stmt;
  for(auto& value : update.values){
    if(value.attr_type() == AttrType::SELECT){
      rc = Stmt::create_stmt(db, *(ParsedSqlNode*)value.data(), sub_stmt, depends, table_map, size);
      if(rc != RC::SUCCESS)return rc;
      stmt_map.insert({values.size(), sub_stmt});
      values.emplace_back(Value());
    }else{
      values.emplace_back(std::move(value));
    }
  }

  if(table_map->at(table_name).second == size){
    table_map->erase(table_name);
  }

  // everything alright
  stmt = new UpdateStmt(table, move(fields), move(values), filter_stmt, move(stmt_map));
  return RC::SUCCESS;
}