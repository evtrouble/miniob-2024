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


#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, tables_t* table_map, const ConditionSqlNode *conditions, 
    int condition_num, FilterStmt *&stmt, vector<vector<uint32_t>>* depends, int fa)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;
  FilterStmt *tmp_stmt = new FilterStmt();

  vector<uint32_t> select_id;
  vector<Table*> tables;
  size_t min_depend = UINT32_MAX;
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;

    rc = create_filter_unit(db, default_table, table_map, conditions[i], filter_unit, &min_depend);
    if (rc != RC::SUCCESS) {
      delete filter_unit;
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    
    if(filter_unit->right().type == 2)select_id.emplace_back(tmp_stmt->filter_units_.size());
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  auto size = depends->size() - 1;
  if(fa >= 0 && min_depend < size)
    depends->at(size).push_back(min_depend);

  if(select_id.size()){
    for(auto& id : select_id){
      rc = tmp_stmt->filter_units_[id]->right().init_stmt(db, conditions[id].right_select.get(), 
        depends, table_map, size);
      if(rc != RC::SUCCESS){
        delete tmp_stmt;
        return rc;
      }
    }
  }
  
  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, tables_t *table_map,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field, size_t *min_depend)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != table_map) {
    auto iter = table_map->find(attr.relation_name);
    if (iter != table_map->end()) {
      table = iter->second.first;
      *min_depend = std::min(*min_depend, iter->second.second);
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, tables_t* table_map,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit, size_t *min_depend)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  AttrType left = AttrType::UNDEFINED, right = AttrType::UNDEFINED;
  filter_unit = new FilterUnit;

  switch (condition.left_type)
  {
    case 0:{
      FilterObj filter_obj;
      filter_obj.init_value(condition.left_value);
      filter_unit->set_left(filter_obj);
      left = condition.left_value.attr_type();
    }break;
    case 1:{
      Table           *table = nullptr;
      const FieldMeta *field = nullptr;
        
      rc = get_table_and_field(db, default_table, table_map, condition.left_attr, table, field, min_depend);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }

      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_unit->set_left(filter_obj);
      left = field->type();
    }break;
    default: {
      FilterObj filter_obj;
      filter_obj.type = 2;
      filter_unit->set_left(filter_obj);
    }break;
  }

  switch (condition.right_type)
  {
    case 0:{
      FilterObj filter_obj;
      filter_obj.init_value(condition.right_value);
      filter_unit->set_right(filter_obj);
      right = condition.right_value.attr_type();
    }break;
    case 1:{
      Table           *table = nullptr;
      const FieldMeta *field = nullptr;
      rc = get_table_and_field(db, default_table, table_map, condition.right_attr, table, field, min_depend);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      FilterObj filter_obj;
      filter_obj.init_attr(Field(table, field));
      filter_unit->set_right(filter_obj);
      right = field->type();
    }break;
    case 2:{
      FilterObj filter_obj;
      filter_obj.type = 2;
      filter_unit->set_right(filter_obj);
      right = condition.right_select->selection.expressions[0]->value_type();
    }break;
    default: break;
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  switch (comp)
  {
    case CompOp::LIKE_OP: case CompOp::NOT_LIKE:
      if(left != AttrType::CHARS || right != AttrType::CHARS)
        return RC::INVALID_ARGUMENT;
    break;
  
    default:
      break;
  }
  return rc;
}
