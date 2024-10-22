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
// Created by WangYunlai on 2022/11/17.
//

#pragma once

#include <memory>
#include <string>

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"

class Session;

struct SelectAnalyzer
{
  vector<bool>                      instack;//是否在栈内
  std::stack<int>                   st;
  vector<int>                       dfn;
  vector<int>                       low;
  int                               cnt = 0;
  vector<int>                       scc;
  unique_ptr<vector<SelectExpr*>> select_exprs_;           ///< 子查询表达式
  unique_ptr<vector<vector<uint32_t>>> depends_;         ///< 依赖关系

  void targan(int u = 0)
  {
    cnt++;
    dfn[u] = low[u] = cnt;
    instack[u] = true;
    st.push(u);
    for (size_t i = 0; i < depends_->at(u).size(); i++)
    {
        int v = depends_->at(u)[i];
        if (dfn[v] == 0)
        {
          targan(v);
          low[u] = std::min(low[u], low[v]);
        }
        else if (instack[v])low[u] = std::min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        int temp = -1;
        scc.push_back(INT32_MAX);
        auto id = scc.size() - 1;
        do{
            temp = st.top();
            st.pop();
            instack[temp] = false;
            scc[id] = std::min(scc[id], temp);
        } while (temp != u);
    }
  }

  RC pretreatment()
  {
    if(depends_->size() == 0 || depends_->size() == 1)return RC::SUCCESS;
    if(scc.size() == 0){
      auto size = depends_->size();
      dfn.resize(size);
      instack.resize(size);
      low.resize(size);

      targan();
      std::sort(scc.begin(), scc.end());
    }

    RC rc = RC::SUCCESS;

    for(int id = scc.size() - 1; id; id--){
      rc = select_exprs_->at(scc[id] - 1)->pretreatment();
      if(rc != RC::SUCCESS)return rc;
    }
    return rc;
  }
};

/**
 * @brief SQL执行结果
 * @details
 * 如果当前SQL生成了执行计划，那么在返回客户端时，调用执行计划返回结果。
 * 否则返回的结果就是当前SQL的执行结果，比如DDL语句，通过return_code和state_string来描述。
 * 如果出现了一些错误，也可以通过return_code和state_string来获取信息。
 */
class SqlResult
{
public:
  SqlResult(Session *session);
  ~SqlResult() {}

  void set_tuple_schema(const TupleSchema &schema);
  void set_return_code(RC rc) { return_code_ = rc; }
  void set_state_string(const std::string &state_string) { state_string_ = state_string; }

  void set_operator(std::unique_ptr<PhysicalOperator> oper);
  void set_depends(unique_ptr<vector<vector<uint32_t>>> depends);
  void set_exprs(unique_ptr<vector<SelectExpr*>> select_exprs);

  bool               has_operator() const { return operator_ != nullptr; }
  const TupleSchema &tuple_schema() const { return tuple_schema_; }
  RC                 return_code() const { return return_code_; }
  const std::string &state_string() const { return state_string_; }

  RC open();
  RC close();
  RC next_tuple(Tuple *&tuple);
  RC next_chunk(Chunk &chunk);

private:
  Session                          *session_ = nullptr;  ///< 当前所属会话
  std::unique_ptr<PhysicalOperator> operator_;           ///< 执行计划
  TupleSchema                       tuple_schema_;       ///< 返回的表头信息。可能有也可能没有
  RC                                return_code_ = RC::SUCCESS;
  std::string                       state_string_;
  SelectAnalyzer                    analyzer_;
};
