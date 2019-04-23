#include "distance.h"


CDistance::CDistance()
{
}

CDistance::~CDistance()
{
}

void CDistance::test_distance(const string &img_path)
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
	Mat dst = Mat::zeros(src.size(), CV_8UC3);
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

	namedWindow("OUTPUT", WINDOW_AUTOSIZE);
	imshow("OUTPUT", dst);
	waitKey(0);
}
