## Sparse matrix

**稀疏矩阵指的是矩阵里面的元素大多都是0值。**

与 sparse 相对的，就是 **dense**, which most elements of the matrix are nonzero

矩阵的稀疏性 = zero-valued elements / total number of elements
$$ Sparsity = \frac{N_0}{N_{all}}$$

## Sparse Representation

**Q：稀疏表达有什么好处？**

稀疏表达的意义在于降维，但是我还是不知道这个怎么搞得

**Q：稀疏表达 sparse representation 与 降维 dimensionality reduction 本质区别在哪？**

降维是将原 space 里的数据在某一个 subspace 里面表达，而稀疏表达是在 a union subspace 里面表达。

**举个例子**

(x, y, z)的空间中，(x, y)就是其中一个 subspace 。而 a union subspace 就包含了多个 subspace ，比如[(x, y), (y, z), (z, x)]就是 a union subspace。

**Q：如何求得数据的稀疏矩阵？**

to be continue

## Storing a sparse matrix

**Compressed sparse row(CSR, CRS pr Yale format)**

CSR格式使用三维数组(A, IA, JA)存放一个稀疏矩阵M(m*n)，NNZ表示M里面非零项的数量

* len(A) = NNZ，用于保存所有非零项。其检索M的顺序是从左到右，从上到下。
* len(IA) = m+1，使用递归定义：
  * IA[0] = 0
  * IA[1] = IA[0] + 第1行的非零元素的数量(这里的第1行对应着矩阵第0行)
  * IA[i] = IA[i-1] + num of nonzero entries
  * 注意，IA[i]的值是累加的
  * IA怎么用呢？ A[IA[i]] to A[IA[i+1]-1]写出来就知道了
* len(JA) = NNZ，包含A中每个元素的列索引



例子：https://en.wikipedia.org/wiki/Sparse_matrix#Compressed_sparse_row_.28CSR.2C_CRS_or_Yale_format.29




>参考:
https://www.zhihu.com/question/26602796/answer/33431062
https://www.zhihu.com/question/24124122/answer/50403932
https://en.wikipedia.org/wiki/Sparse_matrix
