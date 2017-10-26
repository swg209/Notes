### 查找Tensorflow的常用函数
[点击这里](http://blog.csdn.net/lenbow/article/details/52218551)

### tf.train.Supervisor

[点击这里](http://www.cnblogs.com/zhouyang209117/p/7088051.html)

该方法会自动判断传入的logdir里面的模型是否存在，如果有则自动加载

### tf.train.Saver

[说明](http://blog.csdn.net/u011500062/article/details/51728830)

保存模型参数

### tf.summary.FileWriter

用于保存模型，其生成的文件可被TensorBoard可视化

命令：```tensorboard --logdir your_dir```

### tf.GPUOptions

配置GPU的一些选项

### tf.ConfigProto

一般用在创建```session```的时候。用来对```session```进行参数配置

例如：

```python
gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.7)
config=tf.ConfigProto(gpu_options=gpu_options)
session = tf.Session(config=config, ...)

#设置每个GPU应该拿出多少容量给进程使用，0.7代表70%
```

### tf.variable_scope()
