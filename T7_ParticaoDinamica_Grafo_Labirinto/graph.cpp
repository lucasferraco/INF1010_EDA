#include <iostream>
#include <queue>
#include "graph.h"
#include "unionfind.h"

using namespace std;


Graph::Graph( int N )
: G(vector< vector<Edge> >(N)) {
	distances = * new vector<int>(N);
}


void Graph::insertEdge( int from, int to, int weight, bool undirected ) {
    G[from].push_back(Edge({to, weight}));

    if( undirected )
    {
        G[to].push_back(Edge({from, weight}));
    }
}


void Graph::print() {
    for( unsigned int u = 0; u < G.size(); u++ )
    {
        cout << u << ": ";

        if( !G[u].empty() )
        {
            cout << G[u][0].v << '(' << G[u][0].w << ')';
        }

        for( unsigned int e = 1; e < G[u].size(); e++ )
        {
            cout << ", " << G[u][e].v << '(' << G[u][e].w << ')';
        }

        cout << endl;
    }
}


void Graph::bfs( int s ) {
	vector<bool> visited(G.size(), false);
	vector<int> frontier, next;
	int distance = 0;
	
	for (int i = 0; i < G.size(); i++)
		distances[i] = INT_MAX;
	
	visited[s] = true;
	cout << s << " ";
	frontier.push_back(s);
	distances[s] = distance;
	distance++;
	
	while (!frontier.empty()) {
		next.clear();
		
		for (int i = 0; i < frontier.size(); i++) {
			vector<Edge> adj = G[frontier[i]];
			for (int j = 0; j < adj.size(); j++) {
				int v = adj[j].v;
				
				if (!visited[v]) {
					distances[v] = distance;
					next.push_back(v);
					visited[v] = true;
					cout << v << " ";
				}
			}
		}
		
		frontier = next;
		distance++;
	}
	
	cout << endl;
}


void Graph::dfs(int s) {
	vector<bool> visited(G.size(), false);
	
	dfsRec(s, visited);
	cout << endl;
}


void Graph::dfsRec(int s, vector<bool> &visited) {
	visited[s] = true;
	cout << s << ' ';
	
	vector<Edge> adj = G[s];
	for (int i = 0; i < adj.size(); i++) {
		int v = adj[i].v;
		
		if (!visited[v]) dfsRec(v, visited);
	}
}


void Graph::djikstra( int s ) {
	class Compare {
	public:
		bool operator() (pair<int, int> d1, pair<int, int> d2) {
			return d1.second > d2.second;
		}
	};
	
	priority_queue< pair<int, int>, vector <pair<int, int>> , Compare > minHeapDistances;
 
	for (int i = 0; i < G.size(); i++)
		distances[i] = INT_MAX;
 
	minHeapDistances.push(make_pair(s, 0));
	distances[s] = 0;
 
	while (!minHeapDistances.empty()) {
		int actual = minHeapDistances.top().first;
		minHeapDistances.pop();
		vector<Edge> adj = G[actual];
		
		vector<Edge>::iterator i;
		for (i = adj.begin(); i != adj.end(); ++i) {
			int v = (*i).v;
			int weight = (*i).w;
			
			if (distances[v] > distances[actual] + weight) {
				distances[v] = distances[actual] + weight;
				minHeapDistances.push(make_pair(v, distances[v]));
			}
		}
	}
}


Graph Graph::kruskal() {
	class Compare {
	public:
		bool operator() (tuple<int, int, int> e1,
						 tuple<int, int, int> e2) {
			return get<2>(e1) > get<2>(e2);
		}
	};
	
	UnionFind forest(int(G.size()));
	vector<tuple<int, int, int>> minimalEdges;
	priority_queue< tuple<int, int, int>,
					vector<tuple<int, int, int>> ,
					Compare > minHeapEdges;
	
	for (int i = 0; i < G.size(); i++)
		for (int j = 0; j < G[i].size(); j++)
			minHeapEdges.push(make_tuple(i, G[i][j].v, G[i][j].w));
	
	while (forest.getNumSets() > 1 && !minHeapEdges.empty()) {
		int v1 = get<0>(minHeapEdges.top());
		int v2 = get<1>(minHeapEdges.top());
		int w = get<2>(minHeapEdges.top());
		minHeapEdges.pop();
		
		if (forest.find(v1) != forest.find(v2)) {
			forest.makeUnion(v1, v2);
			minimalEdges.push_back(make_tuple(v1, v2, w));
		}
	}
	
	Graph result(int(minimalEdges.size()) + 1);
	
	for (int i = 0 ; i < minimalEdges.size(); i++)
		result.insertEdge(get<0>(minimalEdges[i]),
						  get<1>(minimalEdges[i]),
						  get<2>(minimalEdges[i]));
	
	return result;
}


bool Graph::isBicolored() {
	
	for (int i = 0; i < G.size(); i++)
		if (!isBicoloredAux(i)) return false;
	
	return true;
}


bool Graph::isBicoloredAux(int s) {
	queue<int> allV;
	vector<Color> layers (G.size(), GRAY);
	
	allV.push(s);
	layers[s] = WHITE;
	
	while (!allV.empty()) {
		int actual = allV.front();
		allV.pop();
		vector<Edge> adj = G[actual];
		
		for (int i = 0; i < adj.size(); i++) {
			int v = adj[i].v;
			
			if (layers[v] == GRAY) {
				if (layers[actual] == WHITE) layers[v] = BLACK;
				else layers[v] = WHITE;
				
				allV.push(v);
			}
			else if (layers[v] == layers[actual]) {
				return false;
			}
		}
	}
	
	return true;
}

