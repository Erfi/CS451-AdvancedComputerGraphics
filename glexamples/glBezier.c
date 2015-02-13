#include <OpenGL/gl.h>
#include <GLUT/glut.h>

/*
	Example program that generates a single Bezier surface with a light
	source.
*/

// 4x4 Bezier surface definition
GLfloat cpoints[4][4][3] = {{{-1.5, -1.5, 4.0},
														 {-0.5, -1.5, 2.0},
														 {0.5, -1.5, -1.0},
														 {1.5, -1.5, 2.0}},
														{{-1.5, -0.5, 1.0},
														 {-0.5, -0.5, 3.0},
														 {0.5, -0.5, 0.0},
														 {1.5, -0.5, -1.0}},
														{{-1.5, 0.5, 4.0}, 
														 {-0.5, 0.5, 0.0}, 
														 {0.5, 0.5, 3.0},
														 {1.5, 0.5, 4.0}},
														{{-1.5, 1.5, -2.0},
														 {-0.5, 1.5, -2.0},
														 {0.5, 1.5, 0.0},
														 {1.5, 1.5, -1.0}}};


// main display function
void display(void) {
  GLfloat position[] = {8.0, 2.0, 8.0, 1.0}; // 4th element defines whether directional (0) or position (1)

	// clear the image
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset the modelview matrix and set up the viewer
  glLoadIdentity();
	gluLookAt(10.0, 2.0, 8.0, 0.0, 0.0, 1.5, 0.0, 1.0, 0.0);

	// position the light source
  glLightfv(GL_LIGHT0, GL_POSITION, position);

	// create the Bezier surface
	glEvalMesh2(GL_FILL, 0, 80, 0, 80);

	// flush the drawing commands
  glFlush();
}

// resize window function
void reshape(int w, int h) {
	// set the drawing viewport to the new window size
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// update the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective((GLdouble)30, (GLdouble)w / (GLdouble)h, (GLdouble)2, (GLdouble)100);

	// go back to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
}

// initialize the light source colors and material colors
void initlights(void) {
	GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};

  GLfloat mat_diffuse[] = {0.3, 0.9, 0.5, 1.0};
  GLfloat mat_specular[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_shininess[] = {10.0};

	// set up the default material colors
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// set up the global lights
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  
	// set up light 0
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse);

	// enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

}

//  This function is called whenever a key event occurs.
//  The key value is in "key" and "x" and "y" hold the current mouse position
void keyboard(unsigned char key, int x, int y)
{
   switch( key) {
   case 'q': // quit
     exit(0);
     break;
   default:
     break;
   }
}

// initialization function
void init(void) {

	// set the clear color
  glClearColor(0.0, 0.0, 0.0, 0.0);

	// draw each polygon as a single flat color
  glShadeModel(GL_FLAT);

	// create a new 2D map
  glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &(cpoints[0][0][0]));

	// enable the maps
  glEnable(GL_MAP2_VERTEX_3);

	// enable the depth buffer
  glEnable(GL_DEPTH_TEST);

	// enable automatic surface normal calculation
  glEnable(GL_AUTO_NORMAL);

	// set up the grid
  glMapGrid2f(80, 0.0, 1.0, 80, 0.0, 1.0);

	initlights();
}

// main function
int main(int argc, char **argv) {

	// initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Bezier Surface");
  init();

	// callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

	// main loop
  glutMainLoop();

  return(0);
}
