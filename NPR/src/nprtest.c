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

	// src = image_read("../images/fishman.ppm");
	// image_write(src, "../images/fishman2.ppm");

	// gaussFilter(src, 3);
	kernel_create(&k,1);
	kernel_print(&k);

	// image_free(src);
}