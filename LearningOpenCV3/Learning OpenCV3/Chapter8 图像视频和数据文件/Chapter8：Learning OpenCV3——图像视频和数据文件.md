# 图像、视频和数据文件

[TOC]

OpenCV的HighGUI功能模块允许我们和操作系统、文件系统以及硬件打交道。使用HighGUI模块可以实现图像文件的读写、窗口的创建、图像的显示和进行简单的事件处理。前面第二章也简单介绍过关于HighGUI的内容。

本章将介绍High GUI模块对静态图片和动态视频的采集和存储。我们将学习使用OpenCV的HighGUI平台无关功能怎样实现图像的窗口级操作。



## 一：HighGUI介绍

HighGUI可以被分为三个部分： **硬件部分、文件系统部分和GUI部分**。

**硬件部分** 主要与相机（Camera）的操作相关。在很多操作系统中，相机的操作极其繁琐，OpenCV3使用便捷的方式控制相机，很轻松地读取相机地最新帧。

**文件系统**主要涉及图片地读取和保存。此外，对相机地读取我们也可以使用与处理图片同套的操作完成，极大地简化了整个流程。OpenCV也提供了一套对XML/YML格式文件读取和存储的操作，使用它们可以以易读易改的方式存储图片。

**HighGUI** 是窗口系统（或GUI）。它允许我们使用简单的功能创建窗口，并将图像显示在窗口；同样，它也支持很多相应的窗口事件。

> 在OpenCV3中，HighGUI被分割为3个模块：imgcodecs(image encoding/decoding)，videoio(capturing and encoding video)和highgui(UI)。为了更好地向下兼容，highgui.hpp头文件包含了videoio.hpp和imgcodecs.hpp，因此我们也可以独立使用每个模块。但我们通常说的HighGUI实则是包含了这三个模块的。



## 二：图像文件的操作

### 2.1 读取和保存图片

cv::imread()用于读取图片，cv::imwrite()用于存储图片。对图片的编解码功能同样由它们完成，但操作是相当简单的。

####2.1.1 cv::imread

```c++
cv::Mat cv::imread(
	const string& filename, // Input filename
	int flags = cv::IMREAD_COLOR // Flags set how to interpret file
);
```

当打开一幅图片时，cv::imread()并不看文件名的后缀，而是通过分析文件前面的一些字节来确定文件类型并决定采用哪种类型的编解码器。flags的取值如下表：

| FLAGS                | 意义                                       |
| -------------------- | ---------------------------------------- |
| cv::IMREAD_COLOR     | Always load to three-channel array. (Default) |
| cv::IMREAD_GRAYSCALE | Always load to single-channel array.     |
| cv::IMREAD_ANYCOLOR  | Channels as indicated by file (up to three). |
| cv::IMREAD_ANYDEPTH  | Allow loading of more than 8-bit depth.  |
| cv::IMREAD_UNCHANGED | Equivalent to combining: cv::IMREAD_ANYCOLOR \| cv::IMREAD_ANYDEPTH |

flags取值为cv::IMREAD_COLOR，意味着读取3通道的彩色图像，每个通道为8bits。这种情况下，即使原图像是灰色图像，也将被当作3通道图像读取。cv::IMREAD_GRAYSCALE图片当作灰度图像读取。cv::IMREAD_ANYCOLOR将图片按照图片本身的颜色格式读取，3通道彩色图像或者1通道的灰度图像。当图像深度大于8bits时，可以指定cv::IMREAD_ANYDEPTH标志按原有深度读取图像。

####2.1.2 cv::imwrite

```c++
bool cv::imwrite(
	const string& filename, // Input filename
	cv::InputArray image, // Image to write to file
	const vector<int>& params = vector<int>() // (Optional) for parameterized fmts
);
```

第一个参数为文件名，文件名的扩展指定了图片格式，OpenCV3支持的扩展有：

- .jpg or .jpeg: baseline JPEG; 8-bit; one- or three-channel input
- .jp2: JPEG 2000; 8-bit or 16-bit; one- or three-channel input
- .tif or .tiff: TIFF; 8- or 16-bit; one-, three-, or four-channel input
- .png: PNG; 8- or 16-bit; one-, three-, or four-channel input
- .bmp: BMP; 8-bit; one-, three-, or four-channel input
- .ppm, .pgm: NetPBM; 8-bit; one-channel (PGM) or three-channel (PPM) 

第二个参数为要存储的图像数据。第三个参数由特定的图像格式使用，params参数可以为：

| Parameter ID                | 意义                                       | 范围     | 默认值  |
| --------------------------- | ---------------------------------------- | ------ | ---- |
| cv::IMWRITE_JPG_QUALITY     | JPEG quality                             | 0–100  | 95   |
| cv::IMWRITE_PNG_COMPRESSION | PNG compression (higher values mean more compression) | 0-9    | 3    |
| cv::IMWRITE_PXM_BINARY      | Use binary format for PPM, PGM, or PBM files | 0 or 1 | 1    |

cv::imwrite() 一般只支持8bit单通道或者三通道（BGR）图像，对于特定图片类型，例如PNG、TIF或JPEG 2000可以存储16bit甚至float类型的数据；某些类型也可以存储4通道（BGRA）。

> 图像格式的读取和存储依赖特定的编解码器。OpenCV3使用编解码器有三种情况：1. 不包含特定的编解码器；2. 包含OpenCV提供的编解码器（需要在OpenCV编译的时候和其他模块一起编译）；3. 使用外部编解码库（例如libjpeg, libpng 等）。Windows系统默认是第二种情况，Linux系统默认是第三种情况。

###2.2 压缩和解压缩

如果不是在图片读取和写出的时候编解码，而是需要在程序中使用编解码的数据，则也可以使用OpenCV提供的接口完成。

#### 2.2.1 cv::imencode()

cv::imencode()可以对OpenCV图像数据直接进行压缩，这种情况的输出不是OpenCV的数组类型，而是字节数组。

```c++
void cv::imencode(
	const string& ext, // Extension specifies codec
	cv::InputArray img, // Image to be encoded
	vector<uchar>& buf, // Encoded file bytes go here
	const vector<int>& params = vector<int>() // (Optional) for parameterized fmts
);
```

"ext"为格式扩展，指定编码的类型和特定的编码器。img是输入的编码图像数组；buf为编码完成存储的数据，它的大小由函数自动调整；params由特定编码器使用，意义和cv::imwrite()的params参数一样。

#### 2.2.2 cv::imdecode() 

cv::imdecode() 实现OpenCV图像数据的解压缩。

```c++
cv::Mat cv::imdecode(
	cv::InputArray buf, // Encoded file bytes are here
	int flags = cv::IMREAD_COLOR // Flags set how to interpret file
);
```

第一个参数为待解压缩图像数据，通常为std::vector<uchar> 格式，与cv::imencode()的输出一致。flags参数的含义和cv::imread()的flags参数一致。解码时无需指定特定的文件扩展，因为OpenCV会根据待解码数据的信息来自动确定解码器的类型。



## 三：视频的操作

###3.1 cv::VideoCapture 

前面介绍过，cv::VideoCaptrure可以用于从文件或者相机中获取视频。创建方式：

```c++
cv::VideoCapture::VideoCapture(
	const string& filename, // Input filename
);
cv::VideoCapture::VideoCapture(
	int device // Video capture device id
);
cv::VideoCapture::VideoCapture();
```

当无参构造时，后续可通过 **open()** 方式打开视频采集设备。通过检查 **cv::VideoCapture::isOpened()** 的返回值可以确定是否创建成功。通常创建失败的可能情况有：文件或者设备不存在、没有找到相应的编解码器以及一些其他情况。

当打开相机时，OpenCV使用一个整形数据标识相机的ID。为了对不同类型的相机进行方便操作，OpenCV使用“domain”号来索引这些相机类型。

| Camera capture constant | Numerical value |
| ----------------------- | --------------- |
| cv::CAP_ANY             | 0               |
| cv::CAP_MIL             | 100             |
| cv::CAP_VFW             | 200             |
| cv::CAP_V4L             | 200             |
| cv::CAP_V4L2            | 200             |
| cv::CAP_FIREWIRE        | 300             |
| cv::CAP_IEEE1394        | 300             |
| cv::CAP_DC1394          | 300             |
| cv::CAP_CMU1394         | 300             |
| cv::CAP_QT              | 500             |
| cv::CAP_DSHOW           | 700             |
| cv::CAP_PVAPI           | 800             |
| cv::CAP_OPENNI          | 900             |
| cv::CAP_ANDROID         | 1000            |
| ......                  |                 |

例如：

```c++
cv::VideoCapture capture( cv::CAP_FIREWIRE );
```

OpenCV将尝试打开第一个FireWire类型的相机。通常情况下，当我们只有一个相机时“domain”无关紧要，使用cv::CAP_ANY索引即可。某些平台传入-1参数可以跳出设备选择窗口。

###3.2 读取视频

获得cv::VideoCapture对象之后就可以读取视频帧了。OpenCV3提供以下几种读取视频帧的方式。

#### 3.2.1 cv::VideoCapture::read()

```c++
bool cv::VideoCapture::read(
	cv::OutputArray image // Image into which to read data
);
```

基本的读取帧方式，一帧一帧读取，会自动读取下一帧内容。成功与否由返回的bool值确定。

#### 3.2.2 cv::VideoCapture::operator>>() 

```c++
cv::VideoCapture& cv::VideoCapture::operator>>(
	cv::Mat& image // Image into which to read data
);
```

与read()操作类似，不同之处在于读取成功与否需要判断读取的数组是否为空。

#### 3.2.3 cv::VideoCapture::grab()和cv::VideoCapture::retrieve() 

上述的read()和流去取将视频读取和解码同时完成，也可以使用grab()和retrieve()分步完成视频的获取和解码。

```c++
bool cv::VideoCapture::grab( void );
bool cv::VideoCapture::retrieve(
	cv::OutputArray image, // Image into which to read data
	int channel = 0 // Used for multihead devices
);
```

grab()将当前的图像数组拷贝到OpenCV内部的一个不可见内存内，之后retrieve()对视频帧进行解码和一些必要的拷贝处理。另外，retrieve()的channel参数可以指定特定的视频通道，对于某些多目相机同时会采集多于一路的视频，此时可以grab()一次，retrieve()多次（每个通道一次）。

> 为什么需要将采集和解码分开处理呢？当有多个相机时，read()或流读取会占用大量的时间，为了保证视频采集的实时性和同时性，使用grab()和retrieve()分开操作更为合理。

### 3.3 相机属性设置

不管是文件还是相机，不仅包含视频数据，还会包含视频属性，这些属性在对视频进行操作时候必不可少。因此，获取和设置它们的属性就变得相当重要。使用 **get()和set()** 可以很方便的读取和设置属性：

```c++
double cv::VideoCapture::get(
	int propid // Property identifier (see Table 8-4)
);
bool cv::VideoCapture::set(
	int propid // Property identifier (see Table 8-4)
	double value // Value to which to set the property
);
```

支持的propid如下：

| Video capture property     | Camera only | Meaning                                  |
| -------------------------- | ----------- | ---------------------------------------- |
| cv::CAP_PROP_POS_MSEC      |             | Current position in video file (milliseconds) or videocapture timestamp |
| cv::CAP_PROP_POS_FRAMES    |             | Zero-based index of next frame           |
| cv::CAP_PROP_POS_AVI_RATIO |             | Relative position in the video (range is 0.0 to 1.0) |
| cv::CAP_PROP_FRAME_WIDTH   |             | Width of frames in the video             |
| cv::CAP_PROP_FRAME_HEIGHT  |             | Height of frames in the video            |
| cv::CAP_PROP_FPS           |             | Frame rate at which the video was recorded |
| cv::CAP_PROP_FOURCC        |             | Four character code indicating codec     |
| cv::CAP_PROP_FRAME_COUNT   |             | Total number of frames in a video file   |
| cv::CAP_PROP_FORMAT        |             | Format of the Mat objects returned (e.g., CV_8UC3) |
| cv::CAP_PROP_MODE          |             | Indicates capture mode; values are specific to videobackend being used (e.g., DC1394) |
| cv::CAP_PROP_BRIGHTNESS    | ✓           | Brightness setting for camera (when supported) |
| cv::CAP_PROP_CONTRAST      | ✓           | Contrast setting for camera (when supported) |
| cv::CAP_PROP_SATURATION    | ✓           | Saturation setting for camera (when supported) |
| cv::CAP_PROP_HUE           | ✓           | Hue setting for camera (when supported)  |
| cv::CAP_PROP_GAIN          | ✓           | Gain setting for camera (when supported) |
| cv::CAP_PROP_EXPOSURE      | ✓           | Exposure setting for camera (when supported) |
| cv::CAP_PROP_CONVERT_RGB   | ✓           | If nonzero, captured images will be converted to havethree channels |
| cv::CAP_PROP_WHITE_BALANCE | ✓           | White balance setting for camera (when supported) |
| cv::CAP_PROP_RECTIFICATION | ✓           | Rectification flag for stereo cameras (DC1394-2.x only) |

所有属性都是double类型值，除了cv::CAP_PROP_FOURCC属性的操作：

```c++
cv::VideoCapture cap( "my_video.avi" );

unsigned f = (unsigned)cap.get( cv::CAP_PROP_FOURCC );
char fourcc[] = {
	(char) f, // First character is lowest bits
	(char)(f >> 8), // Next character is bits 8-15
	(char)(f >> 16), // Next character is bits 16-23
	(char)(f >> 24), // Last character is bits 24-31
	'\0' // and don't forget to terminate
};
```

### 3.4 存储视频

视频存储使用 **cv::VideoWriter** 类完成，常用的构造方式有如下两种：

```c++
// Construct method
cv::VideoWriter::VideoWriter(
	const string& filename, // Input filename
	int fourcc, // codec, use CV_FOURCC() macro
	double fps, // Frame rate (stored in output file)
	cv::Size frame_size, // Size of individual images
	bool is_color = true // if false, you can pass gray frames
);

// Open method
cv::VideoWriter out;
out.open(
	"my_video.mpg",
	CV_FOURCC('D','I','V','X'), // MPEG-4 codec
	30.0, // Frame rate (FPS)
	cv::Size( 640, 480 ), // Write out frames at 640x480 resolution
	true // Expect only color frames
);
```

这里需要指定一些例如编码参数、帧率等信息，为的是方便读取。设置完成后就可以使用如下方式写视频了：

```c++
cv::VideoWriter::write(
	const Mat& image // Image to write as next frame
);

my_video_writer << my_frame;
```



## 四：数据持久化
除了基本的视频处理，OpenCV3还提供了针对YAML和XML格式的数据处理机制和接口。这些接口可以处理任何类型的数据（int、float等）。读写此类文件的基本机制是 **cv::FileStorage** 对象，简单来说，这个对象就代表磁盘上的一个文件。
### 4.1 创建cv::FileStorage
cv::FileStorage的创建方式有两种：
```c++
// 先声明后打开
FileStorage::FileStorage();
FileStorage::open( string fileName, int flag );

// 直接创建
FileStorage::FileStorage( string fileName, int flag );
```
其中，fileName为YAML或XML格式的文件名称。flag标志在写入时为**cv::FileStorage::WRITE 或 cv::FileStorage::APPEND** ；在读取时为 **cv::FileStorage::READ** 。 
###4.2 写入到cv::FileStorage
cv::FileStorage的存储有一到两种形式：mapping（i.e.，key/value对形式）和seauence（一系列非命名单元形式）。在上层写入的时候全部以mapping的形式写入，并且可以嵌套使用。“{}”和“[]”符号可分别用于sequence和mapping。
```c++
// common storage
myFileStorage << "someInteger" << 27; // save an integer
myFileStorage << "anArray" << cv::Mat::eye(3,3,CV_32F); // save an array

// sequence
myFileStorage << "theCat" << "{";
myFileStorage << "fur" << "gray" << "eyes" << "green" << "weightLbs" << 16;
myFileStorage << "}";

// mapping
myFileStorage << "theTeam" << "[";
myFileStorage << "eddie" << "tom" << "scott";
myFileStorage << "]";
```
使用完毕后需要 **cv::FileStorage::release()** 关闭文件。以下例程创建了一个test.yml文件：
```c++
#include "opencv2/opencv.hpp"
#include <time.h>

int main(int, char** argv)
{
	cv::FileStorage fs("test.yml", cv::FileStorage::WRITE);
	
  	fs << "frameCount" << 5;
	time_t rawtime; time(&rawtime);
	fs << "calibrationDate" << asctime(localtime(&rawtime));
	cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	cv::Mat distCoeffs = (cv::Mat_<double>(5,1)<< 0.1, 0.01, -0.001, 0, 0);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	fs << "features" << "[";
	for( int i = 0; i < 3; i++ )
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;
		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for( int j = 0; j < 8; j++ )
		fs << ((lbp >> j) & 1);
		fs << "]" << "}";
	}
	fs << "]";

  	fs.release();
	return 0;
}
```
运行的结果为：
```c++
%YAML:1.0
frameCount: 5
calibrationDate: "Fri Jun 17 14:09:29 2011\n"
cameraMatrix: !!opencv-matrix
rows: 3
cols: 3
dt: d
data: [ 1000., 0., 320., 0., 1000., 240., 0., 0., 1. ]
distCoeffs: !!opencv-matrix
rows: 5
cols: 1
dt: d
data: [ 1.0000000000000001e-01, 1.0000000000000000e-02,
-1.0000000000000000e-03, 0., 0. ]
features:
- { x:167, y:49, lbp:[ 1, 0, 0, 1, 1, 0, 1, 1 ] }
- { x:298, y:130, lbp:[ 0, 0, 0, 1, 0, 0, 1, 1 ] }
- { x:344, y:158, lbp:[ 1, 1, 0, 0, 0, 0, 1, 0 ] }
```
### 4.3 读取cv::FileStorage
从cv::FileStorage中读取可以使用 **cv::FileStorage::operator[]() 或者cv::FileNodeIterator ** 。读取的返回值并不是直接值，而是 **cv::FileNode** 形式。
```c++
cv::Mat anArray;
myFileStorage["calibrationMatrix"] >> anArray;// Mat类型
int aNumber;
myFileStorage["someInteger"] >> aNumber;// int类型
int aNumber;
aNumber = (int)myFileStorage["someInteger"];// int类型
```
使用cv::FileNodeIterator迭代也可以逐个访问cv::FileNode的数据。使用 **cv::FileNode::name()** 可以获取Node的名称；使用 **cv::FileNode::type()** 可以获取Node的数据类型，可能的返回值有：
| 返回值                                      | 解释                                       |
| ---------------------------------------- | ---------------------------------------- |
| cv::FileNode::NONE = 0                   | Node is of type None                     |
| cv::FileNode::INT = 1                    | Node contains an integer                 |
| cv::FileNode::REAL = 2<br />cv::FileNode::FLOAT = 2 | Node contains a floating-point number    |
| cv::FileNode::STR = 3<br />cv::FileNode::STRING = 3 | Node contains a string                   |
| cv::FileNode::REF = 4                    | Node contains a reference (i.e., a compound object) |
| cv::FileNode::SEQ = 5                    | Node is itself a sequence of other nodes |
| cv::FileNode::MAP = 6                    | Node is itself a mapping of other nodes  |
| cv::FileNode::FLOW = 8                   | Node is a compact representation of a sequence or mapping |
| cv::FileNode::USER = 16                  | Node is a registered object (e.g., a matrix) |
| cv::FileNode::EMPTY = 32                 | Node has no value assigned to it         |
| cv::FileNode::NAMED = 64                 | Node is a child of a mapping (i.e., it has a name) |
cv::Node支持的操作有：
| 操作                                       | 描述                                       |
| ---------------------------------------- | ---------------------------------------- |
| cv::FileNode fn                          | File node object default constructor     |
| cv::FileNode fn1( fn0 )                  | File node object copy constructor; creates a node fn1 from anode fn0 |
| cv::FileNode fn1( fs, node )             | File node constructor; creates a C++ style cv::FileNodeobject from a C-style CvFileStorage* pointer fs and aC-style CvFileNode* pointer node |
| fn[ (string)key ]<br />fn[ (const char*)key ] | STL string or C-string accessor for named child (of mappingnode); converts key to the appropriate child node |
| fn[ (int)id ]                            | Accessor for numbered child (of sequence node); converts IDto the appropriate child node |
| fn.type()                                | Returns node type enum                   |
| fn.empty()                               | Determines if node is empty              |
| fn.isNone()                              | Determines if node has value None        |
| fn.isSeq()                               | Determines if node is a sequence         |
| fn.isMap()                               | Determines if node is a mapping          |
| fn.isInt()<br />fn.isReal()<br />fn.isString() | Determines if node is an integer, a floating-point number, ora string (respectively) |
| fn.name()                                | Returns nodes name if node is a child of a mapping |
| size_t sz=fn.size()                      | Returns a number of elements in a sequence or mapping |
| (int)fn(float)fn(double)fn(string)fn     | Extracts the value from a node containing an integer, 32-bitfloat, 64-bit float, or string (respectively) |
以下为读取test.yml的示例：
```c++
cv::FileStorage fs2("test.yml", cv::FileStorage::READ);

// first method: use (type) operator on FileNode.
int frameCount = (int)fs2["frameCount"];

// second method: use cv::FileNode::operator >>
std::string date;
cv::Mat cameraMatrix2, distCoeffs2;
fs2["calibrationDate"] >> date;
fs2["cameraMatrix"] >> cameraMatrix2;
fs2["distCoeffs"] >> distCoeffs2;
cout << "frameCount: " << frameCount << endl
	<< "calibration date: " << date << endl
	<< "camera matrix: " << cameraMatrix2 << endl
	<< "distortion coeffs: " << distCoeffs2 << endl;

cv::FileNode features = fs2["features"];
cv::FileNodeIterator it = features.begin(), it_end = features.end();
int idx = 0;
std::vector<uchar> lbpval;
// iterate through a sequence using FileNodeIterator
for( ; it != it_end; ++it, idx++ )
{
	cout << "feature #" << idx << ": ";
	cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
	(*it)["lbp"] >> lbpval;
	for( int i = 0; i < (int)lbpval.size(); i++ )
		cout << " " << (int)lbpval[i];
	cout << ")" << endl;
}
fs.release();
```



