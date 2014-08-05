#include "s_candidate.cpp"
#include "s_position.cpp"
#include "c_lines.cpp"
#include "n_pairs.cpp"
int main()
{
	Board p;
	
	SingleCandidate s_c(&p);
	SinglePosition s_p(&p);
	CandidateLines c_l(&p);
	NakedPairs n_p(&p);

	int level = 1;
	getchar();
	while(1){
		again:
			p.display();
			getchar();
			if(s_c.perform_op())
				goto again;
			level = max(level, 2);
			if(s_p.perform_op()){
				
				goto again;
			}
			level = max(level, 3);
			if(c_l.perform_op()){
				
				goto again;
			}
			level = max(level, 4);
			if(n_p.perform_op()){
				
				goto again;
			}
			level = max(level, 5);
			break;
	}
	while(1)
	{
		char g=getchar();
		if(g!='\n')
			p.display(g-'0');
	}
		//s.perform_op();
		//p.display();
	printf("Board Level:%d\n", level);
	return 0;
}