#include "../header/RootNode.h"

//******************************************************************************
//  FUNCTION: Overloaded RootNode constructor
//  PURPOSE	: Creates and intializes a root node for a BStarTree whose order is 4/3 a Normal
//			  Node object.
//
//  CALL EXAMPLE: Node* ptrNode = new RootNode(true);
//
//  PRE CONDITIONS:  Enough memory has to exist to create a RootNode Object
//  POST CONDITIONS: Memory for a RootNode object has been allocated and members intialized.
//******************************************************************************
RootNode::RootNode(int order, bool rootflag, Node* ancestor): Node(order, rootflag, ancestor)
{
    const unsigned rootNodeOrder = 1;

    keysList = std::list<double>(); //creates an empty list
    childList = std::list<Node*>(rootNodeOrder); //creates a list of keys with the minimum number of keys
}

bool RootNode::addItem(double elem)
{
    this->keysList.push_back(elem);
    this->keysList.sort();
    return true;
}

Node* RootNode::getNode(int iPos)
{
    auto it = childList.begin();
    std::advance(it, iPos);

    return *it;
}
//******************************************************************************
//  FUNCTION: Print
//  PURPOSE	: Prints all the data values except those of the Node*
//
//  CALL EXAMPLE: ptrNode->Print();
//
//  PRE CONDITIONS:  RootNode has to exist
//  POST CONDITIONS: Menber data printed to monitor
//******************************************************************************
void RootNode::print()
{

}