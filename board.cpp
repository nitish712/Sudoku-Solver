#ifndef BOARD_C
#define BOARD_C

class Board
{
	public:
		int board[9][9];
		int chance_board[9][9];
		int chance_board_initialised;
		//variable to prevent multiple initialisations
		//by different operation classes
		Board();
		void display();
		void display(int num);
		string breakval(int v);
		void input();
		//void init_chance_board();

};

void Board::display(int num)
{
	for (int i = 0; i < 9; ++i)
	{
		for(int j=0; j<9; ++j)
		{
			cout<<setw(10)<<
			(chance_board[i][j]&(1<<num) ?
			 breakval(chance_board[i][j]):"")<<"--";
		}
		cout<<endl;
	}
}
void Board::input()
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
	chance_board_initialised = 0;
	//init_chance_board();
}
Board::Board()
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
	input();
}
string Board::breakval(int v)
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
void Board::display()
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
#endif 