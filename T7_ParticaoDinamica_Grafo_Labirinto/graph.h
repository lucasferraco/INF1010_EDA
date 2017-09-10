#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
public:
    //Construtor. N = numero de vertices.
    Graph( int N );

    //Insere uma aresta no grafo, do no 'from' ao no 'to', com peso 'weight'.
    //Caso undirected esteja marcado como true, insere a aresta tambem no sentido to->from
    void insertEdge( int from, int to, int weight = 1, bool undirected = true );

    //Imprime os vertices e seus vizinhos
    void print();

    //Imprime os nos do grafo na ordem de uma busca em largura
    void bfs(int s);

    //Imprime os nos do grafo na ordem de uma busca em profundidade
    void dfs(int s);

    //Retorna a arvore geradora minima do grafo
    Graph kruskal();

    //Calcula a menor distancia de s ate cada vertice
    void djikstra(int s);

    //Verifica se o grafo e bicolorido/bipartido
    bool isBicolored();

    //Menor distancia de cada no ate um vertice especifico
    std::vector<int> distances;
	
private:
	/* Funcoes auxiliares */
	
	//Funcao recursiva para busca em profundidade
	void dfsRec(int s, std::vector<bool> &visited);
	
	//Funcao recursiva para verificar se o grafo e bicolorido/bipartido
	bool isBicoloredAux(int s);

private:
    struct Edge
    {
        int v; //Vertice destino
        int w; //Peso da aresta
    };

	enum Color : int
    {
        WHITE,
        GRAY,
        BLACK
    };

    //Lista de adjacencias
    std::vector< std::vector< Edge > > G;
};

#endif // GRAPH_H
