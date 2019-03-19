/**
CSS 343 Data Structures, Algorithms, and Discrete Mathematics II
Assignment 2 Binary Search Tree
bintree.h
Purpose: Declares the construction, destruction, and operators of a BinTree object.

@author Kaitlyn Yamamoto
@version 1.0 28 Jan 2018
*/
#pragma once
#include "nodedata.h"

class BinTree
{
	friend ostream& operator <<(ostream & outStream, const BinTree & b);	// output operator overload
public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree &);	// assignment operator overload
	bool operator==(const BinTree &) const;	// equality operator overload
	bool operator!=(const BinTree &) const;	// inequality operator overload
	bool insert(NodeData*);					// inserts data into the tree
	bool retrieve(const NodeData &, NodeData*&) const;	// retrieves data in the tree if found
	int getHeight(const NodeData &);	// gets the height of a given node
	void bstreeToArray(NodeData *[]);		// converts a tree to an array
	void arrayToBSTree(NodeData *[]);		// converts an array to a tree
	int getNodeCount() const;						// gets the total count of nodes in the tree
	void displaySideways() const;			// provided below, displays the tree sideways

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree
											// utility functions
	void emptyHelper(BinTree::Node*);
	BinTree::Node* copyHelper(Node*);			// helper for copy constructor
	int equalsHelper(BinTree::Node*, BinTree::Node*) const;	// helper for equality operator
	int insertHelper(BinTree::Node*&, NodeData*);	// helper for insert
	NodeData* retrieveHelper(BinTree::Node *, NodeData) const;	// helper for retrieve
	int heightHelper(BinTree::Node*, NodeData);		// helper for getHeight
	int findLowestLeaf(BinTree::Node*);				// helper for heightHelper to get height
	void arrayHelper(BinTree::Node*, NodeData *[], int&) const;	// helper for bstreeToArray
	BinTree::Node* buildBalanced(NodeData*[], int, int);	// helper for arrayToBSTree
	int counterHelper(BinTree::Node*) const;				// helper for getNodeCount
	void outputHelper(BinTree::Node*, ostream&) const;
	void sideways(Node*, int) const;		// helper for displaySideways()
};