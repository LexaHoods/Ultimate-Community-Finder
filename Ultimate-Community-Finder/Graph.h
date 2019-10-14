#pragma once
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
		void randomGraph();
		void print();

};

#endif
