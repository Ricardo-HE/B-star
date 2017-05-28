#ifndef BSTARTREE_H
#define BSTARTREE_H

#include "Node.h"
#include "RootNode.h"

class BStarTree {
private:
    const int mOrder;
    Node* root;

public:
    BStarTree (int order): mOrder(order < 3 ? 3 : order), root(new RootNode(mOrder, true)) {}
    ~BStarTree ();
    bool add(double val);
    bool find(double val, Node* nodeAdd);

    bool isLeftSiblingFull(Node* node) const;
    bool isRightSiblingFull(Node* node) const;

    bool rotateLeft(Node* node);
    bool rotateRight(Node* node);

    void splitNode(Node* node);
    
    void prueba();
};

#endif //BSTARTREE_H
