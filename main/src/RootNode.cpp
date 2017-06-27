
template <typename T>
RootNode<T>::RootNode(BStarTree const * tree, Node<T>* ancestor, unsigned id, unsigned height): Node(tree, ancestor)
{
    //keysList = std::list<T>(); //creates an empty list
    //childList = std::list<Node<T>*>(); //creates an empty list
    this->id = id;
    this->height = height;
}

template <typename T>
bool RootNode<T>::isOverloaded() const
{
    return keysList.size() > tree->maxKeysRNode() ? true : false;
}

template <typename T>
bool RootNode<T>::isFull() const
{
    return keysList.size() == tree->maxKeysRNode() ? true : false;
}

template <typename T>
bool RootNode<T>::isUnderloaded() const
{
    return keysList.size() < tree->minKeysRNode() ? true : false;
}

template <typename T>
bool RootNode<T>::isAtMinimum() const
{
    return keysList.size() == tree->minKeysRNode() ? true : false;
}
