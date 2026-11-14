# 01 · 顺序表（动态数组）

## 目标

用一块**连续的内存**存数据，支持自动扩容，按下标随机访问。

这和 `c-practice/examples/day4-dynamic-array.c` 是同一种东西，但这次要做到**接口完整、能直接当库用**。

## 数据结构

```c
typedef struct {
    int *data;      /* 指向堆上的连续内存 */
    int  size;      /* 已有元素个数 */
    int  cap;       /* 容量 */
} SeqList;
```

## 要实现的操作

| 函数 | 作用 | 复杂度 |
|---|---|---|
| `seq_init(SeqList *l)` | 初始化，初始容量 4 | O(1) |
| `seq_free(SeqList *l)` | 释放内存，把指针置 NULL | O(1) |
| `seq_push_back(SeqList *l, int x)` | 尾部插入，满了扩容 | 均摊 O(1) |
| `seq_insert(SeqList *l, int idx, int x)` | 在 idx 位置插入 | O(n) |
| `seq_erase(SeqList *l, int idx)` | 删除 idx 位置的元素 | O(n) |
| `seq_get(const SeqList *l, int idx, int *out)` | 按下标取值 | O(1) |
| `seq_find(const SeqList *l, int x)` | 查找，返回下标，找不到返回 -1 | O(n) |
| `seq_size(const SeqList *l)` | 返回元素个数 | O(1) |
| `seq_print(const SeqList *l)` | 打印全部 | O(n) |

## 关键设计点

1. **扩容策略**：容量翻倍（`cap * 2`），不要 `cap + 1`——后者是 O(n²)
2. **`realloc` 必须用临时变量接返回值**：
   ```c
   int *nd = realloc(l->data, sizeof(int) * newcap);
   if (!nd) return 0;        /* 失败，原数据还在 */
   l->data = nd;
   ```
3. **插入时从后往前搬**：
   ```c
   for (int i = l->size; i > idx; i--)
       l->data[i] = l->data[i-1];
   ```
4. **删除时从前往后搬**：
   ```c
   for (int i = idx; i < l->size - 1; i++)
       l->data[i] = l->data[i+1];
   ```
5. **所有下标都要检查边界**：`idx < 0 || idx > l->size` 时返回失败

## 验收

- [ ] 插入 100 万个元素不崩，耗时毫秒级
- [ ] 在头部反复插入 1000 次，结果正确
- [ ] 删除后 `size` 正确，后面的元素前移
- [ ] 越界访问返回失败，不崩溃
- [ ] `seq_free` 后 `data == NULL`
- [ ] 内存账本 `alloc == free`
- [ ] `-Wall -Wextra` 零警告

## 自测题

1. 为什么扩容要翻倍，而不是每次加固定大小？
2. `realloc` 失败时，原来的数据还能用吗？
3. `seq_insert` 的循环为什么必须**从后往前**？从前往后会怎样？
4. `seq_free` 之后如果不把 `data` 置 `NULL`，会有什么风险？

## 写完后

在 `README.md` 里补一节「踩坑记录」，写你实际遇到的问题。
