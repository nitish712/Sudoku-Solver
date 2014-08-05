#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

#include "board.cpp"


#ifndef BASIC_OP_C
#define BASIC_OP_C

class BasicOperations {
	public:
		Board *game;
		void init_chance_board();
		BasicOperations(Board *g)
		{
			game = g;
			if(!(game->chance_board_initialised))
			{
				game->chance_board_initialised = 1;
				init_chance_board();
			}	
		}

		void clear_all(int num, int r, int c);
		void clear_roc(int num, int rc, int rorc=1);
		int clear_partial(int num, int s1, int s2, int e1, int e2);
		void clear_box(int num, int box_num);
		int clear_by_cord(int num, int r, int c);
		int get_box_num(int r, int c);
		pair<int,int> get_box_coords(int box_num);
		//function that has to be overridden
		//by all derived classes...
		//must actually perform the operations
		//that class is intended to
		//return 1 if the board was modified
		//else 0
		int perform_op();
};
int BasicOperations::clear_by_cord(int num, int r, int c)
{
	if(game->chance_board[r][c] & (1<<num))
	{
		game->chance_board[r][c] ^= (1<<num);
		return 1;
	}
	return 0;
}

pair<int,int> BasicOperations::get_box_coords(int box_num)
{
	return make_pair((box_num/3)*3, (box_num%3)*3);
}

//returns box_num for a given (r,c)
int BasicOperations::get_box_num(int r, int c)
{
	return (r/3)*3 + (c/3);
}
int BasicOperations::clear_partial(int num, int s1, int s2, int e1, int e2)
{
	int changed = 0;
	if(s1==e1)//its a row to update
	{
		for(int i=s2; i<=e2; ++i)
		{
			if(game->chance_board[s1][i]&(1<<num)){
				game->chance_board[s1][i] ^= (1<<num);
				changed = 1;
			}
		}
	}
	else if(s2==e2)//its a column to update
	{
		for(int i=s1; i<=e1; ++i)
		{
			if(game->chance_board[i][s2]&(1<<num)){
				game->chance_board[i][s2] ^= (1<<num);
				changed = 1;
			}
		}
	}
	return changed;
}
void BasicOperations::init_chance_board()
{
	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			if(game->board[i][j]!=-1){
				clear_all( game->board[i][j], i, j);
				//display();
			}
		}
	}
}
//clears a number in all possible places
void BasicOperations::clear_all(int num, int r, int c)
{
	clear_roc(num, r);
	clear_roc(num, c, 0);
	clear_box(num, (r/3)*3 + (c/3));
}

//rorc = 1 => clear the row
//else clear the col.
//removes the chance of 'num' in row/col
void BasicOperations::clear_roc(int num, int rc, int rorc)
{
	for(int i=0; i<9; ++i)
	{
		if(rorc)
		{
			if(game->chance_board[rc][i] && (game->chance_board[rc][i]&(1<<num)))
				game->chance_board[rc][i] ^= (1<<num);
		}
		else if(game->chance_board[i][rc] && (game->chance_board[i][rc]&(1<<num)))
			game->chance_board[i][rc] ^= (1<<num);
	}
}
//clears the 'num' in a given 'box_num' (3x3)
// 0   1   2
// 3   4   5
// 6   7   8
void BasicOperations::clear_box(int num, int box_num)
{
	int s_r = (box_num/3)*3, s_c = (box_num%3)*3;
	for(int i=s_r; i<s_r+3; ++i)
	{
		for(int j=s_c; j<s_c+3; ++j)
		{
			if(game->chance_board[i][j] && (game->chance_board[i][j]&(1<<num)))
				game->chance_board[i][j] ^= (1<<num);
		}
	}
}
#endif 
//int main(){}