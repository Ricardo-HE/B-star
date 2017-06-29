#ifndef MENU_H
#define MENU_H

#include <iostream>     //std::cout, std::cin, std::endl, std::ofstream
#include <array>        //std::array
#include <algorithm>    //std::random_shuffle

#include "BStarTree.h"

/**
* @brief Generates a file with as many numbers as the received size, 10 by default and
*          with the received filepath, by default "files/add.txt". The numbers are
*          randomly generated from 0 to 9999.
* @param size How many numbers to generate in the file.
* @param filepath What is the filepath of the file to put the numbers in.
*/
void generateFile(int size = 10, std::string filepath = "files/add.txt");

/**
 * @brief Simple menu to generate a file with numbers.
 */
void generateFileMenu();

/**
 * @brief Menu for the whole program. With this menu you can add, erase, find, print and
 *          empty a tree. You can also generate a file to then add the numbers generated
 *          to the tree.
 */
 void menu();

/**
 * @brief Menu to add elements to the tree. You can add elements by using your keyboard
 *          or by providing a file to take the elements from.
 * @param tree Target tree to put the elements in.
 */
 void addMenu(BStarTree& tree);

/**
 * @brief Menu to erase an element from the tree. You can erase elements by using your keyboard
 *          or by providing a file to take the elements from.
 * @param tree Target tree to take the elements from.
 */
 void eraseMenu(BStarTree& tree);

/**
 * @brief Menu to add elements from a file and then randomly erase elements from the tree until
 *          leaving a certain number of elements.
 * @param tree Target tree to take the elements from.
 */
 void addEraseMenu(BStarTree& tree);

/**
 * @brief Menu to find an element in the tree. The element to add must be take from your
 *          keyboard.
 * @param tree Target tree to put the elements in.
 */
 void findMenu(BStarTree& tree);

#endif //MENU_H
