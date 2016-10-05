#include <iostream>
#include <sys/time.h>
#include "ReaderWriter.h"
#include "GenAssign.h"

using std::cin;
using std::cout;
using std::endl;


int main()
{
	GenAssign *gap = new GenAssign();
	struct timeval inicio, final;
    int tmili;

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

	gettimeofday(&inicio, NULL);
	gap->solve();
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

    cout << "Tempo decorrido: " << tmili << endl; 
	cout << "\nThe maximum profit for this instance is ";
	cout << gap->getMaxProfit() << endl;
	cout << "The algorithm visited ";
	cout << gap->getNumVisitedNodes();
	cout << " nodes.\n";


	delete aux;
	delete gap;
	return 0;
}