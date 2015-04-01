/*
Ryan Brandt & Erfan Azad
Date: 31 March 2015
File: nprtest.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "npr.h"

int main(int args, char* argv[]){
	Image* src;
	Kernel k;

	src = image_read("../images/fishman.ppm");
	Image* border = borderCreate(src);
	kernel_create(&k,10);
	kernel_print(&k);

	gaussFilter(border, &k);

	border = borderRemoval(border);

	// image_write(src, "../images/fishman2.ppm");
	image_write(border,"../images/test.ppm");
	
}