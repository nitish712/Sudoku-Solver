#include "basic.cpp"
class HiddenPairs : public BasicOperations
{
		pair<int, int*> tmp_arr[9];
		int indices[9];
		//int ind_cnt;
		int changed;
	public:
		HiddenPairs(Board* g) : BasicOperations(g){}
		int perform_op();
		void check_recur_n(int st, int cnt, int mx_cnt, int mx_idx, int val);
};
int HiddenPairs::perform_op()
{
	int degree = 2;//pairs, triplets...
	while(degree<=5)
	{
		for(int k=0; k<2; ++k)
		{
			//k=0 for rows, else columns
			for(int itr=0; itr<10; itr++)
				tmp_arr[itr][0] = 0;
			for(int i=0; i<9; ++i)
			{
				//check for row
				for(int j=0; j<9; ++j)
				{
					int vl = (k==0) ? game->chance_board[i][j] :
							game->chance_board[j][i];
					int cnt = 0;
					while(vl)
					{
						if(vl&1)
							tmp_arr[cnt][0] |= (1<<cnt);
						cnt++;
						vl>>=1;
					}
				}
				changed=0;
				check_recur_n(0, 0, degree, 9, 0);
				if(changed)
				{
					printf("changed %s\n",k==0?"row":"column" );
					return 1;
				}
			}
		}
		//now for each box...
		for(int i=0; i<3; ++i)
		{
			for(int j=0; j<3; ++j)
			{
				int k=0;
				for(int i1 = i; i1<i+3; i1++)
					for(int j1 = j; j1<j+3; j1++)
						tmp_arr[k++] = make_pair(game->chance_board[i1][j1],
							&game->chance_board[i1][j1]);

				changed = 0;
				check_recur_n(0, 0, degree, 9, 0);
				if(changed)
				{
					printf("Box no.(%d,%d) changed...\n",i,j );
					return 1;
				}
			}
		}
		degree++;
	}
	return 0;
}
void HiddenPairs::check_recur_n(int st, int cnt, int mx_cnt, int mx_idx, int val)
{
	if(cnt==mx_cnt)
	{
		if(__builtin_popcount(val)!=mx_cnt)
			return;

		//int tmp_vals[9];//to hold all the set bits
		printf("Found n-pairs:");
		for(int i=0; i<mx_cnt;++i)
			cout<<"("<<game->breakval(tmp_arr[indices[i]].first)
				<<"),";
		printf("\n");
		int j=0;
		for(int i=0; i<mx_idx; ++i)
		{//change vals of other elements
			if(i==indices[j])
			{
				++j;
				continue;
			}
			if(tmp_arr[i].first & val)//atleast one number matches
			{
				*tmp_arr[i].second &= ~(tmp_arr[i].first & val);
				changed = 1;
			}
		}
	}
	if(st >= mx_idx)
		return;

	for(int j=st; j<mx_idx; ++j)
	{
		if(tmp_arr[j].first==0)
			continue;
		indices[cnt] = j;
		check_recur_n(j+1, cnt+1, mx_cnt, mx_idx, val|tmp_arr[j].first);
	}
}
