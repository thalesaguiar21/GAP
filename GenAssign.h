#ifndef GEN_ASSIGN_H
#define GEN_ASSIGN_H

class GenAssign
{
private:

	int nAgts;
	int nTasks;
	int maxProfit;
	int visitedNodes;
	int **costs;
	int **profits;
	int *capacity;
	int *assign;
	int *colMaximum;

	void solve(int index);
	bool promising(int agt, int task);
	int actualCap(int agt);
	int totalProfit();
	int colLimit(int strtTask);

public:

	GenAssign();
	~GenAssign();
	int** getCosts();
	int** getProfits();
	int* getCapacity();
	int getNumAgts();
	int getNumTasks();
	int getMaxProfit();
	int getNumVisitedNodes();
	void solve();
	void showAssign();

};

#endif