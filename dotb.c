#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "include/backend.h"
#include "include/dotb.h"
#include "include/dialogue.h"

#define WIN_X 640 
#define WIN_Y 960

int first = 0;
int last = 0;
const char * diqueue[256];

int timer = 0;
int prev_timer = 0;

int
main (){
	if(!init()) {
                return 1;
        };

        
	if (!load_game_state()) {
                kill();
                return 1;
        };

	const char *dialogue;

	int running = 1;
	SDL_Event ev;
	int msg = 0;


	while (running) {
		timer = (int) (SDL_GetTicks()/1000);
		if (timer != prev_timer && get_dialogue(timer, &dialogue)){
			addq(dialogue);
			prev_timer = timer;
		}

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

		SDL_Delay(10);
	}

	kill();
    return 0;
}

int
write_game_state (Uint32 time) {
	FILE* gamestate = fopen("gamestate", "w");
	fprintf(gamestate, "%d", time);
	fclose(gamestate);
	return 0;
}

int
load_game_state () {
	FILE* gamestate = fopen("gamestate", "r");
	if (!gamestate) {
		//no gamestate found => make a new one	
		write_game_state(0);
		fprintf(stderr, "Save file not found! New save file created, please restart.\n");
		return 0;
	} 

	char gs[64];
	if (fgets(gs, sizeof gs, gamestate) == NULL) {
		fprintf(stderr, "Failed to read save file\n");
		fclose(gamestate);
		return 0;
	}   
	timer = atoi(gs);
	printf("%i", timer);

	fclose(gamestate);
	return 1;
} 

//queue helper functions
void
addq (const char* data) {
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

