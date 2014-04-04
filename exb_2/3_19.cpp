/*
   p39 2-3-19

   设A和B是两个单链表（带头结点），其表中元素递增有序。设计一个算法将A和B归并成一个按元素值递增有序的单链表C，要求铺助空间为O(1)，并分析算法的时间复杂度。
   */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_19 {

typedef ListNode<int> node_t;

node_t * merge(node_t * a_head, node_t * b_head)
{
    if (a_head == NULL || b_head == NULL) {
        return NULL;
    }

    node_t * pa = a_head->next;
    node_t * pb = b_head->next;
    node_t * c_head = new node_t;
    node_t * pc = c_head;

    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            pc->next = pa;
            pa = pa->next;
            a_head->next = pa;
        } else {
            pc->next = pb;
            pb = pb->next;
            b_head->next = pb;
        }
        pc = pc->next;
    }

    while (pa != NULL) {
        pc->next = pa;
        pa = pa->next;
        a_head->next = pa;
        pc = pc->next;
    }

    while (pb != NULL) {
        pc->next = pb;
        pb = pb->next;
        b_head->next = pb;
        pc = pc->next;
    }

    pc->next = NULL;

    return c_head;
}

class Runner : public MultiListRunner<int>
{
public:
    Runner()
        : MultiListRunner<int>(2)
    {}

    void exec(Lists * obj)
    {
        node_t * a = obj->at(0);
        node_t * b = obj->at(1);

        a = list_add_head_node(a);
        b = list_add_head_node(b);

        cout << "A: " << a->next << endl;
        cout << "B: " << b->next << endl;

        node_t * c = merge(a, b);
        cout << "C: " << c->next << endl;

        obj->at(0) = a;
        obj->at(1) = b;

        list_destroy(c);
    }
};

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_19
