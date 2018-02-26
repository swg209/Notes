## Bayesian decision theory

- 本章先介绍一些基本定义，然后开始拓展

### 基本定义

**Bayes' theorem**

$$P(A|B)=\frac{P(A) \times P(B|A)}{P(B)}$$

- $P(A)$称为**先验概率或边缘概率**，之所以称为先验是因为它不考虑B方面的因素
- $P(A|B)$是已知B发生的情况下A的概率，也由于得自B的取值而被称之为**A的后验概率**
- $P(B)$称为**先验概率或边缘概率**，之所以称为先验是因为它不考虑A方面的因素
- $P(B|A)$是已知A发生的情况下B的概率，也由于得自A的取值而被称之为**B的后验概率**

<br />

**现假设：**

有N个类，$Y=\{c_1, c_2, ... , c_N\}$，$\lambda_{ij}$是将类$c_j$误分类为$c_i$所产生的损失，则 **expected loss(期望损失)，也就是conditional risk(条件风险)** 为：

$$R(c_i|x) = \sum_{j=1}^{N} \lambda_{ij} P(c_j|x) \tag{1}$$

- >Expected loss is the sum of the values of all the possible losses, each multiply by the probability of that loss occurring
- 但是(1)式想表达的是，将$x$分类为$c_i$所产生的loss，所以应该是所有其他本应分类为$c_j$的样本误分类为$c_i$所产生的loss的期望。

**我们的任务是：**

找到$h: X \mapsto Y$，以最小化总体风险

$$R(h)=E_x [R(h(x)|x)]$$

由此产生 **Bayes decision rule(贝叶斯判定准则)**：为最小化总体风险，只需在每个样本上选择能够使$R(c|x)最小的类别标记，即:$

$$h^* (x) = \mathop{arg\ min}\limits_{c \in Y} R(c|x)$$

- $h^* $被称为**Bayes optimal classifier(贝叶斯最优分类器)**
- $R(h^* )$被称为**Bayes risk(贝叶斯风险)**
- $1-R(h^* )$是分类器所能达到的最好的性能，也是理论上限

**令：**

$$
\lambda_{ij} = \begin{cases}
0, \ if \ \ i = j; \\
1, \ otherwise.
\end{cases}$$

则

$$R(c|x) = 1 - P(c|x)$$

- 其中$c$为x的真实类别

**上面的任务等价为找到$h^* (x)$，使得**

$$h^* (x) = \mathop{arg\ max}\limits_{c \in Y} P(c|x)$$

---

### 生成式模型 vs 判别式模型

之前一直分不清两种模型的区别，因为在我看来，两种模型都能够通过贝叶斯公式统一起来。看了西瓜书才明白区别在哪。
