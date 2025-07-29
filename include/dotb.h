#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#ifndef DOTB_H_
#define DOTB_H_

//SDL window handling
int init ();
int load_game_state ();
int load_fonts ();
void kill ();


// text rendering
int grabc (char c);
int speak (char msg[256], Uint32 delay);

// queue helper functions
void addq (char* data);
char* grabq ();
int qempty ();

int init (void);
int load_game_state (void);
int load_fonts (void);
void kill (void);
int grabc (char c);
int speak (char msg[256], Uint32 delay);

void addq (char* data);
char* grabq ();
int qempty ();

#endif
