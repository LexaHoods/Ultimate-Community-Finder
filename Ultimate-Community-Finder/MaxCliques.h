#pragma once

#include "Graph.h"
#include "BronKerbosch.h"

class SuffixTree;

class Node {
public:
    explicit Node(int v) { value = v; };

    int value;
    vector<Node> children;

private:
    void printRecursive(int depth);
    vector<vector<int>> returnCliques();
    friend class SuffixTree;
};


class SuffixTree {

public:
    vector<Node> children;

    void append(vector<int> sequence);
    bool isContained(vector<int> sequence);
    vector<vector<int>> returnCliques();

    void print();
};



int degeneracy(Graph& g, vector<int>& ordering);    //Given a degeneracy ordering, computes G's degeneracy
vector<vector<int>> degenerateAdjLists(Graph& g, vector<int>& ordering);    //Given a degeneracy ordering, computes G's degenerarte adjacency lists
Graph inducedSubgraph(Graph& g, int v, vector<int>& order, vector<int>& conversionVector);
void convertClique(vector<int>& clique, vector<int>& conversionVector);
vector<int> reorder(vector<int>& order, vector<int>& vec); //Order elements of vec according to ordering, vec being a subset of ordering
vector<vector<int>> maxCliques1(Graph& g);

bool isIncluded(vector<int>& A, vector<int>& B); //Check if all elements of B are in A
vector<vector<int>> maxCliques2(Graph& g);
