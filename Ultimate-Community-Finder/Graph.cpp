#include "Graph.h"
#include <iostream>
#include<time.h>
using namespace std;

void Graph::randomGraph(int v) {


	float p = 0; // random
	srand(time(NULL));
	for (int i = 0; i < v; i++) {
		for (int j = i + 1; j < v; j++) {
			p = (float)rand() / RAND_MAX;
			printf("value of p : %f \n", p);
			if (p >= 0.2) {
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

void Graph::barabasiAlbert(int v, int m, int m0) {
	int degSum = 0;
	int degMarkedVertices = 0;
	vector<int>degVector;
	vector<int>markedVertices;
	int random = 0;
	srand(time(NULL));
	//A clique : 
	for (int i = 0; i < m0; i++) {
		for (int j = i + 1; j < m0; j++) {
			Edge edge;
			edge.vertex1 = i;
			edge.vertex2 = j;
			edgeList.push_back(edge);
		}
		degVector.push_back(m0 - 1);
	}
	//initialize degVector 
	for (int i = m0; i < v; i++) {
		degVector.push_back(0);
	}
	degSum = m0 * (m0 - 1);



	//BarabasiAlbert : 		
	for (int i = m0; i < v; i++) {

		markedVertices.clear();
		degMarkedVertices = 0;
		for (int j = 0; j < m; j++) {

			random = rand() % (degSum - degMarkedVertices) + 1;
			int temp = 0;
			int k = -1;

			while (temp < random) {
				k++;
				for (int l = 0; l < markedVertices.size(); l++) {
					if (markedVertices[l] == k)
						continue;
				}
				temp = temp + degVector[k];
			}

			Edge edge2;
			edge2.vertex1 = i;
			edge2.vertex2 = k;
			edgeList.push_back(edge2);

			degVector[i]++;
			degVector[k]++;
			degSum += 2;
			degMarkedVertices += degVector[k];
		}
	}


}

int Graph::degree(int x) {
	//degree of a vertex
	int count = 0;
	for (int k = 0; k < edgeList.size(); k++) {
		if (edgeList[k].vertex1 == x || edgeList[k].vertex2 == x) {
			count = count + 1;
		}
	}
	printf("degree of %d : %d \n", x, count);
	return count;
}