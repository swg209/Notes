
## shortestpath整体思路解读

### 创建数据

1. 均匀分布下随机生成节点的特征pos
2. 指数分布下随机生成节点权重weight
3. 利用networkx.geographical_threshold_graph生成 图geo_graph。在生成过程中，若两个节点之间满足一定条件则会有边相连。具体公式可以看函数说明。
4. 随机选取两个点，计算出他们的最短路径上的节点，作为ground true

### 划分出input、target

1. 将[创建数据]得到的图作为输入
2. 将输入的图copy两份，分别命名为 input_graph target_graph
3. input_graph -> 节点 特征更新为("pos", "weight", "start", "end")
   target_graph -> 节点 特征更新为onehot后的("solution",)
4. input_graph -> 边 特征更新为("distance",)
   target_graph -> 边 特征更新为onehot后的("solution",)
5. 计算最短路径上节点个数，放入target_graph.graph["features"]
6. input_graph.graph["features"] = 0.0

### 模型部分

```python
                    Hidden(t)   Hidden(t+1)
                       |            ^
          *---------*  |  *------*  |  *---------*
          |         |  |  |      |  |  |         |
Input --->| Encoder |  *->| Core |--*->| Decoder |---> Output(t)
          |         |---->|      |     |         |
          *---------*     *------*     *---------*

```

如上所示，模型分为三个部分

- **Encoder** 包含三部分，分别是edge、node、global。每部分都由一个单独的MLP（也可以传入自定义函数）来对原始特征进行编码，编码后的输出作为Core的输入
- **Core** 如图所示，Core的输入有两部分，分别是Encoder的输出，上一轮Core的输出。同样包含三部分，分别是edge、node、global。
  - edge根据上一轮的edge的特征，邻接点的特征和global特征来更新；
  - node根据上一轮node的特征，与之相连的边的特征和global特征来更新；
  - global根据上一轮global特征，图上所有边的特征的和图上所有节点的特征来更新。

- **Decoder** 与Encoder的结构是一样的，作用与Encoder相反，起解码的作用。


### loss

因为我们最终的目的是求最短路径，所以路径上的节点和边都应该为1，其余的为0。我们训练模型就是希望它的输出逼近这个结果：

$$loss = softmax\_corss\_entropy(output.nodes, target.nodes)+softmax\_corss\_entropy(output.edges, target.edges)$$

---

## sort示例

### 悉知

除了创建数据部分，其他主要思路与shortest path差不多，模型也是一样的，所以在此不再重复，可以看代码中的注释深入理解。

---

## 对graph_nets的简短介绍

### graph_nets的结构

```python
graph_nets
 - blocks.py
 - graphs.py
 - modules.py
 - utils_np.py
 - utils_tf.py
```

### 各个模块的简介

- **`blocks.py`**
  组成图网络的块，包含了：
  - `broadcast_{field_1}_to_{field_2}` 把信息从`field_1`传递到`field_2`相关的元素中
  - `{field_1}To{field_2}Aggregator` 把信息从`field_1`传递到`field_2`相关的元素中，并且按某种方法聚合（相加）信息
  - the `EdgeBlock`, `NodeBlock` and `GlobalBlock` 都是图网络上面的模块，这三个模块都是根据输入的图来更新边、节点或者全局特征。

- **`graphs.py`**

  定义了`GraphTuple`，它的主要目的是希望不同形状和大小的多个图都能通过同一种方式分batch训练

  `GraphTuple`中定义了：

  - `N_NODE` 是一个向量，里面每个元素分别表示对应的图的节点数量，例如`graph.N_NODE[i]`是第i个图的节点数量
  - `N_EDGE` 是一个向量，里面每个元素分别表示对应的图的边的数量，例如`graph.N_EDGE[i]`是第i个图的边的数量
  - `NODES` 是所有节点特征的集合，它或者是一个大小为`[n_nodes]+node_shape`的向量，`n_nodes`为一个batch中所有的图的顶点数之和，`node_shape`表示节点特征的维度。或者为`None`。若为`None`不代表图上没有节点，只是说图上的节点没有特征。
  - `EDGES` 是所有边的集合，它或者是一个大小为`[n_edges]+edge_shape`的向量，`n_edges`为一个batch中所有的图的顶点数之和，`edge_shape`表示节点特征的维度；或者为`None`。若为`None`不代表图上没有边，只是说图上的边没有特征。
  - `RECEIVERS` 是某条边上的接收节点。例如`graph.RECEIVERS[i]`是第i条边上的接收节点
  - `SENDERS` 是某条边上的发送节点。例如`graph.SENDERS[i]`是第i条边上的发送节点
  - `GLOBALS` 是图的全局特征，它或者是一个形状为`[n_graphs] + global_shape`的向量，或者为`None`（图没有）

  注意的是，`GraphTuple`有以下限制
  - `N_NODE`和`N_EDGE`不可为`None`
  - `RECEIVERS`和`SENDERS`必须同时为`None`，或同时不为`None`
  - `RECEIVERS`和`SENDERS`皆为`None`，`EDGES`必须为`None`


- **`modules.py`**

  `modules.py`里面提供了以下现成的模型：

  - `GraphNetwork`: 一般化的图网络，需要设置`blocks.py`里面的`EdgeBlock`, `NodeBlock` and `GlobalBlock`

  - `GraphIndependent`: 一种图网络，仅根据输入的边的特征来更新的边，仅根据节点的特征来更新节点，仅根据全局特征来更新全局的特征

  - `InteractionNetwork` (from https://arxiv.org/abs/1612.00222): 该模型可以在边和节点上传输信息

  - `RelationNetwork` (from https://arxiv.org/abs/1706.01427): 该网络通过输入节点特征之间的关系更新全局特征

  - `DeepSets` (from https://arxiv.org/abs/1703.06114): 该模型应用在顶点的集合上，可以看做是`GraphNetwork`去掉了边的图，带有顶点、全局特征

  - `CommNet` (from https://arxiv.org/abs/1605.07736 and https://arxiv.org/abs/1706.06122): 该网络通过当前节点上一轮迭代时的特征和邻接点的特征来更新当前节点的特征
- **`utils_np.py`**

  `utils_np.py`和`utils_tf`中提供了一些方便的方法用于numpy和tensorflow相关的数据处理。

- **`utils_tf.py`**

  主要是用于图上对`Tensor`的操作，主要有：

  - `build_placeholders_from_data_dicts` 和 `build_placeholders_from_networkx`
     创建表示图的placeholder

  - `get_feed_dict` 从`graphs.GraphsTuple`上获取`NODES, EDGES, RECEIVERS, SENDERS, GLOBALS, N_NODE, N_EDGE`，并创建`feed_dict`

  - `data_dicts_to_graphs_tuple` 将数据字典转换为`graphs.GraphsTuple`

  - `fully_connect_graph_static` (resp. `fully_connect_graph_dynamic`) adds
    edges to a `graphs.GraphsTuple` in a fully-connected manner, in the case
    where the number of nodes per graph is known at graph construction time and is the same for all graphs (resp. only known at runtime and may depend on the graph); 往`graphs.GraphsTuple`实例中添加边

  - `set_zero_node_features`, `set_zero_edge_features` and
    `set_zero_global_features` complete a `graphs.GraphsTuple` with a `Tensor`
    of zeros for the nodes, edges and globals;

  - `concat` batches `graphs.GraphsTuple` together (when using `axis=0`), or
    concatenates them along their data dimension;

  - `repeat` is a utility convenient to broadcast globals to edges or nodes of
    a graph;

  - `get_graph` indexes or slices a `graphs.GraphsTuple` to extract a subgraph
    or a subbatch of graphs;

  - `stop_gradients` stops the gradients flowing through a graph;

  - `identity` applies a `tf.identity` to every field of a graph;

  - `make_runnable_in_session` allows to run a graph containing `None` fields
    through a Tensorflow session.

## 如何使用graph_nets

### 创建数据

1. 由于graph_nets的输入和输出都是图，所以一开始你可以使用networkx创建图来作为训练数据(input_graph)，并且创建target_graph，也就是ground true。训练数据和ground true怎么定义，视具体问题而定，只要以networkx的图结构（例如nx.Graph()、nx.DiGraph()），或者graph_nets定义的GraphTurple，作为数据的载体即可。
2. 用graph_nets.utils_tf.placeholders_from_networkxs将input_graph和target_graph转换为graph_nets所需要的graphs.GraphTuple格式的图。这个函数会帮你创建placeholders，所以不需要自己另外去定义，只需要给定输入的图即可，很方便。

### 创建模型

graph_nets中目前仅包含少数图模型，

- **GraphNetwork** 普通的图，带有边、顶点、全局特征
- **DeepSets** 应用在顶点的集合上，可以看做是**GraphNetwork**去掉了边的图，带有顶点、全局特征
- **SelfAttention**

如果是希望往graph_nets中添加图模型，可以在这里创建新的模型class

如果希望使用现有的模型，可以看模型的说明按需选择

以GraphNetwork为例，它需要我们提供边、顶点、全局特征的更新函数，所以在创建实例时需要将更新函数传入。注意，传入的更新函数必须能返回Sonnet module或者类似的可调用的模型。因为源码中有"()"的调用操作。

##
