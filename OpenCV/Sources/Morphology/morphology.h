#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;


class CMorphology
{
public:
	CMorphology();
	virtual ~CMorphology();

	void erode(const string &img_path);
	void dilate(const string &img_path);
	void open(const string &img_path);
	void close(const string &img_path);
	void gradient(const string &img_path);
	void tophat(const string &img_path);
	void blackhat(const string &img_path);

	void morphology_lines(const string &img_path);
};