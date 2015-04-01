#ifndef __RAY__
#define __RAY__

#include "point.h"
#include "color.h"


typedef struct{
	Point position;
	Vector direction;
}Ray;

void ray_normalize(Ray r);

#endif