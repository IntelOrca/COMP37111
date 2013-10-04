/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "interpolation.h"

Interpolation interpolation_create(int count)
{
	Interpolation result;
	result.count = count;
	result.items = (InterpolationItem*)calloc(count, sizeof(InterpolationItem));
	return result;
}

void interpolation_dispose(Interpolation *interpolation)
{
	free(interpolation->items);
	free(interpolation);
}

void interpolation_set(Interpolation *interpolation, int index, double time, double value)
{
	interpolation->items[index].time = time;
	interpolation->items[index].value = value;
}

double linear_interpolate(double t, double b, double c, double d)
{
	return c * (t / d) + b;
}

double bicubic_interpolate(double t, double b, double c, double d)
{
	t /= d / 2;
	if (t < 1)
		return ((c / 2) * (t * t * t)) + b;
	t -= 2;
	return (c / 2) * ((t * t * t) + 2) + b;
}

double interpolate(Interpolation *interpolation, double time)
{
	int i;
	InterpolationItem *item_a, *item_b, *item;

	assert(interpolation != NULL);
	
	if (interpolation->count == 0)
		return 0.0;

	// Set defaults
	item_a = &interpolation->items[0];
	item_b = &interpolation->items[interpolation->count - 1];

	// Repeat interpolation
	time = fmod(time, item_b->time + 1.0);

	// Find a and b
	for (i = 0; i < interpolation->count; i++) {
		item = &interpolation->items[i];
		if (item->time <= time)
			item_a = item;
		if (item->time >= time) {
			item_b = item;
			break;
		}
	}

	// Check if a and b are same value
	if (item_a->value == item_b->value)
		return item_a->value;

	// Bicubic interpolation
	if (interpolation_mode == INTERPOLATIONMODE_LINEAR)
		return linear_interpolate(time - item_a->time, item_a->value, item_b->value - item_a->value, item_b->time - item_a->time);
	else if (interpolation_mode == INTERPOLATIONMODE_BICUBIC)
		return bicubic_interpolate(time - item_a->time, item_a->value, item_b->value - item_a->value, item_b->time - item_a->time);
	else
		return item_a->value;
}

Interpolation interpolation_create_1(double v0)
{
	Interpolation result = interpolation_create(1);
	result.items[0].value = v0;
	return result;
}

Interpolation interpolation_create_2(double t0, double v0, double t1, double v1)
{
	Interpolation result = interpolation_create(2);
	result.items[0].time = t0;
	result.items[0].value = v0;
	result.items[1].time = t1;
	result.items[1].value = v1;
	return result;
}

Interpolation interpolation_create_3(double t0, double v0, double t1, double v1, double t2, double v2)
{
	Interpolation result = interpolation_create(3);
	result.items[0].time = t0;
	result.items[0].value = v0;
	result.items[1].time = t1;
	result.items[1].value = v1;
	result.items[2].time = t2;
	result.items[2].value = v2;
	return result;

}

Interpolation interpolation_create_4(double t0, double v0, double t1, double v1, double t2, double v2, double t3, double v3)
{
	Interpolation result = interpolation_create(4);
	result.items[0].time = t0;
	result.items[0].value = v0;
	result.items[1].time = t1;
	result.items[1].value = v1;
	result.items[2].time = t2;
	result.items[2].value = v2;
	result.items[3].time = t3;
	result.items[3].value = v3;
	return result;
}

Interpolation interpolation_create_5(double t0, double v0, double t1, double v1, double t2, double v2, double t3, double v3, double t4, double v4)
{
	Interpolation result = interpolation_create(5);
	result.items[0].time = t0;
	result.items[0].value = v0;
	result.items[1].time = t1;
	result.items[1].value = v1;
	result.items[2].time = t2;
	result.items[2].value = v2;
	result.items[3].time = t3;
	result.items[3].value = v3;
	result.items[4].time = t4;
	result.items[4].value = v4;
	return result;
}