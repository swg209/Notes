# Ad Click Prediction: a View from the Trenches —— KDD 2013


## INTRODUCTION

在这篇文章中，我们会展示一系列研究，这些研究是来自最近的部署系统的设置，这些部署系统是在Google中用来预测CTR的。

由于这个problem setting已经被充分研究，我们选择研究那些在working system中没什么人关注但是又同样地重要问题。因此，我们探索 节约内存，性能分析，预测的置信度，校准和特征管理

## BRIEF SYSTEM OVERVIEW

用户搜索$q$的时候，会基于advertiser-chosen keywords产生与$q$匹配的候选广告集，竞选机制决定那些广告会展示给用户，会以怎样的顺序展示，还有广告被点击后广告主应该付多少钱。除了广告主的竞价之外，一个对于竞选机制很重要的是，对每个ad $a$，$P(click|q, a)$的预测值是多少。这个概率表示了若广告$a$被展示，它被点击的概率有多大。

我们系统中用的特征是从各种source提取的，包括查询，广告文案和各种跟广告相关的元数据。这些特征会特别稀疏，通常每个数据只有很少的非零特征值。

像正则化的LR是很适合此类问题的，当新的点击或者不点击产生时，就需要更新模型。

我们用的一个跟Google Brain团队的Downpour SGD很像的方法，不同的是我们的是训练一层model，而不是多层的deep network。由于训练的模型需要被复制到许多数据服务中心，所以我们更关心的是serving过程中的稀疏性，而不是训练过程中的

下面就开始讲Online Learning FTRL

## 4.6 Subsampling Training Data

实际中的CTR一般远远低于50%，所以正样本远少于负样本。因此，正样本在CTR预估学习中更有价值。我们能够利用这一点显著地减少训练数据的大小，并最小化对acc的影响：

- 

## 后记

本以为后面的对自己帮助不大，后来发现还是有一些值得参考的地方的

---
