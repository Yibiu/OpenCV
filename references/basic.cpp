#include "basic.h"


CBasic::CBasic()
{
}

CBasic::~CBasic()
{
}

void CBasic::test_load(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Color convert
	Mat dst;
	cvtColor(src, dst, CV_BGR2GRAY);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);

	// Save
	imwrite("./output.jpg", dst);
}

void CBasic::test_conv(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;
	
	// Convolution
	Mat dst = Mat::zeros(src.size(), src.type());
	for (int row = 1; row < src.rows - 1; row++) {
		uchar *pre_ptr = src.ptr<uchar>(row - 1);
		uchar *cur_ptr = src.ptr<uchar>(row);
		uchar *next_ptr = src.ptr<uchar>(row + 1);
		uchar *output_ptr = dst.ptr<uchar>(row);
		for (int col = 1 * src.channels(); col < (src.cols - 1) * src.channels(); col++) {
			for (int i = 0; i < src.channels(); i++) {
				output_ptr[col + i] = saturate_cast<uchar>(5 * cur_ptr[col + i] - (cur_ptr[col - src.channels() + i] + cur_ptr[col + src.channels() + i] + pre_ptr[col + i] + next_ptr[col + i]));
			}
		}
	}

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_mat(string &img_path)
{
	// Load
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

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_operator(string &img_path)
{
	// Load
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

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", src_gray);
	waitKey(0);
}

void CBasic::test_mixture(string &img_path1, string img_path2)
{
	// g(x) = (1-a)f0(x) + af1(x)

	// Load
	Mat src1 = imread(img_path1);
	if (src1.empty())
		return;
	Mat src2 = imread(img_path2);
	if (src1.empty())
		return;
	if (src1.rows != src2.rows || src1.cols != src2.cols || src1.type() != src2.type())
		return;

	// Mixture
	Mat dst;
	double a = 0.5;
	addWeighted(src1, a, src2, 1.0 - a, 0.0, dst);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_light_contrast(string &img_path)
{
	// g(i,j) = af(i,j) + b

	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Light and contrast
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

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_draw(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Draw
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

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", src);
	waitKey(0);
}

void CBasic::test_smooth(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Smooth
	Mat dst;
	//blur(src, dst, Size(3, 3));
	//GaussianBlur(src, dst, Size(5, 5), 11);
	//medianBlur(src, dst, 3);
	bilateralFilter(src, dst, 15, 100, 3);
	Mat result;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(dst, result, -1, kernel);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", result);
	waitKey(0);
}

void CBasic::test_morphology(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Morphology
	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate(src, dst, kernel);
	//erode(src, dst, kernel);
	//morphologyEx(src, dst, CV_MOP_OPEN, kernel);
	//morphologyEx(src, dst, CV_MOP_CLOSE, kernel);
	//morphologyEx(src, dst, CV_MOP_GRADIENT, kernel);
	//morphologyEx(src, dst, CV_MOP_TOPHAT, kernel);
	morphologyEx(src, dst, CV_MOP_BLACKHAT, kernel);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_morphology_line(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Morphology line
	Mat temp, dst;
	adaptiveThreshold(src_gray, temp, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1));
	Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16));
	morphologyEx(temp, dst, MORPH_OPEN, hline);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_pyramid(string &img_path)
{
	// Load
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

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dog);
	waitKey(0);
}

void CBasic::test_threshold(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Threshold
	Mat dst;
	//threshold(src_gray, dst, 150, 255, THRESH_BINARY);
	threshold(src_gray, dst, 150, 255, THRESH_OTSU);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_filter(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Filter
	Mat dst;
	Mat robert_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
	Mat robert_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);
	//filter2D(src, dst, -1, robert_x);
	//filter2D(src, dst, -1, robert_y);
	Mat sobel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	Mat sobel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	//filter2D(src, dst, -1, sobel_x);
	//filter2D(src, dst, -1, sobel_y);
	Mat laplance = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	filter2D(src, dst, -1, laplance);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_border(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Border
	int top = 0.05 * src.rows;
	int bottom = 0.05 * src.rows;
	int left = 0.05 * src.cols;
	int right = 0.05 * src.cols;
	int border_type = BORDER_DEFAULT;
	while (true)
	{
		int c = waitKey(500);
		if (c == '1') {
			border_type = BORDER_REPLICATE;
		}
		else if (c == '2') {
			border_type = BORDER_WRAP;
		}
		else if (c == '3') {
			border_type = BORDER_CONSTANT;
		}
		else if (c == 'e') {
			break;
		}

		Mat dst;
		copyMakeBorder(src, dst, top, bottom, left, right, border_type);
		imshow("BASIC", dst);
	}
}

void CBasic::test_edage(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;

	// Edage
	// Sobel
	/*Mat src_gray, dst;
	GaussianBlur(src, dst, Size(3, 3), 0);
	cvtColor(dst, src_gray, CV_BGR2GRAY);
	Mat grad_x, grad_y;
	//Sobel(src_gray, grad_x, CV_16S, 1, 0);
	//Sobel(src_gray, grad_y, CV_16S, 0, 1);
	Scharr(src_gray, grad_x, CV_16S, 1, 0);
	Scharr(src_gray, grad_y, CV_16S, 0, 1);
	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);*/
	// Laplance
	Mat src_gray, dst;
	GaussianBlur(src, dst, Size(3, 3), 0);
	cvtColor(dst, src_gray, CV_BGR2GRAY);
	Laplacian(src_gray, dst, CV_16S);
	convertScaleAbs(dst, dst);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_canny(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Canny
	Mat dst;
	double threshold = 40;
	blur(src_gray, src_gray, Size(3, 3));
	Canny(src_gray, dst, threshold, threshold * 3);

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_hough(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Hough line
	/*Mat dst;
	GaussianBlur(src_gray, dst, Size(3, 3), 0);
	vector<Vec4f> plines;
	HoughLinesP(dst, plines, 1, CV_PI / 180.0, 10, 0, 0);
	for (int i = 0; i < plines.size(); i++) {
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}*/
	// Hough circle
	Mat dst;
	medianBlur(src_gray, dst, 3);
	vector<Vec3f> pcircles;
	HoughCircles(dst, pcircles, CV_HOUGH_GRADIENT, 1, 10);
	for (int i = 0; i < pcircles.size(); i++) {
		Vec3f cc = pcircles[i];
		circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255), 3, LINE_AA);
		circle(dst, Point(cc[0], cc[1]), 2, Scalar(198, 23, 155), 3, LINE_AA);
	}

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_contours(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//
	Mat temp;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	Canny(src_gray, temp, 100, 100 * 2);
	findContours(temp, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat dst = Mat::zeros(src.size(), src.type());
	RNG rng(12345);
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 2, 8, hierachy);
	}

	// Show
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_convexhull(string &img_path)
{
	// Load
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	// Convex hull
	Mat bin_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	threshold(src_gray, bin_output, 50, 200, THRESH_BINARY);
	findContours(bin_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> convexs(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		convexHull(contours[i], convexs[i], false, true);
	}

	// Show
	Mat dst = Mat::zeros(src.size(), CV_8UC3);
	vector<Vec4i> empty(0);
	RNG rng;
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 2, LINE_AA, hierachy, 0);
		drawContours(dst, convexs, i, color, 2, LINE_AA, empty, 0);
	}
	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_distance()
{
	int r = 100;
	Mat src = Mat::zeros(r * 4, r * 4, CV_8UC1);
	vector<Point2f> vert(6);
	vert[0] = Point(3 * r / 2, 1.34 * r);
	vert[1] = Point(1 * r, 2 * r);
	vert[2] = Point(3 * r / 2, 2.866 * r);
	vert[3] = Point(5 * r / 2, 2.866 * r);
	vert[4] = Point(3 * r, 2 * r);
	vert[5] = Point(5 * r / 2, 1.34 * r);
	for (int i = 0; i < 6; i++) {
		line(src, vert[i], vert[(i + 1) % 6], Scalar(255));
	}

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	Mat csrc;
	src.copyTo(csrc);
	findContours(csrc, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat raw_dist = Mat::zeros(csrc.size(), CV_32FC1);
	for (int row = 0; row < raw_dist.rows; row++) {
		for (int col = 0; col < raw_dist.cols; col++) {
			double dist = pointPolygonTest(contours[0], Point(col, row), true);
			raw_dist.at<float>(row, col) = dist;
		}
	}
	double min, max;
	minMaxLoc(raw_dist, &min, &max);
	Mat dst = Mat::zeros(src.size(),CV_8UC3);
	for (int row = 0; row < dst.rows; row++) {
		for (int col = 0; col < dst.cols; col++) {
			float dist = raw_dist.at<float>(row, col);
			if (dist > 0) {
				dst.at<Vec3b>(row, col)[0] = (uchar)(abs(1.0 - dist / max) * 255);
			}
			else if (dist < 0) {
				dst.at<Vec3b>(row, col)[2] = (uchar)(abs(1.0 - dist / min) * 255);
			}
			else {
				dst.at<Vec3b>(row, col)[0] = (uchar)(abs(255 - dist));
				dst.at<Vec3b>(row, col)[1] = (uchar)(abs(255 - dist));
				dst.at<Vec3b>(row, col)[2] = (uchar)(abs(255 - dist));
			}
		}
	}

	namedWindow("BASIC", CV_WINDOW_AUTOSIZE);
	imshow("BASIC", dst);
	waitKey(0);
}

void CBasic::test_segmentation(string &img_path)
{

}
