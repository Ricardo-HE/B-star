
template <typename T>
RootNode<T>::RootNode(BStarTree<T> const * tree, Node<T>* ancestor, unsigned id): Node<T>(tree, ancestor)
{
    this->id = id;
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
