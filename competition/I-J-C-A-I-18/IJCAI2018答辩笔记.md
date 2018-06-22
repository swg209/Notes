## 队伍1

### 数据划分方式

1. 用第7天上午训练

![](assets/IJCAI2018答辩笔记-e3673.png)

优点：训练数据的分布十分接近下午测试数据的分布
缺点：这个题目是个时序问题，这样划分体现不了如小时啊这种时间特征

2. 前七天也用来训练

![](assets/IJCAI2018答辩笔记-2a297.png)

优点：与第一种划分方式互补，可以体现小时特征
缺点：前七天数据分布与双十一差距比较大

所以两种方式都使用，最后做融合

### 数据清洗

**缺失值处理两个方面**

- 连续值：均值
- 离散值：众数/中位数

**具体**

1. 同一商品一天有两种销量，-1和5，-1是缺失值，用5填充
2. 同一用户出现多次，有些数据里面的属性值有缺失，用该用户数据的非缺失值的众数代替
3. train和test分布差异小的-1属性值保留（城市、品牌）

### 特征工程

**数据处理**

![](assets/IJCAI2018答辩笔记-04bba.png)

- 有些模型需要做归一化所以要做归一化


![](assets/IJCAI2018答辩笔记-e3943.png)

- 这里将时间分为上午下午晚上，可以避免对小时的过拟合，增加鲁棒性
- 可以看到，离散之后，店铺评价与转化率呈很好的线性关系，鲁棒性强
- 离散之后可以做交叉特征

![](assets/IJCAI2018答辩笔记-17b08.png)

- 提取实体，其实远远不止这五种实体
- 有了实体，就可以方便地结合业务场景想它们之间的交互，想特征
- 重视用户的点击，即使不发生购买但是反映倾向

组合特征

![](assets/IJCAI2018答辩笔记-7c34c.png)

![](assets/IJCAI2018答辩笔记-d1683.png)

rank特征是这样的，比如说这个商品，在衣服这个类目中，按销量排序是第34位，做归一化34/1000=0.034，这个就是我们得到的新的rank特征，这个体现了销量或者价格在整个序列中的位置

![](assets/IJCAI2018答辩笔记-ba2ed.png)

转化率

使用滑动窗口，统计前七天的，前几个小时的

![](assets/IJCAI2018答辩笔记-f7bba.png)

![](assets/IJCAI2018答辩笔记-1c269.png)

![](assets/IJCAI2018答辩笔记-7d1a2.png)

![](assets/IJCAI2018答辩笔记-c47a1.png)

将双十一当天的样本权重加大

![](assets/IJCAI2018答辩笔记-bd5b7.png)

![](assets/IJCAI2018答辩笔记-d8ea8.png)

![](assets/IJCAI2018答辩笔记-49d0f.png)

---

![](assets/IJCAI2018答辩笔记-0b34a.png)

![](assets/IJCAI2018答辩笔记-46b97.png)

![](assets/IJCAI2018答辩笔记-b3ec5.png)

![](assets/IJCAI2018答辩笔记-cfe28.png)

用户对某个属性搜索几次，所有用户对某个属性搜索几次

![](assets/IJCAI2018答辩笔记-38045.png)

![](assets/IJCAI2018答辩笔记-cc4cd.png)


### 个人总结

**数据划分**：

两种结合要比单单使用7号的要好。但是单用0-10点提取特征有可能捕捉不到下午和晚上的分布。

**特征工程亮点**：

- 对时间做binning，分为上午下午晚上，避免对小时的过拟合
- 离散之后，店铺评价与转化率呈很好的线性关系，鲁棒性强。这个是我没料到的。
- 对item的商品和品牌做了转化率
- 使用了xgb的权重设置
- 在predict_category_property上，构建了统计、组合、比值特征
- 时间粒度划分得很细（10分钟、30分钟、1小时、2小时）

---

强东队

![](assets/IJCAI2018答辩笔记-4021b.png)

![](assets/IJCAI2018答辩笔记-00389.png)

![](assets/IJCAI2018答辩笔记-e78ef.png)

![](assets/IJCAI2018答辩笔记-96ae6.png)

![](assets/IJCAI2018答辩笔记-d40d1.png)

![](assets/IJCAI2018答辩笔记-2c768.png)

![](assets/IJCAI2018答辩笔记-96615.png)

连乘容易导致梯度爆炸和梯度消失，可以通过乘以log解决

![](assets/IJCAI2018答辩笔记-712ef.png)

![](assets/IJCAI2018答辩笔记-645b2.png)

![](assets/IJCAI2018答辩笔记-8bcd6.png)

![](assets/IJCAI2018答辩笔记-9ea50.png)

![](assets/IJCAI2018答辩笔记-91fa2.png)

### 个人总结

**亮点**

- 这个解决方案重点在深度学习上
- 一个模型大融合
- 觉得还有改进空间，比如说答辩选手提到训练数据不够。可以用第一名的迁移学习解决。
- 答辩中提到的DL模型调试的trick值得一学

---

躺分队

![](assets/IJCAI2018答辩笔记-ca3fc.png)

![](assets/IJCAI2018答辩笔记-b2159.png)

![](assets/IJCAI2018答辩笔记-29a42.png)

![](assets/IJCAI2018答辩笔记-9567c.png)

![](assets/IJCAI2018答辩笔记-a00c8.png)

![](assets/IJCAI2018答辩笔记-e2cef.png)

![](assets/IJCAI2018答辩笔记-3cada.png)

![](assets/IJCAI2018答辩笔记-206bd.png)

采用acc与logloss两种验证方法，当两个指标都同时变好的时候，就采用这个特征。这在比赛中取得了线上线下同增减。

![](assets/IJCAI2018答辩笔记-b4ac5.png)

![](assets/IJCAI2018答辩笔记-7d566.png)

![](assets/IJCAI2018答辩笔记-87dc0.png)

![](assets/IJCAI2018答辩笔记-0b5e6.png)

![](assets/IJCAI2018答辩笔记-dc647.png)

![](assets/IJCAI2018答辩笔记-61c8c.png)

![](assets/IJCAI2018答辩笔记-b534d.png)

![](assets/IJCAI2018答辩笔记-42b6c.png)

![](assets/IJCAI2018答辩笔记-ff42b.png)

协同过滤？

![](assets/IJCAI2018答辩笔记-314b4.png)

![](assets/IJCAI2018答辩笔记-cb121.png)

![](assets/IJCAI2018答辩笔记-47781.png)



---

禁止实习咋找工作

![](assets/IJCAI2018答辩笔记-4ce2a.png)

![](assets/IJCAI2018答辩笔记-0676d.png)

![](assets/IJCAI2018答辩笔记-923f6.png)

![](assets/IJCAI2018答辩笔记-98b99.png)

![](assets/IJCAI2018答辩笔记-2bbac.png)

![](assets/IJCAI2018答辩笔记-3512b.png)

![](assets/IJCAI2018答辩笔记-bb59e.png)

![](assets/IJCAI2018答辩笔记-20e1c.png)

![](assets/IJCAI2018答辩笔记-92bfe.png)

![](assets/IJCAI2018答辩笔记-413ed.png)

![](assets/IJCAI2018答辩笔记-648fa.png)

![](assets/IJCAI2018答辩笔记-e9b32.png)

---

learner_ctr

![](assets/IJCAI2018答辩笔记-3e15e.png)

![](assets/IJCAI2018答辩笔记-18d28.png)

![](assets/IJCAI2018答辩笔记-c469b.png)

![](assets/IJCAI2018答辩笔记-04acc.png)

![](assets/IJCAI2018答辩笔记-604ce.png)

![](assets/IJCAI2018答辩笔记-da214.png)

![](assets/IJCAI2018答辩笔记-f7e2c.png)

![](assets/IJCAI2018答辩笔记-e264d.png)

![](assets/IJCAI2018答辩笔记-d6c03.png)

![](assets/IJCAI2018答辩笔记-af9e4.png)

![](assets/IJCAI2018答辩笔记-04d1e.png)

![](assets/IJCAI2018答辩笔记-29457.png)

![](assets/IJCAI2018答辩笔记-f4b47.png)

![](assets/IJCAI2018答辩笔记-4cfd1.png)

![](assets/IJCAI2018答辩笔记-775c0.png)

![](assets/IJCAI2018答辩笔记-54270.png)

![](assets/IJCAI2018答辩笔记-cdd3c.png)

---

蓝鲸烧香队

![](assets/IJCAI2018答辩笔记-3ba99.png)

![](assets/IJCAI2018答辩笔记-9bed9.png)

![](assets/IJCAI2018答辩笔记-d1948.png)

大部分都是一次点击然后就买了的，说明是即时兴趣，目标明确

![](assets/IJCAI2018答辩笔记-313d4.png)

提取出现次数最多的top10 property。第一个property作为一个特征，第一第二个拼接作为第二个特征。。。如此得到10个新特征

而对于predict_category_property来说，是取去最先出现的前十个，如上构造新特征

item一级类目做一个特征，二级类目做一个特征

![](assets/IJCAI2018答辩笔记-65b5a.png)

可以看到，前6天的各个小时点击数的趋势是差不多的，几乎重合。所以小时也很重要的

![](assets/IJCAI2018答辩笔记-2c081.png)

![](assets/IJCAI2018答辩笔记-274dc.png)

将时间信息模型的预测结果作为特征给前两个模型

![](assets/IJCAI2018答辩笔记-a1427.png)

![](assets/IJCAI2018答辩笔记-637e8.png)

![](assets/IJCAI2018答辩笔记-b882a.png)

![](assets/IJCAI2018答辩笔记-23856.png)

![](assets/IJCAI2018答辩笔记-e7dd8.png)

![](assets/IJCAI2018答辩笔记-ce336.png)

![](assets/IJCAI2018答辩笔记-4b4e4.png)

![](assets/IJCAI2018答辩笔记-63662.png)

![](assets/IJCAI2018答辩笔记-6ef22.png)

![](assets/IJCAI2018答辩笔记-56687.png)

用cvr乘以a调整最后的答案（就是那个调整）
