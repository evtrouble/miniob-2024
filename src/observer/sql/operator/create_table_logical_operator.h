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

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行create_table_select语句
 * @ingroup LogicalOperator
 */
class CreateTableLogicalOperator : public LogicalOperator
{
public:
    CreateTableLogicalOperator(Db *db, const string &&table_name, const std::vector<AttrInfoSqlNode> &&attr_infos,
        const StorageFormat storage_format);
    virtual ~CreateTableLogicalOperator() = default;

    LogicalOperatorType type() const override { return LogicalOperatorType::CREATE_TABLE; }
    Db                                 *db() { return db_; }
    const string                        table_name() const { return table_name_; }
    const std::vector<AttrInfoSqlNode>  attr_infos() const { return attr_infos_; }
    const StorageFormat                 storage_format() const { return storage_format_; }

private:
    Db                                 *db_;
    const string                        table_name_;
    const std::vector<AttrInfoSqlNode>  attr_infos_;
    StorageFormat                storage_format_;
};
