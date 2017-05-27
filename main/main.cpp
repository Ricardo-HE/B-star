//driver.cpp
#include "RootNode.h"
#include "NormalNode.h"


void main()
{
	Node* poNode[2];
	poNode[0] = new RootNode(true);
	poNode[1] = new NormalNode(false);
	
	poNode[0]->Print();
	poNode[1]->Print();
}
