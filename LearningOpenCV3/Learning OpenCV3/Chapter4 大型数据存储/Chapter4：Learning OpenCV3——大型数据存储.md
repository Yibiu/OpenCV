# 大型数据存储

[TOC]

上一章介绍了基本数据类型和辅助类型数据，这章将介绍OpenCV3对大型数据的存储。

其中比较具有代表性的是 **cv::Mat和cv::SparseMat** 类型。 cv::Mat针对的是密集连续性的存储，大多数的图像数据被存储为这种类，即使数据为空，预留的存储空间仍然存在；而cv::SparseMat针对的是稀疏的存储方式，只有数据不为0才保留空间，否则不会预留。显然cv::SparseMat存储更为节省空间，典型使用cv::SparseMat的例如直方图数据的存储。



## 一：cv::Mat

### 1.1 创建cv::Mat

cv::Mat用于密集连续型的n维数据存储。成员变量：

- **flags：** 数据内容标识；
- **dims：** 数据维数；
- **rows和cols：** 数据行列数；
- **data：** 指向存储的数据；
- **refcount:** 用于智能指针的引用计数。

**cv::Mat分为头部和数据部分，不拷贝数据的操作为“浅拷贝”，只是复制了头部；如果拷贝了数据则叫“深拷贝”，这种操作会创建空间并拷贝对方的数据。** 常见的构造方式有：

```c++
// 先声明，再创建数据
cv::Mat m;
// Create data area for 3 rows and 10 columns of 3-channel 32-bit floats
m.create( 3, 10, CV_32FC3 );
// Set the values in the 1st channel to 1.0, the 2nd to 0.0, and the 3rd to 1.0
m.setTo( cv::Scalar( 1.0f, 0.0f, 1.0f ) );

// 声明同时创建
cv::Mat m( 3, 10, CV_32FC3, cv::Scalar( 1.0f, 0.0f, 1.0f ) );
```

其中，type的组成方式为：**CV_{8U,16S,16U,32S,32F,64F}C{1,2,3}** 。例如：CV_32FC3 代表32bit浮点类型的三通道数据。

 常见的无值拷贝构造：

| 构造                                       | 描述                                       |
| ---------------------------------------- | ---------------------------------------- |
| cv::Mat;                                 | Default constructor                      |
| cv::Mat( int rows, int cols, int type ); | Two-dimensional arrays by type           |
| cv::Mat(int rows, int cols, int type,const Scalar& s); | Two-dimensional arrays by type with initialization value |
| cv::Mat(int rows, int cols, int type,void* data, size_t step=AUTO_STEP); | Two-dimensional arrays by type with preexisting data |
| cv::Mat( cv::Size sz, int type );        | Two-dimensional arrays by type (size in sz) |
| cv::Mat(cv::Size sz,int type, const Scalar& s); | Two-dimensional arrays by type with initialization value (sizein sz) |
| cv::Mat(cv::Size sz, int type,void* data, size_t step=AUTO_STEP); | Two-dimensional arrays by type with preexisting data (size insz) |
| cv::Mat(int ndims, const int* sizes,int type); | Multidimensional arrays by type          |
| cv::Mat(int ndims, const int* sizes,int type, const Scalar& s); | Multidimensional arrays by type with initialization value |
| cv::Mat(int ndims, const int* sizes,int type, void* data,size_t step=AUTO_STEP); | Multidimensional arrays by type with preexisting data |

拷贝构造：

| 构造                                       | 描述                                       |
| ---------------------------------------- | ---------------------------------------- |
| cv::Mat( const Mat& mat );               | Copy constructor                         |
| cv::Mat(const Mat& mat,const cv::Range& rows,const cv::Range& cols); | Copy constructor that copies only a subset of rows andcolumns |
| cv::Mat(const Mat& mat,const cv::Rect& roi); | Copy constructor that copies only a subset of rows andcolumns specified by a region of interest |
| cv::Mat(const Mat& mat,const cv::Range* ranges); | Generalized region of interest copy constructor that uses anarray of ranges to select from an n-dimensional array |
| cv::Mat( const cv::MatExpr& expr );      | Copy constructor that initializes m with the result of analgebraic expression of other matrices |

模板构造和功能构造：

| 构造                                       | 描述                                       |
| ---------------------------------------- | ---------------------------------------- |
| cv::Mat(const cv::Vec<T,n>& vec,bool copyData=true); | Construct a one-dimensional array of type T and size n from acv::Vec of the same type |
| cv::Mat(const cv::Matx<T,m,n>& vec,bool copyData=true); | Construct a two-dimensional array of type T and size m × nfrom a cv::Matx of the same type |
| cv::Mat(const std::vector<T>& vec,bool copyData=true); | Construct a one-dimensional array of type T from an STLvector containing elements of the same type |
| cv::Mat::zeros( rows, cols, type );      | Create a cv::Mat of size rows × cols, which is full ofzeros, with type type (CV_32F, etc.) |
| cv::Mat::ones( rows, cols, type );       | Create a cv::Mat of size rows × cols, which is full ofones, with type type (CV_32F, etc.) |
| cv::Mat::eye( rows, cols, type );        | Create a cv::Mat of size rows × cols, which is anidentity matrix, with type type (CV_32F, etc.) |

### 1.2 元素访问

本节介绍访问cv::Mat元素的方式：位置访问、迭代器访问和块访问。

#### 1.2.1 位置访问

最直接的位置访问方式是使用 **at<>() ** ：

```c++
cv::Mat m = cv::Mat::eye( 10, 10, 32FC1 );
printf("Element (3,3) is %f\n",m.at<float>(3,3));

cv::Mat m = cv::Mat::eye( 10, 10, 32FC2 );
printf("Element (3,3) is (%f,%f)\n",m.at<cv::Vec2f>(3,3)[0],m.at<cv::Vec2f>(3,3)[1]);

cv::Mat m = cv::Mat::eye( 10, 10, cv::DataType<cv::Complexf>::type );
printf("Element (3,3) is %f + i%f\n",m.at<cv::Complexf>(3,3).re,m.at<cv::Complexf>(3,3).im,);

M.at<int>( i ); // Element i from integer array M
M.at<float>( i, j ); // Element ( i, j ) from float array M
M.at<int>( pt ); // Element at location (pt.x, pt.y) in integer matrix M
M.at<float>( i, j, k ); // Element at location ( i, j, k ) in three-dimensional float array M
M.at<uchar>( idx ); // Element at n-dimensional location indicated by idx[] in array M of unsigned characters
```

####1.2.2 迭代器访问

使用 **cv::MatIterator<> 和cv::MatConstIterator<> ** 迭代器可以对cv::Mat元素进行访问：

```c++
int sz[3] = { 4, 4, 4 };
cv::Mat m( 3, sz, CV_32FC3 ); // A three-dimensional array of size 4-by-4-by-4
cv::randu( m, -1.0f, 1.0f ); // fill with random numbers from -1.0 to 1.0
float max = 0.0f; // minimum possible value of L2 norm

cv::MatConstIterator<cv::Vec3f> it = m.begin();
while( it != m.end() ) 
{
	len2 = (*it)[0]*(*it)[0]+(*it)[1]*(*it)[1]+(*it)[2]*(*it)[2];
	if( len2 > max ) max = len2;
	it++;
}
```

和c++ STL的迭代器一样，在使用时要时刻注意迭代器的失效问题。此外，还可以使用 **NAryMatIterator ** 迭代器进行“plane by plane”类型的数据访问：

```c++
// Example 1:Summation of a multidimensional array, done plane by plane
const int n_mat_size = 5;
const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
cv::Mat n_mat( 3, n_mat_sz, CV_32FC1 );
cv::RNG rng;
rng.fill( n_mat, cv::RNG::UNIFORM, 0.f, 1.f );
const cv::Mat* arrays[] = { &n_mat, 0 };
cv::Mat my_planes[1];
cv::NAryMatIterator it( arrays, my_planes );

// On each iteration, it.planes[i] will be the current plane of the
// i-th array from 'arrays'.
float s = 0.f; // Total sum over all planes
int n = 0; // Total number of planes
for (int p = 0; p < it.nplanes; p++, ++it) 
{
	s += cv::sum(it.planes[0])[0];
	n++;
}

// Example 2:Summation of two arrays using the N-ary operator
const int n_mat_size = 5;
const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
cv::Mat n_mat0( 3, n_mat_sz, CV_32FC1 );
cv::Mat n_mat1( 3, n_mat_sz, CV_32FC1 );
cv::RNG rng;
rng.fill( n_mat0, cv::RNG::UNIFORM, 0.f, 1.f );
rng.fill( n_mat1, cv::RNG::UNIFORM, 0.f, 1.f );
const cv::Mat* arrays[] = { &n_mat0, &n_mat1, 0 };
cv::Mat my_planes[2];
cv::NAryMatIterator it( arrays, my_planes );

float s = 0.f; // Total sum over all planes in both arrays
int n = 0; // Total number of planes
for(int p = 0; p < it.nplanes; p++, ++it) 
{
	s += cv::sum(it.planes[0])[0];
	s += cv::sum(it.planes[1])[0];
	n++;
}
```

#### 1.2.3 块访问

块访问提供对cv::Mat子数组的访问方式。这种访问方式返回的往往是个数组或范围，而不是单个元素。

| 示例                                       | 描述                                       |
| ---------------------------------------- | ---------------------------------------- |
| m.row( i );                              | Array corresponding to row i of m        |
| m.col( j );                              | Array corresponding to column j of m     |
| m.rowRange( i0, i1 );                    | Array corresponding to rows i0 through i1-1 of matrix m |
| m.rowRange( cv::Range( i0, i1 ) );       | Array corresponding to rows i0 through i1-1 of matrix m |
| m.colRange( j0, j1 );                    | Array corresponding to columns j0 through j1-1 of matrix m |
| m.colRange( cv::Range( j0, j1 ) );       | Array corresponding to columns j0 through j1-1 of matrix m |
| m.diag( d );                             | Array corresponding to the d-offset diagonal of matrix m |
| m( cv::Range(i0,i1), cv::Range(j0,j1) ); | Array corresponding to the subrectangle of matrix m with one cornerat i0, j0 and the opposite corner at (i1-1, j1-1) |
| m( cv::Rect(i0,i1,w,h) );                | Array corresponding to the subrectangle of matrix m with one cornerat i0, j0 and the opposite corner at (i0+w-1, j0+h-1) |
| m( ranges );                             | Array extracted from m corresponding to the subvolume that is theintersection of the ranges given by ranges[0]-ranges[ndim-1] |

#### 1.2.4 饱和度转换

在opencv中，对计算式进行计算的时候经常会出现值溢出（上溢出或下溢出），尤其是对无符号数值进行加减操作时。opencv中使用Saturation Casting“转换很好的解决这个问题，使用saturate_cast<>（），opencv对数组或矩阵进行代数运算或其他操作时，会自动检测underflows and overflows，当结果上溢出时就会用最大的可用值代替，当下溢出时就会用最小的可用值代替。

```c++
uchar& Vxy = m0.at<uchar>( y, x );
Vxy = cv::saturate_cast<uchar>((Vxy-128)*2 + 128);}
```

如果Vxy=10，那么Vxy-128 =-118，(Vxy-128)*2 + 128=-108，超出了uchar(8-bit)Vxy 范围，cv::saturate_cast就会把范围限定为uchar的最小值0。

### 1.3 操作

cv::Mat支持的算术表达式操作：

| 示例                                       | 描述                                       |
| ---------------------------------------- | ---------------------------------------- |
| m0 + m1, m0 – m1;                        | Addition or subtraction of matrices      |
| m0 + s; m0 – s; s + m0, s – m1;          | Addition or subtraction between a matrix and a singleton |
| -m0;                                     | Negation of a matrix                     |
| s * m0; m0 * s;                          | Scaling of a matrix by a singleton       |
| m0.mul( m1 ); m0/m1;                     | Per element multiplication of m0 and m1, per-element division ofm0 by m1 |
| m0 * m1;                                 | Matrix multiplication of m0 and m1       |
| m0.inv( method );                        | Matrix inversion of m0 (default value of method is DECOMP_LU) |
| m0.t();                                  | Matrix transpose of m0 (no copy is done) |
| m0>m1; m0>=m1; m0==m1; m0<=m1; m0<m1;    | Per element comparison, returns uchar matrix with elements 0or 255 |
| m0&m1; m0\|m1; m0^m1; ~m0;m0&s; s&m0; m0\|s; s\|m0; m0^s; s^m0; | Bitwise logical operators between matrices or matrix and asingleton |
| min(m0,m1); max(m0,m1); min(m0,s);min(s,m0); max(m0,s); max(s,m0); | Per element minimum and maximum between two matrices or amatrix and a singleton |
| cv::abs( m0 );                           | Per element absolute value of m0         |
| m0.cross( m1 ); m0.dot( m1 );            | Vector cross and dot product (vector cross product is defined onlyfor 3 × 1 matrices) |
| cv::Mat::eye( Nr, Nc, type );cv::Mat::zeros( Nr, Nc, type );cv::Mat::ones( Nr, Nc, type ); | Class static matrix initializers that return fixed Nr × Nc matrices oftype type |

cv::Mat支持的其他操作：

| 示例                                     | 描述                                       |
| -------------------------------------- | ---------------------------------------- |
| m1 = m0.clone();                       | Make a complete copy of m0, copying all data elements as well; cloned array willbe continuous |
| m0.copyTo( m1 );                       | Copy contents of m0 onto m1, reallocating m1 if necessary (equivalent tom1=m0.clone()) |
| m0.copyTo( m1, mask );                 | Same as m0.copyTo(m1), except only entries indicated in the array mask arecopied |
| m0.convertTo(m1, type, scale, offset); | Convert elements of m0 to type (e.g., CV_32F) and write to m1 after scaling byscale (default 1.0) and adding offset (default 0.0) |
| m0.assignTo( m1, type );               | Internal use only (resembles convertTo)  |
| m0.setTo( s, mask );                   | Set all entries in m0 to singleton value s; if mask is present, set only those valuescorresponding to nonzero elements in mask |
| m0.reshape( chan, rows );              | Changes effective shape of a two-dimensional matrix; chan or rows may be zero,which implies “no change”; data is not copied |
| m0.push_back( s );                     | Extend an m × 1 matrix and insert the singleton s at the end |
| m0.push_back( m1 );                    | Extend an m × n by k rows and copy m1 into those rows; m1 must be k × n |
| m0.pop_back( n );                      | Remove n rows from the end of an m × n (default value of n is 1) |
| m0.locateROI( size, offset );          | Write whole size of m0 to cv::Size size; if m0 is a “view” of a larger matrix,write location of starting corner to Point& offset |
| m0.adjustROI( t, b, l, r );            | Increase the size of a view by t pixels above, b pixels below, l pixels to the left,and r pixels to the right |
| m0.total();                            | Compute the total number of array elements (does not include channels) |
| m0.isContinuous();                     | Return true only if the rows in m0 are packed without space between them inmemory |
| m0.elemSize();                         | Return the size of the elements of m0 in bytes (e.g., a three-channel float matrixwould return 12 bytes) |
| m0.elemSize1();                        | Return the size of the subelements of m0 in bytes (e.g., a three-channel floatmatrix would return 4 bytes) |
| m0.type();                             | Return a valid type identifier for the elements of m0 (e.g., CV_32FC3) |
| m0.depth();                            | Return a valid type identifier for the individial channels of m0 (e.g., CV_32F) |
| m0.channels();                         | Return the number of channels in the elements of m0 |
| m0.size();                             | Return the size of the m0 as a cv::Size object |
| m0.empty();                            | Return true only if the array has no elements (i.e., m0.total==0 orm0.data==NULL) |



## 二：cv::SparseMat

cv::SparseMat与cv::Mat内部数据组织方式不同，cv::SparseMat使用Hash表记录非零数值，且Hash表可以根据需要自动增长。

### 2.1 元素访问

cv::SparseMat提供四种元素访问的形式：**cv::SparseMat::ptr()，cv::SparseMat::ref()，cv::SparseMat::value()和cv::SparseMat::find()** 。

```c++
// i0:值索引
// createMissing：值不存在时创建
// hashval：Hash表的key值，如果填充则不再重新计算；如果为NULL则重新计算key。
uchar* cv::SparseMat::ptr( int i0, bool createMissing, size_t* hashval=0 );

// 返回引用值
cv::SparseMat::ref<_T>();
// 返回拷贝值，非引用
cv::SparseMat::value<_T>();
// 返回指针
cv::SparseMat::find<_T>();
```

另外，也可以采用 **cv::SparseMatIterator\_<>和 cv::SparseMatConstIterator\_<>** 迭代器方式访问元素：

````c++
// Create a 10x10 sparse matrix with a few nonzero elements
int size[] = {10,10};
cv::SparseMat sm( 2, size, CV_32F );
for( int i=0; i<10; i++ ) 
{ // Fill the array
	int idx[2];
	idx[0] = size[0] * rand();
	idx[1] = size[1] * rand();
	sm.ref<float>( idx ) += 1.0f;
}

// Print out the nonzero elements
cv::SparseMatConstIterator_<float> it = sm.begin<float>();
cv::SparseMatConstIterator_<float> it_end = sm.end<float>();
for(; it != it_end; ++it) 
{
	const cv::SparseMat::Node* node = it.node();
	printf(" (%3d,%3d) %f\n", node->idx[0], node->idx[1], *it );
}
````

###2.2 操作 

cv::SparseMat其他操作方式见下表：

| 示例                                       | 描述                                       |
| ---------------------------------------- | ---------------------------------------- |
| cv::SparseMat sm;                        | Create a sparse matrix without initialization |
| cv::SparseMat sm( 3, sz, CV_32F );       | Create a three-dimensional sparse matrix with dimensions given by thearray sz of type float |
| cv::SparseMat sm( sm0 );                 | Create a new sparse matrix that is a copy of the existing sparse matrix sm0 |
| cv::SparseMat( m0, try1d );              | Create a sparse matrix from an existing dense matrix m0; if the booltry1d is true, convert m0 to a one-dimensional sparse matrix if thedense matrix was n × 1 or 1 × n |
| cv::SparseMat( &old_sparse_mat );        | Create a new sparse matrix from a pointer to a pre–version 2.1 C-stylesparse matrix of type CvSparseMat |
| CvSparseMat* old_sm =(cv::SparseMat*) sm; | Cast operator creates a pointer to a pre–version 2.1 C-style sparse matrix;that CvSparseMat object is created and all data is copied into it, andthen its pointer is returned |
| size_t n = sm.nzcount();                 | Return the number of nonzero elements in sm |
| size_t h = sm.hash( i0 );size_t h = sm.hash( i0, i1 );size_t h = sm.hash( i0, i1, i2 );size_t h = sm.hash( idx ); | Return the hash value for element i0 in a one-dimensional sparse matrix;i0, i1 in a two-dimensional sparse matrix; i0, i1, i2 in a threedimensional sparse matrix; or the element indicated by the array ofintegers idx in an n-dimensional sparse matrix |
| sm.ref<float>( i0 ) = f0;sm.ref<float>( i0, i1 ) = f0;sm.ref<float>( i0, i1, i2 ) = f0;sm.ref<float>( idx ) = f0; | Assign the value f0 to element i0 in a one-dimensional sparse matrix;i0, i1 in a two-dimensional sparse matrix; i0, i1, i2 in a threedimensional sparse matrix; or the element indicated by the array ofintegers idx in an n-dimensional sparse matrix |
| f0 = sm.value<float>( i0 );f0 = sm.value<float>( i0, i1 );f0 = sm.value<float>( i0, i1, i2 );f0 = sm.value<float>( idx ); | Assign the value to f0 from element i0 in a one-dimensional sparsematrix; i0, i1 in a two-dimensional sparse matrix; i0, i1, i2 in a threedimensional sparse matrix; or the element indicated by the array ofintegers idx in an n-dimensional sparse matrix |
| p0 = sm.find<float>( i0 );p0 = sm.find<float>( i0, i1 );p0 = sm.find<float>( i0, i1, i2 );p0 = sm.find<float>( idx ); | Assign to p0 the address of element i0 in a one-dimensional sparsematrix; i0, i1 in a two-dimensional sparse matrix; i0, i1, i2 in a threedimensional sparse matrix; or the element indicated by the array ofintegers idx in an n-dimensional sparse matrix |
| sm.erase( i0, i1, &hashval );sm.erase( i0, i1, i2, &hashval );sm.erase( idx, &hashval ); | Remove the element at (i0, i1) in a two-dimensional sparse matrix; at(i0, i1, i2) in a three-dimensional sparse matrix; or the elementindicated by the array of integers idx in an n-dimensional sparse matrix.If hashval is not NULL, use the provided value instead of computing it |
| cv::SparseMatIterator<float> it= sm.begin<float>(); | Create a sparse matrix iterator it and point it at the first value of thefloating-point array sm |
| cv::SparseMatIterator<uchar> it_end= sm.end<uchar>(); | Create a sparse matrix iterator it_end and initialize it to the valuesucceeding the final value in the byte array sm |







