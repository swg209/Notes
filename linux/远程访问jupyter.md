# 远程访问jupyter notebook

* 环境 linux
* 转载于[点击这里](http://blog.leanote.com/post/jevonswang/%E8%BF%9C%E7%A8%8B%E8%AE%BF%E9%97%AEjupyter-notebook)

## 配置方法


```bash
(py35)$jupyter notebook --generate-config
# 若这里提示sql相关的库缺失，要安装sqlite3等包
# 问题出在下载python的时候，仅装了官方提供的安装包，没有装其他可能需要的相应的库而导致的。
# 所以编译安装python时先
# 安装 python3-dev libffi-dev libssl-dev libsqlite3-dev sqlite3 pysqlite2
# 具体哪个是apt那个是pip装的不记得了

$ipython
In [1]: from notebook.auth import passwd
In [2]: passwd()
Enter password:
Verify password:
Out[2]: 'sha1:ce23d945972f:34769685a7ccd3d08c84a18c63968a41f1140274'

$vim ~/.jupyter/jupyter_notebook_config.py
# 作如下修改
c.NotebookApp.ip='*'
c.NotebookApp.password = u'sha:ce...刚才复制的那个密文'
c.NotebookApp.open_browser = False
c.NotebookApp.port =8888 #随便指定一个端口

# 进入虚拟环境启动jupyter
(py35)$jupyter notebook
```

## 远程访问
此时应该可以直接从本地浏览器直接访问http://address_of_remote:8888就可以看到jupyter的登陆界面

## 建立ssh通道
如果登陆失败，则有可能是服务器防火墙设置的问题，此时最简单的方法是在本地建立一个ssh通道：
在本地终端中输入
```bash
ssh username@address_of_remote -L127.0.0.1:1234:127.0.0.1:8888
```
便可以在localhost:1234直接访问远程的jupyter了。
