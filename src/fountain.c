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
static Particle *fountain_emitter;

void fountain_emitter_update(Emitter *e);

void system_fountain()
{
	if (elapsed_ticks == 0) {
		spread = interpolation_create_3(
			0.0, 4.0,
			120.0, 22.5,
			240.0, 4.0
		);

		fountain_emitter = particle_create();
		particles_add(fountain_emitter);

		fountain_emitter->displacement.y = 300;
		fountain_emitter->lifetime = 120;
		fountain_emitter->reset_after_lifetime = 1;

		fountain_emitter->emitter = emitter_create();
		fountain_emitter->emitter->speed = interpolation_create_1(28.0);
		fountain_emitter->emitter->colour.a = interpolation_create_3(0, 1.0, 60 * 1, 0.6, 60 * 2, 0.0);
		fountain_emitter->emitter->colour.b = interpolation_create_1(1.0);
		fountain_emitter->emitter->lifetime = 60 * 2;
		fountain_emitter->emitter->acceleration.y = interpolation_create_1(0.5);
		fountain_emitter->emitter->frequency = interpolation_create_1(1 / 16.0);
		fountain_emitter->emitter->size = interpolation_create_3(0, 32.0, 60 * 1, 28.0, 60 * 2, 16.0);
		fountain_emitter->emitter->rotation = interpolation_create_2(0, 0.0, 60 * 2, 360.0);
		fountain_emitter->emitter->property_updater = fountain_emitter_update;
	} else {
		if (elapsed_ticks % (60 * 4) == 0) {
			fountain_emitter->emitter->colour.r = interpolation_create_1((rand() % 4) * 0.25);
			fountain_emitter->emitter->colour.g = interpolation_create_1((rand() % 4) * 0.25);
			fountain_emitter->emitter->colour.b = interpolation_create_1((rand() % 4) * 0.25);
		}
	}
}

void fountain_emitter_update(Emitter *e)
{
	double current_spread = interpolate(&spread, elapsed_ticks * time_factor);
	fountain_emitter->emitter->direction = interpolation_create_1(
		randomAngle(180.0 - current_spread, 180.0 + current_spread)
	);
}