#include <SDL2/SDL.h>

#ifndef BACKEND_H_
#define BACKEND_H_

#define WIN_X 640 
#define WIN_Y 960

//clickable stuffs
#define DIALOGUE_BOX_X 20
#define DIALOGUE_BOX_Y WIN_Y - 130
#define DIALOGUE_BOX_SIZE 100

#define TTT_BOX_X WIN_X - 120
#define TTT_BOX_Y WIN_Y - 130
#define TTT_BOX_SIZE 100

//SDL window handling
int init ();
int load_fonts ();
void kill ();

// text rendering
int grabc (char c);
int speak (char msg[256], Uint32 delay);
int draw_dialogue_box ();

// buttons
int draw_speak_button (int hovered);
int draw_ttt_button (int hovered);

// tictactoe
int draw_ttt_board ();
int play_ttt(int x, int y);

int draw_notifier();
int draw_background ();

#endif
