/**
CSS 343 Data Structures, Algorithms, and Discrete Mathematics II
Assignment 2 Binary Search Tree
bintree.cpp
Purpose: Defines the construction, destruction, and operators of a BinTree object.

@author Kaitlyn Yamamoto
@version 1.0 28 Jan 2018
*/
//#include "stdafx.h"
#include "bintree.h"

/**
Constructs a BinTree object and sets the root to NULL.
*/
BinTree::BinTree()
{
	root = NULL;
}

/**
Copy constructor for a BinTree object.

@param  the BinTree object to be copied.
*/
BinTree::BinTree(const BinTree & toCopy)
{
	if (toCopy.root == NULL)
	{
		return;
	}
	else
	{
		root = copyHelper(toCopy.root);
		return;
	}
}

/**
Helper function that copies a BinTree object.

@param  a Node pointer passed by reference to be modified.
@param	a Node pointer to be copied.
*/
BinTree::Node* BinTree::copyHelper(BinTree::Node * copyRoot)
{
	if (copyRoot == NULL)
	{
		return NULL;
	}

	Node* newNode = new Node();

	if (copyRoot->data == NULL)
	{
		newNode->data = NULL;
		newNode->left = NULL;
		newNode->right = NULL;
	}
	else
	{
		NodeData * nodeData = new NodeData();
		*nodeData = *copyRoot->data;
		newNode->data = nodeData;
	}
	newNode->left = copyHelper(copyRoot->left);
	newNode->right = copyHelper(copyRoot->right);
	return newNode;
}

/**
Destructor for a BinTree object. Calls a function that empties the tree.
*/
BinTree::~BinTree()
{
	makeEmpty();
}

/**
Return a boolean true if the tree is empty, and false if not.

@return a boolean whether the tree is empty or not.
*/
bool BinTree::isEmpty() const
{
	return root == NULL;
}

/**
Helper function that empties a BinTree object.
*/
void BinTree::makeEmpty()
{
	Node * storage = new Node();
	Node * itr = new Node();
	for (itr = root; itr != NULL; itr = storage) {
		if (itr->left == NULL) {
			storage = itr->right;
			delete itr;
		}
		else {
			storage = itr->left;
			itr->left = storage->right;
			storage->right = itr;
		}
	}
	root = NULL;
}

/**
Helper function that helps traverse the tree to make the tree empty.

@param  a Node pointer of a BinTree object.
*/
void BinTree::emptyHelper(BinTree::Node * node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		emptyHelper(node->left);
		emptyHelper(node->right);
		delete node;
	}
}

/**
Assignment operator overload for a BinTree object.

@param  a BinTree passed by reference for assignment.
@return this Bintree reference after assignment.
*/
BinTree & BinTree::operator=(const BinTree & other)
{
	root = copyHelper(other.root);
	return *this;
}

/**
Equality operator overload for a BinTree object. Returns true if two
BinTree objects are equal, false if not.

@param  a BinTree passed by reference to be evaluated.
@return a boolean whether the BinTree passed in is equal to this BinTree.
*/
bool BinTree::operator==(const BinTree & other) const
{
	if (root == NULL && other.root == NULL)
	{
		return true;
	}
	else
	{
		return equalsHelper(root, other.root) > 0;
	}
}

/**
Inequality operator overload for a BinTree object. Returns true if two
BinTree objects are not equal, false if they are.

@param  a BinTree passed by reference to be evaluated.
@return a boolean whether the BinTree passed in is not equal to this BinTree.
*/
bool BinTree::operator!=(const BinTree & other) const
{
	if (root == NULL && other.root == NULL)
	{
		return false;
	}
	else
	{
		return !(*this == other);
	}
}

/**
Helper function that helps traverse the tree to test the equality of two
BinTree objects.

@param  a Node pointer of a BinTree object.
@param  a Node pointer of another BinTree object.
@return an int 1 (true) if the BinTree objects are identical, 0 (false) if not.
*/
int BinTree::equalsHelper(BinTree::Node * thisRoot, BinTree::Node * otherRoot) const
{
	if (thisRoot == NULL && otherRoot == NULL)
	{
		return 1;
	}
	if (thisRoot != NULL && otherRoot != NULL)
	{
		return (*thisRoot->data == *otherRoot->data && equalsHelper(thisRoot->left, otherRoot->left) &&
			equalsHelper(thisRoot->right, otherRoot->right));
	}
}

/**
Insert wrapper function that adds the given NodeData to the tree.

@param  a NodeData pointer to be added.
@return a boolean true if the data is inserted, false if not.
*/
bool BinTree::insert(NodeData * data)
{
	return insertHelper(root, data) > 0;
}

/**
Insert recursive function that helps add the given NodeData to the tree.

@param  a Node pointer reference to the current node.
@param  a NodeData pointer to be added.
@return an int 1 (true) if the data is inserted, 0 (false) if not.
*/
int BinTree::insertHelper(BinTree::Node *& root, NodeData * data)
{
	if (root == NULL)
	{
		Node * newNode = new Node();
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		root = newNode;
		return 1;
	}
	else
	{
		if (*root->data == *data)
		{
			return 0;
		}
		else if (*root->data > *data)
		{
			return insertHelper(root->left, data);
		}
		else if (*root->data < *data)
		{
			return insertHelper(root->right, data);
		}
		else
		{
			return 0;
		}
	}
}

/**
Retrieve function that searches for a target data in the tree, and
retrieves a pointer to that data if found. Returns true if the target
is retrieved, false if not.

@param  a NodeData reference to be searched for.
@param  a NodeData pointer reference to be modified if the target is found.
@return a boolean true if the data is retrieved, false if not.
*/
bool BinTree::retrieve(const NodeData & target, NodeData *& result) const
{
	if (root == NULL)
	{
		return false;
	}
	else
	{
		result = NULL;
		NodeData t = target;
		BinTree tree = *this;
		result = tree.retrieveHelper(root, t);
		return result != NULL;
	}
}

/**
Retrieve recursive function that helps search for the given data in
a tree. Returns the NodeData pointer if found, NULL if not found.

@param  a Node pointer of the current node.
@param  a NodeData target to be retrieved.
@return a NodeData pointer if target is found, NULL if not.
*/
NodeData * BinTree::retrieveHelper(BinTree::Node * root, NodeData target) const
{
	if (root == NULL)
	{
		return NULL;
	}
	else if (*root->data == target)
	{
		return root->data;
	}
	else if (*root->data > target)
	{
		return retrieveHelper(root->left, target);
	}
	else if (*root->data < target)
	{
		return retrieveHelper(root->right, target);
	}
	else
	{
		return NULL;
	}
}

/**
Height function that gets the height of a given node. Returns 0 if not found.

@param  a NodeData reference to be searched for.
@return an int of the node's height, 0 if not found.
*/
int BinTree::getHeight(const NodeData & target)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		BinTree tree = *this;
		NodeData t = target;
		return tree.heightHelper(root, t);
	}
}

/**
Height helper function that helps get the height of a given node. 
Returns 0 if not found.

@param	a Node pointer of the current node.
@param  a NodeData to be searched for.
@return an int of the node's height, 0 if not found.
*/
int BinTree::heightHelper(BinTree::Node * root, NodeData target)
{
	if (root == NULL)
	{
		return 0;
	}
	// once target is located, then traverse to the lowest child to get height
	else if (*root->data == target)
	{
		return findLowestLeaf(root);
	}
	// if target not found, traverse tree
	else if (*root->data > target)
	{
		return heightHelper(root->left, target);
	}
	else if (*root->data < target)
	{
		return heightHelper(root->right, target);
	}
	else
	{
		return 0;
	}
}

/**
Height helper function that compares the left and right heights of a given 
node and returns the greater height. Returns 0 if not found.

@param	a Node pointer of the current node.
@return an int of the node's height, 0 if not found.
*/
int BinTree::findLowestLeaf(BinTree::Node * root)
{
	if (root == NULL)
		return 0;
	else
	{
		int leftHeight = findLowestLeaf(root->left);
		int rightHeight = findLowestLeaf(root->right);

		if (leftHeight > rightHeight)
		{
			return leftHeight + 1;

		}
		else
		{
			return rightHeight + 1;
		}
	}
}

/**
Converts this tree to an array and empties the tree.

@param	a NodeData pointer array to be modified.
*/
void BinTree::bstreeToArray(NodeData * storage[])
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		int start = 0;
		arrayHelper(root, storage, start);
		makeEmpty();
		return;
	}
}

/**
Array helper function that helps traverse the tree to save data to the array.

@param	a Node pointer of the current node.
@param	a Node pointer array to be modified.
@param  an int of the current index.
*/
void BinTree::arrayHelper(BinTree::Node * root, NodeData * storage[], int & index) const
{
	if (root == NULL)
	{
		return;
	}
	arrayHelper(root->left, storage, index);
	storage[index] = root->data;
	index++;
	arrayHelper(root->right, storage, index);
}

/**
Converts an array to a balanced binary search tree.

@param	a Node pointer array to be modified.
*/
void BinTree::arrayToBSTree(NodeData * storage[])
{
	if (storage[0] == 0)
	{
		return;
	}
	else
	{
		int dataCount = 0;
		for (int i = 0; i < 100; i++)
		{
			if (storage[i] != 0)
			{
				dataCount++;
			}
		}
		root = buildBalanced(storage, 0, dataCount - 1);
	}
}

/**
Helps build a balanced binary search tree.

@param	a Node pointer array to be modified.
@param	an int of the starting index.
@param	an int of the ending index.
*/
BinTree::Node * BinTree::buildBalanced(NodeData * storage[], int start, int end)
{
	int midpoint = (start + end) / 2;
	// Base case
	if (start > end)
	{
		return NULL;
	}

	// Get the middle element of the array and make it the new tree "root"
	Node * node = new Node();
	node->data = storage[midpoint];

	// Recursively reconstructs the left side of the tree, using the first half of the given array
	node->left = buildBalanced(storage, start, midpoint - 1);

	// Recursively reconstructs the right side of the tree, using the second half of the given array
	node->right = buildBalanced(storage, midpoint + 1, end);

	// Returns the given "root"
	return node;
}

/**
Counts total number of nodes in the tree.

@return	an int of the node count.
*/
int BinTree::getNodeCount() const
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		int count = counterHelper(root);
		return count;
	}
}

/**
Helps count total number of nodes in the tree.

@param	a Node pointer of the current node.
@return	an int of the node count.
*/
int BinTree::counterHelper(BinTree::Node * node) const
{
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + counterHelper(node->left) + counterHelper(node->right);
	}
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

/**
Output operator overload for a BinTree object. Returns an ostream
of the output representation of the tree, inorder.

@param  an ostream object to be modified and returned.
@param  a BinTree object to be outputted.
@return an ostream object.
*/
ostream & operator<<(ostream & outStream, const BinTree & b)
{
	b.outputHelper(b.root, outStream);
	outStream << endl;
	return outStream;
}

/**
Output operator helper function.

@param  a Node pointer of the current node.
@param  an ostream object to be modified.
*/
void BinTree::outputHelper(BinTree::Node * node, ostream & outStream) const
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		outputHelper(node->left, outStream);
		outStream << *node->data << " ";
		outputHelper(node->right, outStream);
	}
}
