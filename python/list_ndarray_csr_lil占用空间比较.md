feature为(3312, 3312)的稀疏特征矩阵，里面的值全为0或1。由于比较好奇各种存储矩阵的方式之间占用空间的差异，所以做了个实验：

```python
# env
Ubuntu16.04 64位
python3.5
pycharm

# experiment

#list
print(sys.getsizeof(feature))

feature_int64 = np.asarray(feature)
feature_int8 = np.asarray(feature, dtype=np.int8)
# ndarray
print(sys.getsizeof(feature_int64))
print(sys.getsizeof(feature_int8))
# csr
print(sys.getsizeof(scipy.sparse.csr_matrix(feature_int64)))
print(sys.getsizeof(scipy.sparse.csr_matrix(feature_int8)))
# lil
print(sys.getsizeof(scipy.sparse.lil_matrix(feature_int64)))
print(sys.getsizeof(scipy.sparse.lil_matrix(feature_int8)))

output：

26736     list

98114800  ndarray int64
12264448  ndarray int8

56        csr int64
56        csr int8

56        lil int64
56        lil int8
```

可见，csr与lil在这里的占用空间情况相近，list次之，ndarray为最，并且受数据类型影响明显。

按定义来看，lil的读写方式比csr的方便直观一些，csr会有点绕。
