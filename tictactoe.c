#include <stdio.h>
#include <stdlib.h>
#include "include/dotb.h"
#include "include/backend.h"
#include "include/tictactoe.h"

//0 for blank, 1 for X, -1 for O


void print_board (struct Gamestate g) {
	printf("\n\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (g.grid[j][2-i] == 1)
				printf(" [X] ");
			else if (g.grid[j][2-i] == -1)
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
			g->grid[i][j] = 0;
		}
	}
	g->current_turn = 1;
	g->winner = 2; //magic number, means that nobody has won or lost
}

int num_available_moves (struct Gamestate gamestate) {
	int av_count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
            if (gamestate.grid[i][j] == 0) av_count++;
		}
	}
	return av_count;
}	

//hard-coding in is prolly faster
int check_winner (struct Gamestate gamestate){
	for (int i = 0; i < 3; i++) {
        if ( gamestate.grid[i][0] != 0 && gamestate.grid[i][0] == gamestate.grid[i][1] && gamestate.grid[i][1] == gamestate.grid[i][2]) {
			return gamestate.grid[i][0];
		}
		if ( gamestate.grid[0][i] != 0 && gamestate.grid[0][i] == gamestate.grid[1][i] && gamestate.grid[1][i] == gamestate.grid[2][i]) {
			return gamestate.grid[0][i];
		}
	}
	if (gamestate.grid[0][0] != 0 && gamestate.grid[0][0] == gamestate.grid[1][1] && gamestate.grid[1][1] == gamestate.grid[2][2]) {
		return gamestate.grid[0][0];
	}

	if (gamestate.grid[2][0] != 0 && gamestate.grid[2][0] == gamestate.grid[1][1] && gamestate.grid[1][1] == gamestate.grid[0][2]) {
		return gamestate.grid[2][0];
	}

	int av_count = num_available_moves(gamestate);
	//draw
	if (av_count == 0) {
		return 0;
	}

	return 2;
}


int make_turn (struct Gamestate * g, int x, int y) {
	if (abs(g->grid[x][y]) == 1 || g->winner != 2) {
		return 0;
	}

	g->grid[x][y] = g->current_turn;

	g->current_turn*=-1;

    int winner = check_winner(*g);
	if (winner != 2) {
        g->winner = winner;
	}
	return 1;
}

void copy (struct Gamestate * cpy, struct Gamestate g) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cpy->grid[i][j] = g.grid[i][j];
		} }
    cpy->current_turn = g.current_turn;
	cpy->winner = g.winner;
}

int maxi(struct Gamestate g, int alpha, int beta) {
    if (check_winner(g) != 2) return g.winner;
    int max = -10;
    struct Gamestate cpy;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            copy(&cpy, g);
            make_turn(&cpy, i, j);
            int score = mini(cpy, alpha, beta);
            if (score > max) {
                max = score;
                if (score > alpha) alpha = score;
            }
            if (score >= beta) return score;
        }
    }
    return max;
}
int mini(struct Gamestate g, int alpha, int beta) {
    if (check_winner(g) != 2) return g.winner;
    int min = 10;
    struct Gamestate cpy;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (g.grid[i][j] == 0) {
                copy(&cpy, g);
                make_turn(&cpy, i, j);
                int score = maxi(cpy, alpha, beta);
                if (score < min) {
                    min = score;
                    if (score < beta) beta = score;
                }
                if (score <= alpha) return score;
            }
        }
    }
    return min;
}
int hard_eval(struct Gamestate g, int * x, int * y) {
    if (num_available_moves(g) == 9) {
        *x = 1;
        *y = 1;
        return 0;
    }
    struct Gamestate cpy;
    int score;
    if (g.current_turn == 1) score = -10; else score = 10;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (g.grid[i][j] == 0) {
            copy(&cpy, g);
            make_turn(&cpy, i, j);
            if (g.current_turn == 1) {
                int e = mini(cpy, -10, 10);
                if (e > score) {
                    score = e;
                    *x = i;
                    *y = j;
                }
            }
            else {
                int e = maxi(cpy, -10, 10);
                if (e < score) {
                    score = e;
                    *x = i;
                    *y = j;
                }
            }
            }
        }
    }
    return score;
}

int main () {
	struct Gamestate gamestate;

	reset(&gamestate);
    int x, y, e;

    
	while (gamestate.winner == 2) {
		e = hard_eval(gamestate, &x, &y);
        printf("bot plays %i, %i\n", x, y);

        if (!make_turn(&gamestate, x, y)) break;
		printf("Engine evaluation: %i\n", e);
        if (gamestate.winner != 2) break;

        print_board(gamestate);

        while (1) {
            printf("x: ");
            scanf("%d", &x);
            printf("\ny: ");
            scanf("%d", &y);
            printf("\n");
            if (!make_turn(&gamestate, x, y)) {
                printf("move is not possible!\n");
            }
            else {
                break;
            }
        }
	}

    print_board(gamestate);
    if (gamestate.winner == 1) printf("bot wins!\n"); else if (gamestate.winner == -1) printf("you win!\n"); else printf("draw!\n");

	return 0;
}

