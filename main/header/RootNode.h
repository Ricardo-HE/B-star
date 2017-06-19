#ifndef ROOTNODE_H
#define ROOTNODE_H

#include <iostream>
#include <algorithm>

#include "Node.h"
#include "NormalNode.h"

class RootNode : public Node					  // Node is the base class, all public and
												  // protected members of Node can be accessed
												  // by RootNode
{
public:
    RootNode(){}
    RootNode(int order, bool rootflag, Node* ancestor = nullptr, unsigned id = 0, unsigned height = 0);  // Overloaded constructor
    void print();								  // Print for a RootNode
    ~RootNode(){}				  // destructor for a RootNode
    bool addItem(double iItem);					  // Inserts an item to a root node

    Node* getChildNode(int iPos);   // Returns the ptr using iPos as index
    double getKey(int iPos);
    bool isOverloaded();
    bool isFull();
    bool isUnderloaded();
    bool isAtMinimum();
};

#endif
