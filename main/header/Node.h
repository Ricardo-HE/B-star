#ifndef NODE_H
#define NODE_H

#include <list>

class Node
{
public:
    /**
    * @brief Default constructor.
    */
    Node() {}

    /**
    * @brief Constructor with parameters to initialize the variables from the class.
    */
    Node(int order, bool rootflag, Node* ancestor = nullptr):order(order), isRoot(rootflag), ancestor(ancestor) {}

    /**
    *@brief Virtual destructor
    */
    virtual ~Node() {}


    //******************Pure virtual function***********************************
    /**
    * @brief print the node's information such like the keys of the node, father's ID
    * and child's ID.
    */
    virtual void print() const = 0;
    /**
    * @brief Add a key to the Node's array list of keys.
    * @return True if it was added and false if it wasn't added to the array list.
    */
    virtual bool addItem(double item) = 0;
    /**
    * @brief Given an index number return the Node child of the list of child nodes.
    * @return The node child of the position given of the list of child.
    */
    virtual Node* getChildNode(int iPos) const = 0;

    virtual double getKey(int iPos) const = 0;

    virtual bool isOverloaded() const = 0;

    virtual bool isFull() const = 0;

    virtual bool isUnderloaded() const = 0;
    virtual bool isAtMinimum() const = 0;

    //************************Access Functions**********************************

    unsigned getId() const { return id; }

    unsigned getHeight() const { return height; }

    /**
    *@brief Get the order of the node.
    *@return The order of the node.
    */
    unsigned getOrder() const { return order; }
    /**
    *@brief Get the current size of the list of keys in the node.
    *@ The current size of the list of keys in the node.
    */
    std::size_t getNumKeys() const { return keysList.size(); }
    /**
    *@brief Get the list of keys from the node.
    *@return The list of keys from the node.
    */
    std::list<double> &getKeysList() { return keysList; }
    /**
    *@brief Get the list of childs from the node.
    *@return The list of keys from the node.
    */
    std::list<Node*> &getChildList() { return childList; }
    /**
    *@brief Says if the node is root or not.
    *@return True if the node is root, false if isn't.
    */
    bool IsRoot() const { return isRoot; }

    Node* getAncestor() const { return ancestor; }

    double& operator[](int index) {
        auto it = this->keysList.begin();
        std::advance(it, index);

        return *it;
    }

    const double& operator[](int index) const{
        auto it = this->keysList.begin();
        std::advance(it, index);

        return *it;
    }

    //Alternate ways to get the list of keys and children
    std::list<double>& keys() { return getKeysList(); }
    std::list<Node*>& children() { return getChildList(); }

    //Iterators for the keys
    auto begin() { return keysList.begin(); }
    auto end() { return keysList.end(); }
    auto rbegin() { return keysList.rbegin(); }
    auto rend() { return keysList.rend(); }

    bool isLeaf() {return this->children().empty();}

protected:
    unsigned id; //id to identify nodes
    unsigned height; //height in the tree. The root is 0 and each children is ancestor+1
    int order;                      // Order of this node
    std::list<double> keysList;     // Pointer for allocating dynamic memory store
    std::list<Node*> childList;
    bool  isRoot;                   // Tracks if root or not.
    Node* ancestor;

};



#endif
