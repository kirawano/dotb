#ifndef TICTACTOE_H_
#define TICTACTOE_H_

struct Gamestate {
	int grid[3][3];
	int current_turn;
	int winner;
};

int check_winner (struct Gamestate gamestate);
int hard_eval (struct Gamestate g, int * x, int * y);
int maxi (struct Gamestate g, int alpha, int beta);
int mini (struct Gamestate g, int alpha, int beta);
int make_turn (struct Gamestate * g, int x, int y);
void reset (struct Gamestate * g);

#endif // TICTACTOE_H_
