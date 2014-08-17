/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "comp37111.h"
#include "helpers.h"
#include "particle.h"
#include "menu.h"

// Options
double time_factor;
double frequency_factor;
double gravity_modifier;
double size_factor;
double opacity_factor;
int particle_appearance;
int interpolation_mode = INTERPOLATIONMODE_LINEAR;
int system_mode = 1;

#define MAX_DISPLAY_TICKS 120

// Menu
int display_ticks_left = 0;
int current_menu_option = 0;

enum OPTION {
	OPTION_TIMEFACTOR,
	OPTION_FREQUENCYFACTOR,
	OPTION_GRAVITYMODIFIER,
	OPTION_SIZEFACTOR,
	OPTION_OPACITYFACTOR,
	OPTION_PARTICLEAPPERANCE,
	OPTION_INTERPOLATIONMODE,
	OPTION_SYSTEMMODE,
	OPTION_COUNT,
};

char *option_strings[] = {
	"Time factor",
	"Frequency factor",
	"Gravity modifier",
	"Size factor",
	"Opacity factor",
	"Particle apperance",
	"Interpolation mode",
	"Demo",
};

void menu_draw()
{
	char buffer[128];

	if (display_ticks_left <= 0)
		return;
	display_ticks_left--;

	switch (current_menu_option) {
	case OPTION_TIMEFACTOR:
		sprintf(buffer, "%s %.2f", option_strings[current_menu_option], time_factor);
		break;
	case OPTION_FREQUENCYFACTOR:
		sprintf(buffer, "%s %.1f", option_strings[current_menu_option], frequency_factor);
		break;
	case OPTION_GRAVITYMODIFIER:
		sprintf(buffer, "%s %.1f", option_strings[current_menu_option], gravity_modifier);
		break;
	case OPTION_SIZEFACTOR:
		sprintf(buffer, "%s %.1f", option_strings[current_menu_option], size_factor);
		break;
	case OPTION_OPACITYFACTOR:
		sprintf(buffer, "%s %.1f", option_strings[current_menu_option], opacity_factor);
		break;
	case OPTION_PARTICLEAPPERANCE:
		switch (particle_appearance) {
		case TEXTURE_TEAPOT:
			sprintf(buffer, "%s teapots", option_strings[current_menu_option]);
			break;
		case TEXTURE_NONE:
			sprintf(buffer, "%s none", option_strings[current_menu_option]);
			break;
		case TEXTURE_POINT:
			sprintf(buffer, "%s points", option_strings[current_menu_option]);
			break;
		case TEXTURE_LINE:
			sprintf(buffer, "%s lines", option_strings[current_menu_option]);
			break;
		case TEXTURE_CIRCLE:
			sprintf(buffer, "%s circles", option_strings[current_menu_option]);
			break;
		default:
			sprintf(buffer, "%s texture %d", option_strings[current_menu_option], particle_appearance);
			break;
		break;
		}
		break;
	case OPTION_INTERPOLATIONMODE:
		switch (interpolation_mode) {
		case INTERPOLATIONMODE_LINEAR:
			sprintf(buffer, "%s linear", option_strings[current_menu_option]);
			break;
		case INTERPOLATIONMODE_BICUBIC:
			sprintf(buffer, "%s bicubic", option_strings[current_menu_option]);
			break;
		break;
		}
		break;
	case OPTION_SYSTEMMODE:
		sprintf(buffer, "%s %d", option_strings[current_menu_option], system_mode);
		break;
	}
	

	glColor3d(1.0, 1.0, 1.0);
	draw_string(GLUT_BITMAP_9_BY_15, 8, 600 - 20, buffer);
}

void menu_up()
{
	display_ticks_left = MAX_DISPLAY_TICKS;
	if (current_menu_option > 0)
		current_menu_option--;
}

void menu_down()
{
	display_ticks_left = MAX_DISPLAY_TICKS;
	if (current_menu_option < OPTION_COUNT - 1)
		current_menu_option++;
}

void menu_left()
{
	display_ticks_left = MAX_DISPLAY_TICKS;
	switch (current_menu_option) {
	case OPTION_TIMEFACTOR:
		time_factor = max(time_factor - 0.05, 0.05);
		break;
	case OPTION_FREQUENCYFACTOR:
		if (frequency_factor <= 16.0)
			frequency_factor = max(frequency_factor - 0.1, 0.0);
		else
			frequency_factor = max(frequency_factor / 2.0, 0.0);
		break;
	case OPTION_GRAVITYMODIFIER:
		gravity_modifier = max(gravity_modifier - 0.1, -64.0);
		break;
	case OPTION_SIZEFACTOR:
		size_factor = max(size_factor - 0.1, 0.1);
		break;
	case OPTION_OPACITYFACTOR:
		opacity_factor = max(opacity_factor - 0.05, 0.0);
		break;
	case OPTION_PARTICLEAPPERANCE:
		particle_appearance = max(particle_appearance - 1, TEXTURE_TEAPOT);
		break;
	case OPTION_INTERPOLATIONMODE:
		interpolation_mode = max(interpolation_mode - 1, INTERPOLATIONMODE_LINEAR);
		break;
	case OPTION_SYSTEMMODE:
		system_mode = max(system_mode - 1, 1);
		break;
	}
}

void menu_right()
{
	display_ticks_left = MAX_DISPLAY_TICKS;
	switch (current_menu_option) {
	case OPTION_TIMEFACTOR:
		time_factor = min(time_factor + 0.05, 8.0);
		break;
	case OPTION_FREQUENCYFACTOR:
		if (frequency_factor >= 16.0) {
			if (frequency_factor < 32.0)
				frequency_factor = 16.0;
			frequency_factor = min(frequency_factor * 2.0, (double)(1 << 18));
		} else {
			frequency_factor = min(frequency_factor + 0.1, (double)(1 << 18));
			if (frequency_factor >= 16.05) {
				frequency_factor = 32.0;
			}
		}
		break;
	case OPTION_GRAVITYMODIFIER:
		gravity_modifier = min(gravity_modifier + 0.1, 64.0);
		break;
	case OPTION_SIZEFACTOR:
		size_factor = min(size_factor + 0.1, 64.0);
		break;
	case OPTION_OPACITYFACTOR:
		opacity_factor = min(opacity_factor + 0.05, 4.0);
		break;
	case OPTION_PARTICLEAPPERANCE:
		particle_appearance = min(particle_appearance + 1, num_loaded_textures - 1);
		break;
	case OPTION_INTERPOLATIONMODE:
		interpolation_mode = min(interpolation_mode + 1, INTERPOLATIONMODE_BICUBIC);
		break;
	case OPTION_SYSTEMMODE:
		system_mode = min(system_mode + 1, MAX_PARTICLE_SYSTEMS);
		break;
	}
}