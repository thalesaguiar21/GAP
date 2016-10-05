#include "ReaderWriter.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;

template<typename T> void printMat(T **matriz, int linha, int coluna){

	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			cout << matriz[i][j] << std::setw(3);
		}
		cout << "\n";
	}
	cout << "\n";
}
template void printMat<int>(int **matriz, int linha, int coluna);
template void printMat<double>(double **matriz, int linha, int coluna);


template<typename T> T** readCost(int &linha, int &coluna){
	
	cout << "Lendo os custos...\n";
	T **matriz;
	ifstream myFile("gap2-3.txt");		// Change this string to read another instace
	myFile >> linha; 
	myFile >> coluna;

	matriz = new T*[linha];
	for(int i=0; i<linha; i++){
		matriz[i] = new T[coluna];
		for(int j=0; j<coluna; j++){
			myFile >> matriz[i][j];
		}
	}

	cout << "A leitura dos custos foi finalizada com sucesso...\n";

	myFile.close();

	return matriz;
}
template int** readCost<int>(int &linha, int &coluna);
template double** readCost<double>(int &linha, int &coluna);


template<typename T> T** readResource(int &linha, int &coluna){
	
	T **matriz;
	T dunkey;

	ifstream myFile("gap2-3.txt");		// Change this string to read another instace
	cout << "Lendo os recursos...\n";
	myFile >> linha; 
	myFile >> coluna;

	//Jump the first matrix
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			myFile >> dunkey;
		}
	}

	matriz = new T*[linha];
	for(int i=0; i<linha; i++){
		matriz[i] = new T[coluna];
		for(int j=0; j<coluna; j++){
			myFile >> matriz[i][j];
		}
	}

	cout << "A leitura dos recursos foi finalizada com sucesso...\n";

	myFile.close();

	return matriz;
}
template int** readResource<int>(int &linha, int &coluna);
template double** readResource<double>(int &linha, int &coluna);


template<typename T> T* readAgentsCap(int &linha, int &coluna){
	
	T *array;
	T dunkey;

	ifstream myFile("gap2-3.txt");		// Change this string to read another instace	
	cout << "Lendo as capacidades dos agentes...\n";
	myFile >> linha; 
	myFile >> coluna;

	//Jump the first matrix
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			myFile >> dunkey;
		}
	}

	//Jump the second matrix
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			myFile >> dunkey;
		}
	}

	array = new T[linha];
	for(int i=0; i<linha; i++){
		myFile >>array[i];
	}

	cout << "A leitura das capacidades foi finalizada com sucesso...\n";

	myFile.close();

	return array;
}
template int* readAgentsCap<int>(int &linha, int &coluna);
template double* readAgentsCap<double>(int &linha, int &coluna);