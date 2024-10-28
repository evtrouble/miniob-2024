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

#include "sql/operator/order_by_physical_operator.h"

using namespace std;

OrderByPhysicalOperator::OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>>&& order_by, std::vector<bool>&& is_asc, int limit)
    : order_by_(move(order_by)), is_asc_(move(is_asc)), limit_(limit){}

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
        if(limit_ < 0)rc = quick_sort();
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
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next(Tuple *upper_tuple) 
{
    RC                rc    = RC::SUCCESS;
    if(!have_value){
        if(limit_ < 0)rc = quick_sort(upper_tuple);
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
  if (current_id_ != value_list_.size()) {
    return &value_list_[ids_[current_id_]];
  }
  return nullptr;
}

RC OrderByPhysicalOperator::fetch_next()
{
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
                value_list_[id] = move(value_list);
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