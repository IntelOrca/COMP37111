/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef EMITTER_H_
#define EMITTER_H_

#include "interpolation.h"

struct s_Particle;

typedef struct s_Emitter {
	// Emitter properties
	Interpolation frequency;
	double frequency_next;
	int split;
	void (*property_updater)(struct s_Emitter *);

	// Properties to give to emitted particles
	// Static input
	struct s_Emitter *emitter;
	int lifetime;
	int texture;
	Interpolation speed;
	Interpolation direction;

	// Dynamic input
	Interpolation size;
	Interpolation rotation;
	Interpolation opacity;
	InterpolationColour colour;
	InterpolationVector3 acceleration;
} Emitter;

int emitters_count();
Emitter *emitter_create();
Emitter *emitter_copy(Emitter *e);
void emitter_dispose(Emitter *e);
void emitter_update(Emitter *e, struct s_Particle *parent);

#endif