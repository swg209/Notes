# import文件夹A的py文件

* 要在A目录下新建__init__.py文件
* 将目录加进sys.path
* 文件结构如下
```
  test
    -- A
      -- __init__.py
      -- a.py
    -- B
      -- b.py
```
对b.py文件
```python
import sys
sys.path.insert(0, '..')
from A import a
```
