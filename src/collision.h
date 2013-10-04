/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "comp37111.h"

typedef struct s_CollisionBox {
	struct s_CollisionBox *next;

	double x, y, w, h;
	Colour colour;
} CollisionBox;

void collisionboxes_clear();
void collisionboxes_update();
void collisionboxes_draw();
void collisionboxes_add(CollisionBox *c);

CollisionBox* collisionbox_create();
void collisionbox_dispose(CollisionBox *c);
void collisionbox_update(CollisionBox *c);
void collisionbox_draw(CollisionBox *c);

extern CollisionBox* collisionboxes_head;

#endif