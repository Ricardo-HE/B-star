
template <typename T>
NormalNode<T>::NormalNode(BStarTree<T> const * tree, Node<T>* ancestor, unsigned id): Node<T>(tree, ancestor)
{
    this->id = id;
}

template <typename T>
bool NormalNode<T>::isOverloaded() const
{
    return this->keysList.size() > this->tree->maxKeysNNode() ? true : false;
}

template <typename T>
bool NormalNode<T>::isFull() const
{
    return this->keysList.size() == this->tree->maxKeysNNode() ? true : false;
}

template <typename T>
bool NormalNode<T>::isUnderloaded() const
{
    return this->keysList.size() < this->tree->minKeysNNode() ? true : false;
}

template <typename T>
bool NormalNode<T>::isAtMinimum() const
{
    return this->keysList.size() == this->tree->minKeysNNode() ? true : false;
}

