## 配置

```
CPU：Intel E3-1231 v3 @ 3.40GHz
显卡：GTX970
内存：16G
硬盘：SSD256G+HHD2T

拟安装：Ubuntu16.04
```

## 出现的问题

1. 无法进入install ubuntu
2. 进入install ubuntu开始安装时提示
  >"The attempt to mount a file system with type vfat in SCSI2 (0,0,0), partition #1 (sda) at /boot/efi failed You may resume partitioning from the partitioning menu."
3. 安装完重启后无法进入系统，看不到grub，直接黑屏

## 解决办法

### 1.无法进入install ubuntu

进入livecd的grub界面，光标移动到install ubuntu，按e进入编辑模式，找到”quite splash” 然后改为“quite splash nomodeset”，按F10

### 2.提示"The attempt to mount a file system ... at /boot/efi failed ...”

问题出在你的硬盘没有EFI分区，当安装程序试图创建引导项的时候就会出错。

进入PE系统用DG分区工具，选快速分区，里面可以选**MBR**或者**GUID**。选GUID，把左下角“重建EFI分区”和“MS?分区”勾上，然后再重新安装ubuntu

### 3.安装完重启后无法进入系统，看不到grub，直接黑屏

两个办法

#### 办法1

用livecd，选“try ubuntu without installing”，按e，如上加“nomodeset”，进入ubuntu。

```
# sda3为ubuntu所在分区，这个要换成你自己的
sudo mount /dev/sda3 /mnt
cd /mnt
sudo vi etc/default/grub

GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"
## 改为
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash nomodeset"
```

本办法试了，对我木有用。不过可能对某些情况有用。

#### 办法2

由于我的硬盘只装了一个ubuntu，所以不显示grub会直接进入系统，但是由于ubuntu跟GTX970不兼容（我怀疑是我这个显卡品牌奇葩），所以直接黑屏。

所以目的很明确，就是要调出grub

有几种办法：
* 再装一个win，多了个启动项就会出现grub让你选操作系统
* 开机后按住shift，会进入grub，然后按e进入编辑模式，将"quiet splash"改为"quiet splash nomodeset"，按F10。进入系统后装好nvidia驱动。
