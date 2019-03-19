/**
CSS 343 Data Structures, Algorithms, and Discrete Mathematics II
Assignment 3 Graphs
graphl.h
Purpose: Declares the construction, destruction, and operators of a GraphL object.
Representation of an adjacency list graph implementation.

@author Kaitlyn Yamamoto
@version 1.0 12 February 2018
*/
#include "nodedata.h"
#include "limits.h"
#include <fstream>
#include <iomanip>

const int MAX_NODES = 101;	// global constant for maximum size of graph

class GraphL
{
public:
	GraphL();	// Constructor initializing list
	~GraphL();	// Destructor for list
	void buildGraph(ifstream&);	// Builds graph from text file
	void displayGraph();	// Displays grid of graph
	void depthFirstSearch();	// Performs and prints depth first search 
private:
	struct EdgeNode;      // forward reference for the compiler
	struct GraphNode {    // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // node id 
		bool visited;	// saves if node is visited
	};

	struct EdgeNode {
		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;	// pointer to next edge
	};
	int size;	// number of nodes in the graph
	GraphNode * data[MAX_NODES];	// adjacency list
	void dfs(int v);	// private helper method for depth first search
};

