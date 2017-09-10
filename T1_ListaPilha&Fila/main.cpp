//
//  main.cpp
//  EDA_T1
//
//  Created by Lucas Ferraço on 13/03/17.
//  Copyright © 2017 Lucas Ferraço. All rights reserved.
//

#include <iostream>
#include "mod1_lista1.h"

int main(int argc, const char * argv[]) {
    List lista;
    
    lista.push_back(3);
    //lista.push_back(4);
    lista.push_back(2);
    lista.push_back(1);

    lista.print();
    
    lista.print();
    
    return 0;
}
