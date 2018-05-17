# LightGBM: A Highly Efficient Gradient BoostingDecision Tree

## Abstract

虽然目前已经有比较高效的GBDT实现，如XGBoost和pGBRT，但是在特征维度很高数据量很大的时候依然不够快。一个主要的原因是，对于每个特征，他们都需要遍历每一条数据，对每一个可能的分割点去计算信息增益。为了解决这个问题，本文提出了两个新技术：*Gradient-based One-Side Sampling*(GOSS)和*Exclusive Feature Bundling*(EFB)
