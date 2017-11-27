### Huber loss

[wikipedia](https://en.wikipedia.org/wiki/Huber_loss)

在统计学里面，Huber loss是一个在robust regression里面用的loss func。它对离群点没平方差那么敏感。

*定义*

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/e384efc4ae2632cb0bd714462b7c38c272098cf5)

其中，$|a| = \delta, a = y-f(x)$。$\delta$是参数，$f(x)$是模型的预测值，$y$是真实值。

可以看到，当$a < \delta$时，L是二次的；否则，则是线性的。
