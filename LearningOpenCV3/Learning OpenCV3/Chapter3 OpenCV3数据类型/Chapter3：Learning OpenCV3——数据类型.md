#OpenCV3 数据类型

[TOC]

OpenCV3的数据类型比较多，主要分为：

- **基本数据类型(basic data types):** 包括c++对应的基础类，如int、float等；简单的容器、数组和矩阵类；简单的例如点、矩形、尺寸等的几何概念类。
- **帮助类(helper objects)：** 这一类表示一些抽象的概念。例如碎片处理的点类、切片使用的范围类、终止条件类等。
- **大型数组类(large array types)：** 这一类通常包含很多其他类型，最具代表性的是 **cv::Mat** 类。

OpenCV3除了这些类型还极度使用c++的STL，其中vector类和模板的使用尤多。本章介绍前两种类型，大型数组类留到下一章介绍。



## 一：基本数据类型

### 1.1 cv::Vec<>

为什么不使用c++ STL固定的vector呢？因为OpenCV3将vector的使用细化了，cv::Vec<> 针对的是比较小的数据使用，即维数比较小，且在编译时就可以确定大小。而对于大的数据，OpenCV3则使用cv::Mat来处理。

cv::Vec<>的组织类型可以为：**cv::Vec{2,3,4,6}{b,w,s,i,f,d} ** ，例如cv::Vec2i、cv::Vec4d等。

| 操作     | 示例                                       |
| ------ | ---------------------------------------- |
| 默认构造函数 | Vec2s v2s; Vec6f v6f; // etc...          |
| 拷贝构造函数 | Vec3f u3f( v3f );                        |
| 值构造函数  | Vec2f v2f(x0,x1); Vec6d v6d(x0,x1,x2,x3,x4,x5); |
| 成员访问   | v4f[ i ]; v3w( j ); // (operator() and operator[] both work) |
| 向量叉积   | v3f.cross( u3f );                        |

### 1.2 cv::Matx<>

同样，cv::Matx<>针对的时比较小的矩阵。计算机视觉中有很多2x2、3x3和4x4的矩阵，cv::Matx<>就负责存储这些类型。cv::Vec<>继承了cv::Matx<>。

cv::Matx<>的组织类型可以为：**cv::Matx{1,2,3,4,6}{1,2,3,4,6}{f,d} ** ，例如cv::Matx22i等。

| 操作               | 示例                                       |
| ---------------- | ---------------------------------------- |
| 默认构造函数           | cv::Matx33f m33f; cv::Matx43d m43d;      |
| 拷贝构造函数           | cv::Matx22d m22d( n22d );                |
| 值构造函数            | cv::Matx21f m(x0,x1); cv::Matx44dm(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15); |
| 同元素矩阵            | m33f = cv::Matx33f::all( x );            |
| 零矩阵              | m23d = cv::Matx23d::zeros();             |
| 壹矩阵              | m16f = cv::Matx16f::ones();              |
| 单位矩阵             | m33f = cv::Matx33f::eye();               |
| 保存对角矩阵           | m31f = cv::Matx33f::diag(); // Create a matrix of size 3-by-1 of floats |
| 均匀分布矩阵           | m33f = cv::Matx33f::randu( min, max );   |
| 正态分布矩阵           | m33f = cv::Matx33f::nrandn( mean, variance ); |
| 成员访问             | m( i, j ), m( i ); // one argument for one-dimensional matrices only |
| 矩阵代数             | m1 = m0; m0 * m1; m0 + m1; m0 – m1;      |
| 单代数              | m * a; a * m; m / a;                     |
| 比较               | m1 == m2; m1 != m2;                      |
| 点乘               | m1.dot( m2 ); // (sum of element-wise multiplications, precision of m) |
| 叉乘               | m1.ddot( m2 ); // (sum of element-wise multiplications,double precision) |
| 重塑一个矩阵           | m91f = m33f.reshape<9,1>();              |
| 转换操作             | m44f = (Matx44f) m44d                    |
| 从(i,j)处提取一个2x2矩阵 | m44f.get_minor<2, 2>( i, j );            |
| 提取i行             | m14f = m44f.row( i );                    |
| 提取j列             | m41f = m44f.col( j );                    |
| 提取对角             | m41f = m44f.diag();                      |
| 计算转置             | n44f = m44f.t();                         |
| 逆矩阵              | n44f = m44f.inv( method ); // (default method is cv::DECOMP_LU) |
| 解决线性系统           | m31f = m33f.solve( rhs31f, method );    <br />m32f = m33f.solve<2>( rhs32f, method );  // (template forma); <br />// default method is DECOMP_LU) |
| 对应元素相乘           | m1.mul( m2 );                            |

### 1.3 cv::Point<>

cv::Point<>和cv::Vec<>类型很相似，它们的不同在于：**Point类型由命名的变量关联(mypoint.x，mypoint.y等)，而vector类型则由下标访问(myvec[1]等)。** 

cv::Point<>的组织类型可以为：**cv::Point{2,3}{i,f,d}** ，例如cv::Point2i、cv::Point3f等。

| 操作         | 示例                                       |
| ---------- | :--------------------------------------- |
| 默认构造函数     | cv::Point2i p;   cv::Point3f p;          |
| 拷贝构造函数     | cv::Point3f p2( p1 );                    |
| 值构造函数      | cv::Point2i p( x0, x1 );    cv::Point3d p( x0, x1, x2 ); |
| 转化为vector  | (cv::Vec3f) p;                           |
| 成员访问       | p.x;    p.y;    p.z;                     |
| 点积(·)      | float x = p1.dot( p2 );     double x = p1.ddot( p2 ) |
| 叉积(x)      | p1.cross( p2 ); // 仅三维                   |
| 点p在矩形r中的访问 | p.inside( r ); // 仅二维                    |

### 1.4 cv::Scalar<>

cv::Scalar用于表示四维的点，它继承自相应的cv::Vec<T,4>类型。因此，对Scalar元素的访问可以通过下标，而不是命名变量。

| 操作       | 示例                                       |
| -------- | ---------------------------------------- |
| 默认构造函数   | cv::Scalar s;                            |
| 拷贝构造函数   | cv::Scalar s2( s1 );                     |
| 值构造函数    | cv::Scalar s( x0 );    cv::Scalar s( x0, x1, x2, x3 ); |
| 对应分量相乘   | s1.mul( s2 );                            |
| (四元数)共轭  | s.conj(); // (returns cv::Scalar(s0,-s1,-s2,-s2)) |
| (四元数)真测试 | s.isReal(); // (returns true iff s1==s2==s3==0) |

### 1.5 cv::Size<>

cv::Size<>和cv::Point<>很相似，但它一般用于表示尺寸，因此相关的命名变量为 **width** 和 **height** ，而不是 **x** 和 **y**。

cv::Size<>组织类型可以为：**cv::cvSize、cv::Size2i和cv::Size2f**。

| 操作     | 示例                                       |
| ------ | ---------------------------------------- |
| 默认构造函数 | cv::Size sz;    cv::Size2i sz;    cv::Size2f sz; |
| 拷贝构造函数 | cv::Size sz2( sz1 );                     |
| 值构造函数  | cv::Size2f sz( w, h );                   |
| 成员访问   | sz.width;    sz.height;                  |
| 计算面积   | sz.area();                               |

### 1.6 cv::Rect

cv::Rect 既包含x和y分量（左上角点），又包含width和height分量（大小）。

| 操作            | 示例                                    |
| ------------- | ------------------------------------- |
| 默认构造函数        | cv::Rect r;                           |
| 拷贝构造函数        | cv::Rect r2( r1 );                    |
| 值构造函数         | cv::Rect( x, y, w, h );               |
| 从Point和Size构造 | cv::Rect( p, sz );                    |
| 从一对Point构造    | cv::Rect( p1, p2 );                   |
| 成员访问          | r.x;    r.y;    r.width;    r.height; |
| 计算面积          | r.area();                             |
| 提取左上角         | r.tl();                               |
| 提取右下角         | r.br();                               |
| 判断点p是否在矩形内    | r.contains( p );                      |

cv::Rect也支持很多操作符重载操作：

| 操作           | 示例                                    |
| ------------ | ------------------------------------- |
| 矩形r1、r2相交    | cv::Rect r3 = r1 & r2;    r1 &= r2;   |
| 包含r1、r2的最小矩形 | cv::Rect r3 = r1 \| r2;    r1 \|= r2; |
| 矩形r增加x       | cv::Rect rx = r + x;    r += x;       |
| 矩形r扩大s       | cv::Rect rs = r + s;    r += s;       |
| 判断r1、r2相等    | bool eq = (r1 == r2);                 |
| 判断r1、r2不等    | bool ne = (r1 != r2);                 |

###1.7 cv::RotatedRect 

cv::RotatedRect是OpenCV3中少数的不基于模板的类，表示旋转一定角度的矩形。cv::RotatedRect与它中心的位置相关，而cv::Rect与它左上角位置相关。cv::RotatedRect包括：

- 中心：一个cv::Point2f类型；
- 尺寸：一个cv::Size2f 类型；
- 角度：一个float 类型。

| 操作                  | 示例                                   |
| ------------------- | ------------------------------------ |
| 默认构造函数              | cv::RotatedRect rr();                |
| 拷贝构造函数              | cv::RotatedRect rr2( rr1 );          |
| 从两个角点构造             | cv::RotatedRect( p1, p2 );           |
| 值构造；包含一个点，一个尺寸，一个角度 | cv::RotatedRect rr( p, sz, theta ) ; |
| 成员访问                | rr.center;    rr.size;    rr.angle;  |
| 返回四角                | rr.points( pts[4] );                 |

### 1.8 cv::Complex

OpenCV的复数类型和c++ STL的复数类型主要区别是成员访问不同。STL复数的实部和虚部通过real()和imag()访问，而OpenCV的复数实部和虚部成员变量为public，因此可以通过"."或“->”操作直接访问。

| 操作     | 示例                                       |
| ------ | ---------------------------------------- |
| 默认构造函数 | cv::Complexf z1; cv::Complexd z2;        |
| 拷贝构造函数 | cv::Complexf z2( z1 );     cv::Complexf u2f( v2f ); |
| 值构造函数  | cv::Complexd z1(re0); cv::Complexd(re0,im1) ; |
| 成员访问   | z1.re; z1.im;                            |
| 复数共轭   | z2 = z1.conj();                          |



## 二：帮助类

### 2.1 cv::TermCriteria  class

很多算法都有一些终止条件，比如何时结束或者接近什么情况时结束。cv::TermCriteria标识了这些结束条件，并且很容易传递给OpenCV3的算法。它包含三个成员变量：**type、maxCount和epsilon** 。

type可以被设置为：

- cv::TermCriteria::COUNT——在maxCount迭代后结束；
- cv::TermCriteria::EPS——在收敛速度低于ε时候结束；
- cv::TermCriteria::COUNT | cv::TermCriteria::EPS——在两种条件下结束。

### 2.2 cv::Range class

cv::Range类被用来指定一段连续的整数值，它包含 **start和end** 成员变量。通常情况下cv::Range包含start值但不包含end值，例如：cv::Range rng(0,4)包含0，1，2，3但不包含4。

使用 **size()** 成员函数可以获得range包含的数目，例如上例rng.size() 为4；使用 **empty()** 可以判断range是否为空；**all()** 包含Range的所有范围。

### 2.3 cv::Ptr 模板和垃圾回收

c++中的智能指针采用引用计数的方式来标识指针的被引用次数，当引用增加时计数会加1，引用减小时计数会减1；当引用计数为0即指针不再需要时，就会被销毁。OpenCV3中的cv::Ptr<>与c++智能指针的作用相同。

使用时需要让Ptr包裹想要创建的指针类型，例如：

```c++
cv::Ptr<Matx33f> p(new cv::Matx33f);
cv::Ptr<Matx33f> p = makePtr<cv::Matx33f>();
```

使用 **addref()和release()** 可以手动控制智能指针的引用计数，但通常情况下不建议使用。**empty()** 可以判断智能指针是否为空，例如智能指针包裹的指针被销毁了或者一开始包裹的指针就为NULL的情况。重写 **delete_obj()** 成员函数，可以在指针销毁的时候做一些需要的处理操作，这个将函数在销毁的时候调用。

> 使用智能指针好的习惯应该是：每次生成指针时都定义delete_obj()操作，来保证销毁时候所有资源被正确释放。

### 2.3 cv::Exception 类和异常处理

OpenCV3继承STL的 **std::exception** 异常定义了自己的 **cv::Exception** 异常类。cv::Exception 包含以下几个变量： **code, err, func, file和line** ，通过这几个变量可以很快定位和查询异常信息。

使用以下方式可以定义自己的异常：

```c++
CV_Error( errorcode, description );
CV_Error_( errorcode, printf_fmt_str, [printf-args] );
CV_Assert( condition );    // Condition test
CV_DbgAssert( condition );    // Condition test
```

### 2.4 cv::DataType<>

cv::DataType<>用于给基础类型提供说明描述，在c++中这种技术称为类特性。简言之，也就是记录某种数据类型深度多少，有几个通道，格式是什么等。定义如下：

```c++
template<typename _Tp> class DataType
{
	typedef _Tp value_type;
	typedef value_type work_type;
	typedef value_type channel_type;
	typedef value_type vec_type;
	enum {
		generic_type = 1,
		depth = -1,
		channels = 1,
		fmt = 0,
		type = CV_MAKETYPE(depth, channels)
	};
};
```

为了更好地理解，我们来看来自core.hpp的两个示例：

```c++
// Defination for float
template<> class DataType<float>
{
public:
	typedef float value_type;
	typedef value_type work_type;
	typedef value_type channel_type;
	typedef value_type vec_type;
	enum {
		generic_type = 0,
		depth = DataDepth<channel_type>::value,
		channels = 1,
		fmt = DataDepth<channel_type>::fmt,
		type = CV_MAKETYPE(depth, channels)
	};
};
```

其中，value_type是float类型，work_type, channel_type和vec_type同样也是float类型；generic_type设置为0，且在core.hpp中的所有类型都被设置为0； depth由cv::DataDepth<float>::value 定义，它的值为CV_32F；channels为1，因为float为单独的一个数；fmt 由cv::DataDepth<float>::fmt  定义，它的值为f；type由CV_MAKETYPE(CV_32F,1) 确定为CV_32FC1 。这样，对于float类型，DataType<float>可以为它提供很好的解释。

下一个例子：

```c++
// Defination for cv::Rect<>
template<typename _Tp> class DataType<Rect_<_Tp> >
{
public:
	typedef Rect_<_Tp> value_type;
	typedef Rect_<typename DataType<_Tp>::work_type> work_type;
	typedef _Tp channel_type;
	typedef Vec<channel_type, channels> vec_type;
	enum {
		generic_type = 0,
		depth = DataDepth<channel_type>::value,
		channels = 4,
		fmt = ((channels-1)<<8) + DataDepth<channel_type>::fmt,
		type = CV_MAKETYPE(depth, channels)
	};
};
```

### 2.5 cv::InputArray和cv::OutputArray

cv::InputArray和cv::OutputArray代指所有的数组类型，使用它们可以简化输入输出而不需要关心具体的类型，更像是一种数组容器。cv::InputArray默认是const的，即只读的；而cv::OutputArray则无此限制。当无需输入或输出时，可以使用 **cv::noArray()** 。



##三：其他实用功能

OpenCV3也提供了一些经常用于计算机视觉的实用功能，列举如下，具体的信息可参照相关文档：

| 功能                      | 描述                                       |
| ----------------------- | ---------------------------------------- |
| cv::alignPtr()          | Align pointer to given number of bytes   |
| cv::alignSize()         | Align buffer size to given number of bytes |
| cv::allocate()          | Allocate a C-style array of objects      |
| cvCeil()                | Round float number x to nearest integer not smaller than x |
| cv::cubeRoot()          | Compute the cube root of a number        |
| cv::CV_Assert()         | Throw an exception if a given condition is not true |
| CV_Error()              | Macro to build a cv::Exception (from a fixed string) and throw it |
| CV_Error_()             | Macro to build a cv::Exception (from a formatted string) and throw it |
| cv::deallocate()        | Deallocate a C-style array of objects    |
| cv::error()             | Indicate an error and throw an exception |
| cv::fastAtan2()         | Calculate two-dimensional angle of a vector in degrees |
| cv::fastFree()          | Deallocate a memory buffer               |
| cv::fastMalloc()        | Allocate an aligned memory buffer        |
| cvFloor()               | Round float number x to nearest integer not larger than x |
| cv::format()            | Create an STL string using sprintf-like formatting |
| cv::getCPUTickCount()   | Get tick count from internal CPU timer   |
| cv::getNumThreads()     | Count number of threads currently used by OpenCV |
| cv::getOptimalDFTSize() | Compute the best size for an array that you plan to pass to cv::DFT() |
| cv::getThreadNum()      | Get index of the current thread          |
| cv::getTickCount()      | Get tick count from system               |
| cv::getTickFrequency()  | Get number or ticks per second (see cv::getTickCount()) |
| cvIsInf()               | Check if a floating-point number x is infinity |
| cvIsNaN()               | Check if a floating-point number x is “Not a Number” |
| cvRound()               | Round float number x to the nearest integer |
| cv::setNumThreads()     | Set number of threads used by OpenCV     |
| cv::setUseOptimized()   | Enables or disables the use of optimized code (SSE2, etc.) |
| cv::useOptimized()      | Indicates status of optimized code enabling (see cv::setUseOptimized()) |

