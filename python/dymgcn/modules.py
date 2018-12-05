import tensorflow as tf
import sonnet as snt

class DYMGCN(snt.AbstractModule):
    """Implementation of DYMGCN.

    在GCN基础上进行改进，利用CapsNet的动态路由算法，来学习图上的边的权重
    """
    def __init__(self,
                 adj,
                 input_shape,
                 name='DYMGCN'):
        """Initializes the DynamicGCN module.

        Args:

        """
        super(DYMGCN, self).__init__(name=name)
        with self._enter_variable_scope():
            pre_adj = tf.Variable(tf.random_uniform_initializer())

    def _build(self, *args, **kwargs):
