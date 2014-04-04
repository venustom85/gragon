/*
   p38 2-3-17

   设计一个算法删除单链表L中值为x的结点的直接前驱结点。
   */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_17 {

typedef ListNode<int> node_t;

node_t * remove_before_x(node_t * head, int x)
{
    if (head == NULL) {
        return NULL;
    }

    node_t * prev = NULL;
    node_t * cur = head;
    node_t * new_head = head;

    while (cur != NULL) {
        if (cur->data == x && prev != NULL) {
            prev->data = cur->data;
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }

    return new_head;
}

struct TestData
{
    node_t * list_head;
    int data_x;
};

class Runner : public _Runner<TestData>
{
public:
    TestData * create_object()
    {
        node_t * L = list_read<int>(cin);
        if (L == NULL) {
            return NULL;
        }

        TestData * td = new TestData;
        td->list_head = L;
        cin >> td->data_x;

        return td;
    }
    void exec(TestData * obj)
    {
        node_t * L = obj->list_head;
        cout << "Origin list: " << L << endl;

        L = remove_before_x(L, obj->data_x);
        cout << "After remove element before '" << obj->data_x << "': " << L << endl;

        obj->list_head = L;
    }
    void destroy(TestData * obj)
    {
        if (obj != NULL) {
            list_destroy(obj->list_head);
            delete obj;
        }
    }
};

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_17
