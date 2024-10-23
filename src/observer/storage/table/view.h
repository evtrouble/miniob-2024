#pragma once

#include <string>
#include <vector>
#include "storage/table/base_table.h"
#include "storage/table/table_meta.h"
#include "sql/executor/sql_result.h"

class Db;
class Field;
class FieldMeta;
class TableMeta;
class SelectStmt;

class View : public BaseTable
{
public:
  View() = default;
  virtual ~View() = default;

  RC create(Db *db, int32_t table_id, 
            const char *path,       // .view文件路径、名称
            const char *name,       // view_name
            const char *base_dir,   // db/sys
            const std::vector<AttrInfoSqlNode> &attr_infos, 
            std::vector<Field> &map_fields, 
            SelectSqlNode &select_sql, SelectAnalyzer &analyzer);
  RC open();
  RC drop();
  void set_db(Db *db) { db_ = db; }

public:
  virtual int32_t table_id() const { return table_meta_.table_id(); }
  virtual const char *name() const { return table_meta_.name(); }
  virtual const TableMeta &table_meta() const { return table_meta_; }
  
  Db *db() const { return db_; }
  const std::vector<Field> &map_fields() const { return map_fields_; }
  SelectSqlNode select_sql() const { return select_sql_; }

private:
  int get_serialize_size();
  RC serialize(std::fstream &fs);
  RC deserialize();

private:
  Db *db_;
  std::string base_dir_;
  TableMeta   table_meta_;
  std::vector<Field> map_fields_;       // view列映射的原始表中的列，可写view中所有col映射的都是Field，只读view不需要用到这个映射
  SelectSqlNode select_sql_;
  SelectAnalyzer  analyzer_;
};