#include <iostream>

#include "../header/BStarTree.h"

int main()
{
	std::cout << "Main test file for testing the tree. This file will most likely change along with the project." << std::endl;

	BStarTree tree(5);

	tree.add(5);
	tree.print();

	return 0;
}
