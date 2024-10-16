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

#include "sql/operator/order_by_physical_operator.h"

OrderByPhysicalOperator::OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>>&& order_by, std::vector<bool>&& is_asc)
    : order_by_(move(order_by)), is_asc_(move(is_asc)){}

RC OrderByPhysicalOperator::open(Trx *trx)
{
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
    orders_.clear();
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next()
{
    RC                rc    = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    Tuple* tuple = nullptr;
    if(!have_value){
        while (OB_SUCC(rc = child->next())) {
            tuple = child->current_tuple();
            if (nullptr == tuple) {
                LOG_WARN("failed to get current record: %s", strrc(rc));
                child->close();
                return rc;
            }
            orders_.emplace_back(tuple);
        }

        if (RC::RECORD_EOF == rc) {
            rc = RC::SUCCESS;
        }

        if (OB_FAIL(rc)) {
            LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
            return rc;
        }

        sort(orders_.begin(), orders_.end(), [&](const auto& a, const auto& b){
            for(size_t id = 0; id < order_by_.size(); id++){
                Value a_val, b_val;
                auto& expr = order_by_[id];
                bool is_asc = is_asc_[id];

                rc = expr->get_value(*a, a_val);
                rc = expr->get_value(*b, b_val);
                if(a_val.attr_type() == AttrType::NULLS || b_val.attr_type() == AttrType::NULLS){
                    return !is_asc;
                }
                int cmp = a_val.compare(b_val);
                if(cmp == 0)continue;
                else if(is_asc)return cmp < 0;
                else return cmp > 0;
            }
            return true;
        });
        
        if(rc != RC::SUCCESS)return rc;

        current_order_ = orders_.begin();
        first_emited_  = false;
        have_value = true;
    }

    return fetch_next();
}

RC OrderByPhysicalOperator::close()
{
    children_[0]->close();
    LOG_INFO("close order by operator");
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next(Tuple *upper_tuple) 
{
    RC                rc    = RC::SUCCESS;
    std::unique_ptr<PhysicalOperator> &child = children_[0];
    Tuple* tuple = nullptr;
    if(!have_value){
        while (OB_SUCC(rc = child->next(upper_tuple))) {
            tuple = child->current_tuple();
            if (nullptr == tuple) {
                LOG_WARN("failed to get current record: %s", strrc(rc));
                child->close();
                return rc;
            }
            orders_.emplace_back(tuple);
        }

        if (RC::RECORD_EOF == rc) {
            rc = RC::SUCCESS;
        }

        if (OB_FAIL(rc)) {
            LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
            return rc;
        }

        sort(orders_.begin(), orders_.end(), [&](const auto& a, const auto& b){
            for(size_t id = 0; id < order_by_.size(); id++){
                Value a_val, b_val;
                auto& expr = order_by_[id];
                bool is_asc = is_asc_[id];

                rc = expr->get_value(*a, a_val);
                rc = expr->get_value(*b, b_val);
                if(a_val.attr_type() == AttrType::NULLS || b_val.attr_type() == AttrType::NULLS){
                    return !is_asc;
                }
                int cmp = a_val.compare(b_val);
                if(cmp == 0)continue;
                else if(is_asc)return cmp < 0;
                else return cmp > 0;
            }
            return true;
        });

        if(rc != RC::SUCCESS)return rc;

        current_order_ = orders_.begin();
        first_emited_  = false;
        have_value = true;
    }

    return fetch_next();
}

Tuple *OrderByPhysicalOperator::current_tuple()
{
  if (current_order_ != orders_.end()) {
    return *current_order_;
  }
  return nullptr;
}

RC OrderByPhysicalOperator::fetch_next()
{
  if (current_order_ == orders_.end()) {
    return RC::RECORD_EOF;
  }

  if (first_emited_) {
    ++current_order_;
  } else {
    first_emited_ = true;
  }
  if (current_order_ == orders_.end()) {
    return RC::RECORD_EOF;
  }

  return RC::SUCCESS;
}