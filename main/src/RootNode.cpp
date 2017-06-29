#include "../header/RootNode.h"

RootNode::RootNode(BStarTree const * tree, Node* ancestor, unsigned id): Node(tree, ancestor)
{
    this->id = id;
}


bool RootNode::isOverloaded() const
{
    return this->keysList.size() > this->tree->maxKeysRNode() ? true : false;
}


bool RootNode::isFull() const
{
    return this->keysList.size() == this->tree->maxKeysRNode() ? true : false;
}


bool RootNode::isUnderloaded() const
{
    return this->keysList.size() < this->tree->minKeysRNode() ? true : false;
}


bool RootNode::isAtMinimum() const
{
    return this->keysList.size() == this->tree->minKeysRNode() ? true : false;
}
