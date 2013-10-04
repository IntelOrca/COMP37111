/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <stdlib.h>
#include <string.h>
#include "comp37111.h"
#include "menu.h"
#include "helpers.h"
#include "particle.h"

void emitter_emit(Emitter *e, Particle *parent);

Emitter *emitter_create()
{
	Emitter *result = (Emitter*)malloc(sizeof(Emitter));
	memset(result, 0, sizeof(Emitter));
	return result;
}

Emitter *emitter_copy(Emitter *e)
{
	Emitter *result = (Emitter*)malloc(sizeof(Emitter));
	memcpy(result, e, sizeof(Emitter));
	if (e->emitter != NULL)
		result->emitter = emitter_copy(e->emitter);
	return result;
}

void emitter_dispose(Emitter *e)
{
	if (e->emitter != NULL)
		emitter_dispose(e->emitter);
	free(e);
}

void emitter_update(Emitter *e, Particle *parent)
{
	if (e->split) {
		if (e->split == 1 && parent->time >= parent->lifetime - 1) {
			e->frequency_next = interpolate(&e->frequency, parent->time) * frequency_factor;
			while (e->frequency_next >= 1.0) {
				e->frequency_next -= 1.0;
				emitter_emit(e, parent);
			}
			e->split = 0;
		}
	} else {
		e->frequency_next += interpolate(&e->frequency, parent->time) * time_factor * frequency_factor;
		while (e->frequency_next >= 1.0) {
			e->frequency_next -= 1.0;
			emitter_emit(e, parent);
		}
	}
}

void emitter_emit(Emitter *e, Particle *parent)
{
	Particle *p;

	// Update emitter properties
	if (e->property_updater != NULL)
		e->property_updater(e);

	// Emit
	p = particle_create();

	if (e->emitter != NULL)
		p->emitter = emitter_copy(e->emitter);
	p->lifetime = e->lifetime;

	{
		double d = interpolate(&e->direction, parent->time);
		if (parent->time > 120 - 1 && parent->time < 120 + 1)
			d = d;
	}

	angle_to_velocity(
		interpolate(&e->direction, parent->time),
		interpolate(&e->speed, parent->time),
		&p->velocity.x, &p->velocity.y
	);

	p->size = e->size;
	p->rotation = e->rotation;
	p->colour = e->colour;
	p->displacement = parent->displacement;
	p->acceleration = e->acceleration;

	particles_add(p);
}