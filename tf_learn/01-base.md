## 概念

tf用*图*表示计算任务。计算时，图必须放在*会话*里面被启动

* 节点称之为op，其输入输出都是tensor
*

## 基本

* 变量使用前需要先初始化
*

## Feed

```python
input1 = tf.placeholder(tf.float32)
input2 = tf.placeholder(tf.float32)
output = tf.multiply(input1, input2)

with tf.Session() as sess:
    # print(sess.run([output], {input1: [7.], input2: [2.]}))
    print(sess.run(output))
```

这样会报错

> InvalidArgumentError (see above for traceback): You must feed a value for placeholder tensor 'Placeholder' with dtype float
	 [[Node: Placeholder = Placeholder[dtype=DT_FLOAT, shape=<unknown>,device="/job:localhost/replica:0/task:0/gpu:0"]()]]

换成被注释的 print

> [array([ 14.], dtype=float32)]

所以，所谓的Feed


## 一些问题

### 1. 为何要使用tf.app.flags

Tensorflow是分布式


# 更新记录

python  3.5
Tensorflow 1.3

### 基本用法

```python
交互式使用
sub = tf.sub(x, a)
sub = tf.subtract(x, a)

Feed
output = tf.mul(input1, input2)
output = tf.multiply(input1, input2)

```
