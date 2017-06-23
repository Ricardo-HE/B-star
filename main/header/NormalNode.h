#ifndef NORMALNODE_H
#define NORMALNODE_H

#include <cmath>
#include <iostream>
#include <algorithm>

#include "Node.h"

class NormalNode : public Node                      // Node is the base class, all public and
{                                                   // protected members of Node can be accessed
public:                                             // by NormalNode

    NormalNode(){}

    NormalNode(int order, bool rootflag, Node* ancestor = nullptr, unsigned id = 0, unsigned height = 0);                       // Overloaded constructor false = NormalNode
    ~NormalNode(){}                                 // destructor for a NormalNode

    //Definitions of Node class pure virtual functions
    Node* getChildNode(int iPos) const;   // Returns ptr using iPos as an index
    double getKey(int iPos) const;
    void print() const;                         // Print for a NormalNode
    bool addItem(double iItem);                 // Inserts an item to a NormalNode
    bool isOverloaded() const;
    bool isFull() const;
    bool isUnderloaded() const;
    bool isAtMinimum() const;
    void setAncestor(Node* newAncestor){ancestor = newAncestor;}

};
#endif
