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
}

void kernel_create(Kernel *k,float sigma){
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