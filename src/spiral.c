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

static Particle *spiral_emitter;

void spiral_emitter_update(Emitter *e);

void system_spiral()
{
	if (elapsed_ticks == 0) {
		spiral_emitter = particle_create();
		particles_add(spiral_emitter);

		spiral_emitter->lifetime = 60.0;
		spiral_emitter->reset_after_lifetime = 1;

		spiral_emitter->emitter = emitter_create();
		spiral_emitter->emitter->direction = interpolation_create_2(0.0, 0.0, 60.0, M_PI * 2.0);
		spiral_emitter->emitter->speed = interpolation_create_1(28.0);
		spiral_emitter->emitter->colour.a = interpolation_create_3(0, 1.0, 60 * 1, 0.6, 60 * 2, 0.0);
		spiral_emitter->emitter->colour.b = interpolation_create_1(1.0);
		spiral_emitter->emitter->lifetime = 60 * 2;
		spiral_emitter->emitter->frequency = interpolation_create_1(1 / 16.0);
		spiral_emitter->emitter->size = interpolation_create_3(0, 32.0, 60 * 1, 28.0, 60 * 2, 16.0);
		spiral_emitter->emitter->rotation = interpolation_create_2(0, 0.0, 60 * 2, 360.0);
		spiral_emitter->emitter->acceleration.y = interpolation_create_1(0.1);
		spiral_emitter->emitter->property_updater = spiral_emitter_update;
	} else {
		if (elapsed_ticks % (60 * 4) == 0) {
			spiral_emitter->emitter->colour.r = interpolation_create_1((rand() % 4) * 0.25);
			spiral_emitter->emitter->colour.g = interpolation_create_1((rand() % 4) * 0.25);
			spiral_emitter->emitter->colour.b = interpolation_create_1((rand() % 4) * 0.25);
		}
	}
}

void spiral_emitter_update(Emitter *e)
{

}