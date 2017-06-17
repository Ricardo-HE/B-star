#include <iostream>
#include <cmath>

#include "../header/BStarTree.h"

int main()
{
	std::cout << "Main test file for testing the tree. This file will most likely change along with the project." << std::endl;

    const unsigned MAX = 200;
    const unsigned SIZE = 20;
	BStarTree tree(5);
	
/*
    for(unsigned i = 0; i <= MAX; i += 10){
        tree.add(i);
        std::cout << "Printing after adding: " << i << std::endl;
        tree.print();
    }
*/
/*
   for(unsigned i = MAX; i > 0; i -= 10){
        tree.add(i);
        std::cout << "Printing after adding: " << i << std::endl;
        tree.print();
    }
*/
    srand(time(NULL));

    int number;
    for(unsigned i = 0; i <= SIZE; ++i){
        tree.add(number = rand() % 100);
        std::cout << "Printing after adding: " << number << std::endl;
        tree.print();
        std::cout <<"Pause" << std::endl;
        std::cin.ignore();
}

	return 0;
}
