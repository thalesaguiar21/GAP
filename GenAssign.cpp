#include "GenAssign.h"
#include "ReaderWriter.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <cstdlib>


GenAssign::GenAssign(const char *fileName){

	visitedNodes = 0;
	maxProfit = 0;
	readInstance(fileName);
	assign = new int[nTasks];

	for(int i=0; i<nTasks; i++){
		assign[i] = -1;
	}

	colMaximum = new int[nTasks];
	for(int i=0; i<nTasks; i++){
		colMaximum[i] = colLimit(i);
	}
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
}

void GenAssign::readInstance(const char *fileName){
	costs = readResource<int>(fileName, nAgts, nTasks);
	profits = readCost<int>(fileName, nAgts, nTasks);
	capacity = readAgentsCap<int>(fileName, nAgts, nTasks);
	if(!costs || !profits || !capacity){
		std::cerr << "Error reading the file!\n";
		delete this;
		exit(1);
	}
}

void GenAssign::solve(){
	std::cout << "\nSolving the given instance of GAP...\n";
	solve(0);
}

void GenAssign::solve(int task){
	
	int cProfit = 0;
	int agt;
	std::queue<int> order = orderOfAcces(task);

	while(!order.empty()){
		agt = order.front();
		order.pop();
		if(promising(agt, task)){
			visitedNodes++;
			assign[task] = agt;
			if(task == nTasks){
				cProfit = totalProfit();
				if(cProfit > maxProfit){
					maxProfit = cProfit;
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
	if(isPromising && (assign[task] != -1)){
		isPromising = false;
	}
	if(isPromising && (task < nTasks)){
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

std::queue<int> GenAssign::orderOfAcces(int task){
	std::queue<int> orderQ;
	int order[nAgts];
	int prof[nAgts];

	for(int agt=0; agt<nAgts; agt++){
		order[agt] = agt;
		prof[agt] = profits[agt][task] /(float)costs[agt][task];
	}

	for(int i=0; i<nAgts; i++){
		for(int j=i+1; j<nAgts; j++){
			if(prof[j] > prof[i]){
				int aux = order[i];
				order[i] = order[j];
				order[j] = aux;
				aux = prof[i];
				prof[i] = prof[j];
				prof[j] = aux;
			}
		}
	}

	for(int i=0; i<nAgts; i++){
		orderQ.push(order[i]);
	}

	return orderQ;
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