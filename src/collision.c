/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <string.h>
#include "collision.h"
#include "particle.h"

CollisionBox *collisionboxes_head;

void collisionboxes_clear()
{
	CollisionBox **c = &collisionboxes_head, *current;
	while (*c != NULL) {
		current = *c;
		c = &((*c)->next);
		collisionbox_dispose(current);
	}

	particles_count = 0;
}

void collisionboxes_update()
{
	CollisionBox *c = collisionboxes_head;
	while (c != NULL) {
		collisionbox_update(c);
		c = c->next;
	}
}

void collisionboxes_draw()
{
	CollisionBox *c = collisionboxes_head;
	while (c != NULL) {
		collisionbox_draw(c);
		c = c->next;
	}
}

void collisionboxes_add(CollisionBox *c)
{
	CollisionBox **cc = &collisionboxes_head;
	while (*cc != NULL) {
		cc = &((*cc)->next);
	}
	*cc = c;
}

CollisionBox *collisionbox_create()
{
	CollisionBox *c = (CollisionBox*)malloc(sizeof(CollisionBox));
	memset(c, 0, sizeof(CollisionBox));

	c->colour.a = 1.0;
	c->colour.r = 1.0;
	c->colour.g = 1.0;
	c->colour.b = 1.0;

	return c;
}

void collisionbox_dispose(CollisionBox *c)
{
	free(c);
}

void collisionbox_updateparticle(CollisionBox *c, Particle *p)
{
	double rx, ry;

	rx = p->displacement.x - c->x;
	ry = p->displacement.y - c->y;
	
	if (rx < 0 || ry < 0 || rx > c->w || ry > c->h)
		return;

	// Work out which triangle quadrant its in
	if (rx >= ry && c->w - rx <= ry) {
		p->velocity.x *= -0.75;
		p->displacement.x = c->x + c->w;
	} else if (rx >= ry && c->w - rx >= ry) {
		p->velocity.y *= -0.75;
		p->displacement.y = c->y - 1;
	} else if (rx <= ry && 128 - rx <= ry) {
		p->velocity.y *= -0.75;
		p->displacement.y = c->y + c->h;
	} else {
		p->velocity.x *= -0.75;
		p->displacement.x = c->x - 1;
	}
}

void collisionbox_update(CollisionBox *c)
{
	Particle *p = particles_head;
	while (p != NULL) {
		collisionbox_updateparticle(c, p);
		p = p->next;
	}
}

void collisionbox_draw(CollisionBox *c)
{
	glColor4d(c->colour.r, c->colour.g, c->colour.b, c->colour.a);
	glBegin(GL_QUADS);
		glVertex3d(c->x, c->y, 0);
		glVertex3d(c->x, c->y + c->h, 0);
		glVertex3d(c->x + c->w, c->y + c->h, 0);
		glVertex3d(c->x + c->w, c->y, 0);
	glEnd();
}