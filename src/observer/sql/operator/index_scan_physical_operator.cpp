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
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/index_scan_physical_operator.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

IndexScanPhysicalOperator::IndexScanPhysicalOperator(Table *table, Index *index, ReadWriteMode mode, 
                                                     const std::vector<Value> &left_value, bool left_inclusive,
                                                     const std::vector<Value> &right_value, bool right_inclusive)
    : table_(table), index_(index), mode_(mode), left_inclusive_(left_inclusive),
      right_inclusive_(right_inclusive) 
{
  const std::vector<FieldMeta>& fields = index_->index_meta().fields();
  size_ = 0;
  for (auto &field : fields) {
    size_ += field.len();
  }

  left_value_.resize(size_);
  right_value_.resize(size_);
  RC rc = RC::SUCCESS;
  rc = make_data(left_value, fields, table, left_value_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("fail to make data");
  }
  rc = make_data(right_value, fields, table, right_value_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("fail to make data");
  }
}

RC IndexScanPhysicalOperator::open(Trx *trx)
{
  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }
  LOG_INFO("open index scanner operator");

  IndexScanner *index_scanner =
      index_->create_scanner(left_value_.data(), size_, left_inclusive_, 
      right_value_.data(), size_, right_inclusive_);
  if (nullptr == index_scanner) {
    LOG_WARN("failed to create index scanner");
    return RC::INTERNAL;
  }

  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    LOG_WARN("invalid record handler");
    index_scanner->destroy();
    return RC::INTERNAL;
  }
  index_scanner_ = index_scanner;

  tuple_.set_schema(table_, table_->table_meta().field_metas());

  trx_ = trx;
  return RC::SUCCESS;
}

RC IndexScanPhysicalOperator::next()
{
  RID rid;
  RC  rc = RC::SUCCESS;

  bool filter_result = false;
  while (RC::SUCCESS == (rc = index_scanner_->next_entry(&rid))) {
    rc = record_handler_->get_record(rid, current_record_);
    if (OB_FAIL(rc)) {
      LOG_TRACE("failed to get record. rid=%s, rc=%s", rid.to_string().c_str(), strrc(rc));
      return rc;
    }

    LOG_TRACE("got a record. rid=%s", rid.to_string().c_str());

    tuple_.set_record(&current_record_);
    rc = filter(tuple_, filter_result);
    if (OB_FAIL(rc)) {
      LOG_TRACE("failed to filter record. rc=%s", strrc(rc));
      return rc;
    }

    if (!filter_result) {
      LOG_TRACE("record filtered");
      continue;
    }

    rc = trx_->visit_record(table_, current_record_, mode_);
    if (rc == RC::RECORD_INVISIBLE) {
      LOG_TRACE("record invisible");
      continue;
    } else {
      return rc;
    }
  }

  return rc;
}

RC IndexScanPhysicalOperator::close()
{
  index_scanner_->destroy();
  index_scanner_ = nullptr;
  LOG_INFO("close index scanner operator");
  return RC::SUCCESS;
}

Tuple *IndexScanPhysicalOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

void IndexScanPhysicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC IndexScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (std::unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}

std::string IndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}

RC IndexScanPhysicalOperator::make_data(const std::vector<Value> &values, const std::vector<FieldMeta> &meta, Table *table,
                                        std::vector<char> &out) {
  std::vector<char> ret;
  int size = 0;
  for (auto &field : meta) {
    size += field.len();
  }
  ret.resize(size);
  char *beg = ret.data();
  beg += meta[0].len();
  for (size_t i = 0; i < values.size() && i + 1 < meta.size(); i++) {
    Value &value = const_cast<Value &>(values[i]);
    Value result;
    Value::cast_to(value, meta[i + 1].type(), result);
    memcpy(beg, result.data(), meta[i + 1].len());
    beg += meta[i + 1].len();
  }
  out.swap(ret);
  return RC::SUCCESS;
}