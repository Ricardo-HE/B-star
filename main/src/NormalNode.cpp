#include "../header/NormalNode.h"

NormalNode::NormalNode(BStarTree const * tree, Node* ancestor, unsigned id): Node(tree, ancestor)
{
    this->id = id;
}


bool NormalNode::isOverloaded() const
{
    return this->keysList.size() > this->tree->maxKeysNNode() ? true : false;
}


bool NormalNode::isFull() const
{
    return this->keysList.size() == this->tree->maxKeysNNode() ? true : false;
}


bool NormalNode::isUnderloaded() const
{
    return this->keysList.size() < this->tree->minKeysNNode() ? true : false;
}


bool NormalNode::isAtMinimum() const
{
    return this->keysList.size() == this->tree->minKeysNNode() ? true : false;
}

