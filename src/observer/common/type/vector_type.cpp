/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/vector_type.h"
#include "common/value.h"

RC VectorType::add(const Value &left, const Value &right, Value &result) const 
{
    return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const 
{
    return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const 
{
    return RC::SUCCESS;
}

RC VectorType::to_string(const Value &val, string &result) const
{
    return RC::SUCCESS;
}