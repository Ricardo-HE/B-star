//NormalNode.cpp
#include "../header/NormalNode.h"

NormalNode::NormalNode(int order, bool rootflag, Node* ancestor): Node(order, rootflag, ancestor)
{
    //this might become handy later
    //const unsigned normalNodeOrder = ceil( (2*order-1) / 3 );

    keysList = std::list<double>(); //creates an empty list
    childList = std::list<Node*>(); //creates an empty list
}

bool NormalNode::addItem(double elem)
{
    this->keysList.push_back(elem);
    this->keysList.sort();
    return true;
}

Node* NormalNode::getChildNode(int iPos)
{
    auto it = childList.begin();
    std::advance(it, iPos);

    return *it;
}

double NormalNode::getKey(int iPos)
{
    auto it = keysList.begin();
    std::advance(it, iPos);

    return *it;
}

bool NormalNode::isOverloaded()
{
    bool overloaded = false;
    const unsigned MAX_SIZE = order - 1;

    if(keysList.size() > MAX_SIZE){
        overloaded = true;
    }

    return overloaded;
}

bool NormalNode::isFull(){
    bool full = false;

    const unsigned MAX_SIZE = order - 1;
    if (keysList.size() ==  MAX_SIZE) {
        full = true;
    }
}

void NormalNode::print()
{
    std::cout << "keys: ";

    std::for_each(keysList.begin(), keysList.end(), [](auto key){
        std::cout << key << " ";
    });

    std::cout << '\n' << std::endl;
}
