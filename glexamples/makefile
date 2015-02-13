CC=gcc 
CFLAGS=-framework GLUT -framework OpenGL -framework Cocoa -O2 -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes -Wmissing-declarations -pedantic -Wno-deprecated -L/usr/local/include
CPPFLAGS = $(CFLAGS)


glview: glView.o
	gcc $(CFLAGS) -o $@ $^ 

glbez: glBezier.o
	gcc $(CFLAGS) -o $@ $^ 

gltex: glTexture.o tiff-util.o
	gcc $(CFLAGS) -o $@ $^ 

gltest: glTest.o
	gcc $(CFLAGS) -o $@ $^ 


clean:
	rm -f *.o *~ a.out




# -I/usr/X11R6/include -L/usr/X11R6/lib -I/opt/local/include -L/opt/local/lib -I./include 