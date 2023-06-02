#pragma once
#include <cstddef>
#include <stdexcept>

template<class T>
class List {
public:
    struct Node {
        T m_data;
        Node* m_next;
        Node(const T& p_d, Node* p_n = nullptr)
            : m_data(p_d), m_next(p_n)
        {}
    };

    // Итератор для класса List
    class Iterator {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        Iterator();
        Iterator(Node* p_node, Node* p_tail, Node* p_head);
        reference operator*() const;
        pointer operator->() const;
        Iterator operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& p_other) const;
        bool operator!=(const Iterator& p_other) const;
        typename List<T>::Iterator& operator=(const Iterator& p_other);

    private:
        Node* m_current;
        Node* m_tail;
        Node* m_head;
    };

public:
    List();
    ~List();
    bool empty() const;
    size_t size() const;
    void push_back(const T& p_value);
    Node* find(const T& p_value) const;
    void remove(const T& p_value);
    Iterator begin() const;
    Iterator end() const;

private:
    Node* m_head;
    Node* m_tail;
    size_t m_listSize;
};

template<class T>
List<T>::List()
    : m_head(nullptr), m_tail(nullptr), m_listSize(0)
{}

template<class T>
List<T>::~List() 
{
    while (m_head != nullptr) 
    {
        Node* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
}

template<class T>
bool List<T>::empty() const 
{
    return m_listSize == 0;
}

template<class T>
size_t List<T>::size() const 
{
    return m_listSize;
}

template<class T>
void List<T>::push_back(const T& p_value) 
{
    Node* newNode = new Node(p_value);

    if (empty()) 
    {
        m_head = m_tail = newNode;
    }
    else 
    {
        m_tail->m_next = newNode;
        m_tail = newNode;
    }

    m_listSize++;
}

template<class T>
typename List<T>::Node* List<T>::find(const T& p_value) const 
{
    Node* current = m_head;
    while (current != nullptr) 
    {
        if (current->m_data == p_value)
            return current;
        current = current->m_next;
    }
    return nullptr;
}

template<class T>
void List<T>::remove(const T& p_value) 
{
    Node* current = m_head;
    Node* previous = nullptr;

    while (current != nullptr) 
    {
        if (current->m_data == p_value) 
        {
            if (previous == nullptr) 
            {
                m_head = current->m_next;
            }
            else 
            {
                previous->m_next = current->m_next;
            }
            if (current == m_tail) 
            {
                m_tail = previous;
            }
            delete current;
            m_listSize--;
            return;
        }
        previous = current;
        current = current->m_next;
    }
}

template<class T>
List<T>::Iterator::Iterator()
    : m_current(nullptr), m_tail(nullptr), m_head(nullptr)
{}

template<class T>
List<T>::Iterator::Iterator(Node* p_node, Node* p_tail, Node* p_head)
    : m_current(p_node), m_tail(p_tail), m_head(p_head)
{}

template<class T>
List<T>::Iterator::reference List<T>::Iterator::operator*() const 
{
    return m_current->m_data;
}

template<class T>
List<T>::Iterator::pointer List<T>::Iterator::operator->() const 
{
    return &(m_current->m_data);
}

template<class T>
List<T>::Iterator List<T>::Iterator::operator++() 
{
    m_current = m_current->m_next;
    return *this;
}

template<class T>
List<T>::Iterator List<T>::Iterator::operator++(int) 
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() 
{
    if (m_current == nullptr) 
    {
        m_current = m_tail;
    }
    else 
    {
        Node* temp = this->m_head;
        while (temp->m_next != m_current) 
        {
            temp = temp->m_next;
        }
        m_current = temp;
    }
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) 
{
    Iterator temp = *this;
    --(*this);
    return temp;
}

template<class T>
bool List<T>::Iterator::operator==(const Iterator& p_other) const 
{
    return m_current == p_other.m_current && m_tail == p_other.m_tail;;
}

template<class T>
bool List<T>::Iterator::operator!=(const Iterator& p_other) const 
{
    return !(*this == p_other);
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& p_other) 
{
    if (this != &p_other) 
    {
        m_current = p_other.m_current;
        m_head = p_other.m_current;
        m_tail = p_other.m_tail;
    }
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::begin() const 
{
    return Iterator(m_head, m_tail, m_head);
}

template<class T>
typename List<T>::Iterator List<T>::end() const 
{
    return Iterator(nullptr, m_tail, m_head);
}