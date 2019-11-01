// Ultimate-Community-Finder.cpp
// Aurélien Delval & Axel Houdayer IATIC4

#include <iostream>
#include "Edge.h"
#include "Graph.h"
#include "BronKerbosch.h"
using namespace std;

int main()
{

	cout << "***** Ultimate Community Finder ! ****\n";

	Graph graph;

	graph.barabasiAlbert(7, 2, 3);
	graph.print(); //debug


	vector<vector<int>> cliques = bronKerboschOrdering(graph);


	cout << "N cliques = " << cliques.size() << endl;
	for(unsigned long int i=0; i<cliques.size(); i++) {
		cout << "Clique " << i <<endl;
		for(unsigned long int j=0; j<cliques[i].size(); j++) {
			cout << "	" << cliques[i][j] <<endl;
		}
	}
}
