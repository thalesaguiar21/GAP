#ifndef GEN_ASSIGN_H
#define GEN_ASSIGN_H

class GenAssign
{
private:

	int nAgts;
	int nTasks;
	int maxProfit;
	int **costs;
	int **profits;
	int *capacity;
	int *assign;

	void solve(int index);
	bool promising(int agt, int task);
	int actualCap(int agt);
	int totalProfit();

public:

	GenAssign();
	~GenAssign();
	int** getCosts();
	int** getProfits();
	int* getCapacity();
	int getNumAgts();
	int getNumTasks();
	int getMaxProfit();
	void solve();
	void showAssign();
};

#endif