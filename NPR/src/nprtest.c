/*
Ryan Brandt & Erfan Azad
Date: 31 March 2015
File: nprtest.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "image.h"
#include "npr.h"

int main(int args, char* argv[]){
	Image* src;
	Image* border;//to hold the blured image with extended borders
	Image* sobelMask;//to record the result after sobel operator applied
	Kernel k;//to hold the gaussian filter convolution matrix
	SobelOperator sop;//holds the sobel operators for horizontal and vertical axis (Gx & Gy)

	src = image_read("../images/fishman.ppm");
	sobelMask = image_create(src->rows, src->cols);
	border = borderCreate(src);
	
	
	kernel_create(&k,10);
	kernel_print(&k);
	gaussFilter(border, &k);

	toGreyscale(border);

	sobel_create(&sop);
	sobel_print(&sop);
	sobelFilter(border, sobelMask, &sop);
	nonMaxSuppression(sobelMask);
	doubleThreshold(sobelMask, 0.8, 0.3);



	// border = borderRemoval(border);

	image_write(sobelMask,"../images/fishmanSuppressed.ppm");
	// image_write(border,"../images/border.ppm");
	

	//free images
	image_free(src);
	image_free(border);
	image_free(sobelMask);	
}