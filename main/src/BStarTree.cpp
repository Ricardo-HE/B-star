#include "../header/BStarTree.h"
#include <stack>

bool BStarTree::add(double val)
{
    bool found;
    Node* nodeAdd = nullptr;    //Node where it will add the number if the number
                                //doesn't exist in the tree.

    if (find(val, nodeAdd)) {
        found = true;
    }else{
        nodeAdd->addItem(val);
        if (nodeAdd->isOverloaded()) {
            this->searchSpace(nodeAdd);
        }
    }

    return found;
}

bool BStarTree::find(double val, Node* nodeAdd)
{
    bool found, keepSearching, goToRightMostChild;
    Node* currentNode;

    keepSearching = true;
    currentNode = this->root;

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

bool BStarTree::searchSpace(Node* node)
{
    Node* currentNode;
    std::stack<Node*> nodesStack;

    currentNode = node;
    nodesStack.push(currentNode);

    while (!nodesStack.empty()) {
        if (this->isLeftSiblingFull(currentNode)){
            if (this->isRightSiblingFull(currentNode)) {
                if (!(currentNode->getAncestor())->IsRoot()) {
                    currentNode = currentNode->getAncestor();
                    nodesStack.push(currentNode);
                }else{
                    //do something when the father is the root node
                    //Maybe empty the stack and return false and state that
                    //there is no space in the tree to give the new key so the
                    //node have split.
                }
            }else{
                currentNode = nodesStack.top();
                nodesStack.pop();
                this->rotateRight(currentNode); //Make rotateRight;
            }
        }else{
            currentNode = nodesStack.top();
            nodesStack.pop();
            this->rotateLeft(currentNode);  //make rotateLeft
        }

    }

    return false;
}

bool BStarTree::isLeftSiblingFull(Node* node) const
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
bool BStarTree::isRightSiblingFull(Node* node) const
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

bool BStarTree::rotateLeft(Node* node)
{

    return false;
}

bool BStarTree::rotateRight(Node* node)
{

    return false;
}

void BStarTree::splitNode(Node* node)
{

}
