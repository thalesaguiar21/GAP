#ifndef READERWRITER_H
#define READERWRITER_H



template<typename T>
extern void printMat(T **matriz, int linha, int coluna);

template<typename T> 
extern T** readCost(int &linha, int &coluna);

template<typename T> 
extern T** readResource(int &linha, int &coluna);

template<typename T>
extern T* readAgentsCap(int &linha, int &coluna);


#endif