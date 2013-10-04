/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <stdlib.h>
#include "collision.h"
#include "helpers.h"
#include "particle.h"

static Particle *firework_emitter;

static void firework_emitter_update(Emitter *e);
static void firework_exploision_emitter_update(Emitter *e);

void system_fireworks()
{
	if (elapsed_ticks == 0) {
		particles_clear();

		// Firework emitter
		firework_emitter = particle_create();
		particles_add(firework_emitter);
		firework_emitter->displacement.x = -500;
		firework_emitter->displacement.y = 500;
		firework_emitter->reset_after_lifetime = 1;

		firework_emitter->emitter = emitter_create();
		firework_emitter->emitter->property_updater = firework_emitter_update;
		firework_emitter->emitter->lifetime = 60;
		firework_emitter->emitter->frequency = interpolation_create_1(1 / 240.0);
		firework_emitter->emitter->speed = interpolation_create_1(16.0);
		firework_emitter->emitter->direction = interpolation_create_1(M_PI / 4.0 * 3.3);
		firework_emitter->emitter->colour.a = interpolation_create_3(0, 1.0, 60 * 1, 0.6, 60 * 2, 0.0);
		firework_emitter->emitter->colour.r = interpolation_create_1(1.0);
		firework_emitter->emitter->colour.g = interpolation_create_1(1.0);
		firework_emitter->emitter->colour.b = interpolation_create_1(1.0);
		firework_emitter->emitter->size = interpolation_create_1(16.0);
		firework_emitter->emitter->rotation = interpolation_create_2(0, 0.0, 60 * 2, 360.0);

		// Explosion A
		firework_emitter->emitter->emitter = emitter_create();
		firework_emitter->emitter->emitter->property_updater = firework_exploision_emitter_update;
		firework_emitter->emitter->emitter->lifetime = 45;
		firework_emitter->emitter->emitter->frequency = interpolation_create_1(2.0);
		firework_emitter->emitter->emitter->split = 1;
		firework_emitter->emitter->emitter->acceleration.y = interpolation_create_1(0.5);
		firework_emitter->emitter->emitter->colour.a = interpolation_create_3(0, 1.0, 60 * 1, 0.6, 60 * 2, 0.0);
		firework_emitter->emitter->emitter->colour.b = interpolation_create_1(1.0);
		firework_emitter->emitter->emitter->size = interpolation_create_1(8.0);
		firework_emitter->emitter->emitter->rotation = interpolation_create_2(0, 0.0, 60 * 2, 360.0);

		// Explosion B
		firework_emitter->emitter->emitter->emitter = emitter_create();
		firework_emitter->emitter->emitter->emitter->property_updater = firework_exploision_emitter_update;
		firework_emitter->emitter->emitter->emitter->lifetime = 60;
		firework_emitter->emitter->emitter->emitter->frequency = interpolation_create_1(4.0);
		firework_emitter->emitter->emitter->emitter->split = 1;
		firework_emitter->emitter->emitter->emitter->acceleration.y = interpolation_create_1(0.5);
		firework_emitter->emitter->emitter->emitter->colour.a = interpolation_create_1(1.0);
		firework_emitter->emitter->emitter->emitter->colour.r = interpolation_create_1(0.0);
		firework_emitter->emitter->emitter->emitter->colour.g = interpolation_create_1(1.0);
		firework_emitter->emitter->emitter->emitter->colour.b = interpolation_create_1(0.0);
		firework_emitter->emitter->emitter->emitter->size = interpolation_create_1(4.0);
		firework_emitter->emitter->emitter->rotation = interpolation_create_2(0, 0.0, 60 * 2, 360.0);
	} else {

	}
}

static void init()
{
	/*
	Particle *p;


	*/
}

static Colour random_colours[] = {
	{ 1.0, 1.0, 0.0, 0.0 },
	{ 1.0, 0.0, 1.0, 0.0 },
	{ 1.0, 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0, 0.0 },
};

static Colour random_colour()
{
	int num_colours = sizeof(random_colours) / sizeof(Colour);
	return random_colours[rand() % num_colours];
}

static void firework_emitter_update(Emitter *e)
{
	e->emitter->colour.r = interpolation_create_1((rand() % 4) * 0.25);
	e->emitter->colour.g = interpolation_create_1((rand() % 4) * 0.25);
	e->emitter->colour.b = interpolation_create_1((rand() % 4) * 0.25);
}

static void firework_exploision_emitter_update(Emitter *e)
{
	e->direction = interpolation_create_1(randomAngle(0, 360));
	e->speed = interpolation_create_1(12.0);

	if (e->emitter != NULL) {
		e->emitter->colour.r = interpolation_create_1((rand() % 4) * 0.25);
		e->emitter->colour.g = interpolation_create_1((rand() % 4) * 0.25);
		e->emitter->colour.b = interpolation_create_1((rand() % 4) * 0.25);
	}
}