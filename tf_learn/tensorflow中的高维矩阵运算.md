## Question

有时我们需要计算高维矩阵的乘法运算，但是我们一般只熟悉二维空间中的矩阵乘法运算，那么如何计算D>2的情况？

## Example
这是capsule的动态路由算法中计算$\hat{u}_{j|i}=W_{ij}u_{i}$
```python
W = tf.get_variable('weight', (1152, 10, 8, 16), dtype=tf.float32,
                    initializer=tf.random_uniform_initializer(123))

u = tf.get_variable('u', (1152, 1, 8, 1), dtype=tf.float32,
                    initializer=tf.random_uniform_initializer(123))
u = tf.tile(u, (1, 10, 1, 1))

output = tf.matmul(W, u, transpose_a=True)

================================================================

其shape的变化如下：

W       (1152, 10, 8, 16)
u       (1152, 1, 8, 1)
# tf.tile操作
u       (1152, 10, 8, 1)
W       (1152, 10, 16, 8)
output  (1152, 10, 16, 1)
```

在Tensorflow中，对矩阵的运算是从最后两维开始的，前面的维度必须相同。它相当于将其变成了1152*10次二维矩阵运算。如果两个矩阵前面的维度不一致，在Tensorflow会报错：
```python
ValueError: Dimension 1 in both shapes must be equal,
    but are 16 and 10 for 'MatMul' (op: 'BatchMatMul')
    with input shapes: [1152,16,8,10], [1152,10,8,1].
```
