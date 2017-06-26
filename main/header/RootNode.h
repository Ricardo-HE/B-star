#ifndef ROOTNODE_H
#define ROOTNODE_H

#include <iostream>
#include <algorithm>

#include "Node.h"
#include "NormalNode.h"

class RootNode : public Node                      // Node is the base class, all public and
                                                  // protected members of Node can be accessed
                                                  // by RootNode
{
public:

    /**
    * @brief Constructor with parameters to initialize the variables from the class.
    * @param tree Constant pointer to the tree where the node is going to be.
    * @ancestor This tells the node what node is its ancestor.
    */
    RootNode(BStarTree const * tree, Node* ancestor = nullptr, unsigned id = 0, unsigned height = 0);
    /**
     * @brief Default destructor of the class.
     */
    ~RootNode(){}

    //Definitions of Node class pure virtual functions
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

    /**
    *@brief Says if the node is root or not.
    *@return True if the node is root, false if isn't.
    */
    bool isRoot() const { return true; }
};

#endif
