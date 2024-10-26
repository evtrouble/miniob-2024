/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <cmath>

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/vector_type.h"
#include "common/value.h"

int VectorType::compare(const Value &left, const Value &right) const
{
    ASSERT(left.attr_type() == AttrType::VECTORS && right.attr_type() == AttrType::VECTORS, "invalid type");
    vector<float>* left_vector = (vector<float>*)left.data();
    vector<float>* right_vector = (vector<float>*)right.data();
    ASSERT(left_vector->size() == right_vector->size(), "invalid type");
    
    for(size_t id = 0; id < left_vector->size(); id++){
        if(left_vector->at(id) - right_vector->at(id) > EPSILON)return 1;
        if(left_vector->at(id) - right_vector->at(id) < -EPSILON)return -1;
    }
    return 0;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const 
{
    ASSERT(left.attr_type() == AttrType::VECTORS && right.attr_type() == AttrType::VECTORS, "invalid type");
    vector<float>* left_vector = (vector<float>*)left.data();
    vector<float>* right_vector = (vector<float>*)right.data();
    ASSERT(left_vector->size() == right_vector->size(), "invalid type");
    
    vector<float> *temp = new vector<float>(left_vector->size());
    for(size_t id = 0; id < left_vector->size(); id++){
        temp->at(id) = left_vector->at(id) + right_vector->at(id);
    }
    result.set_vector(move(*temp));
    return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const 
{
    ASSERT(left.attr_type() == AttrType::VECTORS && right.attr_type() == AttrType::VECTORS, "invalid type");
    vector<float>* left_vector = (vector<float>*)left.data();
    vector<float>* right_vector = (vector<float>*)right.data();
    ASSERT(left_vector->size() == right_vector->size(), "invalid type");
    
    vector<float> *temp = new vector<float>(left_vector->size());
    for(size_t id = 0; id < left_vector->size(); id++){
        temp->at(id) = left_vector->at(id) - right_vector->at(id);
    }
    result.set_vector(move(*temp));
    return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const 
{
    ASSERT(left.attr_type() == AttrType::VECTORS && right.attr_type() == AttrType::VECTORS, "invalid type");
    vector<float>* left_vector = (vector<float>*)left.data();
    vector<float>* right_vector = (vector<float>*)right.data();
    ASSERT(left_vector->size() == right_vector->size(), "invalid type");

    vector<float> *temp = new vector<float>(left_vector->size());
    for (size_t id = 0; id < left_vector->size(); id++) {
        temp->at(id) = left_vector->at(id) * right_vector->at(id);
    }
    
    result.set_vector(move(*temp));
    return RC::SUCCESS;
}


RC VectorType::to_string(const Value &val, string &result) const
{
    ASSERT(val.attr_type() == AttrType::VECTORS, "invalid type");
    vector<float>* val_vector = (vector<float>*)val.data();
    result = "[";
    Value temp;
    size_t id = 0;
    for(; id < val_vector->size() - 1; id++){
        temp.set_float(val_vector->at(id));
        result += temp.to_string() + ",";
    }
    temp.set_float(val_vector->at(id));
    result += temp.to_string() + "]";
    return RC::SUCCESS;
}

RC VectorType::l2_distance(const Value &left, const Value &right, Value &result) const
{
    ASSERT(left.attr_type() == AttrType::VECTORS && right.attr_type() == AttrType::VECTORS, "invalid type");
    vector<float>* left_vector = (vector<float>*)left.data();
    vector<float>* right_vector = (vector<float>*)right.data();
    ASSERT(left_vector->size() == right_vector->size(), "invalid type");

    double ans = 0;
    for (size_t id = 0; id < left_vector->size(); id++) {
        double diff = left_vector->at(id) - right_vector->at(id);
        ans += diff * diff;
    }
    result.set_float(static_cast<float>(sqrt(ans)));
    return RC::SUCCESS;
}

RC VectorType::cosine_distance(const Value &left, const Value &right, Value &result) const
{
    ASSERT(left.attr_type() == AttrType::VECTORS && right.attr_type() == AttrType::VECTORS, "invalid type");
    vector<float>* left_vector = (vector<float>*)left.data();
    vector<float>* right_vector = (vector<float>*)right.data();
    ASSERT(left_vector->size() == right_vector->size(), "invalid type");

    double a2 = 0, b2 = 0, ab = 0;
    for (size_t id = 0; id < left_vector->size(); id++) {
        double a = left_vector->at(id);
        double b = right_vector->at(id);
        a2 += a * a;
        b2 += b * b;
        ab += a * b;
    }

    double norm_a = sqrt(a2);
    double norm_b = sqrt(b2);
    if (norm_a == 0 || norm_b == 0) {
        result.set_float(0);
    } else {
        result.set_float(static_cast<float>(fabs(1 - ab / (norm_a * norm_b))));
    }
    return RC::SUCCESS;
}


RC VectorType::inner_product(const Value &left, const Value &right, Value &result) const
{
    return multiply(left, right, result);
}