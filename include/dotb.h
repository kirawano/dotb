#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#ifndef DOTB_H_
#define DOTB_H_

//gamestate functions
int load_game_state ();
int write_game_state (Uint32 time);

// queue helper functions
void addq (char* data);
char* grabq ();
int qempty ();

#endif
