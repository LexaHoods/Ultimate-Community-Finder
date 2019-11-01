#pragma once

#include "Graph.h"
#include "BronKerbosch.h"


int degeneracy(Graph& g, vector<int> ordering); //Given a degeneracy ordering, computes G's degeneracy

vector<vector<int>> maximumCliques(Graph& g);
