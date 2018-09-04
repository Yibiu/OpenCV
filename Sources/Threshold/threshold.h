#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;


class CThreshold
{
public:
	CThreshold();
	virtual ~CThreshold();

	void threshold(const string &img_path);
	void adaptive_threshold(const string &img_path);
};

