//
//  main.cpp
//  HashTable
//
//  Created by Lucas Ferraço on 27/05/17.
//  Copyright © 2017 Lucas Ferraço. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "mod2_lista6.h"

void countWords( const std::string& inputPath , const std::string& outputPath );

int main() {
	Hash teste(512);
	
	for (int i = 0 ; i<3; i++) {
		std::cout << teste.getCount("sky") << std::endl;
		teste.insert("sky");
	}
	
	std::cout << teste.getCount("sky") << std::endl;
	countWords("/Users/lucasferraco/Desktop/teste.txt", "/Users/lucasferraco/Desktop");
	
    return 0;
}

void countWords( const std::string& inputPath ,
				 const std::string& outputPath ) {
	//Abre o arquivo para leitura
	std::ifstream input;
	input.open( inputPath );
	
	if( input.is_open() ) {
		Hash wordCounter (5);
		std::string word;
		
		// Le palavra por palavra
		while ( input >> word ) {
			auto it = word.begin();
			while( it != word.end() ) {
				if( !isalpha(*it) )
					it = word.erase(it); //A função erase retorna o iterador para o próximo item
				else ++it;
			}
			
			std::transform(word.begin(), word.end(), word.begin(), tolower);
			
			if( !word.empty() )
				wordCounter.insert(word);
		}
		
		//Fecha o arquivo
		//Insere a palavra na tabela hash
		input.close();
		
		//Escreve o resultado em arquivo
		wordCounter.writeCSV( outputPath );
	}
}
