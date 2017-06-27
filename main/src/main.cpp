#include <iostream>
#include <cmath>

#include "../header/BStarTree.h"

int main()
{
    std::cout << "Main test file for testing the tree. This file will most likely change along with the project." << std::endl;

    int order;
    std::cout << "Order of the tree: ";
    std::cin >> order;

    BStarTree<int> tree(order);
    srand(time(NULL));

    int cap;
    std::cout << "Number of elements to add: ";
    std::cin >> cap;

    if(cap < 0) cap = 0;
    tree.generateFile(cap);

    int remain;
    std::cout << "Number of elements to remain in the tree: ";
    std::cin >> remain;
    std::cin.ignore();
    tree.testAddAndDelete(remain);

    std::cout << "Printing the tree" << std::endl;
    tree.print();

    std::cout << "Pause" << std::endl;
    std::cin.ignore();

    return 0;
}
