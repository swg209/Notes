在[廖雪峰的python网站](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/00143186739713011a09b63dcbd42cc87f907a778b3ac73000)上，他是这么说的

```python
python是动态语言，它允许程序在执行过程中动态绑定属性或者方法（使用MethodTpye）。

某个实例在执行过程中绑定的属性跟方法，仅在该实例中有效，其他同类实例是没有的。
可以通过给class绑定属性/方法，来给所有实例绑定属性/方法：

Student.name = ''
Student.set_score = set_score

而如果使用__slots__，它仅允许动态绑定()里面有的属性
例如，下面这样会报错

class Student():
  __slots__ = ('name', 'age')

S1 = Student()
S1.name = 'Jack'  # ok!
S1.score = 123  # error!
```

但是我觉得很奇怪，仅有这一个作用吗？于是我再查了其他资料，发现这个函数可以很可观地节约内存，大概能节约40%~50%（详见[这里](https://eastlakeside.gitbooks.io/interpy-zh/content/slots_magic/)）

>在python中，它是使用字典来保存一个对象的实例属性的。这非常有用，因为它允许我们我们在运行时去设置任意的新属性。<br>
但是，这对某型已知属性的类来说，它可能是一个瓶颈。因为这个字典浪费了很多内存。<br>
python不能在对象创建的时候直接分配一个固定量的内存来保存所有属性，因此如果你有成千上万的属性的时候，它就会消耗很多内存。

有一个办法可以规避这个问题，就是使用```__slots__```来告诉python不要使用字典，而是只给一个固定集合的属性分配空间。

可以通过下面的例子来感受下：

```python
Python 3.4.3 (default, Jun  6 2015, 13:32:34)
Type "copyright", "credits" or "license" for more information.

IPython 4.0.0 -- An enhanced Interactive Python.
?         -> Introduction and overview of IPython's features.
%quickref -> Quick reference.
help      -> Python's own help system.
object?   -> Details about 'object', use 'object??' for extra details.

In [1]: import ipython_memory_usage.ipython_memory_usage as imu

In [2]: imu.start_watching_memory()
In [2] used 0.0000 MiB RAM in 5.31s, peaked 0.00 MiB above current, total RAM usage 15.57 MiB

In [3]: %cat slots.py
class MyClass(object):
        __slots__ = ['name', 'identifier']
        def __init__(self, name, identifier):
                self.name = name
                self.identifier = identifier

num = 1024*256
x = [MyClass(1,1) for i in range(num)]
In [3] used 0.2305 MiB RAM in 0.12s, peaked 0.00 MiB above current, total RAM usage 15.80 MiB

In [4]: from slots import *
In [4] used 9.3008 MiB RAM in 0.72s, peaked 0.00 MiB above current, total RAM usage 25.10 MiB

In [5]: %cat noslots.py
class MyClass(object):
        def __init__(self, name, identifier):
                self.name = name
                self.identifier = identifier

num = 1024*256
x = [MyClass(1,1) for i in range(num)]
In [5] used 0.1758 MiB RAM in 0.12s, peaked 0.00 MiB above current, total RAM usage 25.28 MiB

In [6]: from noslots import *
In [6] used 22.6680 MiB RAM in 0.80s, peaked 0.00 MiB above current, total RAM usage 47.95 MiB
```

参考：

https://eastlakeside.gitbooks.io/interpy-zh/content/slots_magic/
https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/00143186739713011a09b63dcbd42cc87f907a778b3ac73000
