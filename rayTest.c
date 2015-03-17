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


void render(Image* src, Camera* camera, Light* light, Sphere* objectArray,int lengthOfArray, int depth);
Color trace(Ray* ray, Camera* camera, Light* lght, Sphere* objectArray, int lengthOfArray, int depth);
Closest intersectScene(Ray* ray, Sphere* objectArray, int lengthOfArray);
double sphereIntersection(Ray* ray, Sphere* sphere);
Vector sphereNormal(Sphere* sphere, Vector position);
Color surface(Ray* ray, Camera* camera, Light* light, Sphere* obj,Sphere* objectArray, int lengthOfArray,Vector* pointAtTime, Vector normal, int depth);
double isLightVisible(Point* pt, Ray* ray, Sphere* objectArray,int lengthOfArray, Light* light);
Vector reflect(Vector a, Vector normal);
Vector Color_to_vector(Color *a);
Color Vector_to_color(Vector* a);

int main(int argc, char* argv[]){
	printf("Congrats your makefile works!\n");
	Image* src;
	Camera camera;
	Sphere sphere;
	Sphere sphere2;
	Sphere objectArray[2];
	Light light;
	int depth = 1;
	int lengthOfArray = 2;
	

	//setting the camera
	point_set3D(&camera.position, 3, 0, 20);
	vector_set(&camera.direction, -3, 0, -20.0);
	camera.fieldOfView = 60.0;

	//setting the light
	point_set3D(&light.position, 0, 5.0, 15);

	//setting the sphere
	point_set3D(&sphere.position, 3, 0, 5.0);
	Color_set(&sphere.color, 1, 0, 0);
	sphere.specular = 0.1;
	sphere.lambert = 0.7;
	sphere.ambient = 0.1;
	sphere.radius = 3;

	//setting the sphere2
	point_set3D(&sphere2.position, 2, 3, 10.0);
	Color_set(&sphere2.color, 0, 0, 1);
	sphere2.specular = 0.1;
	sphere2.lambert = 0.7;
	sphere2.ambient = 0.1;
	sphere2.radius = 1;

	//setting the object array
	objectArray[0] = sphere;
	objectArray[1] = sphere2;


	//setting the image
	src = image_create(700, 700);

	render(src, &camera, &light, objectArray, lengthOfArray,depth);
	image_write(src, "../images/raytracing.ppm");
	image_free(src);
	
}

void render(Image* src, Camera* camera, Light* light, Sphere* objectArray, int lengthOfArray, int depth){
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

	// test condition
	vector_set(&ray.direction,1,2,4);

	
	int x, y;
	for(x=0; x < src->cols; x++){
		for(y=0; y < src->rows; y++){
			Vector xComp = vector_scale(&vpRight, (x * pixelWidth) - halfWidth);
			Vector yComp = vector_scale(&vpUp, (y * pixelHeight) - halfHeight);
			Vector sum = vector_add(&xComp, &yComp);
			ray.direction = vector_add(&sum, &eyevector);

			//trace 
			clr = trace(&ray, camera, light, objectArray,lengthOfArray, depth);
			src->data[x][y].rgb[0] = clr.rgb[0];
			src->data[x][y].rgb[1] = clr.rgb[1];
			src->data[x][y].rgb[2] = clr.rgb[2];
		}

	}

}

Color trace(Ray* ray, Camera* camera, Light* light, Sphere* objectArray, int lengthOfArray,int depth){
	Color color;
	if(depth > 10){
		Color_set(&color, -1, -1, -1);
		return color;
	}

	Closest closeestObject = intersectScene(ray, objectArray,lengthOfArray);
	if(closeestObject.distance == INFINITY){
		// printf("happening \n");
		Color_set(&color, 1,1,1);
		return color;	
	}
	double dist = closeestObject.distance;

	Sphere obj = closeestObject.sphere;
	Vector a = vector_scale(&ray->direction, dist);


	Vector pointAtTime = (vector_add( &a,&ray->position));

	// 	printf("intersection point \n");
	// point_print(&pointAtTime,stdout);

	return surface(ray, camera, light, &obj,objectArray,lengthOfArray, &pointAtTime, sphereNormal(&obj,pointAtTime), depth);


}

Closest intersectScene(Ray* ray, Sphere* objectArray, int lengthOfArray){

	Closest close;
	close.distance = INFINITY;


	int i;
	for (i = 0; i < lengthOfArray; i++)
	{
		Sphere obj = objectArray[i];
		double dist = sphereIntersection(ray,&obj);
		if(dist != -1 && (dist < close.distance)){
			close.distance = dist;
			close.sphere = obj;
		}
	}
	return close;


}

double sphereIntersection(Ray* ray, Sphere* sphere){
	Vector centered = vector_subtract(&sphere->position, &ray->position);

	// printf("centered! \n");
	// point_print(&centered,stdout);

	vector_normalize(&ray->direction);

	double v = vector_dot(&centered, &ray->direction);
		// printf("v! %f \n",v);

	double squareCenter = vector_dot(&centered, &centered);
	
	// printf("squareCenter! %f \n",squareCenter);

	double halfchordSq = (sphere->radius*sphere->radius) - (squareCenter) + (v*v);

	// printf("halfchordSq! %f \n",halfchordSq);

	if(halfchordSq<0){
		return -1;
	}
	return v- sqrt(halfchordSq);

}

Vector sphereNormal(Sphere* sphere, Vector position){
    Vector norm = vector_subtract(&position,&sphere->position);
	vector_normalize(&norm);
	// printf("norm\n");
	// point_print(&norm,stdout);
	return norm;

}

Color surface(Ray* ray, Camera* camera, Light* light, Sphere* obj,Sphere* objectArray, int lengthOfArray,Vector* pointAtTime, Vector normal, int depth){
	//lambert calculations
	float lambertAmount = 0;
	Vector zero;
	vector_set(&zero, 0, 0, 0);
	Sphere *sphere = obj;
	
	if(sphere->lambert > 0){
		int i;
		int numLights = 1;
		for(i=0; i<numLights; i++){
			Light l = light[i];
			if(isLightVisible(pointAtTime, ray, sphere,lengthOfArray, &l) == 0){
				continue;
			}
			Vector subtract = vector_subtract(&l.position, pointAtTime);
			vector_normalize(&subtract);
			double contribution = vector_dot(&subtract, &normal);

			if(contribution > 0){
				lambertAmount += contribution;
			}
		}
	}

	if(sphere->specular > 0){
		Ray reflected;
		reflected.position = (Point)*pointAtTime;
		reflected.direction = reflect(ray->direction, normal);

		Color color = trace(&reflected, camera, light, objectArray,lengthOfArray, ++depth);
		if(color.rgb[0] > 0){

			Vector vector_color = Color_to_vector(&color);
			Vector scaled = vector_scale(&vector_color, sphere->specular);

			zero = vector_add(&zero, &scaled);
		}
	}

	lambertAmount = fminf(1, lambertAmount);
	Vector vtemp = Color_to_vector(&sphere->color);

	Vector scale1 = vector_scale(&vtemp, lambertAmount* sphere->lambert);
	Vector scale2 = vector_scale(&vtemp, sphere->ambient);

	Vector temp = vector_add(&zero, &scale1);
	Vector result = vector_add(&temp, &scale2);

	return Vector_to_color(&result);

}

double isLightVisible(Point* pt, Ray* ray, Sphere* objectArray,int lengthOfArray, Light* light){
	Ray tempRay;
	tempRay.position = *pt;
	tempRay.direction = vector_subtract((Vector*)pt, &light->position);
	vector_normalize(&tempRay.direction);

	Closest closeObj = intersectScene(&tempRay, objectArray,lengthOfArray);

	if(closeObj.distance > -0.005){
		return 1;
	}
	else{
		return 0;
	}
}


Vector reflect(Vector a, Vector normal){
	Vector d = vector_scale(&normal, vector_dot(&a, &normal));
	Vector temp = vector_scale(&d, 2);
	return vector_subtract(&temp, &a);
}

Vector Color_to_vector(Color *a){
    Vector result;
    if(a != NULL){
        vector_set(&result, a->rgb[0], a->rgb[1], a->rgb[2]);
        return result;
    }else{
        printf("ERROR: Color_to_vector >> pointer is NULL");
        // vector_set(&result, -1, -1, -1);
        exit(-1);
    }
}

Color Vector_to_color(Vector* a){
	Color result;
	if(a != NULL){
		Color_set(&result, a->val[0], a->val[1], a->val[2]);
		return result;
	}else{
		printf("ERROR: Vector_to_color >> pointer is NULL");
        // Color_set(&result, -1, -1, -1);
        exit(-1);
	}
}












