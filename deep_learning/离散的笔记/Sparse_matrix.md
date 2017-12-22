### Sparse matrix

**稀疏矩阵指的是矩阵里面的元素大多都是0值。**

与 sparse 相对的，就是 **dense**, which most elements of the matrix are nonzero

矩阵的稀疏性 = zero-valued elements / total number of elements
$$ Sparsity = \frac{N_0}{N_{all}}$$

### Sparse Representation

**Q：稀疏表达有什么好处？**

稀疏表达的意义在于降维，但是我还是不知道这个怎么搞得

**Q：稀疏表达 sparse representation 与 降维 dimensionality reduction 本质区别在哪？**

降维是将原 space 里的数据在某一个 subspace 里面表达，而稀疏表达是在 a union subspace 里面表达。

**举个例子**

(x, y, z)的空间中，(x, y)就是其中一个 subspace 。而 a union subspace 就包含了多个 subspace ，比如[(x, y), (y, z), (z, x)]就是 a union subspace。

**Q：如何求得数据的稀疏矩阵？**

to be continue

### Storing a sparse matrix

**Compressed sparse row(CSR, CRS pr Yale format)**

$$
MatrixA =
\begin{pmatrix}
  0 & 0 & 0 & 0 \\
  5 & 8 & 0 & 0 \\
  0 & 0 & 3 & 0 \\
  0 & 6 & 0 & 0
\end{pmatrix}
$$

```python
# data
A = data = (5, 8, 3, 6)
# indptr的第一个元素为0，数值表示共有多少非零元素
IA = indptr = (0, 0, 2, 3, 4)
# 每个data的index
JA = indices = (0, 1, 2, 1)
```

$$
MatrixB =
\begin{pmatrix}
  10 & 20 & 0 & 0 & 0 & 0 \\
  0 & 30 & 0 & 40 & 0 & 0 \\
  0 & 0 & 50 & 60 & 70 & 0 \\
  0 & 0 & 0 & 0 & 0 & 80
\end{pmatrix}
$$

```python
A = data = (10, 20, 30, 40, 50, 60, 70, 80)
IA = indptr = (0, 2, 4, 7, 8)
JA = indices = (0, 1, 1, 3, 2, 3, 4, 5)
```

**List of list(LIL)**

LIL stores one list per row, with each entry containing the column index and the value. Typically, these entries are kept sorted by column index for faster lookup. This is another format good for incremental matrix construction.

```
MatrixA:

(1, 0) 5
(1, 1) 8
(2, 2) 3
(1, 1) 6

MatrixB:

(0, 0) 10
(0, 1) 20
(1, 1) 30
(1, 3) 40
(2, 2) 50
(2, 3) 60
(2, 4) 70
(3, 5) 80
```

例子：[这里](https://en.wikipedia.org/wiki/Sparse_matrix#Compressed_sparse_row_.28CSR.2C_CRS_or_Yale_format.29)

<br />
<br />

>参考:
https://www.zhihu.com/question/26602796/answer/33431062
https://www.zhihu.com/question/24124122/answer/50403932
https://en.wikipedia.org/wiki/Sparse_matrix
