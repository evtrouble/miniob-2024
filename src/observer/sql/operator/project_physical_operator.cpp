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
// Created by WangYunlai on 2022/07/01.
//

#include "sql/operator/project_physical_operator.h"
#include "common/log/log.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

using namespace std;

ProjectPhysicalOperator::ProjectPhysicalOperator(vector<unique_ptr<Expression>> &&expressions, bool show_table_name)
  : expressions_(std::move(expressions)), tuple_(expressions_), show_table_name_(show_table_name)
{
}

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  RC rc = children_[0]->next();
  if(rc == RC::NULL_RECORD){
    for (const unique_ptr<Expression> &expression : expressions_) {
      if(expression->type() != ExprType::AGGREGATION){
        return RC::RECORD_EOF;
      }
    }
    rc = RC::SUCCESS;
  }
  return rc;
}

RC ProjectPhysicalOperator::next(Tuple *upper_tuple)
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  RC rc = children_[0]->next(upper_tuple);
  if(rc == RC::NULL_RECORD){
    for (const unique_ptr<Expression> &expression : expressions_) {
      if(expression->type() != ExprType::AGGREGATION){
        return rc;
      }
    }
    rc = RC::SUCCESS;
  }
  return rc;
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  LOG_INFO("close project operator");
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

RC ProjectPhysicalOperator::tuple_schema(TupleSchema &schema) const
{
  for (const unique_ptr<Expression> &expression : expressions_) {
    const string& alias = expression->alias();
    if(show_table_name_ && expression->type() == ExprType::FIELD){
      FieldExpr* field_expr = static_cast<FieldExpr*>(expression.get());
      const string& table_alias = field_expr->table_alias();

      schema.append_cell(table_alias.empty() ? field_expr->table_name() : table_alias.c_str(),
        alias.empty() ? expression->name() : alias.c_str());
      schema.append_cell(field_expr->table_name(), expression->name());
    } else schema.append_cell(alias.empty() ? expression->name() : alias.c_str());
  }
  return RC::SUCCESS;
}

Tuple *ProjectPhysicalOperator::current_raw_tuple() 
{
  return children_[0]->current_raw_tuple();
}