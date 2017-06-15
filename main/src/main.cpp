#include <iostream>

#include "../header/BStarTree.h"

int main()
{
	std::cout << "Main test file for testing the tree. This file will most likely change along with the project." << std::endl;

    unsigned MAX = 110;
	BStarTree tree(5);

    for(unsigned i = 0; i < MAX; i += 10){
        tree.add(i);
        tree.print();
    }
    std::cout << "Prints one last time" << std::endl;
	tree.print();

	return 0;
}
