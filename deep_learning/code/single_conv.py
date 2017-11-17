import theano
import numpy
from theano import tensor as T
from theano.tensor.nnet import conv2d

import pylab
from PIL import Image

rng = numpy.random.RandomState(23455)


# instantiate 4D tensor for input
input = T.tensor4(name='input')

# initialize shared variable for weights
w_shp = (3, 3, 9, 9)
w_bound = numpy.sqrt(3 * 9 * 9)
W = theano.shared(
    numpy.asarray(
        rng.uniform(
            low=-1.0 / w_bound,
            high=1 / w_bound,
            size=w_shp
        ),
        dtype=input.dtype
    )
)

tmp = numpy.asarray(
        rng.uniform(
            low=-1.0 / w_bound,
            high=1 / w_bound,
            size=w_shp
        ),
        dtype=input.dtype
)

b_shp = (3,)
b = theano.shared(numpy.asarray(
    rng.uniform(low=-.5, high=.5, size=b_shp),
    dtype=input.dtype), name='b')

conv_out = conv2d(input, W)

output = T.nnet.sigmoid(conv_out + b.dimshuffle('x', 0, 'x', 'x'))

f = theano.function([input], output)

img = Image.open(open('./3wolfmoon.jpg', 'rb'))
img = numpy.asarray(img, dtype='float64') / 256

img_ = img.transpose(2, 0, 1).reshape(1, 3, 639, 516)
filtered_img = f(img_)
print(filtered_img.shape)
'''
pylab.subplot(1, 3, 1);pylab.axis('off');pylab.imshow(img)
# pylab.gray()
pylab.subplot(1, 3, 2);pylab.axis('off');pylab.imshow(filtered_img[0, 0, :, :])
pylab.subplot(1, 3, 3);pylab.axis('off');pylab.imshow(filtered_img[0, 1, :, :])
pylab.show()
'''
pylab.subplot(1, 3, 1);pylab.axis('off');pylab.imshow(filtered_img[0, 0, :, :])
pylab.subplot(1, 3, 2);pylab.axis('off');pylab.imshow(filtered_img[0, 1, :, :])
pylab.subplot(1, 3, 3);pylab.axis('off');pylab.imshow(filtered_img[0, 2, :, :])
pylab.show()