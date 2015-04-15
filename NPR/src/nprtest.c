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
	Image* nonMaxSuppressionBuffer; //to hold the image after the non maximal suppression is applied
	Kernel k;//to hold the gaussian filter convolution matrix
	SobelOperator sop;//holds the sobel operators for horizontal and vertical axis (Gx & Gy)

	src = image_read("../images/fishman.ppm");
	sobelMask = image_create(src->rows, src->cols);
	border = borderCreate(src);
	nonMaxSuppressionBuffer = image_create(sobelMask->rows, sobelMask->cols);
	
	//bluer
	kernel_create(&k,100);
	kernel_print(&k);
	gaussFilter(border, &k);

	//greyscale
	toGreyscale(border);

	//gradient
	sobel_create(&sop);
	sobel_print(&sop);
	sobelFilter(border, sobelMask, &sop);

	//non maximal suppression
	nonMaxSuppression(sobelMask, nonMaxSuppressionBuffer);

	//double threshold
	doubleThreshold(nonMaxSuppressionBuffer, 0.45, 0.1);

	//hysterisis 
	hysteresis(nonMaxSuppressionBuffer);

	//writing the image to disk
	image_write(nonMaxSuppressionBuffer,"../images/fishmanFinal.ppm");
	

	//free images
	image_free(src);
	image_free(border);
	image_free(sobelMask);	
	image_free(nonMaxSuppressionBuffer);
}