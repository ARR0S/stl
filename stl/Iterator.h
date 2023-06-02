#pragma once
#include <iterator>
#include "List.h"
template<class _KeyType, class _DataType, class _Hash >
class UnorderedMap;

template <class _KeyType, class _DataType, class _Hash = std::hash<_KeyType>>
class UnorderedMapIterator
{
public:
    using KeyValuePair = std::pair<_KeyType, _DataType>;
    using ListType = List<KeyValuePair>;
    using ListIterator = typename ListType::Iterator;
    using value_type = KeyValuePair;
    using reference = KeyValuePair&;

    UnorderedMapIterator();

    UnorderedMapIterator(const UnorderedMapIterator& other);
    UnorderedMapIterator(UnorderedMap<_KeyType, _DataType, _Hash>* map);

    UnorderedMapIterator& operator=(const UnorderedMapIterator& other);

    UnorderedMapIterator& operator++();

    UnorderedMapIterator operator++(int);
    UnorderedMapIterator& operator--();

    UnorderedMapIterator operator--(int);
    reference operator*() const;

    _DataType* operator->() const;

    bool operator==(const UnorderedMapIterator& other) const;

    bool operator!=(const UnorderedMapIterator& other) const;

    void setIndex(size_t p_index);
    size_t getIndex();
    void setListIterator(ListIterator p_listIterator);
    ListIterator getListIterator();

private:
    UnorderedMap<_KeyType, _DataType, _Hash>* map;
    size_t index;
    ListIterator listIterator;
};

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::UnorderedMapIterator(const UnorderedMapIterator& other)
    : map(other.map), index(other.index), listIterator(other.listIterator)
{
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>& UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator=(const UnorderedMapIterator& other)
{
    if (this != &other) {
        map = other.map;
        index = other.index;
        listIterator = other.listIterator;
    }
    return *this;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>& UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator++()
{
    ListIterator newlistIterator = ++listIterator;
    --listIterator;
    ListIterator endlistIterator = map->end().getListIterator();
    if (newlistIterator != endlistIterator) {
        size_t newindex = index;
        while (++newindex < map->m_table.size()) {
            if (!map->m_table[newindex].empty()) {
                index = newindex;
                listIterator = map->m_table[index].begin();
                break;
            }
        }
    }
    else ++listIterator;
    return *this;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash> UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator++(int)
{
    UnorderedMapIterator temp = *this;
    ++(*this);
    return temp;
}
template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>& UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator--()
{
    if (listIterator == map->m_table[index].begin()) {
        while (--index >= 0) {
            if (!map->m_table[index].empty()) {
                listIterator = --map->m_table[index].end();
                break;
            }
        }
    }
    else {
        --listIterator;
    }
    return *this;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash> UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator--(int)
{
    UnorderedMapIterator temp = *this;
    --(*this);
    return temp;
}
template <class _KeyType, class _DataType, class _Hash>
typename UnorderedMapIterator<_KeyType, _DataType, _Hash>::reference UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator*() const
{
    return (*listIterator);
}

template <class _KeyType, class _DataType, class _Hash>
_DataType* UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator->() const
{
    return &(listIterator->second);
}
template <class _KeyType, class _DataType, class _Hash>
bool UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator==(const UnorderedMapIterator& other) const
{
    return map == other.map && index == other.index && listIterator == other.listIterator;
}

template <class _KeyType, class _DataType, class _Hash>
bool UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator!=(const UnorderedMapIterator& other) const
{
    return !(*this == other);
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::UnorderedMapIterator(UnorderedMap<_KeyType, _DataType, _Hash>* map)
    : map(map), index(0), listIterator()
{
}
template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::UnorderedMapIterator()
    : map(nullptr), index(0), listIterator()
{
}
template <class _KeyType, class _DataType, class _Hash>
void UnorderedMapIterator<_KeyType, _DataType, _Hash>::setIndex(size_t p_index)
{
    index = p_index;
}
template <class _KeyType, class _DataType, class _Hash>
void UnorderedMapIterator<_KeyType, _DataType, _Hash>::setListIterator(UnorderedMapIterator<_KeyType, _DataType, _Hash>::ListIterator p_listIterator)
{
    listIterator = p_listIterator;
}
template <class _KeyType, class _DataType, class _Hash>
size_t UnorderedMapIterator<_KeyType, _DataType, _Hash>::getIndex()
{
    return index;
}
template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::ListIterator UnorderedMapIterator<_KeyType, _DataType, _Hash>::getListIterator()
{
    return listIterator;
}