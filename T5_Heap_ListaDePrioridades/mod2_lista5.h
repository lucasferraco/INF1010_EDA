#ifndef MOD2_LISTA5_H
#define MOD2_LISTA5_H

#include <string>

#define MAX_ELEMENTS 50

class Heap /* Min-Heap */
{
public:
	//Construtor vazio
	Heap();

	//Constroi o heap a partir de um vetor de elementos
	Heap(int* values, unsigned int size);

	//Constroi o heap a partir de outro heap
	Heap(const Heap& other);

	//Destroi o heap
	~Heap();

	//Retorna o numero de elementos atualmente no heap
	unsigned int size();
	
	//Insere um novo elemento
	void push(int value);

	//Retorna o elemento do topo
	int top();

	//Remove o elemento do topo
	void pop();

	//Exibe os elementos do heap
	void show(const std::string& title);

private:

	/* Funcoes privadas que julgar necessarias */
	
	//Retorna o pai do nó
	int parent(int i);
	
	//Retorna o filho a esquerda do nó
	int left(int i);
	
	//Retorna o filho a direita do nó
	int right(int i);
	
	//Mantem a propriedade do Heap
	void heapify(int i);

private:
	//Contem os elementos do heap
	int _container[MAX_ELEMENTS];

	//Tamanho atual do heap
	unsigned int _size;
};


#endif
