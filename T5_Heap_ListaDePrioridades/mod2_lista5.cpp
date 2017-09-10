#include "mod2_lista5.h"
#include <iostream>


Heap::Heap()
: _size(0) {
	_size = 0;
}


Heap::Heap(int * values, unsigned int size) {
	_size = 0;
	
	for (int i = 0; i < size; i++) push(values[i]);
}


Heap::Heap(const Heap& other) {
	for (int i = 0; i < other._size; i++)
		_container[i] = other._container[i];
	
	_size = other._size;
}


Heap::~Heap() {
	for (int i = 0; i < _size; i++) _container[i] = 0;
	
	_size = -1;
}


unsigned int Heap::size()
{
	return _size;
}


void Heap::push(int value)
{
	int up = parent(_size);
	_container[_size] = value;
	
	if (_size != 0) heapify(up);
	
	_size++;
}


int Heap::top()
{
	if (_size == 0) return -1;

	return _container[0];
}


void Heap::pop() {
	int aux;
	
	for (int i = 1; i < _size; i++) {
		aux = _container[i];
		_container[i - 1] = aux;
	}
	
	_size--;
}


void Heap::show(const std::string& title) {
	std::cout << title << " ";

	if (_size > 0)
		std::cout << _container[0];
	
	for (unsigned int i = 1; i < _size; i++)
		std::cout << " " << _container[i];

	std::cout << std::endl;
}


int Heap::parent(int i) {
	return (i - 1)/2;
}


int Heap::left(int i) {
	return 2*i + 1;
}


int Heap::right(int i) {
	return 2*i + 2;
}


void Heap::heapify(int i) {
	int l = left(i), r = right(i), min;
	
	if (l <= _size && _container[l] < _container[i]) min = l;
	else min = i;
	
	if (r <= _size && _container[r] < _container[min]) min = r;
	
	if (min != i) {
		int temp = _container[i];
		_container[i] = _container[min];
	 	_container[min] = temp;
		
		heapify(min);
	}
}
