可以使自定义类像函数一样被调用

```python
class Entity:
'''调用实体来改变实体的位置。'''
  def __init__(self, x):
      self.x = x

  def __call__(self):
      '''改变实体的位置'''
      print('self.x:', self.x)

entity = Entity(1)
entity()

================================
output:
self.x: 1
```

详细资料：[这里](http://pycoders-weekly-chinese.readthedocs.io/en/latest/issue6/a-guide-to-pythons-magic-methods.html)
