#include "BronKerbosch.h"
#include <iostream>
#include <map>

using namespace std;


    //Misc functions

vector<int> inter(vector<int>& A, vector<int>& B) {
    vector<int> inter;

    //Iterates over all elements of A
    for(long unsigned int i=0; i<A.size(); i++) {
        bool found = false;

        //Iterates over B to find the same element
        long unsigned int j = 0;
        while(!found) {
            if(A[i] == B[j]) {
                found = true;
                break;
            }

            j++;
            if(j == B.size()) {
                break;
            }
        }

        //If it has been found, add to intersection
        if(found) {
            inter.push_back(A[i]);
        }
    }

    return inter;
}



vector<int> uni(Graph& g, vector<int>& A, vector<int>& B) {
    vector<bool> marked (g.v, false);   //Mark
    vector<int> uni;

    //Iterate A
    for(unsigned long int i=0; i<A.size(); i++) {
        if(!marked[A[i]]) {
            marked[A[i]] = true;
            uni.push_back(A[i]);
        }
    }

    //Iterate B
    for(unsigned long int i=0; i<B.size(); i++) {
        if(!marked[B[i]]) {
            marked[B[i]] = true;    //Just in case there is redundancy in B
            uni.push_back(B[i]);
        }
    }

    return uni;

}



vector<int> difference(vector<int>& A, vector<int>& B) {
    vector<int> excl;
    bool found;

    for(long unsigned int i=0; i<A.size(); i++) {
        found = false;

        long unsigned int j = 0;
        while(!found) {
            if(A[i] == B[j]) {
                found = true;
                break;
            }

            j++;
            if(j == B.size()) {
                break;
            }
        }

        if(!found) {
            excl.push_back(A[i]);
        }
    }

    return excl;
}



bool isIn(vector<int>& A, int x) {
    for(long unsigned int i=0; i<A.size(); i++) {
        if(A[i] == x) {
            return true;
        }
    }

    return false;
}



    //Classic Bron-Kerbosch

void bronKerboschRecursive(Graph& g, vector<vector<int>>& cliques, vector<int> R, vector<int> P, vector<int> X) {
    if(P.size() == 0 && X.size() == 0) {
        cliques.push_back(R);
        return;
    }


    while(P.size()) {
        std::vector<int> Rv = R;
        Rv.push_back(P[0]);

        vector<int> neighbours = g.neighbours(P[0]);

        bronKerboschRecursive(g, cliques, Rv, inter(P,  neighbours), inter(X, neighbours ));

        X.push_back(P[0]);
        P.erase(P.begin());
    }
}



vector<vector<int>> bronKerbosch(Graph& g) {
    vector<int> P;
    vector<int> R;
    vector<int> X;

    //Fill P with all vertices of G
    for(int i=0; i<g.v; i++) {
        //Necessary to protect against segfaults with non connected vertices
        if(g.degree(i) > 0) {
            P.push_back(i);
        }
    }

    vector<vector<int>> cliques;

    bronKerboschRecursive(g, cliques, R, P, X);

    return cliques;
}



    //Bron-Kerbosch pivoting

int tomitaPivot(Graph& g, vector<int>& P, vector<int>& X) {

    vector<int> PcupX = uni(g, P, X);

    vector<int> neighbours = g.neighbours(PcupX[0]);
    int maxGamma = inter(P, neighbours).size();
    int maxIndex = 0;

    for(long unsigned int i=1; i<PcupX.size(); i++) {
        neighbours = g.neighbours(PcupX[i]);
        int gamma = inter(P, neighbours).size();

        if(gamma > maxGamma) {
            maxGamma = gamma;
            maxIndex = i;
        }
    }

    return PcupX[maxIndex];
}



void bronKerboschPivoting(Graph& g, vector<vector<int>>& cliques, vector<int> R, vector<int> P, vector<int> X) {

    if(P.size() == 0 && X.size() == 0) {
        cliques.push_back(R);
        return;
    }

    int pivot = tomitaPivot(g, P, X);
    vector<int> pivotGamma = g.neighbours(pivot);
    vector<int> PexGamma = difference(P, pivotGamma);

    while(PexGamma.size()) {
        vector<int> Rv = R;
        Rv.push_back(PexGamma[0]);

        vector<int> neighbours = g.neighbours(PexGamma[0]);

        bronKerboschPivoting(g, cliques, Rv, inter(P, neighbours), inter(X, neighbours ));

        X.push_back(PexGamma[0]);
        PexGamma.erase(PexGamma.begin());

    }

}



    //Bron-Kerbosch vertex ordering

vector<int> ordering(Graph g) {
    //Initializations
    vector<int> L;

    int i=0;
    while(i<g.v) {

        //Look for min degree
        int minIndex = 0;
        int minDegree = g.v;
        for(int j=0; j<g.v; j++) {
            if(g.degree(j) < minDegree && !isIn(L, j)) {
                minIndex = j;
                minDegree = g.degree(j);
            }
        }

        //Remove vertex (we just remove edges to keep the same vertices indices)
        for(int j=0; j<g.v; j++) {
            if(j == minDegree) {
                //Remove all neighbours
                g.vertices[j].clear();
            }
            else {
                //Look for vertex to remove
                for(long unsigned int k=0; k<g.vertices[j].size(); k++) {
                    if(g.vertices[j][k] == minIndex) {
                        g.vertices[j].erase(g.vertices[j].begin() + k);
                        break; //Assumes there is no redundancy
                    }
                }
            }
        }

        L.push_back(minIndex);
        i++;

    }
    return L;
}



vector<vector<int>> bronKerboschOrdering(Graph& g) {

    //Compute ordering
    vector<int> order = ordering(g);
    vector<vector<int>> cliques;

    for(long unsigned int i=0; i<order.size(); i++) {
        vector<int> R = { order[i] };


        vector<int> neighbours = g.neighbours(order[i]);

        vector<int> orderPlus;
        for(long unsigned int j=i+1; j<order.size(); j++) {
            orderPlus.push_back(order[j]);
        }
        vector<int> P = inter(orderPlus, neighbours);

        vector<int> orderMinus;
        for(long unsigned int j=0; j<i; j++) {
            orderMinus.push_back(order[j]);
        }
        vector<int> X = inter(orderMinus, neighbours);


        bronKerboschPivoting(g, cliques, R, inter(P, neighbours), inter(X, neighbours));



    }

    return cliques;
}
