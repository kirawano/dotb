#include <SDL2/SDL_events.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "include/backend.h"
#include "include/dotb.h"
#include "include/dialogue.h"
#include "include/tictactoe.h"

int first = 0;
int last = 0;
const char * diqueue[256];

int timer;
int base_timer;
int prev_timer;

int
main (){
	printf("%i\n", timer);
	if(!init()) {
                return 1;
        };

        
	if (!load_game_state()) {
                kill();
                return 1;
        };


	int running = 1;
	SDL_Event ev;
	int msg = 0;


	while (running) {
		prim_loop(ev, &running);

		update_timer();
		draw_notifier();
	}


	write_game_state(timer);
	kill();
    return 0;
}


void prim_loop (SDL_Event ev, int * running) {
	// Event loop
	while (SDL_PollEvent(&ev) != 0) {
		update_timer();
		switch (ev.type) {
			case SDL_QUIT:
				*running = 0;
				printf("quitting\n");
				break;

			case SDL_MOUSEBUTTONUP:
				switch (ev.button.button) {
					case SDL_BUTTON_LEFT:
						if (ev.button.x >= DIALOGUE_BOX_X && ev.button.x <= DIALOGUE_BOX_X + DIALOGUE_BOX_SIZE && ev.button.y >= DIALOGUE_BOX_Y && ev.button.y <= DIALOGUE_BOX_Y + DIALOGUE_BOX_SIZE && !qempty()) {
							speak(grabq(), 50);
						}

						if (ev.button.x >= TTT_BOX_X && ev.button.x <= TTT_BOX_X + TTT_BOX_SIZE && ev.button.y >= TTT_BOX_Y && ev.button.y <= TTT_BOX_Y + TTT_BOX_SIZE && !qempty()) {
							tictactoe(ev, running);
						}

						break;
				}

				break;

			case SDL_MOUSEMOTION:
				//hack? idk
				if (ev.motion.x >= DIALOGUE_BOX_X && ev.motion.x <= DIALOGUE_BOX_X + DIALOGUE_BOX_SIZE && ev.motion.y >= DIALOGUE_BOX_Y && ev.motion.y <= DIALOGUE_BOX_Y + DIALOGUE_BOX_SIZE) {
					draw_speak_button(1);
				}
				else {
					draw_speak_button(0);
				}

				if (ev.motion.x >= TTT_BOX_X && ev.motion.x <= TTT_BOX_X + TTT_BOX_SIZE && ev.motion.y >= TTT_BOX_Y && ev.motion.y <= TTT_BOX_Y + TTT_BOX_SIZE) {
					draw_ttt_button(1);
				}
				else {
					draw_ttt_button(0);
				}
				

		}
	}

	SDL_Delay(10);
}

void tictactoe (SDL_Event ev, int * running) {
	draw_ttt_board();

	struct Gamestate g;
	reset(&g);
	int i = 0;

	while (SDL_PollEvent(&ev) != 0 && !check_winner(&g)) {
		int x, y, ax, ay;
		update_timer();
		switch (ev.type) {
			case SDL_QUIT:
				*running = 0;
				printf("quitting\n");
			break;

			case SDL_MOUSEBUTTONUP:
				switch (ev.button.button) {
					case SDL_BUTTON_LEFT:
						//TODO clean this hack up and set positions correctly
						if (ev.button.x >= 20 && ev.button.x <= 220) x = 0;	
						else if (ev.button.x >= 220 && ev.button.x <= 420) x = 1;
						else if (ev.button.x >= 220 && ev.button.x <= 420) x = 2;

						if (ev.button.y >= 20 && ev.button.y <= 220) y = 0;
						else if (ev.button.y >= 220 && ev.button.y <= 420) y = 1;
						else if (ev.button.y >= 220 && ev.button.y <= 420) y = 2;
						
						make_turn(&g, x, y);

						int ev = eval(g, &ax, &ay);

						break;
				}
			break;

		}
	}

	i++;


	draw_background();

	printf("done");
}


int
write_game_state (Uint32 timer) {
	FILE* gamestate = fopen("gamestate", "w");
	fprintf(gamestate, "%d", timer);
	fclose(gamestate);
	return 0;
}

int
load_game_state () {
	FILE* gamestate = fopen("gamestate", "r");
	if (gamestate == NULL) {
		gamestate = fopen("gamestate", "a+");
		//no gamestate found => make a new one	
		fprintf(gamestate, "%d", timer);
		printf("Save file not found! New save file created.\n");
		rewind(gamestate);	
	} 

	char gs[64];
	if (fgets(gs, sizeof gs, gamestate) == NULL) {
		fprintf(stderr, "Failed to read save file\n");
		fclose(gamestate);
		return 0;
	}   
	base_timer = atoi(gs);

	fclose(gamestate);
	return 1;
} 

//update timer, then check lookup table to see if (a) the dialogue has been grabbed before and if (b) dialogue exists
void
update_timer () {
	const char *dialogue;

	timer = base_timer + (int) (SDL_GetTicks()/1000);
	if (timer != prev_timer && get_dialogue(timer, &dialogue)){
		addq(dialogue);
		prev_timer = timer;
	}
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
		const char* ret = diqueue[first];
		++first;
		return ret;
	}
	return NULL;
}

//THE WORST HACK THAT I'VE HAD THE DISPLEASURE OF LAYING MY EYES ON
void
first_in_queue (const char* data) {
	if (!qempty()) {
		--first;
		diqueue[first] = data;
	}
}


