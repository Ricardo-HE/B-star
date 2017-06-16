#include "../header/BStarTree.h"
#include <stack>

bool BStarTree::add(double val)
{
    bool added;
    Node* nodeAdd = nullptr;    //Node where it will add the number if the number
                                //doesn't exist in the tree.
    nodeAdd = findPlace(val);
    if (nodeAdd == nullptr) {
        return false;
    }
    nodeAdd->addItem(val);
    if (nodeAdd->isOverloaded()) {
        if (!nodeAdd->IsRoot()) {
            if (!this->searchSpace(nodeAdd)) {
                if (!this->isLeftmost(nodeAdd)) {
                    splitLeft(nodeAdd);    //This split every node with their left sibling
                }else{
                    splitRight(nodeAdd);   //This split the leftmost node with his right sibling
                                            //because he has no left sibling
                }
            }
        }else{
            splitRoot();
        }
    }
    added = true;

    return added;
}

bool BStarTree::find(double val)
{
    //remember to check if there is a more optimal way to do this
    return findPlace(val) != nullptr ? true : false;
}

//this search can be optimized because when searching a node there is no need to keep
//searching for a value once the values of the node are bigger than the searched value.
Node* BStarTree::findPlace(double val)
{
    Node* currentNode = root;
    std::list<Node*>::iterator child;


    while(!currentNode->children().empty()){
        child = currentNode->children().begin();
        for(auto key = currentNode->keys().begin();
                key != currentNode->keys().end();
                ++key){
            if(*key == val){ //exceptional case, the value already is in the tree
                return nullptr;
            }else if(*key < val){
                ++child;
            }
        }
        if(!currentNode->children().empty()){
            currentNode = *child;
        }
    }

    auto firstKey = currentNode->keys().begin();
    auto endKey = currentNode->keys().end();


    //search if the value to add is in the leaf node about to be returned
    if (std::find(firstKey, endKey, val) != endKey) {
        return nullptr;
    }

    return currentNode;
}

bool BStarTree::searchSpace(Node* node)
{
    Node* nodeCopy;
    bool foundSpace;

    foundSpace = true;
    nodeCopy = node;

    if (this->areLeftSiblingsFull(nodeCopy)){
        if (this->areRightSiblingsFull(nodeCopy)) {
            foundSpace = false;
        }else{
            this->rotateRight(nodeCopy);
        }
    }else{
        this->rotateLeft(nodeCopy);
    }

    return foundSpace;
}

bool BStarTree::areLeftSiblingsFull(Node* node) const
{
    Node* ancestor = node->getAncestor();
    bool nodeIsFull = true;

    //this checks all the nodes before the received one to see if at least one of them is
    //not full
    for(auto leftSibling = ancestor->children().begin(); *leftSibling != node;  ++leftSibling){
         if ( !(*leftSibling)->isFull() ) {
            nodeIsFull = false;
            break;
        }
    }

   return nodeIsFull;
}
bool BStarTree::areRightSiblingsFull(Node* node) const
{
    Node* ancestor = node->getAncestor();
    bool nodeIsFull = true;

    for(auto rightSibling = ancestor->children().rbegin(); *rightSibling != node; ++rightSibling){
         if ( !(*rightSibling)->isFull() ) {
            nodeIsFull = false;
            break;
        }
    }

    return nodeIsFull;
}

bool BStarTree::isLeftmost(Node* node) const
{
    return *node->getAncestor()->children().begin() ==  node ? true : false;
}

bool BStarTree::isRightmost(Node* node) const
{
    return *node->getAncestor()->children().rbegin() ==  node ? true : false;
}
Node* BStarTree::getLeftSibling(Node* node)
{
    Node* ancestor, *sibling;

    ancestor = node->getAncestor();

    sibling = nullptr;

    auto it = ancestor->children().begin();
    while(*it != node){
        ++it;
    }

    if (it != ancestor->children().begin()) {
        sibling = *prev(it);
    }

    return sibling;
}

Node* BStarTree::getRightSibling(Node* node)
{
    Node* ancestor, *sibling;

    ancestor = node->getAncestor();

    sibling = nullptr;

    auto it = ancestor->children().begin();
    while(*it != node){
        ++it;
    }

    if (it != prev(ancestor->children().end())) {
        sibling = *next(it);
    }

    return sibling;
}

bool BStarTree::rotateLeft(Node* node)
{
    Node *currentNode, *ancestor, *leftSibling, *child;
    std::list<double>::iterator ancestorKey;
    std::list<Node*>::iterator nodeIt;

    currentNode = node;
    do {
        ancestor = currentNode->getAncestor();
        ancestorKey = ancestor->keys().begin();
        for(nodeIt = next(ancestor->children().begin()); *nodeIt != currentNode; ++nodeIt){
            ++ancestorKey;
        }
        leftSibling = *prev(nodeIt);

        //key rotation
        leftSibling->keys().push_back(*ancestorKey);
        *ancestorKey = currentNode->keys().front();
        currentNode->keys().pop_front();

        //child rotation
        if(!currentNode->children().empty()){
            child = currentNode->children().front();
            currentNode->children().pop_front();
            dynamic_cast<NormalNode*>(child)->setAncestor(leftSibling);
            leftSibling->children().push_back(child);
        }

        currentNode = leftSibling;
    } while(!isLeftmost(currentNode) && currentNode->isOverloaded());

    return true;
}

bool BStarTree::rotateRight(Node* node)
{
    Node *currentNode, *ancestor, *rightSibling, *child;
    std::list<double>::iterator ancestorKey;
    std::list<Node*>::iterator nodeIt;

    currentNode = node;
    do {
        ancestor = currentNode->getAncestor();
        ancestorKey = ancestor->keys().begin();
        for(nodeIt = ancestor->children().begin(); *nodeIt != currentNode; ++nodeIt){
            ++ancestorKey;
        }
        rightSibling = *next(nodeIt);

        //key rotation
        rightSibling->keys().push_front(*ancestorKey);
        *ancestorKey = currentNode->keys().back();
        currentNode->keys().pop_back();

        //child rotation
        if(!currentNode->children().empty()){
            child = currentNode->children().back();
            currentNode->children().pop_back();
            dynamic_cast<NormalNode*>(child)->setAncestor(rightSibling);
            rightSibling->children().push_front(child);
        }

        currentNode = rightSibling;
    } while(!isRightmost(currentNode) && currentNode->isOverloaded());

    return true;
}
void BStarTree::splitRoot(){
    Node *child1, *child2;

    child1 = new NormalNode(mOrder, false, root);
    child2 = new NormalNode(mOrder, false, root);

    auto putKeys = [&](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->keys().push_back( root->keys().front() );
            root->keys().pop_front();
        }
    };


    unsigned limitRoot = std::floor((2*mOrder - 2)/3) /*root->keys().size()/2*/;
    putKeys(limitRoot, child1);

    double auxKey = root->keys().front();
    root->keys().pop_front();

    putKeys(limitRoot, child2);

    root->keys().push_front(auxKey);
    //////////////////////////////////////////s///////////////////
    //Review this lamnda
    ////////////////////////////////////////////
    auto putChildren = [&](unsigned limit, Node*& lNode){
        if(!root->children().empty()){
            for (std::size_t i = 0; i < limit; i++) {
                lNode->children().push_back( root->children().front() );
                root->children().pop_front();
            }
        }

    };
    //////////////////////////////////////////////////
    unsigned limitForChild1 = child1->keys().size() + 1;
    unsigned limitForChild2 = child2->keys().size() + 1;


    putChildren(limitForChild1, child1);
    putChildren(limitForChild2, child2);


    root->children().push_back(child1);
    root->children().push_back(child2);
}

void BStarTree::splitLeft(Node* node)
{
    Node *leftSibling, *ancestor;
    double ancestorKeyCopy;
    std::list<double>::iterator ancestorKey;
    std::list<Node*>::iterator nodeIt;

    ancestor = node->getAncestor();
    ancestorKey = ancestor->keys().begin();
    for(nodeIt = next(ancestor->children().begin()); *nodeIt != node; ++nodeIt){
        ++ancestorKey;
    }

    ancestorKeyCopy = *ancestorKey;
    ancestor->keys().erase(ancestorKey);

    leftSibling = *prev(nodeIt);

    //moves all the keys of the left sibling to an auxiliar list, leaving the sibling empty
    std::list<double> auxList(std::move(leftSibling->keys()));
    auxList.push_back(ancestorKeyCopy);
    //moves all the keys of the node to the auxiliar list, leaving the node empty
    auxList.merge(node->keys());

    Node *newNode; //new node that goes in the middle of the current node and its left sibling

    newNode = new NormalNode(mOrder, false, ancestor);

    ancestor->children().push_back(newNode);

    auto putKeys = [&auxList](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->keys().push_back( auxList.front() );
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestor, &auxList](){
        ancestor->keys().push_back( auxList.front() );
        auxList.pop_front();
    };

    unsigned limitOne = std::floor( (2*mOrder - 2)/3 );
    putKeys(limitOne, leftSibling);
    putKeyAncestor();

    unsigned limitTwo = std::floor( (2*mOrder - 1)/3 );
    putKeys(limitTwo, newNode);
    putKeyAncestor();

    unsigned limitThree = std::floor( 2*mOrder/3 );
    putKeys(limitThree, node);

    ancestor->keys().sort();
    ancestor->children().sort( compareKeyNodes );
}

/*
this split with the right sibling.
*/
void BStarTree::splitRight(Node* node)
{
    Node *rightSibling, *ancestor;
    double ancestorKeyCopy;
    std::list<double>::iterator ancestorKey;
    std::list<Node*>::iterator nodeIt;

    ancestor = node->getAncestor();
    ancestorKey = ancestor->keys().begin();
    for(nodeIt = ancestor->children().begin(); *nodeIt != node; ++nodeIt){
        ++ancestorKey;
    }

    ancestorKeyCopy = *ancestorKey;
    ancestor->keys().erase(ancestorKey);

    rightSibling = *next(nodeIt);

    //moves all the keys of the node to the auxiliar list, leaving the node empty
    std::list<double> auxList(std::move(node->keys()));
    auxList.push_back(ancestorKeyCopy);
    //moves all the keys of the right sibling to an auxiliar list, leaving the sibling empty
    auxList.merge(rightSibling->keys());

    Node *newNode; //new node that goes in the middle of the current node and its right sibling

    newNode = new NormalNode(mOrder, false, ancestor);

    ancestor->children().push_back(newNode);

    auto putKeys = [&auxList](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->keys().push_back( auxList.front() );
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestor, &auxList](){
        ancestor->keys().push_back( auxList.front() );
        auxList.pop_front();
    };

    unsigned limitOne = std::floor( (2*mOrder - 2)/3 );
    putKeys(limitOne, rightSibling);
    putKeyAncestor();

    unsigned limitTwo = std::floor( (2*mOrder - 1)/3 );
    putKeys(limitTwo, newNode);
    putKeyAncestor();

    unsigned limitThree = std::floor( 2*mOrder/3 );
    putKeys(limitThree, node);

    ancestor->keys().sort();
    ancestor->children().sort( compareKeyNodes );
}

void BStarTree::print()
{
    Node* currentNode;
    std::queue<Node*> nodeQueue;

    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        currentNode = nodeQueue.front();
        nodeQueue.pop();

        std::cout << "Current node's children: " << currentNode->children().size() << std::endl;
        currentNode->print();

        std::for_each(currentNode->children().begin(),
                      currentNode->children().end(),
                      [&nodeQueue](auto child){
            nodeQueue.push(child);
        });
    }

}

bool compareKeyNodes(Node* nodeA, Node* nodeB)
{
	return *nodeA->keys().begin() < *nodeB->keys().begin();
}
