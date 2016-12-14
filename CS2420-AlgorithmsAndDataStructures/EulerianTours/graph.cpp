#include <vector>
#include <fstream>
#include <algorithm>
#include "edge.h"
#include "graph.h"

// Reads in input file
void Graph::readFile()
{
	std::ifstream fin (inFileName);

	char a;
	char b;

	fin >> nodeCt >> edgeCt;

	edges.reserve(edgeCt);

	while (fin >> a >> b)
	{
		Edge newEdge;
		newEdge.set(a, b);
		edges.push_back(newEdge);
	}
}

// Prints the adjacency matrix
void Graph::printMatrix()
{
	output << std::endl << "Adjacency Matrix:" << std::endl;
	for (int i = 0; i < nodeCt; ++i)
	{
		for (int j = 0; j < nodeCt; ++j)
		{
			if (matrix[i][j] == -1) output << ". ";
			else output << matrix[i][j];

			if (matrix[i][j] < 10 && matrix[i][j] >= 0) output << "  ";
			else output << " ";
		}
		output << std::endl;
	}
}

// Builds the adjacency matrix
void Graph::constructMatrix()
{
	std::vector< std::vector<int> > newMatrix(nodeCt, std::vector<int>(nodeCt, -1));
	matrix = newMatrix;

	int index = 0;
	for(auto&& edge : edges)
	{
		auto i = edge.toNode;
		auto j = edge.fromNode;
		matrix[i][j] = index;
		matrix[j][i] = index;
		++index;
	}
}

// Returns true if an eulerian tour is possible
bool Graph::tourExists()
{
	for (auto&& row : matrix)
	{
		int degreeSum = 0;
		for (auto&& n : row)
		{
			if ( n >= 0 ) degreeSum += 1;
		}
		if (degreeSum % 2 != 0) return false; // Return false if degree is not odd
	}
	return true;
}

// Chooses a proper edge to follow for the cycle marking phase
int Graph::getEdge(int fromNode, int curIndex)
{
	int newIndex = -1;

	for (int i = 0; i < nodeCt; ++i)
	{
		auto nextEdgeIndex = matrix[fromNode][i];

		if (
			nextEdgeIndex != -1 && 							 // is a valid index
			nextEdgeIndex != curIndex && 				 // is not the same edge
			edges[nextEdgeIndex].cycleID == -1   // is not already in a cycle
			)
		{
			newIndex = nextEdgeIndex;
			return newIndex;
		}
	}

	output << "CRITICAL FAILURE" << std::endl;
	return -1; 
}

// Converts a node number to its alphabet letter
char makeChar(int node) { return node + 'A'; }

// Marks edges with their cycle number
void Graph::startCycle(int startNode, int curIndex, int curCycle, int prevNode)
{
	edges[curIndex].cycleID = curCycle; // Set the cycle 
	output << edges[curIndex].toString() << std::endl;
	
	auto curEdge = edges[curIndex];

	int nextNode = curEdge.toNode;
	if (nextNode == prevNode) nextNode = curEdge.fromNode;

	if (nextNode == startNode) return;

	int nextEdgeIndex = getEdge(nextNode, curIndex);
	startCycle(startNode, nextEdgeIndex, curCycle, nextNode);
}

// Finds eulerian cycles in the graph
void Graph::findCycles()
{
	int curCycle = 0;
	for (auto i = 0u; i < edges.size(); ++i)
	{
		auto curEdge = edges[i];
		if (curEdge.cycleID == -1) // If edge is not in a cycle
		{
			output << "Marking cycle: " << curCycle << std::endl;
			auto startNode = curEdge.fromNode;
			startCycle(startNode, i, curCycle, -1);
			++curCycle;
		}
	}

	cycleCt = curCycle + 1;
}

// Returns true if the given cycleID is in the cycle stack
bool Graph::inStack(int cycleID)
{
	return std::find(cycleStack.begin(), cycleStack.end(), cycleID) != cycleStack.end();
}

// Manages the cycle stack
void Graph::updateCycle(int edgeIndex, int toNode)
{
	auto edge = edges[edgeIndex];
	int fromNode = edge.getOtherEndpoint(toNode); 

	if (!inStack(edge.cycleID)) // if current cycle is not on the stack
	{
		cycleStack.push_back(edge.cycleID);
		cycleStartNodes[edge.cycleID] = fromNode;
	}

	if (toNode == cycleStartNodes[edge.cycleID]) // If the cycle is finished
	{
		cycleStack.pop_back();
	}
}

// Chooses the correct edge to follow given possible options in the cycle joining phase 
int Graph::selectEdge(std::vector<int> & connections)
{
	std::vector<int> firstPri;
	std::vector<int> secondPri;
	std::vector<int> thirdPri;

	for(auto&& edgeIndex : connections)
	{
		auto edge = edges[edgeIndex];

		if (!inStack(edge.cycleID)) 
		{
			firstPri.push_back(edgeIndex); 		// First priority: Return unused edge from a new cycle
		}

		if (edge.cycleID == cycleStack.end()[-1]) 
		{
			secondPri.push_back(edgeIndex);			// Second priority: Return unused edge from current cycle
		}

		if (edge.cycleID == cycleStack.end()[-2])
		{
			thirdPri.push_back(edgeIndex); 		// Third priority: Return unused edge from previous cycle
		}
	}

	if (!firstPri.empty()) return firstPri[0];
	else if (!secondPri.empty()) return secondPri[0];
	else if (!thirdPri.empty()) return thirdPri[0];

	output << "CRITICAL FAILURE :(" << std::endl;
	return -1;
}


// Fills a vector with all valid edges to follow in the cycle joining phase
std::vector<int> Graph::fetchConnections(int node, int curIndex)
{
	std::vector<int> connections;
	for (int i = 0; i < nodeCt; ++i)
	{
		auto edgeIndex = matrix[node][i];

		if ( edgeIndex != -1 && edgeIndex != curIndex && edges[edgeIndex].used == false )
			connections.push_back(edgeIndex);
	}
	assert(!connections.empty());
	return connections; 
}

// Retrieve the best edge to follow in the cycle joining phase
int Graph::getNextEdge(int edgeIndex, int toNode)
{
	updateCycle(edgeIndex, toNode);
	std::vector<int> connections = fetchConnections(toNode, edgeIndex);
	return selectEdge(connections);	
}

// Begin following cycles and joining them to compute the final tour
void Graph::mergeCycles(int curEdgeIndex, int prevNode)
{
	edges[curEdgeIndex].used = true;   // Mark the edge as used
	finalTour.push_back(curEdgeIndex);

	if (finalTour.size() == edgeCt) return;

	auto toNode = edges[curEdgeIndex].toNode;
	if (toNode == prevNode) toNode = edges[curEdgeIndex].fromNode;  // Swap the nodes if they're in the wrong order

	auto nextEdgeIndex = getNextEdge(curEdgeIndex, toNode);

	mergeCycles(nextEdgeIndex, toNode);
}

// Begin the merge cycle process
void Graph::mergeCycles()
{
	std::vector<int> tempStartNodes (cycleCt + 1, 0);
	cycleStartNodes = tempStartNodes;
	mergeCycles(0, -1); // 0 here is just the first edge in the list. -1 is a dummy integer
}

// Print out the final completed tour
void Graph::printTour()
{
	output << std::endl << "Final tour:" << std::endl;
	
	for(auto&& i : finalTour)
	{
		output << edges[i].toString() << std::endl;
	}

	output << std::endl;
}

// Compute an eulerian tour
void Graph::computeTour()
{
	if(tourExists())
	{
		output << std::endl << "Tour exists! Hooray!" << std::endl << std::endl;
		findCycles();
		mergeCycles();
		printTour();
	}
	else
	{
		output << "No Eulerian tour available." << std::endl;
		return;
	}
}
