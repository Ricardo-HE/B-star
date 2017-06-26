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
    bool overloaded = false;

    if(keysList.size() > tree->maxKeysNNode()){
        overloaded = true;
    }

    return overloaded;
}

bool NormalNode::isFull() const
{
    bool full = false;

    if (keysList.size() == tree->maxKeysNNode()){
        full = true;
    }

    return full;
}

bool NormalNode::isUnderloaded() const
{
    bool underloaded = false;

    if (keysList.size() < tree->minKeysNNode()) {
        underloaded = true;
    }

    return underloaded;
}

bool NormalNode::isAtMinimum() const
{
    bool atMinimum = false;

    if (keysList.size() == tree->minKeysNNode()) {
        atMinimum = true;
    }

    return atMinimum;
}

