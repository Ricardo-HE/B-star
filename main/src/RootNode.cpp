#include "../header/RootNode.h"

RootNode::RootNode(int order, Node* ancestor, unsigned id, unsigned height): Node(order, ancestor)
{
    //keysList = std::list<double>(); //creates an empty list
    //childList = std::list<Node*>(); //creates an empty list
    this->id = id;
    this->height = height;
}

bool RootNode::isOverloaded() const
{
    bool overloaded = false;
    const unsigned MAX_SIZE = 2 * floor( (2*order - 2) / 3 );

    if(keysList.size() > MAX_SIZE){
        overloaded = true;
    }

    return overloaded;
}

bool RootNode::isFull() const
{
    bool full = false;

    const unsigned MAX_SIZE = 2 * floor( (2*order - 2) / 3 );
    if (keysList.size() ==  MAX_SIZE) {
        full = true;
    }

    return full;
}

bool RootNode::isUnderloaded() const
{
    bool atMinimum = false;

    const unsigned MIN_SIZE = 1;
    if (keysList.size() < MIN_SIZE) {
        atMinimum = true;
    }

    return atMinimum;
}
bool RootNode::isAtMinimum() const
{
    bool atMinimum = false;

    const unsigned MIN_SIZE = 1;
    if (keysList.size() == MIN_SIZE) {
        atMinimum = true;
    }

    return atMinimum;
}

