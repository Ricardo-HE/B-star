#include "../headers/BStarTree.h"

bool BStarTree::add(double val){
    bool found;
    Node* nodeAdd = nullptr;    //Node where it will add the number if the number
                                //doesn't exist in the tree.

    if (find(val, nodeAdd)) {
        found = true;
    }else{
        nodeAdd->AddItem(val);  //overcharge AddItem to add to the keys list and
                                //sort them
        if (nodeAdd->isOverloaded()) {  //make isOverloaded function

            if (this->isLeftSiblingsFull(nodeAdd)) {    //Make isLeftSiblingsFull

                if (this->isRightSiblingsFull(nodeAdd)) {   //Make isRightSiblingsFull
                    this->splitNode(nodeAdd);   //Make splitNode


                }else{
                    this->rotateRight(nodeAdd); //Make rotateRight;
                }
            }else{
                this->rotateLeft(nodeAdd);  //make rotateLeft
            }
        }
    }

    return found;
}

bool BStarTree::find(double val, Node* nodeAdd){
    bool found, keepSearching, goToRightMostChild;
    Node* currentNode;

    keepSearching = true;
    currentNode = this->root;

    while (keepSearching) {
        goToRightMostChild = true;
        for (std::size_t i = 0; i < currentNode.getNumKeys(); i++) {
            if (val < currentNode.getKey(i)) {     //Compare the value with ith key of the node.
                nodeAdd = currentNode;
                currentNode = getChildNode(i);      //If the value was lower than the ith key of the node
                                                    //the current node change to the left child of the
                                                    //ith key of the node.
                goToRightMostChild = false;
                break;
            }else{
                if (val == currentNode.getKey(i)) {
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
            currentNode = getChildNode( currentNode.getNumKeys() );
        }

        if (currentNode == nullptr) {
            found = false;
            keepSearching = false;
        }

    }
    return found;
}
