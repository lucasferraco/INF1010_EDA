#include "mod2_lista6.h"

#include <fstream>
#include <utility>

using namespace std;

Hash::Hash(int tableSize)
: _table( new pair <string, int> [tableSize] )
, _size(tableSize) {
	if (tableSize < 0) tableSize = 0;
	
	// Inicializa cada posicao com <"",0>
	for( int i = 0; i < tableSize; ++i )
		_table[i] = make_pair("",0);
}


Hash::~Hash() {
    delete[] _table;
}


void Hash::insert(const string& word) {
	int index = hash(word);
	
	while (_table[index].first != "" && _table[index].first != word)
		index++;
	
	if (_table[index].first == word) {
		_table[index].second++;
	}
	else {
		_table[index].first = word;
		_table[index].second = 1;
	}
}


int Hash::getCount(const string& word) {
	int index = hash(word);
	
	while (_table[index].first != word && index <= _size)
		index++;
	
	if (index > _size) return 0;
	
    return _table[index].second;
}


bool Hash::writeCSV(const string& filePath) {
	string fileName = filePath;
	if (filePath.find(".csv") == string::npos)
		fileName += "/Table_with_words_count.csv";
	ofstream output(fileName);
	string word;
	
	if (output.is_open()) {
		
		for (int i = 0; i < _size; i++) {
			output << _table[i].first << ",";
			output << _table[i].second << std::endl;
		}
		
		output.close();
	}
	return false;
}


int Hash::hash(const string& word) {
	int hash = 0;
	
	for (int i = 0; i < word.length(); i++)
		hash = 13*hash + word[i];
	
	return abs(hash % _size);
}
