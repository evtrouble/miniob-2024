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
// Created on 2024/10/15.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include <vector>
#include <fstream>
#include <string>
#include <queue>

/**
 * @brief 更新物理算子
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>>&& order_by, std::vector<bool>&& is_asc, int limit);

  virtual ~OrderByPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  RC next(Tuple *upper_tuple) override;

  Tuple *current_tuple() override;
  int    limit() { return limit_; }

private:
  RC fetch_next();
  RC fetch_next_external();
  RC load_next_tuple_from_run(size_t run_index);
  RC read_single_tuple_from_stream(ValueListTuple& tuple, std::ifstream& file);

  RC sort_in_memory();
  RC     limit_sort(Tuple *upper_tuple = nullptr);
  RC     external_sort(Tuple *upper_tuple = nullptr);
  RC     external_sort_with_cached_data(Tuple *upper_tuple, size_t cached_count);
  RC     adaptive_sort(Tuple *upper_tuple = nullptr);
  bool     cmp(const vector<Value>& a_vals, const vector<Value>& b_vals) const;
  
  // 外排序相关方法
  RC write_chunk_to_file(const std::vector<ValueListTuple>& chunk, const std::string& filename);
  RC cleanup_temp_files();
  std::string create_temp_file();
  
  // 辅助方法：排序并写入临时文件
  RC sort_and_write_chunk(const std::vector<ValueListTuple>& chunk, std::string& temp_file);
 
private:
  std::vector<std::unique_ptr<Expression>> order_by_;
  std::vector<bool>                        is_asc_;
  bool                                     first_emited_ = false;  /// 第一条数据是否已经输出
  bool                                     have_value = false;
  vector<ValueListTuple>                   value_list_;
  vector<size_t>                           ids_;     
  vector<vector<Value>>                    order_values_;        
  size_t                                   current_id_;
  int                                      limit_ = -1;
  
  // Helper struct for the merge priority queue
  struct MergeElement {
    std::vector<Value> sort_keys;
    size_t run_index;
  };

  // Custom comparator for the priority queue
  struct MergeElementComparator {
    const OrderByPhysicalOperator* op_;
    MergeElementComparator(const OrderByPhysicalOperator* op) : op_(op) {}
    // For min-heap, return true if a should come after b
    bool operator()(const MergeElement& a, const MergeElement& b) const {
      return !op_->cmp(a.sort_keys, b.sort_keys);
    }
  };

  // 外排序相关成员变量
  std::vector<std::string>                 temp_files_;           /// 临时文件列表
  size_t                                   chunk_size_;           /// 每个块的大小
  size_t                                   memory_threshold_;     /// 内存阈值（字节）
  static constexpr size_t                  DEFAULT_CHUNK_SIZE = 1000;  /// 默认块大小
  static constexpr size_t                  DEFAULT_MEMORY_THRESHOLD = 8 * 1024 * 1024;  /// 默认内存阈值 8MB
  
  // 外排序流式处理相关
  bool                                     is_external_sort_ = false;  /// 是否使用外排序
  std::vector<std::ifstream>               file_streams_;        /// 多路归并时的文件流
  std::vector<ValueListTuple>              current_tuples_;      /// 每个run的当前tuple
  std::vector<bool>                        run_exhausted_;       /// 每个run是否已耗尽
  std::unique_ptr<std::priority_queue<MergeElement, std::vector<MergeElement>, MergeElementComparator>> merge_pq_;
  ValueListTuple                           current_external_tuple_;
};
