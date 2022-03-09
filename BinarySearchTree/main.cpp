#include <iostream>
#include "LinkedList.h"
#include "Stack.h"
#include "BinarySearchTree.h"
using namespace std;

class Tester
{
public:
    void test_default_constructor();
    void test_five_inserts()
    {
        LinkedList the_list;
        for (int i = 0; i < 5; i++)
            the_list.insert_at_head(i + 1);
        the_list.display();
    }

    void test_insert_at_position()
    {
        cout << "Beginning insert at position test... inserting 10 things" << endl;
        LinkedList the_list;
        for (int i = 0; i < 10; i++)
            the_list.insert_at_head(i + 1);
        if (the_list.insert_at_position(4, 17))
        {
            cout << "Insert at position returned true." << endl;
        }
        else
        {
            cout << "Insert at position failed test.  [Returned False]" << endl;
        }
        the_list.display();
        cout << "Test passed if ... -> 7 -> 17 -> 6" << endl;
    }

    void test_insert_at_position_too_far()
    {
        cout << "Beginning insert at position test... inserting 10 things" << endl;
        LinkedList the_list;
        for (int i = 0; i < 10; i++)
            the_list.insert_at_head(i + 1);
        if (!the_list.insert_at_position(44, 17))
        {
            cout << "Insert at position correctly returned false." << endl;
        }
        else
        {
            cout << "Insert at position failed test.  [Returned True]" << endl;
        }
        the_list.display();
        cout << "Test passed if list is 10->9->...->1 with no insertion" << endl;
    }

    void test_remove_at_head_empty_list()
    {
        cout << "testing remove at head, with an empty list" << endl;
        LinkedList the_list;
        if (!the_list.remove_at_head())
        {
            cout << "Test Passed" << endl;
        }
        else
        {
            cout << "Test Failed" << endl;
        }
    }

    void test_remove_at_head()
    {
        cout << "testing remove at head, inserting five things..." << endl;
        LinkedList the_list;
        for (int i = 0; i < 5; i++)
            the_list.insert_at_head(i + 1);
        cout << "list values should be 5, 4, 3, 2, 1" << endl;
        the_list.display();
        the_list.remove_at_head();
        cout << "List values should be 4, 3, 2, 1" << endl;
        the_list.display();
    }

    void run_tests()
    {
        Tester t;
        t.test_five_inserts();
        cout << endl << endl;
        t.test_remove_at_head_empty_list();
        cout << endl << endl;
        t.test_remove_at_head();
        cout << endl << endl;
        t.test_insert_at_position();
        cout << endl << endl;
        t.test_insert_at_position_too_far();

    }
};

void stackTest()
{

    Stack s;
    int data;
    string cmd;
    cin >> cmd;
    while(cmd != "exit")
    {
        if (cmd == "push")
        {
            cin >> data;
            s.push(data);
        }
        else if (cmd == "pop")
        {
            try {

                cout << s.pop() << endl;

            }
            catch (underflow_error & ue)
            {
                cout << ue.what() << endl;
            }
        }
        else
        {

            try {

                cout << s.peek() << endl;

            }
            catch (underflow_error & ue)
            {
                cout << ue.what() << endl;
            }
        }
        s.display();
        cin >> cmd;
    }
}

int main() {

    BinarySearchTree<int> the_tree;
    int data;
    string cmd;
    cin >> cmd;
    while(cmd != "exit")
    {
        if (cmd == "insert")
        {
            cin >> data;
            the_tree.insert(data);
        }
        else if (cmd == "insertrec")
        {
            cin >> data;
            the_tree.insert_recursive(data);
        }
        else if (cmd == "find")
        {
            cin >> data;
            if (the_tree.find(data))
            {
                cout << "Data has been found." << endl;
            }
            else
            {
                cout << "Data has NOT been found" << endl;
            }
        }

        the_tree.displayTree();
        the_tree.inOrderTraversal();
        cin >> cmd;
    }
    return 0;
}
