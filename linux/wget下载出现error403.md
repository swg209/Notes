## wget下载出现 error 403
```bash
wget wget http://datasets-ac.oss-cn-zhangjiakou.aliyuncs.com/ai_challenger_stock_train_20170916.zip?OSSAccessKeyId=LTAIrOA0FFfXPB7A

--2017-09-19 17:15:08-- http://datasets-ac.oss-cn-zhangjiakou.aliyuncs.com/ai_challenger_stock_train_20170916.zip?OSSAccessKeyId=LTAIrOA0FFfXPB7A
Resolving datasets-ac.oss-cn-zhangjiakou.aliyuncs.com (datasets-ac.oss-cn-zhangjiakou.aliyuncs.com)... 47.92.17.73
Connecting to datasets-ac.oss-cn-zhangjiakou.aliyuncs.com (datasets-ac.oss-cn-zhangjiakou.aliyuncs.com)|47.92.17.73|:80... connected.
HTTP request sent, awaiting response... 403 Forbidden
2017-09-19 17:15:08 ERROR 403: Forbidden.
```

## 解决办法

```bash
wget -O 'test.zip' "http://datasets-ac.oss-cn-zhangjiakou.aliyuncs.com/ai_challenger_stock_train_20170916.zip?OSSAccessKeyId=LTAIrOA0FFfXPB7A"
```

## 问题原因
与wget用不同方式发送的header有关，具体看[这里](http://ju.outofmemory.cn/entry/251802)
