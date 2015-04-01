#ifndef __SPHERE__
#define __SPHERE__

#include "point.h"
#include "color.h"


typedef struct{
	Point position;
	Color color;
	float specular;
	float lambert;
	float ambient;
	float radius;
}Sphere;

void setSphere(Point position, Color, color, float radius, float specilar, float lambert, float ambient);

#endif