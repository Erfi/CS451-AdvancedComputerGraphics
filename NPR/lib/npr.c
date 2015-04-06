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

void toGreyscale(Image* src){
	int i, j;
	double avg;
	for(i=0; i<src->rows; i++){
		for(j=0; j<src->cols; j++){
			avg = (src->data[i][j].rgb[0] + src->data[i][j].rgb[1] + src->data[i][j].rgb[2])/3;
			src->data[i][j].rgb[0] = avg;
			src->data[i][j].rgb[1] = avg;
			src->data[i][j].rgb[2] = avg;
		}
	}
}

void gaussFilter(Image* src, Kernel* k){
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
	printf("Gauss's Kernel: ");
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

//creates a bigger image from the "src" image by 2xp border and fills the border with 
//near by pixels
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
	return NULL;

}

//creates an image by removing a 2px border from the input image
Image* borderRemoval(Image* src){
	int i,j;
	Image *removed = image_create(src->rows-4,src->cols-4);
	for (i = 2; i < src->rows-2; i++){
		for (j = 2; j < src->cols-2; j++){
			removed->data[i-2][j-2] = src->data[i][j];
		}
	}
	return removed;
}

//initializes the values of Gx and Gy in the SobelOperator
void sobel_create(SobelOperator* sop){
	sop->Gx[0][0] = -1;
	sop->Gx[0][1] = 0;
	sop->Gx[0][2] = 1;
	sop->Gx[1][0] = -2;
	sop->Gx[1][1] = 0;
	sop->Gx[1][2] = 2;
	sop->Gx[2][0] = -1;
	sop->Gx[2][1] = 0;
	sop->Gx[2][2] = 1;

	sop->Gy[0][0] = -1;
	sop->Gy[0][1] = -2;
	sop->Gy[0][2] = -1;
	sop->Gy[1][0] = 0;
	sop->Gy[1][1] = 0;
	sop->Gy[1][2] = 0;
	sop->Gy[2][0] = 1;
	sop->Gy[2][1] = 2;
	sop->Gy[2][2] = 1;
}

void sobel_print(SobelOperator* sop){
	int i, j;
	printf("\nSobel Operator: Gx\n");
	for(i=0; i<3; i++){
		for(j=0; j<3 ; j++){
			printf(" %d ",sop->Gx[i][j]);
		}
		printf("\n");
	}

	printf("\nSobel Operator: Gy\n");
	for(i=0; i<3; i++){
		for(j=0; j<3 ; j++){
			printf(" %d ",sop->Gy[i][j]);
		}
		printf("\n");
	}
}

//applies the sobel operator to each (inner >> not the borders!) pixel of the "border" image
//and puts the result in "sobelMask"
void sobelFilter(Image* border, Image* sobelMask, SobelOperator* sop){
	int i, j, k, l;
	double sumx[3];
	double sumy[3];
	for (i=0; i<sobelMask->rows; i++){
		for(j=0; j<sobelMask->cols; j++){
			sumx[0] =0;
			sumx[1] =0;
			sumx[2] =0;

			sumy[0] =0;
			sumy[1] =0;
			sumy[2] =0;
			for(k=-1; k<=1; k++){
				for(l=-1; l<=1; l++){
					sumx[0] += border->data[i+2+k][j+2+l].rgb[0] * sop->Gx[k+1][l+1];
					sumx[1] += border->data[i+2+k][j+2+l].rgb[1] * sop->Gx[k+1][l+1];
					sumx[2] += border->data[i+2+k][j+2+l].rgb[2] * sop->Gx[k+1][l+1];

					sumy[0] += border->data[i+2+k][j+2+l].rgb[0] * sop->Gy[k+1][l+1];
					sumy[1] += border->data[i+2+k][j+2+l].rgb[1] * sop->Gy[k+1][l+1];
					sumy[2] += border->data[i+2+k][j+2+l].rgb[2] * sop->Gy[k+1][l+1];
				}
			} 
			sobelMask->data[i][j].rgb[0] = sqrt(sumx[0]*sumx[0] + sumy[0]*sumy[0]);
			sobelMask->data[i][j].rgb[1] = sqrt(sumx[1]*sumx[1] + sumy[1]*sumy[1]); 
			sobelMask->data[i][j].rgb[2] = sqrt(sumx[2]*sumx[2] + sumy[2]*sumy[2]);
		}

	}

}






