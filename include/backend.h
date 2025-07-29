#include <SDL2/SDL.h>

#ifndef BACKEND_H_
#define BACKEND_H_

//SDL window handling
int init ();
int load_fonts ();
void kill ();

// text rendering
int grabc (char c);
int speak (char msg[256], Uint32 delay);

#endif
