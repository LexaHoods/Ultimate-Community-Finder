#pragma once

#include "Graph.h"

using namespace std;


vector<int> inter(vector<int>& A, vector<int>& B);  //Sets ntersection
vector<int> uni(Graph& g, vector<int>& A, vector<int>& B);  //Sets union
vector<int> exclusion(vector<int>& A, vector<int>& B);  //Sets exclusion
bool isIn(vector<int>& A, int x);   //Check if an element is in the set

void bronKerboschRecursive(Graph& g, vector<vector<int>>& cliques, vector<int> R, vector<int> P, vector<int> X);
vector<vector<int>> bronKerbosch(Graph& g);

int tomitaPivot(Graph& g, vector<int>& P, vector<int>& X);
void bronKerboschPivoting(Graph& g, vector<vector<int>>& cliques, vector<int> R, vector<int> P, vector<int> X);

vector<int> ordering(Graph g);  //Computes a degeneracy ordering
vector<vector<int>> bronKerboschOrdering(Graph& g);
