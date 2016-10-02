#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Retorna uma matriz nula de linha X coluna 
template<typename T>
T** matrizNula(int linha, int coluna);

// Dada uma submatriz de '**col', indo da linha 'strtL' até 'lin'
// e da coluna 'strtC' até col, retorna a soma dos menores termos
// de cada linha de '**cost' 
// int lineLimit(int **cost, int lin, int col, int strtL, int strtC);

// Dada uma submatriz de '**col', indo da linha 'strtL' até 'lin'
// e da coluna 'strtC' até col, retorna a soma dos menores termos
// de cada coluna de '**cost'
// int colLimit(int **cost, int lin, int col, int strtL, int strtC);

int getTotalProfit(int **assign, int **profit, int lin, int col);

#endif