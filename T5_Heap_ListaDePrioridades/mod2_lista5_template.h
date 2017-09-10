#ifndef MOD2_LISTA5_H
#define MOD2_LISTA5_H

#include <string>
#include <vector>
using namespace std;

template < typename T >
class Heap /* Min-Heap */
{
public:
	//Construtor vazio
	Heap();
	
	//Constroi o heap a partir de um vetor de elementos
	Heap(const std::vector<T>& values);
	
	//Constroi o heap a partir de outro heap
	Heap(const Heap& other);
	
	//Destroi o heap
	~Heap();
	
	//Retorna o numero de elementos atualmente no heap
	unsigned int size();
	
	//Insere um novo elemento
	void push(T value);
	
	//Retorna o elemento do topo
	T top();
	
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
	
	//Garante que o filho nao e menor que seu pai
	void heapify_up(int i);
	
	//Garante que o pai nao e maior que seus filhos
	void heapify_down(int i);
	
private:
	//Contem os elementos do heap
	std::vector<T> _container;
};

template < typename T >
Heap<T>::Heap() {}

template < typename T >
Heap<T>::Heap(const vector<T>& values)
:_container(values) {
	int size = (int) _container.size();
	
	for(int i = 0; i < size; i++) heapify_up(i);
}

template < typename T >
Heap<T>::Heap(const Heap& other) {
	for (int i = 0; i < other._container.size(); i++)
		_container.push_back(other._container[i]);
}

template < typename T >
Heap<T>::~Heap() {
	_container.clear();
}

template < typename T >
unsigned int Heap<T>::size()
{
	return (unsigned int) _container.size();
}

template < typename T >
void Heap<T>::push(T value) {
	_container.push_back(value);
	
	if (_container.size() > 0) {
		heapify_up((int) _container.size() - 1);
	}
}

template < typename T >
T Heap<T>::top()
{
	if (_container.size() == 0) return -1;
	
	return _container.front();
}

template < typename T >
void Heap<T>::pop() {
	if(_container.size() == 0) return;
	
	_container[0] = _container.back();
	_container.pop_back();
	
	heapify_down(0);
}

template < typename T >
void Heap<T>::show(const string& title) {
	cout << title << " ";
	
	if (_container.size() > 0)
		cout << _container[0];
	
	for (unsigned int i = 1; i < _container.size(); i++)
		cout << " " << _container[i];
	
	cout << endl;
}

template < typename T >
int Heap<T>::parent(int i) {
	return (i - 1)/2;
}

template < typename T >
int Heap<T>::left(int i) {
	return 2*i + 1;
}

template < typename T >
int Heap<T>::right(int i) {
	return 2*i + 2;
}

template < typename T >
void Heap<T>::heapify_up(int i) {
	int p = parent(i);
	
	if (_container[p] > _container[i]) {
		T temp = _container[i];
		_container[i] = _container[p];
		_container[p] = temp;
		
		heapify_up(p);
	}
}

template < typename T >
void Heap<T>::heapify_down(int i) {
	int l = left(i), r = right(i), min = i;
	
	if (l <= _container.size() && _container[l] < _container[min]) min = l;
	if (r <= _container.size() && _container[r] < _container[min]) min = r;
	
	if (min != i) {
		T temp = _container[i];
		_container[i] = _container[min];
		_container[min] = temp;
		
		heapify_down(min);
	}
}

#endif
