#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

class Hash
{

public:

    /**
     * Construtor. Aloca a tabela com
     * tamanho tableSize
     */
    Hash( int tableSize );

    /**
     * Destrutor. Desaloca a tabela.
     */
    ~Hash();

    /**
      * Insere uma palavra na tabela. Caso ela
      * ja tenha sido inserida, apenas incrementa
      * o numero de ocorrencias.
      */
    void insert(const std::string& word);

    /**
     * Obtem o numero de ocorrencias de uma
     * determinada palavra
     */
    int getCount(const std::string& word);

    /**
     * Escreve todas as palavras e o seu respectivo
     * numero de ocorrencias, no formato CSV (Comma-
     * separated values):
     * palavra,numero_ocorrencias
     *
     * Por exemplo:
     * casa,2
     * bola,1
     * cachorro,1
     *
     * Retorna verdadeiro caso tenha salvo o arquivo
     * com sucesso.
     */
    bool writeCSV(const std::string& filePath);

    /**
     * Funcao hash. Dada uma palavra, retorna em qual
     * posicao da tabela ela deve ser armazenada
     */
    int hash(const std::string& word);

private:

    // Tabela armazenada como um C-array de pairs.
    // Cada pair eh formado por uma string (palavra)
    // e um inteiro (numero de ocorrencias)
    std::pair< std::string, int >* _table;
	
	// Tamanho da tabela
	int _size;

};

#endif // HASHTABLE_H
