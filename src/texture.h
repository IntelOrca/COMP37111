/**************************************
 * COMP37111 Particle System Exercise *
 * University of Manchester           *
 * Ted John 2013                      *
 **************************************/

#ifndef TEXTURE_H_
#define TEXTURE_H_

int load_texture(int index, char *filename);
void unload_texture(int index);
void set_texture(int index);
void unset_texture();

#endif