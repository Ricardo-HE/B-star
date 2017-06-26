#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>

#include "BStarTree.h"

class Node
{
public:

    /**
    * @brief Constructor with parameters to initialize the variables from the class.
    * @param tree Constant reference to the tree where the node is going to be.
    * @ancestor This tells the node what node is its ancestor.
    */
    Node(BStarTree const & tree, Node* ancestor = nullptr):tree(tree), ancestor(ancestor) {}

    /**
    *@brief Virtual destructor
    */
    virtual ~Node() {}


    //******************Pure virtual function***********************************
    /**
     * @brief Tells you if the node has more keys than permited. This means it has to split.
     * @return True if the node is overloaded, false otherwise.
     */
    virtual bool isOverloaded() const = 0;

    /**
     * @brief Tells you if the node has as many keys as permited. One more and it will be overloaded.
     * @return True if the node is full, false otherwise.
     */
    virtual bool isFull() const = 0;

    /**
     * @brief Tells you if the node has less keys than permited. This means it has to merge.
     * @return True if the node is underloaded, false otherwise.
     */
    virtual bool isUnderloaded() const = 0;

    /**
     * @brief Tells you if the node has as many keys as permited. One less and it will be underloade.
     * @return True if the node is at its minimum, false otherwise.
     */
    virtual bool isAtMinimum() const = 0;

    /**
    *@brief Says if the node is root or not.
    *@return True if the node is root, false if isn't.
    */
    virtual bool isRoot() const = 0;

    //************************Access Functions**********************************

    /**
    * @brief print the node's information such like the keys of the node, father's ID
    * and child's ID.
    */
    void print() const;

    /**
    * @brief Add a key to the Node's array list of keys.
    * @param item Element to add to the node.
    */
    void addItem(double item);

    /**
     * @brief Adds a child to the Node's list of children.
     * @param child Child to add to the list.
     */
    void addChild(Node* child);

    /**
     * @brief Gets the Id of the node.
     * @return The id of the node.
     */
    unsigned getId() const { return id; }

    /**
     * @brief Gets the height of the node.
     * @return The height of the node.
     */
    unsigned getHeight() const { return height; }

    /**
    *@brief Get the current size of the list of keys in the node.
    *@ The current size of the list of keys in the node.
    */
    std::size_t getNumKeys() const { return keysList.size(); }

    /**
     * @brief Tells you the ancestor of the node.
     * @return The ancestor of the node. It might be null.
     */
    Node* getAncestor() const { return ancestor; }

    /**
    *@brief Get the list of keys from the node.
    *@return The list of keys from the node.
    */
    std::list<double>& keys() { return keysList; }

    /**
    *@brief Get the list of childs from the node.
    *@return The list of keys from the node.
    */
    std::list<Node*>& children() { return childList; }

    /**
     * @brief Tells you whether the node is a leaf or not.
     * @return True if the node is a leaf, false otherwise.
     */
    bool isLeaf() { return this->children().empty(); }

protected:
    unsigned id; //id to identify nodes
    unsigned height; //height in the tree. The root is 0 and each children is ancestor+1
    BStarTree const & tree; //reference to the tree
    std::list<double> keysList;     // Pointer for allocating dynamic memory store
    std::list<Node*> childList;
    Node* ancestor;

};

/**
 * @brief Compares two nodes to see if the first one is smaller than the second one.
 * @param nodeA Node to check if it is the smaller one.
 * @param nodeB Node to check against nodeA if it is the bigger one.
 * @return True if nodeA is smaller than nodeB.
 */
bool compareKeyNodes(Node* nodeA, Node* nodeB);

#endif
