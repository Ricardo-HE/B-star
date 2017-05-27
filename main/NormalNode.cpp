//NormalNode.cpp
#include "NormalNode.h"

/******************************************************************************
//  FUNCTION: Overloaded RootNode constructor 
//  PURPOSE	: Creates and intializes a root node for a BStarTree.
//
//  CALL EXAMPLE: Node* ptrNode = new NormalNode(false);
//                                                         
//  PRE CONDITIONS:  Enough memory has to exist to create a NormalNode Object			
//  POST CONDITIONS: Memory for a NormalNode object has been allocated and members intialized.
//******************************************************************************/

NormalNode::NormalNode(bool isRoot):Node(NODE_ORDER, isRoot, 0)
{          
	// Allocate memory for storage
	piStore = new int[NODE_ORDER -1];          // Data items are 1 less than the Specific Nodes order

	//Set all stores to 0
	for(int x =0; x < (NODE_ORDER - 1); x++)
	{
		piStore[x] = 0;
	}

	//Set pointers to null
	for(x = 0; x < NODE_ORDER; x++)
	{
		pNodeArray[x] = NULL;
	}

	
}  

//******************************************************************************
//  FUNCTION: Print 
//  PURPOSE	: Prints all the data values except those of the Node*
//
//  CALL EXAMPLE: Node* ptrNode->Print()
//                                                         
//  PRE CONDITIONS:  NormalNode has to exist	
//  POST CONDITIONS: Menber data printed to monitor
//******************************************************************************
void NormalNode::Print()
{
	cout << "iNumInNode is: " <<iNumInNode <<endl; 
	cout << "bIsRoot is: " << bIsRoot <<endl;
	for(int x = 0; x < NODE_ORDER - 1; x++)
	{
		cout << "X is: " << piStore[x] << endl;
	}
	cout << "iOrder is: " << iOrder << endl << endl;
}