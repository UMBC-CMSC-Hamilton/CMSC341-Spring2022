#ifndef CMSC341SPRING22_LINKEDLIST_H
#define CMSC341SPRING22_LINKEDLIST_H


class LinkedList;

class LinkedListNode
{
    friend LinkedList;
    public:
        LinkedListNode(int new_data=0)
        {
            m_data = new_data;
            p_next = nullptr;
        }
    private:
        int m_data;
        LinkedListNode * p_next;
};

class LinkedList {
    public:
        LinkedList()
            : p_head(nullptr)
        {
            // p_head = nullptr;
        }

        /*
         * CRUD = Create Read Update Delete/Destroy
         *
         */

        void insert_at_head(int new_data);
        bool insert_at_position(int position, int new_data);
        void display();
        bool remove_by_value(int value);
        bool remove_at_position(int position);
        bool remove_at_head();
        ~LinkedList();

    private:
        void clear();
        void rec_delete(LinkedListNode * p_node);
        LinkedListNode * p_head;
};


#endif //CMSC341SPRING22_LINKEDLIST_H
