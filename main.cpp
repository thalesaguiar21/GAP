#include <iostream>
#include "ReaderWriter.h"
#include "Functions.h"
#include "GenAssign.h"

using std::cin;
using std::cout;
using std::endl;


int main()
{
	GenAssign *gap = new GenAssign();

	cout << "Number of agents: " << gap->getNumAgts() <<endl;
	cout << "Number of tasks: " << gap->getNumTasks() <<endl;

	cout << "\nCost:\n";
	printMat<int>(gap->getCosts(), gap->getNumAgts(), gap->getNumTasks());

	cout << "\nProfits:\n";
	printMat<int>(gap->getProfits(), gap->getNumAgts(), gap->getNumTasks());

	cout << "\nAgents capacity:\n";
	int *aux = gap->getCapacity();
	for(int i=0; i<gap->getNumAgts(); i++){
		cout << aux[i] << " ";
	}
	cout << endl;


	gap->solve();
	cout << "\nThe maximum profit for this instance is: ";
	cout << gap->getMaxProfit() <<endl;


	delete aux;
	delete gap;
	return 0;
}