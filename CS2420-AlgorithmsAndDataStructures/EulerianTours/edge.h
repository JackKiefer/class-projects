#ifndef EDGE_H
#define EDGE_H

#include <sstream>
#include <string>
#include <iostream>
#include <cassert>

class Edge
{  
public:
	friend bool operator!=(Edge const & a, Edge const & b) // Returns true if the edge's nodes are differetn
	{
		return a.toNode != b.toNode && a.fromNode != b.fromNode;
	}

  int toNode;   // Subscript of one endpoint in node array.  Nodes are stored as numbers, but printed as characters.
	int fromNode; // Subscript of other endpoint in node array
	int cycleID;  // Cycle which the edge is a member of, -1 if it is included in no cycle
	bool used;    // true if edge is used in final tour

  // Create a string version of Edge
  // Edge endpoints are stored as numbers, but printed as characters.

  std::string toString()
  { 
		std::ostringstream oss;  // allows string to act like stream to use stream operations
		char t = toNode + 'A';
		char f = fromNode + 'A';

    oss << "   "<<f << "-"<<t  << "(" << cycleID << ")";
    return oss.str();
  }  

  // if oneNode is an endpoint, return other endpoint
  int getOtherEndpoint(int oneNode)
  { 
		if (fromNode==oneNode) return toNode;
    assert(toNode==oneNode);
    return fromNode;
  }

  // Set initial values of an edge from Node f to Node t
  void set(char f, char t)
  {  
		fromNode = f -'A';
    toNode = t-'A';
    cycleID = -1;
    used = false;
//    std::cout << "creating Edge " << toString() << std::endl;
  }
};

#endif
