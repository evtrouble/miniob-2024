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

#include "storage/index/index.h"

/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
class IvfflatIndex : public Index
{
public:
  IvfflatIndex(){};
  virtual ~IvfflatIndex() noexcept {};

  RC create(Table *table, const char *file_name, const bool unique, const IndexMeta &index_meta,
      const std::vector<int> &field_ids, const std::vector<const FieldMeta *> &field_metas);

  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
  {

    return RC::UNIMPLEMENTED;
  };

  bool is_vector_index() override { return true; }

  vector<RID> ann_search(const vector<float> &base_vector, size_t limit) { return vector<RID>(); }

  RC close() { return RC::UNIMPLEMENTED; }

  RC insert_entry(const char *record, const RID *rid) override { return RC::UNIMPLEMENTED; }
  RC delete_entry(const char *record, const RID *rid) override { return RC::UNIMPLEMENTED; }
  RC update_entry(const char *record, const RID *rid) override { return RC::UNIMPLEMENTED; }

  RC sync() override { return RC::UNIMPLEMENTED; };
  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive,
                                             const char *right_key, int right_len, bool right_inclusive)
                                              override { return nullptr; }
  RC drop() override { return RC::UNIMPLEMENTED; }

private:
  bool   inited_ = false;
  Table *table_  = nullptr;
  int    lists_  = 1;
  int    probes_ = 1;
  IndexMeta index_meta;
};
