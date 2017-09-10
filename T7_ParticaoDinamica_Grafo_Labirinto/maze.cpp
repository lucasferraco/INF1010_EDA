#include "maze.h"

#include <fstream>
#include <random>
#include <iostream>

#include "unionfind.h"
#include "graph.h"

using namespace std;


int randomInt( int from, int to ) {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(from, to);
    return distr(generator);
}


void createMaze( int m, int n, vector< bool >& maze ) {
	int totalOfWalls = 2*m*n;
	UnionFind unionfindMaze(m*n);
	vector<int> borders;
	
	// Inicializa o labirinto com todas as paredes existentes
	maze = vector<bool>(totalOfWalls, true);
	
	// Preenche o vetor com as paredes que nao podem ser derrubadas
	int downBorder = totalOfWalls - 1; // Baixo da ultima linha
	int rightBorder = 2*m - 2; // Direita da ultima coluna
	
	while (downBorder > 2*(n-1)*m) {
		borders.push_back(downBorder);
		downBorder -= 2;
	}
	
	while (rightBorder < totalOfWalls - 1 && rightBorder >= 0) {
		borders.push_back(rightBorder);
		rightBorder += 2*m;
	}
	
	while (unionfindMaze.getNumSets() > 1) {
		int randomWall = randomInt(0, totalOfWalls - 1);
		
		// Verifica se a parede e valida
		bool isValidWall = true;
		for (int i = 0; i < borders.size(); i++)
			if (randomWall == borders[i]) isValidWall = false;
		
		if (isValidWall) {
			int firstCell = randomWall/2, secondCell;
			if (randomWall%2 == 0)
				secondCell = firstCell + 1;
			else
				secondCell = firstCell + m;
			
			firstCell = unionfindMaze.find(firstCell);
			secondCell = unionfindMaze.find(secondCell);
			
			if (firstCell != secondCell) {
				unionfindMaze.makeUnion(firstCell, secondCell);
				maze[randomWall] = false;
			}
		}
	}
}


void drawMaze( const vector< bool >& maze, int m, int n ) {
    //Linha de cima
    cout << "+";
    for( int j = 0; j < m; j++ )
        cout << "---+";

    for( int i = 0; i < n; i++ )
    {
        int pos = i*2*m;
        cout << endl << "|";
        for( int j = 0; j < m; j++ )
        {
            cout << "   ";
            cout << (maze[pos] ? "|" : " ");
            pos+=2;
        }
        cout << endl << "+";

        pos=i*2*m+1;
        for( int j = 0; j < m; j++ )
        {
            cout << (maze[pos] ? "---" : "   ") << "+";
            pos+=2;
        }
    }

    cout<< endl;
}


void printMaze( const vector< bool >& maze ) {
    if( !maze.empty() )
    {
        for( size_t i = 0; i < maze.size()-1; i+=2 )
        {
            cout << i/2 << " "
                      << (maze[i+0] ? 1 : 0) << " "
                      << (maze[i+1] ? 1 : 0) << endl;
        }
    }
}


Graph createGraph( const vector<bool>& maze, int m, int n ) {
    int size = m*n;
    Graph mazeGraph(size);

    for( int i = 0; i < n; i++ )
    {
        for( int j = 0; j < m; j++ )
        {
            int cell1 = i*m+j;
            if( !maze[cell1*2] && (cell1+1)%m!=0 )
                mazeGraph.insertEdge(cell1,cell1+1);
            if( !maze[cell1*2+1] && cell1<(size-m) )
                mazeGraph.insertEdge(cell1,cell1+m);
        }
    }
	
	return mazeGraph;
}

// FIX: tirar as impressoes geradas pela bfs
void findStartEnd(const vector<bool>& maze, int m, int n, int& start, int& end) {
	//Cria o grafo que representa o labirinto
	Graph mazeGraph = createGraph(maze, m, n);
	int size = m*n;
	vector<int> layers;
	int biggestPath = -1, furthestLayer = 0;
	
	if (size == 0) {
		start = end = 0;
		return;
	}
	
	for (int i = 0; i < size; i++) {
		// Acha a camada mais distante
		mazeGraph.bfs(i);
		layers = mazeGraph.distances;
		for (int j = 0; j < mazeGraph.distances.size(); j++)
			if (furthestLayer < mazeGraph.distances[j])
				furthestLayer = mazeGraph.distances[j];
		
		// Acha o menor caminho até a camada mais distante
		mazeGraph.djikstra(i);
		for (int j = 0; j < size; j++) {
			if (biggestPath < mazeGraph.distances[j] && layers[j] == furthestLayer) {
				biggestPath = mazeGraph.distances[i];
				start = i;
				end = j;
			}
		}
	}
}

