#include "basic.cpp"
#include <math.h>
#ifndef S_CANDIDATE
#define S_CANDIDATE

class SingleCandidate : public BasicOperations
{
	public:
		SingleCandidate(Board *g) : BasicOperations(g) {}
		int check_for_one();
		int perform_op();

};
//this returns the box which has only one number 
//as chance...
//return format: (i,j) => ans=i*9 + j
//extract: r = ans/9, c= ans%9
//-1 if none found
int SingleCandidate::check_for_one()
{
	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			int tmp = game->chance_board[i][j];
			if(!tmp)
				continue;
			if(!(tmp&(tmp-1)))
			{
				printf("Found one. r=%d, c=%d, val=%d\n", i,j,(int)log2(tmp));
				return i*9 + j;
			}
		}
	}
	return -1;
}
int SingleCandidate::perform_op()
{
	int tmp;
	int modified = 0;
	if((tmp=check_for_one())!=-1)
	{
		int r = tmp/9, c = tmp%9;
		modified = 1;
		game->board[r][c] = log2(game->chance_board[r][c]);
		game->chance_board[r][c] = 0;
		
		clear_all(game->board[r][c], r, c);
		//game->display();
		//getchar();
		//getchar();
		//printf("* * * * * * * * * * * * * *\n");
	}
	//if(modified)
	//	game->display();
	return modified;
}
#endif