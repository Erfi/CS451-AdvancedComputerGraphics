/*
Ryan Brandt & Erfan Azad
Date: 31 March 2015
File: npr.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Image.h"
#include "npr.h"

void gaussFilter(Image* src, Kernel* k){
	printf("gaussFilter!\n");
	int i, j, x, y;
	double sum[3];
	for(i=2; i<src->rows-2; i++){
		for (j=2; j<src->cols-2; j++){ //for each inside pixel
			sum[0] =0;
			sum[1] =0;
			sum[2] =0;
			for(x=-2; x<=2; x++){
				for(y=-2; y<=2; y++){
					sum[0] += src->data[i+x][j+y].rgb[0] * k->mat[x+2][y+2];
					sum[1] += src->data[i+x][j+y].rgb[1] * k->mat[x+2][y+2];
					sum[2] += src->data[i+x][j+y].rgb[2] * k->mat[x+2][y+2];
				}
			}
			src->data[i][j].rgb[0] = sum[0];
			src->data[i][j].rgb[1] = sum[1];
			src->data[i][j].rgb[2] = sum[2];
		}
	}

}

void kernel_create(Kernel *k, float sigma){
	if(sigma > 0){
		double s = 2 * sigma *sigma;
		double sum = 0;
		double r;

		int x,y;
		for(x=-2; x<= 2; x++){
			for(y=-2; y<=2; y++){
				r = x*x + y*y;
				k->mat[x+2][y+2] = (exp(-(r/s))/(M_PI*s));
				sum += k->mat[x+2][y+2];
			}
		}

		//Normalize
		for(x=0; x<5; x++){
			for(y=0; y<5; y++){
				k->mat[x][y] /= sum;
			}
		}
	}
}

void kernel_print(Kernel* kernel){
	int x, y;
	printf("\n");
	for(x=0; x<5; x++){
		for(y=0; y<5; y++){
			printf(" %f ", kernel->mat[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

Image* borderCreate(Image* src){
	if(src != NULL){
		Image* border = image_create(src->rows+4,src->cols+4);
		int i,j;
		// apply blank border around src image
		for (i = 2; i < border->rows-2; i++){
			for (j = 2; j < border->cols-2; j++){
				border->data[i][j] = src->data[i-2][j-2];
			}
		}

		// filling the border with values
		// Upper Left Corner
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				border->data[i][j] = src->data[0][0];
			}
		}

		// upper Right corner
		for (i = 0; i < 3; i++)
		{
			for (j = border->cols-3; j < border->cols; j++)
			{
				border->data[i][j] = src->data[0][src->cols-1];
			}
		}

				// lower left corner
		for (i = src->rows+1; i < src->rows+4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				border->data[i][j] = src->data[src->rows-1][0];
			}
		}

		// lower right
		for (i = src->rows+1; i < src->rows+4; i++)
		{
			for (j = src->cols+1;  j< src->cols+4; j++)
			{
				border->data[i][j] = src->data[src->rows-1][src->cols-1];
			}
		}

		// upside
		for (i = 3; i < src->cols+1; i++)
		{
			border->data[1][i] = src->data[0][i-2];
			border->data[0][i] = src->data[0][i-2];
		}

		// downside
		for (i = 3; i < src->cols+1; i++)
		{
			border->data[src->rows+2][i] = src->data[src->rows-1][i-2];
			border->data[src->rows+3][i] = src->data[src->rows-1][i-2];
		}

		// left
		for (i = 3; i < src->rows+1; i++)
		{
			border->data[i][0] = src->data[i-2][0];
			border->data[i][1] = src->data[i-2][0];
		}
		// right
		for (i = 3; i < src->rows+1; i++)
		{
			border->data[i][src->cols+2] = src->data[i-2][src->cols-1];
			border->data[i][src->cols+3] = src->data[i-2][src->cols-1];
		}


		return border;


	}

}

Image* borderRemoval(Image* src){
			int i,j;
		// apply blank border around src image
		Image *removed = image_create(src->rows-4,src->cols-4);
		for (i = 2; i < src->rows-2; i++){
			for (j = 2; j < src->cols-2; j++){
				removed->data[i-2][j-2] = src->data[i][j];
			}
		}
		return removed;
}
