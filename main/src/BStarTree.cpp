#include "../header/BStarTree.h"
#include <stack>

bool BStarTree::add(double val)
{
    bool added;
    Node* nodeAdd = nullptr;    //Node where it will add the number if the number
                                //doesn't exist in the tree.

    if (find(val, nodeAdd)) {
        added = false;
    }else{
        nodeAdd->addItem(val);
        if (nodeAdd->isOverloaded()) {
            if (!nodeAdd->IsRoot()) {
                if (!this->searchSpace(nodeAdd)) {

                    if (!this->isLeftMost(nodeAdd)) {
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
    }

    return added;
}
/*
bool BStarTree::find(double val, Node* nodeAdd)
{
    bool found, keepSearching, goToRightMostChild;
    Node* currentNode;

    keepSearching = true;
    currentNode = this->root;
    nodeAdd = this->root;


    while (keepSearching) {
        goToRightMostChild = true;
        for (std::size_t i = 0; i < currentNode->getNumKeys(); i++) {
            if (val < currentNode->getKey(i)) {     //Compare the value with ith key of the node.
                nodeAdd = currentNode;
                currentNode = currentNode->getChildNode(i);      //If the value was lower than the ith key of the node
                                                    //the current node change to the left child of the
                                                    //ith key of the node.
                goToRightMostChild = false;
                break;
            }else{
                if (val == currentNode->getKey(i)) {
                    found = true;
                    keepSearching = false;
                    goToRightMostChild = false;
                    nodeAdd = nullptr;
                    break;
                }
            }
        }

        if (goToRightMostChild) {       //If val was higher than all the keys then we
                                        //change the current node to the rightmost child
            nodeAdd = currentNode;
            currentNode = currentNode->getChildNode( currentNode->getNumKeys() );
        }

        if (currentNode == nullptr) {
            found = false;
            keepSearching = false;
        }

    }
    return found;
}
*/
bool BStarTree::find(double val)
{
    Node* currentNode = root;
    bool found = false;
    bool childExists = true;
    std::list<Node*>::iterator child;

    while(!found && childExists){
        child = currentNode->getChildList().begin();
        for(auto key = currentNode->getKeysList().begin();
                *key > val && key != currentNode->getKeysList().end();
                ++key, ++child){

            if(*key == val){
                return false;
            }
            if(child == currentNode->getChildList().end()){
                childExists = false;
            }
        }
        if(childExists){
            currentNode = *child;
        }
    }

    return found;
}

Node* BStarTree::findPlace(double val)
{
    Node* currentNode = root;
    bool childExists = true;
    std::list<Node*>::iterator child;

    while(childExists){
        child = currentNode->getChildList().begin();

        for(auto key = currentNode->getKeysList().begin();
                key != currentNode->getKeysList().end();
                ++key, ++child){
            if(*key == val){ //exceptional case, the value already is in the tree
                return nullptr;
            }
            if(child == currentNode->getChildList().end()){
                childExists = false;
            }
        }

        if(childExists){
            //no child where the value should be exists so the current one is where the node should be put in
            currentNode = *child;
        }
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
    Node* ancestorCopy;
    int nodeNumberOfChild;
    bool isFull;

    ancestorCopy = node->getAncestor();
    auto it = ancestorCopy->getChildList().begin();
    nodeNumberOfChild = 0;
    isFull = true;

    for (; *it != node; it++, nodeNumberOfChild++)


    ancestorCopy = node->getAncestor();
    auto it = ancestorCopy->getChildList().begin();
    nodeNumberOfChild = 0;
    isFull = true;

    for (; *it != node; it++, nodeNumberOfChild++)


    ancestorCopy = node->getAncestor();
    auto it = ancestorCopy->getChildList().begin();
    nodeNumberOfChild = 0;
    isFull = true;

    for (; *it != node; it++, nodeNumberOfChild++)

    for (std::size_t i = nodeNumberOfChild -1 ; i <= 0; i--) {   //this iters from the
                                                            //left brothers of the node
                                                            //including the leftmost brother

bool BStarTree::areLeftSiblingsFull(Node* node) const
{
    Node* ancestorCopy;
    int nodeNumberOfChild;
    bool isFull;

    ancestorCopy = node->getAncestor();
    auto it = ancestorCopy->getChildList().begin();
    nodeNumberOfChild = 0;
    isFull = true;

    for (; *it != node; it++, nodeNumberOfChild++)

    for (std::size_t i = nodeNumberOfChild -1 ; i <= 0; i--) {   //this iters from the
                                                            //left brothers of the node
                                                            //including the leftmost brother
        if ( !(ancestorCopy->getChildNode(i))->isOverloaded() ) {
            isFull = false;
            break;
        }
    }
    return isFull;
}
bool BStarTree::areRightSiblingsFull(Node* node) const
{
    Node* ancestorCopy;
    int nodeNumberOfChild;
    bool isFull;

    ancestorCopy = node->getAncestor();
    auto it = ancestorCopy->getChildList().end();
    nodeNumberOfChild = ancestorCopy->getChildList().size() - 1;    //-1 because we are
                                                                    //our childList starts from 0
    isFull = true;

    for (; *it != node; it--, nodeNumberOfChild--)

    for (std::size_t i = nodeNumberOfChild +1 ; i < ancestorCopy->getChildList().size(); i++) {
                                                            //this iters from the
                                                            //right brothers of the node
                                                            //including the rightmost brother
        if ( !(ancestorCopy->getChildNode(i))->isOverloaded() ) {   //If some node brother
                                                                    //isn't full (Overloaded)
            isFull = false;
            break;
        }
    }
    return isFull;
}

bool BStarTree::isLeftMost(Node* node) const
{
    Node *ancestorCopy;
    bool isLeftMost;

    ancestorCopy = node->getAncestor();
    isLeftMost = false;
    if (ancestorCopy->getChildNode(0) == node) {
        isLeftMost = true;
    }

    return isLeftMost;
}

Node* BStarTree::getLeftSibling(Node* node)
{
    Node* ancestorCopy, *sibling;

    ancestorCopy = node->getAncestor();
    auto it = ancestorCopy->getChildList().begin();

    sibling = nullptr;


    for (; it != ancestorCopy->getChildList().end() && *it != node; it++)
    if (it != ancestorCopy->getChildList().begin()) {
        sibling = *(--it);
    }

    return sibling;
}

Node* BStarTree::getRightSibling(Node* node)
{
    Node* ancestorCopy, *sibling;


    ancestorCopy = node->getAncestor();
    sibling = nullptr;
    auto it = ancestorCopy->getChildList().rend();

    for (; it != ancestorCopy->getChildList().rbegin() && *it != node; it--)
    if (it != ancestorCopy->getChildList().rbegin()) {
        sibling = *(--it);
    }

    return sibling;
}

bool BStarTree::rotateLeft(Node* node)
{
    Node *currentNode, *ancestorCopy, *leftSiblingCopy, *childCopy;
    unsigned listIndex = 0;
    double parentKey;


    currentNode = node;
    do {
        ancestorCopy = currentNode->getAncestor();
        listIndex = 0;
        for(auto it = ancestorCopy->getChildList().begin(); *it != currentNode && it != ancestorCopy->getChildList().end(); ++it){
            ++listIndex;
        }
        //leftSiblingCopy = ancestorCopy->getChildNode(listIndex - 1);
        leftSiblingCopy = this->getLeftSibling(node);

        //key rotation
        parentKey = (*ancestorCopy)[listIndex-1];
        (*ancestorCopy)[listIndex-1] = currentNode->getKeysList().front();
        currentNode->getKeysList().pop_front();
        leftSiblingCopy->getKeysList().back() = parentKey;

        //child rotation
        if(currentNode->getChildList().front() != nullptr){
            childCopy = currentNode->getChildList().front();
            currentNode->getChildList().pop_front();
            dynamic_cast<NormalNode*>(childCopy)->setAncestor(leftSiblingCopy);
            leftSiblingCopy->getChildList().push_back(childCopy);
        }

        currentNode = leftSiblingCopy;
    } while(currentNode != nullptr && !currentNode->isOverloaded());

    return true;
}

bool BStarTree::rotateRight(Node* node)
{
    Node *currentNode, *ancestorCopy, *rightSiblingCopy, *childCopy;
    unsigned listIndex = 0;
    double parentKey;


    currentNode = node;
    do {
        ancestorCopy = currentNode->getAncestor();
        listIndex = 0;
        for(auto it = ancestorCopy->getChildList().begin(); *it != currentNode && it != ancestorCopy->getChildList().end(); ++it){
            ++listIndex;
        }
        //rightSiblingCopy = ancestorCopy->getChildNode(listIndex + 1);
        rightSiblingCopy = getRightSibling(node);

        //key rotation
        parentKey = (*ancestorCopy)[listIndex+1];
        (*ancestorCopy)[listIndex+1] = currentNode->getKeysList().back();
        currentNode->getKeysList().pop_back();
        rightSiblingCopy->getKeysList().front() = parentKey;

        //child rotation
        if(currentNode->getChildList().back() != nullptr){
            childCopy = currentNode->getChildList().back();
            currentNode->getChildList().pop_back();
            dynamic_cast<NormalNode*>(childCopy)->setAncestor(rightSiblingCopy);
            rightSiblingCopy->getChildList().push_front(childCopy);
        }

        currentNode = rightSiblingCopy;
    } while(currentNode != nullptr && !currentNode->isOverloaded());

    return true;
}

void BStarTree::splitRoot(){
    Node *child1, *child2;

    child1 = new NormalNode(mOrder, false, root);
    child2 = new NormalNode(mOrder, false, root);

    auto putKeys = [&](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->getKeysList().push_front( root->getKeysList().front() );
            root->getKeysList().pop_front();
        }
    };


    unsigned limitRoot = std::floor((2*mOrder - 2)/3) /*root->getKeysList().size()/2*/;

    putKeys(limitRoot, child1);

    double auxKey = root->getKeysList().front();
    root->getKeysList().pop_front();

    putKeys(limitRoot, child2);

    root->getKeysList().push_front(auxKey);
    //////////////////////////////////////////s///////////////////
    auto putChildren = [&](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->getChildList().push_front( root->getChildList().front() );
            root->getChildList().pop_front();
        }
    };
    Node *leftSibling, *ancestorCopy;
    double parentKey;
    unsigned listIndex;

    ancestorCopy = node->getAncestor();
    listIndex = 0;
    for(auto it = ancestorCopy->getChildList().begin(); *it != node && it != ancestorCopy->getChildList().end(); ++it){
        ++listIndex;
    }
    parentKey = (*ancestorCopy)[listIndex-1];
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestorCopy, &auxList](){
        ancestorCopy->getKeysList().push_front( auxList.front() );
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

    ancestorCopy->getKeysList().sort();
    ancestorCopy->getChildList().sort( compareKeyNodes );
}

/*
this split with the right sibling.
*/
void BStarTree::splitRight(Node* node)
{
    Node *rightSibling, *ancestorCopy;
    double parentKey;
    unsigned listIndex;

    ancestorCopy = node->getAncestor();
    listIndex = 0;
    for(auto it = ancestorCopy->getChildList().begin(); *it != node && it != ancestorCopy->getChildList().end(); ++it){
        ++listIndex;
    }
    parentKey = (*ancestorCopy)[listIndex-1];

    rightSibling = this->getRightSibling(node);

    std::list<double> auxList(std::move(rightSibling->getKeysList()));
    auxList.push_back(parentKey);

    auxList.merge(node->getKeysList());

    Node *newNode;

    newNode = new NormalNode(mOrder, false, ancestorCopy);

    ancestorCopy->getChildList().push_back(newNode);

    auto putKeys = [&](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->getKeysList().push_front( auxList.front() );
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestorCopy, &auxList](){
        ancestorCopy->getKeysList().push_front( auxList.front() );
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

    ancestorCopy->getKeysList().sort();
    ancestorCopy->getChildList().sort( compareKeyNodes );


}

bool compareKeyNodes(Node* nodeA, Node* nodeB)
{
	return (*nodeA)[0] < (*nodeB)[0];
}

void BStarTree::print(){
    Node* currentNode;
    std::queue<Node*> nodeQueue;

    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        currentNode = nodeQueue.front();
        nodeQueue.pop();

        currentNode->print();

        std::for_each(currentNode->getChildList().begin(),
                      currentNode->getChildList().end(),
                      [&](auto child){
            nodeQueue.push(child);
        });
    }

}
