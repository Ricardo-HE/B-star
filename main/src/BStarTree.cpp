#include "../headers/BStarTree.h"

bool BStarTree::add(double val){
    bool found;

    if (find(val)) {
        found = true;
    }else{
        //finish later
    }

    return found;
}

bool BStarTree::find(double val){
    bool found, keepSearching, goToRightMostChild;
    Node* currentNode;

    keepSearching = true;
    currentNode = this->root;

    while (keepSearching) {
        goToRightMostChild = true;
        for (std::size_t i = 0; i < currentNode.getNumKeys(); i++) {
            if (val < currentNode.getKey(i)) {     //Compare the value with ith key of the node.
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
                    break;
                }
            }
        }

        if (goToRightMostChild) {       //If val was higher than all the keys then we
                                //change the current node to the rightmost child
            currentNode = getChildNode( currentNode.getNumKeys() );
        }

        if (currentNode == nullptr) {
            found = false;
            keepSearching = false;
        }

    }
    return found;
}
