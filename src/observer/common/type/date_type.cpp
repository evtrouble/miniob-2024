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
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"

int DateType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::DATES || right.attr_type() == AttrType::DATES, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, 10, (void *)right.value_.pointer_value_, 10);
}

RC DateType::set_value_from_str(Value &val, const string &data) const
{
  val.set_date(data.c_str());
  return RC::SUCCESS;
}


RC DateType::max(const Value &left, const Value &right, Value &result) const
{
  if(compare(left, right) > 0){
    if(&left != &result)result.set_date(left.data());
  }else if(&right != &result)result.set_date(right.data());
  return RC::SUCCESS;
}

RC DateType::min(const Value &left, const Value &right, Value &result) const
{
  if(compare(left, right) < 0){
    result.set_date(left.data());
  }else if(&right != &result)result.set_date(right.data());
  return RC::SUCCESS;
}

RC DateType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int DateType::cast_cost(AttrType type)
{
  if (type == AttrType::DATES) {
    return 0;
  }
  return INT32_MAX;
}

RC DateType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}
