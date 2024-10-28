/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <unordered_map>

#include "storage/index/index.h"
#include "sql/expr/expression.h"

struct Calculator
{
public:
  void init(VectorOperationExpr::Type type, int length)
  {
    attr_length_ = length;
    type_ = type;
  }

  float operator()(Value &left, Value &right)
  {
    result_.set_type(AttrType::VECTORS);
    switch (type_)
    {
      case VectorOperationExpr::Type::COSINE_DISTANCE:
        left.cosine_distance(left, right, result_);
        return result_.get_float();
      case VectorOperationExpr::Type::INNER_PRODUCT:
        left.inner_product(left, right, result_);
        return result_.get_float();
      case VectorOperationExpr::Type::L2_DISTANCE:
        left.l2_distance(left, right, result_);
        return result_.get_float();
      default:
        return 0;
    }
  }

  int      attr_length_;
  VectorOperationExpr::Type type_;
  Value    result_;
};

/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */

class IvfflatIndex : public Index
{
public:
  IvfflatIndex() = default;
  virtual ~IvfflatIndex() noexcept = default;

  RC create(Table *table, VectorIndexNode &vector_index, const FieldMeta *field_meta, const IndexMeta &index_meta);
  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
  {
    return RC::UNIMPLEMENTED;
  };

  bool is_vector_index() override { return true; }

  vector<RID> ann_search(const vector<float> &base_vector, size_t limit);

  RC close() { return RC::UNIMPLEMENTED; }

  RC insert_entry(const char *record, const RID *rid) override;
  RC delete_entry(const char *record, const RID *rid) override;
  RC update_entry(const char *record, const RID *rid) override;

  RC sync() override { return RC::UNIMPLEMENTED; };
  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive,
                                             const char *right_key, int right_len, bool right_inclusive)
                                              override { return nullptr; }
  RC drop() override { return RC::UNIMPLEMENTED; }

  VectorOperationExpr::Type type() { return calculator_.type_; }

private:
  void k_means();

  size_t get_id(Value &value)
  {
    size_t id = 0;
    float mmin = 1e38;
    int size = std::min(lists_, num);
    for(int i = 0; i < size; i++){
      float temp = calculator_(centers_[i], value); 
      if(mmin > temp){
        mmin = temp;
        id = i;
      }
    }
    return id;
  }

private:
  constexpr static int upper_limit = 10;
  bool   inited_ = false;
  Table *table_  = nullptr;
  int    lists_  = 1;
  int    probes_ = 1;
  int      attr_offset_;
  Calculator  calculator_;
  vector<Value> centers_;
  vector<Value> before_centers;
  vector<vector<RID>> clusters_;
  unordered_map<RID, Value, RIDHash> records_;
  int num = 0;
};
