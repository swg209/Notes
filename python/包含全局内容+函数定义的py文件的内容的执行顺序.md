假如有一个py文件如下

```python
# config.py

import argparse

parser = argparse.ArgumentParser()
arg_list = []

def get_config():
    config, unparsed = parser.parse_known_args()
    return config, unparsed
```

另一个py文件如下

```python
# gcrn_main.py
import numpy as np
from gconvRNN.config import get_config

if __name__ == "__main__":
    config, unparsed = get_config()
```

他们的*执行顺序*是这样的：

```
运行 gcrn_main.py
执行 import numpy as np
执行 from gconvRNN.config import get_config

跳转到 config.py

执行 import argparse
执行 parser = argparse.ArgumentParser()
执行 arg_list = []

然后运行到
def get_config()
这一行
跳转回 gcrn_main.py

执行 if
执行 get_config

跳转到 config.py

执行 get_config()
```

并且！

config.py 里面的全局变量```parser```是一直存在的！可以被```get_config()```调用的！
