## Jaccard Curvature—an Efficient Proxy for Ollivier-Ricci Curvature in Graphs

### Abstract

Ollivier-Ricci(OR) curvature，需要解决每条边的最佳公共交通问题，这在大型密集网络中计算量很大。

所以提出两个基于 **Jaccard index(JI)** 的替代方案

- **Jaccard curvature(JC)**
- **Generalized Jaccard curvature(gJC)**

**JC** 是一种JI的shift and scaling，它能抓住边上节点的邻域的重叠部分。**gJC** 抓住了shortest path distances。

最后结果表明，gJC在许多网络中效果都比较好，而JC只在某些场景有好效果。

### Introduction

一对顶点的OR curvature的定义是基于他们之间的associated mass distributions所得到的optimal mass transport。若限制该对顶点必须是邻接的顶点，OR curvature可以被看做以边为中心的度量，类似于betweenness或者random-walk度量。

对OR curvature来说

- $>0$ 意味着两个顶点各自的邻接点很近(或许重叠或者共享)
- $=0$ (or near-zero)，意味着节点是局部嵌入到平面中的(啥玩意，原文如下)
>(zero (or near-zero) curvature implies that the nodes are locally embeddable in a flat surface (as in a grid or regular lattice))

- $<0$ 意味着两个顶点各自的邻接点相当远

不幸的是，OR curvature计算复杂度很高。于是看我们的吧。

### Curvature Metrics

**Olliver-Ricci curvature**

对

- 无向图$G = (V,E), |V|=n$
- 无self-loops
- edge $(i, j) \in E$

OR curvature定义为

$$k(i,j) = 1 - W(m_i, m_j)$$

- W(m_i, m_j)是Wasserstein distance，或者表示两个概率度量之间的optimal mass transport cost。对每个顶点$i$，$m_i$是像下面的集合：
$$
m_i(k)=
\begin{cases}
    \frac{1}{d_i} & \text{if } (i, j) \\
    0 & \text{otherwise}
\end{cases}
$$
$m_i$表示


**generalized Jaccard Curvatures**

$\mathscr {N}_i(i,j) = \{ k \in V \setminus \{j\} \ | \ (i,k) \in E \}.$
