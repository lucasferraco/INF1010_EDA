#include "mod1_lista1.h"
#include <iostream>

List::List()
{
    first = NULL;
    last = NULL;
}


List::List(const List& list)
{
    this->first = list.first;
    this->last = list.last;
}


List::~List()
{
    Node * p;
    Node * pNext;
    p = this->first;
    
    while (p != NULL) {
        pNext = p->next;
        free(p);
        p = pNext;
    }
    
    this->first = NULL;
    this->last = NULL;
}

void List::push_back(const int& element)
{
    Node * newNode = NULL;
    newNode = (Node *) malloc(sizeof(Node));
    newNode->val = element;
    newNode->prev = this->last;
    newNode->next = NULL;
    
    if (this->first == NULL) {
        this->first = newNode;
    }
    else {
        this->last->next = newNode;
    }
    
    this->last = newNode;
}


void List::push_front(const int& element)
{
    Node * newNode = NULL;
    newNode = (Node *) malloc(sizeof(Node));
    newNode->val = element;
    newNode->prev = NULL;
    newNode->next = this->first;
    
    if (this->first == NULL) {
        this->last = newNode;
    }
    else {
        this->first->prev = newNode;
    }
    
    this->first = newNode;
}


void List::pop_back()
{
    Node * aux;
    aux = this->last;
    
    this->last = this->last->prev;
    this->last->next = NULL;
    
    free(aux);
}


void List::pop_front()
{
    Node * aux;
    aux = this->first;
    
    this->first = this->first->next;
    this->first->prev = NULL;
    
    free(aux);
}


unsigned int List::size()
{
    Node * p;
    unsigned int counter = 0;
    p = this->first;
    
    while (p != NULL) {
        counter++;
        p = p->next;
    }
    
    return counter;
}


void List::remove(const int& element)
{
    Node * p;
    p = this->first;
    
    while (p != NULL) {
        if (p->val == element) {
            Node * pPrev = p->prev;
            Node * pNext = p->next;
            
            if (pNext != NULL) {
                pNext->prev = p->prev;
            }
            else {
                this->last = p->prev;
            }
            
            if (pPrev != NULL) {
                pPrev->next = p->next;
            }
            else {
                this->first = p->next;
            }
            
            free(p);
            p = NULL;
        }
        else {
            p = p->next;
        }
    }
}


void List::print()
{
    Node * p;
    p = this->first;
    
    std::cout << "Elementos da Lista: ";
    while (p != NULL) {
        std::cout << p->val;
        std::cout << " ";
        p = p->next;
    }
    std::cout << "\n";
}
