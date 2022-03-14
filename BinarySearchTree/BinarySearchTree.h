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

    BSTNode<data_type> * p_left;
    BSTNode<data_type> * p_right;

    // BSTNode<data_type> * p_parent;

    data_type m_data;
};

template <typename data_type>
struct BSTPair
{
    BSTPair()
    : p_parent(nullptr), p_node(nullptr)
    {}
    BSTNode<data_type> * p_parent;
    BSTNode<data_type> * p_node;
};

class BinarySearchTreeTester;

template<typename datatype>
class BinarySearchTree {

    friend class BinarySearchTreeTester;

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<datatype> & other_tree);
    bool insert(datatype new_data);
    bool insert_recursive(datatype new_data);
    bool remove(datatype remove_value);
    bool find(datatype value_to_find);
    void displayTree();
    void inOrderTraversal();

    BSTPair<datatype> find_node(datatype value);
    BSTPair<datatype> get_successor(BSTNode<datatype> * p_node);
    bool remove_node(BSTPair<datatype> remove_pair);

    ~BinarySearchTree();
private:
    BSTNode<datatype> * p_root;
    void delete_subtree(BSTNode<datatype> * p_node);
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
BinarySearchTree<datatype>::~BinarySearchTree()
{
    delete_subtree(p_root);
}

template <typename datatype>
void BinarySearchTree<datatype>::delete_subtree(BSTNode<datatype> * p_node)
{
    if (p_node)
    {
        delete_subtree(p_node->p_left);
        delete_subtree(p_node->p_right);
        delete p_node;
    }
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
BSTPair<datatype> BinarySearchTree<datatype>::find_node(datatype value)
/*
 * What if the node we want to find is the root?
 * find that node, but doesn't have a parent
 */
{
    BSTPair<datatype> result;
    result.p_node = p_root; // creativity and ingenuity WILL BE PUNISHED!!!
    while(result.p_node && result.p_node->m_data != value)
    {
        if (value < result.p_node->m_data)
        {
            result.p_parent = result.p_node;
            result.p_node = result.p_node->p_left;
        }
        else
        {
            result.p_parent = result.p_node;
            result.p_node = result.p_node->p_right;
        }
    }

    if(!result.p_node)
    {
        result.p_parent = nullptr;
    }

    return result;
}

template <typename datatype>
BSTPair<datatype> BinarySearchTree<datatype>::get_successor(BSTNode<datatype> * p_node)
{
    BSTPair<datatype> result;
    if(p_node)
    {
        // go right
        result.p_parent = p_node;
        result.p_node = p_node->p_right;

        while(result.p_node && result.p_node->p_left)
        {
            // go left until you can't
            result.p_parent = result.p_node;
            result.p_node = result.p_node->p_left;
        }
    }

    return result;
}
template <typename datatype>
bool BinarySearchTree<datatype>::remove(datatype remove_value)
{
    BSTPair<datatype> remove_pair = find_node(remove_value);
    return remove_node(remove_pair);
}



template <typename datatype>
bool BinarySearchTree<datatype>::remove_node(BSTPair<datatype> remove_pair)
{
    // we're going to want a BSTNode * find_node and we're going to want a successor function
    // what if the value doesn't exist?
    if (!remove_pair.p_node)
    {
        return false; // didn't do anything return false no removal
    }
    // what if it's a leaf? we kinda want this edge case because if we don't have it,
    // we'll end up recursing again to delete a leaf, won't find a successor... handle the edge case there
    if(!remove_pair.p_node->p_left && !remove_pair.p_node->p_right)
    {
        // now we can delete the node and fix the parent's pointer
        if(!remove_pair.p_parent) // or remove_pair.p_node == p_root
        {
            // there's only one node in the tree without a parent.
            delete p_root;
            p_root = nullptr;
            return true;
        }
        if(remove_pair.p_parent->p_left == remove_pair.p_node)
        {
            remove_pair.p_parent->p_left = nullptr;
        }
        else
        {
            remove_pair.p_parent->p_right = nullptr;
        }
        delete remove_pair.p_node;
        return true;
    }

    // actually what remove is... find_successor time...
    BSTPair<datatype> successor_pair = get_successor(remove_pair.p_node);
    if (successor_pair.p_node)
    {
        // copy the data up to the node
        remove_pair.p_node->m_data = successor_pair.p_node->m_data;
        return remove_node(successor_pair);
    }
    else
    {
        if (remove_pair.p_node == p_root)
        {
            p_root = p_root->p_left;
            delete remove_pair.p_node;
            return true;
        }
        // no successor, but there's a left child.
        if (remove_pair.p_parent->p_left == remove_pair.p_node)
        {
            // something in here went weird
            remove_pair.p_parent->p_left = remove_pair.p_node->p_left;
        }
        else
        {
            // probably something in here too
            remove_pair.p_parent->p_right = remove_pair.p_node->p_left;
        }
        delete remove_pair.p_node;
    }

    return true;
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
