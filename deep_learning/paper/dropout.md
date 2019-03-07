---
html:
  embed_local_images: true
  embed_svg: true
  offline: false
  toc: true

print_background: true
---

# Dropout: A Simple Way to Prevent Neural Networks from Overfitting

## Abstract

dropout就是通过随机丢弃神经元来解决过拟合问题。

## Introduction

**为什么会过拟合？**

因为在数据量少的时候，神经网络强大的拟合能力会把训练数据的噪声也学习了，而在测试数据中并不存在这种噪声。即使训练集跟测试集都是从同一分布抽样也会出现这种情况。

**如何解决过拟合？**

1. early stoping：在验证集效果变差前停止训练
2. weight penalty：例如L1、L2正则化
3. soft weight sharing：Nowlan and Hinton 1992 权重共享？这个不了解

最好的解决办法是，将参数所有的可能性都列出来，将训练集给定的后验概率作为权重，然后加权得到最终的参数。
