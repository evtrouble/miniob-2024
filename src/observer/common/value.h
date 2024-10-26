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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include "common/lang/string.h"
#include "common/lang/memory.h"
#include "common/type/attr_type.h"
#include "common/type/data_type.h"

static constexpr int MAX_TEXT_LENGTH = 65535;//设置TEXT数据的最大长度
class Date;
class ParsedSqlNode;

/**
 * @brief 属性的值
 * @ingroup DataType
 * @details 与DataType，就是数据类型，配套完成各种算术运算、比较、类型转换等操作。这里同时记录了数据的值与类型。
 * 当需要对值做运算时，建议使用类似 Value::add 的操作而不是 DataType::add。在进行运算前，应该设置好结果的类型，
 * 比如进行两个INT类型的除法运算时，结果类型应该设置为FLOAT。
 */
class Value final
{
public:
  friend class DataType;
  friend class IntegerType;
  friend class FloatType;
  friend class BooleanType;
  friend class CharType;
  friend class DateType;
  friend class VectorType;

  Value() = default;
  Value(void*) { set_null(); }

  ~Value() { reset(); }

  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type) { this->set_data(data, length); }

  explicit Value(int val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(const char *s, int len = 0);
  explicit Value(const Date *s, int len = 0);
  explicit Value(int64_t val);//添加int64_t的Value构造函数

  Value(const Value &other) noexcept;
  Value(Value &&other) noexcept;

  Value &operator=(const Value &other) noexcept;
  Value &operator=(Value &&other) noexcept;

  void reset();

  static RC add(const Value &left, const Value &right, Value &result)
  {
    if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->add(left, right, result);
  }

  static RC subtract(const Value &left, const Value &right, Value &result)
  {
    if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->subtract(left, right, result);
  }

  static RC multiply(const Value &left, const Value &right, Value &result)
  {
    if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->multiply(left, right, result);
  }

  static RC divide(const Value &left, const Value &right, Value &result)
  {
    if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->divide(left, right, result);
  }

  static RC negative(const Value &value, Value &result)
  {
    if(value.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->negative(value, result);
  }

  static RC cast_to(const Value &value, AttrType to_type, Value &result)
  {
    if(value.attr_type_ == AttrType::NULLS){
      result = std::move(value);
      return RC::SUCCESS;
    }
    return DataType::type_instance(value.attr_type())->cast_to(value, to_type, result);
  }

  static RC max(const Value &&left, const Value &&right, Value &result)
  {
    int cmp = left.compare(right);
    if(cmp > 0)result = left;
    else if(cmp < 0)result = right;
    return RC::SUCCESS;
  }

  static RC min(const Value &&left, const Value &&right, Value &result)
  {
    int cmp = left.compare(right);
    if(cmp < 0)result = std::move(left);
    else if(cmp > 0)result = std::move(right);
    return RC::SUCCESS;
  }

  static RC avg(const Value &val, Value &result, Value& num)
  {
    Value float_result;
    RC rc = RC::SUCCESS;

    num.set_int(num.get_int() + 1);
    if(val.attr_type() != AttrType::FLOATS){
      rc = cast_to(val, AttrType::FLOATS, float_result);
      if(rc != RC::SUCCESS)return rc;
      result.set_float(result.get_float() + float_result.get_float());
    } else
      result.set_float(result.get_float() + val.get_float());
    
    return rc;
  }

  static RC count(Value &result)
  {
    result.set_int(result.get_int() + 1);
    return RC::SUCCESS;
  }

  static RC l2_distance(const Value &left, const Value &right, Value &result)
  {
    if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->l2_distance(left, right, result);
  }

  static RC cosine_distance(const Value &left, const Value &right, Value &result)
  {
    if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->cosine_distance(left, right, result);
  }

  static RC inner_product(const Value &left, const Value &right, Value &result)
  {
    if(left.attr_type_ == AttrType::NULLS || right.attr_type_ == AttrType::NULLS){
      result.set_null();
      return RC::SUCCESS;
    }
    return DataType::type_instance(result.attr_type())->inner_product(left, right, result);
  }

public:
  void set_type(AttrType type) { this->attr_type_ = type; }
  void set_data(char *data, int length);
  void set_data(const char *data, int length) { this->set_data(const_cast<char *>(data), length); }
  void set_value(const Value &value);
  void set_boolean(bool val);
  void set_vector(const char *data, int length);
  void set_vector(const char *data);
  void set_vector(vector<float>* embedding);
  void set_vector(vector<float>&& embedding);
  void set_null();
  void set_long(int64_t val);

  string to_string() const;

  int compare(const Value &other) const;

  const char *data() const;

  int      length() const { return length_; }
  AttrType attr_type() const { return attr_type_; }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   */
  int    get_int() const;
  float  get_float() const;
  string get_string() const;
  bool   get_boolean() const;
  int64_t get_long() const;

  static constexpr int ATTR_TYPE_LENGTH[] = {-1, 4, 4, 4, 4, 1, 10, 4, 8, 0};

private:
  void set_int(int val);
  void set_float(float val);
  void set_string(const char *s, int len = 0);
  void set_date(const char *s, int len = 10);
  void set_string_from_other(const Value &other);
  void set_date_from_other(const Value &other);
  void set_vector_from_other(const Value &other);
  bool check_date(const char *data);

private:
  AttrType attr_type_ = AttrType::UNDEFINED;
  int      length_    = 0;

  union Val
  {
    int32_t int_value_;
    float   float_value_;
    bool    bool_value_;
    char   *pointer_value_;
    vector<float>   *vector_value_;
    ParsedSqlNode   *select_value_;
    int64_t long_value_;
  } value_ = {.int_value_ = 0};

  /// 是否申请并占有内存, 目前对于 CHARS 类型 own_data_ 为true, 其余类型 own_data_ 为false
  bool own_data_ = false;
};
