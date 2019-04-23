#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "misc.h"


int main()
{
	CMisc misc;

	//misc.image_io("../../Resources/beauty.jpg");
	//misc.mat_create("../../Resources/beauty.jpg");
	//misc.mat_operator("../../Resources/beauty.jpg");
	//misc.mixture("../../Resources/boat1.jpg", "../../Resources/boat2.jpg");
	//misc.light_contrast("../../Resources/beauty.jpg");
	//misc.draw("../../Resources/beauty.jpg");
	misc.pyramid("../../Resources/beauty.jpg");

	return 0;
}
