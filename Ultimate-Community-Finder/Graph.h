#ifndef GRAPH
#define GRAPH
#include <vector>

using namespace std;


class Graph {
public:
	int v = 0;	//Number of vertices
	vector<vector<int>> vertices;

	int degree(int v);
	vector<int> neighbours(int v);

	void random(int nVertices);
	void barabasiAlbert(int nVertices, int m, int m0);

	//For testing purpose only
	void print();
};

#endif
