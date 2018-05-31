# SPECTRAL CAPSULE NETWORKS

## Methodology

诊断任务是一个多变量时间序列分类任务，我们需要根据患者的生命体征和实验结果预测患者的疾病。这是多标签分类任务，即患者可被诊断为有多种疾病或没有疾病。

#### Step1: Extracting features

首先，我们使用一维卷积提取出要给capsule处理的维度更低的特征。我们使用一种方法增加了卷积的感受域，而且减少了输入的层数和参数。最后我们将residual network的输出拉平为一个120维的向量给capsule层处理。

#### Step2: Primary capsuel

在这两种结构中，我们对每个capsule使用两个dense residual networks
