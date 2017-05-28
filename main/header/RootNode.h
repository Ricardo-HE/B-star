//******************************************************************************
//				CLASS DECLARATION
//  CLASS NAME	:RootNode
//  PURPOSE	    :This is aderived class from the base class of Node.
//               Where an object of Node can never be created an object of
//               RootNode can.  Furthermore an object of RootNode can be
//               pointed to by a Node*:
//					 Node* nodePtr = new RootNode(true);   true == is a root.
//
//               THIS ROOTNODE IS DESIGNED FOR A BSTAR TREE.
//				 The root of a BStarTree is 2*(floor(2/3(NODE_ORDER - 1)) + 1 the order of all the other nodes in
//				 the tree. This is to facilitate a split from one node to two nodes
//				 both 2/3's full. This is different than all the NormalNodes.
//
//				 TheNormalNodes use the derived Node classes order (NODE_ORDER).
//				 It splits when 2 NormalNodes are full and splits them into 3 nodes 2/3 full.
//
//  DESCRIPTION	:The RootNode inherits the iOrder, number of items
//               stored, dynamically allocated memory for data storage, from the
//				 derived Node class. The RootNode statically allocates an array of
//				 Node* base on 2*(floor(2/3(NODE_ORDER - 1)) + 1;
//  METHODS:
//      Constructor -- intializes a RootNode object
//		void Print()  -- Currenty prints out contents of a node except the nodePtrs
//		bool AddItem() -- Does nothing right now.
//
//******************************************************************************
#ifndef ROOTNODE_H
#define ROOTNODE_H

#include "Node.h"
#include "NormalNode.h"


																// with an order of
																// NODE_ORDER (defined in Node.h)



class RootNode : public Node					  // Node is the base class, all public and
												  // protected members of Node can be accessed
												  // by RootNode
{
public:
	RootNode(){}
	RootNode(bool isRoot);						  // Overloaded constructor
	void print();								  // Print for a RootNode
	~RootNode(){}				  // destructor for a RootNode
	bool AddItem(int iItem);					  // Inserts an item to a root node

	Node getChildNode(int iPos);   // Returns the ptr using iPos as index

};

#endif
