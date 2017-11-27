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
