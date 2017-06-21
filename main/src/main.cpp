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
    int cap;
    std::cout << "Capacity: ";
    std::cin >> cap;
    std::cin.ignore();

    if(cap < 0) cap = 0;

    int number;
    for(unsigned i = 1; i <= (unsigned)cap; ++i){
        tree.add(number = rand() % 10000);
        //tree.add(i);
        std::cout << "Printing after adding: " << number << std::endl;
        //std::cout << "Printing after adding: " << i << std::endl;
        tree.print();
        /*if(i == 52){
            std::cout <<"Pause" << std::endl;
            std::cin.ignore();
            std::cin.ignore();
        }*/
        std::cout << "-------------------------------" << std::endl;
        //std::cin.ignore();
    }

/*
    std::cout << "Adding from a file: " << std::endl;
    unsigned numberOfElements = tree.addFromFile("files/file.txt");
    std::cout << numberOfElements << " where added " << std::endl;
    std::cout << "Printing:" << std::endl;
    tree.print();
*/
    return 0;
}
