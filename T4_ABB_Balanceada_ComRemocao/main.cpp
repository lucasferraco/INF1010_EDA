//
//  main.cpp
//  T3
//
//  Created by Lucas Ferraço on 11/04/17.
//  Copyright © 2017 Lucas Ferraço. All rights reserved.
//

#include <iostream>
#include "mod1_lista3.h"

int main(int argc, const char * argv[]) {
    
    Avl a;
    a.insert(5);
    a.insert(8);
    a.insert(10);
    a.insert(4);
    a.insert(3);
    a.insert(6);
    a.insert(12);
    a.insert(11);
    a.show("Arvore A:");
    std::cout << "Altura de A: " << a.height() << std::endl;
    Avl b(a); a.show("Arvore B:");
    
    a.first();
    std::cout << "\nCrescente: " << a.value();
    while (a.next())
    {
        std::cout << " " << a.value();
    }
    std::cout << std::endl;
    
    a.last();
    std::cout << "Decrescente: " << a.value();
    while (a.prev())
    {
        std::cout << " " << a.value();
    }
    std::cout << std::endl;
	
	a.remove(5);
    a.show("\nArvore A (remove):");
	
    return 0;
}
