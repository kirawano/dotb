#ifndef TICTACTOE_H_
#define TICTACTOE_H_

struct Gamestate {
	int grid[3][3];
	//each point on the grid is a boolean
	int available_moves[3][3];
	int current_turn;
	int winner;
	//boolean
	int ai_x;
};

int check_winner (struct Gamestate * gamestate);
int eval (struct Gamestate g, int* x, int* y);
int make_turn (struct Gamestate * g, int x, int y);
void reset (struct Gamestate * g);

#endif // TICTACTOE_H_
