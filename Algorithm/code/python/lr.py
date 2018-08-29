#!/home/beta/Documents/py35/bin/python3
import tensorflow as tf

x = tf.placeholder(tf.float32, [None, 784])
y = tf.placeholder(tf.float32, [None, 10])

W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))

pred = tf.nn.softmax(tf.matul(x, W)+b)
cost = tf.reduce_mean(-tf.reduce_mean(y*tf.log(pred), axis=1))
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    # Train
    for epoch in range(training_epochs)：
        for i in range(total_batch):
            _, c = sess.run([optimizer, cost], feed_dict={x: batch_X, y:batch_y})
            avg_cost += c / total_batch

    # Test
    correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(pred, 1))
    accuary = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    
