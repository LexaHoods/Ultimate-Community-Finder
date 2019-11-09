#include "MaxCliques.h"

#include "iostream"


    //Data structures

    //TODO Fix tree (or find smth else)

void Leaf::printRecursive(int depth) {
    for(long unsigned int i=0; i<children.size(); i++) {
        for(int j=0; j<depth; j++) {
            cout << "   ";
        }
        cout << children[i].value << endl;
        children[i].printRecursive(depth+1);
    }
}



void SuffixTree::print() {
    for(long unsigned int i=0; i<children.size(); i++) {
        cout << children[i].value << endl;
        children[i].printRecursive(1);
    }
}


void SuffixTree::append(vector<int> sequence) {
    vector<Leaf> * childrenVector = &children;

    while(sequence.size()) {

            //We look for the next value in current leaf's children
        bool found = false;
        for(long unsigned int i=0; i<(*childrenVector).size(); i++) {
            if((*childrenVector)[i].value == sequence[sequence.size()-1]) {
                childrenVector = &((*childrenVector)[i].children);
                found = true;
                break;
            }
        }

            //If not found, we create a new leaf containing that value
        if(!found) {
            (*childrenVector).push_back(Leaf(sequence[sequence.size()-1]));
            childrenVector = &((*childrenVector)[childrenVector->size()-1].children);
        }

        if(sequence.size() > 1)
            sequence.erase(sequence.end()-1);
        else
            sequence.clear();
    }

}



bool SuffixTree::isContained(vector<int> sequence) {

    vector<Leaf> * childrenVector = &children;

    while(sequence.size()) {

            //We look for the next value in current leaf's children
        bool found = false;
        for(long unsigned int i=0; i<(*childrenVector).size(); i++) {
            if((*childrenVector)[i].value == sequence[sequence.size()-1]) {
                childrenVector = &((*childrenVector)[i].children);
                found = true;
                break;
            }
        }

            //If not found, we create a new leaf containing that value
        if(!found) {
            return false;
        }

        if(sequence.size() > 1)
            sequence.erase(sequence.end()-1);
        else
            sequence.clear();
    }

    return true;

}



    //maxCliques1

int degeneracy(Graph& g, vector<int>& ordering) {
    int minDegree = g.v;

    //Vector with ranks in ordering for each vertex
    //(for better time complexity)
    vector<int> orderingRanks (g.v, 0);
    for(int i=0; i<g.v; i++) {
        orderingRanks[ordering[i]] = i;
    }

    //Looks for min degree
    for(int i=0; i<g.v; i++) {

        //Compute degree with vertices coming later in the ordering only
        int degree = 0;
        for(long unsigned int j=0; j<g.vertices[i].size(); j++) {

            //Potentially increment current degree
            if(orderingRanks[i] < orderingRanks[g.vertices[i][j]])
                degree++;

        }

        if(degree<minDegree) {
            degree = minDegree;
        }

    }

    return minDegree;
}



vector<vector<int>> degenerateAdjLists(Graph& g, vector<int>& ordering) {
    vector<vector<int>> degenerateAdjLists;

    //Vector with ranks in ordering for each vertex
    //(for better time complexity)
    vector<int> orderingRanks (g.v, 0);
    for(int i=0; i<g.v; i++) {
        orderingRanks[ordering[i]] = i;
    }


    //Fills degenerateAdjLists by iterationg over g.vertices
    for(int i=0; i<g.v; i++) {
        degenerateAdjLists.push_back(vector<int>());

            //Fill degenerate adjacency list of vertex i
        for(long unsigned int j=0; j<g.vertices[i].size(); j++) {

            //Check if j comes later in ordering
            if(orderingRanks[g.vertices[i][j]] > orderingRanks[i]) {
                //Append at the beginning
                degenerateAdjLists[i].insert(degenerateAdjLists[i].begin(), g.vertices[i][j]);
            }
            else {
                //Append at the end
                degenerateAdjLists[i].push_back(g.vertices[i][j]);
            }
        }
    }

    return degenerateAdjLists;
}



Graph inducedSubgraph(Graph& g, int v, vector<int>& order, vector<int>& conversionVector) {

    //In order to avoid errors with non-connected graphs in Bron-Kerbosch
    //implementations, we can't just remove edges connected to non-included
    //vertices.
    //Since we're too lazy to modify them and make them compatible with
    //non-connected graphs, we will instead compute a subgraph with different
    //vertices labeling.
    //We will then use a conversion vector to convert found cliques to the
    //original labeling.

    if(v > g.v) {
        //Incorrect vertex
        return g;
    }

    //Get order of v
    int vOrder = 0;
    bool found = false;
    while(!found) {
        if(v == order[vOrder]) {
            found = true;
        } else {
            vOrder++;
        }
    }

    vector<int> N = g.neighbours(v);
    N.push_back(v);
    vector<int> V;
    for(int i=vOrder; i<g.v; i++) {
        V.push_back(order[i]);
    }

    vector<int> verticesSubset =  inter(N, V);


        //Build conversion vector and building vector
    vector<int> buildingVector;
    conversionVector.clear();
    for(int i=0; i<g.v; i++) {
        if(isIn(verticesSubset, i)) {
            conversionVector.push_back(i);
            buildingVector.push_back(conversionVector.size()-1);
        }
        else {
            buildingVector.push_back(-1);
        }
    }

    //NOTE:
    //Building vector: g -> subgraph
    //Conversion vector: subgraph -> g    (better time complexity for this algorithm)


        //Build subgraph induced by v cap gamma(v)
    Graph subgraph;
    for(int i=0; i<g.v; i++) {
        if(buildingVector[i] != -1) {
            subgraph.vertices.push_back(vector<int>());

            for(long unsigned int j=0; j<g.vertices[i].size(); j++) {
                if(buildingVector[g.vertices[i][j]] != -1) {
                    subgraph.vertices[subgraph.vertices.size()-1].push_back(buildingVector[g.vertices[i][j]]);
                }
            }
        }
    }
    subgraph.v = (int) verticesSubset.size();

    return subgraph;
}



void convertClique(vector<int>& clique, vector<int>& conversionVector) {
    for(long unsigned int i=0; i< clique.size(); i++) {
        clique[i] = conversionVector[clique[i]];
    }
}



vector<int> reorder(vector<int>& order, vector<int>& vec) {
    //We can simply return difference since this function conserves order

    vector<int> temp =  difference(order, vec);

    return difference(order, temp);
}



vector<vector<int>> maxCliques1(Graph& g) {
    vector<vector<int>> K;
    vector<int> conversionVector;

    vector<int> order = ordering(g);
    vector<vector<int>> degenAdjLists = degenerateAdjLists(g, order);
    SuffixTree T;

    for(long unsigned int i=0; i<order.size(); i++) {

        Graph subgraph = inducedSubgraph(g, order[i], order, conversionVector);
        if(subgraph.v == 1) {
            continue;
        }

        vector<vector<int>> cliques = bronKerbosch(subgraph);

        for(long unsigned int j=0; j<cliques.size(); j++) {
            convertClique(cliques[j], conversionVector);
            cliques[j] = reorder(order, cliques[j]);

            bool contained = T.isContained(cliques[j]);

            if(!contained) {
                T.append(cliques[j]);
                K.push_back(cliques[j]);
            }

        }

    }

    return K;
}



//Max cliques 2

bool isIncluded(vector<int>& A, vector<int>& B) {
    vector<int> intersection = inter(A, B);

    return B.size() == intersection.size();
}



vector<vector<int>> maxCliques2(Graph& g) {
    vector<vector<int>> K;
    vector<int> conversionVector;

    vector<int> order = ordering(g);
    vector<vector<int>> degenAdjLists = degenerateAdjLists(g, order);
    SuffixTree T;

    for(long unsigned int i=0; i<order.size(); i++) {

        Graph subgraph = inducedSubgraph(g, order[i], order, conversionVector);
        subgraph.print();
        if(subgraph.v == 1) {
            continue;
        }

        vector<vector<int>> cliques = bronKerbosch(subgraph);

        //Considering cliques
        for(long unsigned int j=0; j<cliques.size(); j++) {
            convertClique(cliques[j], conversionVector);

            //Considering all vertices of a clique
            for(long unsigned int k=0; k<cliques[j].size(); k++) {

                vector<int> neighbours = g.neighbours(cliques[j][k]);

                //Considering all of its neighbours
                for(long unsigned int l=0; l<neighbours.size(); l++) {
                    if(l < i) {
                        //Is it adjacent to all elements of K?
                        vector<int> gN = g.neighbours(l);
                        if(!isIncluded(gN, cliques[j])) {
                            K.push_back(cliques[j]);
                            l=neighbours.size();
                            k=cliques[j].size();
                        }
                    }
                }
            }
        }

    }

    return K;
}
