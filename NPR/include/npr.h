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

void gaussFilter(Image* src, Kernel* k);
void kernel_create(Kernel * k,float sigma);
void kernel_print(Kernel* kernel);

#endif