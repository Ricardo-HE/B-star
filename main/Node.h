//File Name:
//Programmer:
//Section:
//******************************************************************************
//				CLASS DECLARATION
//  CLASS NAME	:Node
//  PURPOSE	    :This is an abstract node class which is the base class
//               for a RootNode class and a NormalNode class. An object of type
//               Node cannot ever be declared. However any class that
//               uses node as a base class can be pointed to be a Node* pointer.
//
//  DESCRIPTION	:The node keeps track of its particular iOrder, number of items
//               stored, dynamically allocated memory for data storage, whether
//               it is a root or normal node.
//  METHODS:
//      Constructor -- sets up iOrder, bisRoot, and iNumInNode before constructor called
//		virtual void Print() = 0; -- pure abastract function; code is written by derived class
//		virtual bool AddItem = 0; -- pure abstract function; code is written by derived class
//
//******************************************************************************
#ifndef NODE_H
#define NODE_H

//#include "fstream.h"
#include <cstdlib>
#include <cmath>

const int NODE_ORDER = 9;           // The order of a Node inheriting this class

class Node
{
public:
	Node(){};
	Node(int order, bool rootflag, int howMany =0):iOrder(order), bIsRoot(rootflag),iNumInNode(0){}

	//Pure virtual function
	virtual void Print() = 0;
	virtual bool AddItem(int iItem) = 0;
	virtual Node* GetNodePtrs(int iPos) = 0;

	//Access Functions

	int GetOrder(){return iOrder;}
	int GetNumInNode(){return iNumInNode;}
	int* GetIntStore(){return piStore;}
	bool IsRoot(){return bIsRoot;}


	~Node(){};


protected:
	int	  iOrder;             // Order of this node
	int   iNumInNode;		  // Number of data in this node
	int*  piStore;			  // Pointer for allocating dynamic memory store
	bool  bIsRoot;			  // Tracks if root or not.

};

#endif
