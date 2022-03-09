//
// Created by Administrator on 3/7/2022.
//

#ifndef CMSC341SPRING22_BINARYSEARCHTREE_H
#define CMSC341SPRING22_BINARYSEARCHTREE_H

#include <iostream>
using namespace std;

template <typename data_type>
struct BSTNode {
    BSTNode(data_type value = data_type())
        : p_left(nullptr), p_right(nullptr), m_data(value)
    {}

    BSTNode * p_left;
    BSTNode * p_right;

    data_type m_data;
};

template<typename datatype>
class BinarySearchTree {
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree<datatype> & other_tree);
        bool insert(datatype new_data);
        bool insert_recursive(datatype new_data);
        bool remove(datatype remove_value);
        bool find(datatype value_to_find);
        void displayTree();
        void inOrderTraversal();
    private:
        BSTNode<datatype> * p_root;

        BSTNode<datatype> * insert_recursive_helper(BSTNode<datatype> * p_current, datatype & new_data);
        void display_helper(BSTNode<datatype> * p_current, int tab_level=0);
        void inOrderTraversalHelper(BSTNode<datatype> * p_current);
};

template <typename datatype>
BinarySearchTree<datatype>::BinarySearchTree()
    : p_root(nullptr)
{

}
template <typename datatype>
BinarySearchTree<datatype>::BinarySearchTree(const BinarySearchTree<datatype> & other_tree)
{

}

template <typename datatype>
bool BinarySearchTree<datatype>::insert(datatype new_data)
{
    if (!p_root)
    {
        p_root = new BSTNode<datatype>(new_data);
        return true;
    }
    else
    {
        BSTNode<datatype> * p_current = p_root;
        //  while(!inserted) create some boolean flag, make sure the loop exits, etc
        while (true)
        {
            if (new_data < p_current->m_data)
            {
                if (p_current->p_left == nullptr)
                {
                    p_current->p_left = new BSTNode<datatype>(new_data);
                    return true;
                }
                else
                {
                    p_current = p_current->p_left;
                }
            }
            else
            {
                if (p_current->p_right == nullptr)
                {
                    p_current->p_right = new BSTNode<datatype>(new_data);
                    return true;
                }
                else
                {
                    p_current = p_current->p_right;
                }
            }
        }
    }
}

template <typename datatype>
bool BinarySearchTree<datatype>::remove(datatype remove_value)
{
    return false;
}

template <typename datatype>
bool BinarySearchTree<datatype>::find(datatype value_to_find)
{
    BSTNode<datatype> * p_find = p_root;
    while (p_find)
    {
        if (value_to_find < p_find->m_data)
        {
            p_find = p_find->p_left;
        }
        else if (value_to_find > p_find->m_data)
        {
            p_find = p_find->p_right;
        }
        else
        {
            return true;
        }
    }
    return false;
}

template <typename datatype>
void BinarySearchTree<datatype>::displayTree()
{
    if(p_root)
    {
        display_helper(p_root);
    }
    else
    {
        cout << "The tree is null" << endl;
    }

}

template <typename datatype>
void BinarySearchTree<datatype>::display_helper(BSTNode<datatype> * p_current, int tab_level)
{
    if(p_current)
    {
        display_helper(p_current->p_left, tab_level + 1);
        for (int i = 0; i < tab_level; i++)
        {
            cout << "\t";
        }
        cout << p_current->m_data << endl;

        display_helper(p_current->p_right, tab_level + 1);
    }
    else
    {
        // not for now...
    }
}


template <typename datatype>
bool BinarySearchTree<datatype>::insert_recursive(datatype new_data) {
    if(p_root)
    {
        insert_recursive_helper(p_root, new_data);
    }
    else
    {
        p_root = new BSTNode<datatype>(new_data);
    }
    return true;
}


template <typename datatype>
BSTNode<datatype> * BinarySearchTree<datatype>::insert_recursive_helper(BSTNode<datatype> * p_current, datatype & new_data)
{
    if (new_data < p_current->m_data)
    {
        if (p_current->p_left)
        {
            return insert_recursive_helper(p_current->p_left, new_data);
        }
        else
        {
            p_current->p_left = new BSTNode<datatype>(new_data);
            return p_current->p_left;
        }
    }
    else
    {
        if (p_current->p_right)
        {
            return insert_recursive_helper(p_current->p_right, new_data);
        }
        else
        {
            p_current->p_right = new BSTNode<datatype>(new_data);
            return p_current->p_right;
        }
    }
}


template <typename datatype>
void BinarySearchTree<datatype>::inOrderTraversal()
{
    if(p_root)
    {
        inOrderTraversalHelper(p_root);
    }
}

template <typename datatype>
void BinarySearchTree<datatype>::inOrderTraversalHelper(BSTNode<datatype> * p_current)
{
    if (p_current)
    {
        cout << "(";
        inOrderTraversalHelper(p_current->p_left);
        cout << p_current->m_data;
        inOrderTraversalHelper(p_current->p_right);
        cout << ")";
    }
}

#endif //CMSC341SPRING22_BINARYSEARCHTREE_H
