#include "basic.cpp"
class CandidateLines : public BasicOperations
{
	public:
		CandidateLines(Board* g) : BasicOperations(g){}
		int perform_op();
		int check_c_lines(int box_num);
		pair<int, int> check_c_lines_num(int box_num, int num);
		int remove_adj_chances(int box_num, int num, int rc, int rorc);

};
int CandidateLines::perform_op()
{
	for(int i=0; i<9; ++i)
	{
		if(check_c_lines(i))
			return 1;
	}
	return 0;
}

int CandidateLines::check_c_lines(int box_num)
{
	pair<int, int> tmp;
	int modified = 0;
	for(int i=1; i<=9; ++i)
	{
		tmp = check_c_lines_num(box_num, i);
		if(tmp.first!=-1)
		{
			modified = 1;
			printf("Got an alignment. val:%d for %s:%d\n", i,
			(tmp.second?"Row":"Column"), tmp.first);
			 return remove_adj_chances(box_num, i, tmp.first, tmp.second);
		}

	}
	return 0;
}

int CandidateLines::remove_adj_chances(int box_num, int num, int rc, int rorc)
{
	int modified = 0;
	if(rorc)//then manipulate the row
	{
		for(int i=0; i<9; i+=3)
		{
			if(get_box_num(rc,i)!=box_num)
			{//this box can be filled....
				modified |= clear_partial(num, rc, i, rc, i+2);
			}
		}
	}
	else
	{
		for(int i=0; i<9; i+=3)
		{
			if(get_box_num(i,rc)!=box_num)
			{//this box can be filled....
				modified |= clear_partial(num, i, rc, i+2, rc);
			}
		}
	}
	return modified;
}
//checks if 'num' chances only lie on a single line
//in the box 'box_num'
//returns (rc, rorc) => if rorc=1 then rc is a row else column
//if nothing found => (-1, -1)
pair<int, int> CandidateLines::check_c_lines_num(int box_num, int num)
{
	int s_r = (box_num/3)*3, s_c = (box_num%3)*3;
	pair<int, int> first_point;
	//int got_first_point = 0;
	int count = 0;
	int rc = -1;
	int rorc = -1;
	for(int i=s_r; i<s_r+3; ++i)
	{
		for(int j=s_c; j<s_c+3; ++j)
		{
			if(game->chance_board[i][j] & (1<<num))
			{
				count++;
				if(count==1)
					first_point = make_pair(i,j);
				else if(count==2)
				{
					rc = (first_point.first == i) ? i : 
							((first_point.second == j) ? j : -1);
					if(rc==-1)
						return make_pair(-1,-1);
					rorc = (i==rc) ? 1 : 0;
				}
				else
				{
					if((rorc && i!=rc) || (!rorc && j!=rc))
						return make_pair(-1,-1);
				}
			}
		}
	}
	return make_pair(rc, rorc);
}