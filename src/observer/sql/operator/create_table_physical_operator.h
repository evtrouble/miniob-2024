/* Copyright (c) OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/12/26.
//

#pragma once

#include "sql/operator/physical_operator.h"

/**
 * @brief 逻辑算子，用于执行create_table_select语句
 * @ingroup LogicalOperator
 */
class CreateTablePhysicalOperator : public PhysicalOperator
{
public:
    CreateTablePhysicalOperator(Db *db, const string &&table_name, const std::vector<AttrInfoSqlNode> &&attr_infos, 
        const StorageFormat storage_format);
     virtual ~CreateTablePhysicalOperator() = default;

    PhysicalOperatorType type() const override { return PhysicalOperatorType::CREATE_TABLE; }

    RC open(Trx *trx) override;
    RC next() override;
    RC close() override;

    Tuple *current_tuple() override { return nullptr; }

private:
    Db                                 *db_;
    const string                        table_name_;
    const std::vector<AttrInfoSqlNode>  attr_infos_;
    Trx                *trx_   = nullptr;
    const StorageFormat                 storage_format_;
};
