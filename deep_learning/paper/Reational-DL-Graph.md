[toc]

# Relational inductive biases, deep learning, and graph networks

## Abstract

AI的复兴一定程度是因为便宜的数据和便宜的计算资源。目前仍有许多挑战，比如说在一个人的经验之外的归纳学习。

我们认为组合概括是AI首要实现的能力。我们探索如何在深度学习体系结构中使用关系归纳偏差（*relational inductive biases*）来促进学习实体、关系和组成它们的规则。我们提供了一个图网络相关的工具包，这个工具包概括和拓展了各种graph上的操作和方法，并且提供简单直接的接口去操纵结构化知识和产生结构化行为。我们讨论图网络如何支持关系推理和组合泛化，为更复杂、可解释性更强和更灵活的推理模式奠定基础。

## 1 Introduction

人类的组合概括能力的关键在于对认识实体和关系推理。

1. 我们将复杂的系统表示为实体和它们相互作用的组合，例如判断一堆随意叠放的物体是否稳定（Battaglia et al., 2013）
2. 我们使用层次结构来抽象细粒度差异，并捕抓表示和行为之间更一般的共性，例如对象的部分，场景中的对象，城镇中的邻域和一个国家的城镇 (Botvinick, 2008; Tenenbaum et al., 2011)
3. 我们根据组合熟悉的技能和惯例去解决新的问题，例如组合已有的过程得到新的过程——“乘飞机旅行”、“去圣地亚哥”、“在...吃”、“一个印度餐厅”（Anderson, 1982）
4. 我们通过对齐两个域之间的关系结构来绘制类比，并基于另一个域的相应知识得出关于一个域的推论 (Gentner andMarkman, 1997; Hummel and Holyoak, 2003)

世界是组合的，至少我们用组合的方式去理解世界。当我们学习新知识的时候，我们会将新知识放入已有的知识体系中，或者调整知识体系使得可以兼容新旧知识(Tenenbaum et al.,2006; Griths et al., 2010; Ullman et al., 2017)

所以核心问题就是如何搭建拥有组合推广能力的系统（Chomsky, 1957; Nilsson and Fikes, 1970; Pearl, 1986, 2009; Russell andNorvig, 2009; Hjort et al., 2010; Goodman et al., 2012; Ghahramani, 2015）。 整个子领域专注于以实体和关系为中心的学习，例如关系强化学习（Dzeroski et al., 2001）和统计关系学习（Getoor and Taskar, 2007）。结构化方法在以前的时代对于机器学习如此重要的一个关键原因部分是因为数据和计算资源很昂贵，并且结构化方法强大的归纳偏差所带来的改进的样本复杂性非常有价值。

与过去的人工智能方法相比，现代的深度学习方法常常是“end-to-end”的，这类方法带有很小的的先验和假设，

—— 行吧太多了有时间再看


### Box 1: Relational reasoning

定义 *structure* 是由已知模块以一定的组合方式构成的，*structured representations* 表示这种组合方式，*structured computations* 是以整体为单位的操作，那么，关系推理涉及如何利用组合的规则区去操作实体与关系组成的结构化表示。

- *entity* 是有属性的，例如物体有体积和质量
- *relation* 是两个实体之间的，例如“与...大小相等”、“距离...多远”
- *rule* 是一个函数，将实体与关系映射到另一对实体和关系，例如
    ```
    if y.size > x.size and y.weight > x.weight:
        return True
    else:
        return False
    ```
    它考虑一个或多个参数和规则>，返回一元属性值

机器学习中关系推理的示例： graphical models（Pearl,1988; Koller and Friedman, 2009）可以使随机变量之间条件独立来表示复杂的联合分布。这些模型之所以成功，是因为它们捕获了稀疏结构，这种结构是许多现实生成过程的基础，并且因为它们支持用于学习和推理的高效算法。例如，隐马尔可夫模型约束潜状态在条件上独立于其他状态给出前一时间步的状态，并且观察在条件上独立于给定当前时间步的潜状态，这与许多现实世界因果过程的关系结构非常匹配。明确表达稀疏依赖性



## 2 Relational inductive biases

许多有关系推理能力的模型用的就是 *Relational inductive biases*（关系归纳偏差）。作为一个不正式的定义，这个术语一般是指 Box 2 中的inductive biases。

近几年产生了许多新的机器学习模型——由几个已知模块拼接、叠加多层、变得更深。这些不同的组合表示了特定类型的 *Relational inductive biases*，而且是分层处理的。其中计算是分阶段执行的，通常导致输入信号中的信息之间的长距离交互。也就是说，构建模型的每个块本身也带有各种 *Relational inductive biases*（表1）

### Box 2: Inductive biases

学习是一个通过观察和与外界互动来理解知识的过程，包括在解空间中找到较好的解。但是有时会有几个同样好的解存在。*inductive bias* 能使得某个解优于另一个解（Mitchell,1980）。在贝叶斯模型中，*inductive bias* 通过先验分布的选择和其参数来表示。在其他情况中，它也有可能是一个正则项，或者是包含在算法的体系结构中。*inductive bias* 可以提高在提高样本复杂度中提供灵活性，并且可以依据方差-偏差权衡的方式来理解(Geman et al.,1992)。理想情况下，*inductive bias* 可以改善对解的选择，又不会显著降低性能，也能帮助找到理想的泛化能力可以的解。但是，不匹配的 *inductive bias* 会因为引入了过大的约束而使得效果次优。

*Inductive bias* 可以表达数据生成过程或解空间的假设。例如，当我们用一元函数拟合数据时，线性最小二乘是在“得到的模型是线性模型”这个约束下去拟合的，误差应该是二次惩罚下的最小值。这反映了一种假设，数据生成过程中，线性性加上了高斯噪声，得到最终的数据。类似的，L2正则项使得我们优先选择参数小的解，并且在不同的问题得到不同的解和全局结构。

所以总的来说，这个东西可以使得解之间的差异性变大，那么我们在找最优解时也容易些。注意这些假设不一定是明确的，他们反映了模型或算法如何解释世界的方式

那么他是如何实现关系推理的？

- rule functions的参数（例如将那个实体或者关系作为输入）
- rule functions如何在计算图中被使用和共享的（例如通过不同的 *entities* 和 *relations*，通过不同的时间或者不同的步骤）
- 体系结构如何定义 *interaction* 和 *isolation* （例如将多个相关实体一起处理，而不是单独处理）

### 2.1 Relational inductive biases in standard deep learning building blocks

#### 2.1.1 Fully connected layers

*entities* 即网络中的神经元，*relations* 是all-to-all，*relational inductive bias* 比较弱，因为所有的输入单元都可以相互作用以确定输出单元的值，并且独立于输出。

#### 2.1.2 Convolutional layers

*entities* 即网络中的神经元或者说像素点，*relations* 是稀疏的，*relational inductive bias* 是locality和translation invariance的。locality是指filter所覆盖的像素区域，反映了像素跟周边的像素关系比较强，与远的像素关系比较弱。Translation invariance反映了跨区域对输入应用相同的规则（例如应用同一个filter）。这些 *biases* 对于处理图像非常有效，因为在局部邻域内存在高协方差，随着距离增大协方差减小。

#### 2.1.3 Recurrent layers

*entities* 即每一时刻的输入和隐藏状态，*relations* 是当前时刻的隐藏状态与前一时刻的隐藏状态和输入有关，*rule* 是每一时刻的隐藏状态与前一时刻的隐藏状态和输入有关 *relational inductive bias* 是 *rule* 所反映出的时间不变性

### 2.2 Computations over sets and graphs

有深度学习工具包包含了各种 *relational inductive biases* ，但是没有可以在任意关系结构中操作的深度学习组件。我们需要具有明确表示 *entities* 和 *relations* 的模型，并且需要能够找出它们的 *interactions* 的算法。更重要的是 *entities* 在现实中是没有顺序的。相反，可以由它们之间关系的属性来定义顺序。例如，物体的大小之间的 *relations* 可以用来排序。除了面向属性关系外，还有排序不变性，它是一种能够通过关系推理中的深度学习组件反映的属性。

现有一个表示系统的集合，是由无序的或者不相关的 *entities* 表示的。它们的 *relational inductive biases* 不是来自某事物的出现，而是来自于存在。举个例子，现有一个由n个行星（$\{x_1, x_2, ... , x_n\}$）组成的太阳系，我们需要预测其质心。在这个任务中，我们先考虑哪个行星的顺序并不重要，因为质心只能用相加的、平均的数量来描述。但是，如果我们使用MLP做这个任务，输出就和输入的顺序有关了。MLP会考虑所有的组合（$n!$），因此计算复杂度是指数性增长的。为了处理这种组合爆炸的情况，可以使用对称函数处理，例如求均值，或者Deep Set model (Zaheer et al., 2017) ，Section 4.2.3会讲。

当然，排列不变性不是唯一重要的形式，还有成对相互影响这种形式。

## 3 Graph networks

接下来，3.1会介绍关于图模型的背景文献，剩下的小节介绍图网络框架。

### 3.2 Graph network (GN) block

我们提出图网络框架，定义了一类函数用于基于图结构的关系推理。我们的框架概括和拓展了各种图神经网络，MPNN，NLNN方法，并且支持利用简单的模块构建复杂的结构。注意，我们避免在“graph network”使用“neural”这个词，因为我们还可以用神经网络以外的函数来实现。

GN框架中的主要计算单元是GN块，它是一个“graph-to-graph”的模块，将图作为输入，然后计算并输出图。Box 3描述了基本术语的定义。GN框架强调可定制性，能将模块组合成表示所需的 *relational inductive biases* 的新架构。设计的关键原则是：灵活的表示、可配置的模块结构、能用模块组合的结构


#### Box 3: Our definition of "graph"

- “graph”表示图
- “$v_i$”表示节点
- “$e_k$”表示边
- “u”表示全局属性
- “$s_k$、$r_k$”分别表示边k上的发送节点、接受节点
- Directed 有向边
- Attribute 能被表示为向量、集合、甚至是图的属性
- Attributed 与边、顶点相关联的属性
- Global attribute graph-level 的属性
- Multi-graph 顶点间可以有多个边，包括自连接的边
- graph 表示为 $G=(u, V, E)$，$V=\{v_i\}_{i=1:N^v}$，$v_i$是节点的属性；$E=\{(e_k, r_k, s_k)\}_{k=1:N^e}$，$e_k$是边的属性。
- $E^{\prime} = \cup_i E^{\prime}_i = \{(e^{\prime}_k, r_k, s_k)\}_{k=1:N^e}$
- $E^{\prime}_i = \{(e^{\prime}_k, r_k, s_k)\}_{r_k=i,k=1:N^e}$
- $\rho$将一个集合作为输入，输出表示聚合信息的单个元素
- $\phi^?$是用于更新信息的函数，比如$\phi^e$是用于更新变得信息的。重要的是，它必须对其输入的排列不变，并且参数数量可变（例如，元素求和，平均值，最大值等）

#### 3.2.2 Internal structure of a GN block

一个GN模块中包含三个可更新函数，$\phi$，三个加法函数，$\rho$


#### 3.2.3 GN模块中的计算步骤

图3描述了每个计算中涉及那些图元素，图4a描述了一整个GN模块的更新和聚合函数，算法1描述了以下计算步骤

图3主要讲先更新边，再更新节点，然后更新全局属性


#### Algorithm 1

简单来说

1. 更新各个边的状态，输入为边，边上节点，全局属性，得到$e^{\prime}$
2. 对每个顶点，都有一个或多个给它传消息的顶点，所以将{(边、接受顶点、发送顶点)}作为集合，记为$E^{\prime}_i$
  将集合$E^{\prime}_i$的信息聚合，得到以顶点i为接收点，相关的边信息的集合$\text{\={e}}^{\prime}_i$
3. 以$\text{\={e}}^{\prime}_i,v_i,u$作为输入，更新顶点，得到$v^{\prime}_i$
4. 后面就是利用已更新顶点的信息、已更新边的信息，去更新全局属性

3.2.4 Relational inductive biases in graph networks

我们的GN框架

首先，graph可以表示 *entities* 之间的任意关系，这意味着输入决定了 *entities* 之间的关系，而不是模型体系结构决定的。

第二，graph将 *entities* 和它们之间的关系表示为集合，这些集合的排列是不变的。这意味着GN对于这些元素的顺序是不变的。例如，场景中的物体没有自然顺序。

第三，GN上的每条边和每个节点的函数是复用的，这意味着GN支持一种组合泛化形式（Section 5.1）：单个GN可以应用在不同size的graph上。

## 4 Design principles for graph network architectures

通常，框架于特额定的属性和函数形式无关，然而这里我们主要关注深度学习的架构，它使得GNs能够学习到graph-to-graph的函数逼近。

### 4.1 Flexible representations

GNs可以通过两种方式灵活地表示图表达：1.通过属性 2.通过图的结构

#### 4.1.1 Attributes

GNs模块中的全局的，节点的、边的属性可以用任意格式表达。例如向量、tensors、序列、集合或者图

输出也可以根据具体任务改动：

- edge-focused的GN可以将边作为输出，例如根据 *entities* 之间的关系做决策
- node-focused的GN可以将节点作为输出，例如物理系统中的关系推理
- graph-focused的GN可以将全局信息作为输出，例如预测物理系统的能量、分子的性质

#### 4.1.2 Graph structure

在定义输入数据如何表示为图时，有两种情况

1. 输入明确指定关系结构，例如知识图、社交网络、解析树、化学图、道路网络等
2. 必须推断或假设关系结构，例如视觉场景、文本语料库、编程语言源码，这些场景中，数据可以被格式化为没有关系的一组实体，或甚至仅仅是矢量或张量。

### 4.2 Configurable within-block structured
