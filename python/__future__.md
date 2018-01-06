## \_\_future\_\_

有时我们会看到程序最开头有：`from __future__ import xxx`，它的作用是将更高级的python版本的语言特性xxx包含进来

比如说，

```python
# In python2
a = 23/6  # a = 3, / 是整除

# In python3
a = 23/6  # a = 3.833333333, / 是精准除法
a = 23//6  # a = 3, // 是整除
```

当我们要在低版本python中使用高版本的特性，在文件开头加上`from __furture__ import division`就可以了

```python
from __furture__ import division

# In python2
a = 23/6  # a = 3.833333333
```
