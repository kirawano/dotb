#include <stdio.h>
#include <stdlib.h>
#include "include/dotb.h"
#include "include/backend.h"
#include "include/tictactoe.h"

//0 for blank, 1 for X, -1 for O

void print_board (int gamestate[3][3]) {
	printf("\n\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gamestate[j][2-i] == 1)
				printf(" [X] ");
			else if (gamestate[j][2-i] == -1)
				printf(" [O] ");
			else
			 	printf(" [ ] ");
		}
		printf("\n");
	}
	printf("\n\n");
}

void reset (struct Gamestate * g) {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			g->available_moves[i][j] = 1;
			g->grid[i][j] = 0;
		}
	}
	g->current_turn = 1;
	g->winner = -2; //magic number, means that nobody has won or lost
	g->ai_x = 1;

}

int num_available_moves (struct Gamestate gamestate) {
	int av_count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			av_count+=gamestate.available_moves[i][j];
		}
	}
	return av_count;
}	

//hard-coding in is prolly faster
int check_winner (struct Gamestate * gamestate){
	for (int i = 0; i < 3; i++) {
		if ( gamestate->grid[i][0] != 0 && gamestate->grid[i][0] == gamestate->grid[i][1] && gamestate->grid[i][1] == gamestate->grid[i][2]) {
			gamestate->winner = gamestate->grid[i][0];
			return 1;
		}
		if ( gamestate->grid[0][i] != 0 && gamestate->grid[0][i] == gamestate->grid[1][i] && gamestate->grid[1][i] == gamestate->grid[2][i]) {
			gamestate->winner = gamestate->grid[i][0];
			return 1;
		}
	}
	if (gamestate->grid[0][0] != 0 && gamestate->grid[0][0] == gamestate->grid[1][1] && gamestate->grid[1][1] == gamestate->grid[2][2]) {
		gamestate->winner = gamestate->grid[0][0];
		return 1;
	}

	if (gamestate->grid[2][0] != 0 && gamestate->grid[2][0] == gamestate->grid[1][1] && gamestate->grid[1][1] == gamestate->grid[0][2]) {
		gamestate->winner = gamestate->grid[2][0];
		return 1;
	}

	int av_count = num_available_moves(*gamestate);
	//draw
	if (av_count == 0) {
		gamestate->winner = 0;
		return 1;
	}

	return 0;
}


int make_turn (struct Gamestate * g, int x, int y) {
	if (abs(g->grid[x][y]) == 1) {
		return 0;
	}

	g->grid[x][y] = g->current_turn;

	
	if (check_winner(g)) {
		return 0;
	}
		

	g->available_moves[x][y] = 0;

	g->current_turn*=-1;

	
	return 1;
}

void copy (struct Gamestate * cpy, struct Gamestate g) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cpy->grid[i][j] = g.grid[i][j];
			cpy->available_moves[i][j] = g.available_moves[i][j];
		} } cpy->current_turn = g.current_turn;
	cpy->winner = g.winner;
	cpy->ai_x = g.ai_x;
}

int eval (struct Gamestate g, int* x, int* y) {
	// opening move will always be at center
	if (num_available_moves(g) == 9) {
		*x = 1;
		*y = 1; 
		return 0;
	}

	if (check_winner(&g)) return g.winner * g.current_turn;		

	int e = 1;

	struct Gamestate cpy; 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			copy(&cpy, g);
			if (cpy.available_moves[i][j]) {
				make_turn(&cpy, i, j);
				int ev = eval(cpy, x, y);
				if (ev < e) { 
					e = ev;
					*x = i;
					*y = j;
				}
			}
		}
	}	
	return e;
}

// eval with depth
int easy_eval (struct Gamestate g, int* x, int* y, int depth) {
	// opening move will always be at center
	if (num_available_moves(g) == 9) {
		*x = 1;
		*y = 1; 
		return 0;
	}

	if (depth == 0) return 0;
	if (check_winner(&g)) return g.winner * g.current_turn;	

	int e = 1;
	struct Gamestate cpy;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			copy(&cpy, g);	
			if (cpy.available_moves[i][j]) {
				make_turn(&cpy, i, j);
				int ev = eval(cpy, x, y);
				if (ev < e) { 
					e = ev;
					*x = i;
					*y = j;
				}

			}
		}
	}
	return e;
}

/*
int main () {
	struct Gamestate gamestate;

	reset(&gamestate);

	int x, y, e;
	eval(gamestate, &x, &y);
	printf("%i, %i\n", x, y);

	while (!check_winner(&gamestate)) {
		e = eval(gamestate, &x, &y);
		if (!make_turn(&gamestate, x, y)) break;

		printf("Engine evaluation: %i\n", e);

		print_board(gamestate.grid);
		printf("x: ");
		scanf("%d", &x);
		printf("\ny: ");
		scanf("%d", &y);
		printf("\n");
		
		if (!make_turn(&gamestate, x, y)) break;
	}
	print_board(gamestate.grid);

	return 0;
}
*/
