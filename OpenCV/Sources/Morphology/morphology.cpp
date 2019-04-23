#include "morphology.h"


CMorphology::CMorphology()
{
}

CMorphology::~CMorphology()
{
}

void CMorphology::erode(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	cv::erode(src, dst, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMorphology::dilate(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	cv::dilate(src, dst, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMorphology::open(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(src, dst, CV_MOP_OPEN, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMorphology::close(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(src, dst, CV_MOP_CLOSE, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMorphology::gradient(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(src, dst, CV_MOP_GRADIENT, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMorphology::tophat(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(src, dst, CV_MOP_TOPHAT, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMorphology::blackhat(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat dst;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(src, dst, CV_MOP_BLACKHAT, kernel);

	namedWindow("INPUT", WINDOW_AUTOSIZE);
	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("INPUT", src);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CMorphology::morphology_lines(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	Mat temp, dst;
	adaptiveThreshold(src_gray, temp, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1));
	//Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16));
	morphologyEx(temp, dst, MORPH_OPEN, hline);
	//morphologyEx(temp, dst, MORPH_OPEN, vline);

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}
