//RootNode.cpp

#include "RootNode.h"


//******************************************************************************
//  FUNCTION: Overloaded RootNode constructor 
//  PURPOSE	: Creates and intializes a root node for a BStarTree whose order is 4/3 a Normal
//			  Node object.
//
//  CALL EXAMPLE: Node* ptrNode = new RootNode(true);
//                                                         
//  PRE CONDITIONS:  Enough memory has to exist to create a RootNode Object			
//  POST CONDITIONS: Memory for a RootNode object has been allocated and members intialized.
//******************************************************************************
RootNode::RootNode(bool isRoot):Node(ROOT_ORDER, isRoot, 0)
{          
	// Allocate memory for storage
	piStore = new int[ROOT_ORDER -1];    // Data items are 1 less than the Specific Nodes order

	//Set all stores to 0
	for(int x =0; x < (ROOT_ORDER - 1); x++)
	{
		piStore[x] = 0;
	}

	//Set pointers to null
	for(x = 0; x < ROOT_ORDER; x++)
	{
		pNodeArray[x] = NULL;
	}

	
}  

//******************************************************************************
//  FUNCTION: Print 
//  PURPOSE	: Prints all the data values except those of the Node*
//
//  CALL EXAMPLE: ptrNode->Print();
//                                                         
//  PRE CONDITIONS:  RootNode has to exist	
//  POST CONDITIONS: Menber data printed to monitor
//******************************************************************************
void RootNode::Print()
{
	cout << "iNumInNode is: " <<iNumInNode <<endl; 
	cout << "bIsRoot is: " << bIsRoot <<endl;
	for(int x = 0; x < ROOT_ORDER - 1; x++)
	{
		cout << "X is: " << piStore[x] << endl;
	}
	cout << "iOrder is: " << iOrder << endl << endl;
}


bool RootNode::AddItem(int iItem)
{
	return true;	
}