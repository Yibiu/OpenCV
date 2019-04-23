#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;


class CImageFilter
{
public:
	CImageFilter();
	virtual ~CImageFilter();

	// Convolution
	void border(const string &img_path);
	void filter(const string &img_path);
	void conv(const string &img_path);

	// Linear filter
	void box_filter(const string &img_path);
	void blur_filter(const string &img_path);
	void gaussia_filter(const string &img_path);

	// No-Linear filter
	void media_filter(const string &img_path);
	void bilateral_filter(const string &img_path);
};

