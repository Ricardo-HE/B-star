#ifndef BSTARTREE_H
#define BSTARTREE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <queue>

#include "Node.h"
#include "RootNode.h"
#include "NormalNode.h"

class BStarTree {

public:
    
    /**
        @brief Constructor of the BStarTree.
        @param order The order of the b-tree. This controls the maximum numbers of keys and
                children for each node. Minimum is 3.
    */
    BStarTree (int order): mOrder(order < 3 ? 3 : order), root(new RootNode(mOrder, true)) {}
    
    /**
        @brief Destructor of the BStarTree. Deallocates the memory
    */
    ~BStarTree();
    
    /**
        @brief Method to add an element to the tree.
        @pre The element must not be already in the tree.
        @param val The element to add to the tree.
        @return True if the element didn't exist previously in the tree and got added, false otherwise.
    */
    bool add(double val);
    
    /**
        @brief Method to delete an element to the tree.
        @pre The element must exist in the tree.
        @param val The element to deleten from the tree.
        @return True if the element existed previously in the tree and got deleted, false otherwise.
    */
    bool erase(double val);

    /**
        @param Method to find an element in the tree.
        @param val Element to look for in the tree.
        @return True if the element exists in the tree, false otherwise.
    */
    bool find(double val);

    /**
        @brief Method to add elements listed in a file.
        @pre The file must only contain elements to add to the tree and they must be separated by whitespace
                characters.
        @param filepath String with the filepath of the file with the elements to add.
        @return The number of elements added to the tree from the file.
    */
    unsigned addFromFile(std::string filepath);
    
    /**
        @brief Method to delete elements listed in a file.
        @pre The file must only contain elements to add to the tree and they must be separated by whitespace
                characters.
        @param filepath String with the filepath of the file with the elements to add.
        @return The number of elements added to the tree from the file.
    */
    unsigned deleteFromFile(std::string filepath);

    /**
        @brief Method to print, by levels, the nodes of the tree.
    */
    void print();
    
private:
    const int mOrder; //order of the tree
    Node* root;

    Node* findPlace(double val);
    Node* findPlaceDelete(double val);

    bool searchSpace(Node* nodeAdd);
    bool isLeftmost(Node* node) const;
    bool isRightmost(Node* node) const;

    bool areLeftSiblingsFull(Node* node) const;
    bool areRightSiblingsFull(Node* node) const;
    
    bool areLeftSiblingsAtMinimum(Node* node) const;
    bool areRightSiblingsAtMinimum(Node* node) const;

    bool rotateLeft(Node* node);
    bool rotateRight(Node* node);
    bool rotateLeftDelete(Node* node);
    bool rotateRightDelete(Node* node);

    void splitRoot();
    void splitLeft(Node* node);
    void splitRight(Node* node);

    Node* getLeftSibling(Node* node);
    Node* getRightSibling(Node* node);
};

bool compareKeyNodes(Node* nodeA, Node* nodeB);

#endif //BSTARTREE_H
