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
    srand(time(NULL));
    //int number;

    //int aux[30];
    /*aux[0] =722;
    aux[1] =444;
    aux[2] =355;
    aux[3] =801;
    aux[4] = 623;
    aux[5] =142;
    aux[6] =760;
    aux[7] =475;
    aux[8] =823;
    aux[9] =12;
    aux[10] =73;
    aux[11] =238;
    aux[12] =648;
    aux[13] =13;
    aux[14] =156;
    aux[15] =225;
    aux[16] =625;
    aux[17] =639;
    aux[18] =651;
    aux[19] =696;
    aux[20] =769;
    aux[21] =803;
    aux[22] =818;
    aux[23] =837;
    aux[24] =849;
    aux[25] =880;
    aux[26] =979;*/

    /*
    for (size_t i = 0; i < 27; i++) {
        tree.add(aux[i] = rand() % 10000);
        std::cout << "adding: " << aux[i];
    }
    std::cout << "\n\n";

    tree.print();

    std::cout << "------------------------------" << '\n';
    for (size_t i = 0; i < 27; i++) {
        std::cout << "deleting : " << aux[i] << '\n';
        tree.erase(aux[i]);
        tree.print();
        std::cin.ignore();
        std::cout << "------------------------------" << '\n';
    }
    */

    int cap;
    std::cout << "Number of elements to add: ";
    std::cin >> cap;

    if(cap < 0) cap = 0;
    tree.generateFile("files/add.txt", cap);

    int remain;
    std::cout << "Number of elements to remain in the tree: ";
    std::cin >> remain;
    std::cin.ignore();
    tree.testAddAndDelete("files/add.txt", remain);

    std::cout << "Printing the tree" << std::endl;
    tree.print();

    std::cout << "Pause" << std::endl;
    std::cin.ignore();
    std::cin.ignore();




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

    /*int cap;
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
    tree.print();*/


/*
    std::cout << "Adding from a file: " << std::endl;
    unsigned numberOfElements = tree.addFromFile("files/file.txt");
    std::cout << numberOfElements << " where added " << std::endl;
    std::cout << "Printing:" << std::endl;
    tree.print();
*/
    return 0;
}
