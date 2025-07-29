#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "include/dotb.h"

#define WIN_X 640 
#define WIN_Y 960

SDL_Window *win;
SDL_Surface *winSurface;

SDL_Surface *font[50];

int first = 0;
int last = 0;
char* diqueue[256];


int
main (int argc, char *argv[]){
	if(init() != 0) {
                return 1;
        };

	if (load_fonts() != 0) {
                kill();
                return 1;
        };

        /*
	if (load_game_state() != 0) {
                kill();
                return 1;
        };
        */

	addq("ABCDEFGHIJKLM\nNOPQRSTUVWXYZ");
	addq(" 0123456789(),.;:><?! .=.");

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 480;
	rect.w = 640;
	rect.h = 480;

	SDL_FillRect( winSurface, &rect, SDL_MapRGB( winSurface->format, 255, 255, 255 ) );

	int running = 1;
	SDL_Event ev;
	int msg = 0;

	while (running) {
		// Event loop
		while (SDL_PollEvent(&ev) != 0) {
			switch (ev.type) {
				case SDL_QUIT:
					running = 0;
					printf("quitting\n");
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.sym) {
						case SDLK_z:
							if (!qempty()) speak(grabq(), 50);
							break;
					}
					break;
			}
		}

		SDL_Delay(100);
	}

	kill();
    return 0;
}

//delay: amount of time between each message bleep
//TODO clear previous text before rendering new ones
int
speak (char msg[256], Uint32 delay) {
	int c;

	SDL_Rect ptr;
	ptr.x = 15;
	ptr.y = 480;

	for (int i = 0; i < 256; i++) {	
		if (msg[i] == '\0') return 0;
		c = grabc(msg[i]);
		
		if(c == 51 || ptr.x > 500){
			ptr.y += 50;
			ptr.x = -10;
		}
		else {
			SDL_BlitSurface(font[c], NULL, winSurface, &ptr);
			SDL_Delay(delay);
		}

		SDL_UpdateWindowSurface(win);
		ptr.x+=25;
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
		fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());;
        SDL_Quit();
		return 1;
	}
	winSurface = SDL_GetWindowSurface(win);
	if (!winSurface) {
		fprintf(stderr, "SDL_GetWindowSurface failed: %s\n", SDL_GetError());;
        SDL_DestroyWindow(win);
        SDL_Quit();
		return 1;
	}
	return 0;
}

int
load_game_state () {
	FILE* gamestate = fopen("gamestate", "r");
	if (!gamestate) {
		perror("Faild to read gamestate file");
		return 1;
	} 

	char gs[1];
	if (fgets(gs, sizeof gs, gamestate) == NULL) {
	    fprintf(stderr, "Failed to read gamestate file\n");
        fclose(gamestate);
        return 1;
	}   
	printf("%s\n", gs);

	fclose(gamestate);
	return 0;
} 

int
load_fonts () {
	char index[10];
	char bmp[5] = ".bmp";

	for (int i = 0; i < 50; i++) {
		char filename[30] = "assets/fonts/";
		sprintf(index, "%d", i);
		strcat(index, bmp);
		strcat(filename, index); 

		font[i] = SDL_LoadBMP(filename);
		if (!font[i]) {
			fprintf(stderr, "SDL_LoadBMP failed for %s: %s\n", filename, SDL_GetError());
			return 1;
		}
	}

	return 0;

}

void 
kill () {
	//shut down
	for (int i = 0; i < 39; i++) {
        if (font[i]) {
		    SDL_FreeSurface(font[i]);
            font[i] = NULL;
        }
	}
    if (win) {
        SDL_DestroyWindow(win);
        win = NULL;
    } 
	SDL_Quit();
}

int 
grabc (char c) {
	static const char ascii_table[128] = { ['A'] = 0,['B'] = 1,['C'] = 2,['D'] = 3,['E'] = 4,['F'] = 5,['G'] = 6,['H'] = 7,['I'] = 8,['J'] = 9,['K'] = 10,['L'] = 11,['M'] = 12,['N'] = 13,['O'] = 14,['P'] = 15,['Q'] = 16,['R'] = 17,['S'] = 18,['T'] = 19,['U'] = 20,['V'] = 21,['W'] = 22,['X'] = 23,['Y'] = 24,['Z'] = 25, ['('] = 26, [')'] = 27, [' '] = 28, ['!'] = 29, ['?'] = 30, [':'] = 31, [';'] = 32, ['<'] = 33, ['>'] = 34, ['='] = 35, ['/'] = 36, ['0'] = 37, ['1'] = 38, ['2'] = 39, ['3'] = 40, ['4'] = 41, ['5'] = 42, ['6'] = 43, ['7'] = 44, ['8'] = 45, ['9'] = 46, [','] = 47, ['.'] = 48, ['"'] = 49, ['\''] = 50, ['\n'] = 51};

	if ((unsigned char) c >= 128)
		return -1; //invalid

	return ascii_table[(unsigned char) c];
}

//queue helper functions
void
addq (char* data) {
	diqueue[last] = data; 
	last++;
}

char*
grabq () {
	if (!qempty()) {
		char* ret = diqueue[first];
		++first;
		return ret;
	}
	return NULL;
}
int
qempty () {
	if (first == last) {
		return 1;
	}
	else {
		return 0;
	}

	return 0;
}
