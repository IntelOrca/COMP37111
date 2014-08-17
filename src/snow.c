/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <stdlib.h>
#include "collision.h"
#include "menu.h"
#include "helpers.h"
#include "particle.h"

static Particle *snow_emitter;

static void init();

void system_snow()
{
	double size, startAngle;
	if (elapsed_ticks == 0)
		init();

	size = randBetween(8.0, 32.0);

	snow_emitter->displacement.x = sin((elapsed_ticks % 240) / (2.0 * M_PI)) * 1200;
	snow_emitter->emitter->colour.a = interpolation_create_1(randBetween(0.5, 1.0));
	snow_emitter->emitter->size = interpolation_create_1(size);
	snow_emitter->emitter->acceleration.y = interpolation_create_1(size / 10000.0);

	startAngle = randBetween(0.0, 180.0);
	snow_emitter->emitter->rotation = interpolation_create_2(
		0, startAngle,
		60 * 16, startAngle + 360.0
	);

	if (rand() % 2 == 0) {
		snow_emitter->emitter->acceleration.x = interpolation_create_5(
			60 * 0,	-0.01,
			60 * 4,	+0.01,
			60 * 8, -0.02,
			60 * 12, +0.02,
			60 * 16, -0.01
		);
	} else {
		snow_emitter->emitter->acceleration.x = interpolation_create_5(
			60 * 0,	+0.01,
			60 * 4,	-0.01,
			60 * 8, +0.02,
			60 * 12, -0.02,
			60 * 16, +0.01
		);
	}
}

static void snow_emitter_next(Emitter *e)
{
	snow_emitter->displacement.x = randBetween(0 - 1600, 0 + 600);
}

static void init()
{
	Particle *p;
	CollisionBox *c;

	time_factor = 0.6;
	frequency_factor = 2.0;
	gravity_modifier = 1.0;
	size_factor = 1.0;
	opacity_factor = 1.0;
	particle_appearance = 0;

	p = particle_create();
	snow_emitter = p;
	p->acceleration.x = interpolation_create_2(
		0, -0.1,
		180, +0.1
	);
	p->displacement.x = 0;
	p->displacement.y = -600;
	p->reset_after_lifetime = 1;
	p->lifetime = 240;
	p->emitter = emitter_create();
	p->emitter->lifetime = 1024;
	p->emitter->frequency = interpolation_create_1(1 / 4.0);
	p->emitter->speed = interpolation_create_1(2.0);
	p->emitter->direction = interpolation_create_1(M_PI / 4);

	p->emitter->size = interpolation_create_1(32.0);
	p->emitter->rotation = interpolation_create_2(
		0, 0,
		60 * 16, 360
	);

	p->emitter->texture = 0;
	p->emitter->colour.a = interpolation_create_1(1.0);
	p->emitter->colour.r = interpolation_create_1(1.0);
	p->emitter->colour.g = interpolation_create_1(1.0);
	p->emitter->colour.b = interpolation_create_1(1.0);
	p->emitter->property_updater = snow_emitter_next;

	particles_add(p);
}