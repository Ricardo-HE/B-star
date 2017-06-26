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
    bool overloaded = false;

    if(keysList.size() > tree->maxKeysRNode()){
        overloaded = true;
    }

    return overloaded;
}

bool RootNode::isFull() const
{
    bool full = false;

    if (keysList.size() == tree->maxKeysRNode()) {
        full = true;
    }

    return full;
}

bool RootNode::isUnderloaded() const
{
    bool atMinimum = false;

    if (keysList.size() < tree->minKeysRNode()) {
        atMinimum = true;
    }

    return atMinimum;
}
bool RootNode::isAtMinimum() const
{
    bool atMinimum = false;

    if (keysList.size() == tree->minKeysRNode()) {
        atMinimum = true;
    }

    return atMinimum;
}

