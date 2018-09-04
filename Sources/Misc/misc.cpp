#include "misc.h"


CMisc::CMisc()
{
}

CMisc::~CMisc()
{
}

void CMisc::image_io(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	cvtColor(src, dst, CV_BGR2GRAY);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);

	imwrite("./output.jpg", dst);
}

void CMisc::mat_create(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Create mat
	Mat dst;
	// [1]
	//dst = Mat(src.size(), src.type());
	//dst = Scalar(0, 0, 255);
	// [2]
	//src.copyTo(dst);
	//dst = src.clone();
	// [3]
	//Mat dst(100, 100, CV_8UC3, Scalar(0, 0, 255));
	// [4]
	//dst.create(src.size(), src.type());
	// [5]
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(src, dst, -1, kernel);
	// [6]
	//dst = Mat::zeros(src.size(), src.type());

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMisc::mat_operator(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Iterator
	// [1]
	/*for (int row = 0; row < src_gray.rows; row++) {
		uchar *row_ptr = src_gray.ptr<uchar>(row);
		for (int col = 0; col < src_gray.cols; col++) {
			row_ptr[col] = 255 - row_ptr[col];
		}
	}*/
	// [2]
	for (int row = 0; row < src_gray.rows; row++) {
		for (int col = 0; col < src_gray.cols; col++) {
			src_gray.at<uchar>(row, col) = 255 - src_gray.at<uchar>(row, col);
		}
	}

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", src_gray);
	waitKey(0);
}

void CMisc::mixture(const string img_path1, const string img_path2)
{
	// g(x) = (1-a)f0(x) + af1(x)

	Mat src1 = imread(img_path1);
	if (src1.empty())
		return;
	Mat src2 = imread(img_path2);
	if (src1.empty())
		return;
	if (src1.rows != src2.rows || src1.cols != src2.cols || src1.type() != src2.type())
		return;

	Mat dst;
	double a = 0.5;
	addWeighted(src1, a, src2, 1.0 - a, 0.0, dst);

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMisc::light_contrast(const string &img_path)
{
	// g(i,j) = af(i,j) + b

	Mat src = imread(img_path);
	if (src.empty())
		return;

	double a = 1.2;
	double b = 30;
	Mat dst = Mat::zeros(src.size(), src.type());
	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			if (1 == src.channels()) {
				dst.at<uchar>(row, col) = saturate_cast<uchar>(src.at<uchar>(row, col) * a + b);
			}
			else if (3 == src.channels()) {
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(src.at<Vec3b>(row, col)[0] * a + b);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(src.at<Vec3b>(row, col)[1] * a + b);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(src.at<Vec3b>(row, col)[2] * a + b);
			}
		}
	}

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMisc::draw(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Point p1(20, 20);
	Point p2(100, 100);
	line(src, p1, p2, Scalar(0, 0, 255), 1, LINE_AA);
	Rect rect(20, 10, 100, 100);
	rectangle(src, rect, Scalar(255, 0, 0), 1, LINE_AA);
	ellipse(src, Point(src.cols / 2, src.rows / 2), Size(src.cols / 4, src.rows / 8), 90, 0, 360, Scalar(0, 255, 0), 1, LINE_AA);
	circle(src, Point(src.cols / 2, src.rows / 2), 50, Scalar(0, 255, 255), 1, LINE_AA);
	Point pts[1][5];
	pts[0][0] = Point(10, 10);
	pts[0][1] = Point(10, 20);
	pts[0][2] = Point(20, 20);
	pts[0][3] = Point(20, 10);
	pts[0][4] = Point(10, 10);
	const Point *ppts[] = { pts[0] };
	int npt[] = { 5 };
	fillPoly(src, ppts, npt, 1, Scalar(255, 12, 255), LINE_AA);
	putText(src, "Hello OpenCV", Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1.0, Scalar(12, 23, 200), 1, LINE_AA);

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", src);
	waitKey(0);
}

void CMisc::pyramid(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Pyramid
	//Mat dst;
	//pyrUp(src, dst);
	//pyrDown(src, dst);

	// DOG
	Mat dst1, dst2, dog;
	GaussianBlur(src_gray, dst1, Size(3, 3), 0);
	GaussianBlur(dst1, dst2, Size(3, 3), 0);
	subtract(dst1, dst2, dog);
	normalize(dog, dog, 255, 0, NORM_MINMAX);

	namedWindow("OUTPUT", CV_WINDOW_AUTOSIZE);
	imshow("OUTPUT", dog);
	waitKey(0);
}
