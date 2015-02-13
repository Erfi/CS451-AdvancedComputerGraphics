#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

// Function for drawing the contents of the screen
void display(void) {
  GLfloat position[] = {10.0, 5.0, 20.0, 1.0};
	int i;

	// clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	// reset the modelview matrix
  glLoadIdentity();

	// set up the viewing transformation
	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// set up the light
  glLightfv(GL_LIGHT0, GL_POSITION, position);

	// set up a sphere
	glutSolidSphere(1.0, 32, 32);

	// draw everything
  glFlush();
}

//  Function called when the window is resized
void reshape(int w, int h) {
	// set the viewport to the updated window size
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// move to projection matrix mode
  glMatrixMode(GL_PROJECTION);

	// reset the projection to identity
  glLoadIdentity();

	// create the new perspective matrix
  gluPerspective((GLdouble)30, (GLdouble)w / (GLdouble)h, (GLdouble)2, (GLdouble)100);

	// go back to model view matrix mode
  glMatrixMode(GL_MODELVIEW);

	// reset the modeview matrix
  glLoadIdentity();
}

// initialize the lighting and material color values
void initlights(void) {
	GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
	GLfloat specular[] = {0.5, 0.5, 0.5, 1.0};
  GLfloat mat_diffuse[] = {0.3, 0.9, 0.5, 1.0};
  GLfloat mat_specular[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat mat_shininess[] = {50.0};

	// material values
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// generic lighting values
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  
  // specific light source
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular );

	// enable lighting, light0 and depth testing
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST); // important, or you can see through the sphere

}

// init function
void init(void) {
	// background color
  glClearColor(0.0, 0.0, 0.0, 0.0);

	// whether shading is smooth or flat
  glShadeModel(GL_SMOOTH);

	initlights();
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

// main function
int main(int argc, char **argv) {

	// initialize
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Sphere");
  init();

	// set up the callback functions
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

	// run the main loop
  glutMainLoop();

  return(0);
}
