[toc]

## SEMI-SUPERVISED CLASSIFICATION WITH GRAPH CONVOLUTIONAL NETWORKS

<br>

## 2 Fast Approximate Convolutions On Graphs

- 介绍基于图的神经网络模型 $f(X, A)$ 的理论基础

<br>

$$H^{(l+1)} = \sigma( \hat{D}^{-\frac{1}{2}} \hat{A} \hat{D}^{-\frac{1}{2}} H^{(l)} W^{l} ) \tag2$$

- $\hat{A} = A + I_N$：加了自连接的无向图的邻接矩阵
- $\hat{D} = \sum_{j} \hat{A}_{ij}$：度矩阵
- $W^{l}$：可训练的权重矩阵
- $\sigma(\cdot)$：激活函数，如ReLU
- $H^{(l)} \in R^{N * D}$：matrix of activations in the $l^{th}$ layer; $H^{(0)} = X$

对于这个propagation rule，论文中提供了一个解释：**Weisfeiler-Lehman algorithm**，附录里面有解释，下面是原论文
>Boris Weisfeiler and A. A. Lehmann.  A reduction of a graph to a canonical form and an algebraarising during this reduction.Nauchno-Technicheskaya Informatsia, 2(9):12–16, 1968.

<br>

#### 2.1 Spectral Graph Convolutions

Spectral conv on graph定义为信号 $x \in R^{N}$ (每个节点都是一个标量)与filter $g_{\theta} = diag(\theta)$ (在Fourier domain中由 $\theta \in R^{N}$ 参数化的filter)：

$$g_{\theta} \star x = U g_{\theta} U^T x \tag3$$

- U：normalized graph Laplacian *L* 的**特征向量矩阵**
- *L* ：$L = I_N - D^{-\frac{1}{2}} A D^{-\frac{1}{2}} = U \Lambda U^T$

>注：<br>
这里就有很多问题了。
> 1. 首先，上文说 $g_{\theta}$ 是频域中的filter，一个频域的函数与时域的x做卷积？我查的资料没这个说法。
> 2. 文中说U是L的特征向量矩阵，是由L得到的（具体看上面L的解释），那么可不可以说，U跟 $g_{\theta}$ 是没有运算关系的？
> 3. 文中说$U^T x$是对x的傅里叶变化。所以Laplacian的特征向量矩阵还能做傅里叶变换？是有种变换叫拉普拉斯变换，但是不清楚与拉普拉斯矩阵的联系。

先把这些问题放一边，按照论文的解释， $g_{\theta}$ 是一个在Fourier domain的对角矩阵，而L的 $\Lambda$ 是它的一个特例。当L化成$U \Lambda U^T$的时候，由于L是时域的，所以$U^T$ 相当于是将其转为频域，$U$ 相当于将其转回时域。由于矩阵乘法满足结合律，所以论文说$U^T x$表示x的傅里叶变换，而$g_{\theta}$ 看作 $g_{\theta}( \Lambda )$。

(3)式的计算复杂度是 $O(N^2)$ ，太昂贵了，特别是在节点很多的时候计算L的特征值特征向量。下面这篇论文建议用 *Chebyshev polynomials* 来近似计算 $g_{\theta}( \Lambda )$ ：

>David K. Hammond, Pierre Vandergheynst, and R ́emi Gribonval.  Wavelets on graphs via spectralgraph theory.Applied and Computational Harmonic Analysis, 30(2):129–150, 2011.

那么

$$g_{{\theta}^{'}}( \Lambda ) \approx \sum_{k=0}^{K} {\theta}_{k}^{'} T_k({\hat{\Lambda}}) \tag4$$

- $\hat{ \Lambda } = \frac{2}{\lambda_{max}} \Lambda - I_N$，$\lambda_{max}$ 表示L最大的特征值

- $\theta^{'} \in R^K$ 是vector of Chebyshev coefficients

- $T_k(x) = 2 x T_{k-1} - T_{k-2}$，$T_0(x) = 1$，$T_1(x) = x$

<br>

回到(3)式

$$g_{{\theta}^{'}} \star x \approx \sum_{k=0}^{K} {\theta}_{k}^{'} T_k({\hat{L}}) x \tag5$$

- $\hat{L} = \frac{2}{\lambda_{max}} L - I_N$

需要注意的事，现在的（5）式是Laplacian的K阶多项式，是`K-localized`的了。K指的是K steps away from the central node($K^{th}$-order neighborhood)

(5)式的计算复杂度是$O(|\varepsilon|)$ (linear in the number of edges)

<br>

**总结：**

2.1 讲的主要是

- Spectral conv on graph的定义
- 如何利用Chebyshev polynomials近似计算(3)式

<br>

#### 2.2 Layer-wise Linear model

将(5)式叠加，并且“each layer followed by a point-wise non-linearity”， 就形成了基于图卷积的神经网络。现在令K=1，那么函数就变成了关于L的线性函数，即“a linear function on the graph Laplacian spectrum”。

论文上直观地认为，不去明确限定Chebyshev polynomials的参数可以缓和对图上局部邻居结构的过拟合，这种图有着非常广的节点度分布。(这里省略了一部分内容)

<br>

在这种线性GCN下，近似 $\lambda_{max} \approx 2$，因为我们期望神经网络参数可以在训练中适应这种标量变化。在这种近似下，(5)式变为：

$$g_{{\theta}^{'}} \star x \approx \theta_{0}^{'} x + \theta_{1}^{'} (L - I_N) x = \theta_{0}^{'} x - \theta_{1}^{'} D^{-\frac{1}{2}} A D^{-\frac{1}{2}} x \tag6$$

- filter的参数 $\theta_{0}^{'}$ 和 $\theta_{1}^{'}$ 可以在整个graph中共享

filter以这种形式应用相当于对某个节点的$k^{th}$-order neighborhood做了高效的卷积(k是filtering operation的数量，或者是神经网络模型conv层的数量)

<br>

在实践中，**限制参数** 的数量可以解决过拟合，并且最小化operation的数量，所以再如下进行简化：

$$g_{{\theta}^{'}} \star x \approx \theta (I_N + D^{-\frac{1}{2}} A D^{-\frac{1}{2}}) x \tag7$$

- $\theta = \theta_{0}^{'} = - \theta_{1}^{'}$

问题是，重复这个operator会导致数值不稳定和梯度爆炸/消失，因此再用一个renormalization trick：$I_N + D^{-\frac{1}{2}} A D^{-\frac{1}{2}} \to \hat{D}^{-\frac{1}{2}} \hat{A} \hat{D}^{-\frac{1}{2}}$，即令$\hat{A} = A + I_N$，$\hat{D}_{ii} = \sum_j \hat{A}_{ij}$

<br>

之前说X是N×1的，我们可以一般化，使$X \in \mathbb{R}^{N \times C}$ C是input channels
