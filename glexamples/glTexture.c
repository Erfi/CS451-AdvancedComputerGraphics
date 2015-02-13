#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <tiffio.h>
#include "tiff-util.h"

// hard coding these is not a great idea
#define TextureWidth 512
#define TextureHeight 512

// making these global is not a great idea
GLubyte textureImage[TextureHeight][TextureWidth][4];
GLuint  textureName;

// read the image file texture.tif (note the absence of error handling)
void createTextureImage(void) {
  uint32 row, col;
  uint32 *rawImage;
  long i, j;

  rawImage = tiff_read("texture.tif", &row, &col);

  for(i=0;i<TextureWidth;i++) {
    for(j=0;j<TextureHeight;j++) {
      textureImage[i][j][0] = rawImage[i*col + j] & 0x000000FF;
      textureImage[i][j][1] = (rawImage[i*col + j] & 0x0000FF00) >> 8;
      textureImage[i][j][2] = (rawImage[i*col + j] & 0x00FF0000) >> 16;
      textureImage[i][j][3] = 255;
    }
  }

  free(rawImage);

}

// main display functions
void display(void) {
	// clear the image
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* set the texturing function */
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  /* set the correct texture to the active texture */
  glBindTexture(GL_TEXTURE_2D, textureName);

  /* draw the object */
  glColor3f(1.0, 1.0, 1.0);

  glLoadIdentity();
  gluLookAt(4.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// create one quad
  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
  glEnd();

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

// a simple keyboard callback
void keyboard(unsigned char key, int x, int y) {

  if(key == 'q')
    exit(0);
}

void init(void) {
	// set the clear color
  glClearColor(0.0, 0.0, 0.0, 0.0);

	// set the shade model to smooth
  glShadeModel(GL_SMOOTH);

	// turn on the z-buffer
  glEnable(GL_DEPTH_TEST);

  /* enable texturing */
  glEnable(GL_TEXTURE_2D);

	// read in the texture data
  createTextureImage();
  
  /* call this because we haven't packed things */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  /* create the texture and make it the active texture*/
  glGenTextures(1, &textureName);
  glBindTexture(GL_TEXTURE_2D, textureName);

  /* set the texture so it clamps at the edge */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  /* Set the filters for magnifying and reducing the texture (linear interpolates a 2x2 block) */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


  /* Arguments:
     target - either GL_TEXTURE_2D or GL_PROXY_TEXTURE_2D
     level  - supply the level parameter if you have multiple resolutions, 0 otherwise
     internal format - specifies the method of description of the texels, one of 42 possible values (GL_RGBA is good)
     width and height - width and height of the texture (at least 64x64)
     border - width of the border of the texture
     format - format of the texture data
     type   - type of the texture data
     data   - pointer to the data
     */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage);
  
}

// main function
int main(int argc, char **argv) {

	// initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("texture test");
  init();

	// callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

	// main loop
  glutMainLoop();

  return(0);
}
