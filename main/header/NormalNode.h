//******************************************************************************
//				CLASS DECLARATION
//  CLASS NAME	:NormalNode
//  PURPOSE	    :This is aderived class from the base class of Node.
//               Where an object of Node can never be created an object of
//               NormalNode can.  Furthermore an object of NormalNode can be
//               pointed to by a Node*:
//					 Node* nodePtr = new NormalNode(false);   true == is a root.
//
//               THIS NORMALNODE IS DESIGNED FOR A BSTAR TREE.
//               The root of a BStarTree is 2*(floor(2/3(NODE_ORDER - 1)) + 1 the order of all the other nodes in
//				 the tree. This is to facilitate a split from one node to two nodes
//				 both 2/3's full. This is different than all the NormalNodes.
//
//				 TheNormalNodes use the derived Node classes order (NODE_ORDER).
//				 It splits when 2 NormalNodes are full and splits them into 3 nodes 2/3 full.
//
//  DESCRIPTION	:The NormalNode inherits the iOrder, number of items
//               stored, dynamically allocated memory for data storage, from the
//				 derived Node class. The NormalNodeNode statically allocates an array of
//				 Node* the Node's NODE_ORDER
//  METHODS:
//      Constructor -- intializes a NormalNode object
//		void Print()  -- Currenty prints out contents of a node except the nodePtrs
//		bool AddItem() -- Does nothing right now.
//
//******************************************************************************
#ifndef NORMALNODE_H
#define NORMALNODE_H

#include <cmath>
#include <iostream>
#include <algorithm>

#include "Node.h"

class NormalNode : public Node						// Node is the base class, all public and
{													// protected members of Node can be accessed
public:												// by NormalNode

	NormalNode(){}

	NormalNode(int order, bool rootflag, Node* ancestor = nullptr);						// Overloaded constructor false = NormalNode
	~NormalNode(){}					                // destructor for a NormalNode

	//Definitions of Node class pure virtual functions
	Node* getChildNode(int iPos);	// Returns ptr using iPos as an index
	double getKey(int iPos);
	void print();											// Print for a NormalNode
	bool addItem(double iItem);					// Inserts an item to a NormalNode
    bool isOverloaded();
	bool isFull();
	void setAncestor(Node* newAncestor){ancestor = newAncestor;}
};
#endif
