#ifndef NORMALNODE_H
#define NORMALNODE_H

#include <cmath>
#include <iostream>
#include <algorithm>

#include "Node.h"

class NormalNode : public Node                      // Node is the base class, all public and
{                                                   // protected members of Node can be accessed
public:                                             // by NormalNode

    /**
     * @brief Constructor without parameters.
     */
    NormalNode(){}

    /**
    * @brief Constructor with parameters to initialize the variables from the class.
    * @param order Order of the tree. This number indicates the maximum number of keys for a node
    *           befire needing to split.
    * @rootFlag This indicates wheter a node is the root node or not.
    * @ancestor This tells the node what node is its ancestor.
    */
    NormalNode(int order, bool rootflag, Node* ancestor = nullptr, unsigned id = 0, unsigned height = 0);                       // Overloaded constructor false = NormalNode
    /**
     * @brief Default destructor.
     */
    ~NormalNode(){}

    void setAncestor(Node* newAncestor){ancestor = newAncestor;}

    //Definitions of Node class pure virtual functions
    /**
    * @brief print the node's information such like the keys of the node, father's ID
    * and child's ID.
    */
    virtual void print() const;

    /**
    * @brief Add a key to the Node's array list of keys.
    * @param item Element to add to the node.
    * @return True if it was added and false if it wasn't added to the array list.
    */
    virtual bool addItem(double item);

    /**
    * @brief Given an index number return the Node child of the list of child nodes.
    * @param iPos Position, 0-indexed, of the child in the node.
    * @return The node child of the position given of the list of child.
    */
    virtual Node* getChildNode(int iPos) const;

    /**
     * @brief Gets the key of the node in the received position.
     * @param iPos Position, 0-indexed, of the key in the node.
     * @return The key in the received position.
     */
    virtual double getKey(int iPos) const;

    /**
     * @brief Tells you if the node has more keys than permited. This means it has to split.
     * @return True if the node is overloaded, false otherwise.
     */
    virtual bool isOverloaded() const;

    /**
     * @brief Tells you if the node has as many keys as permited. One more and it will be overloaded.
     * @return True if the node is full, false otherwise.
     */
    virtual bool isFull() const;

    /**
     * @brief Tells you if the node has less keys than permited. This means it has to merge.
     * @return True if the node is underloaded, false otherwise.
     */
    virtual bool isUnderloaded() const;

    /**
     * @brief Tells you if the node has as many keys as permited. One less and it will be underloade.
     * @return True if the node is at its minimum, false otherwise.
     */
    virtual bool isAtMinimum() const;

};
#endif
