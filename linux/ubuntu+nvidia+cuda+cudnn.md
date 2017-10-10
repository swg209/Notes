# nvidia驱动+cuda安装方法

详见同目录下[***Ubuntu16.04-TAITAN-X-CUDA-8.pdf***]

# 查看显卡配置

```bash
lspci -vnn | grep VGA -A 12
lshw -C display
```

# 测试cuda

```bash
cd ~/NVIDIA_CUDA-8.0_Samples
make
cd ~/NVIDIA_CUDA-8.0_Samples/bin/x86_64/linux/release
sudo ./deviceQuery
```

# 安装cudnn

下载tgz包
```bash
tar -xf cudnn-8.0-linux-x64-v6.0.tgz
cd cuda
sudo cp ./include/cudnn.h /usr/local/cuda/include
sudo cp -a ./lib64/libcudnn* /usr/local/cuda/lib64
sudo rm -rf libcudnn.so.6 libcudnn.so
sudo ln -s libcudnn.so.6.0.21 libcudnn.so.6
sudo ln -s libcudnn.so.6 libcudnn.so
```

# 一些依赖

https://devtalk.nvidia.com/default/topic/993862/cuda-8-0-missing-required-libraries-on-ubuntu-16-04/

sudo apt-get install freeglut3-dev build-essential libx11-dev libxmu-dev libxi-dev libgl1-mesa-glx libglu1-mesa libglu1-mesa-dev libglfw3-dev libgles2-mesa-dev
