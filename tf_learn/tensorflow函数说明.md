### 查找Tensorflow的常用函数
[点击这里](http://blog.csdn.net/lenbow/article/details/52218551)

<br>

**tf.train.Supervisor**

[点击这里](http://www.cnblogs.com/zhouyang209117/p/7088051.html)

该方法会自动判断传入的logdir里面的模型是否存在，如果有则自动加载

<br>

**tf.train.Saver**

[说明](http://blog.csdn.net/u011500062/article/details/51728830)

保存模型参数

<br>

**tf.summary.FileWriter**

用于保存模型，其生成的文件可被TensorBoard可视化

命令：```tensorboard --logdir your_dir```

<br>

**tf.GPUOptions**

配置GPU的一些选项

<br>

**tf.ConfigProto**

一般用在创建```session```的时候。用来对```session```进行参数配置

例如：

```python
gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.7)
config=tf.ConfigProto(gpu_options=gpu_options)
session = tf.Session(config=config, ...)

#设置每个GPU应该拿出多少容量给进程使用，0.7代表70%
```

<br>

**tf.variable_scope()**

约束变量范围

<br>

**tf.one_hot()**

*定义*

```python
def one_hot(indices, depth, on_value=None, off_value=None, axis=None, dtype=None, name=None)
```

*例子*

```python
# If the input `indices` is rank `N`, the output will have rank `N+1`. The new axis is created at dimension `axis` (default: the new axis is appended at the end).
#   batch x features x depth if axis == -1
#   batch x depth x features if axis == 1
#   depth x batch x features if axis == 0

# Suppose that
indices = [0, 2, -1, 1]
depth = 3  # 三个类别
on_value = 5.0  # 是该类的话赋值5
off_value = 0.0  # 不是该类的赋值0
axis = -1  # 上面有

# Then output is `[4 x 3]`:
output =
  [5.0 0.0 0.0]  // one_hot(0)
  [0.0 0.0 5.0]  // one_hot(2)
  [0.0 0.0 0.0]  // one_hot(-1)
  [0.0 5.0 0.0]  // one_hot(1)
```

<br>

**tf.contrib.layers.conv2d()**

*定义*

```python
conv2d(
    inputs,
    num_outputs,
    kernel_size,
    stride=1,
    padding='SAME',
    data_format=None,
    rate=1,
    activation_fn=tf.nn.relu,
    normalizer_fn=None,
    normalizer_params=None,
    weights_initializer=initializers.xavier_initializer(),
    weights_regularizer=None,
    biases_initializer=tf.zeros_initializer(),
    biases_regularizer=None,
    reuse=None,
    variables_collections=None,
    outputs_collections=None,
    trainable=True,
    scope=None
)
```

<br>

**tf.get_variable与tf.Variable**

```python
with tf.variable_scope("foo"):
  v = tf.get_variable("v", [1])  # v.name == "foo/v:0"
  w = tf.get_variable("w", [1])  # w.name == "foo/w:0"

with tf.variable_scope("foo", reuse=True):
  v = tf.get_variable("v")  # The same as v above
```

而对tf.Variable来说，是直接定义变量

<br>

**tf.tile()**

*例子*

```python
with tf.Graph().as_default():  
    a = tf.constant([[1,2],[3,4]],name='a')     
    b = tf.tile(a,[2,3])  
    sess = tf.Session()  
    print(sess.run(b))

output：
    [[1 2 1 2 1 2]  
     [3 4 3 4 3 4]  
     [1 2 1 2 1 2]  
     [3 4 3 4 3 4]]


tiling `[a b c d]` by `[2]`
produces `[a b c d a b c d]`
```

<br>

**tf.reduce_sum()**

Computes the sum of elements across dimensions of a tensor

*例子*

```python
# 'x' is [[1, 1, 1]
#         [1, 1, 1]]
tf.reduce_sum(x) ==> 6
tf.reduce_sum(x, 0) ==> [2, 2, 2]
tf.reduce_sum(x, 1) ==> [3, 3]
tf.reduce_sum(x, 1, keep_dims=True) ==> [[3], [3]]
tf.reduce_sum(x, [0, 1]) ==> 6

s_J = tf.reduce_sum(s_J, axis=1, keep_dims=True)
```

<br>

**tf.argmax()**

*例子*

```python
import numpy as np
import tensorflow as tf

sess = tf.session()
m = sess.run(tf.truncated_normal((5,10), stddev = 0.1) )
print type(m)
print m

----------------------------------------------------------------
<type 'numpy.ndarray'>
[[ 0.09957541 -0.0965599   0.06064715 -0.03011306  0.05533558  0.17263047
  -0.02660419  0.08313394 -0.07225946  0.04916157]
 [ 0.11304571  0.02099175  0.03591062  0.01287777 -0.11302195  0.04822164
  -0.06853487  0.0800944  -0.1155676  -0.01168544]
 [ 0.15760773  0.05613248  0.04839646 -0.0218203   0.02233066  0.00929849
  -0.0942843  -0.05943     0.08726917 -0.059653  ]
 [ 0.02553608  0.07298559 -0.06958302  0.02948747  0.00232073  0.11875584
  -0.08325859 -0.06616175  0.15124641  0.09522969]
 [-0.04616683  0.01816062 -0.10866459 -0.12478453  0.01195056  0.0580056
  -0.08500613  0.00635608 -0.00108647  0.12054099]]


#使用tensorflow中的tf.argmax()
col_max = sess.run(tf.argmax(m, 0) )  #当axis=0时返回每一列的最大值的位置索引
print col_max

row_max = sess.run(tf.argmax(m, 1) )  #当axis=1时返回每一行中的最大值的位置索引
print row_max

array([2, 3, 0, 3, 0, 0, 0, 0, 3, 4])
array([5, 0, 0, 8, 9])
```

tf.argmax()与numpy.argmax()方法的用法是一致的

- axis = 0的时候返回每一列最大值的位置索引
- axis = 1的时候返回每一行最大值的位置索引
- axis = 2、3、4...，即为多维张量时，同理推断

<br>

**tf.squeeze()**

删除张量中所有大小为1的维度

```python
# ‘t’ is a tensor of shape [1, 2, 1, 3, 1, 1]
shape(squeeze(t)) => [2, 3]

# 't' is a tensor of shape [1, 2, 1, 3, 1, 1]
# 如果不想删除所有大小是1的维度，可以通过squeeze_dims指定
# squeeze_dims: An optional list of ints. Defaults to []. If specified, only squeezes the dimensions listed. The dimension index starts at 0. It is an error to squeeze a dimension that is not 1.
shape(squeeze(t, [2, 4])) => [1, 2, 3, 1]
```
