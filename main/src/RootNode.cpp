#include "../header/RootNode.h"

RootNode::RootNode(BStarTree const * tree, Node* ancestor, unsigned id, unsigned height): Node(tree, ancestor)
{
    //keysList = std::list<double>(); //creates an empty list
    //childList = std::list<Node*>(); //creates an empty list
    this->id = id;
    this->height = height;
}

bool RootNode::isOverloaded() const
{
    return keysList.size() > tree->maxKeysRNode() ? true : false;
}

bool RootNode::isFull() const
{
    return keysList.size() == tree->maxKeysRNode() ? true : false;
}

bool RootNode::isUnderloaded() const
{
    return keysList.size() < tree->minKeysRNode() ? true : false;
}

bool RootNode::isAtMinimum() const
{
    return keysList.size() == tree->minKeysRNode() ? true : false;
}
