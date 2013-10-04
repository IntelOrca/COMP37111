/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <stdlib.h>
#include "collision.h"
#include "helpers.h"
#include "menu.h"
#include "particle.h"

static Interpolation spread;
static Particle *fountain_emitter[3];

Particle *create_fountain(int x, int y, double angle);
void manyfountains_emitter_update(Emitter *e);

void system_manyfountains()
{
	int i;

	if (elapsed_ticks == 0) {
		CollisionBox *c;

		spread = interpolation_create_3(
			0.0, 4.0,
			120.0, 22.5,
			240.0, 4.0
		);

		fountain_emitter[0] = create_fountain(-300, 400, 45.0);
		fountain_emitter[1] = create_fountain(   0, 400, 45.0);
		fountain_emitter[2] = create_fountain(+300, 400, 45.0);

		c = collisionbox_create();
		c->x = -150;
		c->y = -1200;
		c->w = 300;
		c->h = 700;
		collisionboxes_add(c);
	} else {
		if (elapsed_ticks % (60 * 4) == 0) {
			for (i = 0; i < 3; i++) {
				fountain_emitter[i]->emitter->colour.r = interpolation_create_1((rand() % 4) * 0.25);
				fountain_emitter[i]->emitter->colour.g = interpolation_create_1((rand() % 4) * 0.25);
				fountain_emitter[i]->emitter->colour.b = interpolation_create_1((rand() % 4) * 0.25);
			}
		}
	}
}

Particle *create_fountain(int x, int y, double angle)
{
	Particle *fe;

	fe = particle_create();
	particles_add(fe);

	fe->displacement.x = x;
	fe->displacement.y = y;
	fe->lifetime = 120;
	fe->reset_after_lifetime = 1;

	fe->emitter = emitter_create();
	fe->emitter->speed = interpolation_create_1(28.0);
	fe->emitter->colour.a = interpolation_create_3(0, 1.0, 60 * 1, 0.6, 60 * 2, 0.0);
	fe->emitter->colour.b = interpolation_create_1(1.0);
	fe->emitter->lifetime = 60 * 2;
	fe->emitter->acceleration.y = interpolation_create_1(0.5);
	fe->emitter->frequency = interpolation_create_1(1 / 16.0);
	fe->emitter->size = interpolation_create_3(0, 32.0, 60 * 1, 28.0, 60 * 2, 16.0);
	fe->emitter->rotation = interpolation_create_2(0, 0.0, 60 * 2, 360.0);
	fe->emitter->property_updater = manyfountains_emitter_update;

	return fe;
}

void manyfountains_emitter_update(Emitter *e)
{
	double current_spread = interpolate(&spread, elapsed_ticks * time_factor);
	e->direction = interpolation_create_1(
		randomAngle(180.0 - current_spread, 180.0 + current_spread)
	);
}