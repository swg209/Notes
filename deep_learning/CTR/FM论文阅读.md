# Factorization Machines

>论文读到一半查资料的时候发现一篇写得特别好的文章，转载于此，可以参考一下 [链接](https://www.cnblogs.com/pinard/p/6370127.html)

## Introduction

**SVM有以下缺点**

- SVM没法在稀疏数据下的复杂的（非线性）kernel spaces里学习可靠的参数（超平面）
- not applicable to standard prediction data(e.g. a real valued feature vector in $R^n$)
- 特定的模型只能用于特定的任务

**FM的优点**

- FM可以在稀疏数据下进形参数预估
- FM的算法复杂度是线性的
- FM是一个泛化的模型，可以用任何特征值作为输入。相反，其他state-of-the-art因式分解模型对输入数据要求很严格。

## Factorization Machines

### 1. Model Equation：

degree $d=2$的模型方程定义为：

$$\hat{y}(x) := w_0 + \mathop{\sum}^n_{i=1} w_i x_i + \mathop{\sum}^n_{i=1} \mathop{\sum}^n_{j=i+1} \langle \vec{v_i}, \vec{v_j} \rangle x_i x_j \tag{0}$$

- $w_0 \in \Bbb{R}, \ w \in \Bbb{R}^n, \  V \in \Bbb{R}^{n \times k}$
- $\langle \cdot ,\cdot \rangle $ 是点积运算，表示两个变量的交互关系。
- $w_0$是global bias
- $w_i$是第$i$个变量的强度

**重点讲讲第三项和 $\langle v_i, v_j \rangle $**

加入第三项的好处是考虑到了两个特征之间的关系

而使用内积的好处是：按普通来说，应该就是一个像第二项一样的参数$w_{ij}$，而FM用矩阵分解的形式去表示了这个参数。这样做的好处是，他会增强模型的表达能力。

### 2. Expressiveness

只要$k$足够大，FM可以通过交互矩阵$W$表达任何交互关系。然而在稀疏的数据中，应该将$k$设小一点，因为没有足够的数据去训练复杂的$W$。所以

- 如果是稀疏数据，应该将$k$设小一点。
- 适当地限制$k$的大小，以获得更好的泛化能力

### 3. Parameter Estimation Under Sparsity

一般来说，在数据很稀疏的情况下并不能很好地学习交互关系（interaction）。但是FM可以通过用矩阵分解的形式打破交互参数的独立性，从而即使得参数更好训练。

简单来说，原来的话$w_{ij}$只能被$x_i x_j$的信息训练，而现在 $\langle v_i, v_j \rangle $ 可以被$x_i x_j$训练，$\langle v_i, v_k \rangle $ 可以被$x_i x_k$训练，这样$v_i$就跟两个项有关系，所获得的信息自然比第一种要多，进而能够学习得更好。

至此就是FM的核心内容。
