#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>

/*
  Creates a wire-frame cube

*/

// display callback
void display(void) {
  static starttime = 0.0;
  struct timeval tp;
  struct timezone tz;
  double curtime, delta, angle;

  // clear the background
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the color 
  glColor3f(1.0, 1.0, 1.0);

  // initialize the modelview matrix
  glLoadIdentity();

  // set up the view reference coordinates
  gluLookAt(4.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  // rotate once every 5s
  gettimeofday( &tp, &tz );
  curtime = tp.tv_sec + tp.tv_usec/1000000.0;
  if(starttime == 0.0) {
    starttime = curtime;
  }
  delta = curtime - starttime;
  angle = (int)(delta * 1000) % 5000;
  angle = angle * 360.0 / 5000.0;

  glRotatef(angle, 0.0, 1.0, 0.0 ); // rotate around the Y axis by angle;

  // create a wire cube
  glutWireCube(2.0);

  // flush the drawing commands
  glFlush();

  usleep(10000);
  glutPostRedisplay();
}

// resize callback
void reshape(int w, int h) {

  // set the viewport to the new window size
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  // update the projection matrix
  glMatrixMode(GL_PROJECTION);

  // reset
  glLoadIdentity();

  // set up the perspective projection
  // FOV in degrees, apsect ratio of the window, near clip plane, far clip plane
  gluPerspective((GLdouble)30, (GLdouble)w / (GLdouble)h, (GLdouble)2, (GLdouble)30);

  // back to modelview
  glMatrixMode(GL_MODELVIEW);
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

// initialization
void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

// main function
int main(int argc, char **argv) {

  // initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("hello world");
  init();

  // set up callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  // main loop
  glutMainLoop();

  return(0);
}
