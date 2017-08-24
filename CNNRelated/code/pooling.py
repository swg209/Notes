import numpy
import theano
import theano.tensor as T
from theano.tensor.signal import pool

input = T.dtensor4('input')
maxpool_shape = (2, 2)
pool_out = pool.pool_2d(input, maxpool_shape, ignore_border=True)
f = theano.function([input], pool_out)
'''
上面部分定义了单个pooling层
下面invals的shape是(3, 2, 5, 5)

'''

invals = numpy.random.RandomState(1).rand(3, 2, 5, 5)
print('with ignore_border set to True:')
print('invals[0, 0, :, :] = \n', f(invals)[0, 0, :, :])

pool_out = pool.pool_2d(input, maxpool_shape, ignore_border=False)
f = theano.function([input], pool_out)
print('With ignore_border set to False:')
print('invals[1, 0, :, :] =\n ', invals[1, 0, :, :])
print('output[1, 0, :, :] =\n ', f(invals)[1, 0, :, :])
print('\n')
