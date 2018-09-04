#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "edges.h"


int main()
{
	CEdges edges;

	//edges.sobel("../../Resources/beauty.jpg");
	//edges.scharr("../../Resources/beauty.jpg");
	//edges.laplacian("../../Resources/beauty.jpg");

	edges.canny("../../Resources/beauty.jpg");

	return 0;
}
