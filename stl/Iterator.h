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

    UnorderedMapIterator(const UnorderedMapIterator& p_other);
    UnorderedMapIterator(UnorderedMap<_KeyType, _DataType, _Hash>* p_map);

    UnorderedMapIterator& operator=(const UnorderedMapIterator& p_other);

    UnorderedMapIterator& operator++();

    UnorderedMapIterator operator++(int);
    UnorderedMapIterator& operator--();

    UnorderedMapIterator operator--(int);
    reference operator*() const;

    _DataType* operator->() const;

    bool operator==(const UnorderedMapIterator& p_other) const;

    bool operator!=(const UnorderedMapIterator& p_other) const;

    void setIndex(size_t p_index);
    size_t getIndex();
    void setListIterator(ListIterator p_listIterator);
    ListIterator getListIterator();

private:
    UnorderedMap<_KeyType, _DataType, _Hash>* m_map;
    size_t m_index;
    ListIterator m_listIterator;
};

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::UnorderedMapIterator(const UnorderedMapIterator& p_other)
    : m_map(p_other.m_map), m_index(p_other.m_index), m_listIterator(p_other.m_listIterator)
{}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>& UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator=(const UnorderedMapIterator& p_other)
{
    if (this != &p_other) 
    {
        m_map = p_other.m_map;
        m_index = p_other.m_index;
        m_listIterator = p_other.m_listIterator;
    }
    return *this;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>& UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator++()
{
    ListIterator newlistIterator = ++m_listIterator;
    --m_listIterator;
    ListIterator endlistIterator = m_map->end().getListIterator();
    if (newlistIterator != endlistIterator) 
    {
        size_t newindex = m_index;
        while (++newindex < m_map->m_table.size()) 
        {
            if (!m_map->m_table[newindex].empty()) 
            {
                m_index = newindex;
                m_listIterator = m_map->m_table[m_index].begin();
                break;
            }
        }
    }
    else ++m_listIterator;
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
    if (m_listIterator == m_map->m_table[m_index].begin()) 
    {
        while (--m_index >= 0) 
        {
            if (!m_map->m_table[m_index].empty()) 
            {
                m_listIterator = --m_map->m_table[m_index].end();
                break;
            }
        }
    }
    else --m_listIterator;
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
    return (*m_listIterator);
}

template <class _KeyType, class _DataType, class _Hash>
_DataType* UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator->() const
{
    return &(m_listIterator->second);
}

template <class _KeyType, class _DataType, class _Hash>
bool UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator==(const UnorderedMapIterator& p_other) const
{
    return m_map == p_other.m_map && m_index == p_other.m_index && m_listIterator == p_other.m_listIterator;
}

template <class _KeyType, class _DataType, class _Hash>
bool UnorderedMapIterator<_KeyType, _DataType, _Hash>::operator!=(const UnorderedMapIterator& p_other) const
{
    return !(*this == p_other);
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::UnorderedMapIterator(UnorderedMap<_KeyType, _DataType, _Hash>* p_map)
    : m_map(p_map), m_index(0), m_listIterator()
{}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::UnorderedMapIterator()
    : m_map(nullptr), m_index(0), m_listIterator()
{}

template <class _KeyType, class _DataType, class _Hash>
void UnorderedMapIterator<_KeyType, _DataType, _Hash>::setIndex(size_t p_index)
{
    m_index = p_index;
}

template <class _KeyType, class _DataType, class _Hash>
void UnorderedMapIterator<_KeyType, _DataType, _Hash>::setListIterator(UnorderedMapIterator<_KeyType, _DataType, _Hash>::ListIterator p_listIterator)
{
    m_listIterator = p_listIterator;
}

template <class _KeyType, class _DataType, class _Hash>
size_t UnorderedMapIterator<_KeyType, _DataType, _Hash>::getIndex()
{
    return m_index;
}

template <class _KeyType, class _DataType, class _Hash>
UnorderedMapIterator<_KeyType, _DataType, _Hash>::ListIterator UnorderedMapIterator<_KeyType, _DataType, _Hash>::getListIterator()
{
    return m_listIterator;
}