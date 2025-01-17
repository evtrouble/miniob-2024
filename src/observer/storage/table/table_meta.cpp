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
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#include "common/lang/string.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/table/table_meta.h"
#include "storage/trx/trx.h"
#include "json/json.h"

static const Json::StaticString FIELD_TABLE_ID("table_id");
static const Json::StaticString FIELD_TABLE_NAME("table_name");
static const Json::StaticString FIELD_STORAGE_FORMAT("storage_format");
static const Json::StaticString FIELD_FIELDS("fields");
static const Json::StaticString FIELD_INDEXES("indexes");
static constexpr int MAX_VECTORS_LENGTH = 16000;

TableMeta::TableMeta(const TableMeta &other)
    : table_id_(other.table_id_),
      name_(other.name_),
      fields_(other.fields_),
      indexes_(other.indexes_),
      storage_format_(other.storage_format_),
      record_size_(other.record_size_)
{}

void TableMeta::swap(TableMeta &other) noexcept
{
  name_.swap(other.name_);
  fields_.swap(other.fields_);
  indexes_.swap(other.indexes_);
  std::swap(record_size_, other.record_size_);
}

RC TableMeta::init(int32_t table_id, const char *name, const std::vector<FieldMeta> *trx_fields,
    span<const AttrInfoSqlNode> attributes, StorageFormat storage_format)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  if (attributes.size() == 0) {
    LOG_ERROR("Invalid argument. name=%s, field_num=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  int field_offset  = 0;
  int trx_field_num = 0;
  int null_len      = 0;
  //_null

  if (trx_fields != nullptr) {
    fields_.resize(attributes.size() + trx_fields->size() + 1);
    trx_fields_ = *trx_fields;
    null_len    = (attributes.size() + trx_fields->size() + 1 + 7) / 8;  // one field one bit
    fields_[0]  = FieldMeta("__null", AttrType::CHARS, 0, null_len, false, 0, false);
    field_offset += null_len;

    for (size_t i = 0; i < trx_fields->size(); i++) {
      const FieldMeta &field_meta = (*trx_fields)[i];
      fields_[i + 1]              = FieldMeta(field_meta.name(),
          field_meta.type(),
          field_offset,
          field_meta.len(),
          false /*visible*/,
          field_meta.field_id());
      field_offset += field_meta.len();
    }

    trx_field_num = static_cast<int>(trx_fields->size());
  } else {
    fields_.resize(attributes.size() + 1);
    null_len   = (attributes.size() + 1 + 7) / 8;  // one field one bit
    fields_[0] = FieldMeta("__null", AttrType::CHARS, 0, null_len, false, false);
    field_offset += null_len;
  }

  for (size_t i = 0; i < attributes.size(); i++) {
    const AttrInfoSqlNode &attr_info = attributes[i];
    // `i` is the col_id of fields[i]
    rc = fields_[i + trx_field_num + 1].init(attr_info.name.c_str(),
        attr_info.type,
        field_offset,
        attr_info.type == AttrType::VECTORS? attr_info.length * sizeof(float) : attr_info.length,
        true /*visible*/,
        i + trx_field_num + 1, attr_info.nullable);
    if (AttrType::VECTORS_HIGH == fields_[i + trx_field_num + 1].type() && 
    fields_[i + trx_field_num + 1].real_len() > MAX_VECTORS_LENGTH){
      return rc = RC::INVALID_ARGUMENT;
    }
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to init field meta. table name=%s, field name: %s", name, attr_info.name.c_str());
      return rc;
    }

    field_offset += fields_[i + trx_field_num + 1].len();
  }

  record_size_ = field_offset;

  table_id_       = table_id;
  name_           = name;
  storage_format_ = storage_format;
  LOG_INFO("Sussessfully initialized table meta. table id=%d, name=%s", table_id, name);
  return RC::SUCCESS;
}

RC TableMeta::add_index(const IndexMeta &index)
{
  indexes_.emplace_back(index);
  return RC::SUCCESS;
}

const char      *TableMeta::name() const { return name_.c_str(); }
const FieldMeta *TableMeta::null_field() const { return &fields_[0]; }

const FieldMeta *TableMeta::trx_field() const { return &fields_[1]; }

span<const FieldMeta> TableMeta::trx_fields() const
{
  return span<const FieldMeta>(fields_.data() + 1, sys_field_num());
}

const FieldMeta *TableMeta::field(int index) const { return &fields_[index]; }
const FieldMeta *TableMeta::field(const char *name) const
{
  if (nullptr == name) {
    return nullptr;
  }
  for (const FieldMeta &field : fields_) {
    if (0 == strcmp(field.name(), name)) {
      return &field;
    }
  }
  return nullptr;
}

int TableMeta::field_id(const char *name) const
{
  if (nullptr == name) {
    return -1;
  }
  for (size_t id = 0; id < fields_.size(); id++) {
    if (0 == strcmp(fields_[id].name(), name)) {
      return id;
    }
  }
  return -1;
}

const FieldMeta *TableMeta::find_field_by_offset(int offset) const
{
  for (const FieldMeta &field : fields_) {
    if (field.offset() == offset) {
      return &field;
    }
  }
  return nullptr;
}
const int TableMeta::find_field_idx_by_name(const char *field_name) const
{
  for (size_t i = 0; i < fields_.size(); i++) {
    if (0 == strcmp(fields_[i].name(), field_name)) {
      return i;
    }
  }
  return -1;
}

const IndexMeta *TableMeta::find_index_by_fields(std::vector<const char *> fields) const {
  // 找到一个命中字段最多的索引
  size_t nmax = 0;
  const IndexMeta *ret = nullptr;

  for (const IndexMeta &index : indexes_) {
    auto &index_fields = index.fields();
    size_t cnt = 0;
    for (size_t id = sys_field_num(); id < index_fields.size(); id++) {
      bool found = false;
      auto& field = index_fields[id];
      for (auto f : fields)
        if (strcmp(field.name(), f) == 0) {
          found = true;
        }
      if (found)
        cnt++;
      else
        break;
    }
    if (cnt == index_fields.size()) {
      if (nmax < cnt)
        nmax = cnt, ret = &index;
    }
  }
  return ret;
}

int TableMeta::field_num() const { return fields_.size(); }

int TableMeta::sys_field_num() const { return static_cast<int>(trx_fields_.size()) + 1; }  // 1:_null

const IndexMeta *TableMeta::index(const char *name) const
{
  for (const IndexMeta &index : indexes_) {
    if (0 == strcmp(index.name(), name)) {
      return &index;
    }
  }
  return nullptr;
}

const IndexMeta *TableMeta::find_index_by_field(const char *field) const
{
  for (const IndexMeta &index : indexes_) {
    if (0 == strcmp(index.field().at(sys_field_num()).c_str(), field)) {
      // 为什么是at(1),因为at(0)是_null
      return &index;
    }
  }
  return nullptr;
}

const IndexMeta *TableMeta::index(int i) const { return &indexes_[i]; }

int TableMeta::index_num() const { return indexes_.size(); }

int TableMeta::record_size() const { return record_size_; }

int TableMeta::serialize(std::ostream &ss) const
{
  Json::Value table_value;
  table_value[FIELD_TABLE_ID]       = table_id_;
  table_value[FIELD_TABLE_NAME]     = name_;
  table_value[FIELD_STORAGE_FORMAT] = static_cast<int>(storage_format_);

  Json::Value fields_value;
  for (const FieldMeta &field : fields_) {
    Json::Value field_value;
    field.to_json(field_value);
    fields_value.append(std::move(field_value));
  }

  table_value[FIELD_FIELDS] = std::move(fields_value);

  Json::Value indexes_value;
  for (const auto &index : indexes_) {
    Json::Value index_value;
    index.to_json(index_value);
    indexes_value.append(std::move(index_value));
  }
  table_value[FIELD_INDEXES] = std::move(indexes_value);

  Json::StreamWriterBuilder builder;
  Json::StreamWriter       *writer = builder.newStreamWriter();

  std::streampos old_pos = ss.tellp();
  writer->write(table_value, &ss);
  int ret = (int)(ss.tellp() - old_pos);

  delete writer;
  return ret;
}

int TableMeta::deserialize(std::istream &is)
{
  Json::Value             table_value;
  Json::CharReaderBuilder builder;
  std::string             errors;

  std::streampos old_pos = is.tellg();
  if (!Json::parseFromStream(builder, is, &table_value, &errors)) {
    LOG_ERROR("Failed to deserialize table meta. error=%s", errors.c_str());
    return -1;
  }

  const Json::Value &table_id_value = table_value[FIELD_TABLE_ID];
  if (!table_id_value.isInt()) {
    LOG_ERROR("Invalid table id. json value=%s", table_id_value.toStyledString().c_str());
    return -1;
  }

  int32_t table_id = table_id_value.asInt();

  const Json::Value &table_name_value = table_value[FIELD_TABLE_NAME];
  if (!table_name_value.isString()) {
    LOG_ERROR("Invalid table name. json value=%s", table_name_value.toStyledString().c_str());
    return -1;
  }

  std::string table_name = table_name_value.asString();

  const Json::Value &fields_value = table_value[FIELD_FIELDS];
  if (!fields_value.isArray() || fields_value.size() <= 0) {
    LOG_ERROR("Invalid table meta. fields is not array, json value=%s", fields_value.toStyledString().c_str());
    return -1;
  }

  const Json::Value &storage_format_value = table_value[FIELD_STORAGE_FORMAT];
  if (!table_id_value.isInt()) {
    LOG_ERROR("Invalid storage format. json value=%s", storage_format_value.toStyledString().c_str());
    return -1;
  }

  int32_t storage_format = storage_format_value.asInt();

  RC  rc        = RC::SUCCESS;
  int field_num = fields_value.size();

  std::vector<FieldMeta> fields(field_num);
  for (int i = 0; i < field_num; i++) {
    FieldMeta &field = fields[i];

    const Json::Value &field_value = fields_value[i];
    rc                             = FieldMeta::from_json(field_value, field);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to deserialize table meta. table name =%s", table_name.c_str());
      return -1;
    }
  }

  auto comparator = [](const FieldMeta &f1, const FieldMeta &f2) { return f1.offset() < f2.offset(); };
  std::sort(fields.begin(), fields.end(), comparator);

  table_id_       = table_id;
  storage_format_ = static_cast<StorageFormat>(storage_format);
  name_.swap(table_name);
  fields_.swap(fields);
  record_size_ = fields_.back().offset() + fields_.back().len() - fields_.begin()->offset();

  for (size_t id = 1; id < fields_.size(); id++) {
    if (!fields_[id].visible()) {
      trx_fields_.emplace_back(fields_[id]);  // 字段加上trx标识更好
    }
  }

  const Json::Value &indexes_value = table_value[FIELD_INDEXES];
  if (!indexes_value.empty()) {
    if (!indexes_value.isArray()) {
      LOG_ERROR("Invalid table meta. indexes is not array, json value=%s", fields_value.toStyledString().c_str());
      return -1;
    }
    const int              index_num = indexes_value.size();
    std::vector<IndexMeta> indexes(index_num);
    for (int i = 0; i < index_num; i++) {
      IndexMeta &index = indexes[i];

      const Json::Value &index_value = indexes_value[i];
      rc                             = IndexMeta::from_json(*this, index_value, index);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to deserialize table meta. table name=%s", table_name.c_str());
        return -1;
      }
    }
    indexes_.swap(indexes);
  }

  return (int)(is.tellg() - old_pos);
}

int TableMeta::get_serial_size() const { return -1; }

void TableMeta::to_string(std::string &output) const {}

void TableMeta::desc(std::ostream &os) const
{
  os << name_ << '(' << std::endl;
  for (const auto &field : fields_) {
    os << '\t';
    field.desc(os);
    os << std::endl;
  }

  for (const auto &index : indexes_) {
    os << '\t';
    index.desc(os);
    os << std::endl;
  }
  os << ')' << std::endl;
}
