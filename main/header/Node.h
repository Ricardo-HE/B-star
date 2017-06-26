#ifndef NODE_H
#define NODE_H

#include <list>

class Node
{
public:
    /**
    * @brief Constructor without parameters.
    */
    Node() {}

    /**
    * @brief Constructor with parameters to initialize the variables from the class.
    * @param order Order of the tree. This number indicates the maximum number of keys for a node
    *           befire needing to split.
    * @rootFlag This indicates wheter a node is the root node or not.
    * @ancestor This tells the node what node is its ancestor.
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
    * @param item Element to add to the node.
    * @return True if it was added and false if it wasn't added to the array list.
    */
    virtual bool addItem(double item) = 0;

    /**
    * @brief Given an index number return the Node child of the list of child nodes.
    * @param iPos Position, 0-indexed, of the child in the node.
    * @return The node child of the position given of the list of child.
    */
    virtual Node* getChildNode(int iPos) const = 0;

    /**
     * @brief Gets the key of the node in the received position.
     * @param iPos Position, 0-indexed, of the key in the node.
     * @return The key in the received position.
     */
    virtual double getKey(int iPos) const = 0;

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

    //************************Access Functions**********************************

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

    /**
     * @brief Tells you the ancestor of the node.
     * @return The ancestor of the node. It might be null.
     */
    Node* getAncestor() const { return ancestor; }

    /**
     * @brief Overload of the non constant operator [] to get an key.
     * @param index Position, 0-indexed, of the key to get.
     * @return Key in the received position.
     */
    double& operator[](int index) {
        auto it = this->keysList.begin();
        std::advance(it, index);

        return *it;
    }

    /**
     * @brief Overload of the constant operator [] to get an key.
     * @param index Position, 0-indexed, of the key to get.
     * @return Key in the received position.
     */
    const double& operator[](int index) const{
        auto it = this->keysList.begin();
        std::advance(it, index);

        return *it;
    }

    //Alternate ways to get the list of keys and children
    /**
    *@brief Get the list of keys from the node.
    *@return The list of keys from the node.
    */

    std::list<double>& keys() { return getKeysList(); }

    /**
    *@brief Get the list of childs from the node.
    *@return The list of keys from the node.
    */
    std::list<Node*>& children() { return getChildList(); }

    /**
     * @brief Tells you whether the node is a leaf or not.
     * @return True if the node is a leaf, false otherwise.
     */
    bool isLeaf() { return this->children().empty(); }

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
