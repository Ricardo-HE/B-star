
template <typename T>
void Node<T>::addItem(T elem)
{
    auto key = keys().begin();
    while(*key < elem && key != keys().end()){
        ++key;
    }

    keys().insert(key, elem);
}

template <typename T>
void Node<T>::addChild(Node<T>* child)
{
    auto childIt = children().begin();
    while(compareKeyNodes(*childIt, child) && childIt != children().end()){
        ++childIt;
    }

    children().insert(childIt, child);
}


template <typename T>
T Node<T>::popFrontKey()
{
    T copy = keys().front();
    keys().pop_front();

    return copy;
}


template <typename T>
T Node<T>::popBackKey()
{
    T copy = keys().back();
    keys().pop_back();

    return copy;
}

template <typename T>
Node<T>* Node<T>::popFrontChild()
{
    Node<T>* copy = children().front();
    children().pop_front();

    return copy;
}

template <typename T>
Node<T>* Node<T>::popBackChild()
{
    Node<T>* copy = children().back();
    children().pop_back();

    return copy;
}

template <typename T>
void Node<T>::putKeys(std::list<T>& takeList, int limit)
{
    for(int i = 0; i < limit; i++){
        keys().push_back( takeList.front() );
        takeList.pop_front();
    }
}

template <typename T>
void Node<T>::putChildren(std::list<Node<T>*>& takeList, int limit)
{
    for (int i = 0; i < limit; i++) {
        children().push_back( takeList.front() );
        takeList.pop_front();
        dynamic_cast<NormalNode<T>*>(children().back())->setAncestor(this);
    }
}

template <typename T>
void Node<T>::print() const
{

    std::cout << "Id: " << this->id << " | ";
    this->ancestor != nullptr ? std::cout << this->ancestor->id : std::cout << ' ';
    std::cout << std::endl;

    std::cout << "keys: ";
    for(auto key : keysList){
        std::cout << key << " ";
    }

    std::cout <<  "\n\n";
}

template <typename T>
bool compareKeyNodes(Node<T>* nodeA, Node<T>* nodeB)
{
    return *nodeA->keys().begin() < *nodeB->keys().begin();
}
