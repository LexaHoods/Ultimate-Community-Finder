COMPONENTS = Graph.o BronKerbosch.o MaxCliques.o


all: a.out clean


a.out: Ultimate-Community-Finder/Ultimate-Community-Finder.cpp $(COMPONENTS)
	g++ -std=c++17 Ultimate-Community-Finder/Ultimate-Community-Finder.cpp $(COMPONENTS) -Wall



Graph.o : Ultimate-Community-Finder/Graph.cpp
	g++ -c -std=c++17 Ultimate-Community-Finder/Graph.cpp -Wall


BronKerbosch.o : Ultimate-Community-Finder/BronKerbosch.cpp
	g++ -c -std=c++17 Ultimate-Community-Finder/BronKerbosch.cpp -Wall

MaxCliques.o : Ultimate-Community-Finder/MaxCliques.cpp
	g++ -c -std=c++17 Ultimate-Community-Finder/MaxCliques.cpp -Wall



clean:
	rm -rf *.o
