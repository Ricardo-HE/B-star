//driver.cpp
#include "RootNode.h"
#include "NormalNode.h"


void main()
{
	Node* poNode[2];
	poNode[0] = new RootNode(true);
	poNode[1] = new NormalNode(false);

	int x =0;

	for(x = 0; x < 2; x++)
	{
		poNode[x]->Print();
	}

	for(x = 0; x < 2; x++)
	{
		cout << "poNode[" << x << "]->GetOrder()" << poNode[x]->GetOrder() << endl;
	}

	cout << "Size of Node* : " << sizeof(Node*) << endl;
}