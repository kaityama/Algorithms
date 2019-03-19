/**
CSS 343 Data Structures, Algorithms, and Discrete Mathematics II
Assignment 3 Graphs
GraphM.cpp
Purpose: Defines the construction, destruction, and operators of a GraphM object. 
Representation of an adjacency matrix graph implementation.

@author Kaitlyn Yamamoto
@version 1.0 12 February 2018
*/
#include "graphm.h"

/**
Constructs a GraphM object. Sets size to 0. Sets all values of the 
cost matrix C[][] to infinity. Sets all TableType objects in T[][] to: 
distance to infinity, visited to false, and path to 0.
*/
GraphM::GraphM()
{
	// initialize size
	size = 0;

	// initialize data member C
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++)
		{
			C[i][j] = INT_MAX;
		}
	}

	// initalize data member T
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++)
		{
			TableType temp = T[i][j];
			temp.dist = INT_MAX;
			temp.visited = false;
			temp.path = 0;
		}
	}
}

/**
Default destructor for a GraphM object. Keyword new not used, so 
delete not needed.
*/
GraphM::~GraphM(){}

/**
Public buildGraph method for GraphM that reads data in from a text file,
and saves the data in the appropriate field. 

@param  an ifstream object passed by reference to be read.
*/
void GraphM::buildGraph(ifstream& infile)
{
	// initialize variables to temporarily hold data from file
	int nodeCount = 0;	// variable for node count of one graph
	string s;	// variable for node names
	int from = INT_MAX;	// variable for from node
	int to = INT_MAX;	// variable for to node
	int weight = INT_MAX;	// variable for weight

	// get node count from the text file
	infile >> nodeCount;
  
	// checks if nodeCount was updated or if node count is invalid
	if (nodeCount <= 0)
	{
		// if not updated, must end of file. this loop ensures infile is eof before returning
		while (!infile.eof())
		{
			getline(infile, s);	// continue to next line
		}
		return;
	}
	size = nodeCount;	// update size
	getline(infile, s);	// continue to next line

	// get node id's from file and save to data member data[]
	for (int i = 1; i < (nodeCount + 1); i++)
	{
		getline(infile, s);	// read one id per line
		NodeData node(s);	// create NodeData with that id
		data[i] = node;	// save NodeData into data array

	}
	cout << endl;	// for formatting

	// read first edge in from file
	infile >> from >> to >> weight;

	// continues while not end of this graph ("0 0 0"), if not, insert edge
	while (from != 0 && to != 0 && weight != 0)
	{
		insertEdge(from, to, weight);	// inserts edge to graph
		infile >> from >> to >> weight;	// read next edge in from file
	}
}

/**
Public insertEdge method for GraphM that inserts an edge to the graph
from the given input.

@param  an int, of from node.
@param  an int, of to node.
@param	an int, weight of edge.
@return	a boolean, true if successfully inserted, false if not.
*/
bool GraphM::insertEdge(int from, int to, int weight)
{
	// if from and to nodes are within range, insert edge
	if ((from <= size) && (to <= size) && (from >= 1) && (to >= 1))
	{
 		C[from][to] = weight;	// save edge to adjacency matrix and return true
		return true;
	}
	// if from or to node is out of range, return false 
	else
	{
		return false;
	}
}

/**
Public removeEdge method for GraphM that removes an edge from the graph
from the given input.

@param  an int, of from node.
@param  an int, of to node.
@return	a boolean, true if successfully removed, false if not.
*/
bool GraphM::removeEdge(int from, int to)
{
  // if from and to nodes are within range, remove edge
	if ((from <= size) && (to <= size) && (from >= 1) && (to >= 1))
	{
 		C[from][to] = INT_MAX;	// set edge to infinity and return true
		return true;
	}
	// if from or to node is out of range, return false
	else
	{
		return false;
	}
}

/**
Public findShortestPath method for GraphM that implements Dijkstra's algorithm
to find the shortest paths between all nodes in the graph. At the end of
the call, the fields in T[][] are updated to hold information on the
shortest paths found.
*/
void GraphM::findShortestPath()
{
	// set T nodes to visited, distance and path to 0
	initializeT();

	// iterates through each node as a source, to find shortest paths from each
	for (int source = 1; source <= size; source++)
	{
		// finds the shortest distances
		T[source][source].dist = 0;	// change this source weight to 0
		int vIndex = source;	// save the index of V for later use
		int verticesVisited = 0;	// initialize vertices visited count

		// exits when all vertices are visited
		while (verticesVisited <= size)
		{
			T[source][vIndex].visited = true;	// mark V as visited
			++verticesVisited;	// update vertices visited count

			// use C[][] to find adjacent paths from source, and save in T[][]
			for (int w = 1; w <= size; w++)
			{
				// if adjacent to source && vertex not visited
				if (C[vIndex][w] < INT_MAX && !(T[source][w].visited))
				{
					// add weight from previous calculation + current edge's weight
					int newWeight = T[source][vIndex].dist + C[vIndex][w];	
					// if new calculated weight is less than the min weight that is saved (shorter path)
					if (newWeight < T[source][w].dist)
					{
						T[source][w].dist = newWeight;	// set distance to new weight
						T[source][w].path = vIndex;		// set path to previous vertex
					}
				}
			}

			int minWeight = INT_MAX;	// initialize min weight to infinity
			int minIndex = INT_MAX;	// initialize min index to infinity
			bool entered = false;	// initialize entered as false

			// find smallest weight saved in T[][] of vertex that is not yet visited (next one to process)
			for (int w = 1; w <= size; w++)
			{	
				// if satisfies the conditions
				if (!(T[source][w].visited) && T[source][w].dist < minWeight)
				{
					minWeight = T[source][w].dist;	// update new min weight
					minIndex = w;	// update new min index
					entered = true;	// we have entered this statement, so set to true
				}
			}

			if (entered)	// minimum has been updated, so update index to new final min index
			{
				vIndex = minIndex;
			}
			// min has not been updated, so all nodes must be visited 
			// OR remaining unvisited nodes have no path from this source
			else
			{
				vIndex = 0;	// set to 0 as extra precaution
			}
		}
	}
}

/**
Public displayAll method for GraphM that displays all nodes and edges in the graph
in an organized grid.
*/
void GraphM::displayAll()
{
  if (size > 0)
  {
  	// Display column names
	  cout << left << setw(25) << "Description";
  	cout << setw(15) << "From node";
	  cout << setw(15) << "To node";
	  cout << left << setw(20) << "Dijkstra's";
	  cout << left << setw(15) << "Path" << endl;
  }

	findShortestPath();	// get most updated table T

	// Display Name, From node, To node, Dijkstra's (distance), and Path from and to every node
	for (int from = 1; from <= size; from++)
	{
		// Display Node ID and start new line
		cout << data[from] << endl;

		// get data from matrices
		for (int to = 1; to <= size; to++)
		{
			if (from == to)	// do not display matrix info when from == to
			{
				continue;
			}
			// if there is no path between vertices (distance == infinity)
			else if (T[from][to].dist == INT_MAX)
			{
				cout << setw(25) << " ";
				// Display From Node
				cout << setw(15) << from;
				// Display To Node
				cout << setw(15) << to;
				//Display placeholder for Dijkstra's (shortest distance)
				cout << left << setw(20) << "-----";
				// Display placeholder for path
				cout << left << setw(15) << "-----";
				cout << endl;
			}
			// if there is a path betweeen vertices
			else
			{
				cout << setw(25) << " ";
				// Display From Node
				cout << setw(15) << from;
				// Display To Node
				cout << setw(15) << to;
				//Display Dijkstra's (shortest distance)
				cout << left << setw(20) << T[from][to].dist;
				int stack[MAXNODES];	// initialize stack to find path
				int stackSize;	// initialize stack size variable
				// Display path
				printPath(from, to, stack, stackSize);	// displays path
				cout << endl;
			}
		}

	}
	cout << endl;
}

/**
Public display method for GraphM that displays info about a specific path
between two nodes. Checks for invalid input.

@param  an int, source node of path to be displayed.
@param  an int, destination node of path to be displayed.
*/
void GraphM::display(int from, int to)
{
	// get most updated shortest path info
	findShortestPath();

	// if nodes given are valid, and the given nodes have a path
	if ((from <= size) && (to <= size) && (from >= 1) && (to >= 1) && (T[from][to].dist < INT_MAX))
	{
		// Display From Node
		cout << setw(15) << from;
		// Display To Node
		cout << setw(15) << to;
		//Display Dijkstra's (shortest distance)
		cout << left << setw(20) << T[from][to].dist;
		int stack[MAXNODES];	// initialize stack to find path
		int stackSize;	// initialize stack size variable
		// Display path
		printPath(from, to, stack, stackSize);	// displays path
		cout << endl;
		// Display names of vertices
		for (int i = stackSize; i >= 0; i--)
		{
			// gets node numbers from the stack to retrieve node ID's from data array
			cout << data[stack[i]] << endl;	
		}
	}
	// if nodes are out of range, not adjacent, or from == to
	else
	{
		// Display From Node
		cout << setw(15) << from;
		// Display To Node
		cout << setw(15) << to;
		//Display placeholder for Dijkstra's (shortest distance)
		cout << left << setw(20) << "-----";
		// Display placeholder for path
		cout << left << setw(15) << "-----";
		cout << endl;
	}
	cout << endl;
}

/**
Private initializeT method that resets all values of T[][] to: 
distance to infinity, visited to false, path to 0.
*/
void GraphM::initializeT()
{
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++)
		{
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}
	}
}

/**
Private printPath method for GraphM that saves the nodes visited in
the shortest path to a stack for later use.

@param  an int, source node of path to be displayed.
@param  an int, destination node of path to be displayed.
@param	an int[], of a stack to be modified.
@param	an int, stack size of the current stack.
*/
void GraphM::printPath(int source, int dest, int stack[], int & stackSize)
{
	int stackIndex = 0;	// initialize current stack index position
	TableType current = T[source][dest];	// copy info from T[][] about this path

	stack[stackIndex] = dest;	// push destination to the stack
	++stackIndex;	// increase current stack index 

	stack[stackIndex] = current.path; // push previous vertex in path to stack
	current = T[source][current.path];	// update current to T[][] of previous vertex in path

	// ends when source node found
	while (current.path > 0)
	{
		++stackIndex; // increase stack index for next push
		stack[stackIndex] = current.path; // push previous vertex in path to stack
		current = T[source][current.path];	// update current to T[][] of previous vertex in path
	}

	// stack complete, now print path
	for (int i = stackIndex; i >= 0; i--)
	{
		cout << stack[i] << " ";	// print each vertex in stack
	}
	stackSize = stackIndex;	// update stack size to current index
}


