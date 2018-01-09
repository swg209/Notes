# train

* 程序入口

下面以表格形式按顺序描述程序执行情况

初始化参数

- random seed
- flag
- load_data() (utils里面的函数)

做预处理

- 特征做归一化
- 计算support (gcn/gcn_cheby/dense)
  - 计算Chebyshev polynomials
    - norm(adj)，$D^{-1/2}AD^{-1/2}$
    - 生成[adj.shape]的单位矩阵I
    - laplacian = I-norm(adj)
    - 解laplacian，得到最大的特征值
    - rescaled Laplacian $\Lambda = 2/\lambda_{max} - I_N$
    - 计算Chebyshev recurrence
    - 返回tk
- num_supports
- 定义placeholders

初始化GCN

-




# utils

**load_data()**

读取数据

```
原始数据 共 3312 行，每行3703个特征

allx  [2312, 3703]
ally  [2312, 6]
tx    [1000, 3703]
ty    [1000, 6]
x     [120, 3703]
y     [120, 6]
feature [3327, 3703]
```

- 读取names包含的数据文件
- 全部放在object
- 读取test index，shape=1000
- sort test index

对 citeseer

- test.shape = 1000
- test_range_full = 1015
- 有15个**isolated nodes**

处理isolated nodes

- 定义tx_extended [1015, 3703]
- 前1000行把tx填进去
- tx = tx_extended
- 定义ty_extended [1015, 6]
- 前1000行把ty填进去
- ty = ty_extended

数据处理

- feature = allx & tx 垂直拼接（就是所有的数据）
- features[test_idx_reorder, :] = features[test_idx_range, :] 没看太懂，应该是使feature的tx本来是无序的，这条语句将它变成有序（按test_idx)
- graph转adj，`adj [3327, 3327]`
- label = ally & ty 垂直拼接
- labels[test_idx_reorder, :] = labels[test_idx_range, :] 同上

mask

- idx_test, idx_train, idx_val
- 根据idx创建mask，里面是bool类型的值
- 每个mask的shape都是3327
- 生成y_train, y_val, y_test

最后

- return adj, features, y_train, y_val, y_test, train_mask, val_mask, test_mask

---

**preprocess_features()**

- 对feature的axis=1求和
- 上面结果求倒数
- 拉成一维的数组r_inv
- 将r_inv倒数无穷大(也就是原始值为0)的位置赋值为0
- 构成diagonal matrix(scipy里面有很多矩阵操作相关的库)
- r_mat_inv.dot(features)

所以，本质上是做了归一化：对features每一行row，row里面的每个值rowi，有$\frac{row_i}{\sum{row}}$

# models

**class GCN(Model)**

\_\_init\_\_()

- input
- input_dim
- output_dim
- placeholders
- optimizer
- build(这里用到了**以名字命名的scope**，要注意)
  - \_build()
    - layers.append(GraphConvolution())
    - layers.append(GraphConvolution())

\_loss()

这里的loss不算直观，记录一下

```python
def masked_softmax_cross_entropy(preds, labels, mask):
    """Softmax cross-entropy loss with masking."""
    loss = tf.nn.softmax_cross_entropy_with_logits(logits=preds, labels=labels)
    mask = tf.cast(mask, dtype=tf.float32)
    mask /= tf.reduce_mean(mask)
    loss *= mask
    return tf.reduce_mean(loss)
```

先是element-wise的cross-entropy(preds, labels)

将mask的true&false转换为数值

$mask = \frac{mask}{\sum_{i}{mask_i}}$

$loss = loss * mask$

loss = reduce_sum(loss)

---

**class GraphConvolution()**

\_\_init\_\_

- **weight** 用 **glorot(Xavier)** 初始化
- logging, 作用是将weight用柱状图显示

\_call

- dropout(sparse_dropout没看太懂)
- convolve
- bias




# 漏

- defaultdict
- sparse_dropout
