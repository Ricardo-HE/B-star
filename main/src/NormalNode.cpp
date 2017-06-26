#include "../header/NormalNode.h"

NormalNode::NormalNode(int order, Node* ancestor, unsigned id, unsigned height): Node(order, ancestor)
{
    //this might become handy later
    //const unsigned normalNodeOrder = ceil( (2*order-1) / 3 );
    this->id = id;
    this->height = height;
}

bool NormalNode::isOverloaded() const
{
    bool overloaded = false;
    const unsigned MAX_SIZE = order - 1;

    if(keysList.size() > MAX_SIZE){
        overloaded = true;
    }

    return overloaded;
}

bool NormalNode::isFull() const
{
    bool full = false;

    const unsigned MAX_SIZE = order - 1;
    if (keysList.size() ==  MAX_SIZE) {
        full = true;
    }

    return full;
}

bool NormalNode::isUnderloaded() const
{
    bool underloaded = false;

    const unsigned MIN_SIZE = std::ceil( (2*order-1) / 3 ) - 1;
    if (keysList.size() <  MIN_SIZE) {
        underloaded = true;
    }

    return underloaded;
}

bool NormalNode::isAtMinimum() const
{
    bool atMinimum = false;

    const unsigned MIN_SIZE = std::ceil( (2*order-1)/3 ) - 1;
    if (keysList.size() ==  MIN_SIZE) {
        atMinimum = true;
    }

    return atMinimum;
}

