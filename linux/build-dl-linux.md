## 每次重新搭建环境太累，写个文档记录一下，方便以后写shell

## 更新apt
```bash
sudo apt update
sudo apt upgrade
```

## 安装python并创建virtualenv

```bash
# 就是没装这个导致ssl module in Python is not available
sudo apt-get install python3-dev libffi-dev libssl-dev
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
