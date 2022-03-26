//
// Created by Administrator on 3/14/2022.
//

#ifndef CMSC341SPRING22_AVLTREE_H
#define CMSC341SPRING22_AVLTREE_H


struct Node {
    Node(int val=0)
    {
        p_left = nullptr;
        p_right = nullptr;
        height = 0;
        value = val;
    }
    Node * p_left, * p_right;
    int value;
    int height;
};

class AVLTree {
    public:
        void insert(int val);
    private:
        Node * insert_helper(Node * p_current, int value);
        int check_balance(Node * p_node);
        Node * rebalance(Node * p_node);
        Node * m_root;

        Node * rotate_right(Node * p_node);
        Node * rotate_left(Node * p_node);
};




#endif //CMSC341SPRING22_AVLTREE_H
