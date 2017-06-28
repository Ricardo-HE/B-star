#include <iostream>
#include <cmath>

#include "../header/BStarTree.h"

    /**
    * @brief Generates a file with as many numbers as the received size, 10 by default and
    *          with the received filepath, by default "files/add.txt". The numbers are
    *          randomly generated from 0 to 9999.
    * @param size How many numbers to generate in the file.
    * @param filepath What is the filepath of the file to put the numbers in.
    */
void generateFile(int size = 10, std::string filepath = "files/add.txt");

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
    generateFile(cap);

    int remain;
    std::cout << "Number of elements to remain in the tree: ";
    std::cin >> remain;
    std::cin.ignore();
    tree.addDelete(remain);

    std::cout << "Printing the tree" << std::endl;
    tree.print();

    std::cout << "Pause" << std::endl;
    std::cin.ignore();

    return 0;
}

void generateFile(int size /*= 10*/, std::string filepath /*= files/add.txt*/)
{
    std::ofstream oFile;

    oFile.open(filepath);
    if(!oFile.is_open()){
        std::cerr << "Couldn't read file with path " << filepath << std::endl;
    }

    //creates an array to put numbers from 0 to 9999, shuffles them and take size number of
    //elements from it so there are no repetitions.
    std::array<int, 10000> arr; //creates an array with capacity 10000
    for(unsigned i = 0; i < arr.size(); ++i) arr[i] = i;    //puts numbers from 0 to the array
                                                            //capacity in arr
    std::random_shuffle(arr.begin(), arr.end()); //shuffles the array

    for(int i = 0; i < size; ++i){
        oFile << arr[i]  << '\n'; //put the first size random elements in the file
    }

    oFile.close();
}
