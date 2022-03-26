//
// Created by Administrator on 3/14/2022.
//

#include "AVLTree.h"

void AVLTree::insert(int val)
{
    if (!m_root)
    {
        m_root = new Node(val);
    }
    else
    {
        m_root = insert_helper(m_root, val);
    }
}

Node * AVLTree::insert_helper(Node * p_current, int value)
{
    if (!p_current)
    {
        return new Node(value);
    }
    if (value < p_current->value)
    {
        p_current->p_left = insert_helper(p_current->p_left, value);
    }
    else
    {
        p_current->p_right = insert_helper(p_current->p_right, value);
    }

    p_current = rebalance(p_current);
}


Node * AVLTree::rotate_right(Node * p_node)
{
    if(p_node)
    {
        if(!p_node->p_right)
        {
            cout << "called rotate left with no right child to move up" << endl;
            return p_node;
        }
        Node * new_root = p_node->p_right;
        Node * left_right = p_node->p_left->p_right;
        p_node->p_left->p_right = p_node;
        p_node->p_left = left_right;
        return new_root;
    }
    else
    {
        cout << "called rotate on null node" << endl;
    }
    return p_node;
}
Node * AVLTree::rotate_left(Node * p_node)
{
    if(p_node)
    {
        if(!p_node->p_right)
        {
            cout << "called rotate left with no right child to move up" << endl;
            return p_node;
        }
        Node * new_root = p_node->p_right;
        Node * right_left = p_node->p_right->p_left;
        p_node->p_right->p_left = p_node;
        p_node->p_right = right_left;
        return new_root;
    }
    else
    {
        cout << "called rotate on null node" << endl;
    }
    return p_node;
}

int AVLTree::check_balance(Node * p_node)
{
    if(p_node->p_left && p_node->p_right)
    {
        return p_node->p_left->height - p_node->p_right->height;
    }
    else if (p_node->p_left)
    {
        return p_node->p_left->height + 1;
    }
    else if (p_node->p_right)
    {
        return -1 - p_node->p_right->height;
    }
    else
    {
        return 0;
    }
}

Node * AVLTree::rebalance(Node * p_node)
{
    compute_height(p_node->p_left);
    compute_height(p_node->p_right);
    int balance_check = check_balance(p_node);
    if (balance_check <= -2)
    {
        // right heavy

        // zag zag
        // zag zig

        // p_node->p_right is the heavy one

        /**
         * If p_node->p_right->p_left->height > p_node->p_right->p_right->height
         * zag zig
         *
         * else zag zag
         */
    }
    else if (balance_check >= 2)
    {
        // left heavy

        // zig zig
        // zig zag
    }
}