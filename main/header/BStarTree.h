#ifndef BSTARTREE_H
#define BSTARTREE_H

class BStarTree {
private:
    const int mOrder;
    Node* root;

public:
    BStarTree (int order): mOrder(order < 3 ? 3 : order), root(new RootNode(mOrder, true)) {}
    ~BStarTree ();
    bool add(double val);
    bool search(double val, Node* nodeAdd);
};

#endif //BSTARTREE_H
