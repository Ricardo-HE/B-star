#ifndef BSTARTREE_H
#define BSTARTREE_H

#include <iostream>     //std::cout, std::endl
#include <fstream>      //std::ofstream, std::ifstream
#include <cmath>        //floor, ceil
#include <algorithm>    //std::random_shuffle
#include <list>         //std::list
#include <queue>        //std::queue
#include <vector>       //std::vector

template <typename T>
class Node;

template <typename T>
class BStarTree
{

public:

    /**
        @brief Constructor of the BStarTree.
        @param order The order of the b-tree. This controls the maximum numbers of keys and
                children for each node. Minimum is 4.
    */
    BStarTree (int order);

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
    bool add(T val);

    /**
        @brief Method to erase an element to the tree.
        @pre The element must exist in the tree.
        @param val The element to erasen from the tree.
        @return True if the element existed previously in the tree and got erased, false otherwise.
    */
    bool erase(T val);

    /**
        @param Method to find an element in the tree.
        @param val Element to look for in the tree.
        @return True if the element exists in the tree, false otherwise.
    */
    bool find(T val) const;

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
     * @brief Reads all the elements from the received file, adds them to the tree and then
     *          randomly erases until leaving elementsToLeave in the tree.
     * @param elementsToLeave Number of elements to leave in the tree. By default 0.
     * @param filepath Filepath of the file where the elements to read are at. By default is
     *          "files/add.txt"
     */
    void addDelete(int elementsToLeave = 0, std::string filepath = "files/add.txt");

    //methods to get the constants for the nodes
    /**
     * @brief Gets the maximum number of keys for a normal node
     * @return Maximum number of keys for a normal node.
     */
    unsigned maxKeysNNode() const { return maxKeysNormalNode; }

    /**
     * @brief Gets the maximum number of keys for a root node
     * @return Maximum number of keys for a root node.
     */
    unsigned maxKeysRNode() const { return maxKeysRootNode; }

    /**
     * @brief Gets the minimum number of keys for a normal node
     * @return Minimum number of keys for a normal node.
     */
    unsigned minKeysNNode() const { return minKeysNormalNode; }

    /**
     * @brief Gets the minimum number of keys for a root node
     * @return Minimum number of keys for a root node.
     */
    unsigned minKeysRNode() const { return minKeysRootNode; }

    /**
     * @brief Gets the number of keys for the first children when splitting.
     * @return The number of keys for the first children when splitting.
     */
    unsigned getKeysSplitChild1() const { return keysSplitChild1; }

    /**
     * @brief Gets the number of keys for the second children when splitting.
     * @return The number of keys for the second children when splitting.
     */
    unsigned getKeysSplitChild2() const { return keysSplitChild2; }

    /**
     * @brief Gets the number of keys for the third children when splitting.
     * @return The number of keys for the third children when splitting.
     */
    unsigned getKeysSplitChild3() const { return keysSplitChild3; }

    //don't let users use the following
    BStarTree(BStarTree const &) = delete; //copy constructor
    BStarTree(BStarTree&&) = delete; //move constructor
    BStarTree& operator=(BStarTree const &) = delete; //copy assignment operator
    BStarTree& operator=(BStarTree&&) = delete; //move assignment operator

private:
    const int ORDER; //order of the tree
    unsigned id; //id of the next element of the tree.
    Node<T>* root;
    unsigned maxKeysNormalNode;
    unsigned maxKeysRootNode;
    unsigned minKeysNormalNode;
    unsigned minKeysRootNode;
    unsigned keysSplitChild1;
    unsigned keysSplitChild2;
    unsigned keysSplitChild3;


    /**
     * @brief When a node is overloaded, this handles it by either rotating or splitting.
     * @param overloadedNode Node which is overloaded.
     */
    void handleOverload(Node<T>* overloadedNode);

    /**
     * @brief When a node is underloaded, this handles it by either rotating or splitting.
     * @param underloadedNode Node which is overloaded.
     */
    void handleUnderload(Node<T>* underloadedNode);

    /**
     * @brief Finds wether or not a key exists in the tree, telling you if it does and with
     *          what node it was decided if it existed or not.
     * @param val Key to find if it exists in the tree.
     * @param node This will be overwritten with the last node that was needed to know if
     *          the key existed in the tree.
     * @return True if the key was found, false if not.
     */
    bool find(T val, Node<T>*& node) const;

    /**
     * @brief Gets the node where a new key should be inserted in.
     * @param val New key to insert in the tree.
     * @return Node where the new key should go or null if the key is already in the tree.
     */
    Node<T>* findPlaceAdd(T val) const;

    /**
     * @brief Gets the node where there is the key to delete.
     * @param val Key to delete from the tree.
     * @return Node where the key is or null if the key is not already in the tree.
     */
    Node<T>* findPlaceErase(T val) const;

    /**
     * @brief Checks if the siblings have free space and if they do, this rotates until no
     *          node is overloaded.
     * @param node Node which is overloaded and needs to find where to unload one of its keys.
     * @return True if some sibling had space and this rotated, leaving no node overloaded,
     *          false otherwise.
     */
    bool searchSpace(Node<T>* node);

    /**
     * @brief Checks if the siblings don't have the minimum and if they do, this rotates until
     * no node is underloaded.
     * @param node Node which is overloaded and needs to find where to unload one of its keys.
     * @return True if some sibling had space and this rotated, leaving no node underloaded,
     *          false otherwise.
     */
    bool searchSpaceErase(Node<T>* node);

    /**
     * @brief Checks if the node is the leftmost children of its ancestor.
     * @param node Node to check if its the leftmost.
     * @return True if the node is the leftmost children, false otherwise.
     */
    bool isLeftmost(Node<T>* node) const;

    /**
     * @brief Checks if the node is the rightmost children of its ancestor.
     * @param node Node to check if its the rightmost.
     * @return True if the node is the rightmost children, false otherwise.
     */
    bool isRightmost(Node<T>* node) const;

    /**
     * @brief Checks if all the left siblings of the node are full.
     * @param node Node whose left siblings are going to be checked.
     * @return True if all the left siblings are full, false otherwise.
     */
    bool areLeftSiblingsFull(Node<T>* node) const;

    /**
     * @brief Checks if all the right siblings of the node are full.
     * @param node Node whose right siblings are going to be checked.
     * @return True if all the right siblings are full, false otherwise.
     */
    bool areRightSiblingsFull(Node<T>* node) const;

    /**
     * @brief Checks if all the left siblings of the node are at their minimum.
     * @param node Node whose left siblings are going to be checked.
     * @return True if all the left siblings are at their minimum, false otherwise.
     */
    bool areLeftSiblingsAtMinimum(Node<T>* node) const;

    /**
     * @brief Checks if all the right siblings of the node are at their minimum.
     * @param node Node whose right siblings are going to be checked.
     * @return True if all the right siblings are at their minimum, false otherwise.
     */
    bool areRightSiblingsAtMinimum(Node<T>* node) const;

    /**
     * @brief Method to rotate a single time to the left, taking a key from the node
     *          putting it in its ancestor and moving the key of the ancestor to the
     *          left sibling of the node.
     * @pre The received node must not be the leftmost child of the ancestor.
     * @param node Node to take a key from and rotate it to the left.
     * @return An iterator pointing to the received node.
     */
    auto rotateLeft(Node<T>* node);

    /**
     * @brief Method to rotate a single time to the right, taking a key from the node
     *          putting it in its ancestor and moving the key of the ancestor to the
     *          right sibling of the node.
     * @pre The received node must not be the rightmost child of the ancestor.
     * @param node Node to take a key from and rotate it to the right.
     * @return An iterator pointing to the received node.
     */
    auto rotateRight(Node<T>* node);

    /**
     * @brief Method to rotate to the left as long as a node is overloaded.
     * @pre The received node must not be the leftmost child of the acestor.
     * @param node Node to start the rotations to the left. This one should be overloaded.
     */
    void rotateLeftAdd(Node<T>* node);

    /**
     * @brief Method to rotate to the right as long as a node is overloaded.
     * @pre The received node must not be the rightmost child of the acestor.
     * @param node Node to start the rotations to the right. This one should be overloaded.
     */
    void rotateRightAdd(Node<T>* node);

    /**
     * @brief Method to rotate to the right as long as a node is underloaded.
     * @pre The received node must not be the leftmost child of the acestor.
     * @param node Node to start the rotations to the right. This one should be underloaded.
     */
    void rotateLeftErase(Node<T>* node);

    /**
     * @brief Method to rotate to the left as long as a node is underloaded.
     * @pre The received node must not be the rightmost child of the acestor.
     * @param node Node to start the rotations to the left. This one should be overloaded.
     */
    void rotateRightErase(Node<T>* node);

    /**
     * @brief Splits the root node, giving it a new children.
     */
    void splitRoot();

    /**
     * @brief Splits the node with its left node to divide their keys and make a third node.
     * @param node Node to split along with its left sibling.
     */
    void splitLeft(Node<T>* node);

    /**
     * @brief Splits the node with its right node to divide their keys and make a third node.
     * @param node Node to split along with its right sibling.
     */
    void splitRight(Node<T>* node);

    /**
     * @brief Method to merge a root node children with its siblings, or when there are only
     *          two, with its single sibling.
     * @param nodeChildren Children of the root to merge.
     */
    void mergeRootChildren(Node<T>* nodeChildren);

    /**
     * @brief Merges a node along with its left and right siblings. In the case of the leftmost,
     *          it merges with its two right siblings and with the rightmost with its two left
     *          siblings.
     * @param node Node to merge with its two siblings.
     */
    void merge(Node<T>* node);

    /**
     * @brief Gets the node which has the greater key of the left children of the key.
     * @param node Node to start looking for the children with the greater key.
     * @param val Key to know from what left sibling start the search.
     * @return The node with the greates key of the left siblings of the key or the received
     *          node.
     */
    Node<T>* getGreaterMinor(Node<T>* node, T val) const;

    /**
     * @brief Gets the left sibling of the node.
     * @param node Node whose left sibling you want to get.
     * @return The left sibling of the node.
     */
    Node<T>* getLeftSibling(Node<T>* node) const;

    /**
     * @brief Gets the right sibling of the node.
     * @param node Node whose right sibling you want to get.
     * @return The right sibling of the node.
     */
    Node<T>* getRightSibling(Node<T>* node) const;

    /**
     * @brief Gets the an iterator of the node. This won't work for the root node.
     * @param node Get an iterator pointing to this node.
     * @return Iterator pointing to the received node or undefined in the case of the root.
     */
    auto getIterator(Node<T>* node) const;
};

#include "Node.h"       //Node
#include "NormalNode.h" //NormalNode
#include "RootNode.h"   //RootNode
#include "../src/BStarTree.cpp"

#endif //BSTARTREE_H
