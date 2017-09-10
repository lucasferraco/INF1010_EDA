#include "unionfind.h"


UnionFind::UnionFind(int n)
: parent( std::vector<int>(n, -1) )
, size( std::vector<int>(n, 1) )
, numSets(n) {}


UnionFind::~UnionFind() {
	for (int i = 0; i < parent.size(); i++) {
		parent[i] = -1;
		size[i] = 0;
	}
	
	numSets = 0;
}


int UnionFind::find(int u) {
	if (parent[u] == -1) return u;
	
	if (parent[u] != u) parent[u] = find(parent[u]);
	
	return parent[u];
}


void UnionFind::makeUnion(int u, int v) {
	u = find(u);
	v = find(v);
	
	if (u != v) {
		if (size[u] < size[v]) {
			size[v] += size[u];
			size[u] = 0;
			
			parent[u] = v;
		}
		else {
			size[u] += size[v];
			size[v] = 0;
			
			parent[v] = u;
		}
		
		numSets--;
	}
}


int UnionFind::getNumSets() {
    return numSets;
}
