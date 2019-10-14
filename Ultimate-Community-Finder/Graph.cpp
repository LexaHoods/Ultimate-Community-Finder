#include "Graph.h"
#include <iostream>
#include<time.h>
using namespace std;

void Graph::randomGraph() {
	cout << "How much of vertex ? \n";
	cin >>v;

	float p = 0; // random
	srand(time(NULL));
	for (int i = 1; i <= v; i++) {
		for (int j = i+1 ; j <= v; j++) {
			p = (float)rand()/RAND_MAX;
			printf("value of p : %f \n", p);
			if (p >=0.2) {
				Edge edge;
				edge.vertex1 = i;
				edge.vertex2 = j; 
				edgeList.push_back(edge);
			}
		}
	}

}

void Graph::print() {
	printf("number of edges : %d \n ", edgeList.size());

	for (int i = 0; i < edgeList.size(); i++) {
		printf("vertex1 of edge %d = %d \n", i, edgeList[i].vertex1);
		printf("vertex2 of edge %d = %d \n", i, edgeList[i].vertex2);
	}
	
}