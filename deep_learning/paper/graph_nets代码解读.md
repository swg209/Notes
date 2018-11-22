[toc]

#  [列表元素排序](https://colab.research.google.com/github/deepmind/graph_nets/blob/master/graph_nets/demos/shortest_path.ipynb)

本代码主要展示了如何取用graph_nets学习如何排序

将列表看作是个全连接图，我们的任务就是让模型学会如何排序，使其得到一个排序后的图。这个排序后的图的开始节点是列表中最大的元素，它有一条边指向下一个最大的元素，如此类推。

我们通过对比模型预测的排序结果，跟真实的排序结果比较，来衡量模型的好坏。

## 1 依赖包安装

pip install graph_nets matplotlib scipy networkx

## 2 Code

推荐使用debug从“Set up model training and evaluation”开始阅读

### 2.1 Set up model training and evaluation

```python
'''
本代码包含三部分

- Encoder：对边、顶点和全局属性进行编码
- Core：执行N轮处理（message-passing），以Encoder的输出，和Core上一轮的输出，来作为输入
- Decoder：Todo

#                     Hidden(t)   Hidden(t+1)
#                        |            ^
#           *---------*  |  *------*  |  *---------*
#           |         |  |  |      |  |  |         |
# Input --->| Encoder |  *->| Core |--*->| Decoder |---> Output(t)
#           |         |---->|      |     |         |
#           *---------*     *------*     *---------*


-
'''

tf.reset_default_graph()

# Model parameters.
# Number of processing (message-passing) steps.
num_processing_steps_tr = 10
num_processing_steps_ge = 10

# Data / training parameters.
num_training_iterations = 10000
batch_size_tr = 32
batch_size_ge = 100
# Number of elements in each list is sampled uniformly from this range.
num_elements_min_max_tr = (8, 17)
num_elements_min_max_ge = (16, 33)

# Data.
# Training.
inputs_op_tr, targets_op_tr, sort_indices_op_tr, _ = create_data_ops(
    batch_size_tr, num_elements_min_max_tr)
#
inputs_op_tr = utils_tf.set_zero_edge_features(inputs_op_tr, 1)
inputs_op_tr = utils_tf.set_zero_global_features(inputs_op_tr, 1)
# Test/generalization.
inputs_op_ge, targets_op_ge, sort_indices_op_ge, _ = create_data_ops(
    batch_size_ge, num_elements_min_max_ge)
inputs_op_ge = utils_tf.set_zero_edge_features(inputs_op_ge, 1)
inputs_op_ge = utils_tf.set_zero_global_features(inputs_op_ge, 1)

# Connect the data to the model.
# Instantiate the model.
model = models.EncodeProcessDecode(edge_output_size=2, node_output_size=2)
# A list of outputs, one per processing step.
output_ops_tr = model(inputs_op_tr, num_processing_steps_tr)
output_ops_ge = model(inputs_op_ge, num_processing_steps_ge)

# Loss.
loss_ops_tr = create_loss_ops(targets_op_tr, output_ops_tr)
loss_op_tr = sum(loss_ops_tr) / num_processing_steps_tr  # loss_ops_tr
loss_ops_ge = create_loss_ops(targets_op_ge, output_ops_ge)
loss_op_ge = loss_ops_ge[-1]

# Optimizer.
learning_rate = 1e-3
optimizer = tf.train.AdamOptimizer(learning_rate)
step_op = optimizer.minimize(loss_op_tr)

# Lets an iterable of TF graphs be output from a session as NP graphs.
inputs_op_tr, targets_op_tr, sort_indices_op_tr = make_all_runnable_in_session(
    inputs_op_tr, targets_op_tr, sort_indices_op_tr)
inputs_op_ge, targets_op_ge, sort_indices_op_ge = make_all_runnable_in_session(
    inputs_op_ge, targets_op_ge, sort_indices_op_ge)
```
