//NormalNode.cpp
#include "../header/NormalNode.h"

/******************************************************************************
//  FUNCTION: Overloaded RootNode constructor
//  PURPOSE	: Creates and intializes a root node for a BStarTree.
//
//  CALL EXAMPLE: Node* ptrNode = new NormalNode(false);
//
//  PRE CONDITIONS:  Enough memory has to exist to create a NormalNode Object
//  POST CONDITIONS: Memory for a NormalNode object has been allocated and members intialized.
//******************************************************************************/
NormalNode::NormalNode(int order, bool rootflag, Node* ancestor): Node(order, rootflag, ancestor)
{
    const unsigned normalNodeOrder = ceil( (2*order-1) / 3 );

    keysList = std::list<double>(); //creates an empty list
    childList = std::list<Node*>(normalNodeOrder); //creates a list of keys with the minimum number of keys
}

bool NormalNode::addItem(double elem)
{
    this->keysList.push_back(elem);
    this->keyList.sort();
    return true;
}

Node* NormalNode::getNode(int iPos)
{
    auto it = childList.begin();
    std::advance(it, iPos);

    return *it;
}

//******************************************************************************
//  FUNCTION: Print
//  PURPOSE	: Prints all the data values except those of the Node*
//
//  CALL EXAMPLE: Node* ptrNode->Print()
//
//  PRE CONDITIONS:  NormalNode has to exist
//  POST CONDITIONS: Menber data printed to monitor
//******************************************************************************
void NormalNode::print()
{

}
