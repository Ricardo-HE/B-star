#include <iostream>
#include <cmath>

#include "../header/BStarTree.h"

int main()
{
    std::cout << "Main test file for testing the tree. This file will most likely change along with the project." << std::endl;

    //const unsigned MAX = 200;
    //const unsigned SIZE = 20;
    int order;
    std::cout << "Order of the tree: ";
    std::cin >> order;

    BStarTree tree(order);

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

    int cap;
    std::cout << "Number of elements to add to the tree: ";
    std::cin >> cap;

    if(cap < 0) cap = 0;

    int range;
    std::cout << "Put in the tree numbers from 0 to: ";
    std::cin >> range;

    if(range < 1) range = 10;

    srand(time(NULL));
    int number;
    for(unsigned i = 1; i <= (unsigned)cap; ++i){
        tree.add(number = rand() % range);
        //tree.add(i);
        //std::cout << "Printing after adding: " << number << std::endl;
        //std::cout << "Printing after adding: " << i << std::endl;
        //tree.print();
        //std::cout << "-------------------------------" << std::endl;
        //std::cin.ignore();
    }
    std::cout << "Printing the tree: " << std::endl;
    tree.print();


/*
    std::cout << "Adding from a file: " << std::endl;
    unsigned numberOfElements = tree.addFromFile("files/file.txt");
    std::cout << numberOfElements << " where added " << std::endl;
    std::cout << "Printing:" << std::endl;
    tree.print();
*/
    return 0;
}
