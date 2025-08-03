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
void draw_dialogue_box ();

// tictactoe
int draw_ttt_board ();
int play_ttt(int x, int y);

int draw_notifier();
int draw_background ();

#endif
