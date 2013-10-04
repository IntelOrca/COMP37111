/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

typedef struct {
	double time;
	double value;
} InterpolationItem;

typedef struct {
	int count;
	InterpolationItem* items;
} Interpolation;

typedef struct {
	Interpolation x, y, z;
} InterpolationVector3;

typedef struct {
	Interpolation a, r, g, b;
} InterpolationColour;

Interpolation interpolation_create(int count);
void interpolation_dispose(Interpolation *interpolation);
void interpolation_set(Interpolation *interpolation, int index, double time, double value);

double interpolate(Interpolation *interpolation, double time);

Interpolation interpolation_create_1(double v0);
Interpolation interpolation_create_2(double t0, double v0, double t1, double v1);
Interpolation interpolation_create_3(double t0, double v0, double t1, double v1, double t2, double v2);
Interpolation interpolation_create_4(double t0, double v0, double t1, double v1, double t2, double v2, double t3, double v3);
Interpolation interpolation_create_5(double t0, double v0, double t1, double v1, double t2, double v2, double t3, double v3, double t4, double v4);

#endif