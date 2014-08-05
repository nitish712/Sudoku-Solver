#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>
using namespace std;
int board[9][9];
int chance_board[9][9];

void single_candidate();
int single_position();

int check_uniq_roc(int rc, int rorc=1);
int check_uniq_box(int box_num);

int check_for_one();
void clear_all(int num, int r, int c);
void clear_roc(int num, int rc, int rorc=1);
void clear_box(int num, int box_num);
void fill_by_num(int num, int rc, int rorc=1);
void fill_by_num_box(int num, int box_num);
void play();

void input();
void init();
void display();


//this returns the box which has only one number 
//as chance...
//return format: (i,j) => ans=i*9 + j
//extract: r = ans/9, c= ans%9
//-1 if none found
int check_for_one()
{
	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			int tmp = chance_board[i][j];
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
//clears a number in all possible places
void clear_all(int num, int r, int c)
{
	clear_roc(num, r);
	clear_roc(num, c, 0);
	clear_box(num, (r/3)*3 + (c/3));
}
//rorc = 1 => clear the row
//else clear the col.
//removes the chance of 'num' in row/col
void clear_roc(int num, int rc, int rorc)
{
	for(int i=0; i<9; ++i)
	{
		if(rorc)
		{
			if(chance_board[rc][i] && (chance_board[rc][i]&(1<<num)))
				chance_board[rc][i] ^= (1<<num);
		}
		else if(chance_board[i][rc] && (chance_board[i][rc]&(1<<num)))
			chance_board[i][rc] ^= (1<<num);
	}
}
//clears the 'num' in a given 'box_num' (3x3)
// 0   1   2
// 3   4   5
// 6   7   8
void clear_box(int num, int box_num)
{
	int s_r = (box_num/3)*3, s_c = (box_num%3)*3;
	for(int i=s_r; i<s_r+3; ++i)
	{
		for(int j=s_c; j<s_c+3; ++j)
		{
			if(chance_board[i][j] && (chance_board[i][j]&(1<<num)))
				chance_board[i][j] ^= (1<<num);
		}
	}
}

//format:
//1 _ 2 5 _ _ 7 _ 9
//....
//....
void input()
{
	char g;
	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			cin>>g;
			if(g!='_')
			{
				chance_board[i][j] = 0;
				board[i][j] = g - '0';
				//clear_all(g-'0', i, j);//update the chance array
										//simultaneously...
			}
			else
				board[i][j] = -1;
		}
	}
}
void init_chance_board()
{
	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			if(board[i][j]!=-1){
				clear_all( board[i][j], i, j);
				//display();
			}
		}
	}
}
//initially fill all the boxes with 
//all chances
void init()
{
	for(int i=0; i<9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			chance_board[i][j] = 0;
			for(int k=1; k<10; ++k)
				chance_board[i][j] += (1<<k);
			//cout<<"v:"<<chance_board[i][j]<<"\n";
		}
	}
}
string breakval(int v)
{
	string ans;
	v>>=1;
	for(int i=1; i<10;++i)
	{
		if(v&1)
			ans += (i +'0');
		v>>=1;
	}
	return ans;
}
void display()
{
	for (int i = 0; i < 28; ++i)
	{
		printf("|");
	}
	printf("\n");
	for(int i=0; i<9; ++i)
	{
		printf("| ");
		for(int j=0; j<9; ++j)
		{
			if(board[i][j]==-1)
				printf("_ ");
			else
				printf("%d ", board[i][j]);

			if(j%3==2)
				printf(" | ");
		}
		printf("\n");
		if(i%3!=2) continue;
		for (int i = 0; i < 28; ++i)
		{
			printf("|");
		}
		printf("\n");
	}
	for (int i = 0; i < 9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			cout<<setw(10)<<breakval(chance_board[i][j])<<"--";
		}
		cout<<endl;
	}
}
int single_candidate()
{
	int tmp;
	while((tmp=check_for_one())!=-1)
	{
		int r = tmp/9, c = tmp%9;
		board[r][c] = log2(chance_board[r][c]);
		chance_board[r][c] = 0;
		clear_all(board[r][c], r, c);
		//getchar();
		//printf("* * * * * * * * * * * * * *\n");
	}
	display();
}
int check_uniq_box(int box_num)
{
	int s_r = (box_num/3)*3, s_c = (box_num%3)*3;
	unsigned int ans = 0, r_xor = 0;
	for(int i=s_r; i<s_r+3; ++i)
	{
		for(int j=s_c; j<s_c+3; ++j)
		{
			unsigned int tmp = ans;
			ans ^= chance_board[i][j];
			unsigned int tmp2 = ((~tmp) & ans);
			ans &= ~(tmp2 & r_xor);
			r_xor |= chance_board[i][j];
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
void fill_by_num_box(int num, int box_num)
{
	int s_r = (box_num/3)*3, s_c = (box_num%3)*3;
	for(int i=s_r; i<s_r+3; ++i)
	{
		for(int j=s_c; j<s_c+3; ++j)
		{
			if(chance_board[i][j] & (1<<num))
			{//fill it 
				 board[i][j] = num;
				 chance_board[i][j] = 0;
				 clear_all(num, i, j);
			}
		}
	}
}
int check_uniq_roc(int rc, int rorc)
{
	unsigned int ans = 0, r_xor = 0;
	for(int i=0; i<9; ++i)
	{
		unsigned int tmp = ans;
		ans ^= (rorc ? chance_board[rc][i] : chance_board[i][rc]);
		unsigned int tmp2 = ((~tmp) & ans);
		ans &= ~(tmp2 & r_xor);
		r_xor |= (rorc ? chance_board[rc][i] : chance_board[i][rc]);
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
void fill_by_num(int num, int rc, int rorc)
{
	for(int i=0; i<9; ++i)
	{
		int tmp = (rorc ? chance_board[rc][i] : chance_board[i][rc]) & (1<<num);
		if(tmp)//set the value and clear_all on 'num'
		{
			if(rorc){
				board[rc][i] = num;
				chance_board[rc][i] = 0;
				clear_all(num, rc, i);
			} 
			else
			{
				board[i][rc] = num;
				chance_board[i][rc] = 0;
				clear_all(num, i, rc);
			}
		}

	}
}
int single_position()
{
	//first check along all the rows...
	for(int i=0; i<9; ++i)
	{
		int tmp;
		if((tmp = check_uniq_roc(i))!=-1)
			//there exists an element for single pos.
		{
			fill_by_num(tmp, i);
			display();
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
			display();
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
			display();
			return 1;
		}
	}
}
void play()
{

}
int main()
{
	init();
	input();
	init_chance_board();
	int tmp;
	//display();
	//printf("* * * * * * * * * * * * * *\n");
	single_candidate();
	while(1){
		single_position();
		getchar();	
	}
	
	return 0;
}
