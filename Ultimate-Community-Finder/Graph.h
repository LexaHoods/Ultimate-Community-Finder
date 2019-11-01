#ifndef GRAPH
#define GRAPH
#include <vector>
#include "Edge.h"
using namespace std;
class Graph
{
public:
	int v = 0; //fixed number vertex
	vector<Edge> edgeList;

	void randomGraph(int v);
	void print();
	void barabasiAlbert(int v, int m, int m0);
	int degree(int x);
	vector<int> neighbours(int vertex);
};

#endif
