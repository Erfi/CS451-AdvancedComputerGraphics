/*
Erfan Azad
Date: Dec 13 2014
File: final.C
Description: This file will create an animation of letters "GRAPHICS" on a ground and circles arouns them.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "point.h"
#include "matrix.h"
#include "polygon.h"
#include "Image.h"
#include "module.h"
#include "drawState.h"
#include "view.h"
#include "light.h"



//creating unit letters
void module_alphabet_G(Module *md);
void module_alphabet_G(Module *md){
	//3
	module_cube(md); 
	module_translate(md, 2, 0 ,0);

	module_cube(md); 
	module_translate(md, 2, 0 ,0);

	module_cube(md); 
	module_translate(md, 2, 0 ,0);

	//4
	module_cube(md);
	module_translate(md, 0, 0 ,-2);
	module_cube(md); 

	module_translate(md, 0, 0 ,-2);
	module_cube(md);

	module_translate(md, 0, 0 ,-2);
	module_cube(md);

	//5
	module_translate(md, -2, 0, 0);
	module_cube(md);

	//2
	module_identity(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0,0,-2);
		module_cube(md);
	}

	//1
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0 ,0);
		module_cube(md);
	}	
}

void module_alphabet_R(Module *md);
void module_alphabet_R(Module *md){

	//4
	for(int i=0; i<6; i++){
		module_cube(md);
		module_translate(md, 0,0,-2);
	}

	//1
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//2
	for(int i=0; i<2; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}

	//3
	module_translate(md, 0, 0, 2);
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}

	//5
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 2);
		module_cube(md);
	}
}


void module_alphabet_A(Module *md);
void module_alphabet_A(Module *md){
	//1
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}	

	//2
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//3
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}	

	//4
	module_translate(md, 0, 0, -6);
	for(int i=0; i<3; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}
}

void module_alphabet_P(Module *md);
void module_alphabet_P(Module *md){
		//4
	for(int i=0; i<6; i++){
		module_cube(md);
		module_translate(md, 0,0,-2);
	}

	//1
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//2
	for(int i=0; i<2; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}

	//3
	module_translate(md, 0, 0, 2);
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}
}

void module_alphabet_H(Module *md);
void module_alphabet_H(Module *md){
	//1
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}

	//3
	module_translate(md, 0, 0, 6);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//2
	module_translate(md, 0, 0, -6);
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}
}

void module_alphabet_I(Module *md);
void module_alphabet_I(Module *md){
	//1
	module_translate(md, 2,0,0);
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}

	//2
	module_translate(md, -2,0,0);
	module_cube(md);
	for(int i=0; i<2; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//3
	module_translate(md, 0,0,12);
	module_cube(md);
	for(int i=0; i<2; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}
}

void module_alphabet_C(Module *md);
void module_alphabet_C(Module *md){
	//1
	module_translate(md, 2,0,0);
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}

	//2
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//3
	module_translate(md, -6,0,12);
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}
}

void module_alphabet_S(Module *md);
void module_alphabet_S(Module *md){
	//1
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//2
	for(int i=0; i<3; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}

	//3
	for(int i=0; i<3; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}

	//4
	for(int i=0; i<3; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}

	//5
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}
}



int main(int argc, char* argv[]){
	Image* src;
	Module *scene;
	Module* GRAPHICS;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Lighting *light;
	Point center;//center of animation
	Polygon poly;//polygon that holds the animation path points
	int frameNum;//holds the frame number for animation
	char filename[100];//holds the frame name
	Color Red;
	Color Blue;
	Color Green;
	Color Grey;
	Color Black;
	Color White;
	Color Yellow;
	Color DarkAmbiant;
	Color randColor[10];


	//setting colors
	Color_set(&Red, 1.0, 0.2, 0.1 );
	Color_set(&Blue, 0.1, 0.1, 1.0);
	Color_set(&Green, 0.1, 1, 0.1 );
	Color_set(&White, 1, 1, 1 );
	Color_set(&Grey, 0.6, 0.6, 0.6 );
	Color_set(&Black, 0.05, 0.05, 0.05);
	Color_set(&Yellow, 1, 0.894118, 0.709804);
	Color_set(&DarkAmbiant, 0.3, 0.3, 0.3);

	Color_set(&randColor[0], 0, 1, 1);
	Color_set(&randColor[1], 0.498039, 1, 0);
	Color_set(&randColor[2], 1, 0.54902, 0);
	Color_set(&randColor[3], 1, 0.0784314, 0.576471);
	Color_set(&randColor[4], 1, 0.843137, 0);
	Color_set(&randColor[5], 0.960784, 1, 0.980392);
	Color_set(&randColor[6], 1, 0.647059, 0);
	Color_set(&randColor[7], 1, 0.270588, 0);
	Color_set(&randColor[8], 0, 1, 0.498039);
	Color_set(&randColor[9], 1, 1, 0);



	// setting the view
	point_set3D( &(view.vrp), 35, 60, 30 );
	vector_set( &(view.vpn), -view.vrp.val[0]+35, -view.vrp.val[1], -view.vrp.val[2]);
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 1;
	view.du = 1.6;
	view.dv = 0.9;
	view.f = 1;
	view.b = 200;
	view.screenx = 1280;
	view.screeny = 720;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );


	//creating GRAPHICS module
	GRAPHICS = module_create();
	module_alphabet_G(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 10, 0, 0);
	module_alphabet_R(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 20, 0, 0);
	module_alphabet_A(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 30, 0, 0);
	module_alphabet_P(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 40, 0, 0);
	module_alphabet_H(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 50, 0, 0);
	module_alphabet_I(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 56, 0, 0);
	module_alphabet_C(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 68, 0, 0);
	module_alphabet_S(GRAPHICS);


	// setting the light
	light = lighting_create();
	lighting_add( light, LightAmbient, &Grey, NULL, NULL, 0, 0);
	lighting_add(light, LightPoint, &White , NULL, &view.vrp, 0, 0);
	// lighting_add(light, LightSpot, &White, &view.vpn, &view.vrp, cos(10*M_PI/180), 40);

	//setting drawstate
	ds = drawstate_create();
	point_copy(&(ds->viewer), &(view.vrp) );
	ds->shade = ShadePhong;
	// ds->shade = ShadeDepth;
	drawstate_setBody(ds, Black);
	drawstate_setSurface(ds, Red);
	drawstate_setSurfaceCoeff(ds, 5);

	//Animation
	frameNum =0;

	//path #1
	point_set3D(&center, 40, 0, -10);
  	view_rotate_circle(&poly, &center, 100, 50, 0, 0, 0);
  	polygon_print(&poly, stdout);
  	for(int k=0; k<100; k++){
  		frameNum++;
		point_set3D( &(view.vrp), poly.vertex[k].val[0], poly.vertex[k].val[1], poly.vertex[k].val[2]);
		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
		matrix_setView3D( &vtm, &view );

		//creating scene module
		scene = module_create();
		module_module(scene, GRAPHICS);

		// image
		src = image_create( view.screeny, view.screenx );

		//Drawing
		module_draw( scene, &vtm, &gtm, ds, light, src );
		sprintf(filename, "../images/frame_%.4d.ppm",frameNum);
		image_write( src, filename);
	}

	//path #2
	point_set3D(&center, 40, 0, -10);
  	view_rotate_circle(&poly, &center, 100, 90, 0, 0 , 0);
  	// polygon_print(&poly, stdout);
  	for(int k=0; k<100; k++){
  		if(frameNum == 119){
  			point_print(&view.vrp, stdout);
  			break;
  		}
  		view_rotate_circle(&poly, &center, 50, 50+k, 0-2*k, 0 , 0);
  		frameNum++;
		point_set3D( &(view.vrp), poly.vertex[k].val[0], poly.vertex[k].val[1], poly.vertex[k].val[2]);
		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
		matrix_setView3D( &vtm, &view );

		//creating scene module
		scene = module_create();
		module_module(scene, GRAPHICS);

		// image
		src = image_create( view.screeny, view.screenx );

		//Drawing
		module_draw( scene, &vtm, &gtm, ds, light, src );
		sprintf(filename, "../images/frame_%.4d.ppm",frameNum);
		image_write( src, filename);
	}

	//path #3
	for(int k=0; k<120; k++){

  		frameNum++;
  		if(frameNum <= 160){
			point_set3D( &(view.vrp), -3.345+(k), 36.298+(k), 28.391-(k/2.0));
			vector_set( &(view.vpn), -view.vrp.val[0]+k, -view.vrp.val[1], -view.vrp.val[2]);
			matrix_setView3D( &vtm, &view );
		}

		//creating scene module
		scene = module_create();
		module_module(scene, GRAPHICS);

		if(frameNum == 160){
			light = lighting_create();
			lighting_add( light, LightAmbient, &Grey, NULL, NULL, 0, 0);
		}
		// setting the light
		if(frameNum == 165){
			Point plight1;
			point_set3D(&plight1, -5, 10, -10);

			lighting_add(light, LightSpot, &White, &view.vpn, &plight1, cos(10*M_PI/180), 40);
		}
		if(frameNum == 175){
			Point plight2;
			point_set3D(&plight2, 85, 10, -10);

			lighting_add(light, LightSpot, &White, &view.vpn, &plight2, cos(10*M_PI/180), 40);
		}
		if(frameNum == 180){
			lighting_add(light, LightSpot, &White, &view.vpn, &view.vrp, cos(10*M_PI/180), 40);
		}

		if(frameNum >= 183){
			light = lighting_create();
			lighting_add( light, LightAmbient, &Grey, NULL, NULL, 0, 0);

			int output1 = 0 + (rand() % (int)(10 - 0 + 1));
			int output2 = 0 + (rand() % (int)(10 - 0 + 1));
			int output3 = 0 + (rand() % (int)(10 - 0 + 1));

			Point plight1;
			point_set3D(&plight1, -5, 10, -10);
			lighting_add(light, LightSpot, &randColor[output1], &view.vpn, &plight1, cos(10*M_PI/180), 40);

			Point plight2;
			point_set3D(&plight2, 85, 10, -10);
			lighting_add(light, LightSpot, &randColor[output2], &view.vpn, &plight2, cos(10*M_PI/180), 40);

			lighting_add(light, LightSpot, &randColor[output3], &view.vpn, &view.vrp, cos(10*M_PI/180), 40);
		}
		// image
		src = image_create( view.screeny, view.screenx );

		//setting drawstate
		ds = drawstate_create();
		point_copy(&(ds->viewer), &(view.vrp) );
		ds->shade = ShadePhong;
		// ds->shade = ShadeDepth;
		drawstate_setBody(ds, Black);
		drawstate_setSurface(ds, Red);
		drawstate_setSurfaceCoeff(ds, 5);

		//Drawing
		module_draw( scene, &vtm, &gtm, ds, light, src );
		sprintf(filename, "../images/frame_%.4d.ppm",frameNum);
		image_write( src, filename);
	}
	return(0);
}
