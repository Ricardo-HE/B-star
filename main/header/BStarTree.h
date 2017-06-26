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
        @param filepath String with the filepath of the file with the elements to add. By
                default is "files/add.txt"
        @return The number of elements added to the tree from the file.
    */
    unsigned addFromFile(std::string filepath = "files/add.txt");

    /**
        @brief Method to erase elements listed in a file.
        @pre The file must only contain elements to add to the tree and they must be separated by whitespace
                characters.
        @param filepath String with the filepath of the file with the elements to erase. By
                default is "files/erase.txt"
        @return The number of elements added to the tree from the file.
    */
    unsigned eraseFromFile(std::string filepath = "files/erase.txt");

    /**
        @brief Method to print, by levels, the nodes of the tree.
    */
    void print() const;

    /**
     * @brief Generates a file with as many numbers as the received size, 10 by default and
     *          with the received filepath, by default "files/add.txt". The numbers are
     *          randomly generated from 0 to 9999.
     * @param size How many numbers to generate in the file.
     * @param filepath What is the filepath of the file to put the numbers in.
     */
    void generateFile(int size = 10, std::string filepath = "files/add.txt") const;

    /**
     * @brief Reads all the elements from the received file, adds them to the tree and then
     *          erases until leaving elementsToLeave in the tree.
     * @param elementsToLeave Number of elements to leave in the tree. By default 0.
     * @param filepath Filepath of the file where the elements to read are at. By default is
     *          "files/add.txt"
     */
    void testAddAndDelete(int elementsToLeave = 0, std::string filepath = "files/add.txt");

private:
    const int mOrder; //order of the tree
    unsigned id; //id of the next element of the tree.
    Node* root;

    /**
     * @brief When a node is overloaded, this handles it by either rotating or splitting.
     * @param overloadedNode Node which is overloaded.
     */
    void handleOverload(Node* overloadedNode);

    /**
     * @brief When a node is underloaded, this handles it by either rotating or splitting.
     * @param underloadedNode Node which is overloaded.
     */
    void handleUnderload(Node* underloadedNode);

    /**
     * @brief Gets the node where a new key should be inserted in.
     * @param val New key to insert in the tree.
     * @return Node where the new key should go or null if the key is already in the tree.
     */
    Node* findPlace(double val) const;

    /**
     * @brief Gets the node where there is the key to delete.
     * @param val Key to delete from the tree.
     * @return Node where the key is or null if the key is not already in the tree.
     */
    Node* findPlaceErase(double val) const;

    /**
     * @brief Checks if the siblings have free space and if they do, this rotates until no
     *          node is overloaded.
     * @param node Node which is overloaded and needs to find where to unload one of its keys.
     * @return True if some sibling had space and this rotated, leaving no node overloaded,
     *          false otherwise.
     */
    bool searchSpace(Node* node);

    /**
     * @brief Checks if the siblings don't have the minimum and if they do, this rotates until
     * no node is underloaded.
     * @param node Node which is overloaded and needs to find where to unload one of its keys.
     * @return True if some sibling had space and this rotated, leaving no node underloaded,
     *          false otherwise.
     */
    bool searchSpaceErase(Node* node);

    /**
     * @brief Checks if the node is the leftmost children of its ancestor.
     * @param node Node to check if its the leftmost.
     * @return True if the node is the leftmost children, false otherwise.
     */
    bool isLeftmost(Node* node) const;

    /**
     * @brief Checks if the node is the rightmost children of its ancestor.
     * @param node Node to check if its the rightmost.
     * @return True if the node is the rightmost children, false otherwise.
     */
    bool isRightmost(Node* node) const;

    /**
     * @brief Checks if all the left siblings of the node are full.
     * @param node Node whose left siblings are going to be checked.
     * @return True if all the left siblings are full, false otherwise.
     */
    bool areLeftSiblingsFull(Node* node) const;

    /**
     * @brief Checks if all the right siblings of the node are full.
     * @param node Node whose right siblings are going to be checked.
     * @return True if all the right siblings are full, false otherwise.
     */
    bool areRightSiblingsFull(Node* node) const;

    /**
     * @brief Checks if all the left siblings of the node are at their minimum.
     * @param node Node whose left siblings are going to be checked.
     * @return True if all the left siblings are at their minimum, false otherwise.
     */
    bool areLeftSiblingsAtMinimum(Node* node) const;

    /**
     * @brief Checks if all the right siblings of the node are at their minimum.
     * @param node Node whose right siblings are going to be checked.
     * @return True if all the right siblings are at their minimum, false otherwise.
     */
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

    /**
     * @brief Splits the root node, giving it a new children.
     */
    void splitRoot();

    /**
     * @brief Splits the node with its left node to divide their keys and make a third node.
     * @param node Node to split along with its left sibling.
     */
    void splitLeft(Node* node);

    /**
     * @brief Splits the node with its right node to divide their keys and make a third node.
     * @param node Node to split along with its right sibling.
     */
    void splitRight(Node* node);

    /**
     * @brief Method to merge a root node children with its siblings, or when there are only
     *          two, with its single sibling.
     * @param nodeChildren Children of the root to merge.
     */
    void mergeRootChildren(Node* nodeChildren);

    /**
     * @brief Merges a node along with its left and right siblings. In the case of the leftmost,
     *          it merges with its two right siblings and with the rightmost with its two left
     *          siblings.
     * @param node Node to merge with its two siblings.
     */
    void merge(Node* node);

    /**
     * @brief Gets the node which has the greater key of the left children of the key.
     * @param node Node to start looking for the children with the greater key.
     * @param val Key to know from what left sibling start the search.
     * @return The node with the greates key of the left siblings of the key or the received
     *          node.
     */
    Node* getGreaterMinor(Node *node, double val) const;

    /**
     * @brief Gets the left sibling of the node.
     * @param node Node whose left sibling you want to get.
     * @return The left sibling of the node.
     */
    Node* getLeftSibling(Node* node) const;

    /**
     * @brief Gets the right sibling of the node.
     * @param node Node whose right sibling you want to get.
     * @return The right sibling of the node.
     */
    Node* getRightSibling(Node* node) const;

    /**
     * @brief Gets the an iterator of the node. This won't work for the root node.
     * @param node Get an iterator pointing to this node.
     * @return Iterator pointing to the received node or undefined in the case of the root.
     */
    std::list<Node*>::iterator getIterator(Node* node) const;
};

/**
 * @brief Compares two nodes to see if the first one is smaller than the second one.
 * @param nodeA Node to check if it is the smaller one.
 * @param nodeB Node to check against nodeA if it is the bigger one.
 * @return True if nodeA is smaller than nodeB.
 */
bool compareKeyNodes(Node* nodeA, Node* nodeB);

#endif //BSTARTREE_H
