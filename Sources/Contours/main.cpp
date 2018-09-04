#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Contours.h"


int main()
{
	CContours contours;

	//contours.find_countours("../../Resources/beauty.jpg");
	contours.find_convexhull("../../Resources/beauty.jpg");

	return 0;
}
