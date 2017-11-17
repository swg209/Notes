# Structured Sequence Modeling with Graph Convolutional Recurrent Networks

[link](https://arxiv.org/abs/1612.07659)

## 2 Preliminaries

### 2.1 Structured Sequence Modeling

目标：根据前面 len = J 的可观察序列，预测未来 len = k 的 sequence

序列中的元素表示 observed features


# Code Reading

* 记录学习GCRN的代码时的收获

```python
程序流程记录

gcrn_main.py

if __name__
首先从 config.py 参数
执行main()

main()
创建需要用到的文件夹、初始化路径参数
创建trainer.py里面的Trainer实例
  - 里面首先初始化了参数
  - 然后使用utils.py里面的BatchLoader预处理数据文件
    这个BatchLoader做了如下操作：
      读取数据文件
      将数据里面的所有字符创造一个字典，将字符映射成数字
      得到Adj：
        for x, y in zip(train_data, train_data_shift):
          Adj[x, y] += 1
      将train、valid、test都放在了output里面
      将字符字典存了一个pkl文件
      所有数据存了一个pkl文件
      Adj矩阵存了一个pkl文件
      将数据分batch
    然后回到trainer.py
  - 将Adj作为参数矩阵W
  - W归一化
  -


```
