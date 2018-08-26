#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
using namespace std;
using namespace cv;


class CBasic
{
public:
	CBasic();
	virtual ~CBasic();

	void test_load(string &img_path);
	void test_conv(string &img_path);
	void test_mat(string &img_path);
	void test_operator(string &img_path);
	void test_mixture(string &img_path1, string img_path2);
	void test_light_contrast(string &img_path);
	void test_draw(string &img_path);
	void test_smooth(string &img_path);
	void test_morphology(string &img_path);
	void test_morphology_line(string &img_path);
	void test_pyramid(string &img_path);
	void test_threshold(string &img_path);
	void test_filter(string &img_path);
	void test_border(string &img_path);
	void test_edage(string &img_path);
	void test_canny(string &img_path);
	void test_hough(string &img_path);
	// histom...
	void test_contours(string &img_path);
	void test_convexhull(string &img_path);
	// contours rect/circle...
	void test_distance();
	void test_segmentation(string &img_path);
};
