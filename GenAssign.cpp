#include "GenAssign.h"
#include "ReaderWriter.h"
#include "Functions.h"
#include <iostream>
#include <iomanip>


GenAssign::GenAssign(){
	maxProfit = 0;
	costs = readResource<int>(nAgts, nTasks);
	profits = readCost<int>(nAgts, nTasks);
	capacity = readAgentsCap<int>(nAgts, nTasks);
	assign = new int[nTasks];

	for(int i=0; i<nTasks; i++)
		assign[i] = -1;
}

GenAssign::~GenAssign(){
	for(int i=0; i < nAgts; i++){
		delete [] profits[i];
	}
	delete [] profits;

	for(int i=0; i < nAgts; i++){
		delete [] costs[i];
	}
	delete [] costs;

	delete [] assign;
}

void GenAssign::solve(){
	std::cout << "\nSolving the actual instance of GAP...\n";
	solve(0);
}


void GenAssign::solve(int task){
	
	int cProfit = 0;
	for(int agt=0; agt<nAgts; agt++){
		if(promising(agt, task)){
			assign[task] = agt;
			if(task == nTasks){
				cProfit = totalProfit();
				if(cProfit > maxProfit){
					maxProfit = cProfit; 
					std::cout << "New maximum: ";
					std::cout << maxProfit<<std::endl;
					std::cout << "Assignments: ";
					showAssign();
					std::cout << "\n";
				}
			}else
				solve(task+1);
		}
		assign[task] = -1;
	}
}



bool GenAssign::promising(int agt, int task){

	if(actualCap(agt) + costs[agt][task] > capacity[agt]){
		return false;
	}

	if(assign[task] != -1){
		return false;
	}
}

int GenAssign::actualCap(int agt){
	
	int consCap = 0;
	for(int task=0; task<nTasks; task++){
		if(assign[task] == agt){
			consCap += costs[agt][task];
		}
	}
	return consCap; 
}

int GenAssign::totalProfit(){

	int total = 0;
	for(int task=0; task<nTasks; task++)
		total += profits[assign[task]][task];
	return total;
}

void GenAssign::showAssign(){

	std::cout << "(";
	for(int task=0; task<nTasks; task++){
		std::cout << assign[task] << ((task==(nTasks-1)) ? "":", ");
	}
	std::cout << ")\n";
}

// Getters
int** GenAssign::getCosts(){
	return this->costs;
}

int** GenAssign::getProfits(){
	return this->profits;
}

int* GenAssign::getCapacity(){
	return this->capacity;
}

int GenAssign::getNumAgts(){
	return this->nAgts;
}

int GenAssign::getNumTasks(){
	return this->nTasks;
}

int GenAssign::getMaxProfit(){
	return this->maxProfit;
}