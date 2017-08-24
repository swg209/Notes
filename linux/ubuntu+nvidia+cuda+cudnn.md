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
sudo cp /include/cudnn.h /usr/local/cuda/include
sudo cp -a /lib64/libcudnn* /usr/local/cuda/lib64
sudo rm -rf libcudnn.so.6 libcudnn.so
sudo ln -s libcudnn.so.6.0.12 libcudnn.so.6
sudo ln -s libcudnn.so.6 libcudnn.so
```
