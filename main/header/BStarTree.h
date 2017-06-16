#ifndef BSTARTREE_H
#define BSTARTREE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>

#include "Node.h"
#include "RootNode.h"
#include "NormalNode.h"


class BStarTree {
private:
    const int mOrder;
    Node* root;

public:
    BStarTree (int order): mOrder(order < 3 ? 3 : order), root(new RootNode(mOrder, true)) {}
    //  ~BStarTree (){};
    bool add(double val);
    //bool find(double val, Node* nodeAdd);

    bool find(double val);
    Node* findPlace(double val);

    bool searchSpace(Node* nodeAdd);
    bool isLeftmost(Node* node) const;
    bool isRightmost(Node* node) const;

    bool areLeftSiblingsFull(Node* node) const;
    bool areRightSiblingsFull(Node* node) const;

    bool rotateLeft(Node* node);
    bool rotateRight(Node* node);

    void splitRoot();
    void splitLeft(Node* node);
    void splitRight(Node* node);

    Node* getLeftSibling(Node* node);
    Node* getRightSibling(Node* node);

    void print();


};

bool compareKeyNodes(Node* nodeA, Node* nodeB);

//Functions to compare two nodes for equality or inequality. This functions assume that two
//nodes will never have the same keys at the same time.
bool areEqual(Node* nodeA, Node* nodeB);
bool areNotEqual(Node* nodeA, Node* nodeB);

#endif //BSTARTREE_H
