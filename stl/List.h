#pragma once
#include <cstddef>
#include <stdexcept>

template<class T>
class List {
public:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr)
            : data(d), next(n)
        {
        }
    };

    // Итератор для класса List
    class Iterator {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        Iterator();
        Iterator(Node* node, Node* tail, Node* head);
        reference operator*() const;

        pointer operator->() const;

        Iterator operator++();

        Iterator operator++(int);
        Iterator& operator--();

        Iterator operator--(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;
        typename List<T>::Iterator& operator=(const Iterator& other);

    private:
        Node* current;
        Node* tail;
        Node* head; // Добавленное поле
    };

public:
    List();
    ~List();
    bool empty() const;
    size_t size() const;
    void push_back(const T& value);
    Node* find(const T& value) const;
    void remove(const T& value);

    Iterator begin() const;

    Iterator end() const;

private:
    Node* head;
    Node* tail;
    size_t listSize;
};

template<class T>
List<T>::List()
    : head(nullptr), tail(nullptr), listSize(0)
{
}

template<class T>
List<T>::~List() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<class T>
bool List<T>::empty() const {
    return listSize == 0;
}

template<class T>
size_t List<T>::size() const {
    return listSize;
}

template<class T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);

    if (empty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    listSize++;
}

template<class T>
typename List<T>::Node* List<T>::find(const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value)
            return current;
        current = current->next;
    }
    return nullptr;
}

template<class T>
void List<T>::remove(const T& value) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            if (previous == nullptr) {
                // Удаляемый элемент - голова списка
                head = current->next;
            }
            else {
                // Удаляемый элемент - не голова списка
                previous->next = current->next;
            }

            if (current == tail) {
                // Удаляемый элемент - хвост списка
                tail = previous;
            }

            delete current;
            listSize--;
            return;
        }

        previous = current;
        current = current->next;
    }
}

template<class T>
List<T>::Iterator::Iterator()
    : current(nullptr), tail(nullptr), head(nullptr)
{
}

template<class T>
List<T>::Iterator::Iterator(Node* node, Node* tail, Node* head)
    : current(node), tail(tail), head(head)
{
}
template<class T>
List<T>::Iterator::reference List<T>::Iterator::operator*() const {
    return current->data;
}
template<class T>
List<T>::Iterator::pointer List<T>::Iterator::operator->() const {
    return &(current->data);
}
template<class T>
List<T>::Iterator List<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}
template<class T>
List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    if (current == nullptr) {
        // Итератор указывает за пределы списка, перемещаем его на хвост
        current = tail;
    }
    else {
        Node* temp = this->head;
        while (temp->next != current) {
            temp = temp->next;
        }
        current = temp;
    }
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}
template<class T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current && tail == other.tail;;
}
template<class T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& other) {
    if (this != &other) {
        current = other.current;
        head = other.current;
        tail = other.tail;
    }
    return *this;
}
template<class T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head, tail, head);
}
template<class T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr, tail, head);
}