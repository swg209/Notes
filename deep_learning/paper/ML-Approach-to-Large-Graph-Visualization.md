# What Would a Graph Look Like in This Layout?A Machine Learning Approach to Large Graph Visualization

- 2017
- Oh-Hyun Kwon,Student Member, IEEE, Tarik Crnovrsanin, and Kwan-Liu Ma,Fellow, IEEE

## Abstract

使用不同的方法可视化图网络会导致很不一样的显示结构，因此选择一个好的布局方法对于图形可视化非常重要。确定一个好的布局的常用方法是使用美学标准和视觉检测，然而这种方法的计算代价太昂贵了。本文提出一种机器学习方法，使用图核去计算图之间的拓扑相似度。对于给定的图，我们的方法可以显示不同布局下的图形，并估计其相应的美学指标。我们的方法比计算真实比具有和他们的美学标准更快。并且，我们的graph kernels不仅快而且还准确。我们还进行了一项用户研究，证明我们的方法计算的拓扑相似性与人类感知的相似性相匹配。

## Introduction

贡献：

- 提出了快且准确的方法去显示在不同的布局下的图长什么样
- 提出了快且准确的方法估计图布局美学度量
- 一个为graph kernel设计的，基于graphlets的框架
- 演示了graph kernel作为大图可视化方法的有效性

### 2.2 度量两个图的相似性

将Graph kernels用在了计算两个图之间的相似性

所以如何度量？

论文说，graph kernel可以被看做是一个R-卷积核。它是通过递归分解子结构来度量两个图的相似性，度量相似性的方法会根据不同的子结构而变化

### 3.1.1 抽样

1. 随机采点。完全随机，不考虑连接关系。
2. 用游走邻接点的方法。

### 3.1.2 scaling graphlet frequency vector

graphlet到底是真实图的子结构，还是理论上存在的子结构？
所以输入到底是不是整个图？
然后整个图转换为向量？
然后放入核函数计算相似性？

## 3.1.3 各种核函数

- cos
- RBF 高斯核
- laplacian kernel

## 3.2 WGL-What would a graph look like in this layout?

是用graph kernels计算两个图的相似性

他们是通过graphlet frequencies来看两个图的相似性的

输入一个图，找出k个与其最像的图

有个问题，就是没有考虑图的大小。如图三b d所示，虽然二者graphlet frequencies想死，不过layout完全不一样。为了避免这种情况，我们添加一些约束条件，例如只计算输入图中顶点数大于一半，并且小于两倍的图。

总得来说就是：

1. 计算$G_{input}$与其他图之间的相似性
2. 除去不满足约束条件的图
3. 选出k个最相似的图
4. 将k个最像的图展示给用户

## 3.3 Estimating Aesthetic Metrics (EAM)

我们要预测aesthetic metrics，并且这是个回归问题，可以用SVR。


Training：

1. 准备训练数据——现有的图的layouts、aesthetic metrics（layouts应该就是可视化出来的拓扑结构吧？）
2. 计算用核函数核矩阵（就是图两两之间的相似性）
3. 训练回归模型

Estimation：

1. 计算输入图与训练数据中所有图之间的相似性
2. 用回归模型预测值——第一步不是已经预测了吗，这里预测的值是啥？

# 4 Evaluation 1： Estimating Layout Aesthetic Metrics

主要是为了解决以下问题：

- 我们的模型是否能在不计算layout的情况下，准确地预测layout's aesthetis metrics？
- 计算速度是否足够快
- 我们的graph kernels是否能又快又准确？

## 数据集

3700个图，包括社交网络、web文件网络、几何网格等。

在不丧失一般性的情况下，将带有多个连通分量的图分割出来（一个连通分量一个图）

将少于100个节点的图去掉，因为顶点数太小体现不出速度差异

最后剩下8263个图，顶点数从100—113million，边数从100-1.8billion

由于有些layout method计算时间超过了10天或者超出了内存，所以不包含进来

## Kernels

我们共对比了13个graphlet kernels

12种是这样的：2种抽样方法（RV RW）×2中graphlet frequency vector scaling方法（LIN LOG）×3种inner poroducts方法（COS RBF LAPLICIAN）

第13种方法是Deep Graphlet Kernel

然后这里论文部分没太看懂

对于每个图，我们抽样10,000个带有3、4、5个顶点的graphlets。因为计算成本的原因，3 4 5用得比较多。并且，超过6个顶点的graphlet比较少。RW采样的时候只考虑连接的graphlets，RV采样的时候连接的、不连接的graphlet都考虑。所有的核矩阵都归一化了，使得相似度的值在1以内。

## Layouts

- 力定向法:力定向法是基于引力和斥力的物理模型。它们是最早开发的布局方法之一，也是当今最常用的布局方法之一。一般来说，强制布局方法可分为两类:spring-electrical[27,30,32]和energy- based逼近[20,49]。我们从每组中选择了一个:来自spring-electrical方法的Fruchterman-Reingold (FR)[32]和来自energy-based方法的Kamada-Kawai (KK)[49]。

- 基于降维的方法:利用节点对间的图论距离，利用多维尺度变换(MDS)或主成分分析(PCA)等降维技术来绘制图。数据透视表[10]和高维嵌入式设备(HDE)[41]的工作原理是将几个顶点作为数据透视表的顶点，然后构造一个所有顶点到数据透视表的图论距离的矩阵表示。然后，将降维技术应用于矩阵。我们选择了这个家庭。

- 光谱法:光谱布局法使用矩阵的特征向量作为顶点的坐标，如图的距离矩阵[16]或拉普拉斯矩阵[53]。我们在这个家族中选择了byKoren[53]方法。

- 多层方法:为了减少计算时间，开发了多层布局方法。这些多级方法分层地将输入图分解成更粗的图。然后，他们绘制出最复杂的图形，并使用顶点位置作为下一个精细图形的初始布局。这个过程重复进行，直到原始图形显示出来。粗图的绘制有几种方法，如前导法[34,37,40,45,87]、降维基法[17]或谱法[31,54]。我们在这个家族中选择了sfdp[45]和fm3[37]。

- 基于聚类的方法:基于聚类的方法是为了在布局中强调图形聚类。当图形大小较大时，用户倾向于忽略边缘交叉的数量，而倾向于定义良好的集群[84]。我们从这个家族中选择了基于Treemap的布局[60]和基于Gosper曲线的布局[61]，利用图的层次聚类来布局图。

## Aesthetic Metrics

http://jackieanxis.coding.me/2017/09/03/%E6%9C%BA%E5%99%A8%E5%AD%A6%E4%B9%A0%E7%9A%84%E6%96%B9%E6%B3%95%E6%9D%A5%E5%B8%AE%E5%8A%A9%E8%BF%9B%E8%A1%8C%E5%A4%A7%E5%9B%BE%E5%8F%AF%E8%A7%86%E5%8C%96/#%E4%BA%8C%E3%80%81%E6%96%B9%E6%B3%95

实际上就是一些指标，用来判断怎么样的布局比较好看

## 准确性度量

- RMSE
- $R^2$决定系数，表示模型与给定数据的匹配程度，最大值是1，任意负值

## 实验实现

layout method已经有现成了的，分别是sfdp、FM、FR、KK、Spectral、Treemap、Gosper

## 实验结论

RW-LOG-LAPLACIAN kernel最好，耗时也短

时间主要是花在了抽样上
