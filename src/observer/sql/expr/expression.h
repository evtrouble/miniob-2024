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

#pragma once

#include <memory>
#include <string>
#include <regex>
#include <unordered_set>

#include "common/value.h"
#include "storage/field/field.h"
#include "sql/expr/aggregator.h"
#include "storage/common/chunk.h"
#include "sql/parser/expression_binder.h"

class Tuple;
class Stmt;
class LogicalOperator;
class PhysicalOperator;
class Session;
class ParsedSqlNode;
class SqlResult;

/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType
{
  NONE,
  STAR,                 ///< 星号，表示所有字段
  UNBOUND_FIELD,        ///< 未绑定的字段，需要在resolver阶段解析为FieldExpr
  UNBOUND_AGGREGATION,  ///< 未绑定的聚合函数，需要在resolver阶段解析为AggregateExpr

  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  AGGREGATION,  ///< 聚合运算
  VECTOROPERATION,  ///<向量运算操作
  SELECT,        ///< 子查询
  VALUE_LIST     
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 *
 * TODO 区分unbound和bound的表达式
 */
class Expression
{
public:
  Expression()          = default;
  virtual ~Expression() = default;

  RC recursion(std::unique_ptr<Expression>& expr, 
    const std::function<RC(std::unique_ptr<Expression>&)>& func);

  /**
   * @brief 判断两个表达式是否相等
   */
  virtual bool equal(const Expression &other) const { return false; }
  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  virtual RC get_value_set(const Tuple &tuple, vector<Value> &value_list) const {return RC::UNIMPLEMENTED;}

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLEMENTED; }

  /**
   * @brief 从 `chunk` 中获取表达式的计算结果 `column`
   */
  virtual RC get_column(Chunk &chunk, Column &column) { return RC::UNIMPLEMENTED; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式值的长度
   */
  virtual int value_length() const { return -1; }

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual const char *name() const { return name_.c_str(); }
  virtual void        set_name(std::string name) { name_ = name; }

  /**
   * @brief 表达式的别名
   */
  virtual const string   &alias() const { return alias_; }
  virtual void        set_alias(std::string alias) { alias_ = alias; }

  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   */
  virtual int  pos() const { return pos_; }
  virtual void set_pos(int pos) { pos_ = pos; }

  /**
   * @brief 用于 ComparisonExpr 获得比较结果 `select`。
   */
  virtual RC eval(Chunk &chunk, std::vector<uint8_t> &select) { return RC::UNIMPLEMENTED; }

  virtual unique_ptr<Expression> deep_copy(){ return nullptr; };

protected:
  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   * @details 当 pos_ = -1 时表示下层算子没有在返回的 chunk 中计算出该表达式的计算结果，
   * 当 pos_ >= 0时表示在下层算子中已经计算出该表达式的值（比如聚合表达式），且该表达式对应的结果位于
   * chunk 中 下标为 pos_ 的列中。
   */
  int pos_ = -1;

private:
  std::string name_;
  std::string alias_;
};

class StarExpr : public Expression
{
public:
  StarExpr() : table_name_() {}
  StarExpr(const char *table_name) : table_name_(table_name) {}
  virtual ~StarExpr() = default;

  ExprType type() const override { return ExprType::STAR; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::UNIMPLEMENTED; }  // 不需要实现

  const char *table_name() const { return table_name_.c_str(); }

private:
  std::string table_name_;
};

class UnboundFieldExpr : public Expression
{
public:
  UnboundFieldExpr(const std::string &table_name, const std::string &field_name)
      : table_name_(table_name), field_name_(field_name)
  {}

  virtual ~UnboundFieldExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_FIELD; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }

  unique_ptr<Expression> deep_copy() override
  {
    return unique_ptr<Expression>(new UnboundFieldExpr(table_name_, field_name_));
  }


private:
  std::string table_name_;
  std::string field_name_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const BaseTable *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Field &field) : field_(field) {}

  virtual ~FieldExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }
  int      value_length() const override { return field_.meta()->len(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }

  void        set_table_alias(const char * table_alias) { table_alias_ = table_alias; }
  const char *table_name() const { return field_.table_name(); }
  const BaseTable   *table() const { return field_.table(); }
  const char *field_name() const { return field_.field_name(); }
  const string     &table_alias() const { return table_alias_; }

  RC get_column(Chunk &chunk, Column &column) override;

  RC get_value(const Tuple &tuple, Value &value) const override;

  unique_ptr<Expression> deep_copy() override
  {
    unique_ptr<Expression> ret(new FieldExpr(field_));
    if(!table_alias_.empty())
      static_cast<FieldExpr*>(ret.get())->set_table_alias(table_alias_.c_str());
    return ret;
  }

private:
  Field field_;
  std::string table_alias_;
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  bool equal(const Expression &other) const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_column(Chunk &chunk, Column &column) override;
  RC try_get_value(Value &value) const override
  {
    value = value_;
    return RC::SUCCESS;
  }
  
  RC get_value_set(const Tuple &tuple, vector<Value> &value_list)const override
  {
    Value value;
    get_value(value);
    value_list.emplace_back(std::move(value));
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }
  AttrType value_type() const override { return value_.attr_type(); }
  int      value_length() const override { return value_.length(); }

  void         get_value(Value &value) const { value = value_; }
  const Value &get_value() const { return value_; }

  unique_ptr<Expression> deep_copy() override
  {
    return unique_ptr<Expression>(new ValueExpr(value_));
  }

private:
  Value value_;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_value_set(const Tuple &tuple, vector<Value> &value_list)const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

  unique_ptr<Expression> deep_copy() override
  {
    return unique_ptr<Expression>(new CastExpr(move(child_->deep_copy()), cast_type_));
  }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;      ///< 从这个表达式转换
  AttrType                    cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }
  RC       get_value(const Tuple &tuple, Value &value) const override;
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  CompOp   comp() const { return comp_; }

  /**
   * @brief 根据 ComparisonExpr 获得 `select` 结果。
   * select 的长度与chunk 的行数相同，表示每一行在ComparisonExpr 计算后是否会被输出。
   */
  RC eval(Chunk &chunk, std::vector<uint8_t> &select) override;

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

  RC like_value(const Tuple &tuple, bool &result) const;

  RC value_exists(const Tuple &tuple, bool &result) const;

  RC value_in(const Tuple &tuple, bool &result) const;
  RC value_not_in(const Tuple &tuple, bool &result) const;

  RC value_is_null(const Tuple &tuple, bool &result) const;

  template <typename T>
  RC compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const;

  unique_ptr<Expression> deep_copy() override
  {
    return unique_ptr<Expression>(new ComparisonExpr(comp_, move(left_->deep_copy()), move(right_->deep_copy())));
  }

private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
  std::regex                  pattern;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression
{
public:
  enum class Type
  {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  RC       get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type                                     conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression
{
public:
  enum class Type
  {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  bool     equal(const Expression &other) const override;
  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;
  int      value_length() const override
  {
    if (!right_) {
      return left_->value_length();
    }
    return 4;  // sizeof(float) or sizeof(int)
  };

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  unique_ptr<Expression> deep_copy() override
  {
    return unique_ptr<Expression>(new ArithmeticExpr(arithmetic_type_, move(left_->deep_copy()), move(right_->deep_copy())));
  }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

  RC calc_column(const Column &left_column, const Column &right_column, Column &column) const;

  template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
  RC execute_calc(const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const;

private:
  Type                        arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 向量运算表达式
 * @ingroup Expression
 */
class VectorOperationExpr : public Expression
{
public:
  enum class Type
  {
    L2_DISTANCE,
    COSINE_DISTANCE,
    INNER_PRODUCT,
  };
public:
  VectorOperationExpr(Type type, Expression *left, Expression *right);
  VectorOperationExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~VectorOperationExpr() = default;

  bool     equal(const Expression &other) const override;
  ExprType type() const override { return ExprType::VECTOROPERATION; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  Type operation_type() const { return operation_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;
  
private:
  Type                        operation_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

class UnboundAggregateExpr : public Expression
{
public:
  UnboundAggregateExpr(const char *aggregate_name, Expression *child);
  virtual ~UnboundAggregateExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_AGGREGATION; }

  const char *aggregate_name() const { return aggregate_name_.c_str(); }

  std::unique_ptr<Expression> &child() { return child_; }

  RC       get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }
  AttrType value_type() const override { return child_->value_type(); }

  unique_ptr<Expression> deep_copy() override
  {
    return unique_ptr<Expression>(new UnboundAggregateExpr(aggregate_name_.c_str(), child_->deep_copy().release()));
  }

private:
  std::string                 aggregate_name_;
  std::unique_ptr<Expression> child_;
};

class AggregateExpr : public Expression
{
public:
  enum class Type
  {
    COUNT,
    SUM,
    AVG,
    MAX,
    MIN,
  };

public:
  AggregateExpr(Type type, Expression *child);
  AggregateExpr(Type type, std::unique_ptr<Expression> child);
  virtual ~AggregateExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::AGGREGATION; }

  AttrType value_type() const override { return child_->value_type(); }
  int      value_length() const override { return child_->value_length(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  Type aggregate_type() const { return aggregate_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

  const std::unique_ptr<Expression> &child() const { return child_; }

  std::unique_ptr<Aggregator> create_aggregator() const;

  unique_ptr<Expression> deep_copy() override
  {
    return unique_ptr<Expression>(new AggregateExpr(aggregate_type_, move(child_->deep_copy())));
  }

public:
  static RC type_from_string(const char *type_str, Type &type);

private:
  Type                        aggregate_type_;
  std::unique_ptr<Expression> child_;
};

/**
 * @brief 子查询表达式
 * @ingroup Expression
 */
class SelectExpr : public Expression
{
public:
  using tables_t = std::unordered_map<std::string, std::pair<BaseTable*, size_t>>;

  SelectExpr() = default;
  SelectExpr(ParsedSqlNode* sql_node);

  virtual ~SelectExpr();

  ExprType type() const override { return ExprType::SELECT; }
  AttrType value_type() const override { return value_type_;}

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_value_set(const Tuple &tuple, vector<Value> &value_list)const override;
  RC try_get_value(Value &value) const { 
    if(values_ != nullptr){
      if(values_->size() == 0 || values_->at(0).size() == 0){
        value.set_null();
        return RC::SUCCESS;
      }
      if(values_->size() > 1 || values_->at(0).size() > 1)
        return RC::MUTI_TUPLE;
      value = values_->at(0)[0];
      return RC::SUCCESS;
    }
    return RC::UNIMPLEMENTED;
  }

  RC pretreatment();

  RC logical_generate();
  RC physical_generate();
  RC create_stmt(Db *db, vector<vector<uint32_t>>& depends, vector<SelectExpr*>& select_exprs, 
    tables_t& table_map, int fa);

  RC next_tuple(Tuple *&tuple, Tuple *upper_tuple = nullptr) const;

  void set_trx(Trx *trx) { trx_ = trx; };

private:
  AttrType value_type_ = AttrType::UNDEFINED;
  Stmt*     stmt_ = nullptr;

  unique_ptr<LogicalOperator> logical_operator_;
  unique_ptr<PhysicalOperator> physical_operator_;
  unique_ptr<vector<vector<Value>>> values_;
  ParsedSqlNode*  sql_node_ = nullptr;
  Trx*      trx_ = nullptr;
};

class ValueListExpr : public Expression
{
public:
  ValueListExpr() = default;
  explicit ValueListExpr(std::vector<unique_ptr<Expression>>& exprs) {
    exprs_.swap(exprs);
  }

  virtual ~ValueListExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_value_set(const Tuple &tuple, vector<Value> &value_list)const override;

  ExprType type() const override { return ExprType::VALUE_LIST; }
  AttrType value_type() const override { return exprs_[0]->value_type(); }

private:
   std::vector<std::unique_ptr<Expression>> exprs_;
};