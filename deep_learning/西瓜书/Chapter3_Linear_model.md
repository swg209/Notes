### Intro

讲一下这个章节的大概思路

首先我们有线性模型$y=wx+b$，本章节所有内容都是从它展开的

我们要求解模型，于是使用最小二乘法(least square method)，它本质上是最小化Euclidean distance，也就是均方根误差，来找到最优解的。

然后就直接给出logistic function，通过变化logistic function得到“几率”(odds)。

$$ln\frac{y}{1-y}=w^Tx+b \tag{1}$$

即，对数几率(log odds，亦称logit) = 线性回归模型，用线性模型逼近log odds。

然后，引入极大似然法 $l(w,b) = \sum lnp(y_i|x_i;w,b)$。刚好这个是高阶可导连续凸函数，对$l$求最大化，根据凸优化理论，可以用gradient desent、Newton method求最优解。

好，下面是LDA

### LDA

Linear Discriminant Analysis，LDA，线性判别分析，最早来源于Fisher判别分析

LDA本质上：

- 假设x是d维向量
- 在d维空间中
- 给定$y=w^Tx$
- 将样例投影到直线上
- 使直线上同一类的点尽可能近，不同类的点尽可能远
- 即同类投影点协方差尽可能小

LDA不仅用作分类，还被视为监督降维技术

**Todo | 略**

- [具体推导过程看这里](http://www.cnblogs.com/jerrylead/archive/2011/04/21/2024384.html)
- 以及[这个](http://www.cnblogs.com/leftnoteasy/archive/2011/01/08/lda-and-pca-machine-learning.html)

### 多分类学习

- One vs. One, OvO
- One vs. Many, OvM
- Many vs. Many, MvM

OvO, OvM是MvM的特例

最常用的MvM技术：**纠错输出码(Error Correcting Output Codes, 即ECOC)** ，本质上是**将编码思想引入类别拆分，并尽可能在解码过程中具有容错性**(**略**)

### 类别不平衡问题

比如反例998个，正例2个

1. **Rescaling(Rebalance)**： $\frac{y^{'}}{1-y^{'}} = \frac{y}{1-y} × \frac{m^-}{m^+}$
2. **undersampling** 欠采样：去除反例使得正反例数目接近
3. **oversampling** 过采样：增加正例数目

对于1，其实就是cost-sensitive learning的基础
对于2，代表性算法叫EasyEnsemble，采用集成学习机制，将负样本划分成n个子集，与正样本一起给n个学习器学习。这样在全局看来就不会丢失重要信息。
