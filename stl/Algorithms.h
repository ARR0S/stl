#pragma once
#include <utility>
#include <algorithm>
template <typename Iterator, typename Predicate>
Iterator findIf(Iterator p_beg, Iterator p_end, Predicate p_pred)
{
    while (p_beg != p_end) 
    {
        if (p_pred(*p_beg)) 
        {
            return p_beg;
        }
        ++p_beg;
    }
    return p_end;
}

template <typename Iterator>
Iterator minElement(Iterator p_beg, Iterator p_end)
{
    Iterator minIter = p_beg;
    ++p_beg;
    while (p_beg != p_end) 
    {
        if (*p_beg < *minIter) 
        {
            minIter = p_beg;
        }
        ++p_beg;
    }
    return minIter;
}

template <typename Iterator>
Iterator maxElement(Iterator p_beg, Iterator p_end)
{
    Iterator maxIter = p_beg;
    ++p_beg;
    while (p_beg != p_end) 
    {
        if (*p_beg > *maxIter) 
        {
            maxIter = p_beg;
        }
        ++p_beg;
    }
    return maxIter;
}
template <typename Iterator, typename Operation>
void forEach(Iterator p_begin, Iterator p_end, Operation p_op) 
{
        for (Iterator it = p_begin; it != p_end; ++it) 
        {
            p_op(*it);
        }
}

template <typename Iterator, typename Operation>
void Sort(Iterator p_beg, Iterator p_end, Operation p_comp)
{
    bool swapped = true;
    while (swapped) 
    {
        swapped = false;
        Iterator current = p_beg;
        Iterator next = ++current;
        current = p_beg;
        while (next != p_end) 
        {
            if (p_comp(*next, *current)) 
            {
                std::iter_swap(next, current);
            }
            ++current;
            ++next;
        }
    }
}

template <typename InputIt, typename OutputIt, typename Predicate>
OutputIt copyIf(InputIt p_sourceBeg, InputIt p_sourceEnd, OutputIt p_destBeg, Predicate p_pred)
{
    while (p_sourceBeg != p_sourceEnd)
    {
        if (p_pred(*p_sourceBeg))
        {
            *p_destBeg = *p_sourceBeg;
            ++p_destBeg;
        }
        ++p_sourceBeg;
    }
    return p_destBeg;
}

