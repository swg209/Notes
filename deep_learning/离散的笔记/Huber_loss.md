### Huber loss

在统计学里面，Huber loss是一个在robust regression里面用的loss func。它对离群点没平方差那么敏感。

*定义*

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/e384efc4ae2632cb0bd714462b7c38c272098cf5)

其中，$|\alpha| = \delta, a = y-f(x)$
