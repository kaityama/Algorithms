/**
CSS 343 Data Structures, Algorithms, and Discrete Mathematics II
Assignment 3 Graphs
graphm.h
Purpose: Declares the construction, destruction, and operators of a GraphM object.
Representation of an adjacency matrix graph implementation.

@author Kaitlyn Yamamoto
@version 1.0 12 February 2018
*/
#include "nodedata.h"
#include "limits.h"
#include <fstream>
#include <iomanip>

const int MAXNODES = 101;	// global constant for maximum size of graph

class GraphM
{
public:
	GraphM();	// Constructor initializing the matrix
	~GraphM();	// Default destructor
	void buildGraph(ifstream&);	// builds graph from text file
	bool insertEdge(int, int, int);	// inserts edge
	bool removeEdge(int, int);	// removes edge
	void findShortestPath();	// finds shortest paths using Dijkstra's algorithm
	void displayAll();	// displays grid of all nodes and edges
	void display(int, int);	// displays specific path info
private:
	NodeData data[MAXNODES];	// data for graph nodes
	int C[MAXNODES][MAXNODES];	// Cost array, the adjacency matrix
	int size;					// number of nodes in the graph
	struct TableType {
		bool visited;			// whether node has been visited
		int dist;				// shortest distance from source known so far
		int path;				// previous node in path of min dist
	};
	TableType T[MAXNODES][MAXNODES];	// stores visited, distance, path

	void initializeT();	// private helper method to reset T[][]
	void printPath(int, int, int[], int&);	// private helper method to display a path
};
