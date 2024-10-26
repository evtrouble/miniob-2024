#pragma once

#include <string>
#include <vector>
#include "storage/table/base_table.h"
#include "storage/table/table_meta.h"
#include "sql/executor/sql_result.h"
#include "sql/stmt/stmt.h"

class Db;
class Field;
class FieldMeta;
class TableMeta;

class View : public BaseTable
{
public:
  View() = default;
  virtual ~View() = default;

  RC create(int32_t table_id, 
            const char *path,       // .view文件路径、名称
            const char *name,       // view_name
            const char *base_dir,   // db/sys
            span<const AttrInfoSqlNode> attributes, 
            std::vector<unique_ptr<Expression>> &map_exprs, 
            unique_ptr<Stmt> &select_stmt, SelectAnalyzer &analyzer, bool allow_write);

public:
  virtual int32_t table_id() const { return table_meta_.table_id(); }
  virtual const char *name() const { return table_meta_.name(); }
  virtual const TableMeta &table_meta() const { return table_meta_; }
  
  Db *db() const { return db_; }
  const std::vector<unique_ptr<Expression>> &map_exprs() const { return map_exprs_; }
  unique_ptr<PhysicalOperator> &child() { return physical_oper_; }
  SelectAnalyzer   &analyzer() { return analyzer_; }
  bool              allow_write() const { return allow_write_; }

  void set_db(Db *db) { db_ = db; }
  Expression* find_expr(const char *name);

  RC init();

private:
  Db *db_;
  std::string base_dir_;
  TableMeta   table_meta_;
  std::vector<unique_ptr<Expression>> map_exprs_;       // view列映射的原始表中的表达式
  unique_ptr<Stmt> select_stmt_;
  unique_ptr<PhysicalOperator> physical_oper_;
  SelectAnalyzer  analyzer_;
  bool            allow_write_ = false;
};