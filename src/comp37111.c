/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "comp37111.h"
#include "menu.h"
#include "texture.h"
#include "helpers.h"
#include "particle.h"
#include "collision.h"

int window_width;
int window_height;
long long elapsed_ticks;
int num_loaded_textures;

void initGraphics(int argc, char *argv[]);
void display(void);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void reshape(int width, int height);

void render_hud();

int main(int argc, char *argv[])
{
	srand(time(NULL));
	initGraphics(argc, argv);
	glEnable(GL_POINT_SMOOTH);
	glutMainLoop();
}

void load_textures()
{
	int i, result;
	char buffer[256];

	num_loaded_textures = 0;
	for (i = 0; ; i++) {
		sprintf(buffer, "textures/%02d.png", i);
		if ((result = load_texture(i, buffer)) == 0)
			num_loaded_textures++;
		else
			break;
	}
}

void initGraphics(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("COMP37111 Particles");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);

	load_textures();
}

double eyeX;
double eyeY;
double eyeZ;
double pan_angle;

double fps;
int frame;
int fps_time;
int fps_timebase;

int last_system_mode = -1;

void display(void)
{
	frame++;
	fps_time = glutGet(GLUT_ELAPSED_TIME);

	if (fps_time - fps_timebase > 1000) {
		fps = frame * 1000.0 / (fps_time - fps_timebase);
	 	fps_timebase = fps_time;
		frame = 0;
	}

	project3d();
	gluLookAt(	eyeX, eyeY, eyeZ,
				0.0, 0.0, 0.0,
				0.0, 1.0, 0.0);

	eyeX = 0;
	eyeY = 0;
	eyeZ = 1000;

	pan_angle += M_PI / 256.0;

	// Clear the screen
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glLineWidth(size_factor);
	glPointSize(size_factor);

	// Run and draw particle system
	if (last_system_mode != system_mode) {
		last_system_mode = system_mode;
		elapsed_ticks = 0;
	}
	switch (system_mode) {
	default:
	case 1:
		system_fountain();
		break;
	case 2:
		system_spiral();
		break;
	case 3:
		system_snow();
		break;
	case 4:
		system_fireworks();
		break;
	}

	elapsed_ticks++;

	particles_update();
	collisionboxes_update();

	glPushMatrix();
	glScaled(1.0, -1.0, 1.0);
	particles_draw();
	collisionboxes_draw();
	glPopMatrix();

	render_hud();

	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 27)
		exit(0);
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		menu_left();
		break;
	case GLUT_KEY_RIGHT:
		menu_right();
		break;
	case GLUT_KEY_UP:
		menu_up();
		break;
	case GLUT_KEY_DOWN:
		menu_down();
		break;
	}
}

void reshape(int width, int height)
{
	window_width = width;
	window_height = height;

	glClearColor(0.9, 0.9, 0.9, 1.0);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void render_hud()
{
	char text[2048];

	project2d();
	glColor3d(1.0, 1.0, 1.0);

	sprintf(text, "FPS: %.1f", fps);
	draw_string(GLUT_BITMAP_HELVETICA_18, 8, 8 + 18, text);
	sprintf(text, "Particles: %d", particles_count);
	draw_string(GLUT_BITMAP_HELVETICA_18, 8, 8 + 18 + 2 + 18, text);
	sprintf(text, "Emitters: %d", emitters_count());
	draw_string(GLUT_BITMAP_HELVETICA_18, 8, 8 + 18 + 2 + 18 + 2 + 18, text);

	menu_draw();
}

void project2d()
{
	// 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, window_height, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void project3d()
{
	// 3D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)window_width / (GLfloat)window_height, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}