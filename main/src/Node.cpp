
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
void Node<T>::print() const
{

    if(!keysList.empty()){
        for(auto key : keysList){
            std::cout << key << " - ";
        }
        std::cout << "\b\b \b"; //erases the last -

        std::cout <<  "\n\n";
    }
}

template <typename T>
bool compareKeyNodes(Node<T>* nodeA, Node<T>* nodeB)
{
    return *nodeA->keys().begin() < *nodeB->keys().begin();
}
