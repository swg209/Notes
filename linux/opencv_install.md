# [opencv](https://github.com/opencv/opencv)

[官网教程](http://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)

1. 到上面的链接下载源文件

2. 由于要使用cmake：
```bash
[compiler] sudo apt-get install build-essential
[required] sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
[optional] sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
```

3. cd进去文件目录
```bash
cd opencv-3.3
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
```

4. 另外，在Ubuntu上使用python调用OpenCV需要安装python包
```bash
sudo apt-get install python-opencv
```

5. 验证是否安装成功
```
import cv2
cv2.__version__
```

### 碰到的问题

- 缺少IPPICV，需要下载但是下载timeout

  从网上下载包([这里](https://github.com/opencv/opencv_3rdparty/tree/ippicv/master_20170418/ippicv))然后

  ```
  cd opencv-3.3.0/.cache/ippicv
  替换掉原来的cache文件
  然后重新执行cmake命令
  ```

- 安装完成后virtualenv无法使用cv2

  我尝试过将系统的python3.5里面site-packages关于opencv的文件放到virtualenv的对应目录下,但是不行,故activate后再重新安装,就好了.
