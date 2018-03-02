### 读取数据的方式

代码使用的是tensorflow提供的一套读取数据的方式，它并不是像feed_dict的方式可以看到的，它只是创建了graph，在run的时候才开始根据所定义的graph读取数据

关于tf.train.string_input_producer可以看[这里](http://blog.csdn.net/zzk1995/article/details/54292859)
