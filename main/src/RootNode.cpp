
template <typename T>
RootNode<T>::RootNode(BStarTree<T> const * tree, Node<T>* ancestor, unsigned id, unsigned height): Node<T>(tree, ancestor)
{
    //this->keysList = std::list<T>(); //creates an empty list
    //childList = std::list<Node<T>*>(); //creates an empty list
    this->id = id;
    this->height = height;
}

template <typename T>
bool RootNode<T>::isOverloaded() const
{
    return this->keysList.size() > this->tree->maxKeysRNode() ? true : false;
}

template <typename T>
bool RootNode<T>::isFull() const
{
    return this->keysList.size() == this->tree->maxKeysRNode() ? true : false;
}

template <typename T>
bool RootNode<T>::isUnderloaded() const
{
    return this->keysList.size() < this->tree->minKeysRNode() ? true : false;
}

template <typename T>
bool RootNode<T>::isAtMinimum() const
{
    return this->keysList.size() == this->tree->minKeysRNode() ? true : false;
}
