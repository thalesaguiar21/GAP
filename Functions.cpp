#include "Functions.h"
#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::cout;
using std::cin;
using std::endl;

// Retorna uma matriz nula de linha X coluna 
template<typename T> T** matrizNula(int linha, int coluna){
	
	T **matriz;
	matriz = new T*[linha];
	for(int i = 0; i < linha; i++){
		matriz[i] = new T[coluna];
		for(int j = 0; j < coluna; j++){
			matriz[i][j] = 0;
		}
	}

	return matriz;
}
template int** matrizNula<int>(int linha, int coluna);
template double** matrizNula<double>(int linha, int coluna); 

// int lineLimit(int **cost, int lin, int col, int strtL, int strtC){
	
// 	int lineLmt = 0;
// 	int min;

// 	for(int i=strtL; i<lin; i++){
// 		min = cost[i][0];
// 		for(int j=strtC; j<col; j++){
// 			if(cost[i][j] < min){
// 				min = cost[i][j];
// 			}
// 		}
// 		lineLmt += min;
// 	}
// 	return lineLmt;
// }

// int colLimit(int **cost, int lin, int col, int strtL, int strtC){
	
// 	int colLimit = 0;
// 	int min;

// 	for(int i=0; i<col; i++){
// 		min = cost[0][i];
// 		for(int j=0; j<lin; j++){
// 			if(cost[j][i] < min){
// 				min = cost[j][i];
// 			}
// 		}
// 		colLimit += min;
// 	}
// 	return colLimit;
// }