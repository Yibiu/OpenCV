#include "edges.h"


CEdges::CEdges()
{
}

CEdges::~CEdges()
{
}

void CEdges::sobel(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat src_gray, dst;
	GaussianBlur(src, dst, Size(3, 3), 0);
	cvtColor(dst, src_gray, CV_BGR2GRAY);
	Mat grad_x, grad_y;
	Sobel(src_gray, grad_x, CV_16S, 1, 0);
	Sobel(src_gray, grad_y, CV_16S, 0, 1);
	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CEdges::scharr(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat src_gray, dst;
	GaussianBlur(src, dst, Size(3, 3), 0);
	cvtColor(dst, src_gray, CV_BGR2GRAY);
	Mat grad_x, grad_y;
	Scharr(src_gray, grad_x, CV_16S, 1, 0);
	Scharr(src_gray, grad_y, CV_16S, 0, 1);
	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CEdges::laplacian(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;

	Mat src_gray, dst;
	GaussianBlur(src, dst, Size(3, 3), 0);
	cvtColor(dst, src_gray, CV_BGR2GRAY);
	Laplacian(src_gray, dst, CV_16S);
	convertScaleAbs(dst, dst);

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CEdges::canny(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	
	Mat src_gray, dst;
	cvtColor(src, src_gray, CV_BGR2GRAY);
	double threshold = 40;
	blur(src_gray, src_gray, Size(3, 3));
	Canny(src_gray, dst, threshold, threshold * 3);

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}