// Ultimate-Community-Finder.cpp
// Aurélien Delval & Axel Houdayer IATIC4

#include <iostream>
#include "Graph.h"
#include "BronKerbosch.h"
#include "MaxCliques.h"
using namespace std;

int main()
{

	cout << "***** Ultimate Community Finder ! ****\n";

	Graph graph;

	graph.barabasiAlbert(19, 3, 4);
	graph.print(); //debug


	vector<vector<int>> cliques = maxCliques1(graph);


	cout << "N cliques = " << cliques.size() << endl;
	for(unsigned long int i=0; i<cliques.size(); i++) {
		cout << "Clique " << i << ":";
		for(unsigned long int j=0; j<cliques[i].size(); j++) {
			cout << " " << cliques[i][j];
		}
		cout << endl;
	}
}
