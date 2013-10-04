/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef MENU_H_
#define MENU_H_

void menu_draw();
void menu_up();
void menu_down();
void menu_left();
void menu_right();

// Options

enum INTERPOLATIONMODE {
	INTERPOLATIONMODE_LINEAR,
	INTERPOLATIONMODE_BICUBIC,
};

extern double time_factor;
extern double frequency_factor;
extern double gravity_modifier;
extern double size_factor;
extern double opacity_factor;
extern int particle_appearance;
extern int interpolation_mode;
extern int system_mode;

#endif