#include "Contours.h"


CContours::CContours()\
{

}

CContours::~CContours()
{

}

void CContours::find_countours(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

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

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CContours::find_convexhull(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	Mat bin_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	threshold(src_gray, bin_output, 50, 200, THRESH_BINARY);
	findContours(bin_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> convexs(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		convexHull(contours[i], convexs[i], false, true);
	}
	Mat dst = Mat::zeros(src.size(), CV_8UC3);
	vector<Vec4i> empty(0);
	RNG rng;
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 2, LINE_AA, hierachy, 0);
		drawContours(dst, convexs, i, color, 2, LINE_AA, empty, 0);
	}

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}