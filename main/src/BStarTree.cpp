
template <typename T>
BStarTree<T>::BStarTree (int order): ORDER(order < 3 ? 3 : order), id(1),
                        root(new RootNode<T>(this, nullptr, id, 1))
{
    ++id;

    maxKeysNormalNode = ORDER - 1;
    maxKeysRootNode = 2 * floor( (2*ORDER - 2) / 3 );
    minKeysNormalNode = std::ceil( (2*ORDER-1) / 3 ) - 1;
    minKeysRootNode = 1;
    keysSplitChild1 = std::floor( (2*ORDER - 2)/3 );
    keysSplitChild2 = std::floor( (2*ORDER - 1)/3 );
    keysSplitChild3 = std::floor( 2*ORDER/3 );
}

template <typename T>
BStarTree<T>::~BStarTree()
{
    Node<T>* currentNode;
    std::queue<Node<T>*> nodeQueue;

    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        currentNode = nodeQueue.front();
        nodeQueue.pop();

        delete currentNode;
    }
}

template <typename T>
bool BStarTree<T>::add(T val)
{
    bool added;
    Node<T>* nodeAdd = nullptr;    //Node where it will add the number if the number
                                //doesn't exist in the tree.
    Node<T>* currentNode;

    nodeAdd = findPlaceAdd(val);
    if (nodeAdd != nullptr) {
        nodeAdd->addItem(val);
        currentNode = nodeAdd;
        while (currentNode != nullptr && currentNode->isOverloaded()) {
                handleOverload(currentNode);
                currentNode = currentNode->getAncestor();
        }

        added = true;
    }else{
        added = false;
    }

    return added;
}

template <typename T>
void BStarTree<T>::handleOverload(Node<T>* overloadedNode)
{
    if (!overloadedNode->isRoot()) {
        if (!this->searchSpace(overloadedNode)) {
            if (!this->isLeftmost(overloadedNode)) {
                splitLeft(overloadedNode);    //This split every node with their left sibling
            }else{
                splitRight(overloadedNode); //This split the leftmost node with his right sibling
                                            //because he has no left sibling
            }
        }
    }else{
        splitRoot();
    }
}

template <typename T>
bool BStarTree<T>::erase(T val)
{
    bool erased;
    Node<T>* nodeErase = nullptr;  //Node where it will add the number if the number
                                //doesn't exist in the tree.
    Node<T>* currentNode;

    nodeErase = findPlaceErase(val);
    if (nodeErase == nullptr) {
        return false;
    }

    currentNode = nodeErase;

    if (!nodeErase->isLeaf()) {
        currentNode = getGreaterMinor(nodeErase, val);
        nodeErase->addItem(currentNode->keys().back());
        currentNode->keys().pop_back();
    }
    nodeErase->keys().remove(val);

    Node<T>* ancestor;
    while (currentNode != root && currentNode->isUnderloaded()) {
        ancestor = currentNode->getAncestor();
        handleUnderload(currentNode);
        currentNode = ancestor;
    }

    erased = true;

    return erased;
}

template <typename T>
void BStarTree<T>::handleUnderload(Node<T>* underloadedNode)
{
    if(!searchSpaceErase(underloadedNode)){
        if (!underloadedNode->getAncestor()->isRoot()) {
            merge(underloadedNode); //inside of this method it checks if the node is leftmost
                                    //rightmost or none of those two
        }else{
            mergeRootChildren(underloadedNode);
        }
    }
}

template <typename T>
bool BStarTree<T>::find(T val) const
{
    return findPlaceAdd(val) == nullptr ? true : false;
}

template <typename T>
bool BStarTree<T>::find(T val, Node<T>*& node) const
{
    node = root;
    typename std::list<Node<T>*>::iterator child;

    while(!node->isLeaf()){
        child = node->children().begin();
        for(auto key = node->keys().begin(); *key <= val && key != node->keys().end(); ++key){
            if(*key == val) return true;
            ++child;
        }
        if(!node->isLeaf()){
            node = *child;
        }
    }

    //search if the value to add is in the leaf node about to be returned
    for(auto key = node->keys().begin(); *key <= val && key != node->keys().end(); ++key){
        if(*key == val) return true;
    }

    return false;
}

//this search can be optimized because when searching a node there is no need to keep
//searching for a value once the values of the node are bigger than the searched value.
template <typename T>
Node<T>* BStarTree<T>::findPlaceAdd(T val) const
{
    Node<T>* node = nullptr;
    if(!find(val, node)){
        return node;
    }

    return nullptr;
}

// can probably be more optimized
template <typename T>
Node<T>* BStarTree<T>::findPlaceErase(T val) const
{
    Node<T>* node = nullptr;
    if(find(val, node)){
        return node;
    }

    return nullptr;
}

template <typename T>
bool BStarTree<T>::searchSpace(Node<T>* node)
{
    bool foundSpace;
    foundSpace = true;

    if (this->areLeftSiblingsFull(node)){
        if (this->areRightSiblingsFull(node)) {
            foundSpace = false;
        }else{
            this->rotateRightAdd(node);
        }
    }else{
        this->rotateLeftAdd(node);
    }

    return foundSpace;
}

template <typename T>
bool BStarTree<T>::searchSpaceErase(Node<T>* node)
{
    bool foundSpace;
    foundSpace = true;

    if (this->areLeftSiblingsAtMinimum(node)){
        if (this->areRightSiblingsAtMinimum(node)) {
            foundSpace = false;
        }else{
            this->rotateRightErase(node);
        }
    }else{
        this->rotateLeftErase(node);
    }

    return foundSpace;

}

template <typename T>
bool BStarTree<T>::areLeftSiblingsFull(Node<T>* node) const
{
    Node<T>* ancestor = node->getAncestor();
    bool nodeIsFull = true;

    //this checks all the nodes before the received one to see if at least one of them is
    //not full
    for(auto leftSibling = ancestor->children().begin(); *leftSibling != node;  ++leftSibling){
         if ( !(*leftSibling)->isFull() ) {
            nodeIsFull = false;
            break;
        }
    }

    return nodeIsFull;
}

template <typename T>
bool BStarTree<T>::areRightSiblingsFull(Node<T>* node) const
{
    Node<T>* ancestor = node->getAncestor();
    bool nodeIsFull = true;

    for(auto rightSibling = ancestor->children().rbegin(); *rightSibling != node; ++rightSibling){
         if ( !(*rightSibling)->isFull() ) {
            nodeIsFull = false;
            break;
        }
    }

    return nodeIsFull;
}

template <typename T>
bool BStarTree<T>::areLeftSiblingsAtMinimum(Node<T>* node) const
{
    Node<T>* ancestor = node->getAncestor();
    bool nodeIsAtMinimum = true;

    //this checks all the nodes before the received one to see if at least one of them is
    //not full
    for(auto leftSibling = ancestor->children().begin(); *leftSibling != node;  ++leftSibling){
        if ( !(*leftSibling)->isAtMinimum() ) {
            nodeIsAtMinimum = false;
            break;
        }
    }

   return nodeIsAtMinimum;
}

template <typename T>
bool BStarTree<T>::areRightSiblingsAtMinimum(Node<T>* node) const
{
    Node<T>* ancestor = node->getAncestor();
    bool nodeIsAtMinimum = true;

    for(auto rightSibling = ancestor->children().rbegin(); *rightSibling != node; ++rightSibling){
         if ( !(*rightSibling)->isAtMinimum() ) {
            nodeIsAtMinimum = false;
            break;
        }
    }

    return nodeIsAtMinimum;
}

template <typename T>
bool BStarTree<T>::isLeftmost(Node<T>* node) const
{
    return *node->getAncestor()->children().begin() ==  node ? true : false;
}

template <typename T>
bool BStarTree<T>::isRightmost(Node<T>* node) const
{
    return *node->getAncestor()->children().rbegin() ==  node ? true : false;
}

template <typename T>
typename std::list<Node<T>*>::iterator BStarTree<T>::getIterator(Node<T>* node) const
{
    auto it = node->getAncestor()->children().begin();
    while(*it != node){
        ++it;
    }

    return it;
}

template <typename T>
Node<T>* BStarTree<T>::getLeftSibling(Node<T>* node) const
{
    return *prev(getIterator(node));
}

template <typename T>
Node<T>* BStarTree<T>::getRightSibling(Node<T>* node) const
{
    return *next(getIterator(node));
}

template <typename T>
typename std::list<Node<T>*>::iterator BStarTree<T>::rotateLeft(Node<T>* node)
{
    Node<T> *ancestor, *leftSibling, *child;
    typename std::list<T>::iterator ancestorKey;
    typename std::list<Node<T>*>::iterator nodeIt;

    ancestor = node->getAncestor();
    ancestorKey = ancestor->keys().begin();
    for(nodeIt = next(ancestor->children().begin()); *nodeIt != node; ++nodeIt){
        ++ancestorKey;
    }
    leftSibling = *prev(nodeIt);

    //key rotation
    leftSibling->keys().push_back(*ancestorKey);
    *ancestorKey = node->keys().front();
    node->keys().pop_front();

    //child rotation
    if(!node->children().empty()){
        child = node->children().front();
        node->children().pop_front();
        dynamic_cast<NormalNode<T>*>(child)->setAncestor(leftSibling);
        leftSibling->children().push_back(child);
    }

    return nodeIt;
}

template <typename T>
typename std::list<Node<T>*>::iterator BStarTree<T>::rotateRight(Node<T>* node)
{
    Node<T> *ancestor, *rightSibling, *child;
    typename std::list<T>::iterator ancestorKey;
    typename std::list<Node<T>*>::iterator nodeIt;

    ancestor = node->getAncestor();
    ancestorKey = ancestor->keys().begin();
    for(nodeIt = ancestor->children().begin(); *nodeIt != node; ++nodeIt){
        ++ancestorKey;
    }
    rightSibling = *next(nodeIt);

    //key rotation
    rightSibling->keys().push_front(*ancestorKey);
    *ancestorKey = node->keys().back();
    node->keys().pop_back();

    //child rotation
    if(!node->children().empty()){
        child = node->children().back();
        node->children().pop_back();
        dynamic_cast<NormalNode<T>*>(child)->setAncestor(rightSibling);
        rightSibling->children().push_front(child);
    }

    return nodeIt;
}

template <typename T>
bool BStarTree<T>::rotateLeftAdd(Node<T>* node)
{
    Node<T> *currentNode;

    currentNode = node;
    do {
        currentNode = *prev(rotateLeft(currentNode));
    } while(!isLeftmost(currentNode) && currentNode->isOverloaded());

     return true;
}

template <typename T>
bool BStarTree<T>::rotateRightAdd(Node<T>* node)
{
    Node<T> *currentNode;
    currentNode = node;
    do {
        currentNode = *next(rotateRight(currentNode));
    } while(!isRightmost(currentNode) && currentNode->isOverloaded());

    return true;
}

template <typename T>
bool BStarTree<T>::rotateLeftErase(Node<T>* node)
{
    typename std::list<Node<T>*>::iterator currentNode = getIterator(node);

    do {
        currentNode = prev(currentNode);
        rotateRight(*currentNode);
    } while(!isLeftmost(*currentNode) && (*currentNode)->isUnderloaded());

     return true;
}

template <typename T>
bool BStarTree<T>::rotateRightErase(Node<T>* node)
{
    typename std::list<Node<T>*>::iterator currentNode = getIterator(node);

    do {
        currentNode = next(currentNode);
        rotateLeft(*currentNode);
    } while(!isRightmost(*currentNode) && (*currentNode)->isUnderloaded());

    return true;
}

template <typename T>
void BStarTree<T>::splitRoot()
{
    Node<T> *child1, *child2;

    child1 = new NormalNode<T>(this, root, id++, 2);
    child2 = new NormalNode<T>(this, root, id++, 2);

    auto putKeys = [&](unsigned limit, Node<T>*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->keys().push_back( root->keys().front() );
            root->keys().pop_front();
        }
    };

    unsigned limitRoot = maxKeysRootNode /2;
    putKeys(limitRoot, child1);

    T auxKey = root->keys().front();
    root->keys().pop_front();

    putKeys(limitRoot, child2);

    root->keys().push_front(auxKey);

    auto putChildren = [&](unsigned limit, Node<T>*& lNode){
        if(!root->children().empty()){
            for (std::size_t i = 0; i < limit; i++) {
                lNode->children().push_back( root->children().front() );
                dynamic_cast<NormalNode<T>*>(lNode->children().back())->setAncestor(lNode);
                root->children().pop_front();
            }
        }

    };

    unsigned limitForChild1 = child1->keys().size() + 1;
    unsigned limitForChild2 = child2->keys().size() + 1;

    putChildren(limitForChild1, child1);
    putChildren(limitForChild2, child2);

    root->children().push_back(child1);
    root->children().push_back(child2);
}

template <typename T>
void BStarTree<T>::splitLeft(Node<T>* node)
{
    Node<T> *leftSibling, *ancestor;
    T ancestorKeyCopy;
    typename std::list<T>::iterator ancestorKey;
    typename std::list<Node<T>*>::iterator nodeIt;

    ancestor = node->getAncestor();
    ancestorKey = ancestor->keys().begin();
    for(nodeIt = next(ancestor->children().begin()); *nodeIt != node; ++nodeIt){
        ++ancestorKey;
    }

    ancestorKeyCopy = *ancestorKey;
    ancestor->keys().erase(ancestorKey);

    leftSibling = *prev(nodeIt);

    //moves all the keys of the left sibling to an auxiliar list, leaving the sibling empty
    std::list<T> auxList(std::move(leftSibling->keys()));
    auxList.push_back(ancestorKeyCopy);
    //moves all the keys of the node to the auxiliar list, leaving the node empty
    auxList.merge(node->keys());

    Node<T> *newNode; //new node that goes in the middle of the current node and its left sibling
    newNode = new NormalNode<T>(this, ancestor, id++, ancestor->getHeight() + 1);

    auto putKeys = [&auxList](unsigned limit, Node<T>*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->keys().push_back( auxList.front() );
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestor, &auxList](){
        ancestor->addItem( auxList.front() );
        auxList.pop_front();
    };

    //accommodate keys in the nodes
    unsigned limitOne = std::floor( (2*ORDER - 2)/3 );
    putKeys(limitOne, leftSibling);

    putKeyAncestor();

    unsigned limitTwo = std::floor( (2*ORDER - 1)/3 );
    putKeys(limitTwo, newNode);

    putKeyAncestor();

    unsigned limitThree = std::floor( 2*ORDER/3 );
    putKeys(limitThree, node);

    //accommodate children in the nodes.
    std::list<Node<T>*> auxListChildren(std::move(leftSibling->children()));
    auxListChildren.merge(node->children(), compareKeyNodes<T>);

    auto putChildren = [&auxListChildren](unsigned limit, Node<T>*& lNode){
        if (!auxListChildren.empty()) {
            for (std::size_t i = 0; i < limit; i++) {
                lNode->children().push_back( auxListChildren.front() );
                auxListChildren.pop_front();
                dynamic_cast<NormalNode<T>*>(lNode->children().back())->setAncestor(lNode);
            }
        }
    };

    putChildren(limitOne+1, leftSibling);
    putChildren(limitTwo+1, newNode);
    putChildren(limitThree+1, node);

    ancestor->addChild(newNode);
}

template <typename T>
void BStarTree<T>::splitRight(Node<T>* node)
{
    Node<T> *rightSibling, *ancestor;
    T ancestorKeyCopy;
    typename std::list<T>::iterator ancestorKey;
    typename std::list<Node<T>*>::iterator nodeIt;

    ancestor = node->getAncestor();
    ancestorKey = ancestor->keys().begin();
    for(nodeIt = ancestor->children().begin(); *nodeIt != node; ++nodeIt){
        ++ancestorKey;
    }

    ancestorKeyCopy = *ancestorKey;
    ancestor->keys().erase(ancestorKey);

    rightSibling = *next(nodeIt);

    //moves all the keys of the node to the auxiliar list, leaving the node empty
    std::list<T> auxList(std::move(node->keys()));
    auxList.push_back(ancestorKeyCopy);
    //moves all the keys of the right sibling to an auxiliar list, leaving the sibling empty
    auxList.merge(rightSibling->keys());

    Node<T> *newNode; //new node that goes in the middle of the current node and its right sibling
    newNode = new NormalNode<T>(this, ancestor, id++, ancestor->getHeight() + 1);

    auto putKeys = [&auxList](unsigned limit, Node<T>*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->keys().push_back( auxList.front() );
            auxList.pop_front();
        }
    };

    auto putKeyAncestor = [&ancestor, &auxList](){
        ancestor->addItem( auxList.front() );
        auxList.pop_front();
    };

    unsigned limitOne = keysSplitChild1;
    putKeys(limitOne, node);
    putKeyAncestor();

    unsigned limitTwo = keysSplitChild2;
    putKeys(limitTwo, newNode);
    putKeyAncestor();

    unsigned limitThree = keysSplitChild3;
    putKeys(limitThree, rightSibling);

    //accommodate children in the nodes.
    std::list<Node<T>*> auxListChildren(std::move(node->children()));
    auxListChildren.merge(rightSibling->children(), compareKeyNodes<T>);

    auto putChildren = [&auxListChildren](unsigned limit, Node<T>*& lNode){
        if (!auxListChildren.empty()) {
            for (std::size_t i = 0; i < limit; i++) {
                lNode->children().push_back( auxListChildren.front() );
                auxListChildren.pop_front();
                dynamic_cast<NormalNode<T>*>(lNode->children().back())->setAncestor(lNode);
            }
        }
    };

    putChildren(limitOne+1, node);
    putChildren(limitTwo+1, newNode);
    putChildren(limitThree+1, rightSibling);

    ancestor->addChild(newNode);
}

template <typename T>
void BStarTree<T>::mergeRootChildren(Node<T>* rootChildren)
{
    if(root->keys().size() > 1){
        merge(rootChildren);
    }else{
        //if the root only has one key, then it will have either
        //two or none children. If the root has no children, then
        // nothing else has to be done. If it has, then the code here
        // must merge the root with its two children
        //The calls to this method are made so it isn't ever called
        //when the node has no children, so if it reaches this place,
        //then it must have two children and has to merge with them.

        auto deleteRootChildren = [this](){
            root->keys().merge( root->children().front()->keys() );

            for(Node<T>* node : root->children().front()->children()){
                dynamic_cast<NormalNode<T>*>(node)->setAncestor(root);
            }
            //adds all the children of the first children of the root to the end of the list of
            //children of the root.
            root->children().splice(root->children().end(), root->children().front()->children(),
                            root->children().front()->children().begin(),
                            root->children().front()->children().end());

            for(Node<T> *child: (*root->children().begin())->children()){
                root->children().push_front(child);
            }
            delete root->children().front(); //deletes memory used
            root->children().pop_front(); //removes the deallocated memory from the container
        };

        deleteRootChildren();
        deleteRootChildren();
    }
}

//Case where there are left and right siblings.
//this can be used when mergin left and right
template <typename T>
void BStarTree<T>::merge(Node<T>* node)
{
    Node<T> *ancestor, *leftSibling, *rightSibling;
    typename std::list<T>::iterator ancestorKey;
    typename std::list<Node<T>*>::iterator nodeIt;

    ancestor = node->getAncestor();
    ancestorKey = ancestor->keys().begin();
    for(nodeIt = ancestor->children().begin(); *nodeIt != node; ++nodeIt){
        ++ancestorKey;
    }

    //this assigns the left sibling, node and right sibling depending on the node to
    //merge being the leftmost, rightmost or not any node in particular
    if(isLeftmost(node)){
        leftSibling = *nodeIt;
        node = *next(nodeIt);
        rightSibling = *next(next(nodeIt));

        ++ancestorKey;
    }else if(isRightmost(node)){
        leftSibling = *prev(prev(nodeIt));
        node = *prev(nodeIt);
        rightSibling = *nodeIt;

        --ancestorKey;
    }else{
        leftSibling = *prev(nodeIt);
        rightSibling = *next(nodeIt);
    }

    std::list<T> auxList( std::move(leftSibling->keys()) );
    auxList.push_back(*prev(ancestorKey));
    ancestor->keys().erase(prev(ancestorKey));

    auxList.merge(node->keys());
    auxList.push_back(*ancestorKey);
    ancestor->keys().erase(ancestorKey);

    auxList.merge(rightSibling->keys());

    auto putKeys = [&auxList](unsigned limit, Node<T>*& lNode){
        for (std::size_t i = 0; i < limit; i++) {
            lNode->keys().push_back( auxList.front() );
            auxList.pop_front();
        }
    };

    unsigned limitOne = auxList.size() / 2;
    unsigned limitTwo = limitOne;
    if(auxList.size() % 2 == 0){
        limitOne -= 1;
    }

    putKeys(limitOne, leftSibling);
    ancestor->addItem( auxList.front());
    auxList.pop_front();
    putKeys(limitTwo, node);

    //move all childrens before removing the right sibling
    std::list<Node<T>*> auxListChildren( std::move(leftSibling->children()) );
    auxListChildren.merge(node->children(), compareKeyNodes<T>);
    auxListChildren.merge(rightSibling->children(), compareKeyNodes<T>);

    auto putChildren = [&auxListChildren](unsigned limit, Node<T>*& lNode){
        if (!auxListChildren.empty()) {
            for (std::size_t i = 0; i < limit; i++) {
                lNode->children().push_back( auxListChildren.front() );
                auxListChildren.pop_front();
                dynamic_cast<NormalNode<T>*>(lNode->children().back())->setAncestor(lNode);
            }
        }
    };

    putChildren(limitOne+1, leftSibling);
    putChildren(limitTwo+1, node);

    delete rightSibling; //erases the memory used by this node
    ancestor->children().remove(rightSibling);
}

template <typename T>
Node<T>* BStarTree<T>::getGreaterMinor(Node<T> *node, T val) const
{
    if (node->isLeaf()) {
        return nullptr;
    }

    typename std::list<T>::iterator ancestorKey;
    typename std::list<Node<T>*>::iterator childIt;

    childIt = node->children().begin();

    for (ancestorKey = node->keys().begin(); *ancestorKey < val; ++ancestorKey) {
        ++childIt;
    }

    Node<T>* greaterMinor;
    greaterMinor = *childIt;
    while (!greaterMinor->isLeaf()) {
        greaterMinor = greaterMinor->children().back();
    }

    return greaterMinor;
}

template <typename T>
void BStarTree<T>::print() const
{
    Node<T>* currentNode;
    std::queue<Node<T>*> nodeQueue;
    unsigned oldHeight = 0;

    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        currentNode = nodeQueue.front();
        nodeQueue.pop();

            if(currentNode->getHeight() > oldHeight){
                std::cout << "Printing the nodes with height: " << ++oldHeight << std::endl;
            }

        currentNode->print();

        for(Node<T>* child : currentNode->children()){
            nodeQueue.push(child);
        }
    }
}

template <typename T>
unsigned BStarTree<T>::addFromFile(std::string filepath /*= files/add.txt*/)
{
    std::ifstream file;
    T number;
    unsigned addedCount = 0;

    file.open(filepath);

    if(!file.is_open()){
        std::cerr << "couldn't open the file with path: " << filepath << std::endl;
        return 0;
    }

    while(file >> number){
        if(add(number)){ //checks if it adds an element
            ++addedCount;
        }
    }

    file.close();

    return addedCount;
}

template <typename T>
unsigned BStarTree<T>::eraseFromFile(std::string filepath /*=files/erase.txt*/)
{
    std::ifstream file;
    T number;
    unsigned erasedCount = 0;

    file.open(filepath);

    if(!file.is_open()){
        std::cerr << "couldn't open the file with path: " << filepath << std::endl;
        return 0;
    }

    while(file >> number){
        if(erase(number)){ //checks if it erases an element
            ++erasedCount;
        }
    }

    file.close();

    return erasedCount;
}

template <typename T>
void BStarTree<T>::generateFile(int size /*= 10*/, std::string filepath /*= files/add.txt*/) const
{
    std::ofstream oFile;

    oFile.open(filepath);
    if(!oFile.is_open()){
        std::cerr << "Couldn't read file with path " << filepath << std::endl;
    }

    //creates a vector to put numbers from 0 to 9999, shuffles them and take size number of
    //elements from it so there are no repetitions.
    std::vector<T> vec(10000); //creates a vector with capacity 10000
    for(unsigned i = 0; i < 10000; ++i) vec[i] = i; //puts numbers from 0 to 9999 in vec
    std::random_shuffle(vec.begin(), vec.end()); //shuffles the vector

    for(int i = 0; i < size; ++i){
        oFile << vec[i]  << '\n'; //put the first size random elements in the file
    }

    oFile.close();
}

template <typename T>
void BStarTree<T>::testAddAndDelete(int elementsToLeave /*= 0*/, std::string filepath /*= files/add.txt*/)
{
    std::ifstream iaddFile;
    T number;

    int j = 0;
    int k = 0;

    std::vector<T> elements;
    iaddFile.open(filepath);
    if(!iaddFile.is_open()){
        std::cerr << "Couldn't read file with path: " << filepath << std::endl;
        return;
    }

    while(iaddFile >> number){
        if(add(number)){
            elements.push_back(number);
            ++j;
        }
    }

    iaddFile.close();

    std::random_shuffle(elements.begin(), elements.end()); //shuffles the vector

    int elementsToErase = elements.size() - elementsToLeave;
    for(int i = 0; i < elementsToErase; ++i){
        if(erase(elements[i])){
            ++k;
        }
    }

    std::cout << "Number of additions: " << j << std::endl;
    std::cout << "Number of delitions: " << k << std::endl;
}

