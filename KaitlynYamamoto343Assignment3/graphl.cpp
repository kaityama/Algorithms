/**
CSS 343 Data Structures, Algorithms, and Discrete Mathematics II
Assignment 3 Graphs
graphl.cpp
Purpose: Defines the construction, destruction, and operators of a GraphL object.
Representation of an adjacency list graph implementation.

@author Kaitlyn Yamamoto
@version 1.0 12 February 2018
*/
#include "graphl.h"

/**
Constructs a GraphL object. Sets size to 0.
*/
GraphL::GraphL()
{
	size = 0;
}

/**
Destructor for a GraphL object. Iterates through adjacency list
and deletes all data declared with new.
*/
GraphL::~GraphL()
{
	// iterates through GraphNode array to access potential EdgeNodes
	for (int i = 1; i <= size; i++)
	{
		EdgeNode * ptr = data[i]->edgeHead;	// initializes pointer to this GraphNode's edgeHead
		EdgeNode * temp = NULL;	// initializes second pointer
		while (ptr != NULL)	// exits when all edgeNodes from this GraphNode have been deleted
		{
			temp = ptr;	// move second pointer to current pointer
			ptr = ptr->nextEdge;	// move current pointer ahead to nextEdge to be deleted
			delete temp;	// delete current edge
		}
		delete data[i]->data;	// delete nodeData of this GraphNode
		delete data[i];	// delete this GraphNode
	}
}

/**
Public buildGraph method for GraphL that reads data in from a text file,
and saves the data in the appropriate field.

@param  an ifstream object passed by reference to be read.
*/
void GraphL::buildGraph(ifstream & infile)
{
	// initialize variables to temporarily hold data from file
	int nodeCount = 0;	// variable for node count of one graph
	string s;	// variable for node names
	int from = INT_MAX;	// variable for from node
	int to = INT_MAX;	// variable for to node

	// get node count from the text file
	infile >> nodeCount;
	// checks if nodeCount was updated or invalid
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

	// get node id's from file and save to graph node array
	for (int i = 1; i < (nodeCount + 1); i++)
	{
		getline(infile, s);	// read one ID per line
		NodeData * node = new NodeData(s);	// create NodeData with that ID
		GraphNode * newNode = new GraphNode;	// create GraphNode
		newNode->data = node;	// set GraphNode data 
		newNode->edgeHead = NULL;	// initialize GraphNode edgehead to NULL
		newNode->visited = false;	// initialize GraphNode visited to false
		data[i] = newNode;	// save GraphNode to the adjacency list
	}
	cout << endl;

	// read first edge in from file
	infile >> from >> to;

	// continues while not end of this graph ("0 0"), if not, add edge to list
	while (from != 0 && to != 0)
	{
		// if from and to nodes are within range, insert edge
		if ((from <= size) && (to <= size) && (from >= 1) && (to >= 1))
		{
			EdgeNode * newEdge = new EdgeNode;	// create new edgenode
  			newEdge->adjGraphNode = to;	// save this adjacent node's info
  			newEdge->nextEdge = NULL;	// point to null
			// if edgeHead is empty
  			if (data[from]->edgeHead == NULL)	
  			{
  				data[from]->edgeHead = newEdge;	// set newEdge as head
  			}
  			// if edgeHead is occupied
  			else
  			{
  				EdgeNode * temp = NULL;		// temp to save current head
  				temp = data[from]->edgeHead;	// save current head to connect to new head
  				newEdge->nextEdge = temp;	// point new head to old head
  				data[from]->edgeHead = newEdge;	// save new head
  			}
		}
		
		// read in next edge
		infile >> from >> to;
	}
}

/**
Public displayGraph method for GraphL that displays all nodes and edges in the graph
in an organized grid.
*/
void GraphL::displayGraph()
{
	cout << "Graph:" << endl;	// display title
	for (int i = 1; i <= size; i++)	// iterates through adjacency list
	{
		EdgeNode * itr = data[i]->edgeHead;	// initializes iterator, point at this node's edgeHead
		cout << "Node " << i;	// display subheading of node number
		cout << "               " << *data[i]->data << endl;	// display node data (name/ID)
		while (itr != NULL)	// exits when iterator processes all edges from this GraphNode
		{
			cout << "\t edge " << i << " " << itr->adjGraphNode << endl;	// prints edge
			itr = itr->nextEdge;	// updates iterator
		}
	}
}

/**
Public depthFirstSearch method for GraphL that acts as wrapper function for depth first
search algorithm. Displays nodes visited in depth first order.
*/
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";	// print heading

	// mark all not visited
	for (int i = 1; i <= size; i++)
	{
		data[i]->visited = false;
	}

	//for each V in graph, reaches every node in graph
	for (int v = 1; v <= size; v++)
	{
		//if V is not visited, perform DFS private method
		if (!(data[v]->visited))
		{
			dfs(v);
		}
	}
}

/**
Private recursive dfs method for GraphL that performs depth first search
for the vertex provided.

@param  an int, vertex that is being searched.
*/
void GraphL::dfs(int v)
{
	// mark v as visited
	data[v]->visited = true;
	// do whatever with v (print v)
	cout << v << " ";
	// for each w adjacent to v
	EdgeNode * itr = data[v]->edgeHead;	// points iterator at head of edges
	while (itr != NULL)	// exits once all edges have been processed
	{
		int w = itr->adjGraphNode;	// gets w, adjacent to v
		// if w not visited
		if (!(data[w]->visited))
		{
			dfs(w);	// perform DFS on w
		}
		itr = itr->nextEdge;	// update iterator to next edge
	}
}
