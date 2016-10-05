#ifndef GEN_ASSIGN_H
#define GEN_ASSIGN_H

#include <queue>

class GenAssign
{
private:

	int nAgts;			/* Número de agentes da instância */
	int nTasks;			/* Número de tarefas da instância */
	int maxProfit;		/* Candidato de solução para  a instância */
	int visitedNodes;	/* Quantidade de nós visitados */
	int **costs;		/* Custo de alocar o agente i à tarefa j, com
						   0<=i<= nAgts e 0<=j<= nTasks */
	int **profits;		/* Recurso consumido ao alocar o agente i à t
						   arefa j, com 0<=i<= nAgts e 0<=j<= nTasks */
	int *capacity;		/* Capacidade dos agentes */
	int *assign;		/* Alocações realizadas */
	int *colMaximum;	/* Somatórios dos maiores valores de '**profits'
						   a partir da coluna j, 0<=j<= nTasks  */

	/*
		Função privada chamada pela função pública 'solve()'.
		Executa o Branch and Bound para resolver a instância
		lida atualmente.

		INPUT: 	Tarefa para iniciar a busca, inicializada por 
				padrão com '0' pela função 'solve()'.
	*/
	void solve(int task);

	/*
		Verifica se o agente 'agt' é promissor para a tarefa
		'task'. Seu objetivo é eliminar a visita à nós irrel
		evantes, como nós que excedem a capacidade, ou nós q
		ue ao somar os recursos até aquele momento com os ma
		ores recursos possíveis futuramente(colMaximum['task+1'])
		não apresentar uma possíve solução melhor que a já e
		ncontrada.

		INPUT: 	Agente 'agt', com 0<=agt<=nAgts e uma tarefa
				'task' com 0<=task<=nTasks.
		OUTPUT:	true se 'agt' é promissor, e false caso cont
				rário.
	*/
	bool promising(int agt, int task);

	/*
		Calcula a soma dos custos atuais para um dado agente
		'agt', baseado na alocação atual '*assign'.

		INPUT:	Um agente 'agt', com 0<=agt<=nAgts.
		OUTPUT:	Um inteiro representando o custo total do ag
				ente.
	*/
	int actualCap(int agt);

	/*
		Calcula o lucro, ou recursos consumido, até o momento
		Para isso, usa o vetor '*assign' e a matriz '**profit
		s'.

		INPUT:	None
		OUTPUT:	Total de recursos consumidos com a alocação a
				tual.
	*/
	int totalProfit();

	/*
		Soma os maiores valores por coluna de '**profits' a p
		artir de uma coluna 'strtTask'.

		INPUT:	Coluna inicial.
		OUTPUT:	Soma dos maiores valores por coluna a partir 
				de 'strttask'.
	*/
	int colLimit(int strtTask);

	/*
		Soma os menores valores por coluna de '**profits' a p
		artir de uma coluna 'strtTask'.

		INPUT:	Coluna inicial.
		OUTPUT:	Soma dos menores valores por coluna a partir 
				de 'strttask'.
	*/
	int colMin(int strtTask);
	
	/*
		Verifica a ordem de acesso dos agentes em ordem decres
		cente dos recursos, ou '**profit' para uma tarefa 'task'

		
	*/
	std::queue<int> orderOfAcces(int task);

public:

	GenAssign();
	~GenAssign();
	int** getCosts();
	int** getProfits();
	int* getCapacity();
	int getNumAgts();
	int getNumTasks();
	int getMaxProfit();
	int getNumVisitedNodes();
	void solve();
	void showAssign();

};

#endif