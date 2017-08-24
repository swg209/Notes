```python
from PIL import Image
from matplotlab import pyplot as plt


# 读取图片
img = Image.open('000752.png')

# 将通道分开
imgsplit = img.split()

# 显示图片
plt.subplot(1, 4, 1)
plt.imshow(imgsplit[0])
plt.subplot(1, 4, 2)
plt.imshow(imgsplit[1])
...
plt.show()

# 转换为numpy数组
np_img = np.asarray(img)


```
