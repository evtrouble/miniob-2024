/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>

#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/vector_index_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/create_table_logical_operator.h"
#include "sql/operator/limit_logical_operator.h"

#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/stmt.h"

#include "sql/expr/expression_iterator.h"
#include "storage/index/index.h"
#include "storage/index/ivfflat_index.h"

using namespace std;
using namespace common;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CREATE_TABLE: {
      CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);

      rc = create_plan(create_table_stmt, logical_operator);
    } break;

    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);

      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLEMENTED;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(CreateTableStmt *create_table_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  std::unique_ptr<LogicalOperator> select_oper;
  Stmt *create_select_stmt =  create_table_stmt->select_stmt().get();
  if(create_select_stmt == nullptr)return RC::UNIMPLEMENTED;
  if (nullptr != create_select_stmt) {
    SelectStmt *select_stmt = static_cast<SelectStmt*>(create_select_stmt);
    rc = create_plan(select_stmt, select_oper);
    if (RC::SUCCESS != rc) {
      LOG_WARN("failed to create sub select logical plan, r=%s", strrc(rc));
      return rc;
    }
  }

  auto& table_name = create_table_stmt->table_name();
  auto& attr_infos = create_table_stmt->attr_infos();
  logical_operator = std::unique_ptr<LogicalOperator>(new CreateTableLogicalOperator(
      create_table_stmt->db(), move(table_name), move(attr_infos), create_table_stmt->storage_format())); 
  if (select_oper) {
    logical_operator->add_child(std::move(select_oper));
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  if(OB_SUCC(create_vector_plan(select_stmt, logical_operator)))return RC::SUCCESS;

  unique_ptr<LogicalOperator> *last_oper = nullptr;

  unique_ptr<LogicalOperator> table_oper(nullptr);
  last_oper = &table_oper;

  auto &tables = select_stmt->tables();
  for (auto& [table, alias] : tables) {    
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY, alias));
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }

  unique_ptr<LogicalOperator> having_oper;
  if (!select_stmt->having_list().empty()) {
    if(select_stmt->and_or()){
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::OR, select_stmt->having_list()));
      having_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }else{
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, select_stmt->having_list()));
      having_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }

    if (*last_oper) {
      having_oper->add_child(std::move(*last_oper));
    }
    last_oper = &having_oper;
  }

  auto& order_by = select_stmt->order_by();
  unique_ptr<LogicalOperator> order_by_oper;
  if(order_by.size()){
    order_by_oper = make_unique<OrderByLogicalOperator>(std::move(order_by), std::move(select_stmt->is_asc()), select_stmt->limit());
    if (*last_oper) {
      order_by_oper->add_child(std::move(*last_oper));
    }
    
    last_oper = &order_by_oper;
  }

  unique_ptr<LogicalOperator> limit_oper;
  if(select_stmt->limit() > 0){
    limit_oper = make_unique<LimitLogicalOperator>();
    if (*last_oper) {
      limit_oper->add_child(std::move(*last_oper));
    }
    
    last_oper = &limit_oper;
  }

  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()), tables.size() > 1);
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC                                  rc = RC::SUCCESS;
  std::vector<unique_ptr<Expression>> cmp_exprs;
  auto &filter_units = filter_stmt->filter_units();
  for (auto& expr : filter_units) {
    ComparisonExpr* cmp_expr = static_cast<ComparisonExpr*>(expr.get());
    auto& left  = cmp_expr->left();
    auto& right = cmp_expr->right(); 

    if(left->value_type() == AttrType::NULLS || right->value_type() == AttrType::NULLS){
      cmp_exprs.emplace_back(std::move(expr));
      continue;
    }

    if (left->value_type() != right->value_type()) {
      auto left_to_right_cost = implicit_cast_cost(left->value_type(), right->value_type());
      auto right_to_left_cost = implicit_cast_cost(right->value_type(), left->value_type());
      auto left_to_float_cost = implicit_cast_cost(left->value_type(), AttrType::FLOATS);
      auto right_to_float_cost = implicit_cast_cost(right->value_type(), AttrType::FLOATS);

      if(left_to_float_cost != INT32_MAX && right_to_float_cost != INT32_MAX && 
          left_to_float_cost + right_to_float_cost < min(left_to_right_cost, right_to_left_cost)){
        if(left->value_type() != AttrType::FLOATS){
          ExprType left_type = left->type();
          auto cast_expr = make_unique<CastExpr>(std::move(left), AttrType::FLOATS);
          if (left_type == ExprType::VALUE) {
            Value left_val;
            if (OB_FAIL(rc = cast_expr->try_get_value(left_val)))
            {
              LOG_WARN("failed to get value from left child", strrc(rc));
              return rc;
            }
            left = make_unique<ValueExpr>(left_val);
          } else {
            left = std::move(cast_expr);
          }
        }
        if(right->value_type() != AttrType::FLOATS){
          ExprType right_type = right->type();
          auto cast_expr = make_unique<CastExpr>(std::move(right), AttrType::FLOATS);
          if (right_type == ExprType::VALUE) {
            Value right_val;
            if (OB_FAIL(rc = cast_expr->try_get_value(right_val)))
            {
              LOG_WARN("failed to get value from right child", strrc(rc));
              return rc;
            }
            right = make_unique<ValueExpr>(right_val);
          } else {
            right = std::move(cast_expr);
          }
        }
      }
      else if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
        ExprType left_type = left->type();
        auto cast_expr = make_unique<CastExpr>(std::move(left), right->value_type());
        if (left_type == ExprType::VALUE) {
          Value left_val;
          if (OB_FAIL(rc = cast_expr->try_get_value(left_val)))
          {
            LOG_WARN("failed to get value from left child", strrc(rc));
            return rc;
          }
          left = make_unique<ValueExpr>(left_val);
        } else {
          left = std::move(cast_expr);
        }
      } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
        ExprType right_type = right->type();
        auto cast_expr = make_unique<CastExpr>(std::move(right), left->value_type());
        if (right_type == ExprType::VALUE) {
          Value right_val;
          if (OB_FAIL(rc = cast_expr->try_get_value(right_val)))
          {
            LOG_WARN("failed to get value from right child", strrc(rc));
            return rc;
          }
          right = make_unique<ValueExpr>(right_val);
        } else {
          right = std::move(cast_expr);
        }

      } else {
        rc = RC::UNSUPPORTED;
        LOG_WARN("unsupported cast from %s to %s", attr_type_to_string(left->value_type()), attr_type_to_string(right->value_type()));
        return rc;
      }
    }

    ComparisonExpr *new_cmp_expr = new ComparisonExpr(cmp_expr->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(new_cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    if(filter_stmt->and_or()){
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::OR, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }else{
      unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
      predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }
  }

  logical_operator = std::move(predicate_oper);
  return rc;
}

int LogicalPlanGenerator::implicit_cast_cost(AttrType from, AttrType to)
{
  if (from == to) {
    return 0;
  }
  return DataType::type_instance(from)->cast_cost(to);
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  BaseTable        *table = insert_stmt->table();

  auto values_set = insert_stmt->values_set();
  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, move(values_set));
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  BaseTable                  *table       = update_stmt->table();
  FilterStmt                 *filter_stmt = update_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  const std::vector<const FieldMeta *>& fields = update_stmt->fields();
  vector<unique_ptr<Expression>>& values = update_stmt->values();

  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, move(fields), move(values)));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  BaseTable                  *table       = delete_stmt->table();
  FilterStmt                 *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_group_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  vector<unique_ptr<Expression>> &group_by_expressions = select_stmt->group_by();
  vector<unique_ptr<Expression>> &having_expressions = select_stmt->having_list();
  vector<Expression *> aggregate_expressions;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  function<RC(std::unique_ptr<Expression>&)> collector = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if(expr == nullptr)return rc;
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression>&)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if(expr == nullptr)return rc;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(i);
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

 bool found_unbound_column = false;
  function<RC(std::unique_ptr<Expression>&)> find_unbound_column = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if(expr == nullptr)return rc;
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    }else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };
  

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }
  for (unique_ptr<Expression> &expression : having_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }
  for (unique_ptr<Expression> &expression : having_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }
  for (unique_ptr<Expression> &expression : having_expressions) {
    collector(expression);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  if (found_unbound_column) {
    LOG_WARN("column must appear in the GROUP BY clause or must be part of an aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper = make_unique<GroupByLogicalOperator>(std::move(group_by_expressions),
                                                           std::move(aggregate_expressions));
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_vector_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  auto &tables = select_stmt->tables();
  auto& order_by = select_stmt->order_by();

  if(tables.size() != 1 || order_by.size() != 1 || order_by[0]->type() != ExprType::VECTOROPERATION
    || !select_stmt->is_asc()[0])
    return RC::INVALID_ARGUMENT;
  
  VectorOperationExpr* vector_expr = static_cast<VectorOperationExpr*>(order_by[0].get());
  Table *table = static_cast<Table*>(tables[0].first);

  unique_ptr<Expression> &left_expr  = vector_expr->left();
  unique_ptr<Expression> &right_expr = vector_expr->right();

  // 左右比较的一边最少是一个值
  if (left_expr->type() != ExprType::VALUE && right_expr->type() != ExprType::VALUE) 
    return RC::INVALID_ARGUMENT;

  FieldExpr *field_expr = nullptr;
  ValueExpr *value_expr = nullptr;
  if (left_expr->type() == ExprType::FIELD) {
    ASSERT(right_expr->type() == ExprType::VALUE, "right expr should be a value expr while left is field expr");
    field_expr = static_cast<FieldExpr *>(left_expr.get());
    value_expr = static_cast<ValueExpr *>(right_expr.get());
  } else if (right_expr->type() == ExprType::FIELD) {
    ASSERT(left_expr->type() == ExprType::VALUE, "left expr should be a value expr while right is a field expr");
    field_expr = static_cast<FieldExpr *>(right_expr.get());
    value_expr = static_cast<ValueExpr *>(left_expr.get());
  }

  if (field_expr == nullptr)return RC::INVALID_ARGUMENT;

  Value value;
  ASSERT(value_expr != nullptr, "got an index but value expr is null ?");
  if (value_expr->try_get_value(value) != RC::SUCCESS || value.attr_type() != AttrType::VECTORS)
    return RC::INVALID_ARGUMENT;

  Index* index = table->find_index_by_field(field_expr->field().field_name());
  if(index == nullptr || !index->is_vector_index())return RC::INVALID_ARGUMENT;

  if(static_cast<IvfflatIndex*>(index)->type() != vector_expr->operation_type())
    return RC::INVALID_ARGUMENT;
  
  unique_ptr<LogicalOperator> *last_oper = nullptr;
  unique_ptr<LogicalOperator> table_oper(new VectorIndexGetLogicalOperator(index, move(value), table, select_stmt->limit()));
  last_oper = &table_oper;

  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()), tables.size() > 1);
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}