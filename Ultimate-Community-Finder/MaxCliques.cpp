#include "MaxCliques.h"

#include "iostream"


    //Misc functions

int degeneracy(Graph& g, vector<int> ordering) {
    int minDegree = g.v;

    for(int i=0; i<g.v; i++) {
        //Compute degree with vertices coming later in the ordering only
        int degree = 0;
        for(long unsigned int j=0; j<g.vertices[i].size(); j++) {
            if(g.vertices[i][j] > i)
                degree++;
        }

        if(degree<minDegree) {
            degree = minDegree;
        }
    }

    return minDegree;
}







    //Maximum cliques

vector<vector<int>> maximumCliques(Graph& g) {

    return vector<vector<int>>();
}
