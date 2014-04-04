/*
   p40 2-3-20

   已知单链表L（带头结点）是一个递增有序表，设计一个高效算法，删除表中data值在大于或等于min且小于或等于max之间的结点（若表中有这样的结点），同时释放被删结点的空间，这里min和max是两个给定的参数。
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_20 {

typedef ListNode<int> node_t;

node_t * remove_between(node_t * head, int min, int max)
{
    if (head == NULL) {
        return NULL;
    }

    if (min > max) {
        return head;
    }

    node_t * begin = head;
    node_t * end = NULL;

    for (; begin->next != NULL && begin->next->data < min; begin = begin->next)
        ;

    end = begin->next;
    for (; end != NULL && end->data <= max; end = end->next)
        ;

    node_t * h = begin->next;
    begin->next = end;

    while (h != end) {
        node_t * t = h;
        h = h->next;
        delete t;
    }

    return head;
}

struct TestData
{
    node_t * list_head;

    int min;
    int max;
};

class Runner : public _Runner<TestData>
{
public:
    void exec(TestData * obj)
    {
        obj->list_head = list_add_head_node(obj->list_head);
        cout << "Origin list: " << obj->list_head->next << endl;
        cout << "min: " << obj->min << ", max: " << obj->max << endl;
        obj->list_head = remove_between(obj->list_head, obj->min, obj->max);
        cout << "After remove: " << obj->list_head->next << endl;
    }

    TestData * create_object()
    {
        int length = 0;
        node_t * L = list_read<int>(std::cin, length);
        if (L == NULL && length < 0) {
            return NULL;
        }

        TestData * td = new TestData;
        td->list_head = L;

        std::cin >> td->min >> td->max;
        return td;
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

} // namespace exb_2_3_20

