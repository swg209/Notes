## GCNs Part III: Embedding the karate club network

![](http://tkipf.github.io/graph-convolutional-networks/images/karate.png)

来看一下我们这个简单的GCN模型如何在一个著名的图数据集上工作的：Zachary's karate club network(参见上图)

我们使用3层GCN，权重随机初始化。现在，甚至在训练之前，我们简单地将图的邻接矩阵和$X = I$（i.e. 单位矩阵，因为节点没有特征）放入模型。3层GCN在前向传播的过程中执行了三次传播，并且高效地对每个节点的三阶近邻做卷积操作（all nodes up to 3 "hops" way）。特别地，模型产生了节点的嵌入（embedding of nodes），节点的嵌入非常类似于图的community-structure。记住我们是随机初始化权重的都还没开始训练！就已经有下面的这个结果！

![](http://tkipf.github.io/graph-convolutional-networks/images/karate_emb.png)

这可能有点惊喜。最近有一个叫DeepWalk的算法表示，他们在复杂的无监督训练中可以学习一个非常相似的embedding。我们的GCN模型是怎么做到通过更少的甚至没有训练就能达到这样的效果？

我们可以通过将GCN解释为作用在图上的一个广义可微的Weisfeiler-Lehman算法：

对于所有节点 $v_i \in G$


$$batchsize * seqlength * match.floor(\frac{length}{batchsize * seqlength})$$
