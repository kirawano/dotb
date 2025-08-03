//TODO rewrite functions to handle state more cleanly

#include <SDL2/SDL_render.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "include/backend.h"
#include "include/dotb.h"

#define WIN_X 640 
#define WIN_Y 960

SDL_Window *win;
SDL_Renderer* renderer;

SDL_Texture *font[51];

//notifies user if there's new dialogue
int draw_notifier () {
	if (!qempty()) {
		SDL_Rect qbox;
		qbox.x = 620;
		qbox.y = 460;
		qbox.h = 40;
		qbox.w = 20;

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &qbox);
	}
	SDL_RenderPresent(renderer);
	return 0;
}

//TODO package loading and rendering a texture into a single function for readability
int 
draw_background () {
	draw_notifier();
	SDL_RenderClear(renderer);


	SDL_Surface *image = SDL_LoadBMP("assets/bliss.bmp");
	SDL_Texture *bliss = SDL_CreateTextureFromSurface(renderer, image);
	if (!bliss){
		fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return 0;
	}

	image = SDL_LoadBMP("assets/box.bmp");
	SDL_Texture *box = SDL_CreateTextureFromSurface(renderer, image);
	if (!box) {
		fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return 0;
	}

	SDL_FreeSurface(image);
	image = NULL;

	SDL_Rect blissdst;
	blissdst.x = 0;
	blissdst.y = 0;
	blissdst.w = 640;
	blissdst.h = 480;
	SDL_RenderCopy(renderer, bliss, NULL, &blissdst);

	SDL_Rect boxdst;
	boxdst.x = 150;
	boxdst.y = 150;
	boxdst.w = 300;
	boxdst.h = 300;
	SDL_RenderCopy(renderer, box, NULL, &boxdst);

	draw_dialogue_box();

	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	SDL_DestroyTexture(bliss);
	bliss = NULL;
	SDL_DestroyTexture(box);
	box = NULL;

	return 1;
}

void 
draw_dialogue_box () {
	SDL_Rect dialogue_box;
	dialogue_box.x = 0;
	dialogue_box.y = WIN_Y/2;
	dialogue_box.h = WIN_Y/2;
	dialogue_box.w = WIN_X;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &dialogue_box);
}

int 
draw_ttt_board () {
	draw_dialogue_box();

	SDL_Surface *image = SDL_LoadBMP("assets/ttt.bmp");
	SDL_Texture *ttt = SDL_CreateTextureFromSurface(renderer, image);
	if (!ttt){
		fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return 0;
	}

	SDL_FreeSurface(image);
	image = NULL;

	SDL_Rect tttdst;
	tttdst.x = 0;
	tttdst.y = 0;
	tttdst.w = WIN_X;
	tttdst.h = WIN_Y/2;
	SDL_RenderCopy(renderer, ttt, NULL, &tttdst);

	SDL_RenderPresent(renderer);

	return 1;
}

//delay: amount of time between each message bleep
int
speak (char msg[256], Uint32 delay) {
	draw_background();
	int c;

	SDL_Rect ptr;
	ptr.x = 15;
	ptr.y = 490;
	ptr.w = 15;
	ptr.h = 25;

	for (int i = 0; i < 256; i++) {	
		if (msg[i] == '\0') return 0;
		c = grabc(msg[i]);
		
		//magic number means it's a newline
		if(c == 51 || ptr.x > WIN_X - 15){
			ptr.y += 50;
			ptr.x = 15;
		}
		else {
			if (SDL_RenderCopy( renderer, font[c], NULL, &ptr) < 0) {
				fprintf(stderr, "SDL_RenderCopy failed: %s\n", SDL_GetError());
				return 1;
			}
			ptr.x+=20;
		}

		//chop the rest of the text off, make it first in line in the queue, and return so user can read the rest of the displayed text
		if (ptr.y  >= WIN_Y - 15){
			char remainder[256];
			strncpy(remainder, msg + i, 256 - i);
			first_in_queue(remainder);
			return 0;
		}

		update_timer();

		//update window after delay
		SDL_Delay(delay);
		SDL_RenderPresent(renderer);
	}	


	return 0;
}

int
init () {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}



	win = SDL_CreateWindow("Don't Open the Box", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN);
	if (!win) {
		fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
		kill();
		return 1;
	}
	

	Uint32 rflags = SDL_RENDERER_SOFTWARE;
	renderer = SDL_CreateRenderer(win, -1, rflags);
	if (!renderer) {
		fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
		kill();
		return 1;
	}

	
	if (!load_fonts()) {
		kill();
		return 1;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	if (!draw_background()) {
		kill();
		return 1;
	}
	
	SDL_RenderPresent(renderer);

	return 1;
}



int 
grabc (char c) {
	static const char ascii_table[128] = { ['A'] = 0,['B'] = 1,['C'] = 2,['D'] = 3,['E'] = 4,['F'] = 5,['G'] = 6,['H'] = 7,['I'] = 8,['J'] = 9,['K'] = 10,['L'] = 11,['M'] = 12,['N'] = 13,['O'] = 14,['P'] = 15,['Q'] = 16,['R'] = 17,['S'] = 18,['T'] = 19,['U'] = 20,['V'] = 21,['W'] = 22,['X'] = 23,['Y'] = 24,['Z'] = 25, ['('] = 26, [')'] = 27, [' '] = 28, ['!'] = 29, ['?'] = 30, [':'] = 31, [';'] = 32, ['<'] = 33, ['>'] = 34, ['='] = 35, ['/'] = 36, ['0'] = 37, ['1'] = 38, ['2'] = 39, ['3'] = 40, ['4'] = 41, ['5'] = 42, ['6'] = 43, ['7'] = 44, ['8'] = 45, ['9'] = 46, [','] = 47, ['.'] = 48, ['"'] = 49, ['\''] = 50, ['\n'] = 51};

	if ((unsigned char) c >= 128)
		return -1; //invalid

	return ascii_table[(unsigned char) c];
}

int
load_fonts () {
	char index[10];
	char bmp[5] = ".bmp";

	SDL_Surface *image;

	for (int i = 0; i <= 50; i++) {
		char filename[30] = "assets/fonts/";
		sprintf(index, "%d", i);
		strcat(index, bmp);
		strcat(filename, index); 

		image = SDL_LoadBMP(filename);
		font[i] = SDL_CreateTextureFromSurface(renderer, image);

		if (!font[i]) {
			fprintf(stderr, "SDL_LoadBMP failed for %s: %s\n", filename, SDL_GetError());
			return 0;
		}
	}

	SDL_FreeSurface(image);
	image = NULL;

	return 1;

}

void 
kill () {
	//shut down
	for (int i = 0; i < 52; i++) {
        	if (font[i]) {
			SDL_DestroyTexture(font[i]);
            		font[i] = NULL;
        	}
	}

	if (win) {
        	SDL_DestroyWindow(win);
        	win = NULL;
    	} 
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
    	}
	SDL_Quit();
}


