#include "image_filter.h"


CImageFilter::CImageFilter()
{
}

CImageFilter::~CImageFilter()
{
}

void CImageFilter::border(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);

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
		imshow("OUTPUT", dst);
	}
}

void CImageFilter::filter(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(src, dst, -1, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CImageFilter::conv(const string &img_path)
{
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

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CImageFilter::box_filter(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	boxFilter(src, dst, -1, Size(3, 3));

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CImageFilter::blur_filter(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	blur(src, dst, Size(3, 3));

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CImageFilter::gaussia_filter(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	GaussianBlur(src, dst, Size(3, 3), 11);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CImageFilter::media_filter(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	medianBlur(src, dst, 3);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CImageFilter::bilateral_filter(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	bilateralFilter(src, dst, 15, 100, 3);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}