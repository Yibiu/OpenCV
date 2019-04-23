#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;


class CEdges
{
public:
	CEdges();
	virtual ~CEdges();

	void sobel(const string &img_path);
	void scharr(const string &img_path);
	void laplacian(const string &img_path);

	void canny(const string &img_path);
};