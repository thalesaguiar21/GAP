#include "GenAssign.h"
#include "ReaderWriter.h"
#include "Functions.h"
#include <iostream>
#include <iomanip>


GenAssign::GenAssign(){
	visitedNodes = 0;
	maxProfit = 0;
	costs = readResource<int>(nAgts, nTasks);
	profits = readCost<int>(nAgts, nTasks);
	capacity = readAgentsCap<int>(nAgts, nTasks);
	assign = new int[nTasks];

	for(int i=0; i<nTasks; i++)
		assign[i] = -1;

	for(int i=0; i<nTasks; i++)
		assign[i] = -1;

	colMaximum = new int[nTasks];
	for(int i=0; i<nTasks; i++){
		colMaximum[i] = colLimit(i);
	}

	colMinimum = new int[nTasks];
	for(int i=0; i<nTasks; i++){
		colMinimum[i] = colMin(i);
	}

	maxProfit=colMinimum[0];
	std::cout << "\nStarting with a maximum of ";
	std::cout << maxProfit << std::endl;
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

	delete [] colMaximum;

	delete [] colMinimum;
}

void GenAssign::solve(){
	std::cout << "\nSolving the actual instance of GAP...\n";
	solve(0);
}


void GenAssign::solve(int task){
	
	int cProfit = 0;
	for(int agt=0; agt<nAgts; agt++){

		if(promising(agt, task)){
			visitedNodes++;
			assign[task] = agt;
			if(task == nTasks){
				cProfit = totalProfit();
				if(cProfit > maxProfit){
					maxProfit = cProfit; 
					std::cout << "\nNew maximum: ";
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

	bool isPromising = true;

	if(actualCap(agt) + costs[agt][task] > capacity[agt]){
		isPromising = false;
	}
	if(assign[task] != -1){
		isPromising = false;
	}
	if(task < nTasks){
		if(totalProfit() + colMaximum[task] < maxProfit){
			isPromising = false;
		}	
	}

	return isPromising;
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
	for(int task=0; task<nTasks; task++){
		if(assign[task] != -1){
			total += profits[assign[task]][task];
		}
	}
	return total;
}

int GenAssign::colLimit(int strtTask){

	int maximum = 0;
	int total = 0;
	for(int task=strtTask; task<nTasks; task++){
		maximum = profits[0][task];
		for(int agt=1; agt<nAgts; agt++){
			if(profits[agt][task] > maximum){
				maximum = profits[agt][task];
			}
		}
		total += maximum;
	}
	return total;
}

int GenAssign::colMin(int strtTask){

	int minimum = 0;
	int total = 0;
	for(int task=strtTask; task<nTasks; task++){
		minimum = profits[0][task];
		for(int agt=1; agt<nAgts; agt++){
			if(profits[agt][task] < minimum){
				minimum = profits[agt][task];
			}
		}
		total += minimum;
	}
	return  total;
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

int GenAssign::getNumVisitedNodes(){
	return this->visitedNodes;
}