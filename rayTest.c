/*
Erfan Azad & Ryan Brandt
Date: 10 March 2015
File: raytracer.c
Description: Creates a simple raytracer test File
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "image.h"
#include "point.h"
#include "ppmIO.h"


//============Ray==============
typedef struct{
	Point position;
	Vector direction;
}Ray;

//==========Sphere============
typedef struct{
	Point position;
	Color color;
	float specular;
	float lambert;
	float ambient;
	float radius;
}Sphere;
//=========Camera============
typedef struct{
	Point position;
	Vector direction;
	float fieldOfView;
}Camera;
//========Light============
typedef struct{
	Point position;
}Light;
//=======ClosestObject======
typedef struct{
	double distance;
	Sphere sphere;
}Closest;


void render(Image* src, Camera* camera, Light* light);
Color trace(Ray* ray, Camera* camera, Light* lght, Sphere* objectArray, int depth);
Closest intersectScene(Ray* ray, Sphere* objectArray);
double sphereIntersection(Ray* ray, Sphere* sphere);
Vector sphereNormal(Sphere* sphere, Vector position);
Color surface(Ray* ray, Camera* camera, Light* light, Sphere* sphere, Point* pointAtTime, Vector normal, int depth);
double isLightVisible(Point* pt, Ray* ray, Sphere* objectArray, Light* light);

int main(int argc, char* argv[]){
	printf("Congrats your makefile works!\n");
	Image* src;
	Camera camera;
	Sphere sphere;
	Sphere objectArray[1];
	Light light;
	

	//setting the camera
	point_set3D(&camera.position, 0.0, 1.8, 10);
	vector_set(&camera.direction, 0.0, 3.0, 0.0);
	camera.fieldOfView = 45.0;

	//setting the light
	point_set3D(&light.position, -30.0, -10.0, 20);

	//setting the sphere
	point_set3D(&sphere.position, 0.0, 3.5, -3.0);
	Color_set(&sphere.color, 155, 200, 155);
	sphere.specular = 0.2;
	sphere.lambert = 0.7;
	sphere.ambient = 0.1;
	sphere.radius = 3;

	//setting the object array
	objectArray[0] = sphere;

	//setting the image
	src = image_create(640, 480);

	render(src, &camera, &light);
	
}

void render(Image* src, Camera* camera, Light* light){
	Vector vup;
	vector_set(&vup, 0.0, 1.0, 0.0);

	Vector eyevector = vector_subtract(&camera->direction, &camera->position); //vpn
	vector_normalize(&eyevector);

	Vector vpRight;
	vector_cross(&eyevector,&vup,&vpRight);
	vector_normalize(&vpRight);

	Vector vpUp;
	vector_cross(&vpRight, &eyevector, &vpUp);

	double fovRadians =  M_PI * (camera->fieldOfView / 2) / 180;
	double heightWidthRatio = src->rows/ src->cols;
	double halfWidth = tan(fovRadians);
	double halfHeight = heightWidthRatio * halfWidth;
	double camerawidth = halfWidth * 2;
	double cameraheight = halfHeight * 2;
	double pixelWidth = camerawidth / (src->cols - 1);
	double pixelHeight = cameraheight / (src->rows - 1);

	Color clr;
	Ray ray;
	ray.position = camera->position;
	
	int x, y;
	for(x=0; x < src->cols; x++){
		for(y=0; y < src->rows; y++){
			Vector xComp = vector_scale(&vpRight, (x * pixelWidth) - halfWidth);
			Vector yComp = vector_scale(&vpUp, (y * pixelHeight) - halfHeight);
			Vector sum = vector_add(&xComp, &yComp);
			ray.direction = vector_add(&sum, &eyevector);

			//trace 
			//set the color of clr

			src->data[x][y].rgb[0] = clr.rgb[0];
			src->data[x][y].rgb[1] = clr.rgb[1];
			src->data[x][y].rgb[2] = clr.rgb[2];
		}

	}

}

Color trace(Ray* ray, Camera* camera, Light* lght, Sphere* objectArray, int depth){
	Color color;
	if(depth > 3){
		return color;
	}

}

Closest intersectScene(Ray* ray, Sphere* objectArray){

}

double sphereIntersection(Ray* ray, Sphere* sphere){

}

Vector sphereNormal(Sphere* sphere, Vector position){

}

Color surface(Ray* ray, Camera* camera, Light* light, Sphere* sphere, Point* pointAtTime, Vector normal, int depth){

}

double isLightVisible(Point* pt, Ray* ray, Sphere* objectArray, Light* light){

}









