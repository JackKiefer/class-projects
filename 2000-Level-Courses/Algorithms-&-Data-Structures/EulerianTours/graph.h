#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "edge.h"

class Graph
{
public:
	Graph(std::string f, std::ostream& o) :inFileName(f), output(o) 
	{
		// Constructs graph by reading in data and making the adjacency matrix
		readFile();
		constructMatrix();
	}
	void printMatrix(); // Print the adjacency matrix
	void computeTour(); // Compute an eulerian tour
	void printEdges() { for (auto&& e : edges) output << e.toString() << std::endl; } // Print a simple list of edges
private:
	void readFile();
	void constructMatrix();
	void findCycles();
	void startCycle(int, int, int, int);
	void mergeCycles();
	void mergeCycles(int, int);
	void printTour();
	void updateCycle(int, int);
	bool tourExists();
	bool inStack(int);
	int getEdge(int, int);
	int getNextEdge(int, int);
	int selectEdge(std::vector<int>&);
	std::vector<int> fetchConnections(int, int);
	std::string inFileName;
	std::ostream& output;
	std::vector<Edge> edges;	
	std::vector< std::vector<int> > matrix; 
	std::vector<int> cycleStack;
	std::vector<int> cycleStartNodes; // Stores the starting node for cycle i at cycleStartNodes[i]
	std::vector<int> finalTour;
	unsigned int edgeCt;
	int nodeCt;
	int cycleCt;
};

#endif
