#ifndef LEFTISTHEAP_H
#define LEFTISTHEAP_H


#define NULL_NPL -1

struct LeftistHeapNode
{
    LeftistHeapNode(int new_value)
        : p_left(nullptr), p_right(nullptr), value(new_value), npl(NULL_NPL)
    {
    }

    LeftistHeapNode * p_left, *p_right;
    int value;
    int npl;

};

class LeftistHeap
{
    public:
        LeftistHeap();
        LeftistHeap(const LeftistHeap & other_heap)
        void insert(int new_value);
        int get_max();
        int peek_max();
        LeftistHeap & merge_heap(LeftistHeap & other_heap);
        LeftistHeap & operator = (const LeftistHeap & other_heap);
        ~LeftistHeap();
    private:
        LeftistHeapNode * merge();
        void recompute_npl(LeftistHeapNode * p_current);
        void clear_heap(LeftistHeapNode * p_current);
        LeftistHeapNode * m_root;
};

#endif // LEFTISTHEAP_H
