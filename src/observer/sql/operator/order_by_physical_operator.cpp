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

#include <queue>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include "sql/operator/order_by_physical_operator.h"

using namespace std;

OrderByPhysicalOperator::OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>>&& order_by, std::vector<bool>&& is_asc, int limit)
    : order_by_(std::move(order_by)), is_asc_(std::move(is_asc)), limit_(limit), chunk_size_(DEFAULT_CHUNK_SIZE), memory_threshold_(DEFAULT_MEMORY_THRESHOLD){}

RC OrderByPhysicalOperator::open(Trx *trx)
{
    LOG_INFO("open order by operator");
    if (children_.empty()) {
        return RC::SUCCESS;
    }

    std::unique_ptr<PhysicalOperator> &child = children_[0];

    RC rc = child->open(trx);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;
    }

    have_value = false;
    value_list_.clear();
    ids_.clear();
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next()
{
    RC                rc    = RC::SUCCESS;
    if(!have_value){
        if(limit_ < 0)rc = adaptive_sort();
        else rc = limit_sort();

        if(OB_FAIL(rc))return rc;

        current_id_ = 0;
        first_emited_  = false;
        have_value = true;
    }

    return fetch_next();
}

RC OrderByPhysicalOperator::close()
{
    LOG_INFO("close order by operator");
    
    if (is_external_sort_) {
        // 关闭文件流
        if (current_file_stream_.is_open()) {
            current_file_stream_.close();
        }
        
        for (auto& file : file_streams_) {
            if (file.is_open()) {
                file.close();
            }
        }
        
        // 清理临时文件
        cleanup_temp_files();
        
        // 重置状态
        is_external_sort_ = false;
        sorted_files_.clear();
        current_chunk_.clear();
        file_streams_.clear();
        file_chunks_.clear();
        chunk_indices_.clear();
    } else {
        // 清理临时文件
        cleanup_temp_files();
    }
    
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next(Tuple *upper_tuple) 
{
    RC                rc    = RC::SUCCESS;
    if(!have_value){
        if(limit_ < 0)rc = adaptive_sort(upper_tuple);
        else rc = limit_sort(upper_tuple);

        if(OB_FAIL(rc))return rc;

        current_id_ = 0;
        first_emited_  = false;
        have_value = true;
    }

    return fetch_next();
}

Tuple *OrderByPhysicalOperator::current_tuple()
{
  if (is_external_sort_) {
    if (current_chunk_index_ < current_chunk_.size()) {
      return &current_chunk_[current_chunk_index_];
    }
    return nullptr;
  } else {
    if (current_id_ != value_list_.size()) {
      return &value_list_[ids_[current_id_]];
    }
    return nullptr;
  }
}

RC OrderByPhysicalOperator::fetch_next()
{
  if (is_external_sort_) {
    return fetch_next_external();
  } else {
    // 内存排序的数据获取
    if (current_id_ == value_list_.size()) {
      return RC::RECORD_EOF;
    }

    if (first_emited_) {
      ++current_id_;
    } else {
      first_emited_ = true;
    }
    if (current_id_ == value_list_.size()) {
      return RC::RECORD_EOF;
    }

    return RC::SUCCESS;
  }
}

RC OrderByPhysicalOperator::fetch_next_external()
{
  // 如果当前块还有数据，直接返回
  if (current_chunk_index_ < current_chunk_.size()) {
    if (first_emited_) {
      ++current_chunk_index_;
    } else {
      first_emited_ = true;
    }
    
    if (current_chunk_index_ < current_chunk_.size()) {
      return RC::SUCCESS;
    }
  }
  
  // 当前块数据用完，需要读取下一个块
  if (sorted_files_.size() == 1) {
    // 单文件情况：读取下一个块
    return load_next_chunk_single_file();
  } else {
    // 多文件情况：多路归并
    return load_next_chunk_merge();
  }
}

RC OrderByPhysicalOperator::load_next_chunk_single_file()
{
  // 从单个文件中读取下一个块
  if (current_file_stream_.eof()) {
    return RC::RECORD_EOF;
  }
  
  RC rc = read_chunk_from_stream(current_chunk_, current_file_stream_);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  
  current_chunk_index_ = 0;
  first_emited_ = false;
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::load_next_chunk_merge()
{
  // 多路归并：找到当前最小的元素
  int min_file_index = -1;
  std::vector<Value> min_values;
  
  for (size_t i = 0; i < file_chunks_.size(); i++) {
    if (chunk_indices_[i] < file_chunks_[i].size()) {
      std::vector<Value> values(order_by_.size());
      for (size_t j = 0; j < order_by_.size(); j++) {
        order_by_[j]->get_value(file_chunks_[i][chunk_indices_[i]], values[j]);
      }
      
      if (min_file_index == -1 || cmp(values, min_values)) {
        min_file_index = i;
        min_values = values;
      }
    }
  }
  
  if (min_file_index == -1) {
    return RC::RECORD_EOF; // 所有文件都处理完毕
  }
  
  // 将最小的元素放入当前块
  current_chunk_.clear();
  current_chunk_.emplace_back(std::move(file_chunks_[min_file_index][chunk_indices_[min_file_index]]));
  chunk_indices_[min_file_index]++;
  
  // 如果当前文件的数据用完，尝试读取下一块
  if (chunk_indices_[min_file_index] >= file_chunks_[min_file_index].size()) {
    RC rc = load_file_chunk(min_file_index);
    if (rc != RC::SUCCESS && rc != RC::RECORD_EOF) {
      return rc;
    }
  }
  
  current_chunk_index_ = 0;
  first_emited_ = false;
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::load_file_chunk(size_t file_index)
{
  // 从指定文件中读取下一个块
  if (file_index >= file_streams_.size()) {
    return RC::INVALID_ARGUMENT;
  }
  
  std::ifstream& file = file_streams_[file_index];
  if (file.eof()) {
    return RC::RECORD_EOF;
  }
  
  RC rc = read_chunk_from_stream(file_chunks_[file_index], file);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  
  chunk_indices_[file_index] = 0;
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::quick_sort(Tuple *upper_tuple)
{
    RC rc = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    Tuple* tuple = nullptr;
    while (OB_SUCC(rc = (upper_tuple == nullptr ? child->next() : child->next(upper_tuple)))) {
        tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            child->close();
            return rc;
        }
        ValueListTuple value_list;
        rc =  ValueListTuple::make(*tuple, value_list);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to make ValueListTuple: %s", strrc(rc));
            child->close();
            return rc;
        }
        value_list_.emplace_back(std::move(value_list));
    }
    child->close();

    if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
        LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
        return rc;
    }

    ids_.resize(value_list_.size());
    order_values_.resize(value_list_.size());
    for(size_t id = 0; id < value_list_.size(); id++){
        auto& values = order_values_[id];
        values.resize(order_by_.size());
        for(size_t i = 0; i < order_by_.size(); i++){
            order_by_[i]->get_value(value_list_[id], values[i]);
        }
        ids_[id] = id;
    }

    sort(ids_.begin(), ids_.end(), [&](size_t &a, size_t &b){
        return cmp(order_values_[a], order_values_[b]);
    });

    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::quick_sort_with_cached_data(Tuple *upper_tuple, size_t cached_count)
{
    RC rc = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    
    // 继续读取剩余的数据
    Tuple* tuple = nullptr;
    while (OB_SUCC(rc = (upper_tuple == nullptr ? child->next() : child->next(upper_tuple)))) {
        tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            child->close();
            return rc;
        }
        ValueListTuple value_list;
        rc = ValueListTuple::make(*tuple, value_list);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to make ValueListTuple: %s", strrc(rc));
            child->close();
            return rc;
        }
        value_list_.emplace_back(std::move(value_list));
    }
    child->close();

    if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
        LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
        return rc;
    }

    // 对所有数据进行排序（包括已缓存的数据）
    ids_.resize(value_list_.size());
    order_values_.resize(value_list_.size());
    for(size_t id = 0; id < value_list_.size(); id++){
        auto& values = order_values_[id];
        values.resize(order_by_.size());
        for(size_t i = 0; i < order_by_.size(); i++){
            order_by_[i]->get_value(value_list_[id], values[i]);
        }
        ids_[id] = id;
    }

    sort(ids_.begin(), ids_.end(), [&](size_t &a, size_t &b){
        return cmp(order_values_[a], order_values_[b]);
    });

    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::limit_sort(Tuple *upper_tuple)
{
    RC rc = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    Tuple* tuple = nullptr;
    order_values_.reserve(limit_);
    value_list_.reserve(limit_);

    auto cmp_ = [&](size_t &a, size_t &b){
        return cmp(order_values_[a], order_values_[b]);
    };
    priority_queue<size_t, vector<size_t>, decltype(cmp_)> pq(cmp_);
    
    while (OB_SUCC(rc = (upper_tuple == nullptr ? child->next() : child->next(upper_tuple)))) {
        tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            child->close();
            return rc;
        }
        ValueListTuple value_list;
        rc =  ValueListTuple::make(*tuple, value_list);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to make ValueListTuple: %s", strrc(rc));
            child->close();
            return rc;
        }
        if(pq.size() < (size_t)limit_)
        {
            vector<Value> values(order_by_.size());
            for(size_t i = 0; i < order_by_.size(); i++){
                order_by_[i]->get_value(value_list, values[i]);
            }
            value_list_.emplace_back(std::move(value_list));
            order_values_.emplace_back(std::move(values));
            pq.emplace(value_list_.size() - 1);
        } else {
            vector<Value> values(order_by_.size());
            for(size_t i = 0; i < order_by_.size(); i++){
                order_by_[i]->get_value(value_list, values[i]);
            }
            if(cmp(values, order_values_[pq.top()])){
                size_t id = pq.top();
                pq.pop();
                order_values_[id].swap(values);
                pq.emplace(id);
                value_list_[id] = std::move(value_list);
            }
        }
            
    }
    child->close();

    if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
        LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
        return rc;
    }

    ids_.reserve(limit_);
    while(!pq.empty()){
        ids_.emplace_back(pq.top());
        pq.pop();
    }
    reverse(ids_.begin(), ids_.end());

    return RC::SUCCESS;
}

bool OrderByPhysicalOperator::cmp(const vector<Value>& a_vals, const vector<Value>& b_vals)
{
    for(size_t id = 0; id < order_by_.size(); id++){
        bool is_asc = is_asc_[id];
        auto& a_val = a_vals[id];
        auto& b_val = b_vals[id];

        if(a_val.attr_type() == AttrType::NULLS)
        {
            if(b_val.attr_type() == AttrType::NULLS)continue;
            return is_asc;
        }
        else if(b_val.attr_type() == AttrType::NULLS)return !is_asc;

        int cmp = a_val.compare(b_val);
        if(cmp == 0)continue;
        else if(is_asc)return cmp < 0;
        return cmp > 0;
    }
    return false;
}

RC OrderByPhysicalOperator::adaptive_sort(Tuple *upper_tuple)
{
    RC rc = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    
    // 先读取所有数据到内存中
    Tuple* tuple = nullptr;
    size_t tuple_count = 0;
    size_t current_memory_usage = 0;
    
    while (OB_SUCC(rc = (upper_tuple == nullptr ? child->next() : child->next(upper_tuple)))) {
        tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            child->close();
            return rc;
        }
        
        ValueListTuple value_list;
        rc = ValueListTuple::make(*tuple, value_list);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to make ValueListTuple: %s", strrc(rc));
            child->close();
            return rc;
        }
        
        // 更新内存使用量
        current_memory_usage += value_list.get_tuple_size();
        
        value_list_.emplace_back(std::move(value_list));
        tuple_count++;
        
        // 检查内存使用量，如果超过阈值则切换到外排序
        if (current_memory_usage > memory_threshold_) {
            LOG_INFO("Memory usage estimated to exceed threshold (%zu bytes), switching to external sort", memory_threshold_);
            // 不关闭子算子，让external_sort处理
            return external_sort_with_cached_data(upper_tuple, tuple_count);
        }
    }
    child->close();

    if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
        LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
        return rc;
    }

    // 如果数据量在内存范围内，使用快速排序
    LOG_INFO("Using in-memory sort for %zu tuples", tuple_count);
    return sort_in_memory();
}

RC OrderByPhysicalOperator::sort_in_memory()
{
    // 对所有数据进行排序（包括已缓存的数据）
    ids_.resize(value_list_.size());
    order_values_.resize(value_list_.size());
    for(size_t id = 0; id < value_list_.size(); id++){
        auto& values = order_values_[id];
        values.resize(order_by_.size());
        for(size_t i = 0; i < order_by_.size(); i++){
            order_by_[i]->get_value(value_list_[id], values[i]);
        }
        ids_[id] = id;
    }

    sort(ids_.begin(), ids_.end(), [&](size_t &a, size_t &b){
        return cmp(order_values_[a], order_values_[b]);
    });

    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::external_sort_with_cached_data(Tuple *upper_tuple, size_t cached_count)
{
    RC rc = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    
    // 第一阶段：处理已缓存的数据
    if (cached_count > 0) {
        // 将已缓存的数据分成块并排序
        size_t remaining_in_first_chunk = chunk_size_ - (cached_count % chunk_size_);
        if (remaining_in_first_chunk == chunk_size_) {
            remaining_in_first_chunk = 0;
        }
        
        // 处理第一个不完整的块
        if (remaining_in_first_chunk > 0) {
            std::vector<ValueListTuple> first_chunk;
            first_chunk.reserve(remaining_in_first_chunk);
            
            // 继续读取数据直到第一个块满
            Tuple* tuple = nullptr;
            for (size_t i = 0; i < remaining_in_first_chunk; i++) {
                rc = (upper_tuple == nullptr ? child->next() : child->next(upper_tuple));
                if (rc != RC::SUCCESS) {
                    if (rc == RC::RECORD_EOF) {
                        break;
                    }
                    LOG_WARN("failed to get next tuple: %s", strrc(rc));
                    child->close();
                    return rc;
                }
                
                tuple = child->current_tuple();
                if (nullptr == tuple) {
                    LOG_WARN("failed to get current record: %s", strrc(rc));
                    child->close();
                    return rc;
                }
                
                ValueListTuple value_list;
                rc = ValueListTuple::make(*tuple, value_list);
                if (rc != RC::SUCCESS) {
                    LOG_WARN("failed to make ValueListTuple: %s", strrc(rc));
                    child->close();
                    return rc;
                }
                
                first_chunk.emplace_back(std::move(value_list));
            }
            
            // 将已缓存的数据和刚读取的数据合并
            std::vector<ValueListTuple> combined_chunk;
            combined_chunk.reserve(cached_count + first_chunk.size());
            
            // 添加已缓存的数据
            for (size_t i = 0; i < cached_count; i++) {
                combined_chunk.emplace_back(std::move(value_list_[i]));
            }
            
            // 添加新读取的数据
            for (auto& item : first_chunk) {
                combined_chunk.emplace_back(std::move(item));
            }
            
            // 排序并写入临时文件
            std::string temp_file = create_temp_file();
            if (temp_file.empty()) {
                LOG_ERROR("Failed to create temporary file");
                child->close();
                return RC::IOERR_WRITE;
            }
            
            // 对合并的块进行排序
            std::vector<size_t> chunk_ids(combined_chunk.size());
            std::vector<std::vector<Value>> chunk_order_values(combined_chunk.size());
            
            for (size_t i = 0; i < combined_chunk.size(); i++) {
                chunk_ids[i] = i;
                chunk_order_values[i].resize(order_by_.size());
                for (size_t j = 0; j < order_by_.size(); j++) {
                    order_by_[j]->get_value(combined_chunk[i], chunk_order_values[i][j]);
                }
            }
            
            std::sort(chunk_ids.begin(), chunk_ids.end(), [&](size_t a, size_t b) {
                return cmp(chunk_order_values[a], chunk_order_values[b]);
            });
            
            // 按排序后的顺序重新排列chunk
            std::vector<ValueListTuple> sorted_chunk;
            sorted_chunk.reserve(combined_chunk.size());
            for (size_t id : chunk_ids) {
                sorted_chunk.emplace_back(std::move(combined_chunk[id]));
            }
            
            // 写入临时文件
            rc = write_chunk_to_file(sorted_chunk, temp_file);
            if (rc != RC::SUCCESS) {
                LOG_ERROR("Failed to write chunk to file: %s", strrc(rc));
                child->close();
                return rc;
            }
            
            temp_files_.push_back(temp_file);
        } else {
            // 已缓存的数据正好是一个完整的块
            std::string temp_file = create_temp_file();
            if (temp_file.empty()) {
                LOG_ERROR("Failed to create temporary file");
                child->close();
                return RC::IOERR_WRITE;
            }
            
            // 对已缓存的数据进行排序
            std::vector<size_t> chunk_ids(cached_count);
            std::vector<std::vector<Value>> chunk_order_values(cached_count);
            
            for (size_t i = 0; i < cached_count; i++) {
                chunk_ids[i] = i;
                chunk_order_values[i].resize(order_by_.size());
                for (size_t j = 0; j < order_by_.size(); j++) {
                    order_by_[j]->get_value(value_list_[i], chunk_order_values[i][j]);
                }
            }
            
            std::sort(chunk_ids.begin(), chunk_ids.end(), [&](size_t a, size_t b) {
                return cmp(chunk_order_values[a], chunk_order_values[b]);
            });
            
            // 按排序后的顺序重新排列chunk
            std::vector<ValueListTuple> sorted_chunk;
            sorted_chunk.reserve(cached_count);
            for (size_t id : chunk_ids) {
                sorted_chunk.emplace_back(std::move(value_list_[id]));
            }
            
            // 写入临时文件
            rc = write_chunk_to_file(sorted_chunk, temp_file);
            if (rc != RC::SUCCESS) {
                LOG_ERROR("Failed to write chunk to file: %s", strrc(rc));
                child->close();
                return rc;
            }
            
            temp_files_.push_back(temp_file);
        }
        
        // 清空已缓存的数据
        value_list_.clear();
    }
    
    // 第二阶段：继续读取剩余数据并分块处理
    std::vector<ValueListTuple> chunk;
    chunk.reserve(chunk_size_);
    
    Tuple* tuple = nullptr;
    while (OB_SUCC(rc = (upper_tuple == nullptr ? child->next() : child->next(upper_tuple)))) {
        tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            child->close();
            return rc;
        }
        
        ValueListTuple value_list;
        rc = ValueListTuple::make(*tuple, value_list);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to make ValueListTuple: %s", strrc(rc));
            child->close();
            return rc;
        }
        
        chunk.emplace_back(std::move(value_list));
        
        // 当块满了时，排序并写入临时文件
        if (chunk.size() >= chunk_size_) {
            std::string temp_file = create_temp_file();
            if (temp_file.empty()) {
                LOG_ERROR("Failed to create temporary file");
                child->close();
                return RC::IOERR_WRITE;
            }
            
            // 对当前块进行排序
            std::vector<size_t> chunk_ids(chunk.size());
            std::vector<std::vector<Value>> chunk_order_values(chunk.size());
            
            for (size_t i = 0; i < chunk.size(); i++) {
                chunk_ids[i] = i;
                chunk_order_values[i].resize(order_by_.size());
                for (size_t j = 0; j < order_by_.size(); j++) {
                    order_by_[j]->get_value(chunk[i], chunk_order_values[i][j]);
                }
            }
            
            std::sort(chunk_ids.begin(), chunk_ids.end(), [&](size_t a, size_t b) {
                return cmp(chunk_order_values[a], chunk_order_values[b]);
            });
            
            // 按排序后的顺序重新排列chunk
            std::vector<ValueListTuple> sorted_chunk;
            sorted_chunk.reserve(chunk.size());
            for (size_t id : chunk_ids) {
                sorted_chunk.emplace_back(std::move(chunk[id]));
            }
            
            // 写入临时文件
            rc = write_chunk_to_file(sorted_chunk, temp_file);
            if (rc != RC::SUCCESS) {
                LOG_ERROR("Failed to write chunk to file: %s", strrc(rc));
                child->close();
                return rc;
            }
            
            temp_files_.push_back(temp_file);
            chunk.clear();
        }
    }
    child->close();

    if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
        LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
        return rc;
    }
    
    // 处理最后一个不完整的块
    if (!chunk.empty()) {
        std::string temp_file = create_temp_file();
        if (temp_file.empty()) {
            LOG_ERROR("Failed to create temporary file for last chunk");
            return RC::IOERR_WRITE;
        }
        
        // 对最后一个块进行排序
        std::vector<size_t> chunk_ids(chunk.size());
        std::vector<std::vector<Value>> chunk_order_values(chunk.size());
        
        for (size_t i = 0; i < chunk.size(); i++) {
            chunk_ids[i] = i;
            chunk_order_values[i].resize(order_by_.size());
            for (size_t j = 0; j < order_by_.size(); j++) {
                order_by_[j]->get_value(chunk[i], chunk_order_values[i][j]);
            }
        }
        
        std::sort(chunk_ids.begin(), chunk_ids.end(), [&](size_t a, size_t b) {
            return cmp(chunk_order_values[a], chunk_order_values[b]);
        });
        
        // 按排序后的顺序重新排列chunk
        std::vector<ValueListTuple> sorted_chunk;
        sorted_chunk.reserve(chunk.size());
        for (size_t id : chunk_ids) {
            sorted_chunk.emplace_back(std::move(chunk[id]));
        }
        
        // 写入临时文件
        rc = write_chunk_to_file(sorted_chunk, temp_file);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to write last chunk to file: %s", strrc(rc));
            return rc;
        }
        
        temp_files_.push_back(temp_file);
    }
    
    // 第三阶段：设置流式处理
    is_external_sort_ = true;
    sorted_files_ = temp_files_;
    
    if (temp_files_.size() == 1) {
        // 单文件情况：打开文件流
        current_temp_file_ = temp_files_[0];
        current_file_stream_.open(current_temp_file_, std::ios::binary);
        if (!current_file_stream_.is_open()) {
            LOG_ERROR("Failed to open temporary file: %s", current_temp_file_.c_str());
            return RC::IOERR_READ;
        }
        
        // 读取第一个块
        current_chunk_.clear();
        current_chunk_index_ = 0;
        first_emited_ = false;
        
    } else {
        // 多文件情况：设置多路归并
        file_streams_.clear();
        file_chunks_.clear();
        chunk_indices_.clear();
        
        for (const auto& filename : temp_files_) {
            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) {
                LOG_ERROR("Failed to open input file: %s", filename.c_str());
                return RC::IOERR_READ;
            }
            file_streams_.push_back(std::move(file));
            
            // 读取每个文件的第一块数据
            std::vector<ValueListTuple> chunk;
            RC rc = read_chunk_from_file(chunk, filename);
            if (rc != RC::SUCCESS) {
                LOG_ERROR("Failed to read chunk from file: %s", strrc(rc));
                return rc;
            }
            file_chunks_.push_back(std::move(chunk));
            chunk_indices_.push_back(0);
        }
        
        // 初始化当前块
        current_chunk_.clear();
        current_chunk_index_ = 0;
        first_emited_ = false;
    }
    
    LOG_INFO("External sort with cached data initialized for %zu temporary files", temp_files_.size());
    
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::external_sort(Tuple *upper_tuple)
{
    RC rc = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    
    // 清空之前的数据
    value_list_.clear();
    order_values_.clear();
    ids_.clear();
    
    // 第一阶段：分块读取并排序
    std::vector<ValueListTuple> chunk;
    chunk.reserve(chunk_size_);
    
    Tuple* tuple = nullptr;
    while (OB_SUCC(rc = (upper_tuple == nullptr ? child->next() : child->next(upper_tuple)))) {
        tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            child->close();
            return rc;
        }
        
        ValueListTuple value_list;
        rc = ValueListTuple::make(*tuple, value_list);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to make ValueListTuple: %s", strrc(rc));
            child->close();
            return rc;
        }
        
        chunk.emplace_back(std::move(value_list));
        
        // 当块满了时，排序并写入临时文件
        if (chunk.size() >= chunk_size_) {
            std::string temp_file = create_temp_file();
            if (temp_file.empty()) {
                LOG_ERROR("Failed to create temporary file");
                child->close();
                return RC::IOERR_WRITE;
            }
            
            // 对当前块进行排序
            std::vector<size_t> chunk_ids(chunk.size());
            std::vector<std::vector<Value>> chunk_order_values(chunk.size());
            
            for (size_t i = 0; i < chunk.size(); i++) {
                chunk_ids[i] = i;
                chunk_order_values[i].resize(order_by_.size());
                for (size_t j = 0; j < order_by_.size(); j++) {
                    order_by_[j]->get_value(chunk[i], chunk_order_values[i][j]);
                }
            }
            
            std::sort(chunk_ids.begin(), chunk_ids.end(), [&](size_t a, size_t b) {
                return cmp(chunk_order_values[a], chunk_order_values[b]);
            });
            
            // 按排序后的顺序重新排列chunk
            std::vector<ValueListTuple> sorted_chunk;
            sorted_chunk.reserve(chunk.size());
            for (size_t id : chunk_ids) {
                sorted_chunk.emplace_back(std::move(chunk[id]));
            }
            
            // 写入临时文件
            rc = write_chunk_to_file(sorted_chunk, temp_file);
            if (rc != RC::SUCCESS) {
                LOG_ERROR("Failed to write chunk to file: %s", strrc(rc));
                child->close();
                return rc;
            }
            
            temp_files_.push_back(temp_file);
            chunk.clear();
        }
    }
    child->close();

    if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
    }

    if (OB_FAIL(rc)) {
        LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
        return rc;
    }
    
    // 处理最后一个不完整的块
    if (!chunk.empty()) {
        std::string temp_file = create_temp_file();
        if (temp_file.empty()) {
            LOG_ERROR("Failed to create temporary file for last chunk");
            return RC::IOERR_WRITE;
        }
        
        // 对最后一个块进行排序
        std::vector<size_t> chunk_ids(chunk.size());
        std::vector<std::vector<Value>> chunk_order_values(chunk.size());
        
        for (size_t i = 0; i < chunk.size(); i++) {
            chunk_ids[i] = i;
            chunk_order_values[i].resize(order_by_.size());
            for (size_t j = 0; j < order_by_.size(); j++) {
                order_by_[j]->get_value(chunk[i], chunk_order_values[i][j]);
            }
        }
        
        std::sort(chunk_ids.begin(), chunk_ids.end(), [&](size_t a, size_t b) {
            return cmp(chunk_order_values[a], chunk_order_values[b]);
        });
        
        // 按排序后的顺序重新排列chunk
        std::vector<ValueListTuple> sorted_chunk;
        sorted_chunk.reserve(chunk.size());
        for (size_t id : chunk_ids) {
            sorted_chunk.emplace_back(std::move(chunk[id]));
        }
        
        // 写入临时文件
        rc = write_chunk_to_file(sorted_chunk, temp_file);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to write last chunk to file: %s", strrc(rc));
            return rc;
        }
        
        temp_files_.push_back(temp_file);
    }
    
    // 第二阶段：多路归并
    if (temp_files_.size() == 1) {
        // 只有一个文件，直接读取
        current_temp_file_ = temp_files_[0];
        current_file_stream_.open(current_temp_file_, std::ios::binary);
        if (!current_file_stream_.is_open()) {
            LOG_ERROR("Failed to open temporary file: %s", current_temp_file_.c_str());
            return RC::IOERR_READ;
        }
        
        // 读取所有数据到内存
        rc = read_chunk_from_file(value_list_, current_temp_file_);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to read from temporary file: %s", strrc(rc));
            return rc;
        }
        
        // 设置索引
        ids_.resize(value_list_.size());
        for (size_t i = 0; i < value_list_.size(); i++) {
            ids_[i] = i;
        }
        
        current_file_stream_.close();
        unlink(current_temp_file_.c_str());
        temp_files_.clear();
        
    } else {
        // 多个文件，需要归并
        std::string final_file = create_temp_file();
        if (final_file.empty()) {
            LOG_ERROR("Failed to create final temporary file");
            return RC::IOERR_WRITE;
        }
        
        rc = merge_sorted_files(temp_files_, final_file);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to merge sorted files: %s", strrc(rc));
            return rc;
        }
        
        // 读取最终结果
        rc = read_chunk_from_file(value_list_, final_file);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to read from final file: %s", strrc(rc));
            return rc;
        }
        
        // 设置索引
        ids_.resize(value_list_.size());
        for (size_t i = 0; i < value_list_.size(); i++) {
            ids_[i] = i;
        }
        
        // 清理临时文件
        cleanup_temp_files();
        unlink(final_file.c_str());
    }
    
    LOG_INFO("External sort completed for %zu tuples using %zu temporary files", 
             value_list_.size(), temp_files_.size());
    
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::write_chunk_to_file(const std::vector<ValueListTuple>& chunk, const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        LOG_ERROR("Failed to open file for writing: %s", filename.c_str());
        return RC::IOERR_WRITE;
    }
    
    // 写入块大小
    size_t chunk_size = chunk.size();
    file.write(reinterpret_cast<const char*>(&chunk_size), sizeof(chunk_size));
    
    // 写入每个tuple
    for (const auto& tuple : chunk) {
        int cell_num = tuple.cell_num();
        file.write(reinterpret_cast<const char*>(&cell_num), sizeof(cell_num));
        
        for (int i = 0; i < cell_num; i++) {
            Value cell;
            RC rc = tuple.cell_at(i, cell);
            if (rc != RC::SUCCESS) {
                LOG_ERROR("Failed to get cell at index %d", i);
                return rc;
            }
            
            // 序列化Value
            AttrType type = cell.attr_type();
            file.write(reinterpret_cast<const char*>(&type), sizeof(type));
            
            switch (type) {
                case AttrType::INTS: {
                    int val = cell.get_int();
                    file.write(reinterpret_cast<const char*>(&val), sizeof(val));
                    break;
                }
                case AttrType::FLOATS: {
                    float val = cell.get_float();
                    file.write(reinterpret_cast<const char*>(&val), sizeof(val));
                    break;
                }
                case AttrType::CHARS: {
                    string str = cell.get_string();
                    int len = str.length();
                    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    file.write(str.c_str(), len);
                    break;
                }
                case AttrType::NULLS:
                    // NULL值不需要额外数据
                    break;
                default:
                    LOG_ERROR("Unsupported attribute type: %d", static_cast<int>(type));
                    return RC::INVALID_ARGUMENT;
            }
        }
    }
    
    file.close();
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::read_chunk_from_file(std::vector<ValueListTuple>& chunk, const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        LOG_ERROR("Failed to open file for reading: %s", filename.c_str());
        return RC::IOERR_READ;
    }
    
    return read_chunk_from_stream(chunk, file);
}

RC OrderByPhysicalOperator::read_chunk_from_stream(std::vector<ValueListTuple>& chunk, std::ifstream& file)
{
    chunk.clear();
    
    // 检查文件是否到达末尾
    if (file.eof()) {
        return RC::RECORD_EOF;
    }
    
    // 读取块大小
    size_t chunk_size;
    file.read(reinterpret_cast<char*>(&chunk_size), sizeof(chunk_size));
    
    if (file.eof()) {
        return RC::RECORD_EOF;
    }
    
    // 读取每个tuple
    for (size_t i = 0; i < chunk_size; i++) {
        int cell_num;
        file.read(reinterpret_cast<char*>(&cell_num), sizeof(cell_num));
        
        if (file.eof()) {
            break;
        }
        
        ValueListTuple tuple;
        std::vector<Value> cells;
        std::vector<TupleCellSpec> specs;
        
        for (int j = 0; j < cell_num; j++) {
            AttrType type;
            file.read(reinterpret_cast<char*>(&type), sizeof(type));
            
            if (file.eof()) {
                break;
            }
            
            Value cell;
            switch (type) {
                case AttrType::INTS: {
                    int val;
                    file.read(reinterpret_cast<char*>(&val), sizeof(val));
                    cell = Value(val);
                    break;
                }
                case AttrType::FLOATS: {
                    float val;
                    file.read(reinterpret_cast<char*>(&val), sizeof(val));
                    cell = Value(val);
                    break;
                }
                case AttrType::CHARS: {
                    int len;
                    file.read(reinterpret_cast<char*>(&len), sizeof(len));
                    std::string str(len, '\0');
                    file.read(&str[0], len);
                    cell = Value(str.c_str());
                    break;
                }
                case AttrType::NULLS:
                    cell.set_null();
                    break;
                default:
                    LOG_ERROR("Unsupported attribute type: %d", static_cast<int>(type));
                    return RC::INVALID_ARGUMENT;
            }
            
            cells.push_back(cell);
            specs.emplace_back("col_" + std::to_string(j)); // 临时列名
        }
        
        tuple.set_cells(cells);
        tuple.set_names(specs);
        chunk.emplace_back(std::move(tuple));
    }
    
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::merge_sorted_files(const std::vector<std::string>& input_files, const std::string& output_file)
{
    if (input_files.empty()) {
        return RC::SUCCESS;
    }
    
    if (input_files.size() == 1) {
        // 只有一个文件，直接复制
        std::ifstream src(input_files[0], std::ios::binary);
        std::ofstream dst(output_file, std::ios::binary);
        
        if (!src.is_open() || !dst.is_open()) {
            LOG_ERROR("Failed to open files for copying");
            return RC::IOERR_READ;
        }
        
        dst << src.rdbuf();
        src.close();
        dst.close();
        return RC::SUCCESS;
    }
    
    // 多路归并
    std::vector<std::ifstream> file_streams;
    std::vector<std::vector<ValueListTuple>> file_chunks;
    std::vector<size_t> chunk_indices;
    
    // 打开所有输入文件
    for (const auto& filename : input_files) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            LOG_ERROR("Failed to open input file: %s", filename.c_str());
            return RC::IOERR_READ;
        }
        file_streams.push_back(std::move(file));
        
        // 读取每个文件的第一块数据
        std::vector<ValueListTuple> chunk;
        RC rc = read_chunk_from_file(chunk, filename);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to read chunk from file: %s", strrc(rc));
            return rc;
        }
        file_chunks.push_back(std::move(chunk));
        chunk_indices.push_back(0);
    }
    
    std::ofstream output(output_file, std::ios::binary);
    if (!output.is_open()) {
        LOG_ERROR("Failed to open output file: %s", output_file.c_str());
        return RC::IOERR_WRITE;
    }
    
    // 执行多路归并
    while (true) {
        // 找到当前最小的元素
        int min_file_index = -1;
        std::vector<Value> min_values;
        
        for (size_t i = 0; i < file_chunks.size(); i++) {
            if (chunk_indices[i] < file_chunks[i].size()) {
                std::vector<Value> values(order_by_.size());
                for (size_t j = 0; j < order_by_.size(); j++) {
                    order_by_[j]->get_value(file_chunks[i][chunk_indices[i]], values[j]);
                }
                
                if (min_file_index == -1 || cmp(values, min_values)) {
                    min_file_index = i;
                    min_values = values;
                }
            }
        }
        
        if (min_file_index == -1) {
            break; // 所有文件都处理完毕
        }
        
        // 写入最小的元素
        const auto& min_tuple = file_chunks[min_file_index][chunk_indices[min_file_index]];
        
        // 序列化并写入输出文件
        int cell_num = min_tuple.cell_num();
        output.write(reinterpret_cast<const char*>(&cell_num), sizeof(cell_num));
        
        for (int i = 0; i < cell_num; i++) {
            Value cell;
            RC rc = min_tuple.cell_at(i, cell);
            if (rc != RC::SUCCESS) {
                LOG_ERROR("Failed to get cell at index %d", i);
                return rc;
            }
            
            AttrType type = cell.attr_type();
            output.write(reinterpret_cast<const char*>(&type), sizeof(type));
            
            switch (type) {
                case AttrType::INTS: {
                    int val = cell.get_int();
                    output.write(reinterpret_cast<const char*>(&val), sizeof(val));
                    break;
                }
                case AttrType::FLOATS: {
                    float val = cell.get_float();
                    output.write(reinterpret_cast<const char*>(&val), sizeof(val));
                    break;
                }
                case AttrType::CHARS: {
                    string str = cell.get_string();
                    int len = str.length();
                    output.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    output.write(str.c_str(), len);
                    break;
                }
                case AttrType::NULLS:
                    break;
                default:
                    LOG_ERROR("Unsupported attribute type: %d", static_cast<int>(type));
                    return RC::INVALID_ARGUMENT;
            }
        }
        
        chunk_indices[min_file_index]++;
    }
    
    output.close();
    
    // 关闭所有文件流
    for (auto& file : file_streams) {
        file.close();
    }
    
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::cleanup_temp_files()
{
    for (const auto& filename : temp_files_) {
        unlink(filename.c_str());
    }
    temp_files_.clear();
    return RC::SUCCESS;
}

    std::string OrderByPhysicalOperator::create_temp_file()
    {
        char temp_filename[256];
        snprintf(temp_filename, sizeof(temp_filename), "/tmp/miniob_orderby_%d_%d", getpid(), rand());
        return temp_filename;
    }