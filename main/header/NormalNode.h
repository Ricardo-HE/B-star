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

	NormalNode(int order, bool rootflag, Node* ancestor = nullptr, unsigned id = 0, unsigned height = 0);						// Overloaded constructor false = NormalNode
	~NormalNode(){}					                // destructor for a NormalNode

	//Definitions of Node class pure virtual functions
	Node* getChildNode(int iPos);	// Returns ptr using iPos as an index
	double getKey(int iPos);
	void print();											// Print for a NormalNode
	bool addItem(double iItem);					// Inserts an item to a NormalNode
    bool isOverloaded();
	bool isFull();
	bool isUnderloaded();
	bool isAtMinimum();
	void setAncestor(Node* newAncestor){ancestor = newAncestor;}

};
#endif
