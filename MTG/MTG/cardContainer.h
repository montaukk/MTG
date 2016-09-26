#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H

#include <vector>
#include <algorithm>
#include "card.h"

template <class T>
class cardContainer
{
private:
    std::vector<T> collection;
    unsigned long _maxSize;

public:
    cardContainer(unsigned long maxSize);

    ~cardContainer();

    T draw();
    void discardTo(const cardContainer &to);
    void drawFrom(cardContainer &from);
    void add(const T &card);
    void remove(typename std::vector<T>::iterator position);
    T at(const unsigned long position);
    void shuffle();
    unsigned long _size();
//    bool _copy(cardContainer &other);
    typename std::vector<T>::iterator _begin();
};

template <class T>
cardContainer<T>::cardContainer(unsigned long maxSize)
    :_maxSize(maxSize)
{
}

template <class T>
cardContainer<T>::~cardContainer()
{}


template <class T>
T cardContainer<T>::draw()
{
    return this->collection.pop_back();
}

template <class T>
void cardContainer<T>::drawFrom(cardContainer &from)
{
    this->collection.push_back(from.collection.back());
    from.collection.pop_back();
}

template <class T>
void cardContainer<T>::discardTo(const cardContainer &to)
{
}

template <class T>
void cardContainer<T>::add(const T &card)
{
    this->collection.push_back(card);
}

template <class T>
void cardContainer<T>::remove(typename std::vector<T>::iterator position)
{
    this->collection.erase(position);
}

template<class T>
T cardContainer<T>::at(const unsigned long position)
{
    return this->collection.at(position);
}

template <class T>
void cardContainer<T>::shuffle()
{
    std::random_shuffle(this->collection.begin(), this->collection.end());
}

template <class T>
unsigned long cardContainer<T>::_size()
{
    return this->collection.size();
}

//template <class T>
//bool cardContainer<T>::_copy(cardContainer &other)
//{
//    if (this->_maxSize == other._maxSize)
//    {
//        this->collection.assign(other.collection.begin());
//        return true;
//    }
//    return false;
//}

template<class T>
typename std::vector<T>::iterator cardContainer<T>::_begin()
{
    return this->collection.begin();
}

#endif // CARDCONTAINER_H