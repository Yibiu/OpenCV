#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;


class CHough
{
public:
	CHough();
	virtual ~CHough();

	void hough_lines(const string &img_path);
	void hough_circles(const string &img_path);
};

