#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "morphology.h"


int main()
{
	CMorphology morphology;

	//morphology.erode("../../Resources/beauty.jpg");
	//morphology.dilate("../../Resources/beauty.jpg");
	//morphology.open("../../Resources/beauty.jpg");
	//morphology.close("../../Resources/beauty.jpg");
	//morphology.gradient("../../Resources/beauty.jpg");
	//morphology.tophat("../../Resources/beauty.jpg");
	//morphology.blackhat("../../Resources/beauty.jpg");

	morphology.morphology_lines("../../Resources/beauty.jpg");

	return 0;
}
