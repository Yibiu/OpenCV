#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;


class CMisc
{
public:
	CMisc();
	virtual ~CMisc();

	void image_io(const string &img_path);
	void mat_create(const string &img_path);
	void mat_operator(const string &img_path);
	void mixture(const string img_path1, const string img_path2);
	void light_contrast(const string &img_path);
	void draw(const string &img_path);
	void pyramid(const string &img_path);
};