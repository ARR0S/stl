#pragma once
#include "Iterator.h"
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <utility>
#include <initializer_list>
#include <functional>
#include <iostream>
template <class _KeyType, class _DataType, class _Hash>
class UnorderedMapIterator;
template<class _KeyType, class _DataType, class _Hash = std::hash<_KeyType>>
class UnorderedMap
{
private:
    using KeyValuePair = std::pair< _KeyType, _DataType>;
    using ListType = List<KeyValuePair>;
    using TableType = std::vector<ListType>;
    
    TableType m_table;
    size_t m_size;
    float m_maxLoadFactor;

    size_t calculateIndex(const _KeyType& key) const;

    void rehash(size_t newCapacity);
    void insertOrUpdate(_KeyType&& key, _DataType&& value);
    friend class UnorderedMapIterator<_KeyType, _DataType, _Hash>;

public:
    UnorderedMap();
    explicit UnorderedMap(size_t segments);
    template<class InputIt>
    UnorderedMap(InputIt first, InputIt last);
    UnorderedMap(std::initializer_list<KeyValuePair> init);
    UnorderedMap(const UnorderedMap& other);
    UnorderedMap(UnorderedMap&& other) noexcept;
    ~UnorderedMap();
    UnorderedMap& operator=(const UnorderedMap& other);
    UnorderedMap& operator=(UnorderedMap&& other) noexcept;
    _DataType& operator[](const _KeyType& key);
    const _DataType& operator[](const _KeyType& key) const;
    float maxLoadFactor() const;
    void maxLoadFactor(float value);
    _DataType& at(const _KeyType& key);
    const _DataType& at(const _KeyType& key) const;
    using iterator = UnorderedMapIterator<_KeyType, _DataType, _Hash>;
    iterator begin();
    iterator end();
    iterator insert(const KeyValuePair& pair);
    iterator insert(KeyValuePair&& pair);
    void erase(const _KeyType& key);
    iterator erase(iterator pos);
    void reserve(size_t num);
    bool empty() const;
    size_t size() const;
    void clear();
};

template<class _KeyType, class _DataType, class _Hash>
size_t UnorderedMap<_KeyType, _DataType, _Hash>::calculateIndex(const _KeyType& key) const
{
    return std::hash<_KeyType>{}(key) % m_table.size();
}

template<class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::rehash(size_t newCapacity)
{
    if (newCapacity <= m_table.size())
        return;

    TableType newTable(newCapacity);
    for (auto& list : m_table) {
        for (auto& pair : list) {
            size_t index = std::hash<_KeyType>{}(pair.first) % newCapacity;
            newTable[index].push_back(pair);
        }
    }
    m_table = std::move(newTable);
}

template<class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::insertOrUpdate(_KeyType&& key, _DataType&& value)
{
    size_t index = calculateIndex(key);
    for (auto& pair : m_table[index]) {
        if (pair.first == key) {
            pair.second = std::move(value);
            return;
        }
    }
    m_table[index].push_back(std::make_pair(std::move(key), std::move(value)));
    m_size++;
    if (static_cast<float>(m_size) / m_table.size() > m_maxLoadFactor)
        rehash(m_table.size() * 2);
}

template<class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::reserve(size_t num)
{
    if (num > m_table.size())
        rehash(num);
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap()
    : m_table(8), m_size(0), m_maxLoadFactor(0.75f)
{
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(size_t segments)
    : m_table(segments), m_size(0), m_maxLoadFactor(0.75f)
{
}

template<class _KeyType, class _DataType, class _Hash>
template<class InputIt>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(InputIt first, InputIt last)
    : m_table(8), m_size(0), m_maxLoadFactor(0.75f)
{
    reserve(std::distance(first, last));
    for (auto it = first; it != last; ++it) {
        insertOrUpdate(static_cast<_KeyType>((*it).first), static_cast<_DataType>((*it).second));
    }
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(std::initializer_list<KeyValuePair> init)
    : UnorderedMap(init.begin(), init.end())
{
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(const UnorderedMap& other)
    : m_table(other.m_table), m_size(other.m_size), m_maxLoadFactor(other.m_maxLoadFactor)
{
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap(UnorderedMap&& other) noexcept
    : m_table(std::move(other.m_table)), m_size(other.m_size), m_maxLoadFactor(other.m_maxLoadFactor)
{
    other.m_size = 0;
    other.m_maxLoadFactor = 0;
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::~UnorderedMap()
{
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>& UnorderedMap<_KeyType, _DataType, _Hash>::operator=(const UnorderedMap& other)
{
    if (this == &other)
        return *this;

    m_table = other.m_table;
    m_size = other.m_size;
    m_maxLoadFactor = other.m_maxLoadFactor;
    return *this;
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>& UnorderedMap<_KeyType, _DataType, _Hash>::operator=(UnorderedMap&& other) noexcept
{
    if (this == &other)
        return *this;

    m_table = std::move(other.m_table);
    m_size = other.m_size;
    m_maxLoadFactor = other.m_maxLoadFactor;
    other.m_size = 0;
    other.m_maxLoadFactor = 0;
    return *this;
}

template<class _KeyType, class _DataType, class _Hash>
_DataType& UnorderedMap<_KeyType, _DataType, _Hash>::operator[](const _KeyType& key)
{
    size_t index = calculateIndex(key);
    for (auto& pair : m_table[index]) {
        if (pair.first == key)
            return pair.second;
    }
    throw std::out_of_range("Element not found");
}

template<class _KeyType, class _DataType, class _Hash>
const _DataType& UnorderedMap<_KeyType, _DataType, _Hash>::operator[](const _KeyType& key) const
{
    size_t index = calculateIndex(key);
    for (const auto& pair : m_table[index]) {
        if (pair.first == key)
            return pair.second;
    }
    throw std::out_of_range("Element not found");
}

template<class _KeyType, class _DataType, class _Hash>
float UnorderedMap<_KeyType, _DataType, _Hash>::maxLoadFactor() const
{
    return m_maxLoadFactor;
}

template<class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::maxLoadFactor(float value)
{
    m_maxLoadFactor = value;
    if (static_cast<float>(m_size) / m_table.size() > m_maxLoadFactor)
        rehash(m_table.size() * 2);
}

template<class _KeyType, class _DataType, class _Hash>
_DataType& UnorderedMap<_KeyType, _DataType, _Hash>::at(const _KeyType& key)
{
    size_t index = calculateIndex(key);
    for (auto& pair : m_table[index]) {
        if (pair.first == key)
            return pair.second;
    }
    throw std::out_of_range("Element not found");
}

template<class _KeyType, class _DataType, class _Hash>
const _DataType& UnorderedMap<_KeyType, _DataType, _Hash>::at(const _KeyType& key) const
{
    size_t index = calculateIndex(key);
    for (const auto& pair : m_table[index]) {
        if (pair.first == key)
            return pair.second;
    }
    throw std::out_of_range("Key not found");
}

template<class _KeyType, class _DataType, class _Hash>
typename UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::begin()
{
    if (m_size == 0)
        return iterator();

    size_t firstNonEmptyIndex = 0;
    for (size_t i = 0; i < m_table.size(); ++i) {
        if (!m_table[i].empty()) {
            firstNonEmptyIndex = i;
            break;
        }
    }
    iterator it(this);
    it.setIndex(firstNonEmptyIndex);
    it.setListIterator(m_table[firstNonEmptyIndex].begin());
    return it;
}

template<class _KeyType, class _DataType, class _Hash>
typename UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::end()
{
    if (m_size == 0)
        return iterator();

    size_t lastNonEmptyIndex = 0;
    for (size_t i = 0; i < m_table.size(); ++i) {
        if (!m_table[i].empty()) {
            lastNonEmptyIndex = i;
        }
    }
    iterator it(this);
    it.setIndex(lastNonEmptyIndex);
    it.setListIterator(m_table[lastNonEmptyIndex].end());
    return it;
}


template<class _KeyType, class _DataType, class _Hash>
typename UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::insert(const KeyValuePair& pair)
{
    _KeyType key = pair.first;
    _DataType value = pair.second;
    reserve(m_size+1);
    size_t index = calculateIndex(key);
    insertOrUpdate(key, value);
    UnorderedMap<_KeyType, _DataType, _Hash>::iterator iter(this);
    iter.setIndex(index);
    iter.setListIterator(m_table[index].end());  // Устанавливаем итератор на последний элемент списка
    return iter;
}

template<class _KeyType, class _DataType, class _Hash>
typename UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::insert(KeyValuePair&& pair)
{
    _KeyType key = std::move(pair.first);
    _DataType value = std::move(pair.second);
    reserve(m_size + 1);
    size_t index = calculateIndex(key);
    insertOrUpdate(std::move(key), std::move(value));
    UnorderedMap<_KeyType, _DataType, _Hash>::iterator iter(this);
    iter.setIndex(index);
    iter.setListIterator(m_table[index].end());  // Устанавливаем итератор на последний элемент списка
    return iter;
}

template<class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::erase(const _KeyType& key)
{
    size_t index = calculateIndex(key);
    for (auto it = m_table[index].begin(); it != m_table[index].end(); ++it) {
        if ((*it).first == key) {
            m_table[index].remove(*it);
            m_size--;
            return;
        }
    }
}

template<class _KeyType, class _DataType, class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::iterator UnorderedMap<_KeyType, _DataType, _Hash>::erase(iterator pos)
{
    iterator it = pos;
    size_t index = calculateIndex((*pos).first);
    m_table[index].remove(*pos);
    m_size--;
    return it++;
}

template<class _KeyType, class _DataType, class _Hash>
bool UnorderedMap<_KeyType, _DataType, _Hash>::empty() const
{
    return m_size == 0;
}

template<class _KeyType, class _DataType, class _Hash>
size_t UnorderedMap<_KeyType, _DataType, _Hash>::size() const
{
    return m_size;
}

template<class _KeyType, class _DataType, class _Hash>
void UnorderedMap<_KeyType, _DataType, _Hash>::clear()
{
    m_table.clear();
    m_size = 0;
}