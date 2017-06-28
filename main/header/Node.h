#ifndef NODE_H
#define NODE_H

#include <iostream>     //std::cout, std::endl
#include <list>         //std::list

#include "BStarTree.h"  //BStarTree

template <typename T>
class NormalNode;

template <typename T>
class Node
{
public:
    //use the default of the following
    Node() = default; //constructor
    Node(Node const &) = default; //copy constructor
    Node(Node&&) = default; //move constructor
    Node& operator=(Node const &) = default; //copy assignment operator
    Node& operator=(Node&&) = default; //move assignment operator
    virtual ~Node() = default;

    /**
    * @brief Constructor with parameters to initialize the variables from the class.
    * @param tree Constant pointer to the tree where the node is going to be.
    * @ancestor This tells the node what node is its ancestor.
    */
    Node(BStarTree<T> const * tree, Node<T>* ancestor = nullptr):tree(tree), ancestor(ancestor) {}

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
    void addItem(T item);

    /**
     * @brief Adds a child to the Node's list of children.
     * @param child Child to add to the list.
     */
    void addChild(Node<T>* child);

    /**
     * @brief Pops the front key in the list and returns it.
     * @pre The list must not be empty.
     * @return The key at the front of the list or undefined behavior if the list is empty.
     */
    T popFrontKey();

    /**
     * @brief Pops the back key in the list and returns it.
     * @pre The list must not be empty.
     * @return The key at the back of the list or undefined behavior if the list is empty.
     */
    T popBackKey();

    /**
     * @brief Pops the front child in the list and returns it.
     * @pre The list must not be empty.
     * @return The child at the front of the list or undefined behavior if the list is empty.
     */
    Node<T>* popFrontChild();

    /**
     * @brief Pops the back child in the list and returns it.
     * @pre The list must not be empty.
     * @return The child at the back of the list or undefined behavior if the list is empty.
     */
    Node<T>* popBackChild();

    /**
     * @brief Adds from front of the received list up to limit elements to the back of the
     *          keys list.
     * @pre The received list must have at least limit number of elements or will result
     *          in undefined behavior.
     * @param takeList List whose elements on the front are going to be pushed back to the
     *          keys list.
     * @param limit Number of elements to take from the received list and put in the keys
     *          list.
     */
    void putKeys(std::list<T>& takeList, int limit);

    /**
     * @brief Adds from front of the received list up to limit elements to the back of the
     *          children list.
     * @pre The received list must have at least limit number of elements or will result
     *          in undefined behavior.
     * @param takeList List whose elements on the front are going to be pushed back to the
     *          children list.
     * @param limit Number of elements to take from the received list and put in the children
     *          list.
     */
    void putChildren(std::list<Node<T>*>& takeList, int limit);

    /**
     * @brief Gets the Id of the node.
     * @return The id of the node.
     */
    unsigned getId() const { return id; }

    /**
    *@brief Get the current size of the list of keys in the node.
    *@ The current size of the list of keys in the node.
    */
    std::size_t getNumKeys() const { return keysList.size(); }

    /**
     * @brief Tells you the ancestor of the node.
     * @return The ancestor of the node. It might be null.
     */
    Node<T>* getAncestor() const { return ancestor; }

    /**
    *@brief Get the list of keys as constant from the node.
    *@return The list of keys  as constant from the node.
    */
    std::list<T> const & keys() const { return keysList; }

    /**
    *@brief Get the list of keys from the node.
    *@return The list of keys from the node.
    */
    std::list<T>& keys() { return keysList; }

    /**
    *@brief Get the list of children as constant from the node.
    *@return The list of children as constant from the node.
    */
    std::list<Node<T>*> const & children() const { return childList; }

    /**
    *@brief Get the list of children from the node.
    *@return The list of children from the node.
    */
    std::list<Node<T>*>& children() { return childList; }

    /**
     * @brief Tells you whether the node is a leaf or not.
     * @return True if the node is a leaf, false otherwise.
     */
    bool isLeaf() { return this->children().empty(); }

protected:
    unsigned id; //id to identify nodes
    BStarTree<T> const * tree; //pointer to the tree
    std::list<T> keysList;     // Pointer for allocating dynamic memory store
    std::list<Node<T>*> childList;
    Node<T>* ancestor;

};

/**
 * @brief Compares two nodes to see if the first one is smaller than the second one.
 * @param nodeA Node to check if it is the smaller one.
 * @param nodeB Node to check against nodeA if it is the bigger one.
 * @return True if nodeA is smaller than nodeB.
 */
template <typename T>
bool compareKeyNodes(Node<T>* nodeA, Node<T>* nodeB);

#include "../src/Node.cpp"

#endif
