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
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include <vector>
#include <unordered_map>

#include "sql/expr/expression.h"

class BinderContext
{
public:
using tables_t = std::unordered_map<std::string, std::pair<Table*, size_t>>;
  BinderContext()          = default;
  virtual ~BinderContext() = default;

  void add_table(std::string table_name, Table *table, size_t id = 0) 
  { 
    if(!query_tables_.count(table_name)) {
      auto temp = std::make_pair(table, id);
      query_tables_.insert({table_name, temp});
    }
  }

  void del_table(string table_name, size_t id = 0) {
    if(query_tables_.at(table_name).second == id){
      query_tables_.erase(table_name);
    }
  }

  Table *find_table(const char *table_name) const;
  size_t get_id(const char *table_name) const
  {
    if(query_tables_.count(table_name)) {
      return query_tables_.at(table_name).second;
    }
    return INT32_MAX;
  }

  const vector<Table *> query_tables() const { 
    vector<Table *> query_tables;
    for(auto& node : query_tables_){
      query_tables.emplace_back(node.second.first);
    }
    return query_tables;
  }

private:
  tables_t query_tables_;
};

/**
 * @brief 绑定表达式
 * @details 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder
{
public:
  ExpressionBinder(BinderContext &context) : context_(context) {}
  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

private:
  RC bind_star_expression(
      std::unique_ptr<Expression> &star_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_unbound_field_expression(
      std::unique_ptr<Expression> &unbound_field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_field_expression(
      std::unique_ptr<Expression> &field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_value_expression(
      std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_cast_expression(
      std::unique_ptr<Expression> &cast_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_comparison_expression(
      std::unique_ptr<Expression> &comparison_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_conjunction_expression(
      std::unique_ptr<Expression> &conjunction_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_arithmetic_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_aggregate_expression(
      std::unique_ptr<Expression> &aggregate_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_select_expression(
      std::unique_ptr<Expression> &select_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

private:
  BinderContext &context_;
};