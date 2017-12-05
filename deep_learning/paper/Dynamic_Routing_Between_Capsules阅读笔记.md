[toc]

## Intro

- 联系方式：wjy.f@qq.com

由于涉及比较多的公式，而github不支持MathJax或者LaTeX，所以如果想获得更好的阅读体验请安装chrome插件[GitHub with MathJax](https://chrome.google.com/webstore/detail/github-with-mathjax/ioemnmodlmafdkllaclgeombjnmnbima)，或者有更好的方法恳请告知。

本文记录了阅读[《*Dynamic Routing Between Capsules*》](https://arxiv.org/pdf/1710.09829)的理解与收获，若有错误欢迎指出。转载请注明出处。

为了对文章有个大概的认识，先来介绍模型的结构，再结合代码理解实现。



## Main

### CapsNet

<br>

#### 结构概述

论文仅仅是提出了一个可行的方案，目的是为了证明`Capsule`这个思想的可行性，目前还较为粗略，有很多改进空间。下图是论文中所采用的神经网络结构：

![](./img/capsule_figure1.png)

看完这幅图应该大概能理解CapsNet的结构。它先是对图像用了两次卷积得到PrimaryCaps，然后用*Routing-By-Agreement Mechanism*得到DigitCaps。**TODO(DigitCaps后面那部分的说明)**。`Capsule`指的就是PrimaryCaps中长度为8的向量，共有`32*6*6`个Capsule。之所以称之为Capsule是因为在计算最终的输出——DigitCaps的时候，是将一个长度为8的向量当做一个整体来计算的。详细的计算过程后面会讲。

在得到DigitCaps

![](./img/capsule_decoder.png)

下面来详细讲讲CapsNet。

<br>

#### image $\to$ ReLU Conv1

1. image(28 * 28)
<br>
2. img $\to$ `Conv(num_outputs=256, kernel_size=9, stride=1, padding='VALID') + ReLU` $\to$ Conv1(256 * 20 * 20)
<br>
3. Conv1 $\to$ `Conv(num_outputs=256, kernel_size=9, stride=2, padding="VALID") + ReLU` $\to$ PrimaryCaps(256 * 6 * 6)
  这里可能会有人奇怪图片为什么会画成(32 * 8 * 6 * 6)的形式，这是因为后面的路由算法是将一个长度为8的向量当做一个整体来计算的。

<br>

#### PrimaryCaps $\to$ DigitCaps

- 这部分讲解从PrimaryCaps $\to$ DigitCaps的计算过程，其中主要应用了*Routing-By-Agreement Mechanism*

**一张图表示他们之间的关系：**

<br>

![](./img/capsule_routing.png)

<br>

**公式**

$$\hat{u}_{j|i} = W_{ij}u_i \tag{1}$$

- $u_i(i \in [6*6*32])$： 表示PrimaryCaps的某个8D的Capsule
- $\hat{u}_{j|i}$： 论文中称之为低一层的capsules的“prediction vectors”

$$c_{ij} = \frac{exp(b_{ij})}{\sum_kexp(b_{ik})} \tag{2}$$

- $b_{ij}$： 初始化为0，更新方法是 $b_{ij} \leftarrow b_{ij} + \hat{u}_{j|i} \cdot v_j$。 其中，$a_{ij} = \hat{u}_{j|i} \cdot v_j$ 表示 $capsule_j$ 的输出 $v_j$ 跟 $capsule_i$ 的prediction vector的agreement（相似度）。**值越大，表示两个向量的方向越相似，两个向量所表示的性质越相近**。由$c_{ij}$的公式知，$b_{ij}$ 的值越大（也就是两个向量的方向越相似），**$capsule_i$ 越倾向于将信息传送给 $capsule_j$** 。
- $c_{ij}$： 由动态路由算法更新的coupling coefficients，并且$\sum_{i}c_{ij} = 1$

$$s_j = \sum_{i}c_{ij}\hat{u}_{j|i} \tag{3}$$

- $s_j$： $capsule_j$ 的所有input之和。

$$squash(s_j):v_j = \frac{\|s_j\|^2}{1+\|s_j\|^2}\frac{s_j}{\|s_j\|} \tag{4}$$

- $squashing()$： 非线性函数，保留了向量的方向，使长的向量越长，短的向量越短，并且长度都压缩在1之内
- $v_j$： $capsule_j$ 的output。在文章中应该就是指最后的输出DigitCaps，共有10个（因为有10个数字，即10类）Capsule。每个capsule有16维，每一维都代表着数字的某些属性（粗细、倾斜程度等等）。**向量的长度代表了当前输入是类k的概率**。

<br>

##### Margin loss

![](./img/cap_lossfunc.png)

- k： class k
- $m^+=0.9, m^-=0.1$
- $\lambda$ ：
  >The λ down-weighting of the loss for absent digit classes stops the initial learning from shrinking the lengths of the activity vectors of all the digit capsules. We use λ = 0.5.

- 如果输入的数字图像是class k，那么$T_k=1$
- | 示例 | 输入 | $\|v_k\|$ | $L_k$ |
  | -- | ---- | ----- | ----- |
  | TT | 数字k | 比较大 | 比较小 |
  | TF | 数字k | 比较小 | 比较大 |
  | FT | 非数字k | 比较大 | 比较大 |
  | FF | 非数字k | 比较小 | 比较小 |
- 可以看出，在假阳性和假阴性的示例中，loss的值比较大。

<br>

##### 算法流程

下面看公式和Procedure1应该能明白它是怎么一个处理过程了。

![](./img/procedure1.png)

**其中**，若 i 指某一个capsule ，那么 j 就是这个capsule的parent capsule。对下面的公式来说也是一样。

<br>

### 玄学

论文仅仅介绍了capsule初步简单的实现，让大家知道capsule是有效的。而其核心思想

CapsNet与tradictional neuron的对比（图片来自[naturomics](https://github.com/naturomics/CapsNet-Tensorflow)）：

![](https://github.com/naturomics/CapsNet-Tensorflow/raw/master/imgs/capsuleVSneuron.png)

论文有两个比较突出的创新点：

- 采用 routing-by-agreement mechainsm 决定两层capsule之间的连接以及参数$c_{ij}$的更新方式
- 用向量输出替代标量输出

```
这里写背景（为什么要这么构造模型，背后的神经科学知识)
```

<br>

### 存疑

* 32个PrimaryCaps用的是同一个conv吗？
* CapsNet与普通神经网络的区别
* 动态路由算法
* 实体在模型中是否会有所表现

<br>

### 代码阅读

[link](https://github.com/naturomics/CapsNet-Tensorflow)

代码中的实现流程如下

1. image(28*28)
2. img $\to$ `Conv(num_outputs=256, kernel_size=9, stride=1, padding='VALID') + ReLU` $\to$ Conv1(256 * 20 * 20)
3. Conv1 $\to$ `Conv(num_outputs=256, kernel_size=9, stride=2, padding="VALID") + ReLU` $\to$

<br>

- CONV1_LAYER<br>

>conv1 = tf.contrib.layers.conv2d(self.X,num_outputs=256, kernel_size=9, stride=1, padding='VALID')

<br>

- PRIMARYCAPS_LAYER<br>

>primaryCaps = CapsLayer(num_outputs=32, vec_len=8, with_routing=False, layer_type='CONV')
caps1 = primaryCaps(conv1, kernel_size=9, stride=2)

在CapsLayer的实现的CONV中，使得输出为“self.num_outputs * self.vec_len”，问题是，这个设定是否意味着有num_outputs*vec_len个filter？

是的。

<br>

- DIGITCAPS_LAYER<br>



<br>

- def squash(vector)

计算过程：

```
# 将vector^2后，再将倒数第二维全部加起来
vec_squared_norm = tf.reduce_sum(tf.square(vector), -2, keep_dims=True)
```
$$scalar = \frac{vecsqnorm}{(1+vecsqnorm)\sqrt{vecsqnorm+epsilon}}$$

跟论文的公式一样

<br>

- def routing(input, b_IJ)

| Variable | shape |
| -------- | ----- |
| input | (128, 1152, 1, 8, 1) to (128, 1152, 10, 8, 1) |
| W | (1, 1152, 10, 8, 16) |
| b_IJ | (128, 1152, 10, 1, 1) |

函数的思路如下所示

```python
# 难道这个令人窒息的操作是传说中的权重共享？
W (1, 1152, 10, 8, 16)
---tile--->
W (128, 1152, 10, 8, 16)

input (128, 1152, 1, 8, 1)
---tile--->
input (128, 1152, 10, 8, 1)

u_hat = matmul(W, input)    (128, 1152, 10, 16, 1)
u_hat_stopped               (128, 1152, 10, 16, 1)

for r_iter in range(迭代次数):
  # b_IJ (128, 1152, 10, 1, 1)
  # 对b_IJ的第三维做softmax
  c_IJ = softmax(b_IJ, dim=2)   (128, 1152, 10, 1, 1)

  if 最后一次迭代：
    s_J = c_IJ * u_hat          (128, 1152, 10, 16, 1)
    reducesum(s_J, axis=1)      (128, 1, 10, 16, 1)
    v_J = squash(s_J)

  if 不是最后一次迭代（这部分和Procedure1的第7步一样）：
    s_J = c_IJ * u_hat_stopped  (128, 1152, 10, 16, 1)
    reduce_sum(s_J, axis=1)     (128, 1, 10, 16, 1)
    v_J = squash(s_J)
    v_J_tiled = tf.tile(v_J, [1, 1152, 1, 1, 1])     (128, 1152, 10, 16, 1)
    u_produce_v = u_hat_stopped_T * v_J_tiled        (128, 1152, 10, 1, 1)
    b_IJ += u_produce_v


```

<br>

- Masking

设DigitCaps的输出结果为x，batchsize=128，则Masking所做的是：

将这部分是要用ground truth的onehot vector与DigitCaps的输出做element-wise multiply(mask)，得到masked_v(128, 10, 16)，然后求DigitCaps的输出向量的长度，得到v_length(128, 10, 1, 1)

<br>

- Decoder

这里将Masking得到的masked_v拉成一维向量(128, 160)，放入fc1层(nun_outputs=512)，得到的结果再放入fc2(num_outputs=1024)，得到的结果再放入fc3(nun_outputs=784, activation_fn=sigmoid)，最后得到decoded，这个decoded就可以reshape一下得到重构的图像。

<br>

**def loss**

- margin_loss

![](./img/cap_lossfunc.png)

- reconstruction loss

将x(128, 28, 28, 1)reshape成orgin(128, 784)
squared = tf.square(self.decoded - orgin)
self.reconstruction_err = tf.reduce_mean(squared)

- 总的loss

total_loss = margin_loss + reconstruction_err * cfg.regularization_scale

<br>

**main**

num_batch = 468
num_test_batch = 78
