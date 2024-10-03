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
#include "common/type/char_type.h"
#include "common/value.h"

int CharType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC CharType::max(const Value &left, const Value &right, Value &result) const
{
  if(compare(left, right) > 0){
    result.set_string_from_other(left);
  }else if(&right != &result)result.set_string_from_other(right);
  return RC::SUCCESS;
}

RC CharType::min(const Value &left, const Value &right, Value &result) const
{
  if(compare(left, right) < 0){
    result.set_string_from_other(left);
  }else if(&right != &result)result.set_string_from_other(right);
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::INTS: {
      const char* s = val.data();
      int temp = 0;
      if(s[0] >= '0' && s[0] <= '9')
      {
        stringstream deserialize_stream;
        deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
        deserialize_stream.str(s);
        deserialize_stream >> temp;
      }
      result.set_int(temp);
    }break;
    case AttrType::FLOATS: {
      const char* s = val.data();
      float temp = 0;
      if(s[0] >= '0' && s[0] <= '9')
      {
        stringstream deserialize_stream;
        deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
        deserialize_stream.str(s);
        deserialize_stream >> temp;
      }
      result.set_float(temp);
    }break;
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS) {
    return 0;
  }
  if (type == AttrType::INTS)return 100;
  if (type == AttrType::FLOATS)return 10;
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}