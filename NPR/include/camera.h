#ifndef __CAMERA__
#define __CAMERA__

#include "point.h"

typedef struct{
	Point position;
	Vector direction;
	int fieldOfView;
}Camera;

#endif

