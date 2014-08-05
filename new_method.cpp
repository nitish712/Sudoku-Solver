#include "basic.cpp"
class new_method : public BasicOperations
{
	//any private methods that are called by 
	//perform_op()
	public:
		new_method(Board *g) : BasicOperations(g){}
		int perform_op();
};
int new_method::perform_op()
{
	//your code goes here...
	//should return 1 if the chance_board has changed
	//else return 0
}