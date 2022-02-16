//
// Created by Administrator on 2/14/2022.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

void LinkedList::insert_at_head(int new_data)
{
    LinkedListNode * new_node = new LinkedListNode(new_data);
    new_node->p_next = p_head;
    // even if the head is nullptr we're still ok
    p_head = new_node;
}

bool LinkedList::insert_at_position(int position, int new_data)
{
    LinkedListNode * p_current = p_head;
    int count = 0;
    if (position == 0)
    {
        insert_at_head(new_data);
        return true;
    }
    while(p_current != nullptr && count < position - 1)
    {
        count++;
        p_current = p_current->p_next;
    }

    if (count != position - 1)
    {
        return false;
    }
    LinkedListNode * p_new_element = new LinkedListNode(new_data);
    p_new_element->p_next = p_current->p_next;
    p_current->p_next = p_new_element;
    return true;
}
void LinkedList::display()
{
    LinkedListNode * p_current = p_head;
    int count = 0;

    if (!p_head) // p_head == nullptr
    {
        cout << "Empty List";
    }
    while(p_current != nullptr)
    {
        cout << "[" << count << ", " << p_current->m_data << "] -> ";
        count++;
        p_current = p_current->p_next;
    }
    cout << endl;
}

bool LinkedList::remove_by_value(int value)
/*
 *  Remove only the first thing we find with that value.
 */
{
    if (!p_head)
    {
        return false;
    }
    LinkedListNode * p_current = p_head;
    // if the value of p_head->m_data == value we ignore it...
    if (p_head->m_data == value)
    {
        return remove_at_head();
    }

    // LinkedListNode * p_previous = p_head;
    while(p_current->p_next && p_current->p_next->m_data != value)
    {
        // p_current->p_next is protecting you from
        // potentially seg faulting on the p-current->p_next->m_data
        // p_previous = p_current; // p_previous->p_next;
        p_current = p_current->p_next;
    }
    if (p_current->p_next == nullptr)
    {
        // scanned to the end didn't find it
        return false;
    }
    auto * p_delete = p_current->p_next;
    p_current->p_next = p_current->p_next->p_next;
    delete p_delete;
    return true;
}

bool LinkedList::remove_at_head()
{
    if (p_head == nullptr)
    {
        return false;
    }
    LinkedListNode * p_remember = p_head;
    p_head = p_head->p_next;
    delete p_remember;
    return true;
}

bool LinkedList::remove_at_position(int position)
{

    LinkedListNode * p_current = p_head;
    int count = 0;
    if (position == 0)
    {
        return remove_at_head();
    }
    while(p_current != nullptr && count < position - 1)
    {
        count++;
        p_current = p_current->p_next;
    }

    if (count != position - 1)
    {
        return false;
    }


    LinkedListNode * old_next = p_current->p_next;
    if (p_current->p_next == nullptr)
    {
        return false;
    }
    p_current->p_next = p_current->p_next->p_next;
    delete old_next;

    return true;
}

LinkedList::~LinkedList()
{
    rec_delete(p_head);
    p_head = nullptr;
}

void LinkedList::rec_delete(LinkedListNode * p_node)
{
    if (p_node)
    {
        rec_delete(p_node->p_next);
        delete p_node;
    }
}

void LinkedList::clear()
/*
 * basically the same as rec_delete except with while.
 * what happens to an empty list? is that some kind of nullptr / seg fault
 * what happens to the head node, is that different?
 */
{
    if (p_head)
    {
        auto * p_current = p_head;
        auto * the_next_one = p_head->p_next;
        while(p_current)
        {
            p_current = the_next_one;
            the_next_one = the_next_one->p_next;
            delete p_current;
        }
        // we don't have to check if p_head == nullptr
        // remember that delete nullptr (C++ will save you).
        delete p_head;
        p_head = nullptr;
    }
}