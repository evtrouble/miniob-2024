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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/limit_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/table/table.h"

using namespace std;

RC LimitPhysicalOperator::open(Trx *trx)
{
  LOG_INFO("open limit operator");
  return children_[0]->open(trx);
}

RC LimitPhysicalOperator::next()
{
    return children_[0]->next();
}

RC LimitPhysicalOperator::next(Tuple *upper_tuple)
{
  return children_[0]->next(upper_tuple);
}

RC LimitPhysicalOperator::close() { LOG_INFO("close limit operator"); return children_[0]->close(); }

Tuple *LimitPhysicalOperator::current_tuple()
{
  return children_[0]->current_tuple();
}