/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "comp37111.h"
#include "emitter.h"
#include "interpolation.h"

#define TEXTURE_TEAPOT (-5)
#define TEXTURE_NONE (-4)
#define TEXTURE_POINT (-3)
#define TEXTURE_LINE (-2)
#define TEXTURE_CIRCLE (-1)
#define TEXTURE_TEXTURE 0
#define DISPLACEMENT_HISTORY_SIZE 8

typedef struct s_Particle {
	// Static input
	Emitter *emitter;
	int reset_after_lifetime;
	int lifetime;

	// Dynamic input
	Interpolation size;
	Interpolation rotation;
	InterpolationColour colour;
	InterpolationVector3 acceleration;

	// Live variables
	double time;
	Vector3 displacement;
	Vector3 velocity;

	Vector3 displacement_history[DISPLACEMENT_HISTORY_SIZE];
} Particle;

#define MAX_PARTICLES 2000000
extern Particle *particles[MAX_PARTICLES];

void particles_clear();
void particles_update();
void particles_draw();
void particles_add(Particle *p);
int particles_count();
Particle *particle_create();

#endif