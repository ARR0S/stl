#pragma once
#include <utility>
#include <algorithm>
template <typename Iterator, typename Predicate>
Iterator findIf(Iterator beg, Iterator end, Predicate pred)
{
    while (beg != end) {
        if (pred(*beg)) {
            return beg;
        }
        ++beg;
    }
    return end;
}

template <typename Iterator>
Iterator minElement(Iterator beg, Iterator end)
{
    Iterator minIter = beg;
    ++beg;
    while (beg != end) {
        if (*beg < *minIter) {
            minIter = beg;
        }
        ++beg;
    }
    return minIter;
}

template <typename Iterator>
Iterator maxElement(Iterator beg, Iterator end)
{
    Iterator maxIter = beg;
    ++beg;
    while (beg != end) {
        if (*beg > *maxIter) {
            maxIter = beg;
        }
        ++beg;
    }
    return maxIter;
}
template <typename Iterator, typename Operation>
void forEach(Iterator begin, Iterator end, Operation op) {
        for (Iterator it = begin; it != end; ++it) {
            op(*it);
        }
}

template <typename Iterator, typename Operation>
void Sort(Iterator beg, Iterator end, Operation comp)
{
    bool swapped = true;
    while (swapped) {
        swapped = false;
        Iterator current = beg;
        Iterator next = ++current;
        current = beg;
        while (next != end) {
            if (comp(*next, *current)) {
                std::iter_swap(next, current);
            }
            ++current;
            ++next;
        }
    }
}

template <typename InputIt, typename OutputIt, typename Predicate>
OutputIt copyIf(InputIt sourceBeg, InputIt sourceEnd, OutputIt destBeg, Predicate pred)
{
    while (sourceBeg != sourceEnd)
    {
        if (pred(*sourceBeg))
        {
            *destBeg = *sourceBeg;
            ++destBeg;
        }
        ++sourceBeg;
    }
    return destBeg;
}

