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
  stringstream deserialize_stream;
  deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
  deserialize_stream.str(left.get_string());
  int left_year, left_month, left_day;
  deserialize_stream >> left_year >> left_month >> left_day;
  left_month = -left_month;
  left_day = -left_day;

  deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
  deserialize_stream.str(right.get_string());
  int right_year, right_month, right_day;
  deserialize_stream >> right_year >> right_month >> right_day;
  right_month = -right_month;
  right_day = -right_day;

  if(left_year == right_year){
    if(left_month == right_month){
      if(left_day == right_day)return 0;
      return (left_day < right_day ? -1 : 1);
    }
    return (left_month < right_month ? -1 : 1);
  }
  return (left_year < right_year ? -1 : 1);
}

RC DateType::set_value_from_str(Value &val, const string &data) const
{
  val.set_date(data.c_str(), 10);
  return RC::SUCCESS;
}

RC DateType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::CHARS: 
      result.set_string(val.data(), val.length_);
      return RC::SUCCESS;
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int DateType::cast_cost(AttrType type)
{
  if (type == AttrType::DATES || type == AttrType::CHARS) {
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
