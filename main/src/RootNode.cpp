#include "../header/RootNode.h"

RootNode::RootNode(int order, bool rootflag, Node* ancestor): Node(order, rootflag, ancestor)
{
    //keysList = std::list<double>(); //creates an empty list
    //childList = std::list<Node*>(); //creates an empty list
}

bool RootNode::addItem(double elem)
{
    this->keysList.push_back(elem);
    this->keysList.sort();
    return true;
}

Node* RootNode::getChildNode(int iPos)
{
    auto it = childList.begin();
    std::advance(it, iPos);

    return *it;
}

double RootNode::getKey(int iPos)
{
    auto it = keysList.begin();
    std::advance(it, iPos);

    return *it;
}

bool RootNode::isOverloaded()
{
    bool overloaded = false;
    const unsigned MAX_SIZE = 2 * floor( (2*order - 2) / 3 );

    if(keysList.size() > MAX_SIZE){
        overloaded = true;
    }

    return overloaded;
}

bool RootNode::isFull()
{
    bool full = false;

    const unsigned MAX_SIZE = 2 * floor( (2*order - 2) / 3 );
    if (keysList.size() ==  MAX_SIZE) {
        full = true;
    }

    return full;
}

bool RootNode::isUnderloaded()
{
    bool atMinimum = false;
    
    const unsigned MIN_SIZE = 1;
    if (keysList.size() < MIN_SIZE) {
        atMinimum = true;
    }

    return atMinimum;
}
bool RootNode::isAtMinimum()
{
    bool atMinimum = false;
    
    const unsigned MIN_SIZE = 1;
    if (keysList.size() == MIN_SIZE) {
        atMinimum = true;
    }

    return atMinimum;
}

void RootNode::print()
{

    std::cout << "keys: ";

    std::for_each(keysList.begin(), keysList.end(), [](auto key){
        std::cout << key << " ";
    });

    std::cout <<  "\n\n";
}
