
template <typename T>
NormalNode<T>::NormalNode(BStarTree<T> const * tree, Node<T>* ancestor, unsigned id, unsigned height): Node<T>(tree, ancestor)
{
    //this might become handy later
    //const unsigned normalNodeOrder = ceil( (2*order-1) / 3 );
    this->id = id;
    this->height = height;
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

