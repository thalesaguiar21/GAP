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

int GenAssign::initialSolution(){
	float costBenefit[nAgts][nTasks];
	int bTasks[nTasks][nAgts];
	float aux;
	int iaux;
	
	for(int agt=0; agt<nAgts; agt++){
		for(int tsk=0; tsk<nTasks; tsk++){
			costBenefit[agt][tsk] = costs[agt][tsk] / (float)profits[agt][tsk];
		}
	}

	for(int tsk=0; tsk<nTasks; tsk++){
		for(int agt=0; agt<nAgts; agt++){
			bTasks[tsk][agt] = agt;
		}
	}

	for(int tsk=0; tsk<nTasks; tsk++){
		for(int agt=0; agt<nAgts; agt++){
			for(int agt2=0; agt2<nAgts; agt2++){
				if(costBenefit[agt][tsk] < costBenefit[agt2][tsk]){
					aux = costBenefit[agt][tsk];
					costBenefit[agt][tsk] = costBenefit[agt2][tsk];
					costBenefit[agt2][tsk] = aux;

					iaux = bTasks[tsk][agt];
					bTasks[tsk][agt] = bTasks[tsk][agt2];
					bTasks[tsk][agt2] = iaux;
				}
			}
		}
	}

	for(int tsk=0; tsk<nTasks; tsk++){
		for(int agt = 0; agt<nAgts; agt++){
			if(actualCap(bTasks[tsk][agt]) + costs[bTasks[tsk][agt]][tsk] <= capacity[bTasks[tsk][agt]]){
				assign[tsk] = bTasks[tsk][agt];
				break;
			}
		}
	}

	return totalProfit();
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
	maxProfit = initialSolution();

	for(int tsk=0; tsk<nTasks; tsk++){
		assign[tsk] = -1;
		std::cout << colMaximum[tsk] << " ";
	}
	std::cout << "\n";
	solve(0);
}

void GenAssign::solve(int task){
	
	if(task >= nTasks) std::cout << task << "º tarefa.\n";
	int cProfit = 0;
	int agt;

	for(int agt = 0; agt < nAgts; agt++){
		if(promising(agt, task)){
			visitedNodes++;
			assign[task] = agt;
			if(task == nTasks-1){
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
	if(isPromising && (task+1 < nTasks)){
		if(totalProfit() + colMaximum[task+1] < maxProfit){
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