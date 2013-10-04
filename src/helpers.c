/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include "comp37111.h"
#include "helpers.h"
#include "texture.h"

double randDouble()
{
	return (rand() / (double)RAND_MAX);
}

double randNegDouble()
{
	if (rand() % 2 == 0)
		return -randDouble();
	else
		return randDouble();
}

double randBetween(double min, double max)
{
	double range = max - min;
	return min + (randDouble() * range);
}

double randomAngle(double minDeg, double maxDeg)
{
	return randBetween(minDeg, maxDeg) / 180.0 * M_PI;
}

void draw_texture(int texture, double size)
{
	set_texture(texture);
	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0);
		glVertex3d(-size, -size, 0);
		glTexCoord2d(0.0, 1.0);
		glVertex3d(-size, +size, 0);
		glTexCoord2d(1.0, 1.0);
		glVertex3d(+size, +size, 0);
		glTexCoord2d(1.0, 0.0);
		glVertex3d(+size, -size, 0);
	glEnd();
	unset_texture();
}

void draw_circle(double size, int points)
{
	int i;
	double angle_div = (2.0 * M_PI) / points;

	glBegin(GL_TRIANGLES);
	for (i = 0; i < points; i++) {
		double aa = angle_div * i;
		double bb = angle_div * (i + 1);

		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(size * cos(aa), size * sin(aa), 0.0);
		glVertex3d(size * cos(bb), size * sin(bb), 0.0);
	}

	glEnd();
}

void draw_string(void *font, float x, float y, const char *str)
{
	glRasterPos3f(x, y, 0);
	while (*str != 0)
		glutBitmapCharacter(font, *str++);
}

Colour get_colour(double a, double r, double g, double b)
{
	Colour c;
	c.a = a;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

void angle_to_velocity(double angle, double power, double *vx, double *vy)
{
	*vx = sin(angle) * power;
	*vy = cos(angle) * power;
}