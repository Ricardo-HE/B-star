
template <typename T>
void menu()
{
    std::cout << "This programs lets you add, delete find and print in a B* star tree" << std::endl;
    int order;
    std::cout << "Order of the tree: ";
    std::cin >> order;

    BStarTree<T> tree(order);

    char option;
    do{
        std::cout << std::endl << "--------------------" << std::endl;
        std::cout << "You can do the following: " << std::endl;
        std::cout << "[1] Add to the tree" << std::endl;
        std::cout << "[2] Erase from the tree" << std::endl;
        std::cout << "[3] Generate numbers in a file" << std::endl;
        std::cout << "[4] Add and erase from the tree" << std::endl;
        std::cout << "[5] Look for an element in the tree" << std::endl;
        std::cout << "[6] Print the tree by level" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cin >> option;
        std::cout << "--------------------" << std::endl << std::endl;

        switch(option){
            case '1':
                addMenu<T>(tree);
                break;
            case '2':
                eraseMenu<T>(tree);
                break;
            case '3':
                generateFileMenu();
                break;
            case '4':
                addEraseMenu<T>(tree);
                break;
            case '5':
                findMenu<T>(tree);
                break;
            case '6':
                tree.print();
                break;
        }
    }while(option != '0');
}

template <typename T>
void addMenu(BStarTree<T>& tree)
{
    char option;
    std::cout << "You selected to add an element to the tree" << std::endl;
    do{
        std::cout << std::endl << "--------------------" << std::endl;
        std::cout << "Select one of the following: " << std::endl;
        std::cout << "[1] To capture and add an element from the keyboard" << std::endl;
        std::cout << "[2] To capture and add elements from a file" << std::endl;
        std::cout << "[0] To return to the main menu" << std::endl;
        std::cin >> option;
        std::cout << "--------------------" << std::endl << std::endl;

        switch(option){
            case '1':
                T element;
                std::cout << "Capture and add element from keyboard" << std::endl;
                std::cout << "Write the element you want to add to the tree: ";
                std::cin >> element;
                if(tree.add(element)){
                    std::cout << "Element successfully added." << std::endl;
                }else{
                    std::cout << "Element couldn't be added. Maybe is already in the tree?" << std::endl;
                }
                break;

            case '2':
                std::string filepath;
                unsigned numberAditions = 0;
                std::cout << "Capture and add element from a file" << std::endl;
                std::cout << "Write the filepath of the file (it must not have spaces): " << std::endl;
                std::cout << "There is already a file with filepath files/add.txt if you have ";
                std::cout << "numbers in it." << std::endl;
                std::cin >> filepath;
                numberAditions = tree.addFromFile(filepath);
                std::cout << "Added " << numberAditions << " elements from " << filepath << std::endl;
                break;
        }
    }while(option != '0');
}

template <typename T>
void eraseMenu(BStarTree<T>& tree)
{
    char option;
    std::cout << "You selected to erase an element from the tree" << std::endl;
    do{
        std::cout << std::endl << "--------------------" << std::endl;
        std::cout << "Select one of the following: " << std::endl;
        std::cout << "[1] To erase all the elements from the tree" << std::endl;
        std::cout << "[2] To capture and erase an element from the keyboard" << std::endl;
        std::cout << "[3] To capture and erase elements from a file" << std::endl;
        std::cout << "[0] To return to the main menu" << std::endl;
        std::cin >> option;
        std::cout << "--------------------" << std::endl << std::endl;

        switch(option){

            case '1':
                std::cout << "Erasing elements..." << std::endl;
                tree.empty();
                std::cout << "Erased all elements from the tree" << std::endl;
                break;

            case '2':
                T element;
                std::cout << "Capture and erase element from keyboard" << std::endl;
                std::cout << "Write the element you want to erase to the tree: ";
                std::cin >> element;
                if(tree.erase(element)){
                    std::cout << "Element successfully erased." << std::endl;
                }else{
                    std::cout << "Element couldn't be erased. Maybe is already in the tree?" << std::endl;
                }
                break;

            case '3':
                std::string filepath;
                unsigned numberDelitions = 0;
                std::cout << "Capture and erase element from a file" << std::endl;
                std::cout << "Write the filepath of the file (it must not have spaces): " << std::endl;
                std::cout << "There is already a file with filepath files/erase.txt if you have ";
                std::cout << "numbers in it." << std::endl;
                std::cin >> filepath;
                numberDelitions = tree.eraseFromFile(filepath);
                std::cout << "Erased " << numberDelitions << " elements from " << filepath << std::endl;
                break;

        }
    }while(option != '0');
}

void generateFileMenu()
{
    std::cout << "Selected to generate numbers in a file" << std::endl;
    std::cout << "This will put as many numbers as you want (as much as 10000, from 0 to 9999)";
    std::cout << "\n in the file." << std::endl;
    char option;
    do{
        std::cout << std::endl << "--------------------" << std::endl;
        std::cout << "Select one of the following: " << std::endl;
        std::cout << "[1] To generate a file" << std::endl;
        std::cout << "[0] To return to the main menu" << std::endl;
        std::cin >> option;
        std::cout << "--------------------" << std::endl << std::endl;

        switch (option){
            case '1':
                int number;
                std::string filepath;
                std::cout << "Generate a file" << std::endl;
                std::cout << "How many numbers you want to generate? ";
                std::cin >> number;
                if(number < 0) number = 0;
                std::cout << "Write the filepath of the file (it must not have spaces): " << std::endl;
                std::cout << "There is already a file with filepath files/add.txt You can ";
                std::cout << "choose to use it if you want." << std::endl;
                std::cin >> filepath;
                generateFile(number, filepath);
                break;
        }
    }while(option != '0');
}

template <typename T>
void addEraseMenu(BStarTree<T>& tree)
{
    char option;
    std::cout << "You selected to add and erase. What this does is, it adds elements from a file";
    std::cout << "\n and then deletes random elements from the tree until leaving however many";
    std::cout << "\n elements you want." << std::endl;
    do{
        std::cout << std::endl << "--------------------" << std::endl;
        std::cout << "Select one of the following: " << std::endl;
        std::cout << "[1] To add and erase from a file: " << std::endl;
        std::cout << "[0] To return to the main menu" << std::endl;
        std::cin >> option;
        std::cout << "--------------------" << std::endl << std::endl;

        switch(option){
            case '1':
                std::string filepath;
                int elementsToLeave = 0;
                std::cout << "Add and erase elements from file" << std::endl;
                std::cout << "Number of elements to leave: ";
                std::cin >> elementsToLeave;
                std::cout << "Write the filepath of the file (it must not have spaces): " << std::endl;
                std::cout << "There is already a file with filepath files/add.txt if you have ";
                std::cout << "numbers in it." << std::endl;
                std::cin >> filepath;
                tree.addDelete(elementsToLeave, filepath);
                break;
        }
    }while(option != '0');
}

template <typename T>
void findMenu(BStarTree<T>& tree)
{
    char option;
    std::cout << "You selected to find an element in the tree" << std::endl;
    do{
        std::cout << std::endl << "--------------------" << std::endl;
        std::cout << "Select one of the following: " << std::endl;
        std::cout << "[1] To find an element in the tree from the keyboard" << std::endl;
        std::cout << "[0] To return to the main menu" << std::endl;
        std::cin >> option;
        std::cout << "--------------------" << std::endl << std::endl;

        switch(option){
            case '1':
                T element;
                std::cout << "Capture and find element from keyboard" << std::endl;
                std::cout << "Write the element you want to find in the tree: ";
                std::cin >> element;
                if(tree.find(element)){
                    std::cout << "Element exists in the tree" << std::endl;
                }else{
                    std::cout << "Element doesn't exist in the tree" << std::endl;
                }
                break;
        }
    }while(option != '0');
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

