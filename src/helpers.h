/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef HELPERS_H_
#define HELPERS_H_

#include "comp37111.h"

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) < (b) ? (b) : (a))
#endif

double randDouble();
double randNegDouble();
double randBetween(double min, double max);
double randomAngle(double minDeg, double maxDeg);

void draw_texture(int texture, double size);
void draw_circle(double size, int points);
void draw_string(void *font, float x, float y, const char *str);

Colour get_colour(double a, double r, double g, double b);

void angle_to_velocity(double angle, double power, double *vx, double *vy);

#endif