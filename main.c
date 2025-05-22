#include <stdio.h>
#include <string.h>

#include <SDL.h>

#define WIN_X 640 
#define WIN_Y 960

SDL_Window *win;
SDL_Surface *winSurface;

SDL_Surface *font[50];

int first = 0;
int last = 0;
char* diqueue[256];

int init (void);
int load_game_state (void);
int load_fonts (void);
void kill (void);
int grabc (char c);
int speak (char msg[256], Uint32 delay);

void addq (char* data);
char* grabq ();
int qempty ();

int
main (){
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

	addq("HI");
	addq("HELLO WORLD");

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

/*
helper functions for speak
*/

int 
grabc (char c) {
	int value;

    	switch (c) {
		case 'A': value = 0; break;
		case 'B': value = 1; break;
		case 'C': value = 2; break;
		case 'D': value = 3; break;
		case 'E': value = 4; break;
		case 'F': value = 5; break;
		case 'G': value = 6; break;
		case 'H': value = 7; break;
		case 'I': value = 8; break;
		case 'J': value = 9; break;
		case 'K': value = 10; break;
		case 'L': value = 11; break;
		case 'M': value = 12; break;
		case 'N': value = 13; break;
		case 'O': value = 14; break;
		case 'P': value = 15; break;
		case 'Q': value = 16; break;
		case 'R': value = 17; break;
		case 'S': value = 18; break;
		case 'T': value = 19; break;
		case 'U': value = 20; break;
		case 'V': value = 21; break;
		case 'W': value = 22; break;
		case 'X': value = 23; break;
		case 'Y': value = 24; break;
		case 'Z': value = 25; break;
		case '(': value = 26; break;
		case ')': value = 27; break;
		case ' ': value = 28; break;
		case '!': value = 29; break;
		case '?': value = 30; break;
		case ':': value = 31; break;
		case ';': value = 32; break;
		case '<': value = 33; break;
		case '>': value = 34; break;
		case '=': value = 35; break;
		case '/': value = 36; break;
		case '0': value = 37; break;
		case '1': value = 38; break;
		case '2': value = 39; break;
		case '3': value = 40; break;
		case '4': value = 41; break;
		case '5': value = 42; break;
		case '6': value = 43; break;
		case '7': value = 44; break;
		case '8': value = 45; break;
		case '9': value = 46; break;
		case ',': value = 47; break;
		case '.': value = 48; break;
		case '"': value = 48; break;
		case '\'': value = 49; break;
		//magic numbers lmao
		case '\n': value = -1; break;
        	default: value = 100; // return 40 (blank) for non-standard and spaces 
    	}
    return value;
}


//delay: amount of time between each message bleep
//this may not be memory safe but we'll see
int
speak (char msg[256], Uint32 delay) {
	int c;

	SDL_Rect ptr;
	ptr.x = 15;
	ptr.y = 480;

	for (int i = 0; i < 256; i++) {	
		if (msg[i] == '\0') return 0;
		c = grabc(msg[i]);
		
		if (c >= 0) {
			SDL_BlitSurface(font[c], NULL, winSurface, &ptr);
			SDL_Delay(delay);
		}
		else {
			ptr.y += 50;
			ptr.x = -10;
		}

		if (SDL_UpdateWindowSurface(win) < 0) {
		        fprintf(stderr, "SDL_WindowSurface failed: %s\n", SDL_GetError());
                        return 1;
		} 
		ptr.x+=25;
	}	

	return 0;
}



