/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "comp37111.h"
#include "menu.h"
#include "helpers.h"
#include "particle.h"
#include "texture.h"

Particle *particles_head = NULL;
Particle *particles_last = NULL;
int particles_count = 0;
int optimise_particles_last_add = 0;

void particle_dispose(Particle *p);
void particle_update();
void particle_draw();

void particles_clear()
{
	Particle **p = &particles_head, *current;
	while (*p != NULL) {
		current = *p;
		p = &((*p)->next);
		particle_dispose(current);
	}

	particles_count = 0;
}

void particles_update()
{
	Particle **last_next = &particles_head, *p = *last_next, *tmp;
	while (p != NULL) {
		// Update the particle
		particle_update(p);

		// Check if it should be removed
		if (p->time >= p->lifetime) {
			if (p->reset_after_lifetime) {
				p->time = 0;
			} else {
				*last_next = p->next;
				tmp = p;
				p = p->next;

				if (particles_last == tmp)
					particles_last = NULL;

				particle_dispose(tmp);
				particles_count--;
				continue;
			}
		}

		last_next = &(p->next);
		p = p->next;
	}
}

void particles_draw()
{
	if (particle_appearance != TEXTURE_NONE) {
		Particle *p = particles_head;
		while (p != NULL) {
			particle_draw(p);
			p = p->next;
		}
	}
}

void particles_add(Particle *p)
{
	if (particles_last != NULL) {
		assert(particles_last->next == NULL);
		particles_last->next = p;
	} else {
		Particle **pp = &particles_head;
		while (*pp != NULL) {
			pp = &((*pp)->next);
		}
		*pp = p;
	}

	particles_last = p;
	particles_count++;
}

int emitters_count()
{
	int count = 0;
	Particle *p = particles_head;
	while (p != NULL) {
		if (p->emitter != NULL)
			count++;
		p = p->next;
	}
	return count;
}

Particle *particle_create()
{
	Particle *result = (Particle*)malloc(sizeof(Particle));
	memset(result, 0, sizeof(Particle));
	return result;
}

void particle_dispose(Particle *p)
{
	if (p->emitter != NULL)
		emitter_dispose(p->emitter);
	free(p);
}

void particle_update(Particle *p)
{
	int i;

	// Update velocity
	Vector3 acceleration;
	acceleration.x = interpolate(&p->acceleration.x, p->time);
	acceleration.y = interpolate(&p->acceleration.y, p->time) * gravity_modifier;
	acceleration.z = interpolate(&p->acceleration.z, p->time);

	p->velocity.x += (acceleration.x * time_factor);
	p->velocity.y += (acceleration.y * time_factor);
	p->velocity.z += (acceleration.z * time_factor);

	// Update displacement
	for (i = DISPLACEMENT_HISTORY_SIZE - 1; i >= 0; i--)
		p->displacement_history[i] = p->displacement_history[i - 1];
	p->displacement_history[0] = p->displacement;

	p->displacement.x += (p->velocity.x * time_factor);
	p->displacement.y += (p->velocity.y * time_factor);
	p->displacement.z += (p->velocity.z * time_factor);

	// Update emitter
	if (p->emitter != NULL)
		emitter_update(p->emitter, p);

	// Update time
	p->time += time_factor;
}

void particle_draw(Particle *p)
{
	int i;

	// Colour
	glColor4d(
		interpolate(&p->colour.r, p->time),
		interpolate(&p->colour.g, p->time),
		interpolate(&p->colour.b, p->time),
		interpolate(&p->colour.a, p->time) * opacity_factor
	);

	// Primitives
	switch (particle_appearance) {
	case TEXTURE_TEAPOT:
		glPushMatrix();
		glTranslated(p->displacement.x, p->displacement.y, p->displacement.z);
		glRotated(interpolate(&p->rotation, p->time), 0.0, 0.0, 1.0);
		glutSolidTeapot(interpolate(&p->size, p->time) * size_factor);
		glPopMatrix();
		break;
	case TEXTURE_POINT:
		glBegin(GL_POINTS);
			glVertex3d(p->displacement.x, p->displacement.y, p->displacement.z);
		glEnd();
		break;
	case TEXTURE_LINE:
		if (p->time == 0) {
			glBegin(GL_POINTS);
				glVertex3d(p->displacement.x, p->displacement.y, p->displacement.z);
			glEnd();
		} else {
			glBegin(GL_LINES);
				glVertex3d(p->displacement.x, p->displacement.y, p->displacement.z);
				glVertex3d(p->displacement_history[0].x, p->displacement_history[0].y, p->displacement_history[0].z);

				for (i = 0; i < min(p->time, DISPLACEMENT_HISTORY_SIZE) - 1; i++) {
					glVertex3d(p->displacement_history[i].x, p->displacement_history[i].y, p->displacement_history[i].z);
					glVertex3d(p->displacement_history[i + 1].x, p->displacement_history[i + 1].y, p->displacement_history[i + 1].z);
				}
			glEnd();
		}
		break;
	case TEXTURE_CIRCLE:
		glPushMatrix();
		glTranslated(p->displacement.x, p->displacement.y, p->displacement.z);
		glRotated(interpolate(&p->rotation, p->time), 0.0, 0.0, 1.0);
		draw_circle(interpolate(&p->size, p->time) * size_factor, 8);
		glPopMatrix();
		break;
	default:
		glPushMatrix();	
		glTranslated(p->displacement.x, p->displacement.y, p->displacement.z);
		glRotated(interpolate(&p->rotation, p->time), 0.0, 0.0, 1.0);
		draw_texture(particle_appearance, interpolate(&p->size, p->time) * size_factor);
		glPopMatrix();
		break;
	}
}