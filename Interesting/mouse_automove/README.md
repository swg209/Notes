**Intro**

本目录下的```mouse.sh```是为了 [不可描述] 的原因而写的，主要是为了实现，鼠标在自己配置的时间段内，会来回移动。由于我不会shell，代码是随便写的，所以不要当真。近来比较忙，后期有时间会去改进。

**Requirement**

- xdotool

ubuntu下```sudo apt install xdotool```就可以了

**Run**

将```conf.ini & mouse.sh```下载到同一个目录，然后在Terminal下进入到mouse.sh所在文件夹

```bash
$ chmod +x mouse.sh
$ ./mouse.sh
```

可以传入参数指定模式。目前有```Weekend```、```Workday```两个模式可选，可在```config.ini```中修改时间设置

不传入参数时默认为```Workday```模式

```bash
$ ./mouse.sh Weekend  # 开启周末模式
$ ./mouse.sh Workday  # 开启工作日模式
```

**Config**

配置文件在conf.ini里面，可自行按照原来的格式更改参数

**Todo**

- 加上日期判断，根据当天是工作日还是周末来设定当前模式
- 加上随机时间，使登录和下线的时范围的随机性
