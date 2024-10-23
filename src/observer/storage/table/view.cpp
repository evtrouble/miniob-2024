#include <fstream>
#include <fcntl.h>
#include <common/lang/string.h>

#include "json/json.h"
#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "storage/table/view.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "event/sql_debug.h"
#include "storage/trx/trx.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"

RC View::create(int32_t table_id, 
            const char *path,       // .view文件路径、名称
            const char *name,       // view_name
            const char *base_dir,   // db/sys
            span<const AttrInfoSqlNode> attr_infos, 
            std::vector<Field> &map_fields, 
            unique_ptr<Stmt> &select_stmt, SelectAnalyzer &analyzer, bool allow_write)
{
  RC rc = RC::SUCCESS;
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, view_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }
  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  if (attr_infos.size() <= 0) {
    LOG_WARN("Invalid arguments. view_name=%s, attribute_count=%d", name, attr_infos.size());
    return RC::INVALID_ARGUMENT;
  }
  
  LOG_INFO("Begin to create view %s:%s", base_dir, name);
  set_view_type();
  allow_write_ = allow_write;

  std::swap(select_stmt_, select_stmt);
  std::swap(analyzer_, analyzer);
  map_fields_.swap(map_fields);

  const vector<FieldMeta> *trx_fields = db_->trx_kit().trx_fields();
  if ((rc = table_meta_.init(table_id, name, trx_fields, attr_infos)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  //Todo 视图持久化

  // 使用 name.view记录一个视图的元数据，判断视图文件是否已经存在
//   int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
//   if (fd < 0) {
//     if (EEXIST == errno) {
//       LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
//       return RC::SCHEMA_TABLE_EXIST;
//     }
//     LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
//     return RC::IOERR_OPEN;
//   }
//   close(fd);

//   // 记录元数据到文件中
//   std::fstream fs;
//   fs.open(path, std::ios_base::out | std::ios_base::binary);
//   if (!fs.is_open()) {
//     LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
//     return RC::IOERR_OPEN;
//   }
//   table_meta_.serialize(fs);
//   fs.close();

  return rc;
}

Field* View::find_field(const char *name)
{
  int id = table_meta_.field_id(name);
  if(id < table_meta_.sys_field_num())return nullptr;
  return &map_fields_[id - table_meta_.sys_field_num()];
}

RC View::init()
{
  if(physical_oper_ != nullptr)return RC::SUCCESS;

  RC rc = RC::SUCCESS;
  LogicalPlanGenerator logical_plan_generator;
  for(int id = analyzer_.select_exprs_.size() - 1; id >= 0; id--){
    rc = analyzer_.select_exprs_[id]->logical_generate();
  }
  if (rc != RC::SUCCESS) return rc;

  std::unique_ptr<LogicalOperator> logical_oper;
  rc = logical_plan_generator.create(select_stmt_.get(), logical_oper);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to create select_logical_oper when view_scan open, rc=%s", strrc(rc));
    return rc;
  }

  PhysicalPlanGenerator physical_plan_generator;
  rc = physical_plan_generator.create(*logical_oper, physical_oper_);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to create select_physical_oper when view_scan open, rc=%s", strrc(rc));
    return rc;
  }
  for(auto& select_expr : analyzer_.select_exprs_){
    rc = select_expr->physical_generate();
  }
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to create select_physical_oper when view_scan open, rc=%s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}