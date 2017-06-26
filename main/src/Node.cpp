#include "../header/Node.h"

void Node::addItem(double elem)
{
    std::list<double>::iterator key = keys().begin();
    while(*key < elem && key != keys().end()){
        ++key;
    }

    keys().insert(key, elem);
}

void Node::addChild(Node* child)
{
    std::list<Node*>::iterator childIt = children().begin();
    while(compareKeyNodes(*childIt, child) && childIt != children().end()){
        ++childIt;
    }

    children().insert(childIt, child);
}

void Node::print() const
{

    std::cout << "keys: ";

    for(auto key : keysList){
        std::cout << key << " ";
    }

    std::cout <<  "\n\n";
}

bool compareKeyNodes(Node* nodeA, Node* nodeB)
{
    return *nodeA->keys().begin() < *nodeB->keys().begin();
}
