//
//  main.cpp
//  T5
//
//  Created by Lucas Ferraço on 11/05/17.
//  Copyright © 2017 Lucas Ferraço. All rights reserved.
//

#include <iostream>
#include "mod2_lista5.h"

int main() {
	Heap a;
	
	a.push(3);
	a.push(2);
	a.push(1);
	a.push(100);
	a.push(25);
	a.push(17);
	a.push(19);
	a.push(7);
	a.push(36);
	
	a.show("Heap a: ");
	
	std::cout << "Top: " << a.top() << std::endl;
	
	std::cout << "Size: " << a.size() << std::endl;
	
	a.pop();
	a.show("Pop: ");
	
	int values[] = {3, 2, 1, 100, 25, 17, 19, 7, 36};
	Heap b(values, 9);
	b.show("Heap b: ");
	
	Heap c(b);
	c.show("Heap c:");
	
    return 0;
}
