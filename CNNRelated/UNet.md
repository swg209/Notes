##　结构

![](https://leanote.com/api/file/getImage?fileId=57a1358aab644135ea03a5e7)

## 代码
```python
def get_unet():
    concat_axis = 3
    inputs = Input((IW, IH, 3))
    conv1 = Conv2D(32, (3, 3), activation='relu', padding='same')(inputs)
    conv1 = Convolution2D(32, (3, 3), activation='relu', padding='same')(conv1)
    pool1 = MaxPooling2D(pool_size=(2, 2))(conv1)
    print('conv1', conv1.shape)
    print('pool1', pool1.shape)

    conv2 = Convolution2D(64, (3, 3), activation='relu', padding='same')(pool1)
    conv2 = Convolution2D(64, (3, 3), activation='relu', padding='same')(conv2)
    pool2 = MaxPooling2D(pool_size=(2, 2))(conv2)
    print('conv2', conv2.shape)
    print('pool2', pool2.shape)

    conv3 = Convolution2D(128, (3, 3), activation='relu', padding='same')(pool2)
    print('conv3', conv3.shape)
    conv3 = Convolution2D(128, (3, 3), activation='relu', padding='same')(conv3)
    pool3 = MaxPooling2D(pool_size=(2, 2))(conv3)
    print('conv3', conv3.shape)
    print('pool3', pool3.shape)

    conv4 = Convolution2D(256, (3, 3), activation='relu', padding='same')(pool3)
    conv4 = Convolution2D(256, (3, 3), activation='relu', padding='same')(conv4)
    pool4 = MaxPooling2D(pool_size=(2, 2))(conv4)
    print('conv4', conv4.shape)
    print('pool4', pool4.shape)

    conv5 = Convolution2D(512, (3, 3), activation='relu', padding='same')(pool4)
    conv5 = Convolution2D(512, (3, 3), activation='relu', padding='same')(conv5)
    print('conv5', conv5.shape)

    USampling6 = UpSampling2D(size=(2, 2))(conv5)
    print('USampling6', USampling6.shape)
    up6 = concatenate([USampling6, conv4], axis=concat_axis)
    conv6 = Convolution2D(256, (3, 3), activation='relu', padding='same')(up6)
    conv6 = Convolution2D(256, (3, 3), activation='relu', padding='same')(conv6)
    print('conv6', conv6.shape)

    USampling7 = UpSampling2D(size=(2, 2))(conv6)
    print('USampling7', USampling7.shape)
    up7 = concatenate([USampling7, conv3], axis=concat_axis)
    conv7 = Convolution2D(128, (3, 3), activation='relu', padding='same')(up7)
    conv7 = Convolution2D(128, (3, 3), activation='relu', padding='same')(conv7)
    print('conv7', conv7.shape)

    USampling8 = UpSampling2D(size=(2, 2))(conv7)
    print('USampling8', USampling8.shape)
    up8 = concatenate([USampling8, conv2], axis=concat_axis)
    conv8 = Convolution2D(64, (3, 3), activation='relu', padding='same')(up8)
    conv8 = Convolution2D(64, (3, 3), activation='relu', padding='same')(conv8)
    print('conv8', conv8.shape)

    USampling9 = UpSampling2D(size=(2, 2))(conv8)
    print('USampling9', USampling9.shape)
    up9 = concatenate([USampling9, conv1], axis=concat_axis)
    conv9 = Convolution2D(32, (3, 3), activation='relu', padding='same')(up9)
    conv9 = Convolution2D(32, (3, 3), activation='relu', padding='same')(conv9)
    print('conv9', conv9.shape)

    conv10 = Convolution2D(N_Cls, (1, 1), activation='sigmoid')(conv9)

    model = Model(input=inputs, output=conv10)
    model.compile(optimizer=Adam(), loss='binary_crossentropy', metrics=[jaccard_coef, jaccard_coef_int, 'accuracy'])
    return model
```

## 注意

- UNet的结构对输入数据的尺寸是有要求的，我也没搞清楚FCN宣称的对输入图片大小没要求，必须使其在conv、pooling后的W和H都能被2整除，否则后面USampling会出现尺寸不一致的问题。
- 关于label，必须是(IW, IH, 1)这种格式，不然出错。另外，如果是多类识别，需要用keras.preprocessing.tocate???事先处理，转换成类别vector，或者你的label本来就是1,2,3标记好了的也可以不用转。
