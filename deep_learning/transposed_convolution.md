# 实质

经过一番推算，其tc前后的shape的计算方式是conv求输出size的逆运算

从1式
$$O = \frac{W+2P-K}{S} + 1$$
到2式
$$ W = (O - 1) * S + K - 2P $$

###　注意

- 2试中，S和K值相同，而2*2的kernal size，K=2，这点和conv不一样。
- 有一个巨坑！若keras中的conv的padding='same'，函数会填充使得输入输出尺寸相同！

### 结合UNet

UNet的结构对输入数据的尺寸是有要求的，必须使其在conv、pooling后的W和H都能被2整除，否则后面USampling会出现尺寸不一致的问题。
