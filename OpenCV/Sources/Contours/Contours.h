#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;


class CContours
{
public:
	CContours();
	virtual ~CContours();

	void find_countours(const string &img_path);
	void find_convexhull(const string &img_path);
};
