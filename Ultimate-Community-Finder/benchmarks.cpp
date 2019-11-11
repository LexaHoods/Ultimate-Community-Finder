#include <hayai/hayai.hpp>

#include "Graph.h"
#include "BronKerbosch.h"
#include "MaxCliques.h"


class random:public::hayai::Fixture {
public:
    virtual void SetUp() {
        this->graph = new Graph();
        this->graph->random(100, 0.2);
    }

    virtual void TearDown() {
        delete this->graph;
    }

    Graph* graph;
};


class barabasiAlbert:public::hayai::Fixture {
public:
    virtual void SetUp() {
        this->graph = new Graph();
        this->graph->barabasiAlbert(100, 4, 5);
    }

    virtual void TearDown() {
        delete this->graph;
    }

    Graph* graph;
};



//bronKerbosch

BENCHMARK_F(random, bronKerbosch, 50, 1) {
    bronKerbosch(*graph);
}

BENCHMARK_F(barabasiAlbert, bronKerbosch, 50, 1) {
    bronKerbosch(*graph);
}


//bronKerboschOrdering

BENCHMARK_F(random, bronKerboschOrdering, 50, 1) {
    bronKerboschOrdering(*graph);
}

BENCHMARK_F(barabasiAlbert, bronKerboschOrdering, 50, 1) {
    bronKerboschOrdering(*graph);
}


//maxCliques1

BENCHMARK_F(random, maxCliques1, 50, 1) {
    maxCliques1(*graph);
}

BENCHMARK_F(barabasiAlbert, maxCliques1, 50, 1) {
    maxCliques1(*graph);
}


//maxCliques2

BENCHMARK_F(random, maxCliques2, 50, 1) {
    maxCliques2(*graph);
}

BENCHMARK_F(barabasiAlbert, maxCliques2, 50, 1) {
    maxCliques2(*graph);
}







int main() {

    srand(time(NULL));

    hayai::ConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}
