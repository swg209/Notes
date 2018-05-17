以cora数据集为例，cora数据集共cora的训练集共2708条数据，特征维度是1433

```python
def capsule(self, input_tensor):
    # input_tensor在这里的shape就是(2708, 1433)
    """Builds a fully connected capsule layer.

      Given an input tensor of shape `[batch, input_dim, input_atoms]`, this op
      performs the following:

        1. For each input capsule, multiples it with the weight variable to get
          votes of shape `[batch, input_dim, output_dim, output_atoms]`.
        2. Scales the votes for each output capsule by iterative routing.
        3. Squashes the output of each capsule to have norm less than one.

      Each capsule of this layer has one weight tensor for each capsules of layer
      below. Therefore, this layer has the following number of trainable variables:
        w: [input_dim * num_in_atoms, output_dim * num_out_atoms]
        b: [output_dim * num_out_atoms]

      Args:
        input_tensor: tensor, activation output of the layer below.
        input_dim: scalar, number of capsules in the layer below.
        output_dim: scalar, number of capsules in this layer.
        layer_name: string, Name of this layer.
        input_atoms: scalar, number of units in each capsule of input layer.
        output_atoms: scalar, number of units in each capsule of output layer.
        **routing_args: dictionary {leaky, num_routing}, args for routing function.

      Returns:
        Tensor of activations for this layer of shape
          `[batch, output_dim, output_atoms]`.
      """


    # 将input_tensor的shape从(2708, 1433)拓展为(2708, 1, 1433)
    input_tensor = tf.expand_dims(input_tensor, 1)

    # weights variable will hold the state of the weights for the layer
    # 定义weights，其shape=[input_dim, input_atoms, output_dim * output_atoms]
    weights = variables.weight_variable(
                [self.input_dim, self.input_atoms, self.output_dim * self.output_atoms], verbose=True)
    # 定义biases，其shape=[output_dim, self.output_atoms]
    biases = variables.bias_variable([self.output_dim, self.output_atoms])

    # Depthwise matmul: [b, d, c] ** [d, c, o_c] = [b, d, o_c]
    # To do this: tile input, do element-wise multiplication and reduce
    # sum over input_atoms dimmension.
    # 将input_tensor的shape拓展为(2708, 1, 1433, 1)，并且对最后一维做title
    input_tiled = tf.tile(
        tf.expand_dims(input_tensor, -1),
        [1, 1, 1, self.output_dim * self.output_atoms])
    # input_tiled * weights, 并对所得结果第3维做reduce_sum
    votes = tf.reduce_sum(input_tiled * weights, axis=2)
    votes_reshaped = tf.reshape(votes,
                                    [-1, self.input_dim, self.output_dim, self.output_atoms])
    with tf.name_scope('routing'):
        input_shape = tf.shape(input_tensor)
        logit_shape = tf.stack([input_shape[0], self.input_dim, self.output_dim])
        activations = self._update_routing(
            votes=votes_reshaped,
            biases=biases,
            logit_shape=logit_shape,
            num_dims=4,
            input_dim=self.input_dim,
            output_dim=self.output_dim,
            num_routing=3,
            leaky=False)
    return activations

def _update_routing(self, votes, biases, logit_shape, num_dims, input_dim, output_dim,
                    num_routing, leaky):
    """Sums over scaled votes and applies squash to compute the activations.

    Iteratively updates routing logits (scales) based on the similarity between
    the activation of this layer and the votes of the layer below.

    Args:
      votes: tensor, The transformed outputs of the layer below.
      biases: tensor, Bias variable.
      logit_shape: tensor, shape of the logit to be initialized.
      num_dims: scalar, number of dimmensions in votes. For fully connected
        capsule it is 4, for convolutional 6.
      input_dim: scalar, number of capsules in the input layer.
      output_dim: scalar, number of capsules in the output layer.
      num_routing: scalar, Number of routing iterations.
      leaky: boolean, if set use leaky routing.

    Returns:
      The activation tensor of the output layer after num_routing iterations.
    """
    votes_t_shape = [3, 0, 1, 2]
    for i in range(num_dims - 4):
        votes_t_shape += [i + 4]
    r_t_shape = [1, 2, 3, 0]
    for i in range(num_dims - 4):
        r_t_shape += [i + 4]
    votes_trans = tf.transpose(votes, votes_t_shape)

    def _body(i, logits, activations):
        """Routing while loop."""
        # route: [batch, input_dim, output_dim, ...]
        # name = logits.name.split('/')[1]
        # itertime = i.name
        if leaky:
            route = self._leaky_routing(logits, output_dim)
        else:
            route = tf.nn.softmax(logits, dim=2)
            # tf.summary.scalar(name + 'route' + itertime, route)

        preactivate_unrolled = route * votes_trans
        preact_trans = tf.transpose(preactivate_unrolled, r_t_shape)
        preactivate = tf.reduce_sum(preact_trans, axis=1) + biases
        activation = self._squash(preactivate)
        # tf.summary.scalar(name + 'activation' + itertime, activation)
        activations = activations.write(i, activation)
        # distances: [batch, input_dim, output_dim]
        act_3d = tf.expand_dims(activation, 1)
        tile_shape = np.ones(num_dims, dtype=np.int32).tolist()
        tile_shape[1] = input_dim
        act_replicated = tf.tile(act_3d, tile_shape)
        distances = tf.reduce_sum(votes * act_replicated, axis=3)
        # tf.summary.scalar(name + 'distances' + itertime, distances)
        logits += distances
        return (i + 1, logits, activations)

    activations = tf.TensorArray(
        dtype=tf.float32, size=num_routing, clear_after_read=False)
    logits = tf.fill(logit_shape, 0.0)
    i = tf.constant(0, dtype=tf.int32)
    _, logits, activations = tf.while_loop(
        lambda i, logits, activations: i < num_routing,
        _body,
        loop_vars=[i, logits, activations],
        swap_memory=True)

    return activations.read(num_routing - 1)

    activations = tf.TensorArray(
        dtype=tf.float32, size=num_routing, clear_after_read=False)
    logits = tf.fill(logit_shape, 0.0)
    i = tf.constant(0, dtype=tf.int32)
    _, logits, activations = tf.while_loop(
        lambda i, logits, activations: i < num_routing,
        _body,
        loop_vars=[i, logits, activations],
        swap_memory=True)

    return activations.read(num_routing - 1)

def _squash(self, input_tensor):
    """Applies norm nonlinearity (squash) to a capsule layer.

    Args:
      input_tensor: Input tensor. Shape is [batch, num_channels, num_atoms] for a
        fully connected capsule layer or
        [batch, num_channels, num_atoms, height, width] for a convolutional
        capsule layer.

    Returns:
      A tensor with same shape as input (rank 3) for output of this layer.
    """
    with tf.name_scope('norm_non_linearity'):
        norm = tf.norm(input_tensor, axis=2, keep_dims=True)
        norm_squared = norm * norm
        return (input_tensor / norm) * (norm_squared / (1 + norm_squared))

def _leaky_routing(self, logits, output_dim):
    """Adds extra dimmension to routing logits.

    This enables active capsules to be routed to the extra dim if they are not a
    good fit for any of the capsules in layer above.

    Args:
      logits: The original logits. shape is
        [input_capsule_num, output_capsule_num] if fully connected. Otherwise, it
        has two more dimmensions.
      output_dim: The number of units in the second dimmension of logits.

    Returns:
      Routing probabilities for each pair of capsules. Same shape as logits.
    """

    # leak is a zero matrix with same shape as logits except dim(2) = 1 because
    # of the reduce_sum.
    leak = tf.zeros_like(logits, optimize=True)
    leak = tf.reduce_sum(leak, axis=2, keep_dims=True)
    leaky_logits = tf.concat([leak, logits], axis=2)
    leaky_routing = tf.nn.softmax(leaky_logits, dim=2)
    return tf.split(leaky_routing, [1, output_dim], 2)[1]



```
