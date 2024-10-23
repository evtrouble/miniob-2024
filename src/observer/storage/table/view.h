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
            std::vector<Field> &map_fields, 
            unique_ptr<Stmt> &select_stmt, SelectAnalyzer &analyzer);

public:
  virtual int32_t table_id() const { return table_meta_.table_id(); }
  virtual const char *name() const { return table_meta_.name(); }
  virtual const TableMeta &table_meta() const { return table_meta_; }
  
  Db *db() const { return db_; }
  const std::vector<Field> &map_fields() const { return map_fields_; }
  unique_ptr<Stmt> &select_stmt() { return select_stmt_; }
  SelectAnalyzer   &analyzer() { return analyzer_; }

  void set_db(Db *db) { db_ = db; }

private:
  Db *db_;
  std::string base_dir_;
  TableMeta   table_meta_;
  std::vector<Field> map_fields_;       // view列映射的原始表中的列，可写view中所有col映射的都是Field，只读view不需要用到这个映射
  unique_ptr<Stmt> select_stmt_;
  SelectAnalyzer  analyzer_;
};