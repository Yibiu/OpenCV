#include "Hough.h"


CHough::CHough()
{
}

CHough::~CHough()
{
}

void CHough::hough_lines(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	Mat dst;
	GaussianBlur(src_gray, dst, Size(3, 3), 0);
	vector<Vec4f> plines;
	HoughLinesP(dst, plines, 1, CV_PI / 180.0, 80, 50, 10);
	for (int i = 0; i < plines.size(); i++) {
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), Scalar(0, 0, 255), 1, LINE_AA);
	}

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}

void CHough::hough_circles(const string &img_path)
{
	Mat src = imread(img_path);
	if (src.empty())
		return;
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	Mat dst;
	medianBlur(src_gray, dst, 3);
	vector<Vec3f> pcircles;
	HoughCircles(dst, pcircles, CV_HOUGH_GRADIENT, 1, 10);
	for (int i = 0; i < pcircles.size(); i++) {
		Vec3f cc = pcircles[i];
		circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255), 3, LINE_AA);
		circle(dst, Point(cc[0], cc[1]), 2, Scalar(198, 23, 155), 3, LINE_AA);
	}

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}
