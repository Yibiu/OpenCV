# 大型数据操作

[TOC]

上一章介绍了OpenCV3大型数据的存储如cv::Mat<>和cv::SparseMat<>以及它们的一些基本操作。这一章将继续介绍针对Mat类型的一些其他常用操作。



##Mat的操作

| 函数                         | 描述                                       |
| -------------------------- | ---------------------------------------- |
| cv::abs()                  | Return absolute value of all elements in an array |
| cv::absdiff()              | Return absolute value of differences between two arrays |
| cv::add()                  | Perform element-wise addition of two arrays |
| cv::addWeighted()          | Perform element-wise weighted addition of two arrays (alpha blending) |
| cv::bitwise_and()          | Compute element-wise bit-level AND of two arrays |
| cv::bitwise_not()          | Compute element-wise bit-level NOT of two arrays |
| cv::bitwise_or()           | Compute element-wise bit-level OR of two arrays |
| cv::bitwise_xor()          | Compute element-wise bit-level XOR of two arrays |
| cv::calcCovarMatrix()      | Compute covariance of a set of n-dimensional vectors |
| cv::cartToPolar()          | Compute angle and magnitude from a two-dimensional vector field |
| cv::checkRange()           | Check array for invalid values           |
| cv::compare()              | Apply selected comparison operator to all elements in two arrays |
| cv::completeSymm()         | Symmetrize matrix by copying elements from one half to the other |
| cv::convertScaleAbs()      | Scale array, take absolute value, then convert to 8-bit unsigned |
| cv::countNonZero()         | Count nonzero elements in an array       |
| cv::arrToMat()             | Convert pre–version 2.1 array types to cv::Mat |
| cv::dct()                  | Compute discrete cosine transform of array |
| cv::determinant()          | Compute determinant of a square matrix   |
| cv::dft()                  | Compute discrete Fourier transform of array |
| cv::divide()               | Perform element-wise division of one array by another |
| cv::eigen()                | Compute eigenvalues and eigenvectors of a square matrix |
| cv::exp()                  | Perform element-wise exponentiation of array |
| cv::extractImageCOI()      | Extract single channel from pre–version 2.1 array type |
| cv::flip()                 | Flip an array about a selected axis      |
| cv::gemm()                 | Perform generalized matrix multiplication |
| cv::getConvertElem()       | Get a single-pixel type conversion function |
| cv::getConvertScaleElem()  | Get a single-pixel type conversion and scale function |
| cv::idct()                 | Compute inverse discrete cosine transform of array |
| cv::idft()                 | Compute inverse discrete Fourier transform of array |
| cv::inRange()              | Test if elements of an array are within values of two other arrays |
| cv::invert()               | Invert a square matrix                   |
| cv::log()                  | Compute element-wise natural log of array |
| cv::magnitude()            | Compute magnitudes from a two-dimensional vector field |
| cv::LUT()                  | Convert array to indices of a lookup table |
| cv::Mahalanobis()          | Compute Mahalanobis distance between two vectors |
| cv::max()                  | Compute element-wise maxima between two arrays |
| cv::mean()                 | Compute the average of the array elements |
| cv::meanStdDev()           | Compute the average and standard deviation of the array elements |
| cv::merge()                | Merge several single-channel arrays into one multichannel array |
| cv::min()                  | Compute element-wise minima between two arrays |
| cv::minMaxLoc()            | Find minimum and maximum values in an array |
| cv::mixChannels()          | Shuffle channels from input arrays to output arrays |
| cv::mulSpectrums()         | Compute element-wise multiplication of two Fourier spectra |
| cv::multiply()             | Perform element-wise multiplication of two arrays |
| cv::mulTransposed()        | Calculate matrix product of one array    |
| cv::norm()                 | Compute normalized correlations between two arrays |
| cv::normalize()            | Normalize elements in an array to some value |
| cv::perspectiveTransform(） | Perform perspective matrix transform of a list of vectors |
| cv::phase()                | Compute orientations from a two-dimensional vector field |
| cv::polarToCart()          | Compute two-dimensional vector field from angles and magnitudes |
| cv::pow()                  | Raise every element of an array to a given power |
| cv::randu()                | Fill a given array with uniformly distributed random numbers |
| cv::randn()                | Fill a given array with normally distributed random numbers |
| cv::randShuffle()          | Randomly shuffle array elements          |
| cv::reduce()               | Reduce a two-dimensional array to a vector by a given operation |
| cv::repeat()               | Tile the contents of one array into another |
| cv::saturate_cast<>()      | Convert primitive types (template function) |
| cv::scaleAdd()             | Compute element-wise sum of two arrays with optional scaling of the first |
| cv::setIdentity()          | Set all elements of an array to 1 for the diagonal and 0 otherwise |
| cv::solve()                | Solve a system of linear equations       |
| cv::solveCubic()           | Find the (only) real roots of a cubic equation |
| cv::solvePoly()            | Find the complex roots of a polynomial equation |
| cv::sort()                 | Sort elements in either the rows or columns in an array |
| cv::sortIdx()              | Serve same purpose as cv::sort(), except array is unmodified and indices arereturned |
| cv::split()                | Split a multichannel array into multiple single-channel arrays |
| cv::sqrt()                 | Compute element-wise square root of an array |
| cv::subtract()             | Perform element-wise subtraction of one array from another |
| cv::sum()                  | Sum all elements of an array             |
| cv::theRNG()               | Return a random number generator         |
| cv::trace()                | Compute the trace of an array            |
| cv::transform()            | Apply matrix transformation on every element of an array |
| cv::transpose()            | Transpose all elements of an array across the diagonal |

