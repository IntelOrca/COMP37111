/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#include <assert.h>
#include "comp37111.h"
#include "lodepng.h"
#include "texture.h"

// Texture structure
typedef struct {
	int width, height;
	GLubyte* bits;
	GLuint name;
} Texture;

// Texture array
#define MAX_TEXTURES 64
Texture *textures[MAX_TEXTURES];

Texture *current_texture;

int load_texture(int index, char *filename)
{
	int error;
	Texture *texture = (Texture*)malloc(sizeof(Texture));

	assert(textures[index] == NULL);

	// Load png file
	error = lodepng_decode_file(
		&texture->bits,
		(unsigned int*)&texture->width, (unsigned int*)&texture->height,
		filename,
		LCT_RGBA, 8
	);

	if (error != 0) {
		free(texture);
		return error;
	}

	// Create OpenGL texture
	glGenTextures(1, &texture->name);
	glBindTexture(GL_TEXTURE_2D, texture->name);

	textures[index] = texture;
	return 0;
}

void unload_texture(int index)
{
	Texture *texture = textures[index];
	assert(texture != NULL);

	glDeleteTextures(1, &texture->name);
	textures[index] = NULL;
}

void set_texture(int index)
{
	Texture *texture = textures[index];
	if (texture != current_texture) {
		current_texture = texture;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->bits);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	glEnable(GL_TEXTURE_2D);
}

void unset_texture()
{
	glDisable(GL_TEXTURE_2D);
}