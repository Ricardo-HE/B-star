#include "../header/NormalNode.h"

NormalNode::NormalNode(BStarTree const * tree, Node* ancestor, unsigned id, unsigned height): Node(tree, ancestor)
{
    //this might become handy later
    //const unsigned normalNodeOrder = ceil( (2*order-1) / 3 );
    this->id = id;
    this->height = height;
}

bool NormalNode::isOverloaded() const
{
    return keysList.size() > tree->maxKeysNNode() ? true : false;
}

bool NormalNode::isFull() const
{
    return keysList.size() == tree->maxKeysNNode() ? true : false;
}

bool NormalNode::isUnderloaded() const
{
    return keysList.size() < tree->minKeysNNode() ? true : false;
}

bool NormalNode::isAtMinimum() const
{
    return keysList.size() == tree->minKeysNNode() ? true : false;
}

