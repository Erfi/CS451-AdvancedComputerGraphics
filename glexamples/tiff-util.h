/*
	Defines a few useful tiff routines
 */

#ifndef TIFF_UTIL_H
#define TIFF_UTIL_H

#include <stdio.h>
#include <sys/types.h>
#include <tiffio.h>

// change the following to 0 if you are not on an intel box
#define INTEL 1 

uint32 *tiff_read(char filename[], uint32 *nrow, uint32 *ncol);
int tiff_write(char filename[], uint32 *raster, uint32 nrow, uint32 ncol);

#endif
