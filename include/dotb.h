#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#ifndef DOTB_H_
#define DOTB_H_

int load_game_state ();

// queue helper functions
void addq (char* data);
char* grabq ();
int qempty ();

#endif
