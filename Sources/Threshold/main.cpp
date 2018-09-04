#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "threshold.h"


int main()
{
	CThreshold threshold;

	//threshold.threshold("../../Resources/beauty.jpg");
	threshold.adaptive_threshold("../../Resources/beauty.jpg");

	return 0;
}
