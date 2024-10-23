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
// Created on 2024/10/23.
//

#include "sql/executor/create_view_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/create_view_stmt.h"
#include "storage/db/db.h"

RC CreateViewExecutor::execute(SQLStageEvent *sql_event)
{
    RC rc = RC::SUCCESS;
    Stmt *stmt = sql_event->stmt();
    Session *session = sql_event->session_event()->session();
    ASSERT(stmt->type() == StmtType::CREATE_VIEW, 
            "create view executor can not run this command: %d", static_cast<int>(stmt->type()));

    CreateViewStmt *create_view_stmt = static_cast<CreateViewStmt*>(stmt);

    rc = session->get_current_db()->create_view(create_view_stmt->view_name().c_str(), 
              create_view_stmt->attr_infos(), create_view_stmt->map_fields(), create_view_stmt->select_stmt(), 
              create_view_stmt->analyzer());
    if (RC::SUCCESS != rc) {
      LOG_WARN("failed to create view %s, rc=%s", create_view_stmt->view_name().c_str(), strrc(rc));
    }

    return rc;
}