#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;


class CDistance
{
public:
	CDistance();
	virtual ~CDistance();

	void test_distance(const string &img_path);
};