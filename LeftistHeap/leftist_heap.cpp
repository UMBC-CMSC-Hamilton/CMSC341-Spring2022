#include "LeftistHeap.h"
#include <stdexcept>
#include <iostream>
using namespace std;

LeftistHeap::LeftistHeap()
    : m_root(nullptr)
{
}

LeftistHeap::LeftistHeap(const LeftistHeap & other_heap)
{
    m_root = copy_heap(other_heap.m_root);
}

LeftistHeapNode * LeftistHeap::copy_heap(LeftistHeapNode * p_current)
{
    if(p_current)
    {
        LeftistHeapNode * the_new_node = new LeftistHeapNode(p_current->value);
        the_new_node->npl = p_current->npl;
        the_new_node->p_left = copy_heap(p_current->p_left);
        the_new_node->p_right = copy_heap(p_current->p_right);
        return the_new_node;
    }
    return nullptr;
}

LeftistHeap & LeftistHeap::operator = (const LeftistHeap & other_heap)
{
    if(&other_heap == this)
    {
        return *this;
    }

    clear_heap(m_root);

    /// set the priority function of this thing to the other_heap->pri
    m_root = copy_heap(other_heap.m_root);
    return *this;
}

void LeftistHeap::insert(int new_value)
{
    LeftistHeapNode * p_new = new LeftistHeapNode(new_value);
    m_root = merge(m_root, p_new);
}

int LeftistHeap::get_max()
{
    if (!m_root)
    {
        throw underflow_error("There was nothing in our heap.");
    }
    int old_max = m_root->value;
    LeftistHeapNode * p_remember = m_root;
    m_root = merge(m_root->p_left, m_root->p_right);
    delete p_remember;
    /// more stuff happens here
    return old_max;
}
int LeftistHeap::peek_max()
{
    if (!m_root)
    {
        throw underflow_error("There was nothing in our heap.");
    }
    return m_root->value;
}
LeftistHeap & LeftistHeap::merge_heap(LeftistHeap & other_heap)
{
    if(this == &other_heap)
    {
        return *this;
    }
    /// check priority function here.
    m_root = merge(m_root, other_heap.m_root);
    /// do this to avoid errors that are bizarre and really hard to figure out...
    other_heap.m_root = nullptr;
    return *this;
}


LeftistHeap::~LeftistHeap()
{
    clear_heap(m_root);
}

void clear_heap(LeftistHeapNode * p_current)
{
    if (p_current)
    {
        clear_heap(p_current->p_left);
        clear_heap(p_current->p_right);
        delete p_current;
    }
}

LeftistHeapNode * LeftistHeap::merge(LeftistHeapNode * p_first, LeftistHeapNode * p_second)
{
    if (!p_first)
    {
        return p_second;
    }
    if (!p_second)
    {
        return p_first;
    }

    LeftistHeapNode * p_current = nullptr;
    /// both are not null... so we can check the values
    if (p_first->value >= p_second->value)
    {
        p_first->p_right = merge(p_first->p_right, p_second);
        p_current = p_first;
    }
    else
    {
        p_second->p_right = merge(p_second->p_right, p_first);
        p_current = p_second;
    }
    recompute_npl(p_current->p_left);
    recompute_npl(p_current->p_right);
    if (p_current->p_left->npl < p_current->p_right->npl)
        swap(p_current->p_left, p_current->p_right);
    return p_current;
}

void LeftistHeap::recompute_npl(LeftistHeapNode * p_current)
{
    if(!p_current)
    {
        return;
    }

    if(!p_current->p_left || !p_current->p_right)
    {
        p_current->npl = 0;
    }
    else
    {
        if (p_current->p_left->npl < p_current->p_right->npl)
        {
            p_current->npl = 1 + p_current->p_left->npl;
        }
        else
        {
            p_current->npl = 1 + p_current->p_right->npl;
        }
    }
}
