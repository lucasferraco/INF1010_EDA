#pragma once

struct Node
{
	int val;
	Node* next;
	Node* prev;
};

class List
{
public:
	//Cria uma lista vazia
	List();

	//Cria uma lista a partir de outra lista
	List(const List& list);

	//Destroi a lista
	~List();

	//Insere um elemento no fim da lista
	void push_back(const int& element);

	//Insere um elemento no inicio da lista
	void push_front(const int& element);

	//Remove o elemento do final da lista
	void pop_back();

	//Remove o elemento do inicio da lista
	void pop_front();

	//Retorna o tamanho da lista
	unsigned int size();

	//Remove a primeira ocorrencia de element
	void remove(const int& element);

	//Imprime os elementos da lista separados por espaco e por fim salta uma linha
	void print();

private:
	Node* first;
	Node* last;
};
