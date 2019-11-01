COMPONENTS = Graph.o Edge.o BronKerbosch.o


all: a.out clean


a.out: Ultimate-Community-Finder/Ultimate-Community-Finder.cpp $(COMPONENTS)
	g++ -std=c++17 Ultimate-Community-Finder/Ultimate-Community-Finder.cpp $(COMPONENTS) -Wall


Graph.o : Ultimate-Community-Finder/Graph.cpp
	g++ -c -std=c++17 Ultimate-Community-Finder/Graph.cpp -Wall

Edge.o : Ultimate-Community-Finder/Edge.cpp
	g++ -c -std=c++17 Ultimate-Community-Finder/Edge.cpp -Wall

BronKerbosch.o : Ultimate-Community-Finder/BronKerbosch.cpp
	g++ -c -std=c++17 Ultimate-Community-Finder/BronKerbosch.cpp -Wall



clean:
	rm -rf *.o
