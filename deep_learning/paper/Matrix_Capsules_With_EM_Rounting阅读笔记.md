## Matrix Capsules With EM Routing

### Abstract

Capsule是一组神经元，它的每个输出的维度表示entity不同的属性。本文我们描述了自己的一个capsule版本，这种capsule用logistic unit去表示entity，并且用4*4的可学习pose matrix表示entity和viewer之间的关系。某一层的一个capsule将自己的pose matrix与viewpoint-invariant transformation marrices相乘来向高一层的capsule vote。这样可以学习出局部-整体的关系。每一次vote都是用assignment coefficient去weighted的。这些coefficient通过EM算法更新，这样，每一个capsule的输出都会送到上面一层的capsule，这些上面一层的capsule会收到一簇相似的vote。整个系统是用3次层与层之间的EM算法迭代训练的。在smallNORB benchmark上，本文的方法相对于state-of-the-art的减少了45%的测试误差。Capsules相对于baseline的CNN来说更能抵抗white box adversarial attack。

### 1 Introduction

#### 1.1 Previous work on Capsules

指出了*Dynamic Routing Between Capsules*的几个不足之处：

- 用pose vector的长度来表示某个capsule是表示某个entity的概率。为了使长度小于1，需要unprincipled non-linearity的函数，以免在路由迭代过程中变成sensible objective function
- 用cosine表示两个pose vector的agreement。cosine不太好辨别quite good agreement和very good agreement。而the log variance of a Gaussian cluster在这方面就好一些。
- 使用了长度为n的向量，而不是用带有n个element的matrix去表示一个pose，因此，transformation matrices有$n^2$个参数而不是仅仅只有$n$个。

### Q

- A capsule is a group of neurons
