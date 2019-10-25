// Ultimate-Community-Finder.cpp 
// Aurélien Delval & Axel Houdayer IATIC4  

#include <iostream>
#include "Edge.h"
#include "Graph.h"
using namespace std;

int main()
{

	cout << "***** Ultimate Community Finder ! ****\n";

	Graph graph;

	graph.barabasiAlbert(7, 2, 3);
	graph.print(); //debug

}


