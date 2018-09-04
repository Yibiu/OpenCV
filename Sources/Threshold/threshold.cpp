#include "threshold.h"


CThreshold::CThreshold()
{
}

CThreshold::~CThreshold()
{
}

void CThreshold::threshold(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	Mat dst;
	cv::threshold(src_gray, dst, 150, 255, THRESH_BINARY);
	//cv::threshold(src_gray, dst, 150, 255, THRESH_BINARY_INV);
	//cv::threshold(src_gray, dst, 150, 255, THRESH_TRUNC);
	//cv::threshold(src_gray, dst, 150, 255, THRESH_TOZERO);
	//cv::threshold(src_gray, dst, 150, 255, THRESH_TOZERO_INV);
	//cv::threshold(src_gray, dst, 150, 255, THRESH_OTSU);
	//cv::threshold(src_gray, dst, 150, 255, THRESH_TRIANGLE);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", dst);
	waitKey(0);
}

void CThreshold::adaptive_threshold(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	Mat dst;
	int max_val = 255;
	int block_size = 41;
	double C = 0.0;
	adaptiveThreshold(src_gray, dst, max_val, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, block_size, C);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", dst);
	waitKey(0);
}
