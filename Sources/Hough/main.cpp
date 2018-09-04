#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Hough.h"


int main()
{
	CHough hough;

	//hough.hough_lines("../../Resources/beauty.jpg");
	hough.hough_circles("../../Resources/beauty.jpg");

	return 0;
}
