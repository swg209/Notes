## 每次重新搭建环境太累，写个文档记录一下，方便以后写shell

---

## 更新apt

```bash
sudo apt update
sudo apt upgrade
```

## 安装python并创建virtualenv

```bash
# 就是没装这个导致ssl module in Python is not available
sudo apt-get install python3-dev libffi-dev libssl-dev
# zipimport.ZipImportError: can't decompress data; zlib not available make: *** [altinstall] Error 1
sudo apt-get install zlib1g-dev

# 下载并安装python
wget https://www.python.org/ftp/python/3.6.0/Python-3.6.0.tgz  
tar xvf Python-3.6.0.tgz
cd Python-3.6.0
./configure --enable-optimizations  
make -j8  
sudo make altinstall
python3.6
```

## 更换系统默认python版本

```bash
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2 100
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 150

# 切换python版本
sudo update-alternatives --config python
```

## 若创建virtualenv提示找不到python

```bash
# 用这个命令倒是可以
virtualenv -p python3.5 py35
```

## 更改pip源

```bash
sudo vim ~/.pip/pip.conf

[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
```

## 安装7z

```bash
$ sudo apt-get install p7zip-full p7zip-rar
```
若碰到无法解压的，要么压缩文件出了问题，要么文件格式不能用这个工具解压

## sougou

[Download](http://pinyin.sogou.com/linux/)

```bash
im-config
选fcitx
在setting-input method configuration里面添加sogou
logout或重启一下
```

## uget+aria2

```bash
sudo apt install uget aria2
```

然后在edit -> setting -> plug-in设置为aria2
