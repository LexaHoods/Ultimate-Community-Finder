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
	printf("Number of edges : %ld \n", edgeList.size());

	for (long unsigned int i = 0; i < edgeList.size(); i++) {
		cout << "(" << edgeList[i].vertex1 << ";" << edgeList[i].vertex2 << ")" << endl;
	}
}



void Graph::barabasiAlbert(int V, int m, int m0) {
	//1) Initialization
	v = V;
	int degSum = 0;
	int degMarkedVertices = 0;
	vector<int>degVector;
	vector<int>markedVertices;
	int random;
	srand(time(NULL));



	//2) Clique creation
	for (int i = 0; i < m0; i++) {
		for (int j = i + 1; j < m0; j++) {
			Edge edge;
			edge.vertex1 = i;
			edge.vertex2 = j;
			edgeList.push_back(edge);
		}
		degVector.push_back(m0 - 1);
	}
	degSum = m0 * (m0 - 1);


	//3) Add edges
	//Consider new vertex v
	for (int i = m0; i < V; i++) {

		//Reset marked vertices
		markedVertices.clear();
		degMarkedVertices = 0;


		//Consider new edge e starting from v
		for (int j = 0; j < m; j++) {

			random = rand() % (degSum - degMarkedVertices);
			int temp = 0;
			int k = -1;

			//Looking for new destination vertex
			do{
				k++;
				bool conflict = false;

				//Checking conflicts with already marked vertices
				for (long unsigned int l = 0; l < markedVertices.size(); l++) {
					if(markedVertices[l] == k)
						conflict = true;
				}

				if(!conflict)
					temp += degVector[k];

			}while(temp < random);

			//At this point, vertex k found
			degVector[k]++;
			degSum++;

			markedVertices.push_back(k);
			degMarkedVertices += degVector[k];

			Edge edge;
			edge.vertex1 = i;
			edge.vertex2 = k;
			edgeList.push_back(edge);

		}

		//Adding new vertex and updating degSum with edges' other hand
		degVector.push_back(m);
		degSum += m;
	}
}



int Graph::degree(int x) {
	int count = 0;
	for (long unsigned int k = 0; k < edgeList.size(); k++) {
		if (edgeList[k].vertex1 == x || edgeList[k].vertex2 == x) {
			count = count + 1;
		}
	}
	return count;
}



vector<int> Graph::neighbours(int vertex) {

	vector<int> neighbours;

	if(vertex >= v) {
		return neighbours;
	}

	for(long unsigned int i=0; i<edgeList.size(); i++) {
		if(edgeList[i].vertex1 == vertex) {
			neighbours.push_back(edgeList[i].vertex2);
		}

		if(edgeList[i].vertex2 == vertex) {
			neighbours.push_back(edgeList[i].vertex1);
		}
	}

	return neighbours;
}
