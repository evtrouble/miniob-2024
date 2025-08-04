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
        for (auto& file : file_streams_) {
            if (file.is_open()) {
                file.close();
            }
        }
        
        // 清理临时文件
        cleanup_temp_files();
        
        // 重置状态
        is_external_sort_ = false;
        temp_files_.clear();
        file_streams_.clear();
        current_tuples_.clear();
        run_exhausted_.clear();
        merge_pq_.reset();
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
    return &current_external_tuple_;
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
  if (merge_pq_ == nullptr || merge_pq_->empty()) {
    return RC::RECORD_EOF;
  }

  // Get the next element with the minimum key
  MergeElement min_element = merge_pq_->top();
  merge_pq_->pop();

  size_t run_index = min_element.run_index;

  // Set the current tuple to the one we just found
  current_external_tuple_ = current_tuples_[run_index];

  // Load the next tuple from this run
  RC rc = load_next_tuple_from_run(run_index);
  if (rc == RC::SUCCESS) {
    // If successfully loaded next tuple, push it to the priority queue
    std::vector<Value> next_keys;
    const auto& next_tuple = current_tuples_[run_index];
    for (const auto& expr : order_by_) {
      Value val;
      expr->get_value(next_tuple, val);
      next_keys.push_back(val);
    }
    merge_pq_->push({next_keys, run_index});
  } else if (rc != RC::RECORD_EOF) {
    return rc; // Propagate errors
  }
  // If rc == RC::RECORD_EOF, this run is exhausted, so we don't push anything to PQ

  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::load_next_tuple_from_run(size_t run_index)
{
  // 从指定run中读取下一个tuple
  if (run_index >= file_streams_.size()) {
    return RC::INVALID_ARGUMENT;
  }
  
  if (run_exhausted_[run_index]) {
    return RC::RECORD_EOF;
  }
  
  std::ifstream& file = file_streams_[run_index];
  if (file.eof()) {
    run_exhausted_[run_index] = true;
    return RC::RECORD_EOF;
  }
  
  // 读取单个tuple
  ValueListTuple tuple;
  RC rc = read_single_tuple_from_stream(tuple, file);
  if (rc != RC::SUCCESS) {
    if (rc == RC::RECORD_EOF) {
      run_exhausted_[run_index] = true;
    }
    return rc;
  }
  
  // 直接设置当前tuple，不缓存
  current_tuples_[run_index] = std::move(tuple);
  
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

bool OrderByPhysicalOperator::cmp(const vector<Value>& a_vals, const vector<Value>& b_vals) const
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
            chunk_size_ = tuple_count;
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
        std::string temp_file;
        rc = sort_and_write_chunk(value_list_, temp_file);
        if (rc != RC::SUCCESS) {
            child->close();
            return rc;
        }
        
        temp_files_.emplace_back(std::move(temp_file));
        value_list_.clear();
    }
    
    // 第二阶段：继续读取剩余数据并分块处理
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
        
        // 当块满了时，排序并写入临时文件
        if (value_list_.size() >= chunk_size_) {
            std::string temp_file;
            rc = sort_and_write_chunk(value_list_, temp_file);
            if (rc != RC::SUCCESS) {
                child->close();
                return rc;
            }
            
            temp_files_.emplace_back(std::move(temp_file));
            value_list_.clear();
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
    if (!value_list_.empty()) {
        std::string temp_file;
        rc = sort_and_write_chunk(value_list_, temp_file);
        if (rc != RC::SUCCESS) {
            return rc;
        }
        
        temp_files_.emplace_back(std::move(temp_file));
        value_list_.clear();
    }
    
    // 第三阶段：初始化多路归并
    is_external_sort_ = true;
    
    // Open file streams for all temporary files
    for (const auto& filename : temp_files_) {
        file_streams_.emplace_back(filename, std::ios::binary);
        if (!file_streams_.back().is_open()) {
            LOG_ERROR("Failed to open temporary file for merging: %s", filename.c_str());
            return RC::IOERR_READ;
        }
    }

    // Initialize current tuples and run status
    current_tuples_.resize(temp_files_.size());
    run_exhausted_.assign(temp_files_.size(), false);

    // Initialize the priority queue
    merge_pq_ = std::make_unique<std::priority_queue<MergeElement, std::vector<MergeElement>, MergeElementComparator>>(MergeElementComparator(this));

    // Load the first tuple from each run and push the first element to the PQ
    for (size_t i = 0; i < temp_files_.size(); ++i) {
        RC rc = load_next_tuple_from_run(i);
        if (rc == RC::SUCCESS) {
            std::vector<Value> keys;
            const auto& tuple = current_tuples_[i];
            for (const auto& expr : order_by_) {
                Value val;
                expr->get_value(tuple, val);
                keys.push_back(val);
            }
            merge_pq_->push({keys, i});
        } else if (rc != RC::RECORD_EOF) {
            return rc; // Error loading initial tuple
        }
    }

    LOG_INFO("External sort merge phase initialized with %zu temporary files.", temp_files_.size());

    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::sort_and_write_chunk(const std::vector<ValueListTuple>& chunk, std::string& temp_file)
{
    // 创建临时文件
    temp_file = create_temp_file();
    if (temp_file.empty()) {
        LOG_ERROR("Failed to create temporary file");
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
    RC rc = write_chunk_to_file(sorted_chunk, temp_file);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to write chunk to file: %s", strrc(rc));
        return rc;
    }
    
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

RC OrderByPhysicalOperator::read_single_tuple_from_stream(ValueListTuple& tuple, std::ifstream& file)
{
    // 读取tuple的cell数量
    int cell_num;
    file.read(reinterpret_cast<char*>(&cell_num), sizeof(cell_num));
    if (file.eof()) {
        return RC::RECORD_EOF;
    }
    if (!file) {
        LOG_ERROR("Failed to read cell number from file");
        return RC::IOERR_READ;
    }
    
    // 创建ValueListTuple
    std::vector<Value> cells;
    cells.reserve(cell_num);
    
    // 读取每个cell
    for (int i = 0; i < cell_num; i++) {
        AttrType type;
        file.read(reinterpret_cast<char*>(&type), sizeof(type));
        if (!file) {
            LOG_ERROR("Failed to read cell type from file");
            return RC::IOERR_READ;
        }
        
        Value cell;
        switch (type) {
            case AttrType::INTS: {
                int val;
                file.read(reinterpret_cast<char*>(&val), sizeof(val));
                if (!file) {
                    LOG_ERROR("Failed to read int value from file");
                    return RC::IOERR_READ;
                }
                cell = Value(val);
                break;
            }
            case AttrType::FLOATS: {
                float val;
                file.read(reinterpret_cast<char*>(&val), sizeof(val));
                if (!file) {
                    LOG_ERROR("Failed to read float value from file");
                    return RC::IOERR_READ;
                }
                cell = Value(val);
                break;
            }
            case AttrType::CHARS: {
                int length;
                file.read(reinterpret_cast<char*>(&length), sizeof(length));
                if (!file) {
                    LOG_ERROR("Failed to read string length from file");
                    return RC::IOERR_READ;
                }
                
                std::string str(length, '\0');
                file.read(&str[0], length);
                if (!file) {
                    LOG_ERROR("Failed to read string value from file");
                    return RC::IOERR_READ;
                }
                cell = Value(str.c_str(), str.length());
                break;
            }
            case AttrType::TEXTS: {
                int length;
                file.read(reinterpret_cast<char*>(&length), sizeof(length));
                if (!file) {
                    LOG_ERROR("Failed to read text length from file");
                    return RC::IOERR_READ;
                }
                
                std::string str(length, '\0');
                file.read(&str[0], length);
                if (!file) {
                    LOG_ERROR("Failed to read text value from file");
                    return RC::IOERR_READ;
                }
                cell = Value(str.c_str(), str.length());
                break;
            }
            case AttrType::NULLS: {
                cell.set_null();
                break;
            }
            default: {
                LOG_ERROR("Unknown attribute type: %d", static_cast<int>(type));
                return RC::INVALID_ARGUMENT;
            }
        }
        cells.emplace_back(std::move(cell));
    }
    
    // 创建ValueListTuple
    RC rc = ValueListTuple::make(cells, tuple);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create ValueListTuple from cells");
        return rc;
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