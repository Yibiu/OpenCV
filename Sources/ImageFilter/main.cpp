#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "image_filter.h"


int main()
{
	CImageFilter filter;

	//filter.border("../../Resources/beauty.jpg");
	//filter.filter("../../Resources/beauty.jpg");
	//filter.conv("../../Resources/beauty.jpg");

	//filter.box_filter("../../Resources/beauty.jpg");
	//filter.blur_filter("../../Resources/beauty.jpg");
	//filter.gaussia_filter("../../Resources/beauty.jpg");

	//filter.media_filter("../../Resources/beauty.jpg");
	filter.bilateral_filter("../../Resources/beauty.jpg");

	return 0;
}
