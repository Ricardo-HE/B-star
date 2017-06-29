#include "../header/Node.h"
#include "../header/NormalNode.h"

void Node::addItem(double elem)
{
    auto key = keys().begin();
    while(*key < elem && key != keys().end()){
        ++key;
    }

    keys().insert(key, elem);
}


void Node::addChild(Node* child)
{
    auto childIt = children().begin();
    while(compareKeyNodes(*childIt, child) && childIt != children().end()){
        ++childIt;
    }

    children().insert(childIt, child);
}



double Node::popFrontKey()
{
    double copy = keys().front();
    keys().pop_front();

    return copy;
}



double Node::popBackKey()
{
    double copy = keys().back();
    keys().pop_back();

    return copy;
}


Node* Node::popFrontChild()
{
    Node* copy = children().front();
    children().pop_front();

    return copy;
}


Node* Node::popBackChild()
{
    Node* copy = children().back();
    children().pop_back();

    return copy;
}


void Node::putKeys(std::list<double>& takeList, int limit)
{
    for(int i = 0; i < limit; i++){
        keys().push_back( takeList.front() );
        takeList.pop_front();
    }
}


void Node::putChildren(std::list<Node*>& takeList, int limit)
{
    for (int i = 0; i < limit; i++) {
        children().push_back( takeList.front() );
        takeList.pop_front();
        dynamic_cast<NormalNode*>(children().back())->setAncestor(this);
    }
}


void Node::print() const
{

    std::cout << "Id: " << this->id << " | ";
    this->ancestor != nullptr ? std::cout << this->ancestor->id : std::cout << ' ';
    std::cout << std::endl;

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
