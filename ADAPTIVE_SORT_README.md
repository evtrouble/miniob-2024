# 自适应内外排序实现

## 概述

本项目为 MiniOB 数据库的 `OrderByPhysicalOperator` 实现了自适应内外排序算法。该算法能够根据数据量自动选择最适合的排序策略，在保证性能的同时有效管理内存使用。

## 功能特性

### 1. 自适应策略选择
- **内存排序**: 当数据量较小时，直接在内存中进行快速排序
- **外排序**: 当数据量超过内存阈值时，自动切换到外排序算法

### 2. 外排序算法
- **分块排序**: 将大数据集分成多个小块，每个块在内存中排序后写入临时文件
- **多路归并**: 使用多路归并算法将多个已排序的临时文件合并为最终结果
- **内存优化**: 通过控制块大小来平衡内存使用和I/O效率
- **缓存优化**: 在切换到外排序时保留已读取的数据，避免重复读取
- **流式处理**: 支持真正的流式数据获取，避免将所有数据加载到内存

### 3. 内存管理
- **动态阈值**: 可配置的内存阈值（默认100MB）
- **内存估算**: 实时估算内存使用量，提前预测是否需要外排序
- **自动清理**: 自动清理临时文件，避免磁盘空间浪费

## 实现细节

### 核心类修改

#### OrderByPhysicalOperator.h
```cpp
class OrderByPhysicalOperator : public PhysicalOperator {
private:
    // 新增成员变量
    std::vector<std::string> temp_files_;           // 临时文件列表
    std::string current_temp_file_;                 // 当前临时文件
    std::ifstream current_file_stream_;             // 当前文件流
    size_t chunk_size_;                             // 每个块的大小
    size_t memory_threshold_;                       // 内存阈值（字节）
    
    // 新增方法
    RC adaptive_sort(Tuple *upper_tuple = nullptr);
    RC external_sort(Tuple *upper_tuple = nullptr);
    RC external_sort_with_cached_data(Tuple *upper_tuple, size_t cached_count);
    RC write_chunk_to_file(const std::vector<ValueListTuple>& chunk, const std::string& filename);
    RC read_chunk_from_file(std::vector<ValueListTuple>& chunk, const std::string& filename);
    RC read_chunk_from_stream(std::vector<ValueListTuple>& chunk, std::ifstream& file);
    RC merge_sorted_files(const std::vector<std::string>& input_files, const std::string& output_file);
    RC cleanup_temp_files();
    std::string create_temp_file();
    size_t estimate_memory_usage(size_t tuple_count);
    size_t estimate_tuple_size();
};
```

### 算法流程

#### 1. 自适应排序 (adaptive_sort)
```cpp
RC OrderByPhysicalOperator::adaptive_sort(Tuple *upper_tuple)
{
    // 1. 读取数据到内存
    // 2. 实时估算内存使用量
    // 3. 如果超过阈值，切换到外排序（保留已缓存数据）
    // 4. 否则使用内存排序（处理已缓存数据）
}
```

#### 2. 带缓存的外排序 (external_sort_with_cached_data)
```cpp
RC OrderByPhysicalOperator::external_sort_with_cached_data(Tuple *upper_tuple, size_t cached_count)
{
    // 1. 处理已缓存的数据（与后续数据合并或单独处理）
    // 2. 继续读取剩余数据并分块排序
    // 3. 执行多路归并
}
```

#### 3. 带缓存的内存排序 (quick_sort_with_cached_data)
```cpp
RC OrderByPhysicalOperator::quick_sort_with_cached_data(Tuple *upper_tuple, size_t cached_count)
{
    // 1. 继续读取剩余数据
    // 2. 对所有数据进行排序（包括已缓存的数据）
}
```

#### 2. 外排序 (external_sort)
```cpp
RC OrderByPhysicalOperator::external_sort(Tuple *upper_tuple)
{
    // 第一阶段：分块排序
    // 1. 读取数据块
    // 2. 在内存中排序
    // 3. 写入临时文件
    
    // 第二阶段：多路归并
    // 1. 读取所有临时文件
    // 2. 执行多路归并
    // 3. 输出最终结果
}
```

### 配置参数

- `DEFAULT_CHUNK_SIZE = 10000`: 默认块大小
- `DEFAULT_MEMORY_THRESHOLD = 100MB`: 默认内存阈值
- 临时文件路径: `/tmp/miniob_orderby_<pid>_<random>`

## 性能优化

### 1. 内存使用优化
- 动态调整块大小
- 精确的内存使用估算
- 及时释放不需要的内存

### 2. I/O优化
- 批量读写操作
- 二进制序列化格式
- 临时文件复用

### 3. 算法优化
- 使用标准库的快速排序
- 高效的多路归并
- 避免不必要的数据复制

## 使用示例

### 基本用法
```sql
-- 小数据集，使用内存排序
SELECT * FROM small_table ORDER BY id;

-- 大数据集，自动使用外排序
SELECT * FROM large_table ORDER BY name, age;
```

### 配置内存阈值
```cpp
// 在构造函数中设置
OrderByPhysicalOperator op(std::move(order_by), std::move(is_asc), limit);
op.memory_threshold_ = 200 * 1024 * 1024; // 200MB
```

## 错误处理

### 常见错误
1. **磁盘空间不足**: 检查临时目录空间
2. **内存分配失败**: 降低块大小或内存阈值
3. **文件I/O错误**: 检查文件权限和磁盘状态

### 错误恢复
- 自动清理临时文件
- 优雅的错误报告
- 资源泄漏防护

## 测试建议

### 1. 功能测试
- 小数据集排序验证
- 大数据集排序验证
- 边界条件测试

### 2. 性能测试
- 内存使用监控
- 排序时间测量
- 磁盘I/O统计

### 3. 压力测试
- 极限数据量测试
- 并发排序测试
- 资源限制测试

## 扩展性

### 1. 可扩展的排序算法
- 支持自定义比较函数
- 可插拔的排序策略
- 支持多列排序

### 2. 分布式排序
- 支持多节点排序
- 网络传输优化
- 负载均衡

### 3. 增量排序
- 支持增量数据更新
- 排序结果缓存
- 增量归并

## 重要修复

### 1. 子算子状态管理问题
在初始实现中，当检测到内存超限时，会调用 `child->close()` 关闭子算子，这导致后续无法重新读取数据。通过引入 `external_sort_with_cached_data()` 方法解决了这个问题：

1. **保留已缓存数据**: 在切换到外排序时，保留已经读取到内存中的数据
2. **智能数据合并**: 将已缓存的数据与后续读取的数据合并处理
3. **避免重复读取**: 确保每个数据只被读取一次，提高效率

### 修复后的流程
```cpp
// 修复前：会丢失数据
if (estimated_memory > memory_threshold_) {
    child->close();  // ❌ 关闭子算子，丢失已读取的数据
    return external_sort(upper_tuple);
}

// 修复后：保留数据
if (estimated_memory > memory_threshold_) {
    return external_sort_with_cached_data(upper_tuple, tuple_count);  // ✅ 保留已缓存数据
}
```

### 2. 流式处理优化
在初始实现中，外排序最终仍会将所有数据加载到内存中，这违背了外排序的初衷。通过引入流式处理机制解决了这个问题：

#### 问题分析
```cpp
// 修复前：所有数据都在内存中
rc = read_chunk_from_file(value_list_, final_file);  // ❌ 加载所有数据到内存
ids_.resize(value_list_.size());  // ❌ 设置所有索引
```

#### 解决方案
```cpp
// 修复后：流式处理
is_external_sort_ = true;  // ✅ 标记为外排序模式
current_file_stream_.open(current_temp_file_, std::ios::binary);  // ✅ 打开文件流
// 数据按需读取，不预加载到内存
```

#### 流式处理机制
1. **分块读取**: 每次只读取一个块的数据到内存
2. **按需获取**: 通过 `fetch_next_external()` 按需获取下一条数据
3. **内存控制**: 严格控制内存使用量，避免内存溢出
4. **多路归并**: 支持真正的多路归并流式处理

#### 核心方法
- `fetch_next_external()`: 外排序的数据获取逻辑
- `load_next_chunk_single_file()`: 单文件流式读取
- `load_next_chunk_merge()`: 多路归并流式处理
- `read_chunk_from_stream()`: 从文件流读取数据块

### 3. 内存排序数据重复问题
在初始实现中，`adaptive_sort()` 已经读取了一部分数据，但 `quick_sort()` 会重新读取所有数据，导致数据重复或丢失。通过引入 `quick_sort_with_cached_data()` 方法解决了这个问题：

#### 问题分析
```cpp
// 修复前：数据重复读取
adaptive_sort() {
    // 读取部分数据到 value_list_
    return quick_sort(upper_tuple);  // ❌ 重新读取所有数据
}

quick_sort() {
    // 重新读取所有数据，忽略已缓存的数据
    while (child->next()) { ... }  // ❌ 重复读取
}
```

#### 解决方案
```cpp
// 修复后：正确处理已缓存数据
adaptive_sort() {
    // 读取部分数据到 value_list_
    return quick_sort_with_cached_data(upper_tuple, tuple_count);  // ✅ 处理已缓存数据
}

quick_sort_with_cached_data() {
    // 继续读取剩余数据
    while (child->next()) { ... }  // ✅ 只读取剩余数据
    // 对所有数据进行排序（包括已缓存的数据）
}
```

## 总结

自适应内外排序算法为 MiniOB 提供了高效、可靠的排序功能。通过智能的策略选择和优化的算法实现，能够在各种数据规模下提供良好的性能表现。该实现具有良好的扩展性和维护性，为未来的功能增强奠定了坚实的基础。 