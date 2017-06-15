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
    std::cout << val << " was added to the tree " << std::endl;
    if (nodeAdd->isOverloaded()) {
        if (!nodeAdd->IsRoot()) {
            if (!this->searchSpace(nodeAdd)) {
                std::cout << "Search space returned false" << std::endl;
                if (!this->isLeftMost(nodeAdd)) {
                    std::cout << "A node has to be splitted and it is not the leftmost" << std::endl;
                    splitLeft(nodeAdd);    //This split every node with their left sibling
                    std::cout << "A node was splitted using its left sibling" << std::endl;
                }else{

                    std::cout << "A node has to be splitted and it is not the rightmost" << std::endl;
                    splitRight(nodeAdd);   //This split the leftmost node with his right sibling
                                            //because he has no left sibling

                    std::cout << "A node was splitted using its right sibling" << std::endl;
                }
            }
        }else{
            splitRoot();
        }
    }
    added = true;

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
    //remember to check if there is a more optimal way to do this
    return findPlace(val) != nullptr ? true : false;
}

//this search can be optimized because when searching a node there is no need to keep
//searching for a value once the values of the node are bigger than the searched value.
Node* BStarTree::findPlace(double val)
{
    Node* currentNode = root;
    std::list<Node*>::iterator child;


    while(!currentNode->getChildList().empty()){
        child = currentNode->getChildList().begin();
        for(auto key = currentNode->getKeysList().begin();
                key != currentNode->getKeysList().end();
                ++key){
            if(*key == val){ //exceptional case, the value already is in the tree
                return nullptr;
            }else if(*key < val){
                ++child;
            }
        }
        if(!currentNode->getChildList().empty()){
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

    std::cout << "searching space" << '\n';
    if (this->areLeftSiblingsFull(nodeCopy)){
        std::cout << "Hermanos izquierdos llenos" << '\n';
        if (this->areRightSiblingsFull(nodeCopy)) {
            std::cout << "hermanos derechos llenos" << '\n';
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
    Node* ancestor;
    int nodeNumberOfChild;
    bool nodeIsFull;

    ancestor = node->getAncestor();
    auto it = ancestor->getChildList().begin();
    nodeNumberOfChild = 0;
    nodeIsFull = true;

    for (; *it != node; it++, nodeNumberOfChild++){}

    for (int i = nodeNumberOfChild-1; i >= 0; i--) {     //iterates from left sibling
                                                        //up to the leftmost sibling
        if ( !(ancestor->getChildNode(i)->isFull()) ) {
            nodeIsFull = false;
            break;
        }
    }

    if (nodeIsFull) {
        std::cout << "A node is full" << '\n';
    }else{
        std::cout << "A node is not full" << '\n';
    }
    return nodeIsFull;
}
bool BStarTree::areRightSiblingsFull(Node* node) const
{
    Node* ancestor;
    int nodeNumberOfChild;
    bool isFull;

    ancestor = node->getAncestor();
    auto it = ancestor->getChildList().end();
    nodeNumberOfChild = ancestor->getChildList().size() - 1;    //-1 because we are
                                                                    //our childList starts from 0
    isFull = true;

    for (; *it != node; it--, nodeNumberOfChild--){}

    for (std::size_t i = nodeNumberOfChild +1 ; i < ancestor->getChildList().size(); i++) {
                                                            //this iters from the
                                                            //right brothers of the node
                                                            //including the rightmost brother
        if ( !(ancestor->getChildNode(i))->isOverloaded() ) {   //If some node brother
                                                                    //isn't full (Overloaded)
            isFull = false;
            break;
        }
    }
    return isFull;
}

bool BStarTree::isLeftMost(Node* node) const
{
    Node *ancestor;
    bool isLeftMost;

    ancestor = node->getAncestor();
    isLeftMost = false;
    if (ancestor->getChildNode(0) == node) {
        isLeftMost = true;
    }

    return isLeftMost;
}

Node* BStarTree::getLeftSibling(Node* node)
{
    Node* ancestor, *sibling;

    ancestor = node->getAncestor();
    //std::list<Node*>::iterator it = ancestor->getChildList().begin();
    std::list<Node*>::iterator it;

    sibling = nullptr;

    //std::cout << "it: " << *it << " - - - " << '\n';
    for (it = ancestor->getChildList().begin(); it != ancestor->getChildList().end() && *it != node; it++){
        //std::cout << "++it: " << *it << '\n';
        //std::advance(it, 1);
        //std::cout << "begin: " << *(ancestor->getChildList().begin()) << '\n';
        //std::cout << "end: " << *(ancestor->getChildList().end()) << '\n';
    }

    if (it != ancestor->getChildList().begin()) {
        sibling = *(--it);
    }

    return sibling;
}

Node* BStarTree::getRightSibling(Node* node)
{
    Node* ancestor, *sibling;


    ancestor = node->getAncestor();
    sibling = nullptr;
    auto it = ancestor->getChildList().rend();

    for (; it != ancestor->getChildList().rbegin() && *it != node; it--)
    if (it != ancestor->getChildList().rbegin()) {
        sibling = *(--it);
    }

    return sibling;
}

bool BStarTree::rotateLeft(Node* node)
{
    Node *currentNode, *ancestor, *leftSibling, *child;
    unsigned listIndex = 0;
    double parentKey;


    currentNode = node;
    do {
        ancestor = currentNode->getAncestor();
        listIndex = 0;
        for(auto it = ancestor->getChildList().begin(); *it != currentNode && it != ancestor->getChildList().end(); ++it){
            ++listIndex;
        }
        //leftSibling = ancestor->getChildNode(listIndex - 1);
        leftSibling = this->getLeftSibling(node);


        //key rotation
        parentKey = (*ancestor)[listIndex-1];
        (*ancestor)[listIndex-1] = currentNode->getKeysList().front();
        currentNode->getKeysList().pop_front();
        leftSibling->getKeysList().push_back(parentKey);

        //child rotation
        if(!currentNode->getChildList().empty()){
            child = currentNode->getChildList().front();
            currentNode->getChildList().pop_front();
            dynamic_cast<NormalNode*>(child)->setAncestor(leftSibling);
            leftSibling->getChildList().push_back(child);
        }

        currentNode = leftSibling;
    } while(currentNode != nullptr && currentNode->isOverloaded());

    return true;
}

bool BStarTree::rotateRight(Node* node)
{
    Node *currentNode, *ancestor, *rightSibling, *child;
    unsigned listIndex = 0;
    double parentKey;


    currentNode = node;
    do {
        ancestor = currentNode->getAncestor();
        listIndex = 0;
        for(auto it = ancestor->getChildList().begin(); *it != currentNode && it != ancestor->getChildList().end(); ++it){
            ++listIndex;
        }
        //rightSibling = ancestor->getChildNode(listIndex + 1);
        rightSibling = getRightSibling(node);

        //key rotation
        parentKey = (*ancestor)[listIndex+1];
        (*ancestor)[listIndex+1] = currentNode->getKeysList().back();
        currentNode->getKeysList().pop_back();
        rightSibling->getKeysList().push_front(parentKey);

        //child rotation
        if(!currentNode->getChildList().empty()){
            child = currentNode->getChildList().back();
            currentNode->getChildList().pop_back();
            dynamic_cast<NormalNode*>(child)->setAncestor(rightSibling);
            rightSibling->getChildList().push_front(child);
        }

        currentNode = rightSibling;
    } while(currentNode != nullptr && !currentNode->isOverloaded());

    return true;
}

void BStarTree::splitRoot(){
    std::cout << "Splitting the root!" << std::endl << std::endl;
    Node *child1, *child2;

    child1 = new NormalNode(mOrder, false, root);
    child2 = new NormalNode(mOrder, false, root);

    auto putKeys = [&](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->getKeysList().push_back( root->getKeysList().front() );
            root->getKeysList().pop_front();
        }
    };


    unsigned limitRoot = std::floor((2*mOrder - 2)/3) /*root->getKeysList().size()/2*/;
    std::cout << "Number of keys to give to the children when the root splits: " << limitRoot << std::endl;
    putKeys(limitRoot, child1);

    double auxKey = root->getKeysList().front();
    root->getKeysList().pop_front();

    putKeys(limitRoot, child2);

    root->getKeysList().push_front(auxKey);
    //////////////////////////////////////////s///////////////////
    //Review this lamnda
    ////////////////////////////////////////////
    auto putChildren = [&](unsigned limit, Node*& lNode){
        if(!root->getChildList().empty()){
            for (std::size_t i = 0; i < limit; i++) {
                lNode->getChildList().push_back( root->getChildList().front() );
                root->getChildList().pop_front();
            }
        }

    };
    //////////////////////////////////////////////////
    unsigned limitForChild1 = child1->getKeysList().size() + 1;
    unsigned limitForChild2 = child2->getKeysList().size() + 1;

    std::cout << "Maximum number of children for the first child " << limitForChild1 << std::endl;
    std::cout << "Maximum number of children for the first child " << limitForChild1 << std::endl;

    putChildren(limitForChild1, child1);
    putChildren(limitForChild2, child2);


    root->getChildList().push_back(child1);
    root->getChildList().push_back(child2);

    std::cout << "Printing the new root: " << std::endl;
    root->print();
}

void BStarTree::splitLeft(Node* node)
{
    std::cout << "Splitting this node along with its left sibling: " << std::endl;
    node->print();

    Node *leftSibling, *ancestor;
    double parentKey;
    unsigned listIndex; //this is the index of the node in the list of children of its ancestor

    ancestor = node->getAncestor();
    listIndex = 0;
    for(auto it = ancestor->children().begin();
            *it != node && it != ancestor->children().end();
            ++it){
        ++listIndex;
    }
    parentKey = (*ancestor)[listIndex-1];

    leftSibling = this->getLeftSibling(node);

    //moves all the keys of the left sibling to an auxiliar list, leaving the sibling empty
    std::list<double> auxList(std::move(leftSibling->getKeysList()));
    auxList.push_back(parentKey);
    //moves all the keys of the node to the auxiliar list, leaving the node empty
    auxList.merge(node->getKeysList());

    Node *newNode; //new node that goes in the middle of the current node and its left sibling

    newNode = new NormalNode(mOrder, false, ancestor);

    ancestor->getChildList().push_back(newNode);

    auto putKeys = [&auxList](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->getKeysList().push_back( auxList.front() );
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestor, &auxList](){
        ancestor->getKeysList().push_back( auxList.front() );
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

    ancestor->getKeysList().sort();
    ancestor->getChildList().sort( compareKeyNodes );
}

/*
this split with the right sibling.
*/
void BStarTree::splitRight(Node* node)
{
    Node *rightSibling, *ancestor;
    double parentKey;
    unsigned listIndex;

    ancestor = node->getAncestor();
    listIndex = 0;
    for(auto it = ancestor->getChildList().begin(); *it != node && it != ancestor->getChildList().end(); ++it){
        ++listIndex;
    }
    parentKey = (*ancestor)[listIndex-1];

    rightSibling = this->getRightSibling(node);

    std::list<double> auxList(std::move(rightSibling->getKeysList()));
    auxList.push_back(parentKey);

    auxList.merge(node->getKeysList());

    Node *newNode;

    newNode = new NormalNode(mOrder, false, ancestor);

    ancestor->getChildList().push_back(newNode);

    auto putKeys = [&](unsigned limit, Node*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->getKeysList().push_front( auxList.front() );
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestor, &auxList](){
        ancestor->getKeysList().push_front( auxList.front() );
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

    ancestor->getKeysList().sort();
    ancestor->getChildList().sort( compareKeyNodes );


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

        std::cout << "currentNode childs: " << currentNode->getChildList().size() << '\n';
        currentNode->print();

        std::for_each(currentNode->getChildList().begin(),
                      currentNode->getChildList().end(),
                      [&](auto child){
            nodeQueue.push(child);
        });
    }

}
