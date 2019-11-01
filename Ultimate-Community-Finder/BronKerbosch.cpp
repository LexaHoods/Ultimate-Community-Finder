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



vector<int> exclusion(vector<int>& A, vector<int>& B) {
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
        P.push_back(i);
    }

    vector<vector<int>> cliques;

    bronKerboschRecursive(g, cliques, R, P, X);

    return cliques;
}



    //Bron-Kerbosch pivoting

int tomitaPivot(Graph& g, vector<int>& P, vector<int>& X) {


    vector<int> PcupX = uni(g, P, X);

        //Build subgraph P
    Graph subgraph = g;
    subgraph.v = (int) P.size();
    for(long unsigned int i = 0; i<subgraph.edgeList.size(); i++) {
        if(!isIn(P, subgraph.edgeList[i].vertex1) || !isIn(P, subgraph.edgeList[i].vertex2)) {
            subgraph.edgeList.erase(subgraph.edgeList.begin() + i);
            i--;
        }
    }

        //Look for vertex v with max gamma(v) in P
    long unsigned int maxIndex = 0;
    int maxGamma = subgraph.neighbours(PcupX[0]).size();


    for(long unsigned int i=1; i<PcupX.size(); i++) {
        int gamma = subgraph.neighbours(PcupX[i]).size();

        if(gamma>maxGamma) {
            maxGamma = gamma;
            maxIndex = i;
        }
    }

    return PcupX[maxIndex];
}



void bronKerboschPivoting(Graph& g, vector<vector<int>>& cliques, vector<int> R, vector<int> P, vector<int> X, int degree) {

    if(P.size() == 0 && X.size() == 0) {
        cliques.push_back(R);
        return;
    }

    int pivot = tomitaPivot(g, P, X);
    vector<int> pivotGamma = g.neighbours(pivot);
    vector<int> PexGamma = exclusion(P, pivotGamma);

    while(PexGamma.size()) {
        std::vector<int> Rv = R;
        Rv.push_back(PexGamma[0]);

        vector<int> neighbours = g.neighbours(PexGamma[0]);

        bronKerboschPivoting(g, cliques, Rv, inter(P,  neighbours), inter(X, neighbours ), degree+1);

        X.push_back(PexGamma[0]);
        PexGamma.erase(PexGamma.begin());
    }
}



    //Bron-Kerbosch vertex ordering

vector<int> ordering(Graph g) {
    //Initializations
    vector<int> L;
    vector<int> degrees;
    int originalV = g.v;

    //Compute degrees of all vertices
    for(int i=0; i<g.v; i++) {
        degrees.push_back(g.degree(i));
    }

    while(g.v > 0) {
        //Look for min degree
        int minIndex = 0;
        int minDegree = degrees[0];

        for(long unsigned int i=0; i<degrees.size(); i++) {
            if(degrees[i] < minDegree) {
                minDegree = degrees[i];
                minIndex = i;
            }
        }

        //Remove node from G
        g.v--;
        for(long unsigned int i=0; i<g.edgeList.size(); i++) {
            if(g.edgeList[i].vertex1 == minIndex || g.edgeList[i].vertex1 == minIndex) {
                //Delete edge and update degrees array
                if(g.edgeList[i].vertex1 != minIndex) {
                    degrees[g.edgeList[i].vertex1]--;
                }
                else if(g.edgeList[i].vertex2 != minIndex) {
                    degrees[g.edgeList[i].vertex2]--;
                }
                g.edgeList.erase(g.edgeList.begin() + minIndex);
            }
        }
        L.push_back(minIndex);
        degrees[minIndex] = originalV;  //Prevent being selected as min again without changinf indices
    }


    return L;
}


vector<vector<int>> bronKerboschOrdering(Graph& g) {
    vector<int> P;
    vector<int> R;
    vector<int> X;

    //Fill P with all vertices of G
    for(int i=0; i<g.v; i++) {
        P.push_back(i);
    }

    //Compute ordering
    vector<int> order = ordering(g);
    vector<vector<int>> cliques;

    for(long unsigned int i=0; i<order.size(); i++) {
        vector<int> vVector;
        vVector.push_back(order[i]);

        vector<int> neighbours = g.neighbours(order[i]);

        bronKerboschPivoting(g, cliques, vVector, inter(P, neighbours), inter(X,neighbours), 0);

        P = exclusion(P, vVector);
        X.push_back(order[i]);

    }

    return cliques;
}
