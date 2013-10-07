/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef COMP37111_H_
#define COMP37111_H_

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>

#if WIN32
	#include "../glut/glut.h"
#elif __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

typedef struct {
	double a, r, g, b;
} Colour;

typedef struct {
	double x, y, z;
} Vector3;

extern int window_width;
extern int window_height;
extern long long elapsed_ticks;
extern int num_loaded_textures;

// Particle systems
void system_fountain();
void system_spiral();
void system_snow();
void system_fireworks();
void system_manyfountains();

#define MAX_PARTICLE_SYSTEMS 5

void project2d();
void project3d();

#endif