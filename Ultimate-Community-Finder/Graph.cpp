#include "Graph.h"
#include <iostream>
#include<time.h>
using namespace std;


	//Basic functions

int Graph::degree(int v) {
	return vertices[v].size();
}



vector<int> Graph::neighbours(int v) {
	return vertices[v];
}



	//Random generation functions

void Graph::random(int nVertices) {
	v = nVertices;

	//Generate vertices vector
	for(int i=0; i<v; i++) {
		vertices.push_back(vector<int>());
	}


	float p = 0;
	srand(time(NULL));
	for (int i = 0; i < v; i++) {
		for (int j = i + 1; j < v; j++) {
			p = (float)rand() / RAND_MAX;
			printf("value of p : %f \n", p);
			if (p >= 0.2) {
				vertices[i].push_back(j);
				vertices[j].push_back(i);
			}
		}
	}
}



void Graph::barabasiAlbert(int nVertices, int m, int m0) {
	//1) Initialization
	v = nVertices;

	//Generate vertices vector
	for(int i=0; i<v; i++) {
		vertices.push_back(vector<int>());
	}


	int degSum = 0;
	int degMarkedVertices = 0;
	vector<int>degVector;
	vector<int>markedVertices;
	int random;
	srand(time(NULL));


	//2) Clique creation
	for (int i = 0; i < m0; i++) {
		for (int j = i + 1; j < m0; j++) {
			vertices[i].push_back(j);
			vertices[j].push_back(i);
		}
		degVector.push_back(m0 - 1);
	}
	degSum = m0 * (m0 - 1);


	//3) Add edges
	//Consider new vertex v
	for (int i = m0; i < v; i++) {

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

			vertices[i].push_back(k);
			vertices[k].push_back(i);

		}

		//Adding new vertex and updating degSum with edges' other hand
		degVector.push_back(m);
		degSum += m;
	}
}



	//Testing functions

void Graph::print() {
	for (long unsigned int i = 0; i < vertices.size(); i++) {
		cout << i << ":";
		for (long unsigned int j = 0; j < vertices[i].size(); j++) {
			cout << " " << vertices[i][j];
		}
		cout << endl;
	}
}
