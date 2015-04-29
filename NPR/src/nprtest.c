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
	Image* edgeMask;
	Image* thickMask;
	Image* final;


	if(args < 4){
		printf("Not enough argumets: <file> <sigma> <T1> <T2>\n");
		exit(-1);
	}else{
		src = image_read("../images/beerFall.ppm");
		image_write(src, "../images/CLAS/CLASSS/Original.ppm");
		
		edgeMask = cannyEdgeDetect(src, atof(argv[1]), atof(argv[2]), atof(argv[3]));

		//thinkening the edges
		thickMask = image_create(edgeMask->rows, edgeMask->cols);
		thickenLines(edgeMask, thickMask,2);
		image_write(thickMask, "../images/CLAS/CLASSS/Step7_thickening.ppm");

		//anti_Alias
		Image* Alias = borderCreate(thickMask);
		Kernel k;
		kernel_create(&k, 5);
		gaussFilter(Alias, &k);
		Image* anti_aliased = cropBorder(Alias, 2);
		image_write(anti_aliased, "../images/CLAS/CLASSS/Step8_antiAlias.ppm");

		//blend
		final = alphaBlend(src, anti_aliased);
		image_write(final, "../images/CLAS/CLASSS/Step9_Blending.ppm");


		image_free(src);
		image_free(edgeMask);
		image_free(final);
		image_free(thickMask);
		image_free(Alias);
		image_free(anti_aliased);
	}



//============================All made into one function: cannyEdgeDetect()============================
	// Image* src;
	// Image* border;//to hold the blured image with extended borders
	// Image* sobelMask;//to record the result after sobel operator applied
	// Image* nonMaxSuppressionBuffer; //to hold the image after the non maximal suppression is applied
	// Image* edgeImage; // holds the edge detected picture
	// Kernel k;//to hold the gaussian filter convolution matrix
	// SobelOperator sop;//holds the sobel operators for horizontal and vertical axis (Gx & Gy)

	// src = image_read("../images/fishman.ppm");
	// sobelMask = image_create(src->rows, src->cols);
	// border = borderCreate(src);
	// nonMaxSuppressionBuffer = image_create(sobelMask->rows, sobelMask->cols);
	
	// //bluer
	// kernel_create(&k,100);
	// kernel_print(&k);
	// gaussFilter(border, &k);

	// //greyscale
	// toGreyscale(border);

	// //gradient
	// sobel_create(&sop);
	// sobel_print(&sop);
	// sobelFilter(border, sobelMask, &sop);

	// //non maximal suppression
	// nonMaxSuppression(sobelMask, nonMaxSuppressionBuffer);

	// //double threshold
	// doubleThreshold(nonMaxSuppressionBuffer, 0.45, 0.1);

	// //hysterisis 
	// hysteresis(nonMaxSuppressionBuffer);

	// edgeImage = cropBorder(nonMaxSuppressionBuffer, 1);


	// //writing the image to disk
	// image_write(edgeImage,"../images/fishmanFinalFinal.ppm");
	

	// //free images
	// image_free(src);
	// image_free(border);
	// image_free(sobelMask);	
	// image_free(nonMaxSuppressionBuffer);
	// image_free(edgeImage);
}