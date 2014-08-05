#include "basic.cpp"
#ifndef S_POSITION 
#define S_POSITION
class SinglePosition : public BasicOperations
{
	public:
		SinglePosition(Board *g): BasicOperations(g){}

		int check_uniq_roc(int rc, int rorc=1);
		int check_uniq_box(int box_num);

		void fill_by_num(int num, int rc, int rorc=1);
		void fill_by_num_box(int num, int box_num);

		int perform_op();

};
int SinglePosition::perform_op()
{
	//first check along all the rows...
	for(int i=0; i<9; ++i)
	{
		int tmp;
		if((tmp = check_uniq_roc(i))!=-1)
			//there exists an element for single pos.
		{
			fill_by_num(tmp, i);
			//game->display();
			return 1;
		}
	}
	//now check along columns
	for(int i=0; i<9; ++i)
	{
		int tmp;
		if((tmp = check_uniq_roc(i,0))!=-1)
			//there exists an element for single pos.
		{
			fill_by_num(tmp, i,0);
			//game->display();
			return 1;
		}
	}
	//check in individual boxes
	for(int i=0; i<9; ++i)
	{
		int tmp;
		if((tmp = check_uniq_box(i))!=-1)
		{
			fill_by_num_box(tmp, i);
			//game->display();
			return 1;
		}
	}
	return 0;
}
int SinglePosition::check_uniq_box(int box_num)
{
	int s_r = (box_num/3)*3, s_c = (box_num%3)*3;
	unsigned int ans = 0, r_xor = 0;
	for(int i=s_r; i<s_r+3; ++i)
	{
		for(int j=s_c; j<s_c+3; ++j)
		{
			unsigned int tmp = ans;
			ans ^= game->chance_board[i][j];
			unsigned int tmp2 = ((~tmp) & ans);
			ans &= ~(tmp2 & r_xor);
			r_xor |= game->chance_board[i][j];
		}
	}
	if(ans)
	{
		int val = 0;
		while(!(ans&1)){
			ans >>= 1;
			val++;
		}
		printf("Found value in  box:%d, value:%d\n", box_num, val);
		return val;
	}
	return -1;
}
void SinglePosition::fill_by_num_box(int num, int box_num)
{
	int s_r = (box_num/3)*3, s_c = (box_num%3)*3;
	for(int i=s_r; i<s_r+3; ++i)
	{
		for(int j=s_c; j<s_c+3; ++j)
		{
			if(game->chance_board[i][j] & (1<<num))
			{//fill it 
				 game->board[i][j] = num;
				 game->chance_board[i][j] = 0;
				 clear_all(num, i, j);
			}
		}
	}
}
int SinglePosition::check_uniq_roc(int rc, int rorc)
{
	unsigned int ans = 0, r_xor = 0;
	for(int i=0; i<9; ++i)
	{
		unsigned int tmp = ans;
		ans ^= (rorc ? game->chance_board[rc][i] : game->chance_board[i][rc]);
		unsigned int tmp2 = ((~tmp) & ans);
		ans &= ~(tmp2 & r_xor);
		r_xor |= (rorc ? game->chance_board[rc][i] : game->chance_board[i][rc]);
	}
	if(ans)
	{
		int val = 0;
		while(!(ans&1)){
			ans >>= 1;
			val++;
		}
		printf("Found value at single position %s:%d, value:%d\n", 
			(rorc ? "row" : "column"), rc, val);
		return val;
	}
	return -1;
}
void SinglePosition::fill_by_num(int num, int rc, int rorc)
{
	for(int i=0; i<9; ++i)
	{
		int tmp = (rorc ? game->chance_board[rc][i] : game->chance_board[i][rc]) & (1<<num);
		if(tmp)//set the value and clear_all on 'num'
		{
			if(rorc){
				game->board[rc][i] = num;
				game->chance_board[rc][i] = 0;
				clear_all(num, rc, i);
			} 
			else
			{
				game->board[i][rc] = num;
				game->chance_board[i][rc] = 0;
				clear_all(num, i, rc);
			}
		}

	}
}
#endif