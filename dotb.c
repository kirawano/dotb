#include <stdio.h>

#include <SDL2/SDL.h>

#include "include/backend.h"
#include "include/dotb.h"

#define WIN_X 640 
#define WIN_Y 960

int first = 0;
int last = 0;
char* diqueue[256];

int
main (){
	if(!init()) {
                return 1;
        };

        /*
	if (load_game_state() != 0) {
                kill();
                return 1;
        };
        */
	addq("DON'T OPEN THE BOX.\nSERIOUSLY, JUST DON'T DO IT.");

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
						case SDLK_x:
							if (!qempty()) speak(grabq(), 25);
					}
					break;
			}
		}

		SDL_Delay(100);
	}

	kill();
    return 0;
}

int
load_game_state () {
	FILE* gamestate = fopen("gamestate", "r");
	if (!gamestate) {
		perror("Failed to read gamestate file");
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

//queue helper functions
void
addq (char* data) {
	diqueue[last] = data; 
	last++;
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

char*
grabq () {
	if (!qempty()) {
		char* ret = diqueue[first];
		++first;
		return ret;
	}
	return NULL;
}

