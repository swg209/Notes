# abstract   

### Collaborative filtering Algorithms

#### Memory-based model

##### User-based

1. 首先搜集用户的信息，比如用户对商品的评分，用户的购买记录和浏览记录

2. 用NNS(nearest neighbor search最近邻搜索)。做法是查找n个与A有相似兴趣的用户，把这n个用户对M的评分作为A对M的评分的预测

3. 根据2的最邻近集合，查找n个用户里面出现频率top-N的，而A用户的评分项目里面没有的项，推荐给A

这个方法在用户数量增多之后，计算时间会越来越长

##### Item-based



#### 问题

* 什么是Interation data
* standard collaborative filtering benchmarks

### 2

#### 问题

* first-order neighborhood
