#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#ifndef DOTB_H_
#define DOTB_H_

void update_timer ();

//gamestate functions
int load_game_state ();
int write_game_state (Uint32 time);

// queue helper functions
void addq (const char* data);
char* grabq ();
int qempty ();
void first_in_queue (const char* data);

//game loops
void tictactoe (SDL_Event ev, int * running);
void prim_loop (SDL_Event ev, int * running);

#endif
