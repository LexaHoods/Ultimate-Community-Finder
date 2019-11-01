#pragma once

#include "Graph.h"

using namespace std;


vector<int> inter(vector<int>& A, vector<int>& B);
vector<int> uni(Graph& g, vector<int>& A, vector<int>& B);
vector<int> exclusion(vector<int>& A, vector<int>& B);
bool isIn(vector<int>& A, int x);

void bronKerboschRecursive(Graph& g, vector<vector<int>>& cliques, vector<int> R, vector<int> P, vector<int> X, int degree);
vector<vector<int>> bronKerbosch(Graph& g);

int tomitaPivot(Graph& g, vector<int>& P, vector<int>& X);
void bronKerboschPivoting(Graph& g, vector<vector<int>>& cliques, vector<int> R, vector<int> P, vector<int> X);

vector<int> ordering(Graph g);
vector<vector<int>> bronKerboschOrdering(Graph& g);
