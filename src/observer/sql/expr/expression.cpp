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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/expr/arithmetic_operator.hpp"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/executor/sql_result.h"
#include "sql/stmt/select_stmt.h"

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

bool FieldExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::FIELD) {
    return false;
  }
  const auto &other_field_expr = static_cast<const FieldExpr &>(other);
  return table_name() == other_field_expr.table_name() && field_name() == other_field_expr.field_name();
}

// TODO: 在进行表达式计算时，`chunk` 包含了所有列，因此可以通过 `field_id` 获取到对应列。
// 后续可以优化成在 `FieldExpr` 中存储 `chunk` 中某列的位置信息。
RC FieldExpr::get_column(Chunk &chunk, Column &column)
{
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    column.reference(chunk.column(field().meta()->field_id()));
  }
  return RC::SUCCESS;
}

bool ValueExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::VALUE) {
    return false;
  }
  const auto &other_value_expr = static_cast<const ValueExpr &>(other);
  return value_.compare(other_value_expr.get_value()) == 0;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::get_column(Chunk &chunk, Column &column)
{
  column.init(value_);
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }
  rc = Value::cast_to(value, cast_type_, cast_value);
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &result) const
{
  Value value;
  RC rc = child_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC CastExpr::get_value_set(const Tuple &tuple, vector<Value> &value_list)const 
{
  RC rc = child_->get_value_set(tuple, value_list);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  Value temp;
  for(auto& value : value_list){
    rc = cast(value, temp);
    if(rc != RC::SUCCESS)return rc;
    value = move(temp);
  }
  return rc;
}

RC CastExpr::try_get_value(Value &result) const
{
  Value value;
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{
  if((comp_ == CompOp::LIKE_OP || comp_ == CompOp::NOT_LIKE)
     && right_->type() == ExprType::VALUE){
    Value pattern_val;
    static_cast<ValueExpr*>(right_.get())->get_value(pattern_val);
    string right_string = pattern_val.get_string();
    string pattern_string;
    for(auto& c : right_string){
      switch (c)
      {
      case '_':pattern_string.append(1, '.');break;
      case '%':pattern_string.append(".*");break;
      case '*':case '.':pattern_string.append(1, '\\');
      default:pattern_string.append(1, c);
        break;
      }
    }
    pattern.assign(std::move(pattern_string));
  }
}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  if(left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS){
    result = false;
    return RC::SUCCESS;
  }
  RC  rc         = RC::SUCCESS;
  int cmp_result = left.compare(right);
  result         = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::like_value(const Tuple &tuple, bool &result) const
{
  if(right_->type() != ExprType::VALUE)return RC::INVALID_ARGUMENT;

  Value left_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if(left_value.attr_type() == AttrType::NULLS)
  {
    result = false;
    return RC::SUCCESS;
  }

  result = regex_match(left_value.get_string(), pattern);
  return RC::SUCCESS;
}

RC ComparisonExpr::value_exists(const Tuple &tuple, bool &result) const
{
  if(right_->type() != ExprType::SELECT)return RC::INVALID_ARGUMENT;

  Value right_value;

  RC rc = right_->get_value(tuple, right_value);
  
  if (rc != RC::SUCCESS && rc != RC::NULL_TUPLE && rc != RC::MUTI_TUPLE) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  result = !(rc == RC::NULL_TUPLE); 
  return RC::SUCCESS;
}

RC ComparisonExpr::value_in(const Tuple &tuple, bool &result) const
{
  if(right_->type() != ExprType::SELECT && right_->type() != ExprType::VALUE_LIST)
    return RC::INVALID_ARGUMENT;

  result = false;
  Value left_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if(left_value.attr_type() == AttrType::NULLS)return RC::SUCCESS;

  vector<Value> value_list;
  rc = right_->get_value_set(tuple, value_list);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  for(auto& value : value_list){
    if(value.attr_type() != AttrType::NULLS && left_value.compare(value) == 0){
      result = true;
      break;
    }
  }

  return RC::SUCCESS;
}

RC ComparisonExpr::value_not_in(const Tuple &tuple, bool &result) const
{
  if(right_->type() != ExprType::SELECT && right_->type() != ExprType::VALUE_LIST)
    return RC::INVALID_ARGUMENT;

  result = false;
  Value left_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if(left_value.attr_type() == AttrType::NULLS)return RC::SUCCESS;

  vector<Value> value_list;
  rc = right_->get_value_set(tuple, value_list);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  for(auto& value : value_list){
    if(value.attr_type() == AttrType::NULLS)
    {
      result = false;
      return RC::SUCCESS;
    }
    else if(left_value.compare(value) == 0){
      result = true;
    }
  }
  result = !result;

  return RC::SUCCESS;
}

RC ComparisonExpr::value_is_null(const Tuple &tuple, bool &result) const
{
  if(right_->type() != ExprType::VALUE || right_->value_type() != AttrType::NULLS)
    return RC::INVALID_ARGUMENT;

  Value left_value;
  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  result = (left_value.attr_type() == AttrType::NULLS);
  
  return RC::SUCCESS;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *  left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr *  right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    if(comp_ == CompOp::IS_NULL || comp_ == CompOp::IS_NOT_NULL){
      if(right_cell.attr_type() != AttrType::NULLS)return RC::INVALID_ARGUMENT;
      if((comp_ == CompOp::IS_NULL && left_cell.attr_type() == AttrType::NULLS) || 
        (comp_ == CompOp::IS_NOT_NULL && left_cell.attr_type() != AttrType::NULLS))
          cell.set_boolean(true);
      else cell.set_boolean(false);
      return RC::SUCCESS;
    }
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  bool bool_value = false;
  
  switch (comp_)
  {
    case CompOp::LIKE_OP:{
      rc = like_value(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(bool_value);
      }
    }break;
    case CompOp::NOT_LIKE:{
      rc = like_value(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(!bool_value);
      }
    }break;
    case CompOp::EXISTS_OP:{
      rc = value_exists(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(bool_value);
      }
    }break;
    case CompOp::NOT_EXISTS:{
      rc = value_exists(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(!bool_value);
      }
    }break;
    case CompOp::IN_OP:{
      rc = value_in(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(bool_value);
      }
    }break;
    case CompOp::NOT_IN:{
      rc = value_not_in(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(bool_value);
      }
    }break;
    case CompOp::IS_NULL:{
      rc = value_is_null(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(bool_value);
      }
    }break;
    case CompOp::IS_NOT_NULL:{
      rc = value_is_null(tuple, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(!bool_value);
      }
    }break;
    default:{
      Value left_value;
      Value right_value;

      rc = left_->get_value(tuple, left_value);
      if(rc == RC::NULL_TUPLE){
        value.set_boolean(false);
        return RC::SUCCESS;
      }
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
        return rc;
      }
      rc = right_->get_value(tuple, right_value);
      if(rc == RC::NULL_TUPLE){
        value.set_boolean(false);
        return RC::SUCCESS;
      }
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
        return rc;
      }

      rc = compare_value(left_value, right_value, bool_value);
      if (rc == RC::SUCCESS) {
        value.set_boolean(bool_value);
      }
    }break;
  }
  return rc;
}

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select)
{
  RC     rc = RC::SUCCESS;
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  if (left_column.attr_type() != right_column.attr_type()) {
    LOG_WARN("cannot compare columns with different types");
    return RC::INTERNAL;
  }
  if (left_column.attr_type() == AttrType::INTS) {
    rc = compare_column<int>(left_column, right_column, select);
  } else if (left_column.attr_type() == AttrType::FLOATS) {
    rc = compare_column<float>(left_column, right_column, select);
  } else {
    // TODO: support string compare
    LOG_WARN("unsupported data type %d", left_column.attr_type());
    return RC::INTERNAL;
  }
  return rc;
}

template <typename T>
RC ComparisonExpr::compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const
{
  RC rc = RC::SUCCESS;

  bool left_const  = left.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    compare_result<T, true, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else if (left_const && !right_const) {
    compare_result<T, true, false>((T *)left.data(), (T *)right.data(), right.count(), result, comp_);
  } else if (!left_const && right_const) {
    compare_result<T, false, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else {
    compare_result<T, false, false>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool ArithmeticExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &other_arith_expr = static_cast<const ArithmeticExpr &>(other);
  return arithmetic_type_ == other_arith_expr.arithmetic_type() && left_->equal(*other_arith_expr.left_) &&
         right_->equal(*other_arith_expr.right_);
}
AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  value.set_type(target_type);

  switch (arithmetic_type_) {
    case Type::ADD: {
      Value::add(left_value, right_value, value);
    } break;

    case Type::SUB: {
      Value::subtract(left_value, right_value, value);
    } break;

    case Type::MUL: {
      Value::multiply(left_value, right_value, value);
    } break;

    case Type::DIV: {
      Value::divide(left_value, right_value, value);
    } break;

    case Type::NEGATIVE: {
      Value::negative(left_value, value);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
RC ArithmeticExpr::execute_calc(
    const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const
{
  RC rc = RC::SUCCESS;
  switch (type) {
    case Type::ADD: {
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, AddOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, AddOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
    } break;
    case Type::SUB:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, SubtractOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, SubtractOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::MUL:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, MultiplyOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, MultiplyOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::DIV:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, DivideOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, DivideOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::NEGATIVE:
      if (attr_type == AttrType::INTS) {
        unary_operator<LEFT_CONSTANT, int, NegateOperator>((int *)left.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        unary_operator<LEFT_CONSTANT, float, NegateOperator>(
            (float *)left.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    default: rc = RC::UNIMPLEMENTED; break;
  }
  if (rc == RC::SUCCESS) {
    result.set_count(result.capacity());
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
    return rc;
  }
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_column(left_column, right_column, column);
}

RC ArithmeticExpr::calc_column(const Column &left_column, const Column &right_column, Column &column) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  column.init(target_type, left_column.attr_len(), std::max(left_column.count(), right_column.count()));
  bool left_const  = left_column.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right_column.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    column.set_column_type(Column::Type::CONSTANT_COLUMN);
    rc = execute_calc<true, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (left_const && !right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<true, false>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (!left_const && right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, false>(left_column, right_column, column, arithmetic_type_, target_type);
  }
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////

UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, Expression *child)
    : aggregate_name_(aggregate_name), child_(child)
{}

////////////////////////////////////////////////////////////////////////////////
AggregateExpr::AggregateExpr(Type type, Expression *child) : aggregate_type_(type), child_(child) {}

AggregateExpr::AggregateExpr(Type type, unique_ptr<Expression> child) : aggregate_type_(type), child_(std::move(child))
{}

RC AggregateExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    rc = RC::INTERNAL;
  }
  return rc;
}

bool AggregateExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const AggregateExpr &other_aggr_expr = static_cast<const AggregateExpr &>(other);
  return aggregate_type_ == other_aggr_expr.aggregate_type() && child_->equal(*other_aggr_expr.child());
}

unique_ptr<Aggregator> AggregateExpr::create_aggregator() const
{
  unique_ptr<Aggregator> aggregator;
  switch (aggregate_type_) {
    case Type::SUM: {
      aggregator = make_unique<SumAggregator>();
      break;
    }
    case Type::COUNT: {
      aggregator = make_unique<CountAggregator>();
      break;
    }
    case Type::MAX: {
      aggregator = make_unique<MaxAggregator>();
      break;
    }
    case Type::MIN: {
      aggregator = make_unique<MinAggregator>();
      break;
    }
    case Type::AVG: {
      aggregator = make_unique<AvgAggregator>();
      break;
    }
    default: {
      ASSERT(false, "unsupported aggregate type");
      break;
    }
  }
  return aggregator;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(name()), value);
}

RC AggregateExpr::type_from_string(const char *type_str, AggregateExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "count")) {
    type = Type::COUNT;
  } else if (0 == strcasecmp(type_str, "sum")) {
    type = Type::SUM;
  } else if (0 == strcasecmp(type_str, "avg")) {
    type = Type::AVG;
  } else if (0 == strcasecmp(type_str, "max")) {
    type = Type::MAX;
  } else if (0 == strcasecmp(type_str, "min")) {
    type = Type::MIN;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

RC SelectExpr::logical_generate()
{
  RC rc = RC::SUCCESS;
  rc = LogicalPlanGenerator().create(stmt_, logical_operator_);
  value_type_ = logical_operator_->expressions().at(0)->value_type();
  return rc;
}

SelectExpr::SelectExpr(ParsedSqlNode* sql_node) : sql_node_(sql_node){}

RC SelectExpr::physical_generate()
{
  return PhysicalPlanGenerator().create(*logical_operator_, physical_operator_);
}

SelectExpr::~SelectExpr(){
  if(stmt_ != nullptr)delete stmt_;
  if(sql_node_ != nullptr)delete sql_node_;
}

RC SelectExpr::create_stmt(Db *db, unique_ptr<vector<vector<uint32_t>>>& depends, unique_ptr<vector<SelectExpr*>>& select_exprs,
  tables_t& table_map, int fa)
{
  return Stmt::create_stmt(db, *sql_node_, stmt_, depends, select_exprs, table_map, fa);
}

RC SelectExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if(values_ != nullptr){
    if(values_->size() == 0 || values_->at(0).size() == 0)
      return RC::NULL_TUPLE;
    if(values_->size() > 1 || values_->at(0).size() > 1)
      return RC::MUTI_TUPLE;
    value = values_->at(0)[0];
    return rc;
  }

  physical_operator_->open(trx_);
  Tuple *ret_tuple = nullptr;
  auto temp = const_cast<Tuple*>(&tuple);
  int num = 0;
  while (RC::SUCCESS == (rc = next_tuple(ret_tuple, temp))) {   
    assert(ret_tuple != nullptr);

    num++;
    if(num > 1){
      physical_operator_->close();
      return RC::MUTI_TUPLE;
    }
    
    ret_tuple->cell_at(0, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get tuple cell value. rc=%s", strrc(rc));
      return rc;
    }
  }

  physical_operator_->close();

  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }
  if(num == 0)return RC::NULL_TUPLE;
  return rc;
}

RC SelectExpr::get_value_set(const Tuple &tuple, vector<Value> &value_list) const
{
  RC rc = RC::SUCCESS;
  
  if(values_ != nullptr){
    for(auto& values : *values_){
      if(values.size() == 0)return RC::INVALID_ARGUMENT;
      if(values.size() > 1)return RC::INVALID_ARGUMENT;
      value_list.emplace_back(values[0]);
    }
    return rc;
  }

  physical_operator_->open(trx_);
  Tuple *ret_tuple = nullptr;
  auto temp = const_cast<Tuple*>(&tuple);

  Value value_get;
  while (RC::SUCCESS == (rc = next_tuple(ret_tuple, temp))) {   
    assert(ret_tuple != nullptr);
    
    rc = ret_tuple->cell_at(0, value_get);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get tuple cell value. rc=%s", strrc(rc));
      return rc;
    }

    value_list.emplace_back(value_get);
  }

  physical_operator_->close();

  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }
  return rc;
}

RC SelectExpr::next_tuple(Tuple *&tuple, Tuple *upper_tuple) const
{
  RC rc = RC::SUCCESS;
  if(upper_tuple == nullptr)
    rc = physical_operator_->next();
  else rc = physical_operator_->next(upper_tuple); 
  if (rc != RC::SUCCESS) {
    return rc;
  }

  tuple = physical_operator_->current_tuple();
  return rc;
}

RC SelectExpr::pretreatment()
{
  RC rc = RC::SUCCESS;
  Tuple *tuple = nullptr;
  physical_operator_->open(trx_);
  if(values_ == nullptr)
    values_ = make_unique<vector<vector<Value>>>();

  Value value;
  while (RC::SUCCESS == (rc = next_tuple(tuple))) {
    assert(tuple != nullptr);

    int cell_num = tuple->cell_num();
    auto size = values_->size();
    values_->emplace_back(vector<Value>());

    for (int i = 0; i < cell_num; i++) {
      rc = tuple->cell_at(i, value);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get tuple cell value. rc=%s", strrc(rc));
        return rc;
      }
      values_->at(size).emplace_back(move(value));
    }
  }

  physical_operator_->close();

  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }

  return rc;
}

RC ValueListExpr::get_value(const Tuple &tuple, Value &value) const 
{
  return exprs_[0]->get_value(tuple, value);
}

RC ValueListExpr::get_value_set(const Tuple &tuple, vector<Value> &value_list) const
{
  RC rc = RC::SUCCESS;
  Value value;
  for(auto& expr : exprs_){
    rc = expr->get_value(tuple, value);
    if(rc != RC::SUCCESS)return rc;
    value_list.emplace_back(move(value));
  }
  return RC::SUCCESS;
}