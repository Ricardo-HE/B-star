#ifndef BSTARTREE_H
#define BSTARTREE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <functional>

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
    BStarTree (int order): mOrder(order < 3 ? 3 : order), id(1), root(new RootNode(mOrder, true, nullptr, id, 1)) {
        ++id;
    }

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
        @brief Method to erase an element to the tree.
        @pre The element must exist in the tree.
        @param val The element to erasen from the tree.
        @return True if the element existed previously in the tree and got erased, false otherwise.
    */
    bool erase(double val);

    /**
        @param Method to find an element in the tree.
        @param val Element to look for in the tree.
        @return True if the element exists in the tree, false otherwise.
    */
    bool find(double val) const;

    /**
        @brief Method to add elements listed in a file.
        @pre The file must only contain elements to add to the tree and they must be separated by whitespace
                characters.
        @param filepath String with the filepath of the file with the elements to add.
        @return The number of elements added to the tree from the file.
    */
    unsigned addFromFile(std::string filepath);

    /**
        @brief Method to erase elements listed in a file.
        @pre The file must only contain elements to add to the tree and they must be separated by whitespace
                characters.
        @param filepath String with the filepath of the file with the elements to add.
        @return The number of elements added to the tree from the file.
    */
    unsigned eraseFromFile(std::string filepath);

    /**
        @brief Method to print, by levels, the nodes of the tree.
    */
    void print() const;

    void generateFile(int size) const;

    void testAddAndDelete(std::string filepath, int elementsToLeave );

private:
    const int mOrder; //order of the tree
    unsigned id; //id of the next element of the tree.
    Node* root;

    void handleOverload(Node* overloadedNode);
    void handleUnderload(Node* underloadedNode);

    Node* findPlace(double val) const;
    Node* findPlaceErase(double val) const;

    bool searchSpace(Node* nodeAdd);
    bool searchSpaceErase(Node* nodeAdd);
    bool isLeftmost(Node* node) const;
    bool isRightmost(Node* node) const;

    bool areLeftSiblingsFull(Node* node) const;
    bool areRightSiblingsFull(Node* node) const;

    bool areLeftSiblingsAtMinimum(Node* node) const;
    bool areRightSiblingsAtMinimum(Node* node) const;


    /**
     * @brief Method to rotate a single time to the left, taking a key from the node
     *          putting it in its ancestor and moving the key of the ancestor to the
     *          left sibling of the node.
     * @pre The received node must not be the leftmost child of the ancestor.
     * @param node Node to take a key from and rotate it to the left.
     * @return An iterator pointing to the received node.
     */
    std::list<Node*>::iterator rotateLeft(Node* node);

    /**
     * @brief Method to rotate a single time to the right, taking a key from the node
     *          putting it in its ancestor and moving the key of the ancestor to the
     *          right sibling of the node.
     * @pre The received node must not be the rightmost child of the ancestor.
     * @param node Node to take a key from and rotate it to the right.
     * @return An iterator pointing to the received node.
     */
    std::list<Node*>::iterator rotateRight(Node* node);

    /**
     * @brief Method to rotate to the left as long as a node is overloaded.
     * @pre The received node must not be the leftmost child of the acestor.
     * @param node Node to start the rotations to the left. This one should be overloaded.
     * @return --
     */
    bool rotateLeftAdd(Node* node);

    /**
     * @brief Method to rotate to the right as long as a node is overloaded.
     * @pre The received node must not be the rightmost child of the acestor.
     * @param node Node to start the rotations to the right. This one should be overloaded.
     * @return --
     */
    bool rotateRightAdd(Node* node);

    /**
     * @brief Method to rotate to the right as long as a node is underloaded.
     * @pre The received node must not be the leftmost child of the acestor.
     * @param node Node to start the rotations to the right. This one should be underloaded.
     * @return --
     */
    bool rotateLeftErase(Node* node);

    /**
     * @brief Method to rotate to the left as long as a node is underloaded.
     * @pre The received node must not be the rightmost child of the acestor.
     * @param node Node to start the rotations to the left. This one should be overloaded.
     * @return --
     */
    bool rotateRightErase(Node* node);

    void splitRoot();
    void splitLeft(Node* node);
    void splitRight(Node* node);
    void mergeRoot();
    void merge(Node* node);
    void mergeLeft(Node* node);
    void mergeRight(Node* node);

    Node* getGreaterMinor(Node *node, double val) const;

    Node* getLeftSibling(Node* node) const;
    Node* getRightSibling(Node* node) const;

    std::list<Node*>::iterator getIterator(Node* node) const;
    std::list<Node*>::iterator getLeftSiblingIt(Node* node) const;
    std::list<Node*>::iterator getRightSiblingIt(Node* node) const;
};

bool compareKeyNodes(Node* nodeA, Node* nodeB);

#endif //BSTARTREE_H
