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


#define NORMAL_NODE_ORDER = 5;           // The order of a Node inheriting this class
#define ROOT_NODE_ORDER = 5;           // The order of a Root Node inheriting this class

class Node
{
public:
	Node(){};
	Node(int order, bool rootflag, ancestor = nullptr):order(order), isRoot(rootflag), ancestor(ancestor){}
    virtual ~Node(){};

	//Pure virtual function
	virtual void print() = 0;
	virtual bool addItem(double item) = 0;
	virtual Node getNode(int iPos) = 0;

	//Access Functions
	int getOrder(){ return order; }
	int getNumKeys(){ return listKeys.size(); }
	std::list<double> getKeysList(){ return keysList; }
	std::list<Node> getChildList(){ return childList; }
	bool IsRoot(){ return isRoot; }

protected:
	int order;                      // Order of this node
	std::list<double> keysList;     // Pointer for allocating dynamic memory store
	std::list<Node> childList;
	bool  isRoot;			        // Tracks if root or not.
	Node* ancestor;

};

#endif
