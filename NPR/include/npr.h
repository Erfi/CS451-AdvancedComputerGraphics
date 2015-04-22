/*
Ryan Brandt & Erfan Azad
Date: 31 March 2015
File: npr.h
*/


#ifndef __NPR_H__
#define __NPR_H__

typedef struct{
	double mat[5][5];
}Kernel;

typedef struct{
	int Gx[3][3];
	int Gy[3][3];
}SobelOperator;

void gaussFilter(Image* src, Kernel* k);
Image* borderCreate(Image* src);
Image* borderRemoval(Image* src);
void kernel_create(Kernel * k,float sigma);
void kernel_print(Kernel* kernel);
void sobel_create(SobelOperator* sop);
void sobelFilter(Image* border, Image* sobelMask, SobelOperator* sop);
void sobel_print(SobelOperator* sop);
void toGreyscale(Image* src);
void nonMaxSuppression(Image* src, Image* buffer);
void doubleThreshold(Image* src, double high, double low);
void hysteresis(Image* src);
Image* cropBorder(Image* src, int n);
Image* cannyEdgeDetect(Image* src, float sigma, double T_high, double T_low);
Image* alphaBlend(Image* src, Image* edgeMask, float alpha);


#endif