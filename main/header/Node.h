//File Name:
//Programmer:
//Section:
//******************************************************************************
//				CLASS DECLARATION
//  CLASS NAME	:Node
//  PURPOSE	    :This is an abstract node class which is the base class
//               for a RootNode class and a NormalNode class. An object of type
//               Node cannot ever be declared. However any class that
//               uses node as a base class can be pointed to be a Node* pointer.
//
//  DESCRIPTION	:The node keeps track of its particular iOrder, number of items
//               stored, dynamically allocated memory for data storage, whether
//               it is a root or normal node.
//  METHODS:
//      Constructor -- sets up iOrder, bisRoot, and iNumInNode before constructor called
//		virtual void Print() = 0; -- pure abastract function; code is written by derived class
//		virtual bool AddItem = 0; -- pure abstract function; code is written by derived class
//
//******************************************************************************
#ifndef NODE_H
#define NODE_H

#include <list>

class Node
{
public:
	/**
	* @brief Default constructor.
	*/
	Node(){}

	/**
	* @brief Constructor with parameters to initialize the variables from the class.
	*/
	Node(int order, bool rootflag, Node* ancestor = nullptr):order(order), isRoot(rootflag), ancestor(ancestor){}

	/**
	*@brief Virtual destructor
	*/
    virtual ~Node(){}


	//******************Pure virtual function***********************************
	/**
	* @brief print the node's information such like the keys of the node, father's ID
	* and child's ID.
	*/
	virtual void print() = 0;
	/**
	* @brief Add a key to the Node's array list of keys.
	* @return True if it was added and false if it wasn't added to the array list.
	*/
	virtual bool addItem(double item) = 0;
	/**
	* @brief Given an index number return the Node child of the list of child nodes.
	* @return The node child of the position given of the list of child.
	*/
	virtual Node* getChildNode(int iPos) = 0;

	virtual double getKey(int iPos) = 0;

	virtual bool isOverloaded() = 0;

	//************************Access Functions**********************************
	/**
	*@brief Get the order of the node.
	*@return The order of the node.
	*/
	unsigned getOrder(){ return order; }
	/**
	*@brief Get the current size of the list of keys in the node.
	*@ The current size of the list of keys in the node.
	*/
	std::size_t getNumKeys(){ return keysList.size(); }
	/**
	*@brief Get the list of keys from the node.
	*@return The list of keys from the node.
	*/
	std::list<double> getKeysList(){ return keysList; }
	/**
	*@brief Get the list of childs from the node.
	*@return The list of keys from the node.
	*/
	std::list<Node*> getChildList(){ return childList; }
	/**
	*@brief Says if the node is root or not.
	*@return True if the node is root, false if isn't.
	*/
	bool IsRoot(){ return isRoot; }

	Node* getAncestor(){ return ancestor; }

protected:
	int order;                      // Order of this node
	std::list<double> keysList;     // Pointer for allocating dynamic memory store
	std::list<Node*> childList;
	bool  isRoot;			        // Tracks if root or not.
	Node* ancestor;

};

#endif
