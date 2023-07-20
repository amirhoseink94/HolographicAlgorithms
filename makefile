CC = g++
CFLAGS = -Wall -g
OPGLFLAGS = -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
ARMAFLAG = -larmadillo
extFLAG = -I ~/Desktop/ThreeDEnvironment/ext/
HEADERS = Particle.h

res: main.o
	$(CC) $(CFLAGS) -o res main.o $(ARMAFLAG)
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
